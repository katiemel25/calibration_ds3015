/*
  This script plots all real CUORE calibration histograms on MULTIPLE canvases with a different color and separate graph for each peak.

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
  int nbins = 988;
  int xmin = 0;
  int xmax = 988;

  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  //Single-tower file for code testing
  /*
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3015/calibration_Production_ds3015_tower019.list");
  */
  
  //Defining individual peak histograms to be filled with cut energy
  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, xmin, 988);
  TH1F* Peak969 = new TH1F("Peak969", "Peak969", nbins, xmin, 988);
  TH1F* Peak911 = new TH1F("Peak911", "Peak911", nbins, xmin, 988);
  TH1F* Peak583 = new TH1F("Peak583", "Peak583", nbins, xmin, 988);
  TH1F* Peak338 = new TH1F("Peak338", "Peak338", nbins, xmin, 988);
  TH1F* Peak239 = new TH1F("Peak239", "Peak239", nbins, xmin, 988);

  TCut("Filter_RejectBadIntervals");
  TCut("IsSignal");
  TCut("Filter_NumberofPulses==1");
  
  //Applying cuts on Energy to separate each peak
  TCut cut3 = "Energy > 2605";
  TCut cut4 = "Energy < 2625";
  TCut cut2615 = cut3 && cut4;

  TCut cut5 = "Energy > 959";
  TCut cut6 = "Energy < 979";
  TCut cut969 = cut5 && cut6;

  TCut cut7 = "Energy > 901";
  TCut cut8 = "Energy < 921";
  TCut cut911 = cut7 && cut8;

  TCut cut9 = "Energy > 573";
  TCut cut10 = "Energy < 593";
  TCut cut583 = cut9 && cut10;

  TCut cut11 = "Energy > 323";
  TCut cut12 = "Energy < 353";
  TCut cut338 = cut11 && cut12;

  TCut cut13 = "Energy > 229";
  TCut cut14 = "Energy < 249";
  TCut cut239 = cut13 && cut14;

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

  Peak338->SetLineColor(kAzure);
  Peak2615->SetLineColor(kSpring);
  Peak969->SetLineColor(kMagenta);
  Peak911->SetLineColor(kOrange);
  Peak583->SetLineColor(kRed);
  Peak239->SetLineColor(kCyan);

  TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);
  ch->Draw("Channel >> Peak2615", cut2615);
  Peak2615->Draw();
  pt->Draw();

  Peak2615->GetXaxis()->SetTitle("Channel");
  Peak2615->GetXaxis()->SetRangeUser(0,988);
  // Peak2615->GetXaxis()->CenterTitle();
  Peak2615->GetXaxis()->SetNdivisions(1319, kFALSE);
  
  Peak2615->GetYaxis()->SetTitle("Counts");
  Peak2615->GetYaxis()->SetRangeUser(0.1,10000);
  // Peak2615->GetYaxis()->CenterTitle();

  c3->SetGridx();
  c3->SetTickx();
  c3->SetTicky();
  c3->SetLogy();

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

}
