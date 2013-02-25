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
#include "Rutherford.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

UInt_t fNumberOfEvents;
TString file;
TH1F* ef3[24];
TH1F* ef4[24];
TH1F* eb3[32];
TH1F* eb4[32];
const int cutoff = 100;


void RutherfordEnergy::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

	fNumberOfEvents = 0;
  file = GetOption();

  int n3 = 3000;
  int n4 = 4000;
  for(int i = 0; i<24; i++){ // FRONT
    n3++; n4++;
    
    ef3[i] = new TH1F(Form("h%i",n3),Form("h%i",n3),4096,0.,4096.);
    ef4[i] = new TH1F(Form("h%i",n4),Form("h%i",n4),4096,0.,4096.);
  }

  n3 = 3100; n4 = 4100;
  for(int i = 0; i<32; i++){ // BACK
    n3++; n4++;
    eb3[i] = new TH1F(Form("h%i",n3),Form("h%i",n3),4096,0.,4096.);
    eb4[i] = new TH1F(Form("h%i",n4),Form("h%i",n4),4096,0.,4096.);
  }

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
    if(Ef3[i] > cutoff) ef3[Nsfe3[i]-1]->Fill(Ef3[i],1);
  }
  
  for(int i = 0; i < Nbe3; i++){
    if(Eb3[i] > cutoff) eb3[Nsbe3[i]-1]->Fill(Eb3[i],1);
  }
  
  /* // ----- Detector #4 (S3_1000um) -----   */
  for(int i = 0; i < Nfe4; i++){
    if(Ef4[i] > cutoff) ef4[Nsfe4[i]-1]->Fill(Ef4[i],1);
  }
  
  for(int i = 0; i < Nbe4; i++){
    if(Eb4[i] > cutoff) eb4[Nsbe4[i]-1]->Fill(Eb4[i],1);
  }

}

