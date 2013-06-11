#pragma once
#include "CircularAngleCalculator.h"
class DownStreamAngleCalculator : public CircularAngleCalculator
{
public:
	DownStreamAngleCalculator(void) : CircularAngleCalculator(40) {};
	~DownStreamAngleCalculator(void) {};
};

