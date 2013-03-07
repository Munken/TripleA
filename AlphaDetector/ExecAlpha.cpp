// Rutherford.cpp : Defines the entry point for the console application.
//
class Analyzer;

#include "stdafx.h"
#include "TROOT.h"
#include <iostream>
#include <string>
#include "Analyzer.h"
#include "AlphaDetector.h"
#include "Selector.h"
//#include "Constants.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();

	


    for (int i = 1194; i <= 1194; i++) {
        cout << "**************************** " << i << " ****************************" << endl;

        char* outputChar = Form("Alpha-%i", i);

        //char* title = Form("%i keV - %s", RUN_TO_ENERGY[i], RUN_TO_AND_OR[i].data());


        Analyzer* a = new AlphaDetector(2370, outputChar, "");
        Selector* s = new Selector(a);

        TString input = Form("../../Data/bachelor_%i_0_m1.root", i);
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

