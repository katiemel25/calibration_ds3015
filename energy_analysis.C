/*
  This script is used to look at the energy spectrum (energy versus counts) during specific calibration runs. All peaks are visible.

  Needs to be updated and used for looking at specific channels based on location within the tower as well as examining areas of distinct difference between calibration simulations and real data.
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
  int nbins = 100;
  int xmin = 0;
  int xmax = 4000;

  QChain * ch = new QChain("qtree_Energy");
  ch->Add("/../../nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  //Defining an Energy histogram
  TH1F* Energy_Hist = new TH1F("Energy_Hist", "Energy_Hist", 1000, 0, 3000);

  //Defining individual peak histograms to be filled with cut energy
  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, 0, xmax);
  TH1F* Peak969 = new TH1F("Peak969", "Peak969", nbins, 0, xmax);
  TH1F* Peak911 = new TH1F("Peak911", "Peak911", nbins, 0, xmax);
  TH1F* Peak583 = new TH1F("Peak583", "Peak583", nbins, 0, xmax);
  TH1F* Peak338 = new TH1F("Peak338", "Peak338", nbins, 0, xmax);
  TH1F* Peak239 = new TH1F("Peak239", "Peak239", nbins, 0, xmax);

  //Applying cuts on Energy to separate each peak
  TCut basecut = "QNDBDAnalysisBaseCut";
  //TCut channelcut = "Channel == 937";

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
  
  TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TPaveText *t = new TPaveText(0.7,0.9, 0.3, 1.0, "brNDC");
  t->AddText("Energy Histogram");
  t->SetTextSize(.05);
  t->SetFillColor(0);
  t->SetBorderSize(0);

  //Filling my energy histogram with "Energy" values from the data
  ch->Draw("QNDBDOfficialEnergy >> Energy_Hist");
  t->Draw("SAME");

  Energy_Hist->GetXaxis()->SetTitle("Energy");
  Energy_Hist->GetXaxis()->SetRangeUser(0,4000);
  Energy_Hist->GetXaxis()->CenterTitle();
  
  Energy_Hist->GetYaxis()->SetTitle("Counts");
  Energy_Hist->GetYaxis()->SetRangeUser(0.1,7000);
  Energy_Hist->GetYaxis()->CenterTitle();

}

  /*****************************************************************
  
    Used this code to draw a random histogram as a test
  
  TH1F* h1 = new TH1F("h1","Random Gaussian",100,-2,2);
  h1->FillRandom("gaus",10000);

  ******************************************************************/
