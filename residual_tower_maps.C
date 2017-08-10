//Creates tower maps like in CORC to visualize data channel by channel.
//Different function for every peak.

void tower_map2615()
{
 //defining repeatedly used variables
  int nbins = 988;
  int xmin = 0;
  int xmax = 988;
  double ymax = 1000;
  double ymin = 0.1;

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

  // gStyle->SetPalette(53,0);
  
  UInt_t Number = 3;
  Double_t Red[3]    = {0.00, 1.00, 1.00};
  Double_t Green[3]  = {0.00, 1.00, 0.00};
  Double_t Blue[3]   = {1.00, 1.00, 0.00};
  Double_t Length[3] = {0.00, 0.5, 1.00};
  Int_t nb=50;
  TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);

  std::map<int, double> myMap;
  for (Int_t i = 1; i <= nbins; i++) {
    if (Peak2615->GetBinContent(i) != 0)
      {
	Double_t diff = (Peak2615sim->GetBinContent(i) - Peak2615->GetBinContent(i)) / Peak2615->GetBinContent(i);
      }
    
    int valueToPlot = diff;
    myMap.insert(std::pair<int, double>(i, (double)valueToPlot));
  }


  
  DrawTowerMaps residuals(myMap);
  residuals.SetZRange(-2,2);
  residuals.Draw();

}


/*
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
*/
