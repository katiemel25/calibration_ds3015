//Used to test simulation and real data comparison one peak at a time

#ifndef __CINT__
#include "RooGlobalFunc.h"
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

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "TAxis.h"

void plot_peaks()
{

  int nbins = 988;
  int xmin = 0;
  int xmax = 988;

  TFile* f1 = new TFile("06Jun2017_g4cuore.root");
  TTree* t1 = (TTree*)f1->Get("outTree");
   
  QChain * ch = new QChain("qtree");
  ch->Add("/../../nfs/cuore1/scratch/shared_output/output/ds3018/calibration_Production_ds3018_tower019.list");

  TH1F* Peak2615sim = new TH1F("Peak2615sim", "Peak2615sim", nbins, 0, 988);
  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, xmin, 988);

  TCut cut3sim = "Ener1 > 2605";
  TCut cut4sim = "Ener1 < 2625";
  TCut cut2615sim = cut3sim && cut4sim;

  TCut cut3 = "Energy > 2605";
  TCut cut4 = "Energy < 2625";
  TCut cut2615 = cut3 && cut4;

  t1->Draw("Detector >> Peak2615sim", cut2615sim);
  ch->Draw("Channel >> Peak2615", cut2615);

  Double_t normsim = Peak2615sim->GetEntries();
  Peak2615sim->Scale(1/normsim);

  Double_t norm = Peak2615->GetEntries();
  Peak2615->Scale(1/norm);
  
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetLegendBorderSize(1);
  gStyle->SetLegendFillColor(0);

  TPaveText *pt = new TPaveText(0.7,0.9, 0.3, 1.0, "brNDC");
  pt->AddText("Calibration Data");
  pt->SetTextSize(.05);
  pt->SetFillColor(0);
  pt->SetBorderSize(0);
  
  TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);
  Peak2615sim->Draw();
  Peak2615sim->SetLineColor(kBlack);

  Peak2615->Draw("same");
  Peak2615->SetLineColor(kMagenta);
  pt->Draw("same");
  c3->Update();
  
  Peak2615->GetXaxis()->SetTitle("Channel");
  Peak2615->GetXaxis()->SetRangeUser(0,988);
  Peak2615->GetXaxis()->SetNdivisions(1319, kFALSE);
  
  Peak2615->GetYaxis()->SetTitle("Counts");
  Peak2615->GetYaxis()->SetRangeUser(0.1,10000);
  
  c3->SetGridx();
  c3->SetTickx();
  c3->SetTicky();
  c3->SetLogy();

  c3->cd();
}
