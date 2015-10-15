#include "wwwAnalysis/Jet.h"

#include "TLorentzVector.h"

#include <string>
#include <iostream>
#include <vector>

ClassImp( wwwAnalysis::Jet )

JetAnalysisCalib::JetCalibrationTool *wwwAnalysis::Jet::sm_pDataCalibrationTool = 0;
JetAnalysisCalib::JetCalibrationTool *wwwAnalysis::Jet::sm_pMC12aCalibrationTool = 0;
JetAnalysisCalib::JetCalibrationTool *wwwAnalysis::Jet::sm_pMC12bFullSimCalibrationTool = 0;
JetAnalysisCalib::JetCalibrationTool *wwwAnalysis::Jet::sm_pMC12bAFIICalibrationTool = 0;
::Analysis::CalibrationDataInterfaceROOT *wwwAnalysis::Jet::sm_pBJetScalingTool = 0;
JESUncertaintyProvider *wwwAnalysis::Jet::sm_pMC12aJESUncertaintyTool = 0;
MultijetJESUncertaintyProvider *wwwAnalysis::Jet::sm_pMC12aMultijetJESUncertaintyTool = 0;
JVFUncertaintyTool *wwwAnalysis::Jet::sm_pJVFUncTool = 0; 
//JERProvider *wwwAnalysis::Jet::sm_pJERTool = 0;
JetSmearingTool *wwwAnalysis::Jet::sm_pJERSmearingTool = 0;
//TRandom *wwwAnalysis::Jet::sm_pRandom = 0;

