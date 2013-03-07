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

#include "Selector.h"
#include "Analyzer.h"
#include <TFile.h>
#include "DownStreamCalibration.h"
#include "UpstreamCalibration.h"

using namespace std;

TString file;

EnergyCalibration* Selector::calibrationDownStream = new EnergyCalibration("../../Kalibrering/calib_s3_1000DLM.dat");
EnergyCalibration* Selector::calibrationUpStream = new EnergyCalibration("../../Kalibrering/calib_s3_64DLM.dat");


void Selector::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).
	file = GetOption();

	fOutput->AddAll(gDirectory->GetList());
}

void Selector::SlaveBegin(TTree * /*tree*/)
{
}

Bool_t Selector::Process(Long64_t entry)
{
	GetEntry(entry);
	calculateCalibratedEnergies();
	// count number of entries (=events) ...
	nEvents++;

	analyzer->analyze(this);

	return kTRUE;
}

void Selector::SlaveTerminate()
{
}

void Selector::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.

	//  TCanvas *canvas = new TCanvas("cresult","Resistance",0,0,1600,400);
	analyzer -> terminate();
	WriteToFile();
	printf("Number of Events: %i\n", nEvents);
}


void Selector::WriteToFile() {
	// finally, store all output
	
		TString rootFile = file;
		rootFile += ".root";

		TFile hfile(rootFile,"RECREATE","test");
		fOutput -> Write();
}

void Selector::calculateCalibratedEnergies() {
	writeCalibratedEnergiesToArrays(calibrationUpStream, calibrationDownStream);
}


void Selector::writeCalibratedEnergiesToArrays( EnergyCalibration* upStreamCalibration, EnergyCalibration* downStreamCalibration )
{
	for(int i = 0; i < Nfe3; i++){ 
		int strip = Nsfe3[i];
		double energy = upStreamCalibration -> getEnergyCircularStrip(strip, Ef3[i]);
		cEf3[i] = energy;
	}

	for(int i = 0; i < Nbe3; i++){ 
		int strip = Nsbe3[i];
		double energy = upStreamCalibration -> getEnergyRadialStrip(strip, Eb3[i]);
		cEb3[i] = energy;
	}

	for(int i = 0; i < Nfe4; i++){ 
		int strip = Nsfe4[i];
		double energy = downStreamCalibration -> getEnergyCircularStrip(strip, Ef4[i]);
		cEf4[i] = energy;
	}

	for(int i = 0; i < Nbe4; i++){ 
		int strip = Nsbe4[i];
		double energy = downStreamCalibration -> getEnergyRadialStrip(strip, Eb4[i]);
		cEb4[i] = energy;
	}
}


Selector::Selector( Analyzer* a ) : nEvents(0)
{
	analyzer = a;
}




