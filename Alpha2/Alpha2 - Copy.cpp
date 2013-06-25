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
#include <TString.h>
#include "FlippedSquareAngleCalculator.h"

using namespace std;
using namespace constants;

const double SQRT_3 = sqrt(3);

// Her skal skiftes til 6 µm dødlags kalibrering for de runde. 
EnergyCalibration* Alpha2::energyCalibration[4] = {
	new EnergyCalibration(EnergyCalibration::CAL1_PATH, 16),
	new EnergyCalibration(EnergyCalibration::CAL2_PATH, 16),
	new UpStreamDeadCalibration(EnergyCalibration::CAL3_PATH, EnergyCalibration::HE4_RANGE, false),
	new DownStreamDeadCalibration(EnergyCalibration::CAL4_PATH, EnergyCalibration::HE4_RANGE, false)
};

AngleCalculator* Alpha2::angleCalculators[4] = {
	new SquareAngleCalculator(33, -2.52243, -7.27611e+00),
	new FlippedSquareAngleCalculator(-37, 3.60734, -8.11409e+00),
	new UpstreamAngleCalculator(),
	new DownStreamAngleCalculator()
};

//SystemTransformation* Alpha2::transformer = new LabToCM(2650, ALPHA_MASS);




Alpha2::Alpha2( double beamEnergy, char* output, char* title, double tripleLow, double tripleHigh, double doubleLow, double doubleHigh, double maxDiff) : output(output), maxDiff(maxDiff), 
	dalitzT("Triple", "", 120, -0.4, 0.4, 120, -0.4, 0.4),
	dalitzD("Double", "", 120, -0.4, 0.4, 120, -0.4, 0.4),
	spectrumT("SpecT", "T;Energi [keV];Tællinger", 3096, 0, 7500),
	spectrumD("SpecD", "D;Energi [keV];Tællinger", 3096, 0, 7500),
	specP("SpecP", "", 200, -100, 100, 200, -100, 100, 200, -100, 100),
	specA("SpecA", "", 100, 0.6*6.28, 1.2*6.28),
	specPMag("PMag", "", 100, 0, 100),
	//upperCut(1560), lowerCut(1460)
	//upperCutDouble(1660), lowerCutDouble(1400),
	upperCutDouble(doubleHigh), lowerCutDouble(doubleLow),
	upperCutTripple(tripleHigh), lowerCutTripple(tripleLow)
{
	transformer = new LabToCM(beamEnergy, ALPHA_MASS);
	energy = new double*[N_DETECTORS];
	momentum = new TVector3*[N_DETECTORS];

	for (int i = 0; i < N_DETECTORS; i++) {
		int n = (i < 2) ? 16 : 24;
		energy[i] = new double[n];
		momentum[i] = new TVector3[n];
	}

	Q = (11./12. * beamEnergy + BORON_11_MASS + PROTON_MASS) - 3*ALPHA_MASS;

	spectrumT.GetYaxis()->SetTitleOffset(1.7);
	specQ = TH1F("QSpec", "", 100, 0.95*Q, 1.05*Q);
	for (int i = 0; i < N_DETECTORS; i++) {
		detectorSpectrum[i] = TH1F(Form("%i", i), Form("%i", i), 3096, 400, 8000);
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
		findDoubleCoincidence();
	} else {
		findTripleAlphas();
	}
	

}


void Alpha2::findTripleAlphas()
{
	const int start = 2;
	const int end = N_DETECTORS;
	for (int i = start; i < end; i++) {
		for (int j = i + 1; j < end; j++) {

			// Two alphas in one detector and one in another. 
			if (N[i] + N[j] >= 3) {
				findTwoDetectorCoincidence(N[i], energy[i], momentum[i], N[j], energy[j], momentum[j]);
				findTwoDetectorCoincidence(N[j], energy[j], momentum[j], N[i], energy[i], momentum[i]);
			}

			// One alpha in 3 detectors
			for (int k = j + 1; k < end; k++) {
				if (N[i] + N[j] + N[k] < 3) continue;
				findTripleDetectorCoincidence(N[i], energy[i], momentum[i], N[j], energy[j], momentum[j], N[k], energy[k], momentum[k]);
			}
		}
	}
}


