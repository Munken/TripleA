// Rutherford.cpp : Defines the entry point for the console application.
//
class Analyzer;

#include "stdafx.h"
#include "TROOT.h"
#include <iostream>
#include <string>
#include "Analyzer.h"
#include "Selector.h"
#include "Constants.h"
#include <TStyle.h>
#include "SpetrumPlotter.h"
#include "SquareAngleCalculator.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();
	gStyle -> SetOptStat(kFALSE);



    {int i = 1044;
        cout << "**************************** " << i << " ****************************" << endl;

        char* outputChar = Form("spec-%i", i);

        char* title = Form("");


        Analyzer* a = new SpectrumPlotter(outputChar);
        Selector* s = new Selector(a);

        TString input = Form("../../Data/calib_%i_*_m1.root", i);
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

