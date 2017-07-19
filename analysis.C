/* This script plots all real CUORE calibration histograms on one canvas with a different color for each peak.

Written by: Katie Melbourne
katherine.melbourne@yale.edu
*/

#include "TTree.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TCut.h"
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

 //Defining individual peak histograms to be filled with cut energy
  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, xmin, 988);
  TH1F* Peak969 = new TH1F("Peak969", "Peak969", nbins, xmin, 988);
  TH1F* Peak911 = new TH1F("Peak911", "Peak911", nbins, xmin, 988);
  TH1F* Peak583 = new TH1F("Peak583", "Peak583", nbins, xmin, 988);
  TH1F* Peak338 = new TH1F("Peak338", "Peak338", nbins, xmin, 988);
  TH1F* Peak239 = new TH1F("Peak239", "Peak239", nbins, xmin, 988);
  
  //Applying cuts on Energy to separate each peak
  TCut basecut = "QNDBDAnalysisBaseCut";
  
  TCut cut3 = "QNDBDOfficialEnergy > 2605";
  TCut cut4 = "QNDBDOfficialEnergy < 2625";
  TCut cut2615 = cut3 && cut4 && basecut;

  TCut cut5 = "QNDBDOfficialEnergy > 959";
  TCut cut6 = "QNDBDOfficialEnergy < 979";
  TCut cut969 = cut5 && cut6 && basecut;

  TCut cut7 = "QNDBDOfficialEnergy > 901";
  TCut cut8 = "QNDBDOfficialEnergy < 921";
  TCut cut911 = cut7 && cut8 && basecut;

  TCut cut9 = "QNDBDOfficialEnergy > 573";
  TCut cut10 = "QNDBDOfficialEnergy < 593";
  TCut cut583 = cut9 && cut10 && basecut;

  TCut cut11 = "QNDBDOfficialEnergy > 323";
  TCut cut12 = "QNDBDOfficialEnergy < 353";
  TCut cut338 = cut11 && cut12 && basecut;

  TCut cut13 = "QNDBDOfficialEnergy > 229";
  TCut cut14 = "QNDBDOfficialEnergy < 249";
  TCut cut239 = cut13 && cut14 && basecut;

  TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);

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

  //Filling peak histograms with Channels that have been altered by cut energy
  ch->Draw("Channel >> Peak2615", cut2615);
  ch->Draw("Channel >> Peak969", cut969);
  ch->Draw("Channel >> Peak911", cut911);
  ch->Draw("Channel >> Peak583", cut583);
  ch->Draw("Channel >> Peak338", cut338);
  ch->Draw("Channel >> Peak239", cut239);

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

}
