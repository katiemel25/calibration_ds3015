//Creates tower maps like in CORC to visualize data channel by channel.
//Different function for every peak.

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

void tower_map2615()
{
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  DrawTowerSpectra Spectra(ch, "QNDBDOfficialEnergy", "IsSignal && Filter_RejectBadIntervals && QNDBDOfficialEnergy > 2595 && QNDBDOfficialEnergy < 2635 && NumberOfPulses==1 &&  Run > 301113" , 100, 2595, 2635);

  gStyle->SetPalette(54, 0);
  
  Spectra.DoFits("gaus");
  DrawTowerMaps IntMap(Spectra.GetIntegrals());
  IntMap.Draw();
}

void tower_map969()
{
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  DrawTowerSpectra Spectra(ch, "QNDBDOfficialEnergy", "IsSignal && Filter_RejectBadIntervals && QNDBDOfficialEnergy > 949 && QNDBDOfficialEnergy < 989 && NumberOfPulses==1 &&  Run > 301113" , 100, 949, 989);

  gStyle->SetPalette(54, 0);
  
  Spectra.DoFits("gaus");
  DrawTowerMaps IntMap(Spectra.GetIntegrals());
  IntMap.Draw();
}

void tower_map911()
{
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  DrawTowerSpectra Spectra(ch, "QNDBDOfficialEnergy", "IsSignal && Filter_RejectBadIntervals && QNDBDOfficialEnergy > 891 && QNDBDOfficialEnergy < 931 && NumberOfPulses==1 &&  Run > 301113" , 100, 891, 931);

  gStyle->SetPalette(54, 0);
  
  Spectra.DoFits("gaus");
  DrawTowerMaps IntMap(Spectra.GetIntegrals());
  IntMap.Draw();
}
void tower_map583()
{
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  DrawTowerSpectra Spectra(ch, "QNDBDOfficialEnergy", "IsSignal && Filter_RejectBadIntervals && QNDBDOfficialEnergy > 563 && QNDBDOfficialEnergy < 603 && NumberOfPulses==1 &&  Run > 301113" , 100, 563, 603);

  gStyle->SetPalette(54, 0);
  
  Spectra.DoFits("gaus");
  DrawTowerMaps IntMap(Spectra.GetIntegrals());
  IntMap.Draw();
}

void tower_map338()
{
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  DrawTowerSpectra Spectra(ch, "QNDBDOfficialEnergy", "IsSignal && Filter_RejectBadIntervals && QNDBDOfficialEnergy > 949 && QNDBDOfficialEnergy < 989 && NumberOfPulses==1 &&  Run > 301113" , 100, 949, 989);

  gStyle->SetPalette(54, 0);
  
  Spectra.DoFits("gaus");
  DrawTowerMaps IntMap(Spectra.GetIntegrals());
  IntMap.Draw();
}

void tower_map338()
{
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  DrawTowerSpectra Spectra(ch, "QNDBDOfficialEnergy", "IsSignal && Filter_RejectBadIntervals && QNDBDOfficialEnergy > 318 && QNDBDOfficialEnergy < 358 && NumberOfPulses==1 &&  Run > 301113" , 100, 318, 358);

  gStyle->SetPalette(54, 0);
  
  Spectra.DoFits("gaus");
  DrawTowerMaps IntMap(Spectra.GetIntegrals());
  IntMap.Draw();
}

void tower_map239()
{
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018_unblinded/calibration_UnblindedReduced_ds3018.list");

  DrawTowerSpectra Spectra(ch, "QNDBDOfficialEnergy", "IsSignal && Filter_RejectBadIntervals && QNDBDOfficialEnergy > 219 && QNDBDOfficialEnergy < 239 && NumberOfPulses==1 &&  Run > 301113" , 100, 219, 259);

  gStyle->SetPalette(54, 0);
  
  Spectra.DoFits("gaus");
  DrawTowerMaps IntMap(Spectra.GetIntegrals());
  IntMap.Draw();
}

