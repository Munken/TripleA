#pragma once
#include "Analyzer.h"
#include "EnergyCalibration.h"
#include "TH2.h"
class Coincidence2 : public Analyzer
{
public:
	Coincidence2(char* output, char* plotOptions = "", float cut = 0.1) ;
	~Coincidence2(void) {};
	void analyze(Selector* s);
	void terminate();

private:
	TH2F histUp;
	TH2F histDown;
	char* output;
	char* plotOptions;
	float cut;
	float cutR;
};

