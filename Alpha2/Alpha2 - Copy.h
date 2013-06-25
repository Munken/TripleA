#pragma once
#include "Analyzer.h"
#include "TH2.h"
#include "TH3.h"
#include <TVector3.h>
#include "SystemTransformation.h"
#include "EnergyCalibration.h"
#include "AngleCalculator.h"
class Alpha2 : public Analyzer
{
public:
	Alpha2(double beamEnergy, char* output, char* title, double tripleLow, double tripleHigh, double doubleLow, double doubleHigh, double maxDiff = 100) ;
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
	void writeSquareEnergies(EnergyCalibration* calibration, AngleCalculator* angleCalc, double* energyArray, TVector3* momentumArray,
		short* frontChannelArray, UChar_t* frontStripArray, int nFrontHits, 
		short* backChannelArray, UChar_t* backStripArray, int nBackHits);

	void findTripleAlphas();
	void findTwoDetectorCoincidence(int N1, double* E1, TVector3* p1, int N2, double* E2, TVector3* p2);
	void findTripleDetectorCoincidence(int N1, double* E1, TVector3* p1, int N2, double* E2, TVector3* p2, int N3, double* E3, TVector3* p3);
	void findDoubleCoincidence();
	void fillPlots(TH2F& dalitz, TH1F& spetrum);
	void determinePeakPositions();
	double calculateAngleSum(TVector3& p1, TVector3& p2, TVector3& p3);

	char* output;
	double Q;
	double maxDiff;
	double alphaEnergies[3];

	static EnergyCalibration* energyCalibration[4];
	static AngleCalculator* angleCalculators[4];

	SystemTransformation* transformer;

	static const int N_DETECTORS = 4;

	double** energy;
	TVector3** momentum;
	int N[N_DETECTORS];

	TH2F dalitzT, dalitzD;
	TH1F spectrumT, spectrumD;
	TH1F detectorSpectrum[4];
	TH1F specQ;
	TH1F specA;
	TH3F specP;
	TH1F specPMag;
	double upperCutTripple, lowerCutTripple;
	double upperCutDouble, lowerCutDouble;

};

