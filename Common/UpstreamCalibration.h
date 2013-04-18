#pragma once
#include "DeadLayerCalibration.h"
#include "UpStreamAngleCalculator.h"

class UpStreamDeadCalibration : public DeadLayerCalibration {
public:
	UpStreamDeadCalibration(char* calibrationPath, char* rangePath) : DeadLayerCalibration(calibrationPath, rangePath, new UpstreamAngleCalculator(), 4.2) {};
	~UpStreamDeadCalibration(void) {};
};