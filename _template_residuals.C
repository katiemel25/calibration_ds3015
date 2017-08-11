/*
 This script contains the peak_residuals() function, which creates a graph with the residuals for each peak in a separate color.

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
  double ymax = 2;
  double ymin = -2;
  int columns = 1304;

  //reading June 2017 calibration simulations
  TFile* f1 = new TFile("06Jun2017_g4cuore.root");
  TTree* t1 = (TTree*)f1->Get("outTree");

  //reading all unblinded calibration data from data set 3018 (May and June)
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

   //creating empty simulation histograms for each peak
  TH1F* Peak2615sim = new TH1F("Peak2615sim", "Peak2615sim", nbins, xmin, xmax);
  TH1F* Peak969sim = new TH1F("Peak969sim", "Peak969sim", nbins, xmin, xmax);
  TH1F* Peak911sim = new TH1F("Peak911sim", "Peak911sim", nbins, xmin, xmax);
  TH1F* Peak583sim = new TH1F("Peak583sim", "Peak583sim", nbins, xmin, xmax);
  TH1F* Peak338sim = new TH1F("Peak338sim", "Peak338sim", nbins, xmin, xmax);
  TH1F* Peak239sim = new TH1F("Peak239sim", "Peak239sim", nbins, xmin, xmax);

  //creating empty real data histograms for each peak
  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, xmin, xmax);
  TH1F* Peak969 = new TH1F("Peak969", "Peak969", nbins, xmin, xmax);
  TH1F* Peak911 = new TH1F("Peak911", "Peak911", nbins, xmin, xmax);
  TH1F* Peak583 = new TH1F("Peak583", "Peak583", nbins, xmin, xmax);
  TH1F* Peak338 = new TH1F("Peak338", "Peak338", nbins, xmin, xmax);
  TH1F* Peak239 = new TH1F("Peak239", "Peak239", nbins, xmin, xmax);

  //creating empty residual histograms for each peak
  TH1F* residuals_2615 = new TH1F("residuals_2615", "residuals_2615", nbins, xmin, xmax);
  TH1F* residuals_969 = new TH1F("residuals_969", "residuals_969", nbins, xmin, xmax);
  TH1F* residuals_911 = new TH1F("residuals_911", "residuals_911", nbins, xmin, xmax);
  TH1F* residuals_583 = new TH1F("residuals_583", "residuals_583", nbins, xmin, xmax);
  TH1F* residuals_338 = new TH1F("residuals_338", "residuals_338", nbins, xmin, xmax);
  TH1F* residuals_239 = new TH1F("residuals_239", "residuals_239", nbins, xmin, xmax);
  
  //cut for "IsSignal", "Number of pulses==1", and "RejectBadIntervals"
  TCut basecut = "QNDBDAnalysisBaseCut";
  //cut to exclude all real calibration runs that occurred before June
  TCut runcut = "Run > 301113";

  //cuts to the simulated data energies
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

  //cuts to the real data energies
  TCut cut3 = "QNDBDOfficialEnergy > 2605";
  TCut cut4 = "QNDBDOfficialEnergy < 2625";
  TCut cut2615 = cut3 && cut4 && basecut && runcut;

  TCut cut5 = "QNDBDOfficialEnergy > 959";
  TCut cut6 = "QNDBDOfficialEnergy < 979";
  TCut cut969 = cut5 && cut6 && basecut && runcut;

  TCut cut7 = "QNDBDOfficialEnergy > 901";
  TCut cut8 = "QNDBDOfficialEnergy < 921";
  TCut cut911 = cut7 && cut8 && basecut && runcut;

  TCut cut9 = "QNDBDOfficialEnergy > 573";
  TCut cut10 = "QNDBDOfficialEnergy < 593";
  TCut cut583 = cut9 && cut10 && basecut && runcut;

  TCut cut11 = "QNDBDOfficialEnergy > 323";
  TCut cut12 = "QNDBDOfficialEnergy < 353";
  TCut cut338 = cut11 && cut12 && basecut && runcut;

  TCut cut13 = "QNDBDOfficialEnergy > 229";
  TCut cut14 = "QNDBDOfficialEnergy < 249";
  TCut cut239 = cut13 && cut14 && basecut && runcut;
  
  //filling histrograms with cut data
  ch->Draw("Channel >> Peak2615", cut2615);
  t1->Draw("Detector >> Peak2615sim", cut2615sim);
  ch->Draw("Channel >> Peak969", cut969);
  t1->Draw("Detector >> Peak969sim", cut969sim);
  ch->Draw("Channel >> Peak911", cut911);
  t1->Draw("Detector >> Peak911sim", cut911sim);
  ch->Draw("Channel >> Peak583", cut583);
  t1->Draw("Detector >> Peak583sim", cut583sim);
  ch->Draw("Channel >> Peak338", cut338);
  t1->Draw("Detector >> Peak338sim", cut338sim);
  ch->Draw("Channel >> Peak239", cut239);
  t1->Draw("Detector >> Peak239sim", cut239sim);
  
  //scaling simulated data to Peak Events per Day per Channel
  //Time is called in function, and in this case is 864000 sec (10 days)
  Double_t Time = 864000;
  Peak2615sim->Scale(1.0 / (Time / 86400.0));
  Peak969sim->Scale(1.0 / (Time / 86400.0));
  Peak911sim->Scale(1.0 / (Time / 86400.0));
  Peak583sim->Scale(1.0 / (Time / 86400.0));
  Peak338sim->Scale(1.0 / (Time / 86400.0));
  Peak239sim->Scale(1.0 / (Time / 86400.0));

  //scaling real data to Peak Events per Day per Channel
  //calculated using code in runtime.C and adding up only runs from June
  Double_t runtime = 231143;
  Peak2615->Scale(1.0 / (runtime / 86400.0));
  Peak969->Scale(1.0 / (runtime / 86400.0));
  Peak911->Scale(1.0 / (runtime / 86400.0));
  Peak583->Scale(1.0 / (runtime / 86400.0));
  Peak338->Scale(1.0 / (runtime / 86400.0));
  Peak239->Scale(1.0 / (runtime / 86400.0));

  //setting basic style preferences 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetLegendBorderSize(1);
  gStyle->SetLegendFillColor(0);

  //creating unique titles for each graph for each peak
  TPaveText *t2615 = new TPaveText(0.309,0.938, 0.691, 0.995, "brNDC");
  t2615->AddText("Tower tower_number");
  t2615->SetTextFont(63);
  t2615->SetTextSizePixels(18);
  t2615->SetFillColor(0);
  t2615->SetBorderSize(0);

  //creating a unique legend for each graph for each peak
  TLegend *l2615 = new TLegend(0.904,0.117,0.998,0.316);
  l2615->AddEntry(residuals_2615,"2615 keV", "P");
  l2615->AddEntry(residuals_969, "969 keV", "P");
  l2615->AddEntry(residuals_911,"911 keV", "P");
  l2615->AddEntry(residuals_583, "583 keV", "P");
  l2615->AddEntry(residuals_338,"338 keV", "P");
  l2615->AddEntry(residuals_239, "239 keV", "P");
  l2615->SetTextSize(0.025);
  
  TCanvas* c3 = new TCanvas("c3", "c3", 1000, 700);
  c3->cd();

  residuals_2615->GetXaxis()->SetLabelFont(63);
  residuals_2615->GetXaxis()->SetLabelSize(14);
  residuals_2615->GetXaxis()->SetTitle("Channel");
  residuals_2615->GetXaxis()->SetRangeUser(_xstart_,_xend_);
  residuals_2615->GetXaxis()->SetNdivisions(columns, kFALSE);
  residuals_2615->GetXaxis()->SetTitleFont(63);
  residuals_2615->GetXaxis()->SetTitleSize(14);
  residuals_2615->GetXaxis()->SetTitleOffset(1);
  residuals_2615->GetYaxis()->SetTitle("(Simulation-Data)/Data");
  residuals_2615->GetYaxis()->SetTitleFont(63);
  residuals_2615->GetYaxis()->SetTitleSize(14);
  residuals_2615->GetYaxis()->SetTitleOffset(1);
  residuals_2615->GetYaxis()->SetLabelFont(63);
  residuals_2615->GetYaxis()->SetLabelSize(14);
  residuals_2615->GetYaxis()->SetRangeUser(ymin, ymax);
  
 for (Int_t i = 1; i <= nbins; i++) {
    if (Peak2615->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak2615sim->GetBinContent(i) - Peak2615->GetBinContent(i)) / Peak2615->GetBinContent(i);
      }
    residuals_2615->SetBinContent(i, diff);
  }

  residuals_2615->SetMarkerColor(kRed-7);
  residuals_2615->Draw("P");

 for (Int_t i = 1; i <= nbins; i++) {
    if (Peak969->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak969sim->GetBinContent(i) - Peak969->GetBinContent(i)) / Peak969->GetBinContent(i);
      }
    residuals_969->SetBinContent(i, diff);
 }

  residuals_969->SetMarkerSize(2);
  residuals_969->SetMarkerColor(kViolet-4);
  residuals_969->Draw("SAME P");
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak911->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak911sim->GetBinContent(i) - Peak911->GetBinContent(i)) / Peak911->GetBinContent(i);
      }
    residuals_911->SetBinContent(i, diff);
  }

  residuals_911->SetMarkerSize(5);
  residuals_911->SetMarkerColor(kAzure-3);
  residuals_911->Draw("SAME P");
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak583->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak583sim->GetBinContent(i) - Peak583->GetBinContent(i)) / Peak583->GetBinContent(i);
      }
    residuals_583->SetBinContent(i, diff);
  }

  residuals_583->SetMarkerSize(5);
  residuals_583->SetMarkerColor(kCyan-3);
  residuals_583->Draw("SAME P");
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak338->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak338sim->GetBinContent(i) - Peak338->GetBinContent(i)) / Peak338->GetBinContent(i);
      }
    residuals_338->SetBinContent(i, diff);
  }

  residuals_338->SetMarkerSize(5);
  residuals_338->SetMarkerColor(kGreen-3);
  residuals_338->Draw("SAME P");
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak239->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak239sim->GetBinContent(i) - Peak239->GetBinContent(i)) / Peak239->GetBinContent(i);
      }
    residuals_239->SetBinContent(i, diff);
  }

  residuals_239->SetMarkerSize(5);
  residuals_239->SetMarkerColor(kOrange-3);
  residuals_239->Draw("SAME P");

  t2615->Draw("SAME");
  l2615->Draw("SAME");
  
  c3->SaveAs("../graphs/residuals_by_tower/_plotname__sim-data.pdf");
  
}


