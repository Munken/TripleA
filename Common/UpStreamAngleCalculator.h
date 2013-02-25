#pragma once
#include "angle.h"
class UpstreamAngleCalculator : public AngleCalculator
{
public:
	UpstreamAngleCalculator(void) : AngleCalculator(-44.0) {};
	~UpstreamAngleCalculator(void) {};
};

