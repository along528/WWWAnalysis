#include "wwwAnalysis/Electron.h"

#include <egammaAnalysisUtils/CaloIsoCorrection.h>
#include <egammaAnalysisUtils/IsEMPlusPlusDefs.h>
#include <egammaEvent/egammaPIDdefs.h>
#include <cmath>

ClassImp( wwwAnalysis::Electron )

//eg2011::EnergyRescaler *wwwAnalysis::Electron::sm_pEnergyTool = 0;
egRescaler::EnergyRescalerUpgrade *wwwAnalysis::Electron::sm_pEnergyTool = 0;
Root::TElectronEfficiencyCorrectionTool *wwwAnalysis::Electron::sm_pSFTool_reco = 0;
Root::TElectronEfficiencyCorrectionTool *wwwAnalysis::Electron::sm_pSFTool_id = 0;
Root::TElectronLikelihoodTool   *wwwAnalysis::Electron::sm_pElectronLLTool = 0;

void wwwAnalysis::Electron::initialize()
{
  std::string pathRescaler = std::string(getenv("ROOTCOREDIR")) + "/../egammaAnalysisUtils/share/";
  std::string pathSF = std::string(getenv("ROOTCOREDIR")) + "/../ElectronEfficiencyCorrection/data/";
  std::string pathLikelihood = std::string(getenv("ROOTCOREDIR")) + "/../ElectronPhotonSelectorTools/data/";

  if(!sm_pEnergyTool)
  {
      //sm_pEnergyTool = new eg2011::EnergyRescaler();
      //sm_pEnergyTool->useDefaultCalibConstants("2012");
      sm_pEnergyTool = new egRescaler::EnergyRescalerUpgrade();
      sm_pEnergyTool->Init(pathRescaler+"EnergyRescalerData.root","2012","es2012");
      //sm_pEnergyTool->Init(pathRescaler+"EnergyRescalerData.root","2012","es2010");
      //sm_pEnergyTool->SetDebugFlag(true);
   }
  if(!sm_pSFTool_reco){
    sm_pSFTool_reco = new Root::TElectronEfficiencyCorrectionTool();
    //sm_pSFTool_reco->addFileName((pathSF+"efficiencySF.offline.RecoTrk.2012.8TeV.rel17p2.v05.root").c_str());
    sm_pSFTool_reco->addFileName((pathSF+"efficiencySF.offline.RecoTrk.2012.8TeV.rel17p2.GEO20.v08.root").c_str());
    sm_pSFTool_reco->initialize();
  }
  if(!sm_pSFTool_id){
    sm_pSFTool_id = new Root::TElectronEfficiencyCorrectionTool();
    //configurable???
    //sm_pSFTool_id->addFileName((pathSF+"efficiencySF.offline.Tight.2012.8TeV.rel17p2.v05.root").c_str());
    sm_pSFTool_id->addFileName((pathSF+"efficiencySF.offline.Tight.2012.8TeV.rel17p2.v07.root").c_str());
    //sm_pSFTool_id->addFileName((pathSF+"efficiencySF.offline.Medium.2012.8TeV.rel17p2.v02.root").c_str());
    sm_pSFTool_id->initialize();
  }

  if(!sm_pElectronLLTool){
  	sm_pElectronLLTool = new Root::TElectronLikelihoodTool();
	sm_pElectronLLTool->setPDFFileName((pathLikelihood+"ElectronLikelihoodPdfs.root").c_str());
	//set initial operating point
	sm_pElectronLLTool->setOperatingPoint(LikeEnum::Loose);
	sm_pElectronLLTool->initialize();
  }


}
bool wwwAnalysis::Electron::initialized()
{
	return sm_pEnergyTool && sm_pSFTool_reco && sm_pSFTool_id;
}
void wwwAnalysis::Electron::finalize()
{
  if(sm_pEnergyTool)
    delete sm_pEnergyTool;
  if(sm_pSFTool_reco)
    delete sm_pSFTool_reco;
  if(sm_pSFTool_id)
    delete sm_pSFTool_id;
  sm_pEnergyTool = 0;
  sm_pSFTool_reco = 0;
  sm_pSFTool_id = 0;

}
wwwAnalysis::Electron::Electron(){

}
wwwAnalysis::Electron::Electron(const D3PDReader::Event &event, int index, int nPV_2trks, int run, bool fake,wwwAnalysis::ElectronEnergyScaleSys energyScaleSys,wwwAnalysis::ElectronEnergySmearingSys energySmearingSys,double alternateEnergy)
  :PhysicsObject(event.eventinfo, ELECTRON, fake,index), m_pD3PD(&(event.el[index])), m_iRun(run)
{

	if(!initialized())
		initialize();
  double energy, eta, phi, correction;
  if(alternateEnergy>=0) energy = alternateEnergy;
  else energy = d3pd().cl_E();

  if(d3pd().nSiHits() + d3pd().nPixHits() >= 4)
  {
    eta = d3pd().tracketa();
    phi = d3pd().trackphi();
  }
  else
  {
    eta = d3pd().cl_eta();
    phi = d3pd().cl_phi();
  }
  
  
  //sm_pEnergyTool->SetRandomSeed(event.eventinfo.EventNumber()*100+index);
  correction=1.;
  sm_pEnergyTool->SetRandomSeed(1771561+event.eventinfo.EventNumber()+10*index);
  if(eventInfo().mc_channel_number.IsAvailable())
  {
    if(energySmearingSys==ElEnergySmearingUp)
    	correction = sm_pEnergyTool->getSmearingCorrection(d3pd().cl_eta(), energy, egRescaler::EnergyRescalerUpgrade::ERR_UP);
    else if(energySmearingSys==ElEnergySmearingDown)
    	correction = sm_pEnergyTool->getSmearingCorrection(d3pd().cl_eta(), energy, egRescaler::EnergyRescalerUpgrade::ERR_DOWN);
    else 
    	correction = sm_pEnergyTool->getSmearingCorrection(d3pd().cl_eta(), energy, egRescaler::EnergyRescalerUpgrade::Nominal);


    if(energyScaleSys!=ElectronEnergyScaleSysOff){
        //double deltaAlpha = sm_pEnergyTool->applyEnergyCorrection(d3pd().cl_eta(), energy,egRescaler::EnergyRescalerUpgrade::Electron,egRescaler::EnergyRescalerUpgrade::Nominal,1.,m_iRun)/energy;
	egRescaler::EnergyRescalerUpgrade::Variation var = egRescaler::EnergyRescalerUpgrade::Nominal;
	//symmetric energy scale variations
  	if(energyScaleSys == ElScaleZeeStatUp) var = egRescaler::EnergyRescalerUpgrade::ZeeStatUp;
	else if(energyScaleSys == ElScaleZeeStatDown) var = egRescaler::EnergyRescalerUpgrade::ZeeStatDown;
  	else if(energyScaleSys == ElScaleZeeMethUp) var = egRescaler::EnergyRescalerUpgrade::ZeeMethodUp;
	else if(energyScaleSys == ElScaleZeeMethDown) var = egRescaler::EnergyRescalerUpgrade::ZeeMethodDown;
  	else if(energyScaleSys == ElScaleZeeGenUp) var = egRescaler::EnergyRescalerUpgrade::ZeeGenUp;
	else if(energyScaleSys == ElScaleZeeGenDown) var = egRescaler::EnergyRescalerUpgrade::ZeeGenDown;
  	else if(energyScaleSys == ElScaleMaterialUp) var = egRescaler::EnergyRescalerUpgrade::R12StatUp;
	else if(energyScaleSys == ElScaleMaterialDown) var = egRescaler::EnergyRescalerUpgrade::R12StatDown;
  	else if(energyScaleSys == ElScalePresamplerUp) var = egRescaler::EnergyRescalerUpgrade::PSStatUp;
	else if(energyScaleSys == ElScalePresamplerDown) var = egRescaler::EnergyRescalerUpgrade::PSStatDown;
  	else if(energyScaleSys == ElScaleLowPtUp) var = egRescaler::EnergyRescalerUpgrade::LowPtUp;
	else if(energyScaleSys == ElScaleLowPtDown) var = egRescaler::EnergyRescalerUpgrade::LowPtDown;


        double deltaAlpha = sm_pEnergyTool->getAlphaUncertainty(d3pd().cl_eta(), energy,egRescaler::EnergyRescalerUpgrade::Electron,var,1.);//,1.,m_iRun);
	correction*= (1.+deltaAlpha);
    }//end energy scale systematics
    //correction =sm_pEnergyTool->getSmearingCorrectionMeV(d3pd().cl_eta(), d3pd().cl_E(), 0, false);
  }
  else{//data
    correction = sm_pEnergyTool->applyEnergyCorrection(d3pd().cl_eta(), energy,egRescaler::EnergyRescalerUpgrade::Electron,egRescaler::EnergyRescalerUpgrade::Nominal,1.,m_iRun)/energy;
  }
  //correction = sm_pEnergyTool->applyEnergyCorrectionMeV(d3pd().cl_eta(), d3pd().cl_phi(), d3pd().cl_E(), d3pd().cl_E()/cosh(d3pd().tracketa()), 0, "ELECTRON")/d3pd().cl_E();
//  correction *= sm_pEnergyTool->applyMCCalibrationMeV(d3pd().cl_eta(), energy/cosh(d3pd().tracketa()), "ELECTRON");

  TLorentzVector p;
  TLorentzVector raw;

  //smear energy and correct calorimeter Et cone
  double Et = energy/cosh(eta);
  p.SetPtEtaPhiM(Et*correction, eta, phi, 0);
  raw.SetPtEtaPhiM(Et, eta, phi, 0);
  
  setMomentum(p,raw);
  setCharge(d3pd().charge());
  
//  m_fEtCone20 = CaloIsoCorrection::GetPtNPVCorrectedIsolation(nPV_2trks, d3pd().cl_E(), d3pd().etas2(), d3pd().etap(), d3pd().cl_eta(), 20,
//                  eventInfo().mc_channel_number.IsAvailable(), d3pd().Etcone20(), false, CaloIsoCorrection::ELECTRON);
  //m_fEtCone20 = CaloIsoCorrection::GetPtNPVCorrectedIsolation(nPV_2trks, momentum().E(), d3pd().etas2(), d3pd().etap(), d3pd().cl_eta(), 20,
  m_fEtCone20 = CaloIsoCorrection::GetPtNPVCorrectedIsolation(nPV_2trks, energy, d3pd().etas2(), d3pd().etap(), d3pd().cl_eta(), 20,
                  eventInfo().mc_channel_number.IsAvailable(), d3pd().Etcone20(), false, CaloIsoCorrection::ELECTRON);

  Et = energy/cosh(d3pd().etas2());
	m_bTightPP = m_bMediumPP = m_bLoosePP =
								isTightPlusPlus( d3pd().etas2(), Et, d3pd().f3(), d3pd().Ethad()/Et, d3pd().Ethad1()/Et,
                                d3pd().reta(), d3pd().weta2(), d3pd().f1(), d3pd().wstot(),
                                (d3pd().emaxs1()+d3pd().Emax2()) > 0 ? (d3pd().emaxs1() - d3pd().Emax2()) / (d3pd().emaxs1() + d3pd().Emax2()) : 0,
                                d3pd().deltaeta1(), d3pd().trackd0_physics(),
                                d3pd().TRTHighTOutliersRatio(), d3pd().nTRTHits(), d3pd().nTRTOutliers(),
                                d3pd().nSiHits(), d3pd().nSCTOutliers() + d3pd().nPixelOutliers(),
                                d3pd().nPixHits(), d3pd().nPixelOutliers(), d3pd().nBLHits(), d3pd().nBLayerOutliers(),
                                d3pd().expectHitInBLayer(), energy*fabs(d3pd().trackqoverp()),d3pd().deltaphi2(),
                                (d3pd().isEM() & (1 << egammaPID::ConversionMatch_Electron)),
                                egammaMenu::eg2012, false, false);
  if(!m_bMediumPP)
    m_bMediumPP = m_bLoosePP =
    						isMediumPlusPlus( d3pd().etas2(), Et, d3pd().f3(), d3pd().Ethad()/Et, d3pd().Ethad1()/Et,
                                d3pd().reta(), d3pd().weta2(), d3pd().f1(), d3pd().wstot(),
                                (d3pd().emaxs1()+d3pd().Emax2()) > 0 ? (d3pd().emaxs1() - d3pd().Emax2()) / (d3pd().emaxs1() + d3pd().Emax2()) : 0,
                                d3pd().deltaeta1(), d3pd().trackd0_physics(),
                                d3pd().TRTHighTOutliersRatio(), d3pd().nTRTHits(), d3pd().nTRTOutliers(),
                                d3pd().nSiHits(), d3pd().nSCTOutliers() + d3pd().nPixelOutliers(),
                                d3pd().nPixHits(), d3pd().nPixelOutliers(), d3pd().nBLHits(), d3pd().nBLayerOutliers(),
                                d3pd().expectHitInBLayer(),
                                egammaMenu::eg2012, false, false);
	if(!m_bLoosePP)
    m_bLoosePP = isLoosePlusPlus( d3pd().etas2(), Et, d3pd().Ethad()/Et, d3pd().Ethad1()/Et,
                                d3pd().reta(), d3pd().weta2(), d3pd().f1(), d3pd().wstot(),
                                (d3pd().emaxs1()+d3pd().Emax2()) > 0 ? (d3pd().emaxs1() - d3pd().Emax2()) / (d3pd().emaxs1() + d3pd().Emax2()) : 0,
                                d3pd().deltaeta1(),
                                d3pd().nSiHits(), d3pd().nSCTOutliers() + d3pd().nPixelOutliers(),
                                d3pd().nPixHits(), d3pd().nPixelOutliers(),
                                egammaMenu::eg2012, false, false);
	double ip = 0;
	for (int i = 0;i<event.vxp.n();i++){
		if (event.vxp[i].trk_n()>=2) ip+=1;
	}

	//Calculate dpOverp
	double deltaPoverP = 0.;
	vector<int> author = d3pd().refittedTrack_author();
	vector<float> qoverp = d3pd().refittedTrack_LMqoverp();
	unsigned int trackn = d3pd().refittedTrack_n();
	for(unsigned int i=0;i<trackn;i++){
		if((author[i]==4)){
			float num = d3pd().trackqoverp();
			float denom = qoverp.at(i);
			deltaPoverP = 1. - ( num/denom);
		}
	}

	double discriminant;


	//Electron Likelihood VeryLoose
	sm_pElectronLLTool->setOperatingPoint(LikeEnum::VeryLoose);
	discriminant = sm_pElectronLLTool->calculate(d3pd().etas2(),Et,d3pd().f3(),d3pd().Ethad()/Et,d3pd().Ethad1()/Et,
			        	  d3pd().reta(),d3pd().weta2(),d3pd().f1(),
				          (d3pd().emaxs1()+d3pd().Emax2()) > 0 
					  	? (d3pd().emaxs1() - d3pd().Emax2()) / (d3pd().emaxs1() + d3pd().Emax2()) : 0,
					  d3pd().deltaeta1(),d3pd().trackd0pvunbiased(),d3pd().TRTHighTOutliersRatio(),
					  d3pd().tracksigd0pvunbiased(),d3pd().rphi(), deltaPoverP,d3pd().deltaphiRescaled(),ip);
	m_bVeryLooseLL = sm_pElectronLLTool->accept(discriminant,d3pd().etas2(),Et,d3pd().nSiHits(),
					 d3pd().nPixelDeadSensors()+d3pd().nSCTDeadSensors(),d3pd().nPixHits(),
					 d3pd().nPixelDeadSensors(),d3pd().nBLHits(),d3pd().nBLayerOutliers(), 
					 (d3pd().expectHitInBLayer()==-999 ? true : false),d3pd().isEM() & (0x1 << 1),ip);

	//Electron Likelihood Loose
	sm_pElectronLLTool->setOperatingPoint(LikeEnum::Loose);
	discriminant = sm_pElectronLLTool->calculate(d3pd().etas2(),Et,d3pd().f3(),d3pd().Ethad()/Et,d3pd().Ethad1()/Et,
			        	  d3pd().reta(),d3pd().weta2(),d3pd().f1(),
				          (d3pd().emaxs1()+d3pd().Emax2()) > 0 
					  	? (d3pd().emaxs1() - d3pd().Emax2()) / (d3pd().emaxs1() + d3pd().Emax2()) : 0,
					  d3pd().deltaeta1(),d3pd().trackd0pvunbiased(),d3pd().TRTHighTOutliersRatio(),
					  d3pd().tracksigd0pvunbiased(),d3pd().rphi(), deltaPoverP,d3pd().deltaphiRescaled(),ip);
	m_bLooseLL = sm_pElectronLLTool->accept(discriminant,d3pd().etas2(),Et,d3pd().nSiHits(),
					 d3pd().nPixelDeadSensors()+d3pd().nSCTDeadSensors(),d3pd().nPixHits(),
					 d3pd().nPixelDeadSensors(),d3pd().nBLHits(),d3pd().nBLayerOutliers(), 
					 (d3pd().expectHitInBLayer()==-999 ? true : false),d3pd().isEM() & (0x1 << 1),ip);

	//Electron Likelihood Medium
	sm_pElectronLLTool->setOperatingPoint(LikeEnum::Medium);
	discriminant = sm_pElectronLLTool->calculate(d3pd().etas2(),Et,d3pd().f3(),d3pd().Ethad()/Et,d3pd().Ethad1()/Et,
			        	  d3pd().reta(),d3pd().weta2(),d3pd().f1(),
				          (d3pd().emaxs1()+d3pd().Emax2()) > 0 
					  	? (d3pd().emaxs1() - d3pd().Emax2()) / (d3pd().emaxs1() + d3pd().Emax2()) : 0,
					  d3pd().deltaeta1(),d3pd().trackd0pvunbiased(),d3pd().TRTHighTOutliersRatio(),
					  d3pd().tracksigd0pvunbiased(),d3pd().rphi(), deltaPoverP,d3pd().deltaphiRescaled(),ip);
	m_bMediumLL = sm_pElectronLLTool->accept(discriminant,d3pd().etas2(),Et,d3pd().nSiHits(),
					 d3pd().nPixelDeadSensors()+d3pd().nSCTDeadSensors(),d3pd().nPixHits(),
					 d3pd().nPixelDeadSensors(),d3pd().nBLHits(),d3pd().nBLayerOutliers(), 
					 (d3pd().expectHitInBLayer()==-999 ? true : false),d3pd().isEM() & (0x1 << 1),ip);

	//Electron Likelihood Tight
	sm_pElectronLLTool->setOperatingPoint(LikeEnum::Tight);
	discriminant = sm_pElectronLLTool->calculate(d3pd().etas2(),Et,d3pd().f3(),d3pd().Ethad()/Et,d3pd().Ethad1()/Et,
			        	  d3pd().reta(),d3pd().weta2(),d3pd().f1(),
				          (d3pd().emaxs1()+d3pd().Emax2()) > 0 
					  	? (d3pd().emaxs1() - d3pd().Emax2()) / (d3pd().emaxs1() + d3pd().Emax2()) : 0,
					  d3pd().deltaeta1(),d3pd().trackd0pvunbiased(),d3pd().TRTHighTOutliersRatio(),
					  d3pd().tracksigd0pvunbiased(),d3pd().rphi(), deltaPoverP,d3pd().deltaphiRescaled(),ip);
	m_bTightLL = sm_pElectronLLTool->accept(discriminant,d3pd().etas2(),Et,d3pd().nSiHits(),
					 d3pd().nPixelDeadSensors()+d3pd().nSCTDeadSensors(),d3pd().nPixHits(),
					 d3pd().nPixelDeadSensors(),d3pd().nBLHits(),d3pd().nBLayerOutliers(), 
					 (d3pd().expectHitInBLayer()==-999 ? true : false),d3pd().isEM() & (0x1 << 1),ip);
	//Electron Likelihood VeryTight
	sm_pElectronLLTool->setOperatingPoint(LikeEnum::VeryTight);
	discriminant = sm_pElectronLLTool->calculate(d3pd().etas2(),Et,d3pd().f3(),d3pd().Ethad()/Et,d3pd().Ethad1()/Et,
			        	  d3pd().reta(),d3pd().weta2(),d3pd().f1(),
				          (d3pd().emaxs1()+d3pd().Emax2()) > 0 
					  	? (d3pd().emaxs1() - d3pd().Emax2()) / (d3pd().emaxs1() + d3pd().Emax2()) : 0,
					  d3pd().deltaeta1(),d3pd().trackd0pvunbiased(),d3pd().TRTHighTOutliersRatio(),
					  d3pd().tracksigd0pvunbiased(),d3pd().rphi(), deltaPoverP,d3pd().deltaphiRescaled(),ip);
	m_bVeryTightLL = sm_pElectronLLTool->accept(discriminant,d3pd().etas2(),Et,d3pd().nSiHits(),
					 d3pd().nPixelDeadSensors()+d3pd().nSCTDeadSensors(),d3pd().nPixHits(),
					 d3pd().nPixelDeadSensors(),d3pd().nBLHits(),d3pd().nBLayerOutliers(), 
					 (d3pd().expectHitInBLayer()==-999 ? true : false),d3pd().isEM() & (0x1 << 1),ip);

		
      m_bIsSignalLike = false;
      m_bIsFromHeavyFlavor =  false;
      m_bIsFromLightFlavor =  false;
      m_bIsFromPhotonConversion =  false;
      int channel = -1;
      if(eventInfo().mc_channel_number.IsAvailable()) channel=eventInfo().mc_channel_number();
      if(d3pd().type.IsAvailable() && d3pd().typebkg.IsAvailable() && d3pd().originbkg.IsAvailable()){
      	m_bIsSignalLike = isTrueElecMatch(channel,d3pd().type(),d3pd().typebkg(),d3pd().originbkg(),1);
      	m_bIsFromHeavyFlavor =isTrueElecMatch(channel,d3pd().type(),d3pd().typebkg(),d3pd().originbkg(),2);
      	m_bIsFromPhotonConversion = isTrueElecMatch(channel,d3pd().type(),d3pd().typebkg(),d3pd().originbkg(),3);
      	m_bIsFromLightFlavor = isTrueElecMatch(channel,d3pd().type(),d3pd().typebkg(),d3pd().originbkg(),4);
      }

}

