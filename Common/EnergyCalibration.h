#pragma once
#include <vector>
#include <TString.h>


using namespace std;

struct Calibration
{
	Calibration(double off, double sl) {
		offset = off;
		slope = sl;
	}
	double offset;
	double slope;
};

class EnergyCalibration
{
public:
	EnergyCalibration(TString path, int nRings = 24);
	~EnergyCalibration(void) {};
	virtual double getEnergyBackStrip(int strip, short channel);
	virtual double getEnergyFrontStrip(int strip, short channel);
	static char* CAL1_PATH;
	static char* CAL2_PATH;
	static char* CAL3_PATH;
	static char* CAL4_PATH;
	static char* H1_RANGE;
	static char* HE4_RANGE;


private:
	vector<Calibration> calibration;
	const int nRings;
	double getEnergyStrip(int strip, int channel);
	void readCalibrationFile(TString path);
};



