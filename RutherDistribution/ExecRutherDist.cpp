// Rutherford.cpp : Defines the entry point for the console application.
//
class Analyzer;

#include "stdafx.h"
#include "TROOT.h"
#include <iostream>
#include <string>
#include "Analyzer.h"
#include "RutherDistribution.h"
#include "Selector.h"
#include "Constants.h"
#include <UpStreamAngleCalculator.h>
#include <DownStreamAngleCalculator.h>
#include <SquareAngleCalculator.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();

    for (int i = 1072; i <= 1072; i++) {
        cout << "**************************** " << i << " ****************************" << endl;

        char* outputChar = Form("RutherDist-%i", i);

        char* title = Form("");


        Analyzer* a = new RutherDistribution(outputChar);
        Selector* s = new Selector(a);

        TString input = Form("../../Data/april_%i_*_m1.root", i);
        TChain ch("h7","My test");
        ch.Add(input);

        ch.Process(s, outputChar);
        
        s -> Clear();
        delete a;

    }

    cout << "\nDone";
    return 0;
}

