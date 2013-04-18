#pragma once
#include "Analyzer.h"
#include "TH2.h"
#include "SystemTransformation.h"
#include "EnergyCalibration.h"
#include "AngleCalculator.h"
class Alpha2 : public Analyzer
{
public:
	Alpha2(char* output, char* title, double maxDiff = 100) ;
	virtual ~Alpha2(void) {
		for (int i = 0; i < 4; i++) {
			delete [] energy[i];
		}
		delete [] energy;

	};
	void analyze(Selector* s);
	void terminate();

	
private:
	void determineEnergies(Selector* s);
	void writeEnergies(EnergyCalibration* calibration, AngleCalculator* angleCalc, double* energyArray, short* channelArray, UChar_t* stripArray, int nHits);

	void findTripleAlphas();
	void findTwoDetectorCoincidence(int N1, double* E1, int N2, double* E2);
	void findTripleDetectorCoincidence(int N1, double* E1, int N2, double* E2, int N3, double* E3);
	void findDoubleCoincidence();
	void fillPlots();

	char* output;
	double Q;
	double maxDiff;
	double alphaEnergies[3];
	static EnergyCalibration* upStreamCalibration;
	static EnergyCalibration* downStreamCalibration;
	static EnergyCalibration* square1Calibration;
	static EnergyCalibration* square2Calibration;

	static AngleCalculator* angleCalculators[4];

	static SystemTransformation* transformer;

	static const int N_DETECTORS = 4;

	double** energy;
	int N[N_DETECTORS];

	TH2F dalitz;
	TH1F spectrum;
	double upperCut;
	double lowerCut;

};

