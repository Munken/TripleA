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
#include <TCanvas.h>
#include "EnergyCalibration.h"
#include "DownStreamCalibration.h"
#include "UpstreamCalibration.h"
#include "SquareAngleCalculator.h"
#include <TF1.h>
#include "LabToCM.h"
#include <TProfile.h>

using namespace std;
using namespace constants;

UInt_t fNumberOfEvents;
char* file;
const int cutoff = 100;

EnergyCalibration* AngleEnergy2D::calibrationDownStream = //new EnergyCalibration(EnergyCalibration::CAL4_PATH);
new DownStreamDeadCalibration(EnergyCalibration::CAL4_PATH, EnergyCalibration::HE4_RANGE, false);

EnergyCalibration* AngleEnergy2D::calibrationUpStream = //new EnergyCalibration(EnergyCalibration::CAL3_PATH);
new UpStreamDeadCalibration(EnergyCalibration::CAL3_PATH, EnergyCalibration::HE4_RANGE, false);

EnergyCalibration* AngleEnergy2D::square1EnergyCalibration = new EnergyCalibration(EnergyCalibration::CAL1_PATH, 16);
EnergyCalibration* AngleEnergy2D::square2EnergyCalibration = new EnergyCalibration(EnergyCalibration::CAL2_PATH, 16);


CircularAngleCalculator AngleEnergy2D::frontAngleCalculator = UpstreamAngleCalculator();
CircularAngleCalculator AngleEnergy2D::backAngleCalculator = DownStreamAngleCalculator();
AngleCalculator* AngleEnergy2D::square1AngleCalc = new SquareAngleCalculator(32, 0,0);
AngleCalculator* AngleEnergy2D::square2AngleCalc = new SquareAngleCalculator(-38, 0,0);



AngleEnergy2D::AngleEnergy2D(char* out, char* title, double beamEnergy) : 
    labHist("LAB", title, 100, 0, 3.14, 4000, 400, 9000),
    cmPHist("CMP", title, 100, 0, 3.14, 4000, 400, 9000),
    cmAHist("CMA", title, 100, 0, 3.14, 4000, 400, 9000),
    cmATransformer(new LabToCM(beamEnergy, LabToCM::ALPHA_MASS)),
    cmPTransformer(new LabToCM(beamEnergy, LabToCM::PROTON_MASS)),
    beamEnergy(beamEnergy)
{
    file = out;
}

void AngleEnergy2D::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
    fNumberOfEvents = 0;
  //file = GetOption();

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

    
    /// ---- Detector # 1
    for (int i = 0; i < Nfe1; i++) {
        int frontStrip = Nsfe1[i];
        double energy = square1EnergyCalibration -> getEnergyFrontStrip(frontStrip, Ef1[i]);
        int backStrip = findMatchingBackStrip(energy);
        if (backStrip == -1) continue;

        double angle = square1AngleCalc -> getPolar(frontStrip, backStrip);

        FillHistogram(energy, angle);
    }

    /// ---- Detector # 2
    /*for (int i = 0; i < Nfe2; i++) {
    int strip = Nsfe2[i];
    double energy = square2EnergyCalibration -> getEnergyFrontStrip(strip, Ef2[i]);
    double angle = square2AngleCalc -> getPolar(strip);

    FillHistogram(energy, angle);
    }*/

  //// ----- Detector #3 (S3_64um) -----
    for(int i = 0; i < Nfe3; i++){ 
        int strip = Nsfe3[i];
        double energy = calibrationUpStream -> getEnergyFrontStrip(strip, Ef3[i]);
        double angle = frontAngleCalculator.getPolar(strip);

        //if (energy < 1800) continue;

        FillHistogram(energy, angle);
    }

    // /* // ----- Detector #4 (S3_1000um) -----   */
    for(int i = 0; i < Nfe4; i++){
        int strip = Nsfe4[i];
        double energy = calibrationDownStream -> getEnergyFrontStrip(strip, Ef4[i]);
        double angle = backAngleCalculator.getPolar(strip);

        //if (energy < 1800) continue;

        
        FillHistogram(energy, angle);
     }

}

int AngleEnergy2D::findMatchingBackStrip(double energy) {
    
    double minDiff = 50;
    int result = -1;
    for (int i = 0; i < Nbe1; i++) {
        int strip = Nsbe1[i];
        double e2 = square1EnergyCalibration -> getEnergyBackStrip(strip, Eb1[i]);
        double diff = abs(e2 - energy);

        if (diff < minDiff) {
            minDiff = diff;
            result = strip;
        }
    }
    return result;
}

void AngleEnergy2D::FillHistogram(double energy, double angle) {
    labHist.Fill(angle, energy);
    pair<double, double> result = cmPTransformer -> transform(energy, angle);
    cmPHist.Fill(result.second, result.first);

    result = cmATransformer -> transform(energy, angle);
    cmAHist.Fill(result.second, result.first);
}

void AngleEnergy2D::saveResult()
{
    TCanvas labCanvas(file,"Resistance",0,0,1600,1600);
    labHist.Draw();
    labCanvas.SaveAs(Form("%s-LAB.png", file));

    TF1 r("Ruther", "[0]*([1] + [2] + [3]*cos(x))", 0, 3.14);
    r.SetParameter(0, beamEnergy * PROTON_MASS / pow(BORON_11_MASS + PROTON_MASS,2));
    r.SetParameter(1, PROTON_MASS);
    r.SetParameter(2, pow(BORON_11_MASS, 2)/PROTON_MASS);
    r.SetParameter(3, 2*BORON_11_MASS);
    r.Draw("SAME");


    TF1 a("Alpha", "0.5*[0]*(2*[4]*[3]/([2]+[3])^2 + 2 * [5] / ([0] * (1 + [0]/[1])) + 2*sqrt(2*[4]*[3])/([2]+[3])*sqrt(2*[5]/([0]*(1+[0]/[1])))*cos(x))", 0, 3.14);
    a.SetParameter(0, ALPHA_MASS);
    a.SetParameter(1, BERYLLIUM_8_MASS);
    a.SetParameter(2, BORON_11_MASS);
    a.SetParameter(3, PROTON_MASS);
    a.SetParameter(4, beamEnergy);
    a.SetParameter(5, 11./12 * beamEnergy + 8590);
    a.Draw("SAME");
    labCanvas.SaveAs(Form("%s-LABd.png", file));


    TCanvas pCanvas(file,"Resistance",0,0,1600,1600);
    cmPHist.Draw();
    pCanvas.SaveAs(Form("%s-CMp.png", file));

    TCanvas aCanvas(file,"Resistance",0,0,1600,1600);
    cmAHist.Draw();
    aCanvas.SaveAs(Form("%s-CMa.png", file));

}

