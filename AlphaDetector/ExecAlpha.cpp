// Rutherford.cpp : Defines the entry point for the console application.
//
class Analyzer;

#include "stdafx.h"
#include "Analyzer.h"
#include "AlphaDetector.h"
#include "Constants.h"

using namespace std;
using namespace constants;


int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();

    TDatime begin, end;
    for (int i = FIRST_RUN; i <= LAST_RUN; i++) {
        cout << "**************************** " << i << " ****************************" << endl;

        char* outputChar = Form("Alpha-%i", i);

        char* title = Form("%i keV - %s", RUN_TO_ENERGY2[i], RUN_TO_AND_OR2[i]);


        Analyzer* a = new AlphaDetector(2370, outputChar, title, 0.03);
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

