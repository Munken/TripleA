#pragma once
#include "CircularAngleCalculator.h"
class UpstreamAngleCalculator : public CircularAngleCalculator
{
public:
	UpstreamAngleCalculator(void) : CircularAngleCalculator(-44.5) {};
	~UpstreamAngleCalculator(void) {};
};

