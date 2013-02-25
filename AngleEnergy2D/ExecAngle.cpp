// Rutherford.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "AngleEnergy2D.h"
#include "RunToEnergy.h"
#include "TROOT.h"
#include "LabToCM.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();
    for (int i = 1191; i <= 1212; i++)
    {
    cout << "**************************** " << i << " ****************************" << endl;
    TString input = Form("../../Data/bachelor_%i_0_m1.root", i);
    int beamEnergy = runToEnergy[i];
    string andOr = runToAndOr[i];

    LabToCM* trans = new LabToCM(beamEnergy, LabToCM::PROTON_MASS);
    //SystemTransformation* trans = new LabToLab();
    AngleEnergy2D *r = new AngleEnergy2D(trans, Form("%i keV - %s", beamEnergy, andOr.data()));
    TChain ch("h7");
    ch.Add(input);

    TString outputPath = Form("result/AngleEnergy%i-CMp", i);
    ch.Process(r, outputPath);
    }

    cout << "\nDone";
    string line;
    getline( std::cin, line );
    return 0;
}

