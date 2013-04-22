#include "EnergyCalibration.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>

char* EnergyCalibration::CAL1_PATH = "../../Kalibrering/calib_det1_ns_apr2013M.dat";
char* EnergyCalibration::CAL2_PATH = "../../Kalibrering/calib_det2_ns_apr2013M.dat";
char* EnergyCalibration::CAL3_PATH = "../../Kalibrering/calib_s3_64_ns_dlmodM.dat";
char* EnergyCalibration::CAL4_PATH = "../../Kalibrering/calib_s3_1000_ns_dlmodM.dat";
char* EnergyCalibration::H1_RANGE = "../../Range/h1si";
char* EnergyCalibration::HE4_RANGE = "../../Range/he4si";

EnergyCalibration::EnergyCalibration( TString path2, int nRings /*= 24*/ ) : nRings(nRings)
{
	readCalibrationFile(path2);
}


double EnergyCalibration::getEnergyFrontStrip( int strip, short channel )
{
	return getEnergyStrip(strip, channel);
}

double EnergyCalibration::getEnergyBackStrip( int strip, short channel )
{
	return getEnergyStrip(strip+nRings, channel);
}


double EnergyCalibration::getEnergyStrip(int strip, int channel) {
	Calibration c = calibration[strip-1];
	return c.offset + channel*c.slope;
}

void EnergyCalibration::readCalibrationFile(TString path) {
	std::ifstream file(path);
	std::string   line;

	if (file.fail()) {
		cerr << "The file " << path << " is bad" << endl;
		exit(1);

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