#pragma once
#include "CircularAngleCalculator.h"
class UpstreamAngleCalculator : public CircularAngleCalculator
{
public:
	UpstreamAngleCalculator(void) : CircularAngleCalculator(-44.0) {};
	~UpstreamAngleCalculator(void) {};
};

