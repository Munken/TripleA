#pragma once
#include "AngleCalculator.h"
#include <TRandom3.h>
class CircularAngleCalculator : public AngleCalculator
{
public:
	CircularAngleCalculator(const double distance);
	~CircularAngleCalculator(void) {};
	virtual double getPolar(int frontStrip, int backStrip = 0);
	virtual double getAzimuthal(int frontStrip, int backStrip);

	static double getMinRadius(int strip);

	static double getCircularArea(int strip);
	static double getInterSectionArea(int circularStrip);
	static double getRadialArea();
private:
	double dist;
	static const double circularDeadzone;
	static const double circularThickness;
	static const double anglePerSlice;
	static const double rMin;
	static const double rMax;
	double phiOffset;
	static TRandom3 rand3;
};