double wwwAnalysis::Electron::scaleFactor(wwwAnalysis::ElectronEffSys effSys) const
{
  //enum ElectronSys { ElRecoEffUp,ElRecoEffDown,ElIDEffUp,ElIDEffDown,ElectronSysOff }; 
//  std::cout << m_iRun << "\t" << d3pd().cl_eta()<< "\t"<<momentum().Pt() << std::endl;
  const Root::TResult &result_reco = sm_pSFTool_reco->calculate(PATCore::ParticleDataType::Full,m_iRun,d3pd().cl_eta(),momentum().Pt());
  const Root::TResult &result_tight = sm_pSFTool_id->calculate(PATCore::ParticleDataType::Full,m_iRun,d3pd().cl_eta(),momentum().Pt());
  double reco_sf = result_reco.getScaleFactor();
  double id_sf   = result_tight.getScaleFactor();
  
  if(effSys == ElRecoEffUp) 	   reco_sf+=result_reco.getTotalUncertainty();
  else if(effSys == ElRecoEffDown) reco_sf-=result_reco.getTotalUncertainty();
  else if(effSys == ElIDEffUp)     id_sf+=result_tight.getTotalUncertainty();
  else if(effSys == ElIDEffDown)   id_sf-=result_tight.getTotalUncertainty();



  return reco_sf*id_sf;
  //return result_reco.getScaleFactor()*result_tight.getScaleFactor();
//  return getIdScaleFactor(4);
}
bool wwwAnalysis::Electron::loose() const
{
  return m_bLoosePP;
}
bool wwwAnalysis::Electron::medium() const
{
  return m_bMediumPP;
}

