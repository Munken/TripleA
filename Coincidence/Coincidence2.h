#pragma once
#include "Analyzer.h"
#include "EnergyCalibration.h"
#include "TH2.h"
class Coincidence2 : public Analyzer
{
public:
	Coincidence2(char* output, char* plotOptions = "", float cutUp = 0.1, float cutD = 0.2) ;
	~Coincidence2(void) {};
	void analyze(Selector* s);
	void terminate();

	
private:
	TH2F histUpP;
	TH2F histUpA;
	TH2F histDownP;
	TH2F histDownA;
	char* output;
	char* plotOptions;
	float cutUp;
	float cutDown;
};

