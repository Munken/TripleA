#define _USE_MATH_DEFINES
#include "CircularAngleCalculator.h"
#include <math.h>

const double CircularAngleCalculator::circularDeadzone = 0.1;
const double CircularAngleCalculator::circularThickness = 0.9;
const double CircularAngleCalculator::anglePerSlice = 1/32*2*M_PI;
const double CircularAngleCalculator::rMax = 35;
const double CircularAngleCalculator::rMin = 11;
TRandom3 CircularAngleCalculator::rand3;


CircularAngleCalculator::CircularAngleCalculator(const double distance) {
	dist = distance;
}


double CircularAngleCalculator::getPolar( int frontStrip, int backStrip ){
	double r = getMinRadius(frontStrip) + rand3.Uniform() * circularThickness;
	return atan2(r, dist);
}


double CircularAngleCalculator::getMinRadius( int strip )
{
	return rMin + (strip-1) * (circularThickness + circularDeadzone);
}

double CircularAngleCalculator::getCircularArea( int strip )
{
	return 2 * M_PI * getMinRadius(strip) * circularThickness;
}

double CircularAngleCalculator::getInterSectionArea(int circularStrip) {
	return getMinRadius(circularStrip) * circularThickness * anglePerSlice;
}

double CircularAngleCalculator::getRadialArea() {
	return pow(rMax, 2) * anglePerSlice / 2;
} 
