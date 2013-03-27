// Rutherford.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "RutherfordEnergy.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int input[4] = {44, 45, 55, 56};
	for (int j = 0; j < 4; j++)
	{
		int i = 1000 + input[j];
		cout << "**************************** " << i << " ****************************" << endl;
		//TString input = Form("../../Data/bachelor_%i_0_m1.root", i);
		TString input = Form("../../Data/calib_%i_0_m1.root", i);
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

