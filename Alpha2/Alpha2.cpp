#include "stdafx.h"
#include "Alpha2.h"
#include "Selector.h"
#include <TCanvas.h>
#include <iostream>
#include "AngleCalculator.h"
#include "SquareAngleCalculator.h"
#include "UpStreamAngleCalculator.h"
#include "DownStreamAngleCalculator.h"
#include "Constants.h"
#include "LabToCM.h"
#include <algorithm>
#include "TArc.h"
#include "UpstreamCalibration.h"
#include "DownStreamCalibration.h"
#include "TLine.h"


using namespace std;
using namespace constants;

const double SQRT_3 = sqrt(3);

// Her skal skiftes til 6 µm dødlags kalibrering for de runde. 
EnergyCalibration* Alpha2::energyCalibration[4] = {
	new EnergyCalibration(EnergyCalibration::CAL1_PATH, 16),
	new EnergyCalibration(EnergyCalibration::CAL2_PATH, 16),
	new UpStreamDeadCalibration(EnergyCalibration::CAL3_PATH, EnergyCalibration::HE4_RANGE, false),
	new DownStreamDeadCalibration(EnergyCalibration::CAL4_PATH, EnergyCalibration::HE4_RANGE, false)
	//new EnergyCalibration(EnergyCalibration::CAL3_PATH),
	//new EnergyCalibration(EnergyCalibration::CAL4_PATH)
};

AngleCalculator* Alpha2::angleCalculators[4] = {
	new SquareAngleCalculator(32, -2.52243, -7.27611e+00),
	new SquareAngleCalculator(-3.42838e1, 3.60734, -8.11409e+00),
	new UpstreamAngleCalculator(),
	new DownStreamAngleCalculator()
};

SystemTransformation* Alpha2::transformer = new LabToCM(2000, ALPHA_MASS);




Alpha2::Alpha2( char* output, char* title, double maxDiff) : output(output), maxDiff(maxDiff), 
	dalitz("Up", Form("Dalitz: %s", title), 120, -0.4, 0.4, 120, -0.4, 0.4),
	spectrum(title, ";Energi [keV];Tællinger", 3096, 400, 7100),
	upperCut(1560), lowerCut(1460)
{
	energy = new double*[N_DETECTORS];
	energy[0] = new double[16];
	energy[1] = new double[16];
	energy[2] = new double[24];
	energy[3] = new double[24];

	Q = (11./12. * 2000 + BORON_11_MASS + PROTON_MASS) - 3*ALPHA_MASS;


	//hist = TH2F("HistUpP", title, 4096, 400, 9000, 4096, 400, 7000);
	//hist.SetXTitle("Downstream E");
	//hist.SetYTitle("Upstream E");
	spectrum.GetYaxis()->SetTitleOffset(1.7);

	for (int i = 0; i < N_DETECTORS; i++) {
		detectorSpectrum[i] = TH1F(Form("%i", i), Form("%i", i), 3096, 400, 7300);
	}
}


void Alpha2::analyze(Selector* s) {
	/*N[0] = s -> Nfe1;
	N[1] = s -> Nfe2;
	N[2] = s -> Nfe3;
	N[3] = s -> Nfe4;*/
	int nHits = 0;
	for (int i = 0; i < N_DETECTORS; i++) {
		Int_t* n = s -> Nfe[i];
		N[i] = *n;
		nHits += *n;
	}

	if (nHits < 2) return;
	determineEnergies(s);
	
	if (nHits == 2) {
		//findDoubleCoincidence();
	} else {
		findTripleAlphas();
	}
	

}


void Alpha2::findTripleAlphas()
{
	for (int i = 0; i < N_DETECTORS; i++) {
		for (int j = i + 1; j < N_DETECTORS; j++) {

			// Two alphas in one detector and one in another. 
			if (N[i] + N[j] >= 3) {
				findTwoDetectorCoincidence(N[i], energy[i], N[j], energy[j]);
				findTwoDetectorCoincidence(N[j], energy[j], N[i], energy[i]);
			}

			// One alpha in 3 detectors
			for (int k = j + 1; k < N_DETECTORS; k++) {
				if (N[i] + N[j] + N[k] < 3) continue;
				findTripleDetectorCoincidence(N[i], energy[i], N[j], energy[j], N[k], energy[k]);
			}
		}
	}
}


