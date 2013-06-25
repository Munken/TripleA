#include "stdafx.h"
#include "RutherDistribution.h"
#include "Selector.h"
#include <TCanvas.h>
#include <iostream>
#include <AngleCalculator.h>
#include <SquareAngleCalculator.h>
#include "UpStreamAngleCalculator.h"
#include "DownStreamAngleCalculator.h"
#include "CircularAngleCalculator.h"
#include "UpstreamCalibration.h"
#include "DownStreamCalibration.h"
#include "EnergyCalibration.h"

using namespace std;

EnergyCalibration* RutherDistribution::energyCalibration[4] = {
	new EnergyCalibration(EnergyCalibration::CAL1_PATH, 16),
	new EnergyCalibration(EnergyCalibration::CAL2_PATH, 16),
	new UpStreamDeadCalibration(EnergyCalibration::CAL3_PATH, EnergyCalibration::H1_RANGE, false),
	new DownStreamDeadCalibration(EnergyCalibration::CAL4_PATH, EnergyCalibration::H1_RANGE, false)
};

AngleCalculator* RutherDistribution::angleCalculators[4] = {
	new SquareAngleCalculator(32, -2.52243, -7.27611e+00),
	new SquareAngleCalculator(-3.42838e1, 3.60734, -8.11409e+00),
	new UpstreamAngleCalculator(),
	new DownStreamAngleCalculator()
};

RutherDistribution::RutherDistribution( char* output) : output(output)
{
	for (int i = 0; i < N_DETECTOR; i++) {
		int nStrips = i < 2 ? 16 : 24;

		spectra[i] = TH1F(Form("%i",i+1), Form("%i",i+1), nStrips, 0.5, nStrips+0.5);
	}
}


void RutherDistribution::analyze(Selector* s) {
	for (int i = 0; i < N_DETECTOR; i++) {
		fillSpectrum(i, *s);
	}
}

void RutherDistribution::fillSpectrum( int j, Selector& s )
{
	const int n = *s.Nfe[j];

	for (int i = 0; i < n; i++) {
		int strip = s.Nsfe[j][i];
		int chan = s.Ef[j][i];
		double energy = energyCalibration[j] -> getEnergyFrontStrip(strip, chan);
		if (energy < 1700 || energy > 2100) continue;
		double w = (j > 1) ? 1/CircularAngleCalculator::getCircularArea(strip) : 1;
		spectra[j].Fill(strip);
	}
}

void RutherDistribution::terminate() {
	char* dir = "result";
	
	TCanvas dp("Up", "Up", 1200, 1200);

	for (int i = 0; i < N_DETECTOR; i++) {
		spectra[i].Draw();
		dp.SaveAs(Form("%s/%s-%i.png", dir, output, i));
	}

}