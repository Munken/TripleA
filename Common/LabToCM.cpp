#include "LabToCM.h"
#include <math.h>
#include <iostream>

using namespace std;

const double LabToCM::PROTON_MASS = 938.272013e3; // keV
const double LabToCM::ALPHA_MASS = 3.727379240e6; // keV
const double LabToCM::TARGET_MASS = 11.0093054 /* amu */ * 931.494061e3 /* keV / amu */;

LabToCM::LabToCM( double beamEnergy, double ejectedMass, double targetMass /* = TARGET_MASS*/ )
{
	mass = ejectedMass;
	eCM = sqrt(pow(targetMass + PROTON_MASS, 2) + 2 * targetMass * beamEnergy);
	gamma = (targetMass + PROTON_MASS + beamEnergy) / eCM;
	vCM = sqrt(1 - 1/(pow(gamma,2)));
}

std::pair<double, double> LabToCM::transform( double kineticEnergy, double angle )
{
	double labEnergy = mass + kineticEnergy;
	double labMomentum = sqrt(pow(labEnergy,2) - pow(mass,2));

	double cmEnergy = gamma * (labEnergy - vCM * labMomentum * cos(angle));
	double cmMomentum = sqrt(pow(cmEnergy,2) - pow(mass,2));
	double cmMomentumZ = gamma * (labMomentum * cos(angle) - vCM * labEnergy);

	double cmKineticEnergy = cmEnergy - mass;
	double cmAngle = acos(cmMomentumZ / cmMomentum);
	return std::make_pair(cmKineticEnergy, cmAngle);
}