#pragma once
#include "energycalibration.h"
#include "CircularAngleCalculator.h"
class DeadLayerCalibration :
	public EnergyCalibration
{
public:
	DeadLayerCalibration(TString path, char* rangePath, CircularAngleCalculator* angle, double deadLayerThickness);
	virtual ~DeadLayerCalibration(void);
	virtual double getEnergyBackStrip(int strip, short channel);
	virtual double getEnergyFrontStrip(int strip, short channel);


	double getRange(double energy);
	double getEnergy(double range);
	

private:
	float calculateEnergyInKeV(float number, string unit);
	float calculateRangeInUm(float number, string unit);


	float performLinearInterpolation(vector<float> x, vector<float> y, float x0);
	void readRangeFile( char* rangePath );

	vector<float> energies;
	vector<float> ranges;
	CircularAngleCalculator* angleCalculator;
	static float MIN_ENERGY;
	static float MAX_ENERGY;
	double deadLayerThickness;


};