void wwwAnalysis::Jet::initialize()
{
  std::string jetconfig_mc12a_and_data12 = std::string(getenv("ROOTCOREDIR")) + "/../ApplyJetCalibration/data/CalibrationConfigs/JES_Full2012dataset_Preliminary_Jan13.config";
  std::string jetconfig_mc12b_fullsim = std::string(getenv("ROOTCOREDIR")) + "/../ApplyJetCalibration/data/CalibrationConfigs/JES_Full2012dataset_Preliminary_MC12b_Sep23.config";
  std::string jetconfig_mc12b_afII = std::string(getenv("ROOTCOREDIR")) + "/../ApplyJetCalibration/data/CalibrationConfigs/JES_Full2012dataset_Preliminary_MC12b_AFII_Sep23.config";
  std::string jetunc_path = std::string(getenv("ROOTCOREDIR")) + "/data/JetUncertainties";
  std::string jer_file = std::string(getenv("ROOTCOREDIR")) + "/data/JetResolution/JERProviderPlots_2012.root";
  std::string pathMVA =std::string(getenv("ROOTCOREDIR")) + "/../wwwAnalysis/Run/";

  std::string fileMVA =pathMVA+"BTagCalibration.env";
  
  if(!sm_pDataCalibrationTool)
    sm_pDataCalibrationTool = new JetAnalysisCalib::JetCalibrationTool("AntiKt4LCTopo", jetconfig_mc12a_and_data12.c_str(), true);
  if(!sm_pMC12aCalibrationTool)
    sm_pMC12aCalibrationTool = new JetAnalysisCalib::JetCalibrationTool("AntiKt4LCTopo", jetconfig_mc12a_and_data12.c_str(), false);
  if(!sm_pMC12bFullSimCalibrationTool)
    sm_pMC12bFullSimCalibrationTool = new JetAnalysisCalib::JetCalibrationTool("AntiKt4LCTopo", jetconfig_mc12b_fullsim.c_str(), false);
  if(!sm_pMC12bAFIICalibrationTool)
    sm_pMC12bAFIICalibrationTool = new JetAnalysisCalib::JetCalibrationTool("AntiKt4LCTopo", jetconfig_mc12b_afII.c_str(), false);
  if(!sm_pBJetScalingTool)
    sm_pBJetScalingTool = new ::Analysis::CalibrationDataInterfaceROOT("MV1",fileMVA.c_str(),pathMVA.c_str());
  //note MC12a and MC12b are identical in terms of JES uncertainties
  if(!sm_pMC12aJESUncertaintyTool)
    sm_pMC12aJESUncertaintyTool  = new JESUncertaintyProvider("JES_2012/Moriond2013/InsituJES2012_14NP.config","AntiKt4LCTopo","MC12a",jetunc_path.c_str());
  if(!sm_pMC12aMultijetJESUncertaintyTool)
    sm_pMC12aMultijetJESUncertaintyTool  = new MultijetJESUncertaintyProvider("JES_2012/Moriond2013/MultijetJES_2012.config","JES_2012/Moriond2013/InsituJES2012_14NP.config","AntiKt4LCTopo","MC12a",jetunc_path.c_str());
  if(!sm_pJVFUncTool)
    sm_pJVFUncTool = new JVFUncertaintyTool("AntiKt4LCTopo");
  if(!sm_pJERSmearingTool){
    sm_pJERSmearingTool = new JetSmearingTool("AntiKt4LCTopo",jer_file.c_str());
    sm_pJERSmearingTool->init();

  }

  std::vector<string> evs = sm_pBJetScalingTool->listScaleFactorUncertainties("AntiKt4TopoLCJVF0_5" , "B", "0_7892", false);
  std::cout << "******************************************************" << std::endl;
  std::cout << "CalibrationDataInterface Uncertainties AntiKt4TopoLCJVF" << std::endl;
  std::cout << "******************************************************" << std::endl;
  for (unsigned int i = 0;i<evs.size();i++) std::cout << evs[i] << std::endl;

  std::cout << "# Eigenvectors for 0.7892 OP: " << sm_pBJetScalingTool->getNumVariations("AntiKt4TopoLCJVF0_5" , "B", "0_7892", ::Analysis::SFEigen) << std::endl;
  std::cout << "# Eigenvectors for 0.1340 OP: " << sm_pBJetScalingTool->getNumVariations("AntiKt4TopoLCJVF0_5" , "B", "0_1340", ::Analysis::SFEigen) << std::endl;
  std::cout << "# Eigenvectors for 0.3511 OP: " << sm_pBJetScalingTool->getNumVariations("AntiKt4TopoLCJVF0_5" , "B", "0_3511", ::Analysis::SFEigen) << std::endl;
  std::cout << "******************************************************" << std::endl;
    
  /*
  std::cout << "Initialize Jet Uncertainty tool" << std::endl;
  for (int i=0;i<sm_pMC12aJESUncertaintyTool->getNUncertaintyComponents();i++){
  	std::cout << sm_pMC12aJESUncertaintyTool->getComponentNames().at(i) << std::endl;
  }
  */
  





}
bool wwwAnalysis::Jet::initialized()
{
	return sm_pDataCalibrationTool && sm_pMC12aCalibrationTool && 
	       sm_pMC12bFullSimCalibrationTool && sm_pMC12bAFIICalibrationTool && 
	       sm_pBJetScalingTool && sm_pMC12aJESUncertaintyTool && sm_pMC12aMultijetJESUncertaintyTool && sm_pJVFUncTool && sm_pJERSmearingTool  ;
}
void wwwAnalysis::Jet::finalize()
{
  if(sm_pDataCalibrationTool)
    delete sm_pDataCalibrationTool;
  if(sm_pMC12aCalibrationTool)
    delete sm_pMC12aCalibrationTool;
  if(sm_pMC12bFullSimCalibrationTool)
    delete sm_pMC12bFullSimCalibrationTool;
  if(sm_pMC12bAFIICalibrationTool)
    delete sm_pMC12bAFIICalibrationTool;
  if(sm_pBJetScalingTool)
    delete sm_pBJetScalingTool;
  if(sm_pMC12aJESUncertaintyTool)
    delete sm_pMC12aJESUncertaintyTool  ;
  if(sm_pMC12aMultijetJESUncertaintyTool)
    delete sm_pMC12aMultijetJESUncertaintyTool  ;
  if(sm_pJVFUncTool)
    delete sm_pJVFUncTool ;
  if(sm_pJERSmearingTool)
    delete sm_pJERSmearingTool  ;
  sm_pDataCalibrationTool = 0;
  sm_pMC12aCalibrationTool = 0;
  sm_pMC12bFullSimCalibrationTool = 0;
  sm_pMC12bAFIICalibrationTool = 0;
  sm_pBJetScalingTool = 0;
  sm_pMC12aJESUncertaintyTool   = 0;
  sm_pMC12aMultijetJESUncertaintyTool   = 0;
  sm_pJVFUncTool  = 0;
  sm_pJERSmearingTool   = 0;
}