void Alpha2::findTwoDetectorCoincidence( int N1, double* E1, TVector3* p1, int N2, double* E2, TVector3* p2 ) {
	for (int i = 0; i < N1; i++) {
		if (E1[i] < 0 || (E1[i] > lowerCutTripple && E1[i] < upperCutTripple)) continue;
		for (int j = i + 1; j < N1; j++) {
			if (E1[j] < 0 || (E1[j] > lowerCutTripple && E1[j] < upperCutTripple)) continue;
			for (int k = 0; k < N2; k++) {
				if (E2[k] < 0 || (E2[k] > lowerCutTripple && E2[k] < upperCutTripple)) continue;

				double sum = E1[i] + E1[j] + E2[k];
				double diff = fabs(sum - Q);

				
				if (diff > maxDiff) continue;


				alphaEnergies[0] = E1[i];
				alphaEnergies[1] = E1[j];
				alphaEnergies[2] = E2[k];

				fillPlots(dalitzT, spectrumT);

				//TVector3 p = p1[i] + p1[j] + p2[k];
				//specP.Fill(p.x(), p.y(), p.z());
				//specA.Fill(calculateAngleSum(p1[i], p1[j], p2[k]));
				//specPMag.Fill(p.Mag());
			}
		}
	}
}


void Alpha2::findTripleDetectorCoincidence( int N1, double* E1, TVector3* p1, int N2, double* E2, TVector3* p2, int N3, double* E3, TVector3* p3 )
{
	for (int i = 0; i < N1; i++) {
		if (E1[i] < 0 || (E1[i] > lowerCutTripple && E1[i] < upperCutTripple)) continue;

		for (int j = 0; j < N2; j++) {
			if (E2[j] < 0 || (E2[j] > lowerCutTripple && E2[j] < upperCutTripple)) continue;

			for (int k = 0; k < N3; k++) {
				if (E3[j] < 0 || (E3[k] > lowerCutTripple && E3[k] < upperCutTripple)) continue;

				double sum = E1[i] + E2[j] + E3[k];
				double diff = fabs(sum - Q);

				if (diff > maxDiff) continue;
				

				alphaEnergies[0] = E1[i];
				alphaEnergies[1] = E2[j];
				alphaEnergies[2] = E3[k];

				fillPlots(dalitzT, spectrumT);
				
				//TVector3 p = p1[i] + p2[j] + p3[k];
				//
				//double angleSum = calculateAngleSum(p1[i], p2[j], p3[k]);
				////if (angleSum < 0.98*6.28) continue;
				//specA.Fill(angleSum);
				//specP.Fill(p.x(), p.y(), p.z());
				//specPMag.Fill(p.Mag());
			}
		}
	}
}

void Alpha2::fillPlots(TH2F& dalitz, TH1F& spectrum) {
	random_shuffle(alphaEnergies, alphaEnergies+3);

	double x = (alphaEnergies[2]/Q + 2. * alphaEnergies[1]/Q - 1.) / SQRT_3;
	double y = alphaEnergies[2] / Q - 1./3.;

	if (pow(x,2) + pow(y,2) > 1/9.) {
		return;
	}
	dalitz.Fill(x, y);

	double sum = 0;

	for (int i = 0; i < 3; i++) {
		spectrum.Fill(alphaEnergies[i]);
		sum += alphaEnergies[i];
	}
	
	
	specQ.Fill(sum);
}



