#include "wwwAnalysis/TriggerTool.h"
#include <string>
#include <cmath>
#include <iostream>
#include "wwwAnalysis/Muon.h"
#include "wwwAnalysis/Electron.h"
#include "TDirectory.h"
#include <utility>

LeptonTriggerSF *wwwAnalysis::TriggerTool::sm_pLepTrigSFTool = 0;

void wwwAnalysis::TriggerTool::initialize()
{
  std::string lPath = std::string(getenv("ROOTCOREDIR")) + "/../TrigMuonEfficiency/share/";
  std::string ePath = std::string(getenv("ROOTCOREDIR")) + "/../ElectronEfficiencyCorrection/data/";
  std::string llPath = std::string(getenv("ROOTCOREDIR")) + "/../HSG4LepLepTriggerSF/data/";
  if(!sm_pLepTrigSFTool)
    sm_pLepTrigSFTool = new LeptonTriggerSF(2012, lPath.c_str(), "muon_trigger_sf_2012_AtoL.p1328.root", ePath.c_str(), "rel17p2.v07");
}
bool wwwAnalysis::TriggerTool::initialized()
{
	return sm_pLepTrigSFTool ;
}
void wwwAnalysis::TriggerTool::finalize()
{
	if(sm_pLepTrigSFTool)
	  delete sm_pLepTrigSFTool;
	sm_pLepTrigSFTool = 0;
}

wwwAnalysis::TriggerTool::TriggerTool()
{
  m_pMuonMatchingTool = 0;
  m_pElectronMatchingTool = 0;
  m_pTrigNavVars = 0;
}

wwwAnalysis::TriggerTool::~TriggerTool()
{
  if(m_pMuonMatchingTool)
  	delete m_pMuonMatchingTool;
  if(m_pElectronMatchingTool)
  	delete m_pElectronMatchingTool;
  if(m_pTrigNavVars)
	  delete m_pTrigNavVars;
}

double wwwAnalysis::TriggerTool::triggerSF(unsigned int runNumber, const vector<wwwAnalysis::PhysicsObject *> &leps , bool fake,wwwAnalysis::TriggerSFSys trigSFSys)
{
	if(!initialized())
		initialize();
        double sf = 1.0;
	if (leps.size() == 0) return sf;
        std::vector<TLorentzVector> muons;
        std::vector<TLorentzVector> electrons;

	std::vector<muon_quality> muq;
	std::vector<electron_quality> elq;

	for (unsigned int ilep=0;ilep<leps.size();ilep++){
		if (leps[ilep]->type()==MUON){
			muons.push_back(leps[ilep]->rawMomentum());
			muq.push_back(combined);
		}
		else{
			electrons.push_back(leps[ilep]->rawMomentum());
			elq.push_back(tightpp);
		}
	}
	SystematicVariation var = noVariation;
	if(trigSFSys == TrigSFElUp) var = plusOneSigmaElectron;
	else if(trigSFSys == TrigSFElDown) var = minusOneSigmaElectron;
	else if(trigSFSys == TrigSFMuUp) var = plusOneSigmaMuon;
	else if(trigSFSys == TrigSFMuDown) var = minusOneSigmaMuon;

	//default is mu24i_tight_OR_EF_mu36_tight 
	std::pair<double,double> SF = sm_pLepTrigSFTool->GetTriggerSF(runNumber, false, muons,muq,electrons,elq,var);
	sf *= SF.first;


  return sf;
}

