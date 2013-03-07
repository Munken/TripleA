#include "stdafx.h"
#include "AlphaDetector.h"
#include "Constants.h"
#include "DownStreamCalibration.h"
#include "UpstreamCalibration.h"



using namespace std;
using namespace constants;
EnergyCalibration* AlphaDetector::downStreamCalibration = new DownStreamCalibration("../../Kalibrering/calib_s3_1000DLM.dat", "../../Range/he4si");
EnergyCalibration* AlphaDetector::upStreamCalibration = new UpStreamCalibration("../../Kalibrering/calib_s3_64DLM.dat", "../../Range/he4si");

AlphaDetector::AlphaDetector(float beamEnergy, char* output, char* title, float cut /*= 0.5*/) : 
	cut(cut), plotOptions(plotOptions), nAlpha(0)
{
	this -> output = output;
	Q = (beamEnergy + BORON_11_MASS2 + PROTON_MASS2) - 3*ALPHA_MASS2;

	hist = TH1F("HistUpP", title, 3096, 400, 8500);
	hist.SetXTitle("Alpha E");
	hist.SetYTitle("Count");
	hist.GetYaxis()->SetTitleOffset(2);
}


void AlphaDetector::analyze(Selector* s) {
	
	int nDown = s -> Nfe4;
	int nUp = s -> Nfe3;
	if (nDown + nUp < 3 && (nDown < 0 && nUp < 0)) return;

	calculateEnergies(nDown, s, nUp);

	double* shorter = downStreamEnergy;
	double* larger = upStreamEnergy;
	int shortLength = nDown;
	int largeLength = nUp;

	if (nDown > nUp) {
		shorter = upStreamEnergy;
		larger = downStreamEnergy;
		shortLength = nUp;
		largeLength = nDown;
	}

	#pragma omp parallel for
	for (int i = 0; i < shortLength; i++) {
		for (int j = 0; j < largeLength - 1; j++) {
			for (int k = j+1; k < largeLength; k++) {
				
				double T = shorter[i] + larger[j] + larger[k];
				double diff = abs(T-Q);

				if (diff / Q < cut) {
					nAlpha += 3;
					hist.Fill(shorter[i]);
					hist.Fill(larger[j]);
					hist.Fill(larger[k]);
				}
			}
		}
	}
}

void AlphaDetector::calculateEnergies( int nDown, Selector* s, int nUp )
{
	for (int i = 0; i < nDown; i++) {
		int strip = s -> Nsfe4[i];
		short channel = s -> Ef4[i];
		downStreamEnergy[i] = downStreamCalibration -> getEnergyCircularStrip(strip, channel);
	}

	for (int i = 0; i < nUp; i++) {
		int strip = s -> Nsfe3[i];
		short channel = s -> Ef3[i];
		upStreamEnergy[i] = upStreamCalibration -> getEnergyCircularStrip(strip, channel);
	}
}

void AlphaDetector::terminate() {
	char* dir = "result";


	TCanvas dp("Up", "Up", 1200, 1200);
	hist.Draw(plotOptions);
	dp.SaveAs(Form("%s/%s.png", dir, output));

	dp.SetLogy();
	dp.SaveAs(Form("%s/LOGY-%s.png", dir, output));
	printf("Number of alphas: %d\n", nAlpha);
}

