#include "wwwAnalysis/Input.h"
#include "TTree.h"
#include "wwwAnalysis/Functions.h"
#include <iostream>

//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::Input::Input()
:EventData(), m_iEntry(0), m_iEntries(0)
{
}

//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::Input::~Input()
{
}

void wwwAnalysis::Input::initialize(TTree *tree)
{
  EventData::initialize("physics", tree, TREE_READ);
  m_iEntries = tree->GetEntriesFast();
}
bool wwwAnalysis::Input::nextEvent()
{
	if(isDone()) return false;
	tree()->GetEntry(m_iEntry++);
	return true;
}
bool wwwAnalysis::Input::isDone()
{
	return m_iEntry >= m_iEntries;
}
/*
void wwwAnalysis::Output::initialize(const std::string &name,
		const Root::TAccept &vbf, const Root::TAccept &boosted, const Root::TAccept &vh, const Root::TAccept &jet1, const Root::TAccept &jet0)
{
	PassVBF = const_cast<Root::TAccept *>(&vbf);
	PassBoosted = const_cast<Root::TAccept *>(&boosted);
	PassVH = const_cast<Root::TAccept *>(&vh);
	Pass1Jet = const_cast<Root::TAccept *>(&jet1);
	Pass0Jet = const_cast<Root::TAccept *>(&jet0);
	EventData::initialize(TREE_WRITE);

  //initialize truth
  Truth_ggH = Truth_ZH = Truth_WH = Truth_VBFH = Truth_wwwAnalysis_leplep = false;
  if(name.find("ggH") != string::npos)
  	Truth_ggH = true;
  else if(name.find("ZH") != string::npos)
  	Truth_ZH = true;
  else if(name.find("WH") != string::npos)
  	Truth_WH = true;
  else if(name.find("VBFH") != string::npos)
  	Truth_VBFH = true;
  if(Truth_ggH || Truth_ZH || Truth_WH || Truth_VBFH)
  	Truth_wwwAnalysis_leplep = name.find("tautaull") != string::npos;
}
void wwwAnalysis::Output::FillLepton(int i, const PhysicsObject &lep)
{
	Lep[i] = lep.momentum();
	if(lep.type() == MUON)
	{
		Muon *mu = (Muon *)&lep;
		Lep_isMuon[i] = true;
		Lep_ptiso[i] = mu->d3pd().ptcone30()/Lep[i]->Pt();
		Lep_etiso[i] = mu->Etcone30_corr()/Lep[i]->Pt();
		Lep_z0_exPV[i] = mu->d3pd().id_z0_exPV();
		Lep_loose[i] = mu->d3pd().loose();
		Lep_medium[i] = mu->d3pd().medium();
		Lep_tight[i] = mu->d3pd().tight();
		Lep_author[i] = mu->d3pd().author();
	}
	else
	{
		Electron *el = (Electron *)&lep;
		Lep_isMuon[i] = false;
		Lep_ptiso[i] = el->d3pd().ptcone30()/Lep[i]->Pt();
		Lep_etiso[i] = el->Etcone30_corr()/Lep[i]->Pt();
		Lep_z0_exPV[i] = el->d3pd().trackz0pv();
		Lep_loose[i] = el->loose();
		Lep_medium[i] = el->medium();
		Lep_tight[i] = el->tight();
		Lep_author[i] = el->d3pd().author();
	}
}
void wwwAnalysis::Output::Fill(const D3PDReader::Event &event, const PhysicsObject &lep1, const PhysicsObject &lep2,
		const std::vector<Jet> &jets, int jet1, int jet2, const MissingEt &met, const TVector2 &hpto,
		double mcWeight, double sfWeight, double puWeight, double btagWeight, double trigWeight)
{
	//fill leptons
	FillLepton(0,lep1);
	FillLepton(1,lep2);
	
	//fill jets
	Jets->resize(jets.size());
	for(int i = 0; i < jets.size(); i++)
		Jets->at(i) = jets[i].momentum();
	TaggedJet1 = jet1 < jets.size() ? jet1 : -1;
	TaggedJet2 = jet2 < jets.size() ? jet2 : -1;
	
	MET_HPTO_Et = hpto.Mod();
	MET_HPTO_phi = hpto.Phi();
	MET_final_Et = met.Et();
	MET_final_phi = met.phi();

	MonteCarloWeight = mcWeight;
	RecoWeight = sfWeight;
	PileupWeight = puWeight;
	BTagWeight = btagWeight;
	TriggerWeight = trigWeight;

  double MET_sigma = 0.97*sqrt(met.sumEt());  // for 2011 analtsis sigma=0.7*sqrt(MET_sumet)

// lv_l1 and lv_l2 are TLorentzVectors of 1st and second leptons (inGeV). 
//  m_oMMC.Scan6dAnal(m_vLep[0]*(1/1000.0), m_vLep[1]*(1/1000.0), met.Ex()/1000.0, met.Ey()/1000.0, MET_sigma/1000.0);
  double MET_corr_etx = m_oMMC.GetCorrMEX();
  double MET_corr_ety = m_oMMC.GetCorrMEY();
  MET_mmc_Et = sqrt(MET_corr_etx*MET_corr_etx+MET_corr_ety*MET_corr_ety);
  MET_mmc_phi = atan2(MET_corr_ety,MET_corr_etx);

// perform 4d scan to estimate the mass
//  double res2=m_oMMC.Scan4dAnal((*Lep[0])*(1/1000.0), (*Lep[1])*(1/1000.0), MET_corr_etx, MET_corr_ety);

  MmcMass=m_oMMC.GetMZ_peak()*1000;
// get the estimated mass

  LikelyMass=GetLikelyMass(*Lep[0], *Lep[1], met.pt());
    
	Truth_channel = event.eventinfo.mc_channel_number();
 
	tree()->Fill();
}*/
