/* Plots all simulated callibration runs on one graph -- adapted from Chris's original codes and doesn't include RooFit parts.*/

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

  TH1F* Peak2615sim = new TH1F("Peak2615sim", "Peak2615sim", nbins, 0, 988);
  TH1F* Peak969sim = new TH1F("Peak969sim", "Peak969sim", nbins, 0, 988);
  TH1F* Peak911sim = new TH1F("Peak911sim", "Peak911sim", nbins, 0, 988);
  TH1F* Peak583sim = new TH1F("Peak583sim", "Peak583sim", nbins, 0, 988);
  TH1F* Peak338sim = new TH1F("Peak338sim", "Peak338sim", nbins, 0, 988);
  TH1F* Peak239sim = new TH1F("Peak239sim", "Peak239sim", nbins, 0, 988);

  TCut cut3sim = "Ener1 > 2605";
  TCut cut4sim = "Ener1 < 2625";
  TCut cut2615sim = cut3sim && cut4sim;
 
  TCut cut5sim = "Ener1 > 959";
  TCut cut6sim = "Ener1 < 979";
  TCut cut969sim = cut5sim && cut6sim;

  TCut cut7sim = "Ener1 > 901";
  TCut cut8sim = "Ener1 < 921";
  TCut cut911sim = cut7sim && cut8sim;

  TCut cut9sim = "Ener1 > 573";
  TCut cut10sim = "Ener1 < 593";
  TCut cut583sim = cut9sim && cut10sim;

  TCut cut11sim = "Ener1 > 323";
  TCut cut12sim = "Ener1 < 353";
  TCut cut338sim = cut11sim && cut12sim;

  TCut cut13sim = "Ener1 > 229";
  TCut cut14sim = "Ener1 < 249";
  TCut cut239sim = cut13sim && cut14sim;
 
  Peak2615sim->SetLineColor(kMagenta);
  Peak969sim->SetLineColor(kCyan);
  Peak911sim->SetLineColor(kSpring);
  Peak583sim->SetLineColor(kYellow);
  Peak338sim->SetLineColor(kOrange+1);
  Peak239sim->SetLineColor(kRed);


  TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);
  t1->Draw("Detector >> Peak2615sim", cut2615sim);
  Double_t normsim2615 = Peak2615sim->GetEntries();
  Peak2615sim->Scale(1/normsim2615);
  Peak2615sim->Draw();
  c3->Update();

  c3->SetGridx();
  c3->SetTickx();
  c3->SetTicky();
  c3->SetLogy();

  TCanvas* c4 = new TCanvas("c4", "c4", 600, 600);
  t1->Draw("Detector >> Peak969sim", cut969sim, "goff");
  Double_t normsim969 = Peak969sim->GetEntries();
  Peak969sim->Scale(1/normsim969);
  Peak969sim->Draw();

  c4->SetGridx();
  c4->SetTickx();
  c4->SetTicky();
  c4->SetLogy();

  /*
  TCanvas* c5 = new TCanvas("c5", "c5", 600, 600);
  t1->Draw("Detector >> Peak911sim", cut911sim, "goff");
  Peak911sim->Draw();

  c5->SetGridx();
  c5->SetTickx();
  c5->SetTicky();
  c5->SetLogy();

  TCanvas* c6 = new TCanvas("c6", "c6", 600, 600);
  t1->Draw("Detector >> Peak583sim", cut583sim, "goff");
  Peak583sim->Draw();

  c6->SetGridx();
  c6->SetTickx();
  c6->SetTicky();
  c6->SetLogy();

  TCanvas* c7 = new TCanvas("c7", "c7", 600, 600);
  t1->Draw("Detector >> Peak338sim", cut338sim, "goff");
  Peak338sim->Draw();
  
  c7->SetGridx();
  c7->SetTickx();
  c7->SetTicky();
  c7->SetLogy();

  TCanvas* c8 = new TCanvas("c8", "c8", 600, 600);
  t1->Draw("Detector >> Peak239sim", cut239sim, "goff");
  Peak239sim->Draw();
  
  c8->SetGridx();
  c8->SetTickx();
  c8->SetTicky();
  c8->SetLogy();
  */
}
