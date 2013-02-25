// The class definition in Rutherford.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("Rutherford.C")
// Root > T->Process("Rutherford.C","some options")
// Root > T->Process("Rutherford.C+")
//

#include "stdafx.h"
#include "AngleEnergy2D.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "EnergyCalibration.h"
#include "UpStreamAngleCalculator.h"
#include "DownStreamAngleCalculator.h"
using namespace std;

UInt_t fNumberOfEvents;
TString file;
const int cutoff = 100;

EnergyCalibration AngleEnergy2D::calibrationDownStream("../../Kalibrering/linfit_S3_1000um_run_1188.dat");
EnergyCalibration AngleEnergy2D::calibrationUpStream("../../Kalibrering/linfit_S3_64um_runs_1215_1236.dat");
AngleCalculator AngleEnergy2D::frontAngleCalculator = UpstreamAngleCalculator();
AngleCalculator AngleEnergy2D::backAngleCalculator = DownStreamAngleCalculator();


void AngleEnergy2D::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

	fNumberOfEvents = 0;
  file = GetOption();

  fOutput->AddAll(gDirectory->GetList());
}

void AngleEnergy2D::SlaveBegin(TTree * /*tree*/)
{
}

Bool_t AngleEnergy2D::Process(Long64_t entry)
{
  GetEntry(entry);

  // count number of entries (=events) ...
  ++fNumberOfEvents;

  // analsiys code comes here - fill histograms

  FillSimple();

  return kTRUE;
}

void AngleEnergy2D::SlaveTerminate()
{
}

void AngleEnergy2D::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  //  TCanvas *canvas = new TCanvas("cresult","Resistance",0,0,1600,400);

	saveResult();

  WriteToFile();
  printf("Number of Events: %i\n", fNumberOfEvents);
}


void AngleEnergy2D::WriteToFile() {
  // finally, store all output
  TString rootFile = file;
  rootFile += ".root";
  
  TFile hfile(rootFile,"RECREATE","test");
  fOutput -> Write();
}


void AngleEnergy2D::FillSimple()
{


  //// ----- Detector #3 (S3_64um) -----
	for(int i = 0; i < Nfe3; i++){ 
		int strip = Nsfe3[i];
		double energy = calibrationUpStream.getEnergyCircularStrip(strip, Ef3[i]);
		double angle = frontAngleCalculator.getAzimuthMax(strip);

		//if (energy < 1800) continue;

		pair<double, double> result = systemTransformer -> transform(energy, angle);
		energy = result.first;
		angle = result.second;

		hist.Fill(angle, energy);
	}

	// /* // ----- Detector #4 (S3_1000um) -----   */
    for(int i = 0; i < Nfe4; i++){
		int strip = Nsfe4[i];
		double energy = calibrationDownStream.getEnergyCircularStrip(strip, Ef4[i]);
		double angle = backAngleCalculator.getAzimuthMax(strip);

		//if (energy < 1800) continue;

		
		pair<double, double> result = systemTransformer -> transform(energy, angle);
		energy = result.first;
		angle = result.second;
		hist.Fill(angle, energy);
	 }

}

void AngleEnergy2D::saveResult()
{
	TCanvas canvas("cresult","Resistance",0,0,1600,1600);
	hist.Draw();
	TString rootFile = file;
	rootFile += ".png";
	canvas.SaveAs(rootFile);
}

