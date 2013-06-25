#pragma once
#include "SquareAngleCalculator.h"
#include <TRandom3.h>
class FlippedSquareAngleCalculator :
	public SquareAngleCalculator
{
public:
	FlippedSquareAngleCalculator(double distance, double zOffset, double yOffset) : SquareAngleCalculator(distance, zOffset, yOffset) {};
	~FlippedSquareAngleCalculator(void) {};
	virtual double getPolar(int strip, int backStrip = 0) {
		return SquareAngleCalculator::getPolar(17 - strip, backStrip);
	};
	virtual double getAzimuthal(int frontStrip, int backStrip) {
		return SquareAngleCalculator::getAzimuthal(17 - frontStrip, backStrip);
	};
};