// Rutherford.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "AngleEnergy2D.h"
#include "Constants.h"
#include "TROOT.h"
#include "TStyle.h"
#include "LabToCM.h"
#include "DeadLayerCalibration.h"
#include "DownStreamAngleCalculator.h"

using namespace std;
using namespace constants;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();
    gStyle->SetOptStat(kFALSE);

    
    for (int i = 1191; i <= 1212; i++)
    {
        cout << "**************************** " << i << " ****************************" << endl;
        TString input = Form("../../Data/bachelor_%i_0_m1.root", i);
        int beamEnergy = RUN_TO_ENERGY[i];
        string andOr = RUN_TO_AND_OR[i];

        LabToCM* trans = new LabToCM(beamEnergy, LabToCM::PROTON_MASS);
        //SystemTransformation* trans = new LabToLab();
        AngleEnergy2D *r = new AngleEnergy2D(trans, Form("%i keV - %s", beamEnergy, andOr.data()));
        TChain ch("h7");
        ch.Add(input);

        TString outputPath = Form("result/AngleEnergy%i-CMp", i);
        ch.Process(r, outputPath);
    }

    /*DeadLayerCalibration* e = new DeadLayerCalibration("../../Kalibrering/Hans_1000_2M.dat", "../../Range/he4si", new DownStreamAngleCalculator());
    cout << e->getRange(700) << endl;
    cout << e->getEnergy(2.59) << endl;*/
    
    


    cout << "\nDone";
    string line;
    getline( std::cin, line );
    return 0;
}

