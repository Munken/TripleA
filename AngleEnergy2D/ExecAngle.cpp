// Rutherford.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "AngleEnergy2D.h"
#include "Constants.h"
#include "TROOT.h"
#include "TStyle.h"
#include "LabToCM.h"
#include "LabToLab.h"
#include "DeadLayerCalibration.h"
#include "DownStreamAngleCalculator.h"
#include "SquareAngleCalculator.h"
#include <TF1.h>

using namespace std;
using namespace constants;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();
    gStyle->SetOptStat(kFALSE);

	

	for (int i = 1077; i <= 1077; i++)
    {
        cout << "**************************** " << i << " ****************************" << endl;
        TString input = Form("../../Data/april_%i_*_m1.root", i);
        int beamEnergy = 2000/*RUN_TO_ENERGY[i]*/;
        string andOr = "AND"/*RUN_TO_AND_OR[i]*/;

		char* outputPath = Form("result/AngleEnergy%i", i);

		AngleEnergy2D *r = new AngleEnergy2D(outputPath, ";Vinkel [grader];Energi [keV]", beamEnergy);
        TChain ch("h7");
        ch.Add(input);

        ch.Process(r, outputPath);
    }

    /*DeadLayerCalibration* e = new DeadLayerCalibration("../../Kalibrering/Hans_1000_2M.dat", "../../Range/he4si", new DownStreamAngleCalculator());
    cout << e->getRange(700) << endl;
    cout << e->getEnergy(2.59) << endl;*/
    
    


    cout << "\nDone";
    string line;
    //getline( std::cin, line );
    return 0;
}

