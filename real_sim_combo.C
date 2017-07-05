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

void plot_AllString_Th232Peaks(double Time) {

  int nbins = 988;
  int xmin = 0;
  int xmax = 988;

  TFile* f1 = new TFile("/data-mgm/cuore/scratch/simulation_scratch/06Jun2017/06Jun2017_g4cuore.root");
  TTree* t1 = (TTree*)f1->Get("outTree");

   QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3015/calibration_Production_ds3015.list");

  TH1F* Peak2615sim = new TH1F("Peak2615", "Peak2615", nbins, 0, 988);
  TH1F* Peak969sim = new TH1F("Peak969", "Peak969", nbins, 0, 988);
  TH1F* Peak911sim = new TH1F("Peak911", "Peak911", nbins, 0, 988);
  TH1F* Peak583sim = new TH1F("Peak583", "Peak583", nbins, 0, 988);
  TH1F* Peak338sim = new TH1F("Peak338", "Peak338", nbins, 0, 988);
  TH1F* Peak239sim = new TH1F("Peak239", "Peak239", nbins, 0, 988);

  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, xmin, 988);
  TH1F* Peak969 = new TH1F("Peak969", "Peak969", nbins, xmin, 988);
  TH1F* Peak911 = new TH1F("Peak911", "Peak911", nbins, xmin, 988);
  TH1F* Peak583 = new TH1F("Peak583", "Peak583", nbins, xmin, 988);
  TH1F* Peak338 = new TH1F("Peak338", "Peak338", nbins, xmin, 988);
  TH1F* Peak239 = new TH1F("Peak239", "Peak239", nbins, xmin, 988);
  
  TCut cut3 = "Ener1 > 2605";
  TCut cut4 = "Ener1 < 2625";
  TCut cut2615 = cut3 && cut4 && multiplicity;

  TCut cut5 = "Ener1 > 959";
  TCut cut6 = "Ener1 < 979";
  TCut cut969 = cut5 && cut6 && multiplicity;

  TCut cut7 = "Ener1 > 901";
  TCut cut8 = "Ener1 < 921";
  TCut cut911 = cut7 && cut8 && multiplicity;

  TCut cut9 = "Ener1 > 573";
  TCut cut10 = "Ener1 < 593";
  TCut cut583 = cut9 && cut10 && multiplicity;

  TCut cut11 = "Ener1 > 323";
  TCut cut12 = "Ener1 < 353";
  TCut cut338 = cut11 && cut12 && multiplicity;

  TCut cut13 = "Ener1 > 229";
  TCut cut14 = "Ener1 < 249";
  TCut cut239 = cut13 && cut14 && multiplicity;
  
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetLegendBorderSize(1);
  gStyle->SetLegendFillColor(0);

  TPaveText *pt = new TPaveText(0.7,0.9, 0.3, 1.0, "brNDC");
  pt->AddText("Calibration Data");
  pt->SetTextSize(.05);
  pt->SetFillColor(0);
  pt->SetBorderSize(0);

  TLegend *leg = new TLegend(0.1,0.7,0.3,0.5);
  leg->AddEntry(Peak2615,"2615 KeV");
  leg->AddEntry(Peak969,"969 KeV");
  leg->AddEntry(Peak911,"911 KeV");
  leg->AddEntry(Peak583,"583 KeV");
  leg->AddEntry(Peak338,"338 KeV");
  leg->AddEntry(Peak239,"239 KeV");

  /*
  t1->Draw("Detector >> Peak969sim", cut969, "goff");
  t1->Draw("Detector >> Peak911sim", cut911, "goff");
  t1->Draw("Detector >> Peak583sim", cut583, "goff");
  t1->Draw("Detector >> Peak338sim", cut338, "goff");
  t1->Draw("Detector >> Peak239sim", cut239, "goff");
  */
  /***************************************************************/

  Peak2615->SetLineColor(kMagenta);
  Peak969->SetLineColor(kCyan);
  Peak911->SetLineColor(kSpring);
  Peak583->SetLineColor(kYellow);
  Peak338->SetLineColor(kOrange+1);
  Peak239->SetLineColor(kRed);

  Peak2615sim->SetLineColor(kBlack);
  Peak969sim->SetLineColor(kBlack);
  Peak911sim->SetLineColor(kBlack);
  Peak583sim->SetLineColor(kBlack);
  Peak338sim->SetLineColor(kBlack);
  Peak239sim->SetLineColor(kBlack);

  TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);
  ch->Draw("Channel >> Peak2615", cut2615);
  t1->Draw("Detector >> Peak2615sim", cut2615, "goff")
  Peak2615->Draw();
  Peak2615sim->Draw();
  pt->Draw();

  Peak2615->GetXaxis()->SetTitle("Channel");
  Peak2615->GetXaxis()->SetRangeUser(0,988);
  Peak2615->GetXaxis()->SetNdivisions(1319, kFALSE);
  
  Peak2615->GetYaxis()->SetTitle("Counts");
  Peak2615->GetYaxis()->SetRangeUser(0.1,10000);

  c3->SetGridx();
  c3->SetTickx();
  c3->SetTicky();
  c3->SetLogy();
  /*
  TCanvas* c4 = new TCanvas("c4", "c4", 600, 600);
  ch->Draw("Channel >> Peak969", cut969);
  Peak969->Draw();
  pt->Draw();
  
  Peak969->GetXaxis()->SetTitle("Channel");
  Peak969->GetXaxis()->SetRangeUser(0,988);
  // Peak2615->GetXaxis()->CenterTitle();
  Peak969->GetXaxis()->SetNdivisions(1319, kFALSE);
  
  Peak969->GetYaxis()->SetTitle("Counts");
  Peak969->GetYaxis()->SetRangeUser(0.1,10000);
  // Peak2615->GetYaxis()->CenterTitle();

  c4->SetGridx();
  c4->SetTickx();
  c4->SetTicky();
  c4->SetLogy();

  TCanvas* c5 = new TCanvas("c5", "c5", 600, 600);
  ch->Draw("Channel >> Peak911", cut911);
  Peak911->Draw();
  pt->Draw();

  Peak911->GetXaxis()->SetTitle("Channel");
  Peak911->GetXaxis()->SetRangeUser(0,988);
  // Peak2615->GetXaxis()->CenterTitle();
  Peak911->GetXaxis()->SetNdivisions(1319, kFALSE);
  
  Peak911->GetYaxis()->SetTitle("Counts");
  Peak911->GetYaxis()->SetRangeUser(0.1,10000);
  // Peak2615->GetYaxis()->CenterTitle();

  c5->SetGridx();
  c5->SetTickx();
  c5->SetTicky();
  c5->SetLogy();

  TCanvas* c6 = new TCanvas("c6", "c6", 600, 600);
  ch->Draw("Channel >> Peak583", cut583);
  Peak583->Draw();
  pt->Draw();
  
  Peak583->GetXaxis()->SetTitle("Channel");
  Peak583->GetXaxis()->SetRangeUser(0,988);
  // Peak2615->GetXaxis()->CenterTitle();
  Peak583->GetXaxis()->SetNdivisions(1319, kFALSE);
  
  Peak583->GetYaxis()->SetTitle("Counts");
  Peak583->GetYaxis()->SetRangeUser(0.1,10000);
  // Peak2615->GetYaxis()->CenterTitle();

  c6->SetGridx();
  c6->SetTickx();
  c6->SetTicky();
  c6->SetLogy();

  TCanvas* c7 = new TCanvas("c7", "c7", 600, 600);
  ch->Draw("Channel >> Peak338", cut338);
  Peak338->Draw();
  pt->Draw();
  
  Peak338->GetXaxis()->SetTitle("Channel");
  Peak338->GetXaxis()->SetRangeUser(0,988);
  // Peak2615->GetXaxis()->CenterTitle();
  Peak338->GetXaxis()->SetNdivisions(1319, kFALSE);
  
  Peak338->GetYaxis()->SetTitle("Counts");
  Peak338->GetYaxis()->SetRangeUser(0.1,10000);
  // Peak2615->GetYaxis()->CenterTitle();

  c7->SetGridx();
  c7->SetTickx();
  c7->SetTicky();
  c7->SetLogy();

  TCanvas* c8 = new TCanvas("c8", "c8", 600, 600);
  ch->Draw("Channel >> Peak239", cut239);
  Peak239->Draw();
  pt->Draw();

  Peak239->GetXaxis()->SetTitle("Channel");
  Peak239->GetXaxis()->SetRangeUser(0,988);
  // Peak2615->GetXaxis()->CenterTitle();
  Peak239->GetXaxis()->SetNdivisions(1319, kFALSE);
  
  Peak239->GetYaxis()->SetTitle("Counts");
  Peak239->GetYaxis()->SetRangeUser(0.1,10000);
  // Peak2615->GetYaxis()->CenterTitle();

  c8->SetGridx();
  c8->SetTickx();
  c8->SetTicky();
  c8->SetLogy();
  */
}
