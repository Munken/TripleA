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
	EnergyCalibration(TString path);
	~EnergyCalibration(void);
	double getEnergyRadialStrip(int strip, short channel);
	double getEnergyCircularStrip(int strip, short channel);

private:
	vector<Calibration> calibration;
	static const int nRings = 24;
	double getEnergyStrip(int strip, int channel);
};



