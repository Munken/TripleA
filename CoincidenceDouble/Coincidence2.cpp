#include "stdafx.h"
#include "Coincidence2.h"
#include "Selector.h"
#include <TCanvas.h>

using namespace std;


Coincidence2::Coincidence2( char* output, char* title, char* plotOptions /*= ""*/, float cutUp /*= 0.1*/, float cutD /*= 0.2*/ ) : 
	cutUp(cutUp), cutDown(cutD), plotOptions(plotOptions)
{
	this -> output = output;
	hist = TH2F("HistUpP", title, 4096, 400, 9000, 4096, 400, 7000);
	hist.SetXTitle("Downstream E");
	hist.SetYTitle("Upstream E");
	hist.GetYaxis()->SetTitleOffset(2);
}


void Coincidence2::analyze(Selector* s) {
	
	if (s -> Nfe3 < 1 && s -> Nbe3 < 1 && s -> Nfe4 < 1 && s -> Nbe4 < 1) return;

	//// ----- Detector #3 (S3_64um) -----
	int count = 0;
	for (int i = 0; i < s -> Nfe3; i++) {
		double energyC = s -> cEf3[i];

		for (int j = 0; j < s -> Nbe3; j++) {
			double energyR = s -> cEb3[j];
			double diff = abs(energyR - energyC);

			if (diff / energyC > cutDown) continue;
						
			found[count++] = energyC;
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
			
			fillHistogram(count, energyR);

			break;
		}
	}

}

void Coincidence2::fillHistogram( int nFound, double downstreamEnergy ) {
	for (int i = 0; i < nFound; i++) {
		hist.Fill(downstreamEnergy, found[i]);
	}
}

void Coincidence2::terminate() {
	char* dir = "result";
	
	TCanvas dp("Up", "Up", 1200, 1200);
	dp.SetLeftMargin(0.15);
	hist.DrawNormalized(plotOptions);
	dp.SaveAs(Form("%s/%s.png", dir, output));

}


