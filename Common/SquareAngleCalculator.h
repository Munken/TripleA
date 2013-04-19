#pragma once
#include "anglecalculator.h"
#include <TRandom3.h>
class SquareAngleCalculator :
	public AngleCalculator
{
public:
	SquareAngleCalculator(double distance, double zOffset);
	~SquareAngleCalculator(void) {};
	virtual double getPolar(int strip);

private:
	double getMidpoint(int strip);
	const double distance;
	double offset;
	const double zOffset;
	static const double STRIP_WIDTH;
	static const double INTER_STRIP_DIST;
	static const double WIDTH;
	static TRandom3 rand3;
};

