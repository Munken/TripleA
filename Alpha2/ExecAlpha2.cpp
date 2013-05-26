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
#include <TStyle.h>
#include <TColor.h>
#include "UpStreamAngleCalculator.h"
#include "DownStreamAngleCalculator.h"
#include "SquareAngleCalculator.h"
#include "TVector3.h"
#include "FlippedSquareAngleCalculator.h"

using namespace std;
using namespace constants;

int _tmain(int argc, _TCHAR* argv[])
{
    gROOT -> SetBatch();
    gStyle->SetOptStat(kFALSE);

	const Int_t NRGBs = 5;
	const Int_t NCont = 255;

	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);

	SquareAngleCalculator s1(33, -2.52243, -7.27611e+00);
	FlippedSquareAngleCalculator s2(-30, 0, 0);

    //for (int i = 1084; i <= 1133; i++) 
    {int i = 1077;
	
        cout << "**************************** " << i << " ****************************" << endl;
        //cout << "Carbon state: " << BORON_11_MASS + PROTON_MASS + RUN_TO_ENERGY[i] * 11./12 - CARBON_12_MASS << " keV" << endl;

        char* outputChar = Form("Alpha2-%i", i);
		char* outAnalyzer = Form("Alpha2-%i", i);
        char* title = "";//Form("%i keV - %s", RUN_TO_ENERGY[i], RUN_TO_AND_OR[i]);


        Analyzer* a = new Alpha2(2000, outAnalyzer, title, 1460, 1560, 1400, 1660, 75);
        Selector* s = new Selector(a);

        TString input = Form("../../Data/april_%i_*_m1.root", i);
        TChain ch("h7","My test");
        ch.Add(input);
		/*ch.Add(Form("../../Data/april_%i_*_m1.root", 1092));
		ch.Add(Form("../../Data/april_%i_*_m1.root", 1093));
		ch.Add(Form("../../Data/april_%i_*_m1.root", 1098));
		ch.Add(Form("../../Data/april_%i_*_m1.root", 1100));
		for (int i = 21; i <= 28; i++) {
			ch.Add(Form("../../Data/april_11%i_*_m1.root", i));
		}*/
		
        ch.Process(s, outputChar);
        
        s -> Clear();
        delete a;

    }

	string in;
    cout << "\nDone";
	getline(cin, in);
    return 0;
}