void Alpha2::findTwoDetectorCoincidence( int N1, double* E1, int N2, double* E2 ) {
	for (int i = 0; i < N1; i++) {
		if (E1[i] < 0 || (E1[i] > lowerCut && E1[i] < upperCut)) continue;
		for (int j = i + 1; j < N1; j++) {
			if (E1[j] < 0 || (E1[j] > lowerCut && E1[j] < upperCut)) continue;
			for (int k = 0; k < N2; k++) {
				if (E2[k] < 0 || (E2[k] > lowerCut && E2[k] < upperCut)) continue;

				double sum = E1[i] + E1[j] + E2[k];
				double diff = abs(sum - Q);

				if (diff > maxDiff) continue;
				alphaEnergies[0] = E1[i];
				alphaEnergies[1] = E1[j];
				alphaEnergies[2] = E2[k];

				fillPlots();
			}
		}
	}
}


void Alpha2::findTripleDetectorCoincidence( int N1, double* E1, int N2, double* E2, int N3, double* E3 )
{
	for (int i = 0; i < N1; i++) {
		if (E1[i] < 0 || (E1[i] > lowerCut && E1[i] < upperCut)) continue;

		for (int j = 0; j < N2; j++) {
			if (E2[j] < 0 || (E2[j] > lowerCut && E2[j] < upperCut)) continue;

			for (int k = 0; k < N3; k++) {
				if (E3[j] < 0 || (E3[k] > lowerCut && E3[k] < upperCut)) continue;

				double sum = E1[i] + E2[j] + E3[k];
				double diff = abs(sum - Q);

				if (diff > maxDiff) continue;
				alphaEnergies[0] = E1[i];
				alphaEnergies[1] = E2[j];
				alphaEnergies[2] = E3[k];

				fillPlots();
			}
		}
	}
}

void Alpha2::fillPlots() {
	random_shuffle(alphaEnergies, alphaEnergies+3);

	double x = (alphaEnergies[2]/Q + 2. * alphaEnergies[1]/Q - 1.) / SQRT_3;
	double y = alphaEnergies[2] / Q - 1./3.;

	if (pow(x,2) + pow(y,2) > 1/9.) {
		return;
	}
	dalitz.Fill(x, y);

	for (int i = 0; i < 3; i++) {
		spectrum.Fill(alphaEnergies[i]);
	}
}



void Alpha2::terminate() {
	char* dir = "result";
	
	// Draw dalitz plot
	TCanvas dp("Up", "Up", 1200, 1200);
	dp.SetLeftMargin(0.15);
	dalitz.Draw("COLZ");

	//TArc arc(0,0, 1./3);
	//arc.SetLineColor(kRed);
	//arc.Draw();
	//dalitz.DrawNormalized("SAME");
	// 
	//double Q1 = 6.9491e+03;
	//  mB + mP - mBe - mA + 11/12 * Eb
	double eCM = BORON_11_MASS + PROTON_MASS - BERYLLIUM_8_MASS - ALPHA_MASS + 11./12 * 2000;
	double Q1 = 2./3*eCM;
	double Q2 = 2./3*(eCM - 3000);
	double y = Q1 / Q - 1./3.;
	double y2 = Q2 / Q - 1./3.;

	TLine l(-1/SQRT_3, y, 1/SQRT_3, y);
	l.SetLineColor(kRed);
	l.DrawClone("Same");

	l = TLine(-1/SQRT_3, y2, 1/SQRT_3, y2);
	l.SetLineColor(kRed);
	l.DrawClone("SAME");

	dp.SaveAs(Form("%s/%s-DALITZ.png", dir, output));


	// Draw spectrum

	TCanvas spet("Up", "Up", 1200, 1200);
	spet.SetLeftMargin(0.15);
	spectrum.Draw("");
	spet.SaveAs(Form("%s/%s-spec.png", dir, output));
	determinePeakPositions();

	// Draw detector spectrum
	
	spet.SetLogy();
	for (int i = 0; i < N_DETECTORS; i++) {
		detectorSpectrum[i].Draw();
		spet.SaveAs(Form("%s/%s-spec%i.png", dir, output,i));
	}
}

