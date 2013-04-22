#define NOT_SELECT_ENERGY 1 

class Analyzer;

#include "stdafx.h"
#include "TROOT.h"
#include "TStyle.h"
#include <iostream>
#include <string>
#include "Analyzer.h"
#include "DeadLayer.h"
#include "Selector.h"
#include "Constants.h"
#include "DownStreamAngleCalculator.h"
#include "UpStreamAngleCalculator.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();
    gStyle->SetOptStat(kFALSE);

	
    for (int i = 1045; i <= 1045; i++) {
        cout << "**************************** " << i << " ****************************" << endl;

        char* outputChar = Form("calib-%i", i);

        char* title = "";//Form("%i keV - %s", RUN_TO_ENERGY[i], RUN_TO_AND_OR[i].data());


        Analyzer* a = new DeadLayer(3, outputChar, title, 350);
        Selector* s = new Selector(a);

        TString input = Form("../../Data/calib_%i_0_m1.root", i);
        TChain ch("h7","My test");
        ch.Add(input);

        ch.Process(s, outputChar);
        
        s -> Clear();
        delete a;

    }

    cout << "\nDone";
    string line;
    getline( std::cin, line );
    return 0;
}

#undef NOT_SELECT_ENERGY