#pragma once
#include "TH1.h"

class Histogram
{
public:
	Histogram(double low, double high, int nBins);
	~Histogram(void);
	TH1F* ef3[24];
	TH1F* ef4[24];
	TH1F* eb3[32];
	TH1F* eb4[32];
};

