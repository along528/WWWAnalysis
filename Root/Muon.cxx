#include "wwwAnalysis/Muon.h"

ClassImp( wwwAnalysis::Muon )

MuonSmear::SmearingClass *wwwAnalysis::Muon::sm_pStacoSmearingTool = 0;
MuonSmear::SmearingClass *wwwAnalysis::Muon::sm_pThirdMuSmearingTool = 0;
Analysis::AnalysisMuonConfigurableScaleFactors *wwwAnalysis::Muon::sm_pStacoSFTool = 0;
Analysis::AnalysisMuonConfigurableScaleFactors *wwwAnalysis::Muon::sm_pThirdMuSFTool = 0;
CorrectCaloIso *wwwAnalysis::Muon::sm_pCorrectIsoTool = 0;



void wwwAnalysis::Muon::initialize()
{
  std::string pathTrig = std::string(getenv("ROOTCOREDIR")) + "/../HSG4LepLepTriggerSF/data/";
  std::string pathSF = std::string(getenv("ROOTCOREDIR")) + "/../MuonEfficiencyCorrections/share/";
  std::string pathSmear = std::string(getenv("ROOTCOREDIR")) + "/../MuonMomentumCorrections/share/";

	if(!sm_pStacoSmearingTool)
	{
  	//sm_pStacoSmearingTool = new MuonSmear::SmearingClass("Data12", "staco", "pT", "Rel17.2Repro",pathSmear.c_str());
  	sm_pStacoSmearingTool = new MuonSmear::SmearingClass("Data12", "staco", "pT", "Rel17.2Sum13",pathSmear.c_str());
	  sm_pStacoSmearingTool->UseScale(1);
  	sm_pStacoSmearingTool->UseImprovedCombine();
	}


	if(!sm_pThirdMuSmearingTool)
	{
  	//sm_pThirdMuSmearingTool = new MuonSmear::SmearingClass("Data12", "muons", "pT", "Rel17.2Repro",pathSmear.c_str());
  	sm_pThirdMuSmearingTool = new MuonSmear::SmearingClass("Data12", "muons", "pT", "Rel17.2Sum13",pathSmear.c_str());
	  sm_pThirdMuSmearingTool->UseScale(1);
  	sm_pThirdMuSmearingTool->UseImprovedCombine();
// *** NOT AVAILABLE FOR 2012 DATA CORRECTIONS
//  	SmearingTool->RestrictCurvatureCorrections(2.5);
//  	SmearingTool->FillScales("KC");
	}

	if(!sm_pCorrectIsoTool)
	  sm_pCorrectIsoTool = new CorrectCaloIso();

	if(!sm_pStacoSFTool)
	{
	  //sm_pSFTool = new Analysis::AnalysisMuonConfigurableScaleFactors(pathSF.c_str(), "STACO_CB_plus_ST_2012_SF.txt","MeV",Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverRuns);
	  std::string config_file = "STACO_CB_2012_SF.txt.gz";
	  sm_pStacoSFTool = new Analysis::AnalysisMuonConfigurableScaleFactors(pathSF.c_str(), config_file.c_str(),"MeV",Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverPeriods);
  	  sm_pStacoSFTool->Initialise();
  	}
	if(!sm_pThirdMuSFTool)
	{
	  std::string config_file = "MuonsChain_CB_2012_SF.txt.gz";
	  sm_pThirdMuSFTool = new Analysis::AnalysisMuonConfigurableScaleFactors(pathSF.c_str(), config_file.c_str(),"MeV",Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverPeriods);
  	  sm_pThirdMuSFTool->Initialise();
	}
}
bool wwwAnalysis::Muon::initialized()
{
	return sm_pStacoSmearingTool && sm_pThirdMuSmearingTool && sm_pCorrectIsoTool && sm_pStacoSFTool && sm_pThirdMuSFTool;
	//return sm_pStacoSmearingTool && sm_pThirdMuSmearingTool && sm_pCorrectIsoTool && sm_pThirdMuSFTool;
	//return sm_pStacoSmearingTool && sm_pThirdMuSmearingTool && sm_pCorrectIsoTool; 
}
void wwwAnalysis::Muon::finalize()
{
	if(sm_pStacoSmearingTool)
		delete sm_pStacoSmearingTool;
	if(sm_pThirdMuSmearingTool)
		delete sm_pThirdMuSmearingTool;
	if(sm_pCorrectIsoTool)
		delete sm_pCorrectIsoTool;
	if(sm_pStacoSFTool)
		delete sm_pStacoSFTool;
	if(sm_pThirdMuSFTool)
		delete sm_pThirdMuSFTool;
	sm_pStacoSmearingTool = 0;
	sm_pThirdMuSmearingTool = 0;
	sm_pCorrectIsoTool = 0;
	sm_pStacoSFTool = 0;
	sm_pThirdMuSFTool = 0;
}
wwwAnalysis::Muon::Muon(){

}
wwwAnalysis::Muon::Muon(const D3PDReader::Event &event, int index,bool use_third_chain, int nPV_3trks,bool fake,wwwAnalysis::MuonMomSys momSys)
//  :PhysicsObject(event.eventinfo,MUON, fake), m_pD3PD(&(event.mu_staco[index]))
    :PhysicsObject(event.eventinfo,MUON, fake,index),m_bUseThirdChainMuon(use_third_chain)
{

  if(m_bUseThirdChainMuon) {
  	m_pD3PD = (&(event.mu[index]));
  }
  else {
  	m_pD3PD = (&(event.mu_staco[index]));
  }



  if(!initialized()) initialize();

  MuonSmear::SmearingClass *SmearingTool = NULL;
  if(m_bUseThirdChainMuon) {
	SmearingTool = sm_pThirdMuSmearingTool;
  }
  else {
	SmearingTool = sm_pStacoSmearingTool;
  }
  double smear = 1;
  double ptms = sin(d3pd().ms_theta())*fabs(1.0/d3pd().ms_qoverp());
  //double ptme = sin(d3pd().me_theta())*fabs(1.0/d3pd().me_qoverp());
  double ptid = sin(d3pd().id_theta())*fabs(1.0/d3pd().id_qoverp());
  m_fPtMS = ptms;
  if(eventInfo().mc_channel_number.IsAvailable())
  {
    std::string variation = "";
    if(momSys==IDUP) variation = "IDUP";
    if(momSys==IDLOW) variation = "IDLOW";
    else if(momSys==MSUP) variation = "MSUP";
    else if(momSys==MSLOW) variation = "MSLOW";
    else if(momSys==SCALEUP) variation = "SCALEUP";
    else if(momSys==SCALELOW) variation = "SCALELOW";

    SmearingTool->SetSeed(eventInfo().EventNumber(),index);
    if(d3pd().isCombinedMuon())
    {
      //Taken to Match Ruiqi.  Used ptms directly instead of mix of ptme and ptms
      if( abs(d3pd().eta()) < 2.7){
	      SmearingTool->Event(ptms, ptid, d3pd().pt(), d3pd().eta(), d3pd().charge(),d3pd().phi());
	      double pTCB_smeared = SmearingTool->pTCB();
	      double pTMS_smeared = SmearingTool->pTMS();
	      double pTID_smeared = SmearingTool->pTID();

	      if(momSys != MuonMomSysOff) SmearingTool->PTVar(pTMS_smeared,pTID_smeared,pTCB_smeared,variation);
	      //smear = SmearingTool->pTCB()/d3pd().pt();
	      smear = pTCB_smeared/d3pd().pt();
	      //No longer need to rescale to ptms
	      m_fPtMS = pTMS_smeared;
      }
    }
    else if(d3pd().isSegmentTaggedMuon())
    {
      if( abs(d3pd().eta()) < 2.7){

	      SmearingTool->Event(d3pd().pt(), d3pd().eta(), "ID", d3pd().charge(),d3pd().phi());
	      double pTCB_smeared = SmearingTool->pTCB();
	      double pTMS_smeared = SmearingTool->pTMS();
	      double pTID_smeared = SmearingTool->pTID();
	      if(momSys != MuonMomSysOff) SmearingTool->PTVar(pTMS_smeared,pTID_smeared,pTCB_smeared,variation);
	      smear = pTID_smeared/d3pd().pt();
      }
    }
    else if(d3pd().isStandAloneMuon())
    {
      double eta = -log(tan(d3pd().ms_theta()/2.0));
      if (abs(eta) < 2.7) {
	      SmearingTool->Event(ptms, eta, "MS", d3pd().ms_qoverp() > 0 ? 1 : -1,d3pd().phi());
	      double pTCB_smeared = SmearingTool->pTCB();
	      double pTMS_smeared = SmearingTool->pTMS();
	      double pTID_smeared = SmearingTool->pTID();
	      if(momSys != MuonMomSysOff) SmearingTool->PTVar(pTMS_smeared,pTID_smeared,pTCB_smeared,variation);
	      smear = pTMS_smeared / ptms;
	      m_fPtMS = pTMS_smeared ;
      }
    }
  }
  TLorentzVector p,raw;
  if (smear!=smear || smear<=0) smear = 1.;  //check if smearing returns NaN
  //std::cout << d3pd().pt() << "\t" << smear << "\t" << d3pd().eta() << "\t" << d3pd().phi() << "\t"  <<d3pd().E() << std::endl;

  p.SetPtEtaPhiE(d3pd().pt()*smear, d3pd().eta(), d3pd().phi(), d3pd().E()*smear);
  raw.SetPtEtaPhiE(d3pd().pt(), d3pd().eta(), d3pd().phi(), d3pd().E());
  
  setMomentum(p, raw);
  setCharge(d3pd().charge());

  //m_fEtCone20 = sm_pCorrectIsoTool->CorrectEtCone(d3pd().etcone20(), nPV_3trks, momentum().Eta(), "cone20Comb");
  m_fEtCone20 = sm_pCorrectIsoTool->CorrectEtCone(d3pd().etcone20(), nPV_3trks, momentum().Eta(), "cone20Comb2012");


  m_bIsSpectroMuon = false;
  for(unsigned int j=0;j< event.mu_staco_MET[index].statusWord().size();j++)
    		m_bIsSpectroMuon = m_bIsSpectroMuon  || (event.mu_staco_MET[index].statusWord().at(j) & 0x0002); //SPECTRO CODE

  m_bIsSignalLike = false;
  m_bIsFromHeavyFlavor =  false;
  m_bIsFromLightFlavor =  false;
  m_bIsFromPhotonConversion =  false;
  int channel = -1;
  if(eventInfo().mc_channel_number.IsAvailable()) channel=eventInfo().mc_channel_number();
  if(d3pd().type.IsAvailable() ){
      	m_bIsSignalLike = isTrueMuonMatch(channel,d3pd().type(),1);
      	m_bIsFromHeavyFlavor = isTrueMuonMatch(channel,d3pd().type(),2);
      	m_bIsFromPhotonConversion = isTrueMuonMatch(channel,d3pd().type(),3);
      	m_bIsFromLightFlavor = isTrueMuonMatch(channel,d3pd().type(),4);
  }
}
double wwwAnalysis::Muon::scaleFactor(wwwAnalysis::MuonEffSys variation) const
{
  
  Analysis::AnalysisMuonConfigurableScaleFactors *SFTool = NULL;
  if (m_bUseThirdChainMuon) SFTool = sm_pThirdMuSFTool;
  else SFTool = sm_pStacoSFTool;
  //SFTool = sm_pStacoSFTool;

  double sf = SFTool->scaleFactor(charge(), rawMomentum());
  if (variation==wwwAnalysis::MuonEffUp || variation == wwwAnalysis::MuonEffDown){
  	double sf_stat_error=SFTool->scaleFactorUncertainty(charge(),rawMomentum());
  	double sf_syst_error=SFTool->scaleFactorSystematicUncertainty(charge(),rawMomentum());
  	double sf_total_error=sqrt(pow(sf_stat_error,2)+pow(sf_syst_error,2)); 
	if(variation==wwwAnalysis::MuonEffUp) sf += sf_total_error;
	else if(variation==wwwAnalysis::MuonEffDown) sf -= sf_total_error;

  }
  return sf;
}
float wwwAnalysis::Muon::ptms() const
{
  return m_fPtMS;
}
float wwwAnalysis::Muon::Etcone20_corr() const
{
  return m_fEtCone20;
}
bool wwwAnalysis::Muon::useThirdChain() const
{
  return m_bUseThirdChainMuon;
}
bool wwwAnalysis::Muon::isSpectroMuon() const
{
  return m_bIsSpectroMuon;
}