wwwAnalysis::Jet::Jet(){

}
wwwAnalysis::Jet::Jet(const D3PDReader::EventInfoD3PDObject &eventinfo, const D3PDReader::JetD3PDObjectElement &jet, int nPV_2trks, double mu,ShoweringGenerator gen,JESSys jesSys, JetPileupSys pileupSys,JetFlavorSys flavorSys, JetResolutionSys resolutionSys,int JetIndex, bool doPrint)
  :PhysicsObject(eventinfo, JET), m_pD3PD(&jet)
{
	if(!initialized())
		initialize();

  m_iJetTagSFMapIndex  = -1;
  if(gen == Pythia6) m_iJetTagSFMapIndex = 0;
  else if(gen == Pythia8) m_iJetTagSFMapIndex = 1;
  else if(gen == HerwigJimmy) m_iJetTagSFMapIndex = 2;
  else if(gen == Sherpa) m_iJetTagSFMapIndex = 3;
  else if(gen == Herwigpp) m_iJetTagSFMapIndex = 4;
  else std::cout << "Showering Generator not understood" << std::endl;


  m_iJetContainerIndex = JetIndex;

  JetAnalysisCalib::JetCalibrationTool *pTool = sm_pDataCalibrationTool;
  
  if(eventInfo().mc_channel_number.IsAvailable()){
    if (eventInfo().RunNumber()==195847) { //mc12a
    	pTool = sm_pMC12aCalibrationTool; 
    }
    else if (eventInfo().RunNumber()==195848) { //mc12b
	pTool = sm_pMC12bFullSimCalibrationTool;
	/*
	 //We want to ultimately distinguish between AFII and FullSim
	 //this can be done using some branch called is_Geant4
	 //which needs to be included in future skims
	 //for now only afII samples are 
    	if (is_Geant4) pTool = sm_pMC12bFullSimCalibrationTool;
	else pTool = sm_pMC12bAFIICalibrationTool;
	*/
    	if (eventInfo().mc_channel_number() != 117489 && eventInfo().mc_channel_number() != 117490
		&& eventInfo().mc_channel_number() != 173041 && eventInfo().mc_channel_number() != 173042
		&& eventInfo().mc_channel_number() != 173043 && eventInfo().mc_channel_number() != 173044
		&& eventInfo().mc_channel_number() != 173045 && eventInfo().mc_channel_number() != 173046
		&& !(eventInfo().mc_channel_number() >= 185398 && eventInfo().mc_channel_number() <= 185469))  //aQGC samples are AFII
		{
			pTool = sm_pMC12bFullSimCalibrationTool;
		}
	else {
		pTool = sm_pMC12bAFIICalibrationTool;
	}
    }
  }

//std::cout<<"test "<<d3pd().pt()<<std::endl;
 
  double Eraw = d3pd().constscale_E();
  double eta = d3pd().constscale_eta();
  double phi = d3pd().constscale_phi();
  double m = d3pd().constscale_m();
  double Ax = d3pd().ActiveAreaPx();
  double Ay = d3pd().ActiveAreaPy();
  double Az = d3pd().ActiveAreaPz();
  double Ae = d3pd().ActiveAreaE();
  double rho = eventinfo.Eventshape_rhoKt4LC();;

//  setMomentum(pTool->ApplyJetAreaOffsetEtaJES(d3pd().constscale_E(), d3pd().constscale_eta(), d3pd().constscale_phi(), d3pd().constscale_m(), 
//  					      d3pd().ActiveAreaPx(),  d3pd().ActiveAreaPy(),  d3pd().ActiveAreaPz(),  d3pd().ActiveAreaE(), 
//  					      eventInfo().Eventshape_rhoKt4LC(), mu, nPV_2trks));


	std::string var="";
	if(jesSys==JESSysOff) var="";
	else if(jesSys==JESEffectiveNP_1Up || jesSys==JESEffectiveNP_1Down) var = "EffectiveNP_1";
	else if(jesSys==JESEffectiveNP_2Up || jesSys==JESEffectiveNP_2Down) var = "EffectiveNP_2";
	else if(jesSys==JESEffectiveNP_3Up || jesSys==JESEffectiveNP_3Down) var = "EffectiveNP_3";
	else if(jesSys==JESEffectiveNP_4Up || jesSys==JESEffectiveNP_4Down) var = "EffectiveNP_4";
	else if(jesSys==JESEffectiveNP_5Up || jesSys==JESEffectiveNP_5Down) var = "EffectiveNP_5";
	else if(jesSys==JESEffectiveNP_6restTermUp || jesSys==JESEffectiveNP_6restTermDown) var = "EffectiveNP_6restTerm";
	else if(jesSys==JESEtaIntercalibration_ModellingUp || jesSys==JESEtaIntercalibration_ModellingDown) var = "EtaIntercalibration_Modelling";
	else if(jesSys==JESEtaIntercalibration_StatAndMethodUp || jesSys==JESEtaIntercalibration_StatAndMethodDown) var = "EtaIntercalibration_StatAndMethod";
	else if(jesSys==JESSingleParticle_HighPtUp || jesSys==JESSingleParticle_HighPtDown) var = "SingleParticle_HighPt";
	else if(jesSys==JESRelativeNonClosure_Pythia8Up || jesSys==JESRelativeNonClosure_Pythia8Down) var = "RelativeNonClosure_Pythia8";

        //if(doPrint) printf("EVENT %d %d %f %f %f %f %f %f %f %f %f %f %d\n",eventInfo().EventNumber(),m_iJetContainerIndex, Eraw,eta,phi,m,Ax,Ay,Az,Ae,rho, mu, nPV_2trks);
        //if(doPrint) printf("EVENT %d %d %f %f %f %f\n",eventInfo().EventNumber(),m_iJetContainerIndex,d3pd().pt(),d3pd().eta(),d3pd().phi(),d3pd().m());
	TLorentzVector mom = pTool->ApplyJetAreaOffsetEtaJES(Eraw,eta,phi,m,Ax,Ay,Az,Ae,rho, mu, nPV_2trks);


	if(jesSys!=JESSysOff) {
		double unc = 0.;
		unc = sm_pMC12aJESUncertaintyTool->getRelUncertComponent(var,mom.Pt(),mom.Eta());


		if(jesSys==JESEffectiveNP_1Up || jesSys==JESEffectiveNP_2Up ||  jesSys==JESEffectiveNP_3Up ||  jesSys==JESEffectiveNP_4Up ||
	   	   jesSys==JESEffectiveNP_5Up || jesSys==JESEffectiveNP_6restTermUp || jesSys==JESEtaIntercalibration_ModellingUp ||
	   	   jesSys==JESEtaIntercalibration_StatAndMethodUp || jesSys==JESSingleParticle_HighPtUp  || jesSys==JESRelativeNonClosure_Pythia8Up)
				mom*=(1+unc);
		else if(jesSys==JESEffectiveNP_1Down || jesSys==JESEffectiveNP_2Down ||  jesSys==JESEffectiveNP_3Down ||  jesSys==JESEffectiveNP_4Down ||
	   		jesSys==JESEffectiveNP_5Down || jesSys==JESEffectiveNP_6restTermDown || jesSys==JESEtaIntercalibration_ModellingDown ||
	   		jesSys==JESEtaIntercalibration_StatAndMethodDown || jesSys==JESSingleParticle_HighPtDown  || jesSys==JESRelativeNonClosure_Pythia8Down)
				mom*=(1-unc);
		else std::cout <<"JES Uncertainty not specified properly"<<std::endl;

		
	}




	if(pileupSys!=JetPileupSysOff){

		double unc = 0.;
		if( pileupSys==JetPileupNPVUp || pileupSys==JetPileupNPVDown )
			unc = sm_pMC12aJESUncertaintyTool->getRelNPVOffsetTerm(mom.Pt(),mom.Eta(),nPV_2trks);
		if( pileupSys==JetPileupMuUp  || pileupSys==JetPileupMuDown  )
			unc = sm_pMC12aJESUncertaintyTool->getRelMuOffsetTerm(mom.Pt(),mom.Eta(),mu);
		if( pileupSys==JetPileupPtUp  || pileupSys==JetPileupPtDown  )
			unc = sm_pMC12aJESUncertaintyTool->getRelPileupPtTerm(mom.Pt(),mom.Eta(),nPV_2trks,mu);
		if( pileupSys==JetPileupRhoTopoUp  || pileupSys==JetPileupRhoTopoDown )
			unc = sm_pMC12aJESUncertaintyTool->getRelPileupRhoTopology(mom.Pt(),mom.Eta());

		if( pileupSys==JetPileupNPVUp || pileupSys==JetPileupMuUp  || 
		    pileupSys==JetPileupPtUp  || pileupSys==JetPileupRhoTopoUp  )
			mom*=(1+unc);
		else if( pileupSys==JetPileupNPVDown || pileupSys==JetPileupMuDown  || 
		    	 pileupSys==JetPileupPtDown  || pileupSys==JetPileupRhoTopoDown  )
			mom*=(1-unc);
		else std::cout <<"JES Pileup Uncertainty not specified properly"<<std::endl;


	}
	if(flavorSys!=JetFlavorSysOff){

		double unc = 0.;
		if(d3pd().flavor_truth_label() ==5 ){ //only applied to b-jets
		    if( flavorSys==JetFlavorBJESUp || flavorSys == JetFlavorBJESDown )
			unc = sm_pMC12aMultijetJESUncertaintyTool->getRelBJESUncert(mom.Pt(),mom.Eta());
		}
		else{ //do not apply these to b-jets
		
		    bool isUp = true;
		    if( flavorSys==JetFlavorCompositionUp)
			unc = sm_pMC12aMultijetJESUncertaintyTool->getRelFlavorCompUncert(mom.Pt(),mom.Eta(),isUp);
		    if( flavorSys == JetFlavorCompositionDown )
			unc = sm_pMC12aMultijetJESUncertaintyTool->getRelFlavorCompUncert(mom.Pt(),mom.Eta(),!isUp);
		    if( flavorSys==JetFlavorResponseUp || flavorSys == JetFlavorResponseDown )
			unc = sm_pMC12aMultijetJESUncertaintyTool->getRelFlavorResponseUncert(mom.Pt(),mom.Eta());
		}

		if(flavorSys==JetFlavorBJESUp || flavorSys==JetFlavorCompositionUp || flavorSys==JetFlavorResponseUp )
			mom*=(1+unc);
		else if(flavorSys==JetFlavorBJESDown || flavorSys==JetFlavorCompositionDown || flavorSys==JetFlavorResponseDown )
			mom*=(1-unc);
		else std::cout <<"JES Flavor Uncertainty not specified properly"<<std::endl;



	}

	if(resolutionSys!=JetResolutionSysOff){
		sm_pJERSmearingTool->SetSeed(eventInfo().EventNumber());
		 //We want to ultimately distinguish between AFII and FullSim
		 //this can be done using some branch called is_Geant4
		 //which needs to be included in future skims
	 	//for now all samples are full sim


		sm_pJERSmearingTool->SmearJet_Syst(mom);
		//sm_pJERSmearingTool->SmearJet_Syst_AFII(mom);

	}


	setMomentum(mom);

	//setMomentum(pTool->ApplyJetAreaOffsetEtaJES(Eraw,eta,phi,m,Ax,Ay,Az,Ae,rho, mu, nPV_2trks));
	
	//TLorentzVector mom;
	//mom.SetPtEtaPhiM(d3pd().pt(),d3pd().eta(),d3pd().phi(),d3pd().m());
}

