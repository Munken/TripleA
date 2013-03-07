#pragma once
#include "Analyzer.h"
#include "TH2.h"
#include "EnergyCalibration.h"

class AlphaDetector : public Analyzer
{
public:
	AlphaDetector(float beamEnergy, char* output, char* title, char* plotOptions = "", float cut = 0.1) ;
	virtual ~AlphaDetector(void) { };
	void analyze(Selector* s);


	void terminate();

	
private:

	// Methods
	void calculateEnergies( int nDown, Selector* s, int nUp );

	// Vars
	TH1F hist;
	char* output;
	char* plotOptions;
	float cut;
	double Q;
	static EnergyCalibration* upStreamCalibration;
	static EnergyCalibration* downStreamCalibration;
	double upStreamEnergy[24];
	double downStreamEnergy[24];


};

