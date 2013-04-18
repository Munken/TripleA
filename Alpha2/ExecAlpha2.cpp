#define NOT_SELECT_ENERGY 1 


class Analyzer;

#include "stdafx.h"
#include "TROOT.h"
#include <iostream>
#include <string>
#include "Analyzer.h"
#include "Alpha2.h"
#include "Selector.h"
#include "Constants.h"

using namespace std;
using namespace constants;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();


    
	
    for (int i = 1077; i <= 1077; i++) {
        cout << "**************************** " << i << " ****************************" << endl;

        char* outputChar = Form("Alpha2-%i", i);

        char* title = Form("%i keV - %s", RUN_TO_ENERGY[i], RUN_TO_AND_OR[i]);


        Analyzer* a = new Alpha2(outputChar, title, 50);
        Selector* s = new Selector(a);

        TString input = Form("../../Data/april_%i_*_m1.root", i);
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

