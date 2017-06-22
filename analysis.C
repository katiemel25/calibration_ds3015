/* This script uses CUORE calibration data to create histograms of different peak energy events within each Tellurium crystal.

To run:
>root
>.L analysis.cpp
>plot_AllString_Th232Peaks(Time)

where "Time" is the total time from the simulation (can be grabbed from the Time histogram from the g4cuore output file)

Written by: Katie Melbourne
katherine.melbourne@yale.edu
*/

#ifndef __CINT__
#endif

#include "TROOT.h"
#include "TTree.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TCut.h"
#include <iostream>
#include "THStack.h"
#include "TMath.h"

#include "TAxis.h"

void plot_peaks()
{
  TFile* f1 = new TFile("Production_300959_019_C_p001.root");
  
  TTree* t1 = (TTree*)f1->Get("qtree_Energy");

  TH1F* Energy_Hist = new TH1F("Energy_Hist", "Energy_Hist", 1000, 0, 3000);

  TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);

  gStyle->SetOptStat(0);
  
  t1->Draw("Energy >> Energy_Hist");
  
  Energy_Hist->SetLineColor(kSpring);
  
  Energy_Hist->GetXaxis()->SetTitle("Energy_Hist");
  Energy_Hist->GetXaxis()->SetRangeUser(0,3000);
  Energy_Hist->GetXaxis()->SetNdivisions(1000);
  
  Energy_Hist->GetYaxis()->SetTitle("Counts");
  Energy_Hist->GetYaxis()->SetRangeUser(0,500);
 
  c2->SetGridx();
  c2->SetTickx();
  c2->SetTicky();
  c2->BuildLegend();
  
  /*
    Used this code to draw a random histogram as a test
  
  TH1F* h1 = new TH1F("h1","Random Gaussian",100,-2,2);
  h1->FillRandom("gaus",10000);
  h1->Draw();*/ 
}
