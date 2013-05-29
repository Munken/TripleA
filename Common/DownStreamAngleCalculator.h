#pragma once
#include "CircularAngleCalculator.h"
class DownStreamAngleCalculator : public CircularAngleCalculator
{
public:
	DownStreamAngleCalculator(void) : CircularAngleCalculator(42) {};
	~DownStreamAngleCalculator(void) {};
};

