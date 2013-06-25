#include "stdafx.h"
#include "SpetrumPlotter.h"
#include "Selector.h"
#include <TCanvas.h>
#include "UpstreamCalibration.h"
#include "DownStreamCalibration.h"
#include <iostream>

using namespace std;

EnergyCalibration* SpectrumPlotter::energyCalibration[4] = {
	new EnergyCalibration(EnergyCalibration::CAL1_PATH, 16),
	new EnergyCalibration(EnergyCalibration::CAL2_PATH, 16),
	new UpStreamDeadCalibration(EnergyCalibration::CAL3_PATH, EnergyCalibration::HE4_RANGE, true),
	new DownStreamDeadCalibration(EnergyCalibration::CAL4_PATH, EnergyCalibration::HE4_RANGE, true)
};


SpectrumPlotter::SpectrumPlotter(char* output) : output(output)
{
	spectrums = new TH1F*[4];
	spectrums[0] = new TH1F[16];
	spectrums[1] = new TH1F[16];
	spectrums[2] = new TH1F[24];
	spectrums[3] = new TH1F[24];

	for (int i = 0; i < N_DETECTORS; i++) {
		int max = i < 2 ? 16 : 24;
		for (int j = 0; j < max; j++) {
			spectrums[i][j] = TH1F(Form("%i %i", i, j), ";Energi [keV];Tællinger", 1000, 4400, 6600);
			spectrums[i][j].GetYaxis() -> SetTitleOffset(1.7);
		}
	}
}


void SpectrumPlotter::analyze(Selector* p) {
	Selector& s = *p;

	for (int i = 0; i < N_DETECTORS; i++) {
		N[i] = *(s.Nfe[i]);
		fillSpectra(s, i);
	}

}



void SpectrumPlotter::terminate() {
	char* dir = "result";
	
	TCanvas dp("Up", "Up", 1200, 1200);
	dp.SetLeftMargin(0.15);
	dp.SetTopMargin(0.05);
	dp.SetRightMargin(0.05);

	//dp.SetLogy();

	for (int i = 0; i < N_DETECTORS; i++) {
		int max = i < 2 ? 16 : 24;
		for (int j = 0; j < max; j++) {
			spectrums[i][j].Draw();
			dp.SaveAs(Form("%s/%i-%i.pdf", dir, i, j));
		}
	}
}

void SpectrumPlotter::fillSpectra(Selector& s, int i)
{
	UChar_t* stripArray = s.Nsfe[i];
	short* channelArray = s.Ef[i];
	EnergyCalibration* calibration = energyCalibration[i];

	for (int j = 0; j < N[i]; j++) {
		int strip = stripArray[j];
		short channel = channelArray[j];
		double energy = calibration -> getEnergyFrontStrip(strip, channel);
		
		spectrums[i][strip-1].Fill(energy);
	}
}


