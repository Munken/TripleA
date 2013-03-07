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
#include "RutherfordEnergy.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "EnergyCalibration.h"
using namespace std;

UInt_t fNumberOfEvents;
TString file;
const int cutoff = 100;

EnergyCalibration RutherfordEnergy::calibrationDownStream("../../Kalibrering/linfit_S3_1000um_run_1188.dat");
EnergyCalibration RutherfordEnergy::calibrationUpStream("../../Kalibrering/linfit_S3_64um_runs_1215_1236.dat");


void RutherfordEnergy::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

    fNumberOfEvents = 0;
  file = GetOption();

  fOutput->AddAll(gDirectory->GetList());
}

void RutherfordEnergy::SlaveBegin(TTree * /*tree*/)
{
}

Bool_t RutherfordEnergy::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either Rutherford::GetEntry() or TBranch::GetEntry()
  // to read either all or the required parts of the data. When processing
  // keyed objects with PROOF, the object is already loaded and is available
  // via the fObject pointer.
  //
  // This function should contain the "body" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  // - - - - - - - - - begin processing
  GetEntry(entry);

  // count number of entries (=events) ...
  ++fNumberOfEvents;

  // analsiys code comes here - fill histograms

  FillSimple();

  return kTRUE;
}

void RutherfordEnergy::SlaveTerminate()
{
}

void RutherfordEnergy::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  //  TCanvas *canvas = new TCanvas("cresult","Resistance",0,0,1600,400);
  WriteToFile();
  printf("Number of Events: %i\n", fNumberOfEvents);
  fOutput -> Clear();
}


void RutherfordEnergy::WriteToFile() {
  // finally, store all output
  TString rootFile = file;
  rootFile += ".root";
  
  TFile hfile(rootFile,"RECREATE","test");
  fOutput -> Write();
}


void RutherfordEnergy::FillSimple()
{


  // ----- Detector #3 (S3_64um) -----
  for(int i = 0; i < Nfe3; i++){ 
      int strip = Nsfe3[i];
      double energy = calibrationUpStream.getEnergyCircularStrip(strip, Ef3[i]);
      h.ef3[strip - 1]->Fill(energy, 1);
  }
  
  for(int i = 0; i < Nbe3; i++){
    int strip = Nsbe3[i];
    double energy = calibrationUpStream.getEnergyRadialStrip(strip, Eb3[i]);
    h.eb3[strip - 1]->Fill(energy, 1);
  }
  
  /* // ----- Detector #4 (S3_1000um) -----   */
  for(int i = 0; i < Nfe4; i++){
    int strip = Nsfe4[i];
    double energy = calibrationDownStream.getEnergyCircularStrip(strip, Ef4[i]);
    h.ef4[strip - 1]->Fill(energy, 1);
  }
  
  for(int i = 0; i < Nbe4; i++){
      int strip = Nsbe4[i];
      double energy = calibrationDownStream.getEnergyRadialStrip(strip, Eb4[i]);
      h.eb4[strip - 1]->Fill(energy, 1);
  }

}

