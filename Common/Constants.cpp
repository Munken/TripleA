#include "Constants.h"

namespace constants {
std::map<int, char*> create_AND_OR();
std::map<int,int> createEnergyMap();

const int FIRST_RUN = 1191;
const int LAST_RUN = 1212;

const double KEV_PER_AMU = 931.494061e3;
const double BORON_11_MASS = 11.0093054 * KEV_PER_AMU;
const double ALPHA_MASS = 4.00260325415 * KEV_PER_AMU;
const double BERYLLIUM_8_MASS = 8.00530510 * KEV_PER_AMU;
const double CARBON_12_MASS = 12 * KEV_PER_AMU;
const double PROTON_MASS = 938.272013e3;


std::map<int, char*> RUN_TO_AND_OR = create_AND_OR();
std::map<int,int> RUN_TO_ENERGY = createEnergyMap();

std::map<int, char*> create_AND_OR()
{
	std::map<int, char*> result;
	result[1191] = "OR";
	result[1192] = "AND";
	result[1193] = "AND";
	result[1194] = "OR";
	result[1195] = "AND";
	result[1196] = "OR";
	result[1197] = "AND";
	result[1198] = "OR";
	result[1199] = "AND";
	result[1200] = "OR";
	result[1201] = "AND";
	result[1202] = "OR";
	result[1203] = "AND";
	result[1204] = "OR";
	result[1205] = "AND";
	result[1206] = "OR";
	result[1207] = "AND";
	result[1208] = "OR";
	result[1209] = "AND";
	result[1210] = "OR";
	result[1211] = "AND";
	result[1212] = "OR";
	result[1213] = "AND";

	return result;
}

std::map<int,int> createEnergyMap()
{
	std::map<int,int> result;
	result[1191] = 2000;
	result[1192] = 2001;
	result[1193] = 2001;
	result[1194] = 2370;
	result[1195] = 2370;
	result[1196] = 2150;
	result[1197] = 2150;
	result[1198] = 1850;
	result[1199] = 1850;
	result[1200] = 1700;
	result[1201] = 1700;
	result[1202] = 1550;
	result[1203] = 1550;
	result[1204] = 1400;
	result[1205] = 1400;
	result[1206] = 1000;
	result[1207] = 1000;
	result[1208] = 850;
	result[1209] = 850;
	result[1210] = 699;
	result[1211] = 699;
	result[1212] = 550;
	result[1213] = 550;

	return result;
}
}