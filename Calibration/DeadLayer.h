#pragma once
#include "Analyzer.h"
#include "TH2.h"
#include "Angle.h"
class DeadLayer : public Analyzer
{
public:
	DeadLayer(char* output, char* title, int chanDiff) ;
	virtual ~DeadLayer(void) { delete angleCalc;};
	void analyze(Selector* s);
	void terminate();

	void writeHistograms();

	
private:
	void processSector(int refChan, Selector* s);

	char* output;
	TH1F* hist[24];
	TH2F coin;
	AngleCalculator* angleCalc;
	int chanDiff;
};

