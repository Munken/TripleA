#define _USE_MATH_DEFINES

#include "SquareAngleCalculator.h"
#include <math.h>
#include <iostream>

const double SquareAngleCalculator::INTER_STRIP_DIST = 0.1;
const double SquareAngleCalculator::WIDTH = 49.5;
const double SquareAngleCalculator::STRIP_WIDTH = 3;
TRandom3 SquareAngleCalculator::rand3;

using namespace std;

SquareAngleCalculator::SquareAngleCalculator(double xOffset, double zOffset) : xOffset(xOffset), zOffset(zOffset), yOffset(-7.27611e+00)
{

}

SquareAngleCalculator::SquareAngleCalculator(double xOffset, double zOffset, double yOffset) : xOffset(xOffset), zOffset(zOffset), yOffset(yOffset)
{

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

	double r = sqrt(pow(xOffset, 2) + pow(y, 2) + pow(z, 2));


	return acos(z / r);
}

double SquareAngleCalculator::getAzimuthal( int frontStrip, int backStrip )
{
	double z = getMidpointZ(frontStrip) + (rand3.Uniform() - 0.5) * STRIP_WIDTH;
	double y = getMidpointY(backStrip) + (rand3.Uniform() - 0.5) * STRIP_WIDTH;

	double r = sqrt(pow(xOffset, 2) + pow(y, 2) + pow(z, 2));
	
	double cosPolar = z / r;
	double sinPolar = sqrt(1.-pow(cosPolar,2));
	double cosAzimuthal = xOffset/(r*sinPolar);
	double sinAzimuthal = y/(r*sinPolar);

	if (sinAzimuthal > 0)
		return acos(cosAzimuthal);
	else
		return 2*M_PI - acos(cosAzimuthal);
	
}


