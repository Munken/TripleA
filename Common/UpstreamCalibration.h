#pragma once
#include "DeadLayerCalibration.h"
#include "UpStreamAngleCalculator.h"

class UpStreamDeadCalibration : public DeadLayerCalibration {
public:
	UpStreamDeadCalibration(char* calibrationPath, char* rangePath, bool front = true) : DeadLayerCalibration(calibrationPath, rangePath, new UpstreamAngleCalculator(), front ? 4.2 : 0.6) {};
	~UpStreamDeadCalibration(void) {};
};