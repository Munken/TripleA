#define _USE_MATH_DEFINES

#include "SquareAngleCalculator.h"
#include <math.h>
#include <iostream>

const double SquareAngleCalculator::INTER_STRIP_DIST = 0.1;
const double SquareAngleCalculator::WIDTH = 49.5;
const double SquareAngleCalculator::STRIP_WIDTH = 3;
TRandom3 SquareAngleCalculator::rand3;

using namespace std;

SquareAngleCalculator::SquareAngleCalculator(double distance, double zOffset) : distance(distance), zOffset(zOffset), yOffset(-7.27611e+00)
{
	//offset = (distance < 0) ? M_PI : 0;
}

SquareAngleCalculator::SquareAngleCalculator(double distance, double zOffset, double yOffset) : distance(distance), zOffset(zOffset), yOffset(yOffset)
{
	//offset = (distance < 0) ? M_PI : 0;
}

double SquareAngleCalculator::getMidpointZ( int frontStrip )
{
	return zOffset + frontStrip * (INTER_STRIP_DIST + STRIP_WIDTH) - (WIDTH/2 + STRIP_WIDTH/2 + INTER_STRIP_DIST);
}

double SquareAngleCalculator::getMidpointY( int backStrip )
{
	return yOffset + backStrip * (INTER_STRIP_DIST + STRIP_WIDTH) - (WIDTH/2 + STRIP_WIDTH/2 + INTER_STRIP_DIST);
}

double SquareAngleCalculator::getPolar( int frontStrip, int backStrip )
{
	double z = getMidpointZ(frontStrip) + (rand3.Uniform() - 0.5) * STRIP_WIDTH;
	double y = getMidpointY(backStrip) + (rand3.Uniform() - 0.5) * STRIP_WIDTH;

	double r = sqrt(pow(distance, 2) + pow(y, 2) + pow(z, 2));


	return acos(z / r);
}