bool wwwAnalysis::TriggerTool::match ( D3PDReader::Event *event, const wwwAnalysis::PhysicsObject* lep,string trigger){
  if(m_pTrigNavVars == 0)
  {
    m_pTrigNavVars = new TriggerNavigationVariables();
    m_pMuonMatchingTool = new MuonTriggerMatching(m_pTrigNavVars);
    m_pElectronMatchingTool = new ElectronTriggerMatching(m_pTrigNavVars);
  }
	std::vector<short> *chain_ChainId = event->trig_Nav.chain_ChainId();
	std::vector<std::vector<int> > *chain_RoIType = event->trig_Nav.chain_RoIType();
	std::vector<std::vector<int> > *chain_RoIIndex = event->trig_Nav.chain_RoIIndex();

	m_pTrigNavVars->set_trig_DB_SMK(event->trig_DB.SMK());
	m_pTrigNavVars->set_trig_Nav_n(event->trig_Nav.n());
	m_pTrigNavVars->set_trig_Nav_chain_ChainId(chain_ChainId);
	m_pTrigNavVars->set_trig_Nav_chain_RoIType(chain_RoIType);
	m_pTrigNavVars->set_trig_Nav_chain_RoIIndex(chain_RoIIndex); 
	// electron
	std::vector<std::vector<int> > *egamma_Electrons = event->trig_RoI_EF_e.egammaContainer_egamma_Electrons();
	std::vector<std::vector<int> > *egamma_ElectronsStatus = event->trig_RoI_EF_e.egammaContainer_egamma_ElectronsStatus();
	std::vector<float> *el_eta = event->trig_EF_el.eta();
	std::vector<float> *el_phi = event->trig_EF_el.phi();
	std::vector<float> *el_Et = event->trig_EF_el.Et();
	m_pTrigNavVars->set_trig_RoI_EF_e_egammaContainer_egamma_Electrons(egamma_Electrons);
	m_pTrigNavVars->set_trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus(egamma_ElectronsStatus);
	m_pTrigNavVars->set_trig_EF_el_n(event->trig_EF_el.n());
	m_pTrigNavVars->set_trig_EF_el_eta(el_eta);
	m_pTrigNavVars->set_trig_EF_el_phi(el_phi);
	m_pTrigNavVars->set_trig_EF_el_Et(el_Et);
/*
	std::vector<std::vector<int> > hack1;
	std::vector<std::vector<int> > *phack1 = &hack1;
	std::vector<float> hack2;
	std::vector<float> *phack2 = &hack2;
	int hack3 = 0;
	m_pTrigNavVars->set_trig_RoI_EF_e_egammaContainer_egamma_Electrons(phack1);
	m_pTrigNavVars->set_trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus(phack1);
	m_pTrigNavVars->set_trig_EF_el_n(hack3);
	m_pTrigNavVars->set_trig_EF_el_eta(phack2);
	m_pTrigNavVars->set_trig_EF_el_phi(phack2);
	m_pTrigNavVars->set_trig_EF_el_Et(phack2);
	*/

	// muon 
	std::vector<int> *EF_Muon_ROI = event->trig_RoI_EF_mu.Muon_ROI();
	std::vector<std::vector<int> > *EF_TrigMuonEFInfoContainer = event->trig_RoI_EF_mu.TrigMuonEFInfoContainer();
	std::vector<std::vector<int> > *EF_TrigMuonEFInfoContainerStatus = event->trig_RoI_EF_mu.TrigMuonEFInfoContainerStatus();
	std::vector<int> *L2_CombinedMuonFeature = event->trig_RoI_L2_mu.CombinedMuonFeature();
	std::vector<int> *L2_CombinedMuonFeatureStatus = event->trig_RoI_L2_mu.CombinedMuonFeatureStatus();
	std::vector<int> *L2_MuonFeature = event->trig_RoI_L2_mu.MuonFeature();
	std::vector<int> *L2_Muon_ROI = event->trig_RoI_L2_mu.Muon_ROI();
	std::vector<std::vector<float> > *muonef_track_CB_pt = event->trig_EF_trigmuonef.track_CB_pt();
	std::vector<std::vector<float> > *muonef_track_CB_eta = event->trig_EF_trigmuonef.track_CB_eta();
	std::vector<std::vector<float> > *muonef_track_CB_phi = event->trig_EF_trigmuonef.track_CB_phi();
	std::vector<std::vector<float> > *muonef_track_SA_pt = event->trig_EF_trigmuonef.track_SA_pt();
	std::vector<std::vector<float> > *muonef_track_SA_eta = event->trig_EF_trigmuonef.track_SA_eta();
	std::vector<std::vector<float> > *muonef_track_SA_phi = event->trig_EF_trigmuonef.track_SA_phi();
	std::vector<std::vector<float> > *mugirl_track_CB_pt = event->trig_EF_trigmugirl.track_CB_pt();
	std::vector<std::vector<float> > *mugirl_track_CB_eta = event->trig_EF_trigmugirl.track_CB_eta();
	std::vector<std::vector<float> > *mugirl_track_CB_phi = event->trig_EF_trigmugirl.track_CB_phi();
	std::vector<float> *L2_combmuonfeature_eta = event->trig_L2_combmuonfeature.eta();
	std::vector<float> *L2_combmuonfeature_phi = event->trig_L2_combmuonfeature.phi();
	std::vector<float> *L2_muonfeature_eta = event->trig_L2_muonfeature.eta();
	std::vector<float> *L2_muonfeature_phi = event->trig_L2_muonfeature.phi();
	std::vector<float> *L1_mu_eta = event->trig_L1_mu.eta();
	std::vector<float> *L1_mu_phi = event->trig_L1_mu.phi();
	std::vector<std::string> *L1_mu_thrName = event->trig_L1_mu.thrName();
	m_pTrigNavVars->set_trig_RoI_EF_mu_Muon_ROI(EF_Muon_ROI);
	m_pTrigNavVars->set_trig_RoI_EF_mu_TrigMuonEFInfoContainer(EF_TrigMuonEFInfoContainer);
	m_pTrigNavVars->set_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(EF_TrigMuonEFInfoContainerStatus);
	m_pTrigNavVars->set_trig_RoI_L2_mu_CombinedMuonFeature(L2_CombinedMuonFeature);
	m_pTrigNavVars->set_trig_RoI_L2_mu_CombinedMuonFeatureStatus(L2_CombinedMuonFeatureStatus);
	m_pTrigNavVars->set_trig_RoI_L2_mu_MuonFeature(L2_MuonFeature);
	m_pTrigNavVars->set_trig_RoI_L2_mu_Muon_ROI(L2_Muon_ROI);
	m_pTrigNavVars->set_trig_EF_trigmuonef_track_CB_pt(muonef_track_CB_pt);
	m_pTrigNavVars->set_trig_EF_trigmuonef_track_CB_eta(muonef_track_CB_eta);
	m_pTrigNavVars->set_trig_EF_trigmuonef_track_CB_phi(muonef_track_CB_phi);
	m_pTrigNavVars->set_trig_EF_trigmuonef_track_SA_pt(muonef_track_SA_pt);
	m_pTrigNavVars->set_trig_EF_trigmuonef_track_SA_eta(muonef_track_SA_eta);
	m_pTrigNavVars->set_trig_EF_trigmuonef_track_SA_phi(muonef_track_SA_phi);
	m_pTrigNavVars->set_trig_EF_trigmugirl_track_CB_pt(mugirl_track_CB_pt);
	m_pTrigNavVars->set_trig_EF_trigmugirl_track_CB_eta(mugirl_track_CB_eta);
	m_pTrigNavVars->set_trig_EF_trigmugirl_track_CB_phi(mugirl_track_CB_phi);
	m_pTrigNavVars->set_trig_L2_combmuonfeature_eta(L2_combmuonfeature_eta);
	m_pTrigNavVars->set_trig_L2_combmuonfeature_phi(L2_combmuonfeature_phi);
	m_pTrigNavVars->set_trig_L2_muonfeature_eta(L2_muonfeature_eta);
	m_pTrigNavVars->set_trig_L2_muonfeature_phi(L2_muonfeature_phi);
	m_pTrigNavVars->set_trig_L1_mu_eta(L1_mu_eta);
	m_pTrigNavVars->set_trig_L1_mu_phi(L1_mu_phi);
	m_pTrigNavVars->set_trig_L1_mu_thrName(L1_mu_thrName);

	std::vector<std::vector<int> > *IsolationContainer = event->trig_RoI_EF_mu.TrigMuonEFIsolationContainer();
	std::vector<std::vector<int> > *IsolationContainerStatus = event->trig_RoI_EF_mu.TrigMuonEFIsolationContainerStatus();
	std::vector<int> *mu15 = event->trig_EF_trigmuonef.EF_mu15();
	std::vector<int> *mu24i_tight = event->trig_EF_trigmuonef.EF_mu24i_tight();
	std::vector<int> *mu36_tight = event->trig_EF_trigmuonef.EF_mu36_tight();
	std::vector<int> *mu8 = event->trig_EF_trigmuonef.EF_mu8();
	std::vector<int> *mu18_tight = event->trig_EF_trigmuonef.EF_mu18_tight();
	std::vector<int> *mu18_tight_mu8_EFFS = event->trig_EF_trigmuonef.EF_mu18_tight_mu8_EFFS();
	std::vector<int> *_2mu13 = event->trig_EF_trigmuonef.EF_2mu13();
	std::vector<std::vector<int> > *MuonType = event->trig_EF_trigmuonef.track_MuonType();
	m_pTrigNavVars->set_trig_RoI_EF_mu_TrigMuonEFIsolationContainer(IsolationContainer); // for 2012 isolated trigger
	m_pTrigNavVars->set_trig_RoI_EF_mu_TrigMuonEFIsolationContainerStatus(IsolationContainerStatus); // for 2012 isolated trigger
	m_pTrigNavVars->set_trig_EF_trigmuonef_EF_mu15(mu15);  // for ntuple made with TriggerMenuAnalysis-00-02-86
	m_pTrigNavVars->set_trig_EF_trigmuonef_EF_mu24i_tight(mu24i_tight);  // for ntuple made with TriggerMenuAnalysis-00-02-86
	m_pTrigNavVars->set_trig_EF_trigmuonef_EF_mu36_tight(mu36_tight); // for ntuple made with TriggerMenuAnalysis-00-02-86
	m_pTrigNavVars->set_trig_EF_trigmuonef_EF_mu8(mu8);
	m_pTrigNavVars->set_trig_EF_trigmuonef_EF_mu18_tight(mu18_tight);
	m_pTrigNavVars->set_trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS(mu18_tight_mu8_EFFS);
	m_pTrigNavVars->set_trig_EF_trigmuonef_EF_2mu13(_2mu13);
	m_pTrigNavVars->set_trig_EF_trigmuonef_track_MuonType(MuonType);

	//std::cout << " triggerNavigationVariables->trig_Nav_chain_RoIIndex->size() " << m_pTrigNavVars->trig_Nav_chain_RoIIndex->size() << std::endl;
	//std::cout << " triggerNavigationVariables->trig_Nav_chain_RoIIndex->at(124).size() " << m_pTrigNavVars->trig_Nav_chain_RoIIndex->at(124).size() << std::endl;
	//std::cout << " triggerNavigationVariables->trig_Nav_chain_RoIIndex->at(128).size() " << m_pTrigNavVars->trig_Nav_chain_RoIIndex->at(128).size() << std::endl;
	//std::cout << " triggerNavigationVariables->trig_Nav_chain_RoIIndex->at(446).size() " << m_pTrigNavVars->trig_Nav_chain_RoIIndex->at(446).size() << std::endl;
	//std::cout << " triggerNavigationVariables->trig_Nav_chain_RoIIndex->at(460).size() " << m_pTrigNavVars->trig_Nav_chain_RoIIndex->at(460).size() << std::endl;



	if(not m_pTrigNavVars->isValid())
		std::cout << "VARIABLES NOT CORRECTLY SET!" << std::endl;
	//std::cout <<"in match\t"<<lep->type()<<"\t"<<m_pMuonMatchingTool <<"\t"<<m_pElectronMatchingTool<< "\t"<<trigger<<std::endl;
	if (lep->type()==MUON && m_pMuonMatchingTool) {
		//std::cout << "\t doing match muon"<<std::endl;

		//return m_pMuonMatchingTool->match(lep->momentum().Eta(),lep->momentum().Phi(),trigger.c_str());
		return m_pMuonMatchingTool->match(((Muon*)lep)->d3pd().eta(),((Muon*)lep)->d3pd().phi(),trigger.c_str());
	}
	if (lep->type()==ELECTRON &&  m_pElectronMatchingTool) {
		//std::cout << "\t doing match electron"<<std::endl;
		return m_pElectronMatchingTool->match(((Electron*)lep)->d3pd().cl_eta(),((Electron*)lep)->d3pd().cl_phi(),trigger.c_str());

	}

	return false;
}

