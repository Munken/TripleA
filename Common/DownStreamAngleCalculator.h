#pragma once
#include "CircularAngleCalculator.h"
class DownStreamAngleCalculator : public CircularAngleCalculator
{
public:
	DownStreamAngleCalculator(void) : CircularAngleCalculator(41.3) {};
	~DownStreamAngleCalculator(void) {};
};

