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
#include <iostream>

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
#ifdef NOT_SELECT_ENERGY
	calculateCalibratedEnergies();
#endif
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
		double energy = upStreamCalibration -> getEnergyFrontStrip(strip, Ef3[i]);
		cEf3[i] = energy;
	}

	for(int i = 0; i < Nbe3; i++){ 
		int strip = Nsbe3[i];
		double energy = upStreamCalibration -> getEnergyBackStrip(strip, Eb3[i]);
		cEb3[i] = energy;
	}

	for(int i = 0; i < Nfe4; i++){ 
		int strip = Nsfe4[i];
		double energy = downStreamCalibration -> getEnergyFrontStrip(strip, Ef4[i]);
		cEf4[i] = energy;
	}

	for(int i = 0; i < Nbe4; i++){ 
		int strip = Nsbe4[i];
		double energy = downStreamCalibration -> getEnergyBackStrip(strip, Eb4[i]);
		cEb4[i] = energy;
	}
}


Selector::Selector( Analyzer* a ) : nEvents(0)
{
	analyzer = a;
	Nfe = new Int_t*[4];
	Nfe[0] = &Nfe1;
	Nfe[1] = &Nfe2;
	Nfe[2] = &Nfe3;
	Nfe[3] = &Nfe4;

	Nbe = new Int_t*[4];
	Nbe[0] = &Nbe1;
	Nbe[1] = &Nbe2;
	Nbe[2] = &Nbe3;
	Nbe[3] = &Nbe4;

	Nsfe = new UChar_t*[4];
	Nsfe[0] = Nsfe1;
	Nsfe[1] = Nsfe2;
	Nsfe[2] = Nsfe3;
	Nsfe[3] = Nsfe4;

	Nsbe = new UChar_t*[4];
	Nsbe[0] = Nsbe1;
	Nsbe[1] = Nsbe2;
	Nsbe[2] = Nsbe3;
	Nsbe[3] = Nsbe4;

	Ef = new Short_t*[4];
	Ef[0] = Ef1;
	Ef[1] = Ef2;
	Ef[2] = Ef3;
	Ef[3] = Ef4;

	Eb = new Short_t*[4];
	Eb[0] = Eb1;
	Eb[1] = Eb2;
	Eb[2] = Eb3;
	Eb[3] = Eb4;	
}




