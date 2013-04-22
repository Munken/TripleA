#pragma once
class AngleCalculator
{
public:
	AngleCalculator(void) {};
	virtual ~AngleCalculator(void) {};
	virtual double getPolar(int frontStrip, int backStrip = 0) = 0;
};

