#pragma once
#include "Analyzer.h"
#include "EnergyCalibration.h"
#include "TH2.h"
class CoincidenceSingle : public Analyzer
{
public:
	CoincidenceSingle(char* output, char* plotOptions = "", float cutUp = 0.1, float cutD = 0.2) ;
	~CoincidenceSingle(void) {};
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

