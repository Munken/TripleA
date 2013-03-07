#pragma once
#include "DeadLayerCalibration.h"
#include "UpStreamAngleCalculator.h"

class UpStreamCalibration : public DeadLayerCalibration {
public:
	UpStreamCalibration(char* calibrationPath, char* rangePath) : DeadLayerCalibration(calibrationPath, rangePath, new UpstreamAngleCalculator(), 4.2) {};
	~UpStreamCalibration(void) {};
};