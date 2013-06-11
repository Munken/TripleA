#pragma once
#include "systemtransformation.h"
class LabToCM :
	public SystemTransformation
{
public:
	LabToCM(double beamEnergy, double ejectedMass, double targetMass = TARGET_MASS);
	~LabToCM(void) {};
	std::pair<double, double> LabToCM::transform( double kineticEnergy, double angle );

	const static double PROTON_MASS;
	const static double TARGET_MASS;
	const static double ALPHA_MASS;

private:
	
	double eCM;
	double gamma;
	double vCM;
	double mass;
};