bool wwwAnalysis::Muon::isSignalLike() const
{
  return m_bIsSignalLike;
}
bool wwwAnalysis::Muon::isFromHeavyFlavor() const
{
  return m_bIsFromHeavyFlavor;
}
bool wwwAnalysis::Muon::isFromLightFlavor() const
{
  return m_bIsFromLightFlavor;
}
bool wwwAnalysis::Muon::isFromPhotonConversion() const
{
  return m_bIsFromPhotonConversion;
}


const D3PDReader::MuonD3PDObjectElement &wwwAnalysis::Muon::d3pd() const
{
  return *m_pD3PD;
}
//New function to get the SF from external tool:
double wwwAnalysis::Muon::GetScaleFactor(int p_charge, const TLorentzVector& p_rawMomentum)
{
	return 1.;
	/*
//Since it is run independently of the objet, let's initilize the tool if it was not already the case:
	if(!sm_pStacoSFTool)
	{
	  std::string pathSF = std::string(getenv("ROOTCOREDIR")) + "/../MuonEfficiencyCorrections/share/";
	  std::string config_file = "STACO_CB_2012_SF.txt.gz";
	  sm_pStacoSFTool = new Analysis::AnalysisMuonConfigurableScaleFactors(pathSF.c_str(), config_file.c_str(),"MeV",Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverPeriods);
  	sm_pStacoSFTool->Initialise();
  }
	if(!sm_pThirdMuSFTool)
	{
	  std::string pathSF = std::string(getenv("ROOTCOREDIR")) + "/../MuonEfficiencyCorrections/share/";
	  std::string config_file = "MuonsChain_CB_2012_SF.txt.gz";
	  sm_pThirdMuSFTool = new Analysis::AnalysisMuonConfigurableScaleFactors(pathSF.c_str(), config_file.c_str(),"MeV",Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverPeriods);
  	sm_pThirdMuSFTool->Initialise();
  }

  Analysis::AnalysisMuonConfigurableScaleFactors *SFTool = NULL;
  if (m_bUseThirdChainMuon) SFTool = sm_pThirdMuSFTool;
  else SFTool = sm_pStacoSFTool;
  //SFTool = sm_pStacoSFTool;

  return SFTool->scaleFactor(p_charge, p_rawMomentum);
  */
}

