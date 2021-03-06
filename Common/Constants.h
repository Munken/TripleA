#include <map>
#include <TString.h>

namespace constants {
extern const double KEV_PER_AMU;// = 931.494061e3; /* keV / amu */
extern const double BORON_11_MASS;// = 11.0093054 * KEV_PER_AMU;
extern const double ALPHA_MASS;// = 4.00260325415 * KEV_PER_AMU;
extern const double BERYLLIUM_8_MASS; // = 8.00530510 * KEV_PER_AMU;
extern const double CARBON_12_MASS;
extern const double CARBON_13_MASS;
extern const double PROTON_MASS;// = 938.272013e3;
extern const int FIRST_RUN;
extern const int LAST_RUN;


extern std::map<int, char*> RUN_TO_AND_OR;
extern std::map<int,int> RUN_TO_ENERGY;
}