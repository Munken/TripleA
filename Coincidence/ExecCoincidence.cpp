// Rutherford.cpp : Defines the entry point for the console application.
//
class Analyzer;

#include "stdafx.h"
#include "TROOT.h"
#include <iostream>
#include <string>
#include "Analyzer.h"
#include "CoincidenceSingle.h"
#include "Selector.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();


    for (int i = 1193; i <= 1193; i++) {
        cout << "**************************** " << i << " ****************************" << endl;

        char* outputChar = Form("Coincidence2-%i", i);

        Analyzer* a = new CoincidenceSingle(outputChar, "");
        Selector* s = new Selector(a);

        TString input = Form("../../Data/bachelor_%i_0_m1.root", i);
        TChain ch("h7","My test");
        ch.Add(input);

        ch.Process(s, outputChar);
    }

    cout << "\nDone";
    string line;
    getline( std::cin, line );
    return 0;
}

