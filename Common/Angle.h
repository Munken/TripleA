#pragma once
class AngleCalculator
{
public:
	AngleCalculator(const double distance);
	~AngleCalculator(void);
	virtual double getAzimuthMin(int strip);
	virtual double getAzimuthMax(int strip);

	static double getMinRadius(int strip);
	static double getMaxRadius(int strip);

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
};

