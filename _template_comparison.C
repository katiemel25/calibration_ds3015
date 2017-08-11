/*
  This script was developed on ulite to compare CUORE calibration simulations to real calibration data. I adapted sample simulation code provided by Chris Davis to plot a histogram for each individual energy peak, 2615, 969, 911, 583, 338, and 239 keV. The simulation was created for June calibration runs (June 6, 2017), therefore, I adjusted the real calibration data to remove anything that happened before the month of June. I also applied the basic analysis cuts to the real data (as commented below) before plotting.

  This particular version of the code contains residuals showing the difference between simulated and real data for each of the 988 channels.

  The function in this script needs "Time" as the input, referring to the number of seconds the simulation ran. As the simulation was written to demonstrate events over 10 days, the necessary function input in this case is 864000.

  To run:
  Launch root
  ".L real_sim_combo.C"
  "plot_peaks(Time)"

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

void _plotname_()
{
  //10 days of events

  //defining repeatedly used variables
  int nbins = 988;
  int xmin = 1;
  int xmax = 989;
  int columns = 1304;
  //double ymax = 1000;
  //double ymin = 0.1;

  //reading June 2017 calibration simulations
  TFile* f1 = new TFile("06Jun2017_g4cuore.root");
  TTree* t1 = (TTree*)f1->Get("outTree");

  //reading all unblinded calibration data from data set 3018 (May and June)
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  //creating empty simulation histograms for each peak
  TH1F* Peak2615sim = new TH1F("Peak2615sim", "Peak2615sim", nbins, xmin, xmax);

  //creating empty real data histograms for each peak
  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, xmin, xmax);

  //creating empty residual histograms for each peak
  TH1F* residuals_2615 = new TH1F("residuals_2615", "residuals_2615", nbins, xmin, xmax);

  //cut for "IsSignal", "Number of pulses==1", and "RejectBadIntervals"
  TCut basecut = "QNDBDAnalysisBaseCut";
  //cut to exclude all real calibration runs that occurred before June
  TCut runcut = "Run > 301113";

  //cuts to the simulated data energies
  TCut cut3sim = "Ener1 > 2605";
  TCut cut4sim = "Ener1 < 2625";
  TCut cut2615sim = cut3sim && cut4sim;

  //cuts to the real data energies
  TCut cut3 = "QNDBDOfficialEnergy > 2605";
  TCut cut4 = "QNDBDOfficialEnergy < 2625";
  TCut cut2615 = cut3 && cut4 && basecut && runcut;

  //filling histrograms with cut data
  ch->Draw("Channel >> Peak2615", cut2615);
  t1->Draw("Detector >> Peak2615sim", cut2615sim, "goff");

  //scaling simulated data to Peak Events per Day per Channel
  //Time is called in function, and in this case is 864000 sec (10 days)
  Double_t Time = 864000;
  Peak2615sim->Scale(1.0 / (Time / 86400.0));

  //scaling real data to Peak Events per Day per Channel
  //calculated using code in runtime.C and adding up only runs from June
  Double_t runtime = 231143;
  Peak2615->Scale(1.0 / (runtime / 86400.0));
  
  //setting basic style preferences 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetLegendBorderSize(1);
  gStyle->SetLegendFillColor(0);

  //creating unique titles for each graph for each peak
  TPaveText *t2615 = new TPaveText(0.309,0.938, 0.691, 0.995, "brNDC");
  t2615->AddText("Data and Simulation: 2615 keV peak Tower _tower_number_");
  t2615->SetTextFont(63);
  t2615->SetTextSizePixels(18);
  t2615->SetFillColor(0);
  t2615->SetBorderSize(0);

  //creating a unique legend for each graph for each peak
  TLegend *l2615 = new TLegend(0.685,0.174,0.887,0.307);
  l2615->AddEntry(Peak2615sim,"Simulated Data");
  l2615->AddEntry(Peak2615, "Data Set 3018 Unblinded");
  l2615->SetTextSize(0.02083);
 
  Float_t ymax2615 = Peak2615->GetMaximum();

  //creating each graph individually on canvases 3-8
  
  TCanvas* c3 = new TCanvas("c3", "c3", 1000, 600);
  c3->cd();
  c3->SetLogy();

  Peak2615->GetXaxis()->SetLabelFont(63);
  Peak2615->GetXaxis()->SetLabelSize(14);
  Peak2615->GetXaxis()->SetRangeUser(_xstart_,_xend_);
  Peak2615->GetXaxis()->SetNdivisions(columns,kFALSE);
  Peak2615->GetXaxis()->SetTickLength(0.05);
  Peak2615->GetYaxis()->SetTitle("Events per Day per Channel");
  Peak2615->GetYaxis()->SetRangeUser(0.2, ymax2615+100);
  Peak2615->GetYaxis()->SetTitleFont(63);
  Peak2615->GetYaxis()->SetTitleSize(14);
  Peak2615->GetYaxis()->SetTitleOffset(1);
  Peak2615->GetYaxis()->SetLabelFont(63);
  Peak2615->GetYaxis()->SetLabelSize(14);

  Peak2615->Draw();
  Peak2615->SetLineColor(kRed-7);
  Peak2615sim->Draw("SAME");
  Peak2615sim->SetLineColor(kBlack);

  t2615->Draw();
  l2615->Draw();

  c3->SaveAs("../graphs/comparison_by_tower/_plotname_.pdf");
 
}
