#include "LabToLab.h"




std::pair<double, double> LabToLab::transform( double kineticEnergy, double angle ) {
	return std::make_pair(kineticEnergy, angle);
}
