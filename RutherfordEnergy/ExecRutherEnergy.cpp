// Rutherford.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "RutherfordEnergy.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 1191; i <= 1212; i++)
	{

	cout << "**************************** " << i << " ****************************" << endl;
	TString input = Form("../../Data/bachelor_%i_0_m1.root", i);
	RutherfordEnergy *r = new RutherfordEnergy();
	TChain ch("h7","My test");
	ch.Add(input);

    TString outputPath = Form("RutherfordEnergy%i", i);
    ch.Process(r, outputPath);
	}
	cout << "Done";

	string line;
    getline( std::cin, line );
	return 0;
}

