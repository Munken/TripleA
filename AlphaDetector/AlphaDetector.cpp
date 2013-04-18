#include "stdafx.h"
#include "AlphaDetector.h"
#include "Constants.h"
#include "DownStreamCalibration.h"
#include "UpstreamCalibration.h"
#include "LabToCM.h"
#include <TArc.h>
#include <TLine.h>
#include <algorithm>



using namespace std;
using namespace constants;
EnergyCalibration* AlphaDetector::downStreamCalibration = //new EnergyCalibration("../../Kalibrering/calib_s3_1000_ns_apr2013M.dat");
	new DownStreamDeadCalibration("../../Kalibrering/Hans_1000_2M.dat", "../../Range/he4si");
EnergyCalibration* AlphaDetector::upStreamCalibration = //new EnergyCalibration("../../Kalibrering/calib_s3_64_ns_apr2013M.dat");
	new UpStreamDeadCalibration("../../Kalibrering/Hans_64_2M.dat", "../../Range/he4si");
const int AlphaDetector::ENERGY_CUT = 1900;
const double AlphaDetector::SQRT_3 = sqrt(3);

AlphaDetector::AlphaDetector(float beamEnergy, char* output, char* title, float cut /*= 50*/, char* plotOptions /*= ""*/) : 
	cut(cut), plotOptions(plotOptions), nAlpha(0), spectrum(title, title, 3096, 400, 8500), dalitz("Up", Form("Dalitz: %s", title), 100, -0.4, 0.4, 100, -0.4, 0.4)
	
{
	this -> output = output;
	Q = (11./12. * beamEnergy + BORON_11_MASS + PROTON_MASS) - 3*ALPHA_MASS;
	cout << Q << endl;
	Qdistro = TH1F("Q", "Q", 200, 0.8*Q, 1.2*Q);
	spectrum.SetXTitle("Alpha E");
	spectrum.SetYTitle("Count");
	spectrum.GetYaxis()->SetTitleOffset(2);

	transformer = new LabToCM(beamEnergy, ALPHA_MASS);
}


void AlphaDetector::analyze(Selector* s) {
	
	int nDown = s -> Nfe4;
	int nUp = s -> Nfe3;
	if (nDown + nUp < 2 || (nDown < 1 || nUp < 1)) return;

	calculateEnergies(nDown, s, nUp);

	if (nDown + nUp == 2) {
		findDoubleAlphas();
	}
	else {
		findTripleAlphas(nDown, nUp, downStreamEnergy, upStreamEnergy);
		findTripleAlphas(nUp, nDown, upStreamEnergy, downStreamEnergy);
	}
}

void AlphaDetector::calculateEnergies( int nDown, Selector* s, int nUp )
{
	/*if (nDown + nUp >= 2) {
		cout << "Down: " << nDown << endl;
		cout << "Up: " << nUp << endl;
	}*/
	for (int i = 0; i < nDown; i++) {
		int strip = s -> Nsfe4[i];
		short channel = s -> Ef4[i];
		double energy = downStreamCalibration -> getEnergyFrontStrip(strip, channel);

		double angle = downStreamAngle.getPolar(strip);
		std::pair<double, double> transformed = transformer -> transform(energy, angle);
		downStreamEnergy[i] = transformed.first;

	}

	
	for (int i = 0; i < nUp; i++) {
		int strip = s -> Nsfe3[i];
		short channel = s -> Ef3[i];
		double energy = upStreamCalibration -> getEnergyFrontStrip(strip, channel);

		double angle = upStreamAngle.getPolar(strip);
		std::pair<double, double> transformed = transformer -> transform(energy, angle);
		upStreamEnergy[i] = transformed.first;

	}
}

void AlphaDetector::terminate() {
	char* dir = "result";


	TCanvas dp("Up", "Up", 1200, 1200);
	spectrum.Draw();
	dp.SaveAs(Form("%s/%s.png", dir, output));

	dp.SetLogy();
	dp.SaveAs(Form("%s/LOGY-%s.png", dir, output));

	TCanvas dL("Dalitz", "Dalitz", 1200, 1200);
	dalitz.DrawNormalized();

	TArc arc(0,0, 1./3);
	arc.SetLineColor(kRed);
	arc.Draw();

	//double Q1 = 2./3*(CARBON_12_MASS - BERYLLIUM_8_MASS - ALPHA_MASS) / Q + 1./3;
	////cout << Q1 << endl;
	//TLine lBe(-1./3, Q1, 1./3, Q1);
	//lBe.SetLineColor(kRed);
	//lBe.Draw();


	TLine l1(-1/SQRT_3, -1./3, 0, 2./3);
	l1.SetLineColor(kRed);
	l1.Draw();

	TLine l2(-1/SQRT_3, -1./3, 1/SQRT_3, -1./3);
	l2.SetLineColor(kRed);
	l2.Draw();

	TLine l3(1/SQRT_3, -1./3, 0, 2./3);
	l3.SetLineColor(kRed);
	l3.Draw();
	
	dalitz.DrawNormalized("SAME");
	
	
	dL.SaveAs(Form("%s/Dalitz-%s.png", dir, output));
	


	TCanvas dQ("Q", "Q", 1200, 1200);
	Qdistro.DrawNormalized();
	dQ.SaveAs(Form("%s/QDistro-%s.png", dir, output));

	printf("Number of alphas: %d\n", nAlpha);	
}

void AlphaDetector::findTripleAlphas( int shortLength, int largeLength, double* shorter, double* larger )
{
	for (int i = 0; i < shortLength; i++) {
		if (shorter[i] < 1900 && shorter[i] > 1700) continue;
		for (int j = 0; j < largeLength - 1; j++) {
			if (larger[j] < 1900 && larger[j] > 1700) continue;
			for (int k = j+1; k < largeLength; k++) {
				if (larger[k] < 1900 && larger[k] > 1700) continue;

					double T = shorter[i] + larger[j] + larger[k];
					double diff = abs(T-Q);

					if (diff  < cut) {
						alphaEnergies[0] = shorter[i];
						alphaEnergies[1] = larger[j];
						alphaEnergies[2] = larger[k];

						

						//sort(alphaEnergies, alphaEnergies+3);
						random_shuffle(alphaEnergies, alphaEnergies+3);

						//Hans
						double x = (alphaEnergies[2]/Q + 2. * alphaEnergies[1]/Q - 1.) / SQRT_3;
						double y = alphaEnergies[2] / Q - 1./3.;

						if (pow(x,2)+pow(y,2) > 1./9) return;

						nAlpha += 3;
						// SLAC
						/*double x = SQRT_3 * (alphaEnergies[0] - alphaEnergies[1]) / Q;
						double y = (2*alphaEnergies[2] - alphaEnergies[1] - alphaEnergies[0]) / Q;*/
						dalitz.Fill(x, y);
						
						Qdistro.Fill(T);
						for (int i = 0; i < 3; i++) {
							spectrum.Fill(alphaEnergies[i]);
						}
				}
			}
		}
	}
}

void AlphaDetector::findDoubleAlphas( ) {
	if (upStreamEnergy[0] < ENERGY_CUT || downStreamEnergy[0] < ENERGY_CUT) return;

	double diff = Q - upStreamEnergy[0] - downStreamEnergy[0];

	if (diff <= 0) return;

	double T[3] = {upStreamEnergy[0], downStreamEnergy[0], diff};
	random_shuffle(T, T+3);
	double x = (T[1]/Q + 2. * T[0]/Q - 1.) / SQRT_3;
	double y = T[1] / Q - 1./3.;
	if (pow(x,2)+pow(y,2) > 1./9) return;

	nAlpha += 3;
	dalitz.Fill(x, y);


	for (int i = 0; i < 3; i++) {
		spectrum.Fill(T[i]);
	}
}


