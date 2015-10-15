#include<iomanip>
#include<iostream>

#define NUM 16

void print()
{
  TH1 *hists[NUM];
  /*  hists[0] = VBF_cutFlowEvents;
  hists[1] = VBF_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[2] = Boosted_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[3] = VH_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[4] = N1Jet_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[5] = N0Jet_cutFlowEvents_leplep_pu_btag_trig_xsec;
  */

  hists[0] = cutFlowElectrons;
  hists[1] = cutFlowMuons;
  hists[2] = cutFlowTaus;
  hists[3] = cutFlowJets;
  /*  hists[4] = min_cutFlowEvents;
  hists[5] = VBF_cutFlowEvents;
  hists[6] = VBF_cutFlowEvents_leplep;
  hists[7] = VBF_cutFlowEvents_leplep_pu;
  hists[8] = VBF_cutFlowEvents_leplep_pu_btag;
  hists[9] = VBF_cutFlowEvents_leplep_pu_btag_trig;
  hists[10] = VBF_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[11] = Boosted_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[12] = VH_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[13] = VH_cutFlowEvents_leplep_pu_btag_trig_xsec;
  hists[14] = VH_cutFlowEvents_leplep_pu_btag_trig_xsec;
  */
/*  hists[14] = MVA_VBF_cutFlowEvents;
  hists[15] = MVA_Boosted_cutFlowEvents;
  hists[16] = MVA_VH_cutFlowEvents;
  hists[17] = MVA_N1Jet_cutFlowEvents;
  hists[18] = MVA_N0Jet_cutFlowEvents;
*/


  hists[4] = VBF_cutFlowEvents;
  hists[5] = VBF_cutFlowEvents_leplep;
  hists[6] = VBF_cutFlowEvents_leplep_pu;
  hists[7] = VBF_cutFlowEvents_leplep_pu_btag;
  hists[8] = VBF_cutFlowEvents_leplep_pu_btag_trig;
  hists[9] = VBF_cutFlowEvents_leplep_pu_btag_trig_xsec;
 
  hists[10] = MVA_VBF_cutFlowMVAEvents;
  hists[11] = MVA_VBF_cutFlowMVAEvents_xsec;
  hists[12] = MVA_VBF_cutFlowMVAEvents_xsec_pu;
  hists[13] = MVA_VBF_cutFlowMVAEvents_xsec_pu_leplep;
  hists[14] = MVA_VBF_cutFlowMVAEvents_xsec_pu_leplep_btag;
  hists[15] = MVA_VBF_cutFlowMVAEvents_xsec_pu_leplep_btag_trig;
  /*  hists[11] = MVA_VBF_cutFlowEvents_leplep;
  hists[12] = MVA_VBF_cutFlowEvents_leplep;
  hists[13] = MVA_VBF_cutFlowEvents_leplep_pu;
  hists[14] = MVA_VBF_cutFlowEvents_leplep_pu_btag;
  hists[15] = MVA_VBF_cutFlowEvents_leplep_pu_btag_trig;
  hists[16] = MVA_VBF_cutFlowEvents_leplep_pu_btag_trig_xsec;
  */
  /*  hists[9] = Boosted_cutFlowEvents;
  hists[10] = Boosted_cutFlowEvents_leplep;
  hists[11] = Boosted_cutFlowEvents_leplep_pu;
  hists[12] = Boosted_cutFlowEvents_leplep_pu_btag;
  hists[13] = Boosted_cutFlowEvents_leplep_pu_btag_trig;
  hists[14] = VH_cutFlowEvents;
  hists[15] = VH_cutFlowEvents_leplep;
  hists[16] = VH_cutFlowEvents_leplep_pu;
  hists[17] = VH_cutFlowEvents_leplep_pu_btag;
  hists[18] = VH_cutFlowEvents_leplep_pu_btag_trig;
  hists[19] = N1Jet_cutFlowEvents;
  hists[20] = N1Jet_cutFlowEvents_leplep;
  hists[21] = N1Jet_cutFlowEvents_leplep_pu;
  hists[22] = N1Jet_cutFlowEvents_leplep_pu_btag;
  hists[23] = N1Jet_cutFlowEvents_leplep_pu_btag_trig;
  hists[24] = N0Jet_cutFlowEvents;
  hists[25] = N0Jet_cutFlowEvents_leplep;
  hists[26] = N0Jet_cutFlowEvents_leplep_pu;
  hists[27] = N0Jet_cutFlowEvents_leplep_pu_btag;
  hists[28] = N0Jet_cutFlowEvents_leplep_pu_btag_trig;
  */
  for(int i = 0; i < NUM; i++)
//  for(int i = 4; i < 5; i++)
  {
    cout << hists[i]->GetName() << endl;
    for(int b = 1; b <= hists[i]->GetNbinsX(); b++)
    {
      //if(i >= 10 && b < hists[i]->GetNbinsX())
      //  continue;
      const char *name = hists[i]->GetXaxis()->GetBinLabel(b);
      double content = hists[i]->GetBinContent(b);
      double error = hists[i]->GetBinError(b);
      std::cout << std::setw(20) << std::setprecision(10);
//      std::cout << name << "\t" << content << " ± " << error << std::endl;
      std::cout << name << "\t" << content << std::endl;
    }
    cout << endl;
  }
}
