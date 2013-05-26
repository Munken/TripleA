#pragma once
#include "anglecalculator.h"
#include <TRandom3.h>
class SquareAngleCalculator :
	public AngleCalculator
{
public:
	SquareAngleCalculator(double distance, double zOffset);
	SquareAngleCalculator(double distance, double zOffset, double yOffset);
	~SquareAngleCalculator(void) {};
	virtual double getPolar(int strip, int backStrip = 0);
	virtual double getAzimuthal(int frontStrip, int backStrip);

private:
	double getMidpointZ(int frontStrip);
	double getMidpointY(int backStrip);
	const double xOffset;
	double offset;
	const double zOffset;
	const double yOffset;

	static const double STRIP_WIDTH;
	static const double INTER_STRIP_DIST;
	static const double WIDTH;
	static TRandom3 rand3;
};

