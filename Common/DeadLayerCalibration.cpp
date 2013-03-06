#include "DeadLayerCalibration.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "UpStreamAngleCalculator.h"

using namespace std;

float DeadLayerCalibration::MIN_ENERGY = 450;
float DeadLayerCalibration::MAX_ENERGY = 20000;

DeadLayerCalibration::DeadLayerCalibration( TString path, char* rangePath, AngleCalculator* angle ) : EnergyCalibration(path), angleCalculator(angle)
{
	readRangeFile(rangePath);
	deadLayerThickness = 3;

	UpstreamAngleCalculator* v = dynamic_cast<UpstreamAngleCalculator*>(angle);
	if(v != 0) {
		// old was safely casted to NewType
		deadLayerThickness = 4.2;
	}
}


DeadLayerCalibration::~DeadLayerCalibration(void)
{
	delete angleCalculator;
}

double sumFactor;
int count2 = 0;
double DeadLayerCalibration::getEnergyCircularStrip( int strip, short channel ) {
	count2++;
	double E0 = EnergyCalibration::getEnergyCircularStrip(strip, channel);
	double range0 = getRange(E0);
	double extraRange = deadLayerThickness / abs(cos(angleCalculator -> getAzimuthMin(strip)));
	double Er = getEnergy(range0 + extraRange);
	sumFactor += Er/E0;
	//cout << "E0: " << E0 << " Er: " << Er << " Er/E0: " << Er / E0 <<  " Avg(Er/E0): " << sumFactor/count2 << endl;
	return Er;
}

double DeadLayerCalibration::getEnergyRadialStrip( int strip, short channel )
{
	return EnergyCalibration::getEnergyRadialStrip(strip, channel);
}

float DeadLayerCalibration::calculateEnergyInKeV( float number, string unit )
{
	if (unit == "keV") return number;
	else if (unit == "MeV") return 1000 * number;
	throw "Unknown energy unit";
}

float DeadLayerCalibration::calculateRangeInUm( float number, string unit )
{
	if (unit == "um") return number;
	else if (unit == "A") return number / 10000;
	throw "Unknown range unit";
}

double DeadLayerCalibration::getRange( double energy )
{
	return performLinearInterpolation(energies, ranges, energy);
}


double DeadLayerCalibration::getEnergy( double range )
{
	return performLinearInterpolation(ranges, energies, range);
}


float DeadLayerCalibration::performLinearInterpolation( vector<float> x, vector<float> y, float x0 )
{
	vector<float>::iterator it = lower_bound(x.begin(), x.end(), x0);
	int maxIndex = it - x.begin();
	int minIndex = maxIndex - 1;

	float maxX = x[maxIndex];
	float minX = x[minIndex];

	float maxY = y[maxIndex];
	float minY = y[minIndex];
	return minY + (maxY - minY) * (x0 - minX) / (maxX - minX);
}

void DeadLayerCalibration::readRangeFile( char* rangePath )
{
	ifstream file(rangePath);
	string   line;

	if(file.fail()) {
		cerr << "Dead calib" << endl;
		return;
	}
	// Disgard header
	while(getline(file, line)) {
		if (line[0] == '-') break;
	}

	int count = 0;
	while(getline(file, line)) {
		if (line[0] == '-') break;

		std::stringstream   linestream(line);

		float energy;
		string	energyUnit;
		float electricLoss;
		float nuclearLoss;
		float range;
		string rangeUnit;

		linestream >> energy;
		linestream >> energyUnit;

		energy = calculateEnergyInKeV(energy, energyUnit);
		if (energy < MIN_ENERGY) continue;
		else if (energy > MAX_ENERGY) break; 

		linestream >> electricLoss;
		linestream >> nuclearLoss;
		linestream >> range;
		linestream >> rangeUnit;

		range = calculateRangeInUm(range, rangeUnit);

		energies.push_back(energy);
		ranges.push_back(range);
	}
}


