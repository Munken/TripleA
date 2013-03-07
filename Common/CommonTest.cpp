// Rutherford.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Constants.h"
#include "TROOT.h"
#include "TStyle.h"
#include <tchar.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();
    gStyle-> SetOptStat(kFALSE);


    /*DeadLayerCalibration* e = new DeadLayerCalibration("../../Kalibrering/Hans_1000_2M.dat", "../../Range/he4si", new DownStreamAngleCalculator());
    cout << e->getRange(700) << endl;
    cout << e->getEnergy(2.59) << endl;*/


    cout << "\nDone";
    string line;
    getline( std::cin, line );
    return 0;
}

