#pragma once
class AngleCalculator
{
public:
	AngleCalculator(void) {};
	virtual ~AngleCalculator(void) {};
	virtual double getPolar(int strip) = 0;
};