void Alpha2::determineEnergies(Selector* s)
{
	for (int i = 0; i < 2; i++) {
		writeSquareEnergies(energyCalibration[i], angleCalculators[i], energy[i], s -> Ef[i], s -> Nsfe[i], N[i], s -> Eb[i], s -> Nsbe[i], s -> Nbe[i][0], i == 1);
	}

	for (int i = 2; i < N_DETECTORS; i++) {
		writeEnergies(energyCalibration[i], angleCalculators[i], energy[i], s -> Ef[i], s -> Nsfe[i], N[i]);
	}

	for (int i = 0; i < N_DETECTORS; i++) {
		for (int j = 0; j < N[i]; i++) {
			double E = energy[i][j];
			if (E > 0 /*&& E > 3000*/) 
				detectorSpectrum[i].Fill(E);
		}
	}
}

void Alpha2::writeEnergies( EnergyCalibration* calibration, AngleCalculator* angleCalc, double* energyArray, short* channelArray, UChar_t* stripArray, int nHits )
{
	for (int i = 0; i < nHits; i++) {
		int strip = stripArray[i];
		short channel = channelArray[i];
		double energy = calibration -> getEnergyFrontStrip(strip, channel);
		double angle = angleCalc -> getPolar(strip);

		std::pair<double, double> transformed = transformer -> transform(energy, angle);
		energyArray[i] = transformed.first;
	}
}


void Alpha2::writeSquareEnergies( EnergyCalibration* calibration, AngleCalculator* angleCalc, double* energyArray, 
								 short* frontChannelArray, UChar_t* frontStripArray, int nFrontHits, 
								 short* backChannelArray, UChar_t* backStripArray, int nBackHits,
								 bool flip)
{
	for (int i = 0; i < nFrontHits; i++) {
		int frontStrip = frontStripArray[i];
		short channel = frontChannelArray[i];
		double energy = calibration -> getEnergyFrontStrip(frontStrip, channel);
		int backStrip = 0;
		double minDiff = 1e6;

		for (int j = 0; j < nBackHits; j++) {
			int strip = backStripArray[i];
			short backChannel = backChannelArray[i];
			double backEnergy = calibration -> getEnergyBackStrip(strip, backChannel);

			double diff = abs(backEnergy-energy);
			if (diff > minDiff) continue;

			minDiff = diff;
			backStrip = strip;
			
		}
		if (minDiff > 100) {
			energyArray[i] = -1;
			continue;
		}
		if (flip) frontStrip = 17 - frontStrip;
		double angle = angleCalc -> getPolar(frontStrip, backStrip);

		std::pair<double, double> transformed = transformer -> transform(energy, angle);
		energyArray[i] = transformed.first;
	}
}


void Alpha2::findDoubleCoincidence()
{
	/*for (int i = 0; i < N_DETECTORS; i++) {
		if (N[i] > 1) return;
	}*/
	for (int i = 0; i < N_DETECTORS; i++) {
		for (int j = i + 1; j < N_DETECTORS; j++) {

			if (N[i] + N[j] != 2) continue;

			double e1 = energy[i][0];
			double e2 = energy[j][0];
				if ((e1 < 0 || e2 < 0) || 
					e1 < 1660 && e1 > 1400 ||
					e2 < 1660 && e2 > 1400) return;

			double diff = Q - e1 - e2;
			if (diff <= 0) return;

			alphaEnergies[0] = e1;
			alphaEnergies[1] = e2;
			alphaEnergies[2] = diff;

			fillPlots();
			return;
		}
	}
}

void Alpha2::determinePeakPositions() {
	double min = 4000;
	double max = 6500;
	int total = 0;
	double sum = 0;
	for (double x = min; x <= max; x++) {
		int i = spectrum.FindBin(x);

		double N = spectrum.GetBinContent(i);
		sum += x * N;
		total += N;
	}
	cout << "Alpha 1 peak is at: " << sum/total << " keV" << endl;
}