const D3PDReader::JetD3PDObjectElement &wwwAnalysis::Jet::d3pd() const
{
  return *m_pD3PD;
}

double wwwAnalysis::Jet::scaleFactor(BTagJetOperatingPoint bTagOP,JetTagSFSys jetTagSys,JVFSys jvfSys) const
{
  if(fabs(momentum().Eta()) >= 2.5 || momentum().Pt() <= 25000)
    return 1.0;

  ::Analysis::CalibrationDataVariables ajet;
  ::Analysis::Uncertainty uncertainty = ::Analysis::Total;

  ajet.jetAuthor = "AntiKt4TopoLCJVF0_5";
  ajet.jetPt = momentum().Pt();
  ajet.jetEta = momentum().Eta();

  

  int label = d3pd().flavor_truth_label();
  std::string flavour;
  if(label == 4) flavour = "C";
  else if(label == 5) flavour = "B";
  else if(label == 15) flavour = "T";
  else flavour = "Light";


  std::string op_str = "0_7892";  //default is 70% efficiency operating point
  if(bTagOP == Eff60) op_str = "0_9827";
  else if(bTagOP == Eff80) op_str = "0_3511";
  else if(bTagOP == Eff85) op_str = "0_1340";

  bool isBTagged = btagged(bTagOP,jvfSys);

  /*
  std::cout << "map index: " << m_iJetTagSFMapIndex << std::endl;
  std::cout << "is btagged: " << (isBTagged ? "true" : "false") << std::endl;
  std::cout << "flavor: " << flavour << std::endl;
  */

  int mapIndex = 0;
  //if (flavour == "B") 
  mapIndex = m_iJetTagSFMapIndex;

  ::Analysis::CalibResult SF;
  if(isBTagged)
    SF =  sm_pBJetScalingTool->getScaleFactor(ajet, flavour, op_str.c_str(),uncertainty,0,mapIndex);
  else 
    SF =  sm_pBJetScalingTool->getInefficiencyScaleFactor(ajet, flavour, op_str.c_str(),uncertainty,0,mapIndex);


  //by default use uncertainty as taken from tool
  double sf = SF.first;
  double unc = SF.second;

  //if(doPrint) printf("EVENT %d %d %d %f %f %s %d %f\n",eventInfo().EventNumber(),m_iJetContainerIndex,(isBTagged ? 1 : 0),ajet.jetPt,ajet.jetEta,flavour.c_str(),mapIndex,sf);

  if(jetTagSys!=JetTagSFSysOff){
    if(flavour == "B"){

	  int numEigenVector = -1;
	  if ( jetTagSys == JetBTagSFEV1Up || jetTagSys == JetBTagSFEV1Down ) numEigenVector = 0;
	  else if ( jetTagSys == JetBTagSFEV2Up || jetTagSys == JetBTagSFEV2Down ) numEigenVector = 1;
	  else if ( jetTagSys == JetBTagSFEV3Up || jetTagSys == JetBTagSFEV3Down ) numEigenVector = 2;
	  else if ( jetTagSys == JetBTagSFEV4Up || jetTagSys == JetBTagSFEV4Down ) numEigenVector = 3;
	  else if ( jetTagSys == JetBTagSFEV5Up || jetTagSys == JetBTagSFEV5Down ) numEigenVector = 4;
	  else if ( jetTagSys == JetBTagSFEV6Up || jetTagSys == JetBTagSFEV6Down ) numEigenVector = 5;
	  else if ( jetTagSys == JetBTagSFEV7Up || jetTagSys == JetBTagSFEV7Down ) numEigenVector = 6;
	  else if ( jetTagSys == JetBTagSFEV8Up || jetTagSys == JetBTagSFEV8Down ) numEigenVector = 7;
	  else if ( jetTagSys == JetBTagSFEV9Up || jetTagSys == JetBTagSFEV9Down ) numEigenVector = 8;
	  else if ( jetTagSys == JetBTagSFEV10Up || jetTagSys == JetBTagSFEV10Down ) numEigenVector = 9;

	  if (numEigenVector >= 0){
	        ::Analysis::CalibResult SFUnc;
	  	if (isBTagged) 
		  SFUnc =  sm_pBJetScalingTool->getScaleFactor(ajet, "B", op_str.c_str(),::Analysis::SFEigen,numEigenVector,mapIndex);
		else 
		  SFUnc =  sm_pBJetScalingTool->getInefficiencyScaleFactor(ajet, "B", op_str.c_str(),::Analysis::SFEigen,numEigenVector,mapIndex);

		double SFPlusHighErr = SFUnc.first;
		double SFMinusLowErr  = SFUnc.second;

		
	  	if ( jetTagSys == JetBTagSFEV1Up || jetTagSys == JetBTagSFEV2Up || jetTagSys == JetBTagSFEV3Up ||
		     jetTagSys == JetBTagSFEV4Up || jetTagSys == JetBTagSFEV5Up || jetTagSys == JetBTagSFEV6Up ||
		     jetTagSys == JetBTagSFEV7Up || jetTagSys == JetBTagSFEV8Up || jetTagSys == JetBTagSFEV9Up ||
		     jetTagSys == JetBTagSFEV10Up ) return SFPlusHighErr;
	  	else return SFMinusLowErr;

	  } //end if numEigenVector < 0 
	  /*
	  std::cout << "num variations " << sm_pBJetScalingTool->getNumVariations("AntiKt4TopoLCJVF" , flavour, op_str.c_str(), ::Analysis::SFEigen)  << std::endl;
	  for (unsigned int j = 0;j< 10 ; j++){
		SFUnc =  sm_pBJetScalingTool->getScaleFactor(ajet, flavour, op_str.c_str(),::Analysis::SFEigen,j);
		std::cout << "EIGENVECTOR " << j << "\t"<<SFUnc.first << "\t" << SFUnc.second << std::endl;
	  }
	  */
    } //end if flavor == "B"
    else if(flavour == "C" || flavour == "T"){
  	if (jetTagSys == JetCTTagSFUp ) return sf+unc;
	else if (jetTagSys == JetCTTagSFDown) return sf-unc;
    } //end if C or T
    else{
  	if (jetTagSys == JetMisTagSFUp) return sf+unc;
  	else if (jetTagSys == JetMisTagSFDown) return sf-unc;
    } //end else
  }//end if compute systematic

  return sf;
}
bool wwwAnalysis::Jet::jvf(JVFSys sys) const
{
  
  double jvtxf = d3pd().jvtxf();
  double JVFcutNominal = 0.5;//0,0.25,0.5 are supported
  double eta_det = d3pd().constscale_eta();
  bool isPU = false;  //For post-Moriond 2013 analyses, assume all jets are real, hard-scatter jets

  if( momentum().Pt() >= 50000 || fabs(momentum().Eta()) >= 2.4) return true;
  //double testJVFcutup = sm_pJVFUncTool->getJVFcut(JVFcutNominal,isPU,momentum().Pt(),eta_det,true);
  //double testJVFcutdown = sm_pJVFUncTool->getJVFcut(JVFcutNominal,isPU,momentum().Pt(),eta_det,false);


  double JVFcut = JVFcutNominal;
  if(sys==JVFUp) JVFcut = sm_pJVFUncTool->getJVFcut(JVFcutNominal,isPU,momentum().Pt(),eta_det,true);
  else if(sys==JVFDown) JVFcut = sm_pJVFUncTool->getJVFcut(JVFcutNominal,isPU,momentum().Pt(),eta_det,false);


  //should eta_det be used here as well???
  //return momentum().Pt() >= 50000 || fabs(momentum().Eta()) >= 2.4 || fabs(jvtxf) > JVFcutNominal;
  //return momentum().Pt() >= 50000 || fabs(momentum().Eta()) >= 2.4 || fabs(jvtxf) > JVFcut;
  return fabs(jvtxf) > JVFcut;
}
bool wwwAnalysis::Jet::btagged(BTagJetOperatingPoint bTagOP,JVFSys jvfsys) const
{
  float op = 0.7892;  //default is 70% efficiency operating point
  if(bTagOP == Eff60) op = 0.9827;
  else if(bTagOP == Eff80) op = 0.3511;
  else if(bTagOP == Eff85) op = 0.1340;

  bool btagged = momentum().Pt() > 25000 && fabs(momentum().Eta()) < 2.5 && jvf(jvfsys) && d3pd().flavor_weight_MV1() >= op;

  return btagged; 
}