bool wwwAnalysis::Electron::tight() const
{
  return m_bTightPP;
}

bool wwwAnalysis::Electron::veryLooseLL() const
{
  return m_bVeryLooseLL;
}
bool wwwAnalysis::Electron::looseLL() const
{
  return m_bLooseLL;
}
bool wwwAnalysis::Electron::mediumLL() const
{
  return m_bMediumLL;
}
bool wwwAnalysis::Electron::tightLL() const
{
  return m_bTightLL;
}
bool wwwAnalysis::Electron::veryTightLL() const
{
  return m_bVeryTightLL;
}



bool wwwAnalysis::Electron::isSignalLike() const
{
  return m_bIsSignalLike;
}
bool wwwAnalysis::Electron::isFromHeavyFlavor() const
{
  return m_bIsFromHeavyFlavor;
}
bool wwwAnalysis::Electron::isFromLightFlavor() const
{
  return m_bIsFromLightFlavor;
}
bool wwwAnalysis::Electron::isFromPhotonConversion() const
{
  return m_bIsFromPhotonConversion;
}


float wwwAnalysis::Electron::Etcone20_corr() const
{
  return m_fEtCone20;
}
const D3PDReader::ElectronD3PDObjectElement &wwwAnalysis::Electron::d3pd() const
{
  return *m_pD3PD;
}
