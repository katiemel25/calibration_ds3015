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

void tower_maps()
{
  QChain * ch = new QChain("qtree");
  ch->Add("/nfs/cuore1/scratch/shared_output/output/ds3018/calibration_Production_ds3018_tower019.list");

  DrawTowerSpectra Spectra(ch, "Energy", "IsSignal && Filter_RejectBadIntervals && Energy > 2595 && Energy < 2635 && NumberOfPulses==1", 100, 2615-20, 2615+20);
  
  Spectra.DoFits("gaus");
  DrawTowerMaps IntMap(Spectra.GetIntegrals());
  IntMap.Draw();
}
