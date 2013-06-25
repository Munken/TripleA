#pragma once
#include "Analyzer.h"
#include <EnergyCalibration.h>
#include "TH2.h"
class SpectrumPlotter : public Analyzer
{
public:
	SpectrumPlotter(char* output) ;
	virtual ~SpectrumPlotter(void) { };
	void analyze(Selector* s);
	void terminate();


private:
	void fillSpectra(Selector& s, int i);

	TH1F** spectrums;
	int N[4];
	char* output;

	static const int N_DETECTORS = 4;
	static EnergyCalibration* energyCalibration[4];
};

