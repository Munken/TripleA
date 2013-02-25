#include "Histogram2D.h"


Histogram2D::Histogram2D(double xLow3, double xHigh3, int xBins3, double xLow4, double xHigh4, int xBins4,  double yLow, double yHigh, int yBins)
{
	int n3 = 3000;
	int n4 = 4000;
	for(int i = 0; i<24; i++){ // FRONT
		n3++; n4++;

		ef3[i] = new TH2F(Form("h%i",n3),Form("h%i",n3),xBins3, xLow3, xHigh3, yBins, yLow, yHigh);
		ef4[i] = new TH2F(Form("h%i",n4),Form("h%i",n4),xBins4, xLow4, xHigh4, yBins, yLow, yHigh);
	}

	n3 = 3100; n4 = 4100;
	for(int i = 0; i<32; i++){ // BACK
		n3++; n4++;
		eb3[i] = new TH2F(Form("h%i",n3),Form("h%i",n3),xBins3, xLow3, xHigh3, yBins, yLow, yHigh);
		eb4[i] = new TH2F(Form("h%i",n4),Form("h%i",n4),xBins4, xLow4, xHigh4, yBins, yLow, yHigh);
	}
}


Histogram2D::~Histogram2D(void)
{
	delete[] &eb4;
	delete[] &ef3;
	delete[] &eb3;
	delete[] &ef3;
}
