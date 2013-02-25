#include "EnergyCalibration.h"
#include <fstream>
#include <iostream>
#include <sstream>


EnergyCalibration::EnergyCalibration( TString path )
{
	std::ifstream file(path);
	std::string   line;

	if(file.fail()){
		cerr << "Something wrong with the file";
		return;
	}
	while(std::getline(file, line))
	{
		std::stringstream   linestream(line);
		double                 slope;
		double                 offset;

		linestream >> slope;
		linestream >> offset;

		Calibration fit(offset, slope);
		calibration.push_back(fit);
	}

}


EnergyCalibration::~EnergyCalibration(void){
}
double EnergyCalibration::getEnergyCircularStrip( int strip, short channel )
{
	return getEnergyStrip(strip, channel);
}

double EnergyCalibration::getEnergyRadialStrip( int strip, short channel )
{
	return getEnergyStrip(strip+nRings, channel);
}


double EnergyCalibration::getEnergyStrip(int strip, int channel) {
	Calibration c = calibration[strip-1];
	return c.offset + channel*c.slope;
}

