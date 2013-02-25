#pragma once
#include "TH2.h"
class Histogram2D
{
public:
	Histogram2D(double xLow3, double xHigh3, int xBins3, double xLow4, double xHigh4, int xBins4,  double yLow, double yHigh, int yBins);
	~Histogram2D(void);
	TH2F* ef3[24];
	TH2F* ef4[24];
	TH2F* eb3[32];
	TH2F* eb4[32];
};

