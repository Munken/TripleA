#pragma once
#include "systemtransformation.h"
class LabToLab : public SystemTransformation {
public:
	LabToLab(void) {};
	~LabToLab(void) {};
	std::pair<double, double> transform(double kineticEnergy, double angle);
};

