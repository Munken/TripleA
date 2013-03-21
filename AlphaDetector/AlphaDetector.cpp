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
EnergyCalibration* AlphaDetector::downStreamCalibration = new DownStreamCalibration("../../Kalibrering/calib_s3_1000DLM.dat", "../../Range/he4si");
EnergyCalibration* AlphaDetector::upStreamCalibration = new UpStreamCalibration("../../Kalibrering/calib_s3_64DLM.dat", "../../Range/he4si");
const double AlphaDetector::SQRT_3 = 1.7320508075688772935274463415059;

AlphaDetector::AlphaDetector(float beamEnergy, char* output, char* title, float cut /*= 0.5*/, char* plotOptions /*= ""*/) : 
	cut(cut), plotOptions(plotOptions), nAlpha(0), spectrum(title, title, 3096, 400, 8500), dalitz("Up", Form("Dalitz: %s", title), 100, -0.5, 0.5, 100, -0.5, 0.5)
	
{
	this -> output = output;
	Q = (11./12. * beamEnergy + BORON_11_MASS + PROTON_MASS) - 3*ALPHA_MASS;
	Qdistro = TH1F("Q", "Q", 200, 0.8*Q, 1.2*Q);
	spectrum.SetXTitle("Alpha E");
	spectrum.SetYTitle("Count");
	spectrum.GetYaxis()->SetTitleOffset(2);

	transformer = new LabToCM(beamEnergy, ALPHA_MASS);
}


void AlphaDetector::analyze(Selector* s) {
	
	int nDown = s -> Nfe4;
	int nUp = s -> Nfe3;
	if (nDown + nUp < 3 && (nDown < 0 && nUp < 0)) return;

	calculateEnergies(nDown, s, nUp);

	findTripleAlphas(nDown, nUp, downStreamEnergy, upStreamEnergy);
	findTripleAlphas(nUp, nDown, upStreamEnergy, downStreamEnergy);
}

void AlphaDetector::calculateEnergies( int nDown, Selector* s, int nUp )
{
	for (int i = 0; i < nDown; i++) {
		int strip = s -> Nsfe4[i];
		short channel = s -> Ef4[i];
		double energy = downStreamCalibration -> getEnergyCircularStrip(strip, channel);

		double angle = downStreamAngle.getAzimuthMin(strip);
		std::pair<double, double> transformed = transformer -> transform(energy, angle);
		downStreamEnergy[i] = transformed.first;
	}

	for (int i = 0; i < nUp; i++) {
		int strip = s -> Nsfe3[i];
		short channel = s -> Ef3[i];
		double energy = upStreamCalibration -> getEnergyCircularStrip(strip, channel);

		double angle = upStreamAngle.getAzimuthMin(strip);
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

	/*TArc arc(0,0, 1);
	arc.SetLineColor(kRed);
	arc.Draw();

	TLine l1(-SQRT_3, -1, 0, 2);
	l1.SetLineColor(kRed);
	l1.Draw();

	TLine l2(-SQRT_3, -1, SQRT_3, -1);
	l2.SetLineColor(kRed);
	l2.Draw();

	TLine l3(SQRT_3, -1, 0, 2);
	l3.SetLineColor(kRed);
	l3.Draw();*/

	TArc arc(0,0, 1./3);
	arc.SetLineColor(kRed);
	arc.Draw();

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
	
	
	dL.SaveAs(Form("%s/Dalitz-HANS1-%s.png", dir, output));
	


	TCanvas dQ("Q", "Q", 1200, 1200);
	Qdistro.DrawNormalized();
	dQ.SaveAs(Form("%s/QDistro-%s.png", dir, output));

	printf("Number of alphas: %d\n", nAlpha);	
}

void AlphaDetector::findTripleAlphas( int shortLength, int largeLength, double* shorter, double* larger )
{
	for (int i = 0; i < shortLength; i++) {
		for (int j = 0; j < largeLength - 1; j++) {
			for (int k = j+1; k < largeLength; k++) {

				double T = shorter[i] + larger[j] + larger[k];
				double diff = abs(T-Q);

				if (diff / Q < cut) {
					nAlpha += 3;
					alphaEnergies[0] = shorter[i];
					alphaEnergies[1] = larger[j];
					alphaEnergies[2] = larger[k];

					Qdistro.Fill(T);
					for (int i = 0; i < 3; i++) {
						spectrum.Fill(alphaEnergies[i]);
					}

					//sort(alphaEnergies, alphaEnergies+3);
					random_shuffle(alphaEnergies, alphaEnergies+3);

					//Hans
					double x = (alphaEnergies[0]/Q + 2 * alphaEnergies[1]/Q - 1) / SQRT_3;
					double y = alphaEnergies[0] / Q - 1./3.;

					// SLAC
					/*double x = SQRT_3 * (alphaEnergies[0] - alphaEnergies[1]) / Q;
					double y = (2*alphaEnergies[2] - alphaEnergies[1] - alphaEnergies[0]) / Q;*/
					dalitz.Fill(x, y);
				}
			}
		}
	}
}

