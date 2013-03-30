#include "stdafx.h"
#include "DeadLayer.h"
#include "Selector.h"
#include <TCanvas.h>
#include <iostream>
#include "TGraphErrors.h"
#include "DownStreamAngleCalculator.h"
#include "TSpectrum.h"

using namespace std;

DeadLayer::DeadLayer( char* output, char* title, int chanDiff) : chanDiff(chanDiff), 
	coin("Coin", "Coincidence;Strip;Channel", N_SECOND_STRIP, 0.5, N_SECOND_STRIP + 0.5, 1748, 300, 2048)
{
	this -> output = output;
	for (int i = 0; i < N_SECOND_STRIP; i++) {
		hist[i] = new TH1F(Form("%i", i), "", 2048, 0, 2048);
	}
	angleCalc = new DownStreamAngleCalculator();
}


void DeadLayer::analyze(Selector* s) {
	
	
	for (int i = 0; i < s -> Nbe4; i++) {
		int strip = s -> Nsbe4[i];
		int chan = s -> Eb4[i];

		if (strip != 15) continue;

		processSector(chan, s);
	}

}

void DeadLayer::processSector( int refChan, Selector* s )
{
	for (int j = 0; j < s -> Nfe4; j++) {
		int strip = s -> Nsfe4[j];
		int chan = s -> Ef4[j];
		int diff = abs(refChan - chan);

		if (diff > chanDiff) continue;
		hist[strip - 1] -> Fill(refChan);
		coin.Fill(strip, refChan);
	}
}


void DeadLayer::terminate() {
	writeHistograms();

	const int N = N_SECOND_STRIP;
	double y[N];
	double x[N];
	double y0;

	for (int i = 0; i < N; i++) {
		double angle = angleCalc -> getAzimuthMin(i + 1);
		x[i] = 1 / cos(angle);
		y[i] = hist[i] -> GetMaximumBin();


		if (i == 0) y0 = y[0];
		y[i] /= y0;
		cout << y[i] << endl;

	}

	TCanvas c("Rel", "Rel", 1200, 1200);
	TGraphErrors graph(N, x, y);
	graph.SetTitle(";cos^{-1}(#phi);C/C_{0}");
	graph.SetMarkerStyle(kOpenCircle);
	graph.SetMarkerColor(kBlue);
	graph.SetLineColor(kBlue);
	graph.DrawClone("AP");

	c.SaveAs(Form("result/%s-R.png", output));

}



void DeadLayer::writeHistograms()
{
	char* dir = "result";

	for (int i = 0; i < N_SECOND_STRIP; i++) {
		TCanvas dp("Up", "Up", 1200, 1200);
		dp.SetLeftMargin(0.15);
		hist[i] -> Draw();
		dp.SaveAs(Form("%s/%s-%i.png", dir, output, i));
	}

	TCanvas c("Up", "", 1200, 1200);
	coin.Draw();
	c.SaveAs(Form("%s/%s-C.png", dir, output));
}