void Alpha2::terminate() {
	char* dir = "result";
	double eCM = BORON_11_MASS + PROTON_MASS - BERYLLIUM_8_MASS - ALPHA_MASS + 11./12 * 2000;
	double Q1 = 2./3*eCM;
	double Q2 = 2./3*(eCM - 3000);
	double y = Q1 / Q - 1./3.;
	double y2 = Q2 / Q - 1./3.;

	// Draw dalitz plot
	TCanvas dp("Up", "Up", 1200, 1200);
	//dp.GetPad(0)->SetRightMargin(0.5);
	dp.SetRightMargin(0.13);
	dp.SetLeftMargin(0.15);
	//dp.SetLogz();
	//TLine l(-1./3, y, 1./3, y);
	//l.SetLineColor(kRed);
	//l.DrawClone("Same");

	//l = TLine(-1./3, y2, 1./3, y2);
	//l.SetLineColor(kRed);
	//l.DrawClone("SAME");
	TArc arc(0,0, 1./3);
	arc.SetLineColor(kRed);
	arc.SetFillStyle(0);

	
	dalitzT.Draw("COLZ");	
	arc.Draw("SAME");


	dp.SaveAs(TString::Format("%s/%s-DALITZ-T.png", dir, output));

	dalitzD.Draw("COLZ");
	arc.Draw("SAME");

	dp.SaveAs(TString::Format("%s/%s-DALITZ-D.png", dir, output));

	// Draw spectrum

	TCanvas spet("Up", "Up", 1200, 1200);
	spet.SetLeftMargin(0.15);
	spectrumT.Draw("");
	spet.SaveAs(TString::Format("%s/%s-spec-T.png", dir, output));
	spectrumD.Draw("");
	spet.SaveAs(TString::Format("%s/%s-spec-D.png", dir, output));
	determinePeakPositions();

	// Draw detector spectrum
	
	spet.SetLogy();
	for (int i = 0; i < N_DETECTORS; i++) {
		detectorSpectrum[i].Draw();
		spet.SaveAs(TString::Format("%s/%s-spec%i.png", dir, output,i));
	}

	spet.SetLogy(kFALSE);
	specQ.Draw();
	spet.SaveAs(TString::Format("%s/%s-specQ.png", dir, output));

	specP.ProjectionX()->Draw();
	spet.SaveAs(TString::Format("%s/%s-specPx.png", dir, output));

	specP.ProjectionY()->Draw();
	spet.SaveAs(TString::Format("%s/%s-specPy.png", dir, output));

	specP.ProjectionZ()->Draw();
	spet.SaveAs(TString::Format("%s/%s-specPz.png", dir, output));

	specA.Draw();
	spet.SaveAs(TString::Format("%s/%s-specA.png", dir, output));

	specPMag.Draw();
	spet.SaveAs(TString::Format("%s/%s-specP.png", dir, output));
}

void Alpha2::determineEnergies(Selector* s)
{
	for (int i = 0; i < 2; i++) {
		writeSquareEnergies(energyCalibration[i], angleCalculators[i], energy[i], momentum[i], 
								s -> Ef[i], s -> Nsfe[i], N[i], 
								s -> Eb[i], s -> Nsbe[i], s -> Nbe[i][0]);
	}

	for (int i = 2; i < N_DETECTORS; i++) {
		writeEnergies(energyCalibration[i], angleCalculators[i], energy[i], s -> Ef[i], s->Nsfe[i], N[i]);
	}

	for (int i = 0; i < N_DETECTORS; i++) {
		for (int j = 0; j < N[i]; j++) {
			double E = energy[i][j];
			if (E > 0)
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


void Alpha2::writeSquareEnergies( EnergyCalibration* calibration, AngleCalculator* angleCalc, double* energyArray, TVector3* momentumArray,
								 short* frontChannelArray, UChar_t* frontStripArray, int nFrontHits, 
								 short* backChannelArray, UChar_t* backStripArray, int nBackHits)
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

			double diff = fabs(backEnergy-energy);
			if (diff > minDiff) continue;

			minDiff = diff;
			backStrip = strip;
			
		}
		if (minDiff > 100) {
			energyArray[i] = -1;
			continue;
		}
		double polar = angleCalc -> getPolar(frontStrip, backStrip);
		double azimuth = angleCalc -> getAzimuthal(frontStrip, backStrip);

		std::pair<double, double> transformed = transformer -> transform(energy, polar);
		energy = transformed.first;
		energyArray[i] = energy;
		polar = transformed.second;

		/*TVector3& p = momentumArray[i];
		double sqrtE = energy;
		p.SetX(sqrtE * sin(azimuth)*sin(polar));
		p.SetY(sqrtE * cos(azimuth)*sin(polar));
		p.SetZ(sqrtE * cos(polar));*/

		//cout << p.x() << "  " << momentumArray[i].x() << endl;

		//momentumArray[i].SetMagThetaPhi(sqrt(energy), polar, azimuth);
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
					e1 < upperCutDouble && e1 > lowerCutDouble ||
					e2 < upperCutDouble && e2 > lowerCutDouble) return;

			double diff = Q - e1 - e2;
			if (diff <= 0) return;

			alphaEnergies[0] = e1;
			alphaEnergies[1] = e2;
			alphaEnergies[2] = diff;

			fillPlots(dalitzD, spectrumD);
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
		int i = spectrumT.FindBin(x);

		double N = spectrumT.GetBinContent(i);
		sum += x * N;
		total += N;
	}
	cout << "Alpha 1 peak is at: " << sum/total << " keV" << endl;
}

double Alpha2::calculateAngleSum( TVector3& p1, TVector3& p2, TVector3& p3 )
{
	return p1.Angle(p2) + p2.Angle(p3) + p3.Angle(p1);
}







