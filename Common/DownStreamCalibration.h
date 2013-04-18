#pragma once
#include "DeadLayerCalibration.h"
#include "DownStreamAngleCalculator.h"

class DownStreamDeadCalibration : public DeadLayerCalibration {
public:
	DownStreamDeadCalibration(char* calibrationPath, char* rangePath) : DeadLayerCalibration(calibrationPath, rangePath, new DownStreamAngleCalculator(), 3) {};
	~DownStreamDeadCalibration(void) {};
};