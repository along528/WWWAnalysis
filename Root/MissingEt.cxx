#include "wwwAnalysis/MissingEt.h"
#include "TMath.h"

ClassImp( wwwAnalysis::MissingEt )

METUtility *wwwAnalysis::MissingEt::sm_pMETTool = 0;
METUtility *wwwAnalysis::MissingEt::sm_pMETSTVFTool = 0;

wwwAnalysis::MissingEt::~MissingEt(){
	m_mu_energyLossPar_STVF->clear();
	delete m_mu_energyLossPar_STVF;
	m_mu_energyLossPar_STVF = 0;

}

wwwAnalysis::MissingEt::MissingEt(const D3PDReader::Event &event, const D3PDReader::RefFinalMETD3PDObject &met, const std::vector<Electron> &el, const std::vector<Muon> &mu, bool use_third_chain_muon,const std::vector<Jet> &jet,METSoftTermsSys softTermsSys )
  :PhysicsObject(event.eventinfo, MISSING_ET), m_fSumEtRaw(met.sumet()),m_fSumEt(0.),m_fSumEtSTVF(0.),m_pD3PD(&(met)),m_mu_energyLossPar_STVF(0)
{
  if(!initialized())
    initialize();

  TLorentzVector p_RefFinal,p_RefFinalSTVF, raw;
  p_RefFinal.SetPtEtaPhiM(met.et(), 0, met.phi(), 0);
  p_RefFinalSTVF.SetPtEtaPhiM(met.et(), 0, met.phi(), 0);
  raw = p_RefFinal;
  sm_pMETSTVFTool->reset();
  sm_pMETSTVFTool->setJetPUcode(MissingETTags::JPU_JET_JVFCUT);//for STVF only
  sm_pMETSTVFTool->setDoMuEloss(true);

  sm_pMETTool->reset();
  sm_pMETTool->setDoMuEloss(true);

//WZ:
  std::vector<float> new_pt_jet(jet.size(),-100.);
  std::vector<float> new_eta_jet(jet.size(),-100.);
  std::vector<float> new_phi_jet(jet.size(),-100.);
  std::vector<float> new_e_jet(jet.size(),-100.);
/*
  std::vector<float> new_pt_jet(*event.jet_AntiKt4LCTopo.pt());
  std::vector<float> new_eta_jet(*event.jet_AntiKt4LCTopo.eta());
  std::vector<float> new_phi_jet(*event.jet_AntiKt4LCTopo.phi());
  std::vector<float> new_e_jet(*event.jet_AntiKt4LCTopo.E());
  */

/*
  std::vector<float> new_pt_jet(*event.jet.pt());
  std::vector<float> new_eta_jet(*event.jet.eta());
  std::vector<float> new_phi_jet(*event.jet.phi());
  std::vector<float> new_e_jet(*event.jet.E());
*/

  std::vector<float> new_pt_muon(mu.size(),-100.) ;
  std::vector<float> new_pt_muonMS(mu.size(),-100.);
  std::vector<float> new_qoverp_muonMS(mu.size(),-100.);
  std::vector<float> new_charge_muonMS(mu.size(),-100.);
  std::vector<float> new_pt_el(el.size(),-100.);
  std::vector<float> new_eta_el(el.size(),-100.);
  std::vector<float> new_phi_el(el.size(),-100.);

  /*
  //this information isn't used. it is only cloned to get that right
  //size and then written over.  so instead just create based on size
  std::vector<float> new_pt_muon(*event.mu_staco.pt());
  std::vector<float> new_pt_muonMS(*event.mu_staco.ms_qoverp());
  std::vector<float> new_qoverp_muonMS(*event.mu_staco.ms_qoverp());
  std::vector<float> new_charge_muonMS(*event.mu_staco.charge());
  std::vector<float> new_pt_el(*event.el.cl_pt());
  std::vector<float> new_eta_el(*event.el.cl_eta());
  std::vector<float> new_phi_el(*event.el.cl_phi());
  */


  for(unsigned int i = 0; i < jet.size(); i++)
  {
    int index = jet[i].d3pd().GetIndex();
    new_pt_jet[index] = jet[i].momentum().Pt();
    new_eta_jet[index] = jet[i].momentum().Eta();
    new_phi_jet[index] = jet[i].momentum().Phi();
    new_e_jet[index] = jet[i].momentum().E();
  }


  for(unsigned int i = 0; i < mu.size(); i++)
  {
    int index = mu[i].d3pd().GetIndex();
    new_pt_muon[index] = mu[i].momentum().Pt();
    new_pt_muonMS[index] = mu[i].ptms();
    new_qoverp_muonMS[index] = mu[i].charge()*sin(mu[i].d3pd().ms_theta())/mu[i].ptms();
    new_charge_muonMS[index] = mu[i].charge();
  }
  for(unsigned int i = 0; i < el.size(); i++)
  {
    int index = el[i].d3pd().GetIndex();
    new_pt_el[index] = el[i].momentum().Pt();
    new_eta_el[index] = el[i].momentum().Eta();
    new_phi_el[index] = el[i].momentum().Phi();
  }
  sm_pMETTool->setObjects(METUtil::Jets, &new_pt_jet, event.jet_AntiKt4LCTopo.eta(), event.jet_AntiKt4LCTopo.phi(), &new_e_jet, event.jet_AntiKt4LCTopo_MET.wet(), event.jet_AntiKt4LCTopo_MET.wpx(), event.jet_AntiKt4LCTopo_MET.wpy(), event.jet_AntiKt4LCTopo_MET.statusWord());
  sm_pMETSTVFTool->setObjects(METUtil::Jets, &new_pt_jet, event.jet_AntiKt4LCTopo.eta(), event.jet_AntiKt4LCTopo.phi(), &new_e_jet, event.jet_AntiKt4LCTopo_MET.wet(), event.jet_AntiKt4LCTopo_MET.wpx(), event.jet_AntiKt4LCTopo_MET.wpy(), event.jet_AntiKt4LCTopo_MET.statusWord());
  //no longer available since not necessary
  //sm_pMETTool->setOriJetParameters(event.jet_AntiKt4LCTopo.pt()); //old
  float STVF = 1.;
  if (event.MET_CellOut_Eflow.sumet()!=0.) STVF =  event.MET_CellOut_Eflow_STVF.sumet()/ event.MET_CellOut_Eflow.sumet();
  m_mu_energyLossPar_STVF = new std::vector<float>();
  m_mu_energyLossPar_STVF->clear();
  if(use_third_chain_muon) {

  	sm_pMETTool->setMuonParameters(&new_pt_muon, event.mu.eta(), event.mu.phi(), event.mu_MET.wet(), event.mu_MET.wpx(), event.mu_MET.wpy(), event.mu_MET.statusWord());
  	sm_pMETTool->setExtraMuonParameters(&new_pt_muonMS, event.mu.ms_theta(), event.mu.ms_phi());
	sm_pMETTool->setMuonEloss(event.mu.energyLossPar());

	for (unsigned int imu = 0; imu < event.mu.n(); imu++)
		m_mu_energyLossPar_STVF->push_back(event.mu[imu].energyLossPar()*STVF);

  	sm_pMETSTVFTool->setMuonParameters(&new_pt_muon, event.mu.eta(), event.mu.phi(), event.mu_MET.wet(), event.mu_MET.wpx(), event.mu_MET.wpy(), event.mu_MET.statusWord());
  	sm_pMETSTVFTool->setExtraMuonParameters(&new_pt_muonMS, event.mu.ms_theta(), event.mu.ms_phi());
	sm_pMETSTVFTool->setMuonEloss(m_mu_energyLossPar_STVF); 
  }
  else {
  	sm_pMETTool->setMuonParameters(&new_pt_muon, event.mu_staco.eta(), event.mu_staco.phi(), event.mu_staco_MET.wet(), event.mu_staco_MET.wpx(), event.mu_staco_MET.wpy(), event.mu_staco_MET.statusWord());
  	sm_pMETTool->setExtraMuonParameters(&new_pt_muonMS, event.mu_staco.ms_theta(), event.mu_staco.ms_phi());
	sm_pMETTool->setMuonEloss(event.mu_staco.energyLossPar()); 

	for (unsigned int imu = 0; imu < event.mu_staco.n(); imu++)
		m_mu_energyLossPar_STVF->push_back(event.mu_staco[imu].energyLossPar()*STVF);
  	sm_pMETSTVFTool->setMuonParameters(&new_pt_muon, event.mu_staco.eta(), event.mu_staco.phi(), event.mu_staco_MET.wet(), event.mu_staco_MET.wpx(), event.mu_staco_MET.wpy(), event.mu_staco_MET.statusWord());
  	sm_pMETSTVFTool->setExtraMuonParameters(&new_pt_muonMS, event.mu_staco.ms_theta(), event.mu_staco.ms_phi());
	sm_pMETSTVFTool->setMuonEloss(m_mu_energyLossPar_STVF); 
   }
  sm_pMETTool->setElectronParameters(&new_pt_el, &new_eta_el, &new_phi_el, event.el_MET.wet(), event.el_MET.wpx(), event.el_MET.wpy(), event.el_MET.statusWord());
  sm_pMETSTVFTool->setElectronParameters(&new_pt_el, &new_eta_el, &new_phi_el, event.el_MET.wet(), event.el_MET.wpx(), event.el_MET.wpy(), event.el_MET.statusWord());



  double MET_RefGamma_etx = event.MET_RefGamma.et() * TMath::Cos(event.MET_RefGamma.phi());
  double MET_RefGamma_ety = event.MET_RefGamma.et() * TMath::Sin(event.MET_RefGamma.phi());
  double MET_RefTau_etx = event.MET_RefTau.et() * TMath::Cos(event.MET_RefTau.phi());
  double MET_RefTau_ety = event.MET_RefTau.et() * TMath::Sin(event.MET_RefTau.phi());
  double MET_CellOut_Eflow_etx = event.MET_CellOut_Eflow.et() * TMath::Cos(event.MET_CellOut_Eflow.phi());
  double MET_CellOut_Eflow_ety = event.MET_CellOut_Eflow.et() * TMath::Sin(event.MET_CellOut_Eflow.phi());
  double MET_CellOut_Eflow_STVF_etx = event.MET_CellOut_Eflow_STVF.et() * TMath::Cos(event.MET_CellOut_Eflow_STVF.phi());
  double MET_CellOut_Eflow_STVF_ety = event.MET_CellOut_Eflow_STVF.et() * TMath::Sin(event.MET_CellOut_Eflow_STVF.phi());


  sm_pMETTool->setMETTerm(METUtil::RefTau, MET_RefTau_etx, MET_RefTau_ety, event.MET_RefTau.sumet());
  sm_pMETSTVFTool->setMETTerm(METUtil::RefTau, MET_RefTau_etx, MET_RefTau_ety, event.MET_RefTau.sumet());

  sm_pMETTool->setMETTerm(METUtil::RefGamma, MET_RefGamma_etx, MET_RefGamma_ety, event.MET_RefGamma.sumet());
  sm_pMETSTVFTool->setMETTerm(METUtil::RefGamma, MET_RefGamma_etx, MET_RefGamma_ety, event.MET_RefGamma.sumet());

  sm_pMETTool->setMETTerm(METUtil::SoftTerms, MET_CellOut_Eflow_etx, MET_CellOut_Eflow_ety, event.MET_CellOut_Eflow.sumet());
  sm_pMETSTVFTool->setMETTerm(METUtil::SoftTerms, MET_CellOut_Eflow_STVF_etx, MET_CellOut_Eflow_STVF_ety, event.MET_CellOut_Eflow_STVF.sumet());
/*
  sm_pMETTool->setMETTerm(METUtil::RefTau, event.MET_RefTau.etx_CentralReg()+ event.MET_RefTau.etx_ForwardReg()+ event.MET_RefTau.etx_EndcapRegion() , 
					   event.MET_RefTau.ety_CentralReg()+ event.MET_RefTau.ety_ForwardReg()+ event.MET_RefTau.ety_EndcapRegion() , event.MET_RefTau.sumet());
  sm_pMETSTVFTool->setMETTerm(METUtil::RefTau, event.MET_RefTau.etx_CentralReg()+ event.MET_RefTau.etx_ForwardReg()+ event.MET_RefTau.etx_EndcapRegion() , 
					   event.MET_RefTau.ety_CentralReg()+ event.MET_RefTau.ety_ForwardReg()+ event.MET_RefTau.ety_EndcapRegion() , event.MET_RefTau.sumet());

  sm_pMETTool->setMETTerm(METUtil::RefGamma, event.MET_RefGamma.etx_CentralReg()+ event.MET_RefGamma.etx_ForwardReg()+ event.MET_RefGamma.etx_EndcapRegion() , 
					   event.MET_RefGamma.ety_CentralReg()+ event.MET_RefGamma.ety_ForwardReg()+ event.MET_RefGamma.ety_EndcapRegion() , event.MET_RefGamma.sumet());
  sm_pMETSTVFTool->setMETTerm(METUtil::RefGamma, event.MET_RefGamma.etx_CentralReg()+ event.MET_RefGamma.etx_ForwardReg()+ event.MET_RefGamma.etx_EndcapRegion() , 
					   event.MET_RefGamma.ety_CentralReg()+ event.MET_RefGamma.ety_ForwardReg()+ event.MET_RefGamma.ety_EndcapRegion() , event.MET_RefGamma.sumet());

  sm_pMETTool->setMETTerm(METUtil::SoftTerms, event.MET_CellOut_Eflow.etx_CentralReg()+ event.MET_CellOut_Eflow.etx_ForwardReg()+ event.MET_CellOut_Eflow.etx_EndcapRegion() , 
					   event.MET_CellOut_Eflow.ety_CentralReg()+ event.MET_CellOut_Eflow.ety_ForwardReg()+ event.MET_CellOut_Eflow.ety_EndcapRegion() , event.MET_CellOut_Eflow.sumet());
  sm_pMETSTVFTool->setMETTerm(METUtil::SoftTerms, event.MET_CellOut_Eflow_STVF.etx_CentralReg()+ event.MET_CellOut_Eflow_STVF.etx_ForwardReg()+ event.MET_CellOut_Eflow_STVF.etx_EndcapRegion() , 
					   event.MET_CellOut_Eflow_STVF.ety_CentralReg()+ event.MET_CellOut_Eflow_STVF.ety_ForwardReg()+ event.MET_CellOut_Eflow_STVF.ety_EndcapRegion() , event.MET_CellOut_Eflow_STVF.sumet());
*/


/*
  sm_pMETTool->setMETTerm(METUtil::RefTau, event.MET_RefTau.etx_CentralReg()+ event.MET_RefTau.etx_EndcapRegion() , 
					   event.MET_RefTau.ety_CentralReg()+ event.MET_RefTau.ety_EndcapRegion() , event.MET_RefTau.sumet());
  sm_pMETSTVFTool->setMETTerm(METUtil::RefTau, event.MET_RefTau.etx_CentralReg()+ event.MET_RefTau.etx_EndcapRegion() , 
					   event.MET_RefTau.ety_CentralReg()+ event.MET_RefTau.ety_EndcapRegion() , event.MET_RefTau.sumet());

  sm_pMETTool->setMETTerm(METUtil::RefGamma, event.MET_RefGamma.etx_CentralReg()+ event.MET_RefGamma.etx_EndcapRegion() , 
					   event.MET_RefGamma.ety_CentralReg()+ event.MET_RefGamma.ety_EndcapRegion() , event.MET_RefGamma.sumet());
  sm_pMETSTVFTool->setMETTerm(METUtil::RefGamma, event.MET_RefGamma.etx_CentralReg()+ event.MET_RefGamma.etx_EndcapRegion() , 
					   event.MET_RefGamma.ety_CentralReg()+ event.MET_RefGamma.ety_EndcapRegion() , event.MET_RefGamma.sumet());

  sm_pMETTool->setMETTerm(METUtil::SoftTerms, event.MET_CellOut_Eflow.etx_CentralReg()+ event.MET_CellOut_Eflow.etx_EndcapRegion() , 
					   event.MET_CellOut_Eflow.ety_CentralReg()+ event.MET_CellOut_Eflow.ety_EndcapRegion() , event.MET_CellOut_Eflow.sumet());
  sm_pMETSTVFTool->setMETTerm(METUtil::SoftTerms, event.MET_CellOut_Eflow_STVF.etx_CentralReg()+ event.MET_CellOut_Eflow_STVF.etx_EndcapRegion() , 
					   event.MET_CellOut_Eflow_STVF.ety_CentralReg()+ event.MET_CellOut_Eflow_STVF.ety_EndcapRegion() , event.MET_CellOut_Eflow_STVF.sumet());

*/
 
  // if(event.eventinfo.EventNumber() == 102002)
  /*
	   if(1==1)
  {
    std::cout << "DEBUG ====================" << std::endl;
    std::cout << "Jets" << std::endl;
    for(unsigned int i = 0; i < jet.size(); i++)
    {
      std::cout << "\tPt:" << jet[i].momentum().Pt();
      std::cout << "\tEta:" << jet[i].momentum().Eta();
      std::cout << "\tPhi:" << jet[i].momentum().Phi();
      std::cout << "\tE:" << jet[i].momentum().E();
      std::cout << "\tOriPt:" << jet[i].rawMomentum().Pt() << std::endl;
    }
    std::cout << "Muons" << std::endl;
    for(unsigned int i = 0; i < mu.size(); i++)
    {
      std::cout << "\tPt:" << mu[i].momentum().Pt();
      std::cout << "\tEta:" << mu[i].momentum().Eta();
      std::cout << "\tPhi:" << mu[i].momentum().Phi();
      std::cout << "\tE:" << mu[i].momentum().E();
      std::cout << "\tOriPt:" << mu[i].rawMomentum().Pt() << std::endl;
    }
    std::cout << "Electrons" << std::endl;
    for(unsigned int i = 0; i < el.size(); i++)
    {
      std::cout << "\tPt:" << el[i].momentum().Pt();
      std::cout << "\tEta:" << el[i].momentum().Eta();
      std::cout << "\tPhi:" << el[i].momentum().Phi();
      std::cout << "\tE:" << el[i].momentum().E();
      std::cout << "\tOriPt:" << el[i].rawMomentum().Pt() << std::endl;
    }
    std::cout << "RefFinal_etx:\t" << sm_pMETTool->getMissingET(METUtil::RefFinal).etx() << std::endl;
    std::cout << "RefFinal_ety:\t" << sm_pMETTool->getMissingET(METUtil::RefFinal).ety() << std::endl;
    std::cout << "RefFinal_et:\t" << sm_pMETTool->getMissingET(METUtil::RefFinal).et() << std::endl;
    std::cout << "RefEle_et:\t" << sm_pMETTool->getMissingET(METUtil::RefEle).et() << std::endl;
    std::cout << "RefMuon_et:\t" << sm_pMETTool->getMissingET(METUtil::RefMuon).et() << std::endl;
    std::cout << "MuonTotal_et:\t" << sm_pMETTool->getMissingET(METUtil::MuonTotal).et() << std::endl;
    std::cout << "RefJet_et:\t" << sm_pMETTool->getMissingET(METUtil::RefJet).et() << std::endl;
  }
  */
  


/*
  for(int i = 0; i < el.size(); i++)
    correctPt(p, el[i].rawMomentum(), el[i].momentum());
  for(int i = 0; i < mu.size(); i++)
    correctPt(p, mu[i].rawMomentum(), mu[i].momentum());
*/



  METUtil::MultiSyst systematic = METUtil::None;
  if(softTermsSys==METSoftTermsScaleUp) systematic = METUtil::ScaleSoftTermsUp;
  if(softTermsSys==METSoftTermsScaleDown) systematic = METUtil::ScaleSoftTermsDown;
  if(softTermsSys==METSoftTermsResoUp) systematic = METUtil::ResoSoftTermsUp;
  if(softTermsSys==METSoftTermsResoDown) systematic = METUtil::ResoSoftTermsDown;




  //setMomentum(p_RefFinal, raw);


  //Set Random Seed
  //Make sure that only call getMissingET once if getting resolution systematics and reset random seed before the call
  if(!event.eventinfo.mc_channel_number.IsAvailable()) gRandom->SetSeed(UInt_t(event.eventinfo.RunNumber() * event.eventinfo.EventNumber()));
  else gRandom->SetSeed(UInt_t(event.eventinfo.mc_channel_number() * event.eventinfo.EventNumber()));


  METUtility::METObject metRefFinalSTVF = sm_pMETSTVFTool->getMissingET(METUtil::RefFinal,systematic);
  p_RefFinalSTVF.SetPx(metRefFinalSTVF.etx());
  p_RefFinalSTVF.SetPy(metRefFinalSTVF.ety());
  p_RefFinalSTVF.SetZ(0);
  p_RefFinalSTVF.SetE(metRefFinalSTVF.et());
  m_fSumEtSTVF = metRefFinalSTVF.sumet();
  setMomentumSTVF(p_RefFinalSTVF);

  //Set Random Seed
  //Make sure that only call getMissingET once if getting resolution systematics and reset random seed before the call
  if(!event.eventinfo.mc_channel_number.IsAvailable()) gRandom->SetSeed(UInt_t(event.eventinfo.RunNumber() * event.eventinfo.EventNumber()));
  else gRandom->SetSeed(UInt_t(event.eventinfo.mc_channel_number() * event.eventinfo.EventNumber()));

  /*
  std::cout << "METUtil::RefFinal "<< sm_pMETTool->getMissingET(METUtil::RefFinal).etx()<<"\t"<< sm_pMETTool->getMissingET(METUtil::RefFinal).ety() << "\t" << sm_pMETTool->getMissingET(METUtil::RefFinal).et() << std::endl;
  std::cout << "METUtil::SoftTerms "<< sm_pMETTool->getMissingET(METUtil::SoftTerms).etx()<<"\t"<< sm_pMETTool->getMissingET(METUtil::SoftTerms).ety() << "\t" << sm_pMETTool->getMissingET(METUtil::SoftTerms).et() << std::endl;
  std::cout << "METUtil::RefGamma "<< sm_pMETTool->getMissingET(METUtil::RefGamma).etx()<<"\t"<< sm_pMETTool->getMissingET(METUtil::RefGamma).ety() << "\t" << sm_pMETTool->getMissingET(METUtil::RefGamma).et() << std::endl;
  std::cout << "METUtil::RefJet "<< sm_pMETTool->getMissingET(METUtil::RefJet).etx()<<"\t"<< sm_pMETTool->getMissingET(METUtil::RefJet).ety() << "\t" << sm_pMETTool->getMissingET(METUtil::RefJet).et() << std::endl;
  std::cout << "METUtil::MuonTotal "<< sm_pMETTool->getMissingET(METUtil::MuonTotal).etx()<<"\t"<< sm_pMETTool->getMissingET(METUtil::MuonTotal).ety() << "\t" << sm_pMETTool->getMissingET(METUtil::MuonTotal).et() << std::endl;
  std::cout << "METUtil::RefMuon "<< sm_pMETTool->getMissingET(METUtil::RefMuon).etx()<<"\t"<< sm_pMETTool->getMissingET(METUtil::RefMuon).ety() << "\t" << sm_pMETTool->getMissingET(METUtil::RefMuon).et() << std::endl;
  std::cout << "METUtil::RefEle "<< sm_pMETTool->getMissingET(METUtil::RefEle).etx()<<"\t"<< sm_pMETTool->getMissingET(METUtil::RefEle).ety() << "\t" << sm_pMETTool->getMissingET(METUtil::RefEle).et() << std::endl;
  std::cout << "METUtil::RefTau "<< sm_pMETTool->getMissingET(METUtil::RefTau).etx()<<"\t"<< sm_pMETTool->getMissingET(METUtil::RefTau).ety() << "\t" << sm_pMETTool->getMissingET(METUtil::RefTau).et() << std::endl;
  */

  METUtility::METObject metRefFinal = sm_pMETTool->getMissingET(METUtil::RefFinal,systematic);
  p_RefFinal.SetPx(metRefFinal.etx());
  p_RefFinal.SetPy(metRefFinal.ety());
  p_RefFinal.SetZ(0);
  p_RefFinal.SetE(metRefFinal.et());
  m_fSumEt = metRefFinal.sumet();
  setMomentum(p_RefFinal, raw);
}


void wwwAnalysis::MissingEt::setMomentumSTVF(const TLorentzVector &momentum)
{
	m_oMomentumSTVF = momentum;
}
TLorentzVector wwwAnalysis::MissingEt::momentumSTVF() const
{
	return m_oMomentumSTVF;
}
void wwwAnalysis::MissingEt::correctPt(TLorentzVector &met, const TLorentzVector &raw, const TLorentzVector &p)
{
  double x = met.Px() + raw.Px() - p.Px();
  double y = met.Py() + raw.Py() - p.Py();
  met.SetXYZM(x,y,0,0);
}
void wwwAnalysis::MissingEt::initialize()
{
  bool is2012 = true;
  bool isSTVF = true;
  sm_pMETTool = new METUtility();
  sm_pMETTool->configMissingET(is2012,!isSTVF);


  sm_pMETSTVFTool = new METUtility();
  sm_pMETSTVFTool->configMissingET(is2012,isSTVF);
}
bool wwwAnalysis::MissingEt::initialized()
{
  return sm_pMETTool != 0;
}
double wwwAnalysis::MissingEt::Et() const
{
  return momentum().Pt();
}
double wwwAnalysis::MissingEt::phi() const
{
  return momentum().Phi();
}
TVector2 wwwAnalysis::MissingEt::pt() const
{
	TVector2 ret(momentum().Px(), momentum().Py());
  return ret;
}
double wwwAnalysis::MissingEt::Ex() const
{
  return momentum().Px();
}
double wwwAnalysis::MissingEt::Ey() const
{
  return momentum().Py();
}
double wwwAnalysis::MissingEt::sumEt() const
{
  return m_fSumEt;
}
double wwwAnalysis::MissingEt::sumEtRaw() const
{
  return m_fSumEtRaw;
}
double wwwAnalysis::MissingEt::sumEtSTVF() const
{
  return m_fSumEtSTVF;
}
const D3PDReader::RefFinalMETD3PDObject &wwwAnalysis::MissingEt::d3pd() const
{
  return *m_pD3PD;
}
