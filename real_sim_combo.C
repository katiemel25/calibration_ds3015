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

void plot_peaks(double Time)
{
  //10 days of events

  //defining repeatedly used variables
  int nbins = 988;
  int xmin = 0;
  int xmax = 988;
  //double ymax = 1000;
  //double ymin = 0.1;

  //reading June 2017 calibration simulations
  TFile* f1 = new TFile("06Jun2017_g4cuore.root");
  TTree* t1 = (TTree*)f1->Get("outTree");

  //reading all unblinded calibration data from data set 3018 (May and June)
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  //creating empty simulation histograms for each peak
  TH1F* Peak2615sim = new TH1F("Peak2615sim", "Peak2615sim", nbins, 0, 988);
  TH1F* Peak969sim = new TH1F("Peak969sim", "Peak969sim", nbins, 0, 988);
  TH1F* Peak911sim = new TH1F("Peak911sim", "Peak911sim", nbins, 0, 988);
  TH1F* Peak583sim = new TH1F("Peak583sim", "Peak583sim", nbins, 0, 988);
  TH1F* Peak338sim = new TH1F("Peak338sim", "Peak338sim", nbins, 0, 988);
  TH1F* Peak239sim = new TH1F("Peak239sim", "Peak239sim", nbins, 0, 988);

  //creating empty real data histograms for each peak
  TH1F* Peak2615 = new TH1F("Peak2615", "Peak2615", nbins, xmin, 988);
  TH1F* Peak969 = new TH1F("Peak969", "Peak969", nbins, xmin, 988);
  TH1F* Peak911 = new TH1F("Peak911", "Peak911", nbins, xmin, 988);
  TH1F* Peak583 = new TH1F("Peak583", "Peak583", nbins, xmin, 988);
  TH1F* Peak338 = new TH1F("Peak338", "Peak338", nbins, xmin, 988);
  TH1F* Peak239 = new TH1F("Peak239", "Peak239", nbins, xmin, 988);

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
  t1->Draw("Detector >> Peak2615sim", cut2615sim, "goff");
  ch->Draw("Channel >> Peak969", cut969);
  t1->Draw("Detector >> Peak969sim", cut969sim, "goff");
  ch->Draw("Channel >> Peak911", cut911);
  t1->Draw("Detector >> Peak911sim", cut911sim, "goff");
  ch->Draw("Channel >> Peak583", cut583);
  t1->Draw("Detector >> Peak583sim", cut583sim, "goff");
  ch->Draw("Channel >> Peak338", cut338);
  t1->Draw("Detector >> Peak338sim", cut338sim, "goff");
  ch->Draw("Channel >> Peak239", cut239);
  t1->Draw("Detector >> Peak239sim", cut239sim, "goff");

  //scaling simulated data to Peak Events per Day per Channel
  //Time is called in function, and in this case is 864000 sec (10 days)
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
  t2615->AddText("Data and Simulation: 2615 keV peak");
  t2615->SetTextFont(63);
  t2615->SetTextSizePixels(18);
  t2615->SetFillColor(0);
  t2615->SetBorderSize(0);
  TPaveText *t969 = new TPaveText(0.309,0.938, 0.691, 0.995, "brNDC");
  t969->AddText("Data and Simulation: 969 keV peak");
  t969->SetTextFont(63);
  t969->SetTextSizePixels(18);
  t969->SetFillColor(0);
  t969->SetBorderSize(0);
  TPaveText *t911 = new TPaveText(0.309,0.938, 0.691, 0.995, "brNDC");
  t911->AddText("Data and Simulation: 911 keV peak");
  t911->SetTextFont(63);
  t911->SetTextSizePixels(18);
  t911->SetFillColor(0);
  t911->SetBorderSize(0);
  TPaveText *t583 = new TPaveText(0.309,0.938, 0.691, 0.995, "brNDC");
  t583->AddText("Data and Simulation: 583 keV peak");
  t583->SetTextFont(63);
  t583->SetTextSizePixels(18);
  t583->SetFillColor(0);
  t583->SetBorderSize(0);
  TPaveText *t338 = new TPaveText(0.309,0.938, 0.691, 0.995, "brNDC");
  t338->AddText("Data and Simulation: 338 keV peak");
  t338->SetTextFont(63);
  t338->SetTextSizePixels(18);
  t338->SetFillColor(0);
  t338->SetBorderSize(0);
  TPaveText *t239 = new TPaveText(0.309,0.938, 0.691, 0.995, "brNDC");
  t239->AddText("Data and Simulation: 239 keV peak");
  t239->SetTextFont(63);
  t239->SetTextSizePixels(18);
  t239->SetFillColor(0);
  t239->SetBorderSize(0);

  //creating a unique legend for each graph for each peak
  // TLegend *l2615 = new TLegend(0.687,0.090,0.873,0.251); //legend on comparison graph
  TLegend *l2615 = new TLegend(0.133,0.710,0.281,.0.915);
  l2615->AddEntry(Peak2615sim,"Simulated Data");
  l2615->AddEntry(Peak2615, "Data Set 3018 Unblinded");
  l2615->SetTextSize(0.0526);
  TLegend *l969 = new TLegend(0.687,0.090,0.873,0.251);
  l969->AddEntry(Peak969sim,"Simulated Data");
  l969->AddEntry(Peak969, "Data Set 3018 Unblinded");
  l969->SetTextSize(0.03);
  TLegend *l911 = new TLegend (0.687,0.090,0.873,0.251);
  l911->AddEntry(Peak911sim,"Simulated Data");
  l911->AddEntry(Peak911, "Data Set 3018 Unblinded");
  l911->SetTextSize(0.03);
  TLegend *l583 = new TLegend(0.687,0.090,0.873,0.251);
  l583->AddEntry(Peak583sim,"Simulated Data");
  l583->AddEntry(Peak583, "Data Set 3018 Unblinded");
  l583->SetTextSize(0.03);
  TLegend *l338 = new TLegend(0.687,0.090,0.873,0.251);
  l338->AddEntry(Peak338sim,"Simulated Data");
  l338->AddEntry(Peak338, "Data Set 3018 Unblinded");
  l338->SetTextSize(0.03);
  TLegend* l239 = new TLegend(0.687,0.090,0.873,0.251);
  l239->AddEntry(Peak239sim,"Simulated Data");
  l239->AddEntry(Peak239, "Data Set 3018 Unblinded");
  l239->SetTextSize(0.03);

  Float_t ymax2615 = Peak2615->GetMaximum();

  //creating each graph individually on canvases 3-8
  
  TCanvas* c3 = new TCanvas("c3", "c3", 1000, 600);
  c3->cd();
  TPad *pad1c3 = new TPad("pad1c3", "pad1c3", 0, 0.33, 1, 1);
  TPad *pad2c3 = new TPad("pad2c3", "pad2c3", 0, 0, 1, 0.33);
  pad1c3->SetBottomMargin(0.00001);
  pad1c3->SetBorderMode(0);
  pad1c3->SetLogy();
  pad2c3->SetTopMargin(0.0000001);
  pad2c3->SetBottomMargin(0.2);
  pad2c3->SetBorderMode(0);
  pad1c3->Draw();
  pad2c3->Draw();

  pad1c3->cd();
  Peak2615->GetXaxis()->SetLabelFont(63);
  Peak2615->GetXaxis()->SetLabelSize(14);
  Peak2615->GetXaxis()->SetRangeUser(0,988);
  Peak2615->GetXaxis()->SetNdivisions(1319, kFALSE);
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

  for (int i = 52; i <=nbins; i = i+52)
    {
      TLine *line2615 = new TLine(i,0.2,i,ymax2615+100);
      line2615->SetLineStyle(2);
      line2615->Draw("SAME");
    }

  pad2c3->cd();
  residuals_2615->SetTitle("");
  residuals_2615->GetXaxis()->SetLabelFont(63);
  residuals_2615->GetXaxis()->SetLabelSize(14);
  residuals_2615->GetXaxis()->SetTitle("Channel");
  residuals_2615->GetXaxis()->SetRangeUser(0,988);
  residuals_2615->GetXaxis()->SetNdivisions(1319, kFALSE);
  residuals_2615->GetXaxis()->SetTitleFont(63);
  residuals_2615->GetXaxis()->SetTitleSize(14);
  residuals_2615->GetXaxis()->SetTitleOffset(3);
  residuals_2615->GetYaxis()->SetTitle("(Simulation-Data)/Data");
  residuals_2615->GetYaxis()->SetTitleFont(63);
  residuals_2615->GetYaxis()->SetTitleSize(14);
  residuals_2615->GetYaxis()->SetTitleOffset(1);
  residuals_2615->GetYaxis()->SetLabelFont(63);
  residuals_2615->GetYaxis()->SetLabelSize(14);
  residuals_2615->SetMarkerSize(5);
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak2615->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak2615sim->GetBinContent(i) - Peak2615->GetBinContent(i)) / Peak2615->GetBinContent(i);
      }
    residuals_2615->SetBinContent(i, diff);
  }
  residuals_2615->Draw("P");

  l2615->Draw();

  c3->SaveAs("../graphs/ds3018_updated/real_sim_combo_2615_wlines.pdf");
  
  /*
  TCanvas* c4 = new TCanvas("c4", "c4", 1000, 600);
  c4->cd();
  TPad *pad1c4 = new TPad("pad1c4", "pad1c4", 0, 0.33, 1, 1);
  TPad *pad2c4 = new TPad("pad2c4", "pad2c4", 0, 0, 1, 0.33);
  pad1c4->SetBottomMargin(0.00001);
  pad1c4->SetBorderMode(0);
  pad1c4->SetLogy();
  pad2c4->SetTopMargin(0.0000001);
  pad2c4->SetBottomMargin(0.2);
  pad2c4->SetBorderMode(0);
  pad1c4->Draw();
  pad2c4->Draw();

  pad1c4->cd();
  Peak969->GetXaxis()->SetLabelFont(63);
  Peak969->GetXaxis()->SetLabelSize(14);
  Peak969->GetXaxis()->SetRangeUser(0,988);
  Peak969->GetXaxis()->SetNdivisions(1319, kFALSE);
  Peak969->GetYaxis()->SetTitle("Events per Day per Channel");
  // Peak2615->GetYaxis()->SetRangeUser(ymin, ymax);
  Peak969->GetYaxis()->SetTitleFont(63);
  Peak969->GetYaxis()->SetTitleSize(14);
  Peak969->GetYaxis()->SetTitleOffset(1);
  Peak969->GetYaxis()->SetLabelFont(63);
  Peak969->GetYaxis()->SetLabelSize(14);
  
  Peak969->Draw();
  Peak969->SetLineColor(kViolet-4);
  Peak969sim->Draw("SAME");
  Peak969sim->SetLineColor(kBlack);

  t969->Draw();
  l969->Draw();

  pad2c4->cd();
  residuals_969->SetTitle("");
  residuals_969->GetXaxis()->SetLabelFont(63);
  residuals_969->GetXaxis()->SetLabelSize(14);
  residuals_969->GetXaxis()->SetTitle("Channel");
  residuals_969->GetXaxis()->SetRangeUser(0,988);
  residuals_969->GetXaxis()->SetNdivisions(1319, kFALSE);
  residuals_969->GetXaxis()->SetTitleFont(63);
  residuals_969->GetXaxis()->SetTitleSize(14);
  residuals_969->GetXaxis()->SetTitleOffset(3);
  residuals_969->GetYaxis()->SetTitle("(Simulation-Data)/Data");
  residuals_969->GetYaxis()->SetTitleFont(63);
  residuals_969->GetYaxis()->SetTitleSize(14);
  residuals_969->GetYaxis()->SetTitleOffset(1);
  residuals_969->GetYaxis()->SetLabelFont(63);
  residuals_969->GetYaxis()->SetLabelSize(14);
  residuals_969->SetMarkerSize(5);
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak969->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak969sim->GetBinContent(i) - Peak969->GetBinContent(i)) / Peak969->GetBinContent(i);
      }
    residuals_969->SetBinContent(i, diff);
  }
  residuals_969->Draw("P");

  c4->SaveAs("../graphs/ds3018_updated/real_sim_combo_969.pdf");
  
  TCanvas* c5 = new TCanvas("c5", "c5", 1000, 600);
  c5->cd();
  TPad *pad1c5 = new TPad("pad1c5", "pad1c5", 0, 0.33, 1, 1);
  TPad *pad2c5 = new TPad("pad2c5", "pad2c5", 0, 0, 1, 0.33);
  pad1c5->SetBottomMargin(0.00001);
  pad1c5->SetBorderMode(0);
  pad1c5->SetLogy();
  pad2c5->SetTopMargin(0.0000001);
  pad2c5->SetBottomMargin(0.2);
  pad2c5->SetBorderMode(0);
  pad1c5->Draw();
  pad2c5->Draw();

  pad1c5->cd();
  Peak911->GetXaxis()->SetLabelFont(63);
  Peak911->GetXaxis()->SetLabelSize(14);
  Peak911->GetXaxis()->SetRangeUser(0,988);
  Peak911->GetXaxis()->SetNdivisions(1319, kFALSE);
  Peak911->GetYaxis()->SetTitle("Events per Day per Channel");
  // Peak2615->GetYaxis()->SetRangeUser(ymin, ymax);
  Peak911->GetYaxis()->SetTitleFont(63);
  Peak911->GetYaxis()->SetTitleSize(14);
  Peak911->GetYaxis()->SetTitleOffset(1);
  Peak911->GetYaxis()->SetLabelFont(63);
  Peak911->GetYaxis()->SetLabelSize(14);
  
  Peak911->Draw();
  Peak911->SetLineColor(kAzure-3);
  Peak911sim->Draw("SAME");
  Peak911sim->SetLineColor(kBlack);

  t911->Draw();
  l911->Draw();

  pad2c5->cd();
  residuals_911->SetTitle("");
  residuals_911->GetXaxis()->SetLabelFont(63);
  residuals_911->GetXaxis()->SetLabelSize(14);
  residuals_911->GetXaxis()->SetTitle("Channel");
  residuals_911->GetXaxis()->SetRangeUser(0,988);
  residuals_911->GetXaxis()->SetNdivisions(1319, kFALSE);
  residuals_911->GetXaxis()->SetTitleFont(63);
  residuals_911->GetXaxis()->SetTitleSize(14);
  residuals_911->GetXaxis()->SetTitleOffset(3);
  residuals_911->GetYaxis()->SetTitle("(Simulation-Data)/Data");
  residuals_911->GetYaxis()->SetTitleFont(63);
  residuals_911->GetYaxis()->SetTitleSize(14);
  residuals_911->GetYaxis()->SetTitleOffset(1);
  residuals_911->GetYaxis()->SetLabelFont(63);
  residuals_911->GetYaxis()->SetLabelSize(14);
  residuals_911->SetMarkerSize(5);
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak911->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak911sim->GetBinContent(i) - Peak911->GetBinContent(i)) / Peak911->GetBinContent(i);
      }
    residuals_911->SetBinContent(i, diff);
  }
  residuals_911->Draw("P");

  c5->SaveAs("../graphs/ds3018_updated/real_sim_combo_911.pdf");
  
  TCanvas* c6 = new TCanvas("c6", "c6", 1000, 600);
  c6->cd();
  TPad *pad1c6 = new TPad("pad1c6", "pad1c6", 0, 0.33, 1, 1);
  TPad *pad2c6 = new TPad("pad2c6", "pad2c6", 0, 0, 1, 0.33);
  pad1c6->SetBottomMargin(0.00001);
  pad1c6->SetBorderMode(0);
  pad1c6->SetLogy();
  pad2c6->SetTopMargin(0.0000001);
  pad2c6->SetBottomMargin(0.2);
  pad2c6->SetBorderMode(0);
  pad1c6->Draw();
  pad2c6->Draw();

  pad1c6->cd();
  Peak583->GetXaxis()->SetLabelFont(63);
  Peak583->GetXaxis()->SetLabelSize(14);
  Peak583->GetXaxis()->SetRangeUser(0,988);
  Peak583->GetXaxis()->SetNdivisions(1319, kFALSE);
  Peak583->GetYaxis()->SetTitle("Events per Day per Channel");
  // Peak2615->GetYaxis()->SetRangeUser(ymin, ymax);
  Peak583->GetYaxis()->SetTitleFont(63);
  Peak583->GetYaxis()->SetTitleSize(14);
  Peak583->GetYaxis()->SetTitleOffset(1);
  Peak583->GetYaxis()->SetLabelFont(63);
  Peak583->GetYaxis()->SetLabelSize(14);
  
  Peak583->Draw();
  Peak583->SetLineColor(kCyan-3);
  Peak583sim->Draw("SAME");
  Peak583sim->SetLineColor(kBlack);

  t583->Draw();
  l583->Draw();

  pad2c6->cd();
  residuals_583->SetTitle("");
  residuals_583->GetXaxis()->SetLabelFont(63);
  residuals_583->GetXaxis()->SetLabelSize(14);
  residuals_583->GetXaxis()->SetTitle("Channel");
  residuals_583->GetXaxis()->SetRangeUser(0,988);
  residuals_583->GetXaxis()->SetNdivisions(1319, kFALSE);
  residuals_583->GetXaxis()->SetTitleFont(63);
  residuals_583->GetXaxis()->SetTitleSize(14);
  residuals_583->GetXaxis()->SetTitleOffset(3);
  residuals_583->GetYaxis()->SetTitle("(Simulation-Data)/Data");
  residuals_583->GetYaxis()->SetTitleFont(63);
  residuals_583->GetYaxis()->SetTitleSize(14);
  residuals_583->GetYaxis()->SetTitleOffset(1);
  residuals_583->GetYaxis()->SetLabelFont(63);
  residuals_583->GetYaxis()->SetLabelSize(14);
  residuals_583->SetMarkerSize(5);
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak583->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak583sim->GetBinContent(i) - Peak583->GetBinContent(i)) / Peak583->GetBinContent(i);
      }
    residuals_583->SetBinContent(i, diff);
  }
  residuals_583->Draw("P");

  c6->SaveAs("../graphs/ds3018_updated/real_sim_combo_583.pdf");

  TCanvas* c7 = new TCanvas("c7", "c7", 1000, 600);
  c7->cd();
  TPad *pad1c7 = new TPad("pad1c7", "pad1c7", 0, 0.33, 1, 1);
  TPad *pad2c7 = new TPad("pad2c7", "pad2c7", 0, 0, 1, 0.33);
  pad1c7->SetBottomMargin(0.00001);
  pad1c7->SetBorderMode(0);
  pad1c7->SetLogy();
  pad2c7->SetTopMargin(0.0000001);
  pad2c7->SetBottomMargin(0.2);
  pad2c7->SetBorderMode(0);
  pad1c7->Draw();
  pad2c7->Draw();

  pad1c7->cd();
  Peak338->GetXaxis()->SetLabelFont(63);
  Peak338->GetXaxis()->SetLabelSize(14);
  Peak338->GetXaxis()->SetRangeUser(0,988);
  Peak338->GetXaxis()->SetNdivisions(1319, kFALSE);
  Peak338->GetYaxis()->SetTitle("Events per Day per Channel");
  // Peak2615->GetYaxis()->SetRangeUser(ymin, ymax);
  Peak338->GetYaxis()->SetTitleFont(63);
  Peak338->GetYaxis()->SetTitleSize(14);
  Peak338->GetYaxis()->SetTitleOffset(1);
  Peak338->GetYaxis()->SetLabelFont(63);
  Peak338->GetYaxis()->SetLabelSize(14);
  
  Peak338->Draw();
  Peak338->SetLineColor(kGreen-3);
  Peak338sim->Draw("SAME");
  Peak338sim->SetLineColor(kBlack);

  t338->Draw();
  l338->Draw();

  pad2c7->cd();
  residuals_338->SetTitle("");
  residuals_338->GetXaxis()->SetLabelFont(63);
  residuals_338->GetXaxis()->SetLabelSize(14);
  residuals_338->GetXaxis()->SetTitle("Channel");
  residuals_338->GetXaxis()->SetRangeUser(0,988);
  residuals_338->GetXaxis()->SetNdivisions(1319, kFALSE);
  residuals_338->GetXaxis()->SetTitleFont(63);
  residuals_338->GetXaxis()->SetTitleSize(14);
  residuals_338->GetXaxis()->SetTitleOffset(3);
  residuals_338->GetYaxis()->SetTitle("(Simulation-Data)/Data");
  residuals_338->GetYaxis()->SetTitleFont(63);
  residuals_338->GetYaxis()->SetTitleSize(14);
  residuals_338->GetYaxis()->SetTitleOffset(1);
  residuals_338->GetYaxis()->SetLabelFont(63);
  residuals_338->GetYaxis()->SetLabelSize(14);
  residuals_338->SetMarkerSize(5);
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak338->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak338sim->GetBinContent(i) - Peak338->GetBinContent(i)) / Peak338->GetBinContent(i);
      }
    residuals_338->SetBinContent(i, diff);
  }
  residuals_338->Draw("P");

  c7->SaveAs("../graphs/ds3018_updated/real_sim_combo_338.pdf");

  TCanvas* c8 = new TCanvas("c8", "c8", 1000, 600);
  c8->cd();
  TPad *pad1c8 = new TPad("pad1c8", "pad1c8", 0, 0.33, 1, 1);
  TPad *pad2c8 = new TPad("pad2c8", "pad2c8", 0, 0, 1, 0.33);
  pad1c8->SetBottomMargin(0.00001);
  pad1c8->SetBorderMode(0);
  pad1c8->SetLogy();
  pad2c8->SetTopMargin(0.0000001);
  pad2c8->SetBottomMargin(0.2);
  pad2c8->SetBorderMode(0);
  pad1c8->Draw();
  pad2c8->Draw();

  pad1c8->cd();
  Peak239->GetXaxis()->SetLabelFont(63);
  Peak239->GetXaxis()->SetLabelSize(14);
  Peak239->GetXaxis()->SetRangeUser(0,988);
  Peak239->GetXaxis()->SetNdivisions(1319, kFALSE);
  Peak239->GetYaxis()->SetTitle("Events per Day per Channel");
  // Peak2615->GetYaxis()->SetRangeUser(ymin, ymax);
  Peak239->GetYaxis()->SetTitleFont(63);
  Peak239->GetYaxis()->SetTitleSize(14);
  Peak239->GetYaxis()->SetTitleOffset(1);
  Peak239->GetYaxis()->SetLabelFont(63);
  Peak239->GetYaxis()->SetLabelSize(14);
  
  Peak239->Draw();
  Peak239->SetLineColor(kOrange-3);
  Peak239sim->Draw("SAME");
  Peak239sim->SetLineColor(kBlack);

  t239->Draw();
  l239->Draw();

  pad2c8->cd();
  residuals_239->SetTitle("");
  residuals_239->GetXaxis()->SetLabelFont(63);
  residuals_239->GetXaxis()->SetLabelSize(14);
  residuals_239->GetXaxis()->SetTitle("Channel");
  residuals_239->GetXaxis()->SetRangeUser(0,988);
  residuals_239->GetXaxis()->SetNdivisions(1319, kFALSE);
  residuals_239->GetXaxis()->SetTitleFont(63);
  residuals_239->GetXaxis()->SetTitleSize(14);
  residuals_239->GetXaxis()->SetTitleOffset(3);
  residuals_239->GetYaxis()->SetTitle("(Simulation-Data)/Data");
  residuals_239->GetYaxis()->SetTitleFont(63);
  residuals_239->GetYaxis()->SetTitleSize(14);
  residuals_239->GetYaxis()->SetTitleOffset(1);
  residuals_239->GetYaxis()->SetLabelFont(63);
  residuals_239->GetYaxis()->SetLabelSize(14);
  residuals_239->SetMarkerSize(5);
  
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak239->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak239sim->GetBinContent(i) - Peak239->GetBinContent(i)) / Peak239->GetBinContent(i);
      }
    residuals_239->SetBinContent(i, diff);
  }
  residuals_239->Draw("P");

   c8->SaveAs("../graphs/ds3018_updated/real_sim_combo_239.pdf");
   */
}
