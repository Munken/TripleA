#pragma once
#include "CircularAngleCalculator.h"
class UpstreamAngleCalculator : public CircularAngleCalculator
{
public:
	UpstreamAngleCalculator(void) : CircularAngleCalculator(-45) {};
	~UpstreamAngleCalculator(void) {};
};

