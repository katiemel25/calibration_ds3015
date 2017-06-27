
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
  int nbins = 52;

  QChain * ch19 = new QChain("qtree");
  ch19->Add("/nfs/cuore1/scratch/shared_output/output/ds3015/calibration_Production_ds3015_tower019.list");

  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, 936, 988);

  TCut("Filter_RejectBadIntervals");
  // TCut("IsSignal");
  //TCut("NumberofPulses==1");
  
  TCut cut3 = "Energy > 2605";
  TCut cut4 = "Energy < 2625";
  TCut cut2615 = cut3 && cut4;

  TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  ch19->Draw("Channel >> Peak2615", cut2615);

  Peak2615->Draw();

  Peak2615->GetXaxis()->SetTitle("Channel");
  Peak2615->GetXaxis()->SetRangeUser(936,988);
  Peak2615->GetXaxis()->SetNdivisions(13);
  
  Peak2615->GetYaxis()->SetTitle("Counts");
  Peak2615->GetYaxis()->SetRangeUser(0.1,1000);

  c3->SetLogy();
}
