#include "stdafx.h"
#include "Coincidence2.h"
#include "Selector.h"
#include <iostream>
#include <TCanvas.h>
#include "Angle.h"

using namespace std;


Coincidence2::Coincidence2( char* output, char* plotOptions /*= ""*/, float cut /*= 0.1*/ ) : cut(cut), plotOptions(plotOptions)
{
	this -> output = output;
	histUp = TH2F("HistUp", "Upstream - Count vs. StripC and StripR", 24, 0.5, 24.5, 32, 0.5, 32.5);
	histDown = TH2F("HistDown", "Downstream - Count vs. StripC and StripR", 24, 0.5, 24.5, 32, 0.5, 32.5);
}


void Coincidence2::analyze(Selector* s) {
	
	//// ----- Detector #3 (S3_64um) -----
	for (int i = 0; i < s -> Nfe3; i++) {
		double energyC = s -> cEf3[i];

		for (int j = 0; j < s -> Nbe3; j++) {
			double energyR = s -> cEb3[j];
			double diff = abs(energyR - energyC);

			if (diff / energyC > cut) continue;

			int stripC = s -> Nsfe3[i];
			int stripR = s -> Nsbe3[i];

			double area = AngleCalculator::getCircularArea(stripC);
			histDown.Fill(stripC, stripR, 1/area);
			break;
		}
	}

	//// ----- Detector #3 (S3_1000um) -----
	for (int i = 0; i < s -> Nfe4; i++) {
		double energyC = s -> cEf4[i];

		for (int j = 0; j < s -> Nbe4; j++) {
			double energyR = s -> cEb4[j];
			double diff = abs(energyR - energyC);

			if (diff / energyC > cut) continue;

			int stripC = s -> Nsfe4[i];
			int stripR = s -> Nsbe4[i];
			stripC = (stripC <= 16) ? stripC : 17 + 24 - stripC;
			/*stripR = (stripR <= 16) ? 17 - stripR : stripR;
			stripC = (stripC <= 16) ? stripC : 17 + 24 - stripC;
			stripC = (stripC <= 16) ? stripC + 8 : */
			double area = AngleCalculator::getCircularArea(stripC);
			histUp.Fill(stripC, stripR, 1/area);
			break;
		}
	}

}

void Coincidence2::terminate() {
	TCanvas c("Down", "Down", 1200, 1200);
	histDown.DrawNormalized(plotOptions);
	//c.SaveAs(Form("Area/Down-%s.png", output));

	TCanvas d("Up", "Up", 1200, 1200);
	histUp.DrawNormalized(plotOptions);
	d.SaveAs(Form("Area/LIUp-%s.png", output));
}
