#define _USE_MATH_DEFINES

#include "SquareAngleCalculator.h"
#include <math.h>

const double SquareAngleCalculator::INTER_STRIP_DIST = 0.1;
const double SquareAngleCalculator::WIDTH = 49.5;
const double SquareAngleCalculator::STRIP_WIDTH = 3;
TRandom3 SquareAngleCalculator::rand3;


SquareAngleCalculator::SquareAngleCalculator(double distance) : distance(distance)
{
	offset = (distance < 0) ? M_PI : 0;
}

double SquareAngleCalculator::getMidpoint( int strip )
{
	return strip * (INTER_STRIP_DIST + STRIP_WIDTH) - (WIDTH/2 + STRIP_WIDTH/2 + INTER_STRIP_DIST);
}

double SquareAngleCalculator::getPolar( int strip )
{
	return offset + atan2(distance, getMidpoint(strip) + (rand3.Uniform() - 0.5) * STRIP_WIDTH/2);
}


