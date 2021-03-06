#pragma once
#include "Analyzer.h"
#include "TH2.h"
#include "CircularAngleCalculator.h"
class DeadLayer : public Analyzer
{
public:
	DeadLayer(int detector, char* output, char* title, int chanDiff) ;
	virtual ~DeadLayer(void) { delete angleCalc;};
	void analyze(Selector* s);
	void terminate();

	void writeHistograms();

	
private:
	void processSector(int refChan, Selector* s);
	int findPeak( TH1F& hist );
	const static int N_SECOND_STRIP = 24;

	char* output;
	TH1F* hist[N_SECOND_STRIP];
	TH2F coin;
	CircularAngleCalculator* angleCalc;
	int chanDiff;
	int min, max;

	const int detector;
};