//bool wwwAnalysis::Muon::isTag() const
//{
////bool pass=false;

//if(this->momentum().Pt()<15000) return false;
//if(fabs(this->momentum().Eta())>2.4)return false;
//if(d3pd().author()!=6)return false;
//if(!d3pd().tight()) return false;
//if(!(d3pd().expectBLayerHit() == 0 || d3pd().nBLHits() > bLayerHitsMin)) return false;
//if(!(d3pd().nPixHits() + d3pd().nPixelDeadSensors() > pixelHitsMin)) return false;
//if(!(d3pd().nSCTHits() + d3pd().nSCTDeadSensors() > SCTHitsMin)) return false;
//if(!(d3pd().nPixHoles() + d3pd().nSCTHoles() < SiHolesMax)) return false;

////if(!()) return false;
////if(!()) return false;
////if(!()) return false;


//if(!(fabs(d3pd().id_z0_exPV()) < z0ExpPVMax )) return false;
//if(!(d3pd().ptcone40()/pt< PtIsoMax&& d3pd().ptcone40()/pt > PtIsoMin)) return false;
//if(!(this->Etcone20_corr()/pt < EtIsoMax )) return false;

//return true;

////  // Cut TRT
////  double nTRT = data.nTRTHits() + data.nTRTOutliers();
////  if((0.1 < fabs(eta)) && (fabs(eta) < 1.9))
////    m_accept.setCutResult( m_cutPositionTRT, (nTRT > TRTHitsMin) && (data.nTRTOutliers() < 0.9*nTRT));
////  else if(nTRT > TRTHitsMin)
////    m_accept.setCutResult( m_cutPositionTRT, data.nTRTOutliers() < 0.9*nTRT);
////  else
////    m_accept.setCutResult( m_cutPositionTRT, true);

