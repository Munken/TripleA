#include "stdafx.h"
#include "Coincidence2.h"
#include "Selector.h"
#include <iostream>
#include <TCanvas.h>
#include "Angle.h"

using namespace std;


Coincidence2::Coincidence2( char* output, char* plotOptions /*= ""*/, float cutUp /*= 0.1*/, float cutD /*= 0.2*/) : 
	cutUp(cutUp), cutDown(cutD), plotOptions(plotOptions)
{
	this -> output = output;
	histUpP = TH2F("HistUpP", "Upstream - Count vs. StripC and StripR", 24, 0.5, 24.5, 32, 0.5, 32.5);
	histUpA = TH2F("HistUpA", "Upstream - Count vs. StripC and StripR", 24, 0.5, 24.5, 32, 0.5, 32.5);
	histDownP = TH2F("HistDownP", "DownstreamP - Count vs. StripC and StripR", 24, 0.5, 24.5, 32, 0.5, 32.5);
	histDownA = TH2F("HistDownA", "DownstreamA - Count vs. StripC and StripR", 24, 0.5, 24.5, 32, 0.5, 32.5);
}


void Coincidence2::analyze(Selector* s) {
	
	//// ----- Detector #3 (S3_64um) -----
	for (int i = 0; i < s -> Nfe3; i++) {
		double energyC = s -> cEf3[i];

		for (int j = 0; j < s -> Nbe3; j++) {
			double energyR = s -> cEb3[j];
			double diff = abs(energyR - energyC);

			if (diff / energyC > cutDown) continue;

			int stripC = s -> Nsfe3[i];
			int stripR = s -> Nsbe3[i];

			double area = AngleCalculator::getCircularArea(stripC);
			TH2F* hist = (energyC > 3300) ? &histDownA : &histDownP;
			hist -> Fill(stripC, stripR, 1/area);
			break;
		}
	}

	//// ----- Detector #3 (S3_1000um) -----
	for (int i = 0; i < s -> Nfe4; i++) {
		double energyC = s -> cEf4[i];

		for (int j = 0; j < s -> Nbe4; j++) {
			double energyR = s -> cEb4[j];
			double diff = abs(energyR - energyC);

			if (diff / energyC > cutUp) continue;

			int stripC = s -> Nsfe4[i];
			int stripR = s -> Nsbe4[i];
			
			double area = AngleCalculator::getCircularArea(stripC);

			TH2F* hist = (energyC > 3500) ? &histUpA : &histUpP;
			hist -> Fill(stripC, stripR, 1/area);
			break;
		}
	}

}

void Coincidence2::terminate() {
	char* dir = "result";
	TCanvas cp("DownP", "DownP", 1200, 1200);
	histDownP.DrawNormalized(plotOptions);
	cp.SaveAs(Form("%s/DownP-%s.png", dir, output));

	TCanvas ca("DownA", "DownA", 1200, 1200);
	histDownA.DrawNormalized(plotOptions);
	ca.SaveAs(Form("%s/DownA-%s.png", dir, output));

	TCanvas dp("UpP", "UpP", 1200, 1200);
	histUpP.DrawNormalized(plotOptions);
	dp.SaveAs(Form("%s/UpP-%s.png", dir, output));

	TCanvas da("UpA", "UpA", 1200, 1200);
	histUpA.DrawNormalized(plotOptions);
	da.SaveAs(Form("%s/UpA-%s.png", dir, output));
}
