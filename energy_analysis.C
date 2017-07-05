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

  QChain * ch = new QChain("qtree_Energy");
  ch->Add("Production_300959_019_C_p001.root");
  
  //ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3015/calibration_Production_ds3015.list");

  //Defining an Energy histogram
  TH1F* Energy_Hist = new TH1F("Energy_Hist", "Energy_Hist", 1000, 0, 3000);

  //Defining individual peak histograms to be filled with cut energy
  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, 0, 3000);
  TH1F* Peak969 = new TH1F("Peak969", "Peak969", nbins, 0, 3000);
  TH1F* Peak911 = new TH1F("Peak911", "Peak911", nbins, 0, 3000);
  TH1F* Peak583 = new TH1F("Peak583", "Peak583", nbins, 0, 3000);
  TH1F* Peak338 = new TH1F("Peak338", "Peak338", nbins, 0, 3000);
  TH1F* Peak239 = new TH1F("Peak239", "Peak239", nbins, 0, 3000);

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
  
  TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TPaveText *t = new TPaveText(0.7,0.9, 0.3, 1.0, "brNDC");
  t->AddText("Energy Histogram");
  t->SetTextSize(.05);
  t->SetFillColor(0);
  t->SetBorderSize(0);

  //Filling my energy histogram with "Energy" values from the data
  ch->Draw("Energy >> Energy_Hist");
  t->Draw("SAME");

  Energy_Hist->GetXaxis()->SetTitle("Energy");
  Energy_Hist->GetXaxis()->SetRangeUser(0,3000);
  Energy_Hist->GetXaxis()->CenterTitle();
  
  Energy_Hist->GetYaxis()->SetTitle("Counts");
  Energy_Hist->GetYaxis()->SetRangeUser(0.1,1000);
  Energy_Hist->GetYaxis()->CenterTitle();

  TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetLegendBorderSize(1);
  gStyle->SetLegendFillColor(0);

  TPaveText *pt = new TPaveText(0.7,0.9, 0.3, 1.0, "brNDC");
  pt->AddText("Peak Energies");
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
  
  //Filling peak histograms with Channels that have been altered by cut energy
  ch->Draw("Energy >> Peak2615", cut2615);
  ch->Draw("Energy >> Peak969", cut969);
  ch->Draw("Energy >> Peak911", cut911);
  ch->Draw("Energy >> Peak583", cut583);
  ch->Draw("Energy >> Peak338", cut338);
  ch->Draw("Energy >> Peak239", cut239);

  Peak338->SetLineColor(kAzure);
  Peak2615->SetLineColor(kSpring);
  Peak969->SetLineColor(kMagenta);
  Peak911->SetLineColor(kOrange);
  Peak583->SetLineColor(kRed);
  Peak239->SetLineColor(kCyan);

  Peak2615->Draw();
  Peak969->Draw("SAME");
  Peak911->Draw("SAME");
  Peak583->Draw("SAME");
  Peak338->Draw("SAME");
  Peak239->Draw("SAME");
  
  pt->Draw("SAME");
  leg->Draw("SAME");
  
  Peak2615->GetXaxis()->SetTitle("Energy");
  Peak2615->GetXaxis()->SetRangeUser(0,3000);
  Peak2615->GetXaxis()->CenterTitle();
  // Peak2615->GetXaxis()->SetNdivisions(1319, kFALSE);
  
  Peak2615->GetYaxis()->SetTitle("Counts");
  Peak2615->GetYaxis()->SetRangeUser(0.1,1000);
  Peak2615->GetYaxis()->CenterTitle();
 
  c3->SetGridx();
  c3->SetTickx();
  c3->SetTicky();
  c3->SetLogy();

}

  /*****************************************************************
  
    Used this code to draw a random histogram as a test
  
  TH1F* h1 = new TH1F("h1","Random Gaussian",100,-2,2);
  h1->FillRandom("gaus",10000);
  h1->Draw();

  *****************************************************************/
