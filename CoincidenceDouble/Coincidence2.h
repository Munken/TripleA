#pragma once
#include "Analyzer.h"
#include "TH2.h"
class Coincidence2 : public Analyzer
{
public:
	Coincidence2(char* output, char* title, char* plotOptions = "", float cutUp = 0.1, float cutD = 0.2) ;
	virtual ~Coincidence2(void) { };
	void analyze(Selector* s);
	void terminate();

	
private:
	void fillHistogram(int nFound, double downstreamEnergy);

	TH2F hist;
	double found[24];
	char* output;
	char* plotOptions;
	float cutUp;
	float cutDown;
};

