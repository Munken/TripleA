#pragma once
#include "Analyzer.h"
#include "TH2.h"
#include "EnergyCalibration.h"
#include "SystemTransformation.h"
#include "UpStreamAngleCalculator.h"
#include "DownStreamAngleCalculator.h"

class AlphaDetector : public Analyzer
{
public:
	AlphaDetector(float beamEnergy, char* output, char* title, float cut = 0.5, char* plotOptions = "") ;
	virtual ~AlphaDetector(void) { };
	void analyze(Selector* s);

	void findTripleAlphas( int shortLength, int largeLength, double* shorter, double* larger );


	void terminate();

	
private:

	// Methods
	void calculateEnergies( int nDown, Selector* s, int nUp );

	// Vars
	TH1F spectrum;
	TH2F dalitz;
	char* output;
	char* plotOptions;
	float cut;
	double Q;
	static EnergyCalibration* upStreamCalibration;
	static EnergyCalibration* downStreamCalibration;
	static const double SQRT_3;
	double upStreamEnergy[24];
	double downStreamEnergy[24];
	double alphaEnergies[3];
	int nAlpha;

	UpstreamAngleCalculator upStreamAngle;
	DownStreamAngleCalculator downStreamAngle;
	SystemTransformation* transformer;
};

