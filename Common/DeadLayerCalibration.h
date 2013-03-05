#pragma once
#include "energycalibration.h"
#include "Angle.h"
class DeadLayerCalibration :
	public EnergyCalibration
{
public:
	DeadLayerCalibration(TString path, char* rangePath, AngleCalculator* angle);
	~DeadLayerCalibration(void);
	virtual double getEnergyRadialStrip(int strip, short channel);
	virtual double getEnergyCircularStrip(int strip, short channel);


	double getRange(double energy);
	double getEnergy(double range);
	

private:
	float calculateEnergyInKeV(float number, string unit);
	float calculateRangeInUm(float number, string unit);


	float performLinearInterpolation(vector<float> x, vector<float> y, float x0);
	void readRangeFile( char* rangePath );

	vector<float> energies;
	vector<float> ranges;
	AngleCalculator* angleCalculator;
	static float MIN_ENERGY;
	static float MAX_ENERGY;
	double deadLayerThickness;


};

