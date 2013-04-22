#pragma once
#include "DeadLayerCalibration.h"
#include "DownStreamAngleCalculator.h"

class DownStreamDeadCalibration : public DeadLayerCalibration {
public:
	DownStreamDeadCalibration(char* calibrationPath, char* rangePath, bool front = true) : DeadLayerCalibration(calibrationPath, rangePath, new DownStreamAngleCalculator(), front ? 3 : 0.6) {};
	~DownStreamDeadCalibration(void) {};
};