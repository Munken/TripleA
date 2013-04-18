#pragma once
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 24 16:11:02 2013 by ROOT version 5.30/01
// from TTree h7/NTUPLE
// found on file: s3_1162_0_m1.root
//////////////////////////////////////////////////////////

#ifndef Rutherford_h
#define Rutherford_h

#include <TChain.h>
#include <TSelector.h>
#include "EnergyCalibration.h"

class Analyzer;
class Selector : public TSelector {

private:
	Analyzer* analyzer;
	static EnergyCalibration* calibrationDownStream;
	static EnergyCalibration* calibrationUpStream;

public :
	UInt_t nEvents;

	TTree          *fChain;   //!pointer to the analyzed TTree or TChain

	// Declaration of leaf types
	Int_t           Clocks;
	Int_t           Ievent;
	Int_t           Charge;
	Int_t           Ntrig;
	Int_t           Nacc;
	Int_t           Nfe1;
	Int_t           Nbe1;
	UChar_t         Nsfe1[16];   //[Nfe1] 
	UChar_t         Nsbe1[16];   //[Nbe1]
	Short_t         Ef1[16];   //[Nfe1]
	Short_t         Eb1[16];   //[Nbe1]
	Int_t           Nft1;
	Int_t           Nbt1;
	UChar_t         Nsft1[100];   //[Nft1]
	UChar_t         Nsbt1[100];   //[Nbt1]
	Short_t         Tf1[100];   //[Nft1]
	Short_t         Tb1[100];   //[Nbt1]

	// Vi tæller oppe fra og ned
	Int_t           Nfe2; // Vertikal
	Int_t           Nbe2; // Horisontal
	UChar_t         Nsfe2[16];   //[Nfe2]
	UChar_t         Nsbe2[16];   //[Nbe2]
	Short_t         Ef2[16];   //[Nfe2]
	Short_t         Eb2[16];   //[Nbe2]
	Int_t           Nft2;
	Int_t           Nbt2;
	UChar_t         Nsft2[100];   //[Nft2] 
	UChar_t         Nsbt2[100];   //[Nbt2]
	Short_t         Tf2[100];   //[Nft2]
	Short_t         Tb2[100];   //[Nbt2]

	//Den tynde
	Int_t           Nfe3; // Antal cirkel strips ramt. 
	Int_t           Nbe3; // Antal radiale strips ramt.
	UChar_t         Nsfe3[24];   //Strip nummeret ramt
	UChar_t         Nsbe3[32];    
	Short_t         Ef3[24];   // Kanalnummeret for den ramte
	double			cEf3[24];
	Short_t         Eb3[32];
	double			cEb3[24];
	Int_t           Nft3;
	Int_t           Nbt3;
	UChar_t         Nsft3[100];   
	UChar_t         Nsbt3[100];   
	Short_t         Tf3[100];   
	Short_t         Tb3[100];   

	// Den tykke
	Int_t           Nfe4;
	Int_t           Nbe4;
	UChar_t         Nsfe4[24];   //[Nfe4]
	UChar_t         Nsbe4[32];   //[Nbe4]
	Short_t         Ef4[24];   //[Nfe4]
	double			cEf4[24];
	Short_t         Eb4[32];   //[Nbe4]
	double			cEb4[24];
	Int_t           Nft4;
	Int_t           Nbt4;
	UChar_t         Nsft4[100];   //[Nft4]
	UChar_t         Nsbt4[100];   //[Nbt4]
	Short_t         Tf4[100];   //[Nft4]
	Short_t         Tb4[100];   //[Nbt4]

	// List of branches
	TBranch        *b_Clocks;   //!
	TBranch        *b_Ievent;   //!
	TBranch        *b_Charge;   //!
	TBranch        *b_Ntrig;   //!
	TBranch        *b_Nacc;   //!
	TBranch        *b_Nfe1;   //!
	TBranch        *b_Nbe1;   //!
	TBranch        *b_Nsfe1;   //!
	TBranch        *b_Nsbe1;   //!
	TBranch        *b_Ef1;   //!
	TBranch        *b_Eb1;   //!
	TBranch        *b_Nft1;   //!
	TBranch        *b_Nbt1;   //!
	TBranch        *b_Nsft1;   //!
	TBranch        *b_Nsbt1;   //!
	TBranch        *b_Tf1;   //!
	TBranch        *b_Tb1;   //!
	TBranch        *b_Nfe2;   //!
	TBranch        *b_Nbe2;   //!
	TBranch        *b_Nsfe2;   //!
	TBranch        *b_Nsbe2;   //!
	TBranch        *b_Ef2;   //!
	TBranch        *b_Eb2;   //!
	TBranch        *b_Nft2;   //!
	TBranch        *b_Nbt2;   //!
	TBranch        *b_Nsft2;   //!
	TBranch        *b_Nsbt2;   //!
	TBranch        *b_Tf2;   //!
	TBranch        *b_Tb2;   //!
	TBranch        *b_Nfe3;   //!
	TBranch        *b_Nbe3;   //!
	TBranch        *b_Nsfe3;   //!
	TBranch        *b_Nsbe3;   //!
	TBranch        *b_Ef3;   //!
	TBranch        *b_Eb3;   //!
	TBranch        *b_Nft3;   //!
	TBranch        *b_Nbt3;   //!
	TBranch        *b_Nsft3;   //!
	TBranch        *b_Nsbt3;   //!
	TBranch        *b_Tf3;   //!
	TBranch        *b_Tb3;   //!
	TBranch        *b_Nfe4;   //!
	TBranch        *b_Nbe4;   //!
	TBranch        *b_Nsfe4;   //!
	TBranch        *b_Nsbe4;   //!
	TBranch        *b_Ef4;   //!
	TBranch        *b_Eb4;   //!
	TBranch        *b_Nft4;   //!
	TBranch        *b_Nbt4;   //!
	TBranch        *b_Nsft4;   //!
	TBranch        *b_Nsbt4;   //!
	TBranch        *b_Tf4;   //!
	TBranch        *b_Tb4;   //!

	Selector(TTree * /*tree*/ =0) {	}
	Selector(Analyzer* a);
	virtual ~Selector() {}

	virtual Int_t   Version() const { return 2; }
	virtual void    Begin(TTree *tree);
	virtual void    SlaveBegin(TTree *tree);
	virtual void    Init(TTree *tree);
	virtual Bool_t  Notify() { return kTRUE;};
	virtual Bool_t  Process(Long64_t entry);
	virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
	virtual void    SetOption(const char *option) { fOption = option; }
	virtual void    SetObject(TObject *obj) { fObject = obj; }
	virtual void    SetInputList(TList *input) { fInput = input; }
	virtual TList  *GetOutputList() const { return fOutput; }
	virtual void    SlaveTerminate();
	virtual void    Terminate();

	void saveResult();
	void calculateCalibratedEnergies();
	void writeCalibratedEnergiesToArrays(EnergyCalibration* upStreamCalibration, EnergyCalibration* downStreamCalibration);

	virtual void    WriteToFile();

	//ClassDef(Rutherford,0);
};

#endif

inline void Selector::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the branch addresses and branch
	// pointers of the tree will be set.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	// Set branch addresses and branch pointers
	if (!tree) return;
	fChain = tree;
	fChain->SetMakeClass(1);

	fChain->SetBranchAddress("Clocks", &Charge, &b_Clocks);
	fChain->SetBranchAddress("Ievent", &Ievent, &b_Ievent);
	fChain->SetBranchAddress("Charge", &Clocks, &b_Charge);
	fChain->SetBranchAddress("Ntrig", &Ntrig, &b_Ntrig);
	fChain->SetBranchAddress("Nacc", &Nacc, &b_Nacc);
	fChain->SetBranchAddress("Nfe1", &Nfe1, &b_Nfe1);
	fChain->SetBranchAddress("Nbe1", &Nbe1, &b_Nbe1);
	fChain->SetBranchAddress("Nsfe1", Nsfe1, &b_Nsfe1);
	fChain->SetBranchAddress("Nsbe1", Nsbe1, &b_Nsbe1);
	fChain->SetBranchAddress("Ef1", Ef1, &b_Ef1);
	fChain->SetBranchAddress("Eb1", Eb1, &b_Eb1);
	fChain->SetBranchAddress("Nft1", &Nft1, &b_Nft1);
	fChain->SetBranchAddress("Nbt1", &Nbt1, &b_Nbt1);
	fChain->SetBranchAddress("Nsft1", Nsft1, &b_Nsft1);
	fChain->SetBranchAddress("Nsbt1", Nsbt1, &b_Nsbt1);
	fChain->SetBranchAddress("Tf1", Tf1, &b_Tf1);
	fChain->SetBranchAddress("Tb1", Tb1, &b_Tb1);
	fChain->SetBranchAddress("Nfe2", &Nfe2, &b_Nfe2);
	fChain->SetBranchAddress("Nbe2", &Nbe2, &b_Nbe2);
	fChain->SetBranchAddress("Nsfe2", Nsfe2, &b_Nsfe2);
	fChain->SetBranchAddress("Nsbe2", Nsbe2, &b_Nsbe2);
	fChain->SetBranchAddress("Ef2", Ef2, &b_Ef2);
	fChain->SetBranchAddress("Eb2", Eb2, &b_Eb2);
	fChain->SetBranchAddress("Nft2", &Nft2, &b_Nft2);
	fChain->SetBranchAddress("Nbt2", &Nbt2, &b_Nbt2);
	fChain->SetBranchAddress("Nsft2", Nsft2, &b_Nsft2);
	fChain->SetBranchAddress("Nsbt2", Nsbt2, &b_Nsbt2);
	fChain->SetBranchAddress("Tf2", Tf2, &b_Tf2);
	fChain->SetBranchAddress("Tb2", Tb2, &b_Tb2);
	fChain->SetBranchAddress("Nfe3", &Nfe3, &b_Nfe3);
	fChain->SetBranchAddress("Nbe3", &Nbe3, &b_Nbe3);
	fChain->SetBranchAddress("Nsfe3", Nsfe3, &b_Nsfe3);
	fChain->SetBranchAddress("Nsbe3", Nsbe3, &b_Nsbe3);
	fChain->SetBranchAddress("Ef3", Ef3, &b_Ef3);
	fChain->SetBranchAddress("Eb3", Eb3, &b_Eb3);
	fChain->SetBranchAddress("Nft3", &Nft3, &b_Nft3);
	fChain->SetBranchAddress("Nbt3", &Nbt3, &b_Nbt3);
	fChain->SetBranchAddress("Nsft3", Nsft3, &b_Nsft3);
	fChain->SetBranchAddress("Nsbt3", Nsbt3, &b_Nsbt3);
	fChain->SetBranchAddress("Tf3", Tf3, &b_Tf3);
	fChain->SetBranchAddress("Tb3", Tb3, &b_Tb3);
	fChain->SetBranchAddress("Nfe4", &Nfe4, &b_Nfe4);
	fChain->SetBranchAddress("Nbe4", &Nbe4, &b_Nbe4);
	fChain->SetBranchAddress("Nsfe4", Nsfe4, &b_Nsfe4);
	fChain->SetBranchAddress("Nsbe4", Nsbe4, &b_Nsbe4);
	fChain->SetBranchAddress("Ef4", Ef4, &b_Ef4);
	fChain->SetBranchAddress("Eb4", Eb4, &b_Eb4);
	fChain->SetBranchAddress("Nft4", &Nft4, &b_Nft4);
	fChain->SetBranchAddress("Nbt4", &Nbt4, &b_Nbt4);
	fChain->SetBranchAddress("Nsft4", Nsft4, &b_Nsft4);
	fChain->SetBranchAddress("Nsbt4", Nsbt4, &b_Nsbt4);
	fChain->SetBranchAddress("Tf4", Tf4, &b_Tf4);
	fChain->SetBranchAddress("Tb4", Tb4, &b_Tb4);
}