////  // Cut ptMin
////  m_accept.setCutResult( m_cutPositionPtMin, ( pt > ptMin) ? true : false );
////  
////  // Cut z0ExpPVMax
////  m_accept.setCutResult( m_cutPositionz0ExpPVMax, ( fabs(data.id_z0_exPV()) < z0ExpPVMax ) ? true : false );




////  double eta = muon.momentum().Eta();
////  double pt = muon.momentum().Pt();

////  // Cut Staco *** Should already be STACO
////  m_accept.setCutResult( m_cutPositionStaco, true );//(data.author() == 6) ? true : false );

////  // Cut etaMax
////  m_accept.setCutResult( m_cutPositionEtaMax, ( fabs(eta) < etaMax ) ? true : false );
////  
////  // Cut Staco Loose
////  m_accept.setCutResult( m_cutPositionStacoLoose, data.loose() || !stacoLoose);
////  
////  // Cut Staco Medium
////  m_accept.setCutResult( m_cutPositionStacoMedium, data.medium() || !stacoMedium);
////  
////  // Cut Staco Tight
////  m_accept.setCutResult( m_cutPositionStacoTight, data.tight() || !stacoTight);
////  
////  // Cut bLayerHitsMin
////  m_accept.setCutResult( m_cutPositionBLayerHitsMin, data.expectBLayerHit() == 0 || data.nBLHits() > bLayerHitsMin);
////  
////  // Cut pixelHitsMin
////  m_accept.setCutResult( m_cutPositionPixelHitsMin, data.nPixHits() + data.nPixelDeadSensors() > pixelHitsMin);
////  
////  // Cut SCTHitsMin
////  m_accept.setCutResult( m_cutPositionSCTHitsMin, data.nSCTHits() + data.nSCTDeadSensors() > SCTHitsMin);
////  
////  // Cut SiHolesMax
////  m_accept.setCutResult( m_cutPositionSiHolesMax, data.nPixHoles() + data.nSCTHoles() < SiHolesMax);
////  
////  // Cut TRT
////  double nTRT = data.nTRTHits() + data.nTRTOutliers();
////  if((0.1 < fabs(eta)) && (fabs(eta) < 1.9))
////    m_accept.setCutResult( m_cutPositionTRT, (nTRT > TRTHitsMin) && (data.nTRTOutliers() < 0.9*nTRT));
////  else if(nTRT > TRTHitsMin)
////    m_accept.setCutResult( m_cutPositionTRT, data.nTRTOutliers() < 0.9*nTRT);
////  else
////    m_accept.setCutResult( m_cutPositionTRT, true);

////  // Cut ptMin
////  m_accept.setCutResult( m_cutPositionPtMin, ( pt > ptMin) ? true : false );
////  
////  // Cut z0ExpPVMax
////  m_accept.setCutResult( m_cutPositionz0ExpPVMax, ( fabs(data.id_z0_exPV()) < z0ExpPVMax ) ? true : false );

////  // Cut PtIsoMax
////  double ptiso = data.ptcone40()/pt;
////  m_accept.setCutResult( m_cutPositionPtIso, ( ptiso < PtIsoMax && ptiso > PtIsoMin ) ? true : false );
////  
////  // Cut EtIsoMax
////  m_accept.setCutResult( m_cutPositionEtIsoMax, ( muon.Etcone20_corr()/pt < EtIsoMax ) ? true : false );


//if()

//  return sm_pSFTool->scaleFactor(charge(), rawMomentum());
//}

//bool wwwAnalysis::Muon::isProb() const
//{
//  return sm_pSFTool->scaleFactor(charge(), rawMomentum());
//}
