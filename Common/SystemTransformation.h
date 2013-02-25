#pragma once
#include <utility>
class SystemTransformation
{
public:
	SystemTransformation(void);
	~SystemTransformation(void);
	virtual std::pair<double, double> transform(double kineticEnergy, double angle) = 0;


};

