#include<iomanip>
#include<iostream>

#define NUM 19

void printfile(TString File)
{
TFile* F=TFile::Open(File);
  TH1 *hists[NUM];
  hists[0] = cutFlowElectrons;
  hists[1] = cutFlowMuons;
  hists[2] = cutFlowTaus;
  hists[3] = cutFlowJets;
  hists[4] = VBF_cutFlowEvents;
  hists[5] = VBF_cutFlowEvents_leplep;
  hists[6] = VBF_cutFlowEvents_leplep_pu;
  hists[7] = VBF_cutFlowEvents_leplep_pu_btag;
  hists[8] = VBF_cutFlowEvents_leplep_pu_btag_trig;
  hists[9] = VBF_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[10] = Boosted_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[11] = VH_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[12] = N1JET_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[13] = N0JET_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[14] = MVA_VBF_cutFlowEvents;
  hists[15] = MVA_Boosted_cutFlowEvents;
  hists[16] = MVA_VH_cutFlowEvents;
  hists[17] = MVA_N1JET_cutFlowEvents;
  hists[18] = MVA_N0JET_cutFlowEvents;


/*
  hists[4] = VBF_cutFlowEvents;
  hists[5] = VBF_cutFlowEvents_leplep;
  hists[6] = VBF_cutFlowEvents_leplep_pu;
  hists[7] = VBF_cutFlowEvents_leplep_pu_btag;
  hists[8] = VBF_cutFlowEvents_leplep_pu_btag_trig;
  hists[9] = Boosted_cutFlowEvents;
  hists[10] = Boosted_cutFlowEvents_leplep;
  hists[11] = Boosted_cutFlowEvents_leplep_pu;
  hists[12] = Boosted_cutFlowEvents_leplep_pu_btag;
  hists[13] = Boosted_cutFlowEvents_leplep_pu_btag_trig;
  hists[14] = VH_cutFlowEvents;
  hists[15] = VH_cutFlowEvents_leplep;
  hists[16] = VH_cutFlowEvents_leplep_pu;
  hists[17] = VH_cutFlowEvents_leplep_pu_btag;
  hists[18] = VH_cutFlowEvents_leplep_pu_btag_trig;
  hists[19] = N1JET_cutFlowEvents;
  hists[20] = N1JET_cutFlowEvents_leplep;
  hists[21] = N1JET_cutFlowEvents_leplep_pu;
  hists[22] = N1JET_cutFlowEvents_leplep_pu_btag;
  hists[23] = N1JET_cutFlowEvents_leplep_pu_btag_trig;
  hists[24] = N0JET_cutFlowEvents;
  hists[25] = N0JET_cutFlowEvents_leplep;
  hists[26] = N0JET_cutFlowEvents_leplep_pu;
  hists[27] = N0JET_cutFlowEvents_leplep_pu_btag;
  hists[28] = N0JET_cutFlowEvents_leplep_pu_btag_trig;
*/
//  for(int i = 0; i < NUM; i++)
  for(int i = 4; i < 9; i++)
  {
    cout << hists[i]->GetName() << endl;
    for(int b = 1; b <= hists[i]->GetNbinsX(); b++)
    {
      const char *name = hists[i]->GetXaxis()->GetBinLabel(b);
      float content = hists[i]->GetBinContent(b);
      std::cout << std::setw(20) << std::setprecision(8);
      std::cout << name << "\t" << content << std::endl;
    }
    cout << endl;
  }
}
