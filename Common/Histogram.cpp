#include "Histogram.h"


Histogram::Histogram( double low, double high, int nBins )
{
	int n3 = 3000;
	int n4 = 4000;
	for(int i = 0; i<24; i++){ // FRONT
		n3++; n4++;

		ef3[i] = new TH1F(Form("h%i",n3),Form("h%i",n3),nBins,low,high);
		ef4[i] = new TH1F(Form("h%i",n4),Form("h%i",n4),nBins,low,high);
	}

	n3 = 3100; n4 = 4100;
	for(int i = 0; i<32; i++){ // BACK
		n3++; n4++;
		eb3[i] = new TH1F(Form("h%i",n3),Form("h%i",n3),nBins,low,high);
		eb4[i] = new TH1F(Form("h%i",n4),Form("h%i",n4),nBins,low,high);
	}
}


Histogram::~Histogram(void)
{
	delete[] &eb4;
	delete[] &ef3;
	delete[] &eb3;
	delete[] &ef3;
}
