#define _USE_MATH_DEFINES
#include "Angle.h"
#include <math.h>

const double AngleCalculator::circularDeadzone = 0.1;
const double AngleCalculator::circularThickness = 0.9;
const double AngleCalculator::anglePerSlice = 1/32*2*M_PI;
const double AngleCalculator::rMax = 35;
const double AngleCalculator::rMin = 11;


AngleCalculator::AngleCalculator(const double distance) {
	dist = distance;
}


AngleCalculator::~AngleCalculator(void)
{
}

double AngleCalculator::getAzimuthMin( int strip ){
	return atan2(getMinRadius(strip), dist);
}

double AngleCalculator::getAzimuthMax( int strip )
{
	return atan2(getMaxRadius(strip), dist);
}



double AngleCalculator::getMinRadius( int strip )
{
	return rMin + (strip-1) * (circularThickness + circularDeadzone);
}

double AngleCalculator::getMaxRadius( int strip )
{
	return getMinRadius(strip) + circularThickness;
}

double AngleCalculator::getCircularArea( int strip )
{
	return 2 * M_PI * getMinRadius(strip) * circularThickness;
}

double AngleCalculator::getInterSectionArea(int circularStrip) {
	return getMinRadius(circularStrip) * circularThickness * anglePerSlice;
}

double AngleCalculator::getRadialArea() {
	return pow(rMax, 2) * anglePerSlice / 2;
} 
