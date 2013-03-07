#include <map>

namespace constants {
extern const double KEV_PER_AMU2;// = 931.494061e3; /* keV / amu */
extern const double BORON_11_MASS2;// = 11.0093054 * KEV_PER_AMU;
extern const double ALPHA_MASS2;// = 4.00260325415 * KEV_PER_AMU;
extern const double PROTON_MASS2;// = 938.272013e3;
extern const int FIRST_RUN;
extern const int LAST_RUN;


extern std::map<int, char*> RUN_TO_AND_OR2;
extern std::map<int,int> RUN_TO_ENERGY2;
}