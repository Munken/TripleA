#pragma once
#include "DeadLayerCalibration.h"
#include "DownStreamAngleCalculator.h"

class DownStreamCalibration : public DeadLayerCalibration {
public:
	DownStreamCalibration(char* calibrationPath, char* rangePath) : DeadLayerCalibration(calibrationPath, rangePath, new DownStreamAngleCalculator(), 3) {};
	~DownStreamCalibration(void) {};
};