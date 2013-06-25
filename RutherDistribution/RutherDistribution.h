#pragma once
#include "Analyzer.h"
#include <AngleCalculator.h>
#include <EnergyCalibration.h>
#include "TH2.h"
class RutherDistribution : public Analyzer
{
public:
	RutherDistribution(char* output) ;
	virtual ~RutherDistribution(void) { };
	void analyze(Selector* s);
	void terminate();

	
private:
	void fillSpectrum(int i, Selector& s);

	static const int N_DETECTOR = 4;
	static AngleCalculator* angleCalculators[4];
	static EnergyCalibration* energyCalibration[4];

	char* output;
	TH1F spectra[N_DETECTOR];

};

