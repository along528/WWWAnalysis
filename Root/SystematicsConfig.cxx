#include "wwwAnalysis/SystematicsConfig.h"
#include <iostream>

wwwAnalysis::SystematicsConfig::SystematicsConfig() 
	{
		//by default only run central value
		m_mSwitchboard["Central"] = true;
		m_mSwitchboard["ChargeMisIDUp"] = false;
		m_mSwitchboard["ChargeMisIDDown"] = false;
		m_mSwitchboard["MuonEffUp"] = false;
		m_mSwitchboard["MuonEffDown"] = false;
		m_mSwitchboard["MuonMomMSUp"] = false;
		m_mSwitchboard["MuonMomMSDown"] = false;
		m_mSwitchboard["MuonMomIDUp"] = false;
		m_mSwitchboard["MuonMomIDDown"] = false;
		m_mSwitchboard["MuonMomScaleUp"] = false;
		m_mSwitchboard["MuonMomScaleDown"] = false;
		m_mSwitchboard["ElectronEffRecoUp"] = false;
		m_mSwitchboard["ElectronEffRecoDown"] = false;
		m_mSwitchboard["ElectronEffIDUp"] = false;
		m_mSwitchboard["ElectronEffIDDown"] = false;
		m_mSwitchboard["ElectronEnergyScaleZeeStatUp"] = false;
		m_mSwitchboard["ElectronEnergyScaleZeeStatDown"] = false;
		m_mSwitchboard["ElectronEnergyScaleZeeMethUp"] = false;
		m_mSwitchboard["ElectronEnergyScaleZeeMethDown"] = false;
		m_mSwitchboard["ElectronEnergyScaleZeeGenUp"] = false;
		m_mSwitchboard["ElectronEnergyScaleZeeGenDown"] = false;
		m_mSwitchboard["ElectronEnergyScaleMaterialUp"] = false;
		m_mSwitchboard["ElectronEnergyScaleMaterialDown"] = false;
		m_mSwitchboard["ElectronEnergyScalePresamplerUp"] = false;
		m_mSwitchboard["ElectronEnergyScalePresamplerDown"] = false;
		m_mSwitchboard["ElectronEnergyScaleLowPtUp"] = false;
		m_mSwitchboard["ElectronEnergyScaleLowPtDown"] = false;
		m_mSwitchboard["ElectronEnergySmearingUp"] = false;
		m_mSwitchboard["ElectronEnergySmearingDown"] = false;
		m_mSwitchboard["MissingEtSoftTermsScaleUp"] = false;
		m_mSwitchboard["MissingEtSoftTermsScaleDown"] = false;
		m_mSwitchboard["MissingEtSoftTermsResoUp"] = false;
		m_mSwitchboard["MissingEtSoftTermsResoDown"] = false;
	  	m_mSwitchboard["TriggerSFElectronUp"] = false;
	  	m_mSwitchboard["TriggerSFElectronDown"] = false;
	  	m_mSwitchboard["TriggerSFMuonUp"] = false;
	  	m_mSwitchboard["TriggerSFMuonDown"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_1Up"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_1Down"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_2Up"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_2Down"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_3Up"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_3Down"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_4Up"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_4Down"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_5Up"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_5Down"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_6restTermUp"] = false;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_6restTermDown"] = false;
	  	m_mSwitchboard["JetEnergyScaleEtaIntercalibration_ModellingUp"] = false;
	  	m_mSwitchboard["JetEnergyScaleEtaIntercalibration_ModellingDown"] = false;
	  	m_mSwitchboard["JetEnergyScaleEtaIntercalibration_StatAndMethodUp"] = false;
	  	m_mSwitchboard["JetEnergyScaleEtaIntercalibration_StatAndMethodDown"] = false;
	  	m_mSwitchboard["JetEnergyScaleSingleParticle_HighPtUp"] = false;
	  	m_mSwitchboard["JetEnergyScaleSingleParticle_HighPtDown"] = false;
	  	m_mSwitchboard["JetEnergyScaleRelativeNonClosure_Pythia8Up"] = false;
	  	m_mSwitchboard["JetEnergyScaleRelativeNonClosure_Pythia8Down"] = false;
  	  	m_mSwitchboard["JetPileupNPVUp"] = false;
  	  	m_mSwitchboard["JetPileupNPVDown"] = false;
  	  	m_mSwitchboard["JetPileupMuUp"] = false;
  	  	m_mSwitchboard["JetPileupMuDown"] = false;
  	  	m_mSwitchboard["JetPileupPtUp"] = false;
  	  	m_mSwitchboard["JetPileupPtDown"] = false;
  	  	m_mSwitchboard["JetPileupRhoTopoUp"] = false;
  	  	m_mSwitchboard["JetPileupRhoTopoDown"] = false;
		m_mSwitchboard["JetVertexFractionUp"] = false;
		m_mSwitchboard["JetVertexFractionDown"] = false;
  		m_mSwitchboard["JetCTTagSFUp"] = false;
  		m_mSwitchboard["JetCTTagSFDown"] = false;
  		m_mSwitchboard["JetMisTagSFUp"] = false;
  		m_mSwitchboard["JetMisTagSFDown"] = false;
  		m_mSwitchboard["JetBTagSFEV1Up"] = false;
  		m_mSwitchboard["JetBTagSFEV1Down"] = false;
  		m_mSwitchboard["JetBTagSFEV2Up"] = false;
  		m_mSwitchboard["JetBTagSFEV2Down"] = false;
  		m_mSwitchboard["JetBTagSFEV3Up"] = false;
  		m_mSwitchboard["JetBTagSFEV3Down"] = false;
  		m_mSwitchboard["JetBTagSFEV4Up"] = false;
  		m_mSwitchboard["JetBTagSFEV4Down"] = false;
  		m_mSwitchboard["JetBTagSFEV5Up"] = false;
  		m_mSwitchboard["JetBTagSFEV5Down"] = false;
  		m_mSwitchboard["JetBTagSFEV6Up"] = false;
  		m_mSwitchboard["JetBTagSFEV6Down"] = false;
  		m_mSwitchboard["PileupUp"] = false;
  		m_mSwitchboard["PileupDown"] = false;
		/*
  		m_mSwitchboard["JetBTagSFEV7Up"] = false;
  		m_mSwitchboard["JetBTagSFEV7Down"] = false;
  		m_mSwitchboard["JetBTagSFEV8Up"] = false;
  		m_mSwitchboard["JetBTagSFEV8Down"] = false;
  		m_mSwitchboard["JetBTagSFEV9Up"] = false;
  		m_mSwitchboard["JetBTagSFEV9Down"] = false;
  		m_mSwitchboard["JetBTagSFEV10Up"] = false;
  		m_mSwitchboard["JetBTagSFEV10Down"] = false;
		*/
  		m_mSwitchboard["JetFlavorCompositionUp"] = false;
  		m_mSwitchboard["JetFlavorCompositionDown"] = false;
  		m_mSwitchboard["JetFlavorResponseUp"] = false;
  		m_mSwitchboard["JetFlavorResponseDown"] = false;
		m_mSwitchboard["JetFlavorBJESUp"] = false;
		m_mSwitchboard["JetFlavorBJESDown"] = false;
		m_mSwitchboard["JetResolution"] = false;

	  	m_mSwitchboard["MxMElUp"] = false;
	  	m_mSwitchboard["MxMElDown"] = false;
	  	m_mSwitchboard["MxMMuUp"] = false;
	  	m_mSwitchboard["MxMMuDown"] = false;
	  	m_mSwitchboard["MxMBJetAlt"] = false;
	  	m_mSwitchboard["MxMBJetAltFlipped"] = false;
	  	//m_mSwitchboard["MxMBJetGt0"] = false;




		//Build configuration maps from strings to enums

		//Muon Efficiency
  		m_mMuonEff["MuonEffUp"] =   MuonEffUp;
  		m_mMuonEff["MuonEffDown"] =  MuonEffDown;

		//Muon Momentum
  		m_mMuonMom["MuonMomMSUp"] =  MSUP;
  		m_mMuonMom["MuonMomMSDown"] =  MSLOW;
  		m_mMuonMom["MuonMomIDUp"] =  IDUP;
  		m_mMuonMom["MuonMomIDDown"] =  IDLOW;
  		m_mMuonMom["MuonMomScaleUp"] =  SCALEUP;
  		m_mMuonMom["MuonMomScaleDown"] =  SCALELOW;

		//Electron Efficiency
  		m_mElectronEff["ElectronEffRecoUp"] =  ElRecoEffUp;
  		m_mElectronEff["ElectronEffRecoDown"] =  ElRecoEffDown;
  		m_mElectronEff["ElectronEffIDUp"] =  ElIDEffUp;
  		m_mElectronEff["ElectronEffIDDown"] =  ElIDEffDown;

		//Electron Energy Scale
  		m_mElectronEnergyScale["ElectronEnergyScaleZeeStatUp"] =  ElScaleZeeStatUp;
  		m_mElectronEnergyScale["ElectronEnergyScaleZeeStatDown"] =  ElScaleZeeStatDown;
  		m_mElectronEnergyScale["ElectronEnergyScaleZeeMethUp"] =  ElScaleZeeMethUp;
  		m_mElectronEnergyScale["ElectronEnergyScaleZeeMethDown"] =  ElScaleZeeMethDown;
  		m_mElectronEnergyScale["ElectronEnergyScaleZeeGenUp"] =  ElScaleZeeGenUp;
  		m_mElectronEnergyScale["ElectronEnergyScaleZeeGenDown"] =  ElScaleZeeGenDown;
  		m_mElectronEnergyScale["ElectronEnergyScaleMaterialUp"] =  ElScaleMaterialUp;
  		m_mElectronEnergyScale["ElectronEnergyScaleMaterialDown"] =  ElScaleMaterialDown;
  		m_mElectronEnergyScale["ElectronEnergyScalePresamplerUp"] =  ElScalePresamplerUp;
  		m_mElectronEnergyScale["ElectronEnergyScalePresamplerDown"] =  ElScalePresamplerDown;
  		m_mElectronEnergyScale["ElectronEnergyScaleLowPtUp"] =  ElScaleLowPtUp;
  		m_mElectronEnergyScale["ElectronEnergyScaleLowPtDown"] =  ElScaleLowPtDown;

		//Electron Energy Smearing
  		m_mElectronEnergySmearing["ElectronEnergySmearingUp"] =  ElEnergySmearingUp;
  		m_mElectronEnergySmearing["ElectronEnergySmearingDown"] =  ElEnergySmearingDown;

		//Missing Et Soft Terms
  		m_mMissingEtSoftTerms["MissingEtSoftTermsScaleUp"] =  METSoftTermsScaleUp;
  		m_mMissingEtSoftTerms["MissingEtSoftTermsScaleDown"] =  METSoftTermsScaleDown;
  		m_mMissingEtSoftTerms["MissingEtSoftTermsResoUp"] =  METSoftTermsResoUp;
  		m_mMissingEtSoftTerms["MissingEtSoftTermsResoDown"] =  METSoftTermsResoDown;

		//Trigger scale factor
  		m_mTriggerSF["TriggerSFElectronUp"] =  TrigSFElUp;
  		m_mTriggerSF["TriggerSFElectronDown"] =  TrigSFElDown;
  		m_mTriggerSF["TriggerSFMuonUp"] =  TrigSFMuUp;
  		m_mTriggerSF["TriggerSFMuonDown"] =  TrigSFMuDown;

		//JES
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_1Up"] =  JESEffectiveNP_1Up;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_1Down"] =  JESEffectiveNP_1Down;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_2Up"] =  JESEffectiveNP_2Up;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_2Down"] =  JESEffectiveNP_2Down;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_3Up"] =  JESEffectiveNP_3Up;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_3Down"] =  JESEffectiveNP_3Down;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_4Up"] =  JESEffectiveNP_4Up;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_4Down"] =  JESEffectiveNP_4Down;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_5Up"] =  JESEffectiveNP_5Up;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_5Down"] =  JESEffectiveNP_5Down;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_6restTermUp"] =  JESEffectiveNP_6restTermUp;
  		m_mJetEnergyScale["JetEnergyScaleEffectiveNP_6restTermDown"] =  JESEffectiveNP_6restTermDown;
  		m_mJetEnergyScale["JetEnergyScaleEtaIntercalibration_ModellingUp"] =  JESEtaIntercalibration_ModellingUp;
  		m_mJetEnergyScale["JetEnergyScaleEtaIntercalibration_ModellingDown"] =  JESEtaIntercalibration_ModellingDown;
  		m_mJetEnergyScale["JetEnergyScaleEtaIntercalibration_StatAndMethodUp"] =  JESEtaIntercalibration_StatAndMethodUp;
  		m_mJetEnergyScale["JetEnergyScaleEtaIntercalibration_StatAndMethodDown"] =  JESEtaIntercalibration_StatAndMethodDown;
  		m_mJetEnergyScale["JetEnergyScaleSingleParticle_HighPtUp"] = JESSingleParticle_HighPtUp;
  		m_mJetEnergyScale["JetEnergyScaleSingleParticle_HighPtDown"] = JESSingleParticle_HighPtDown;
  		m_mJetEnergyScale["JetEnergyScaleRelativeNonClosure_Pythia8Up"] = JESRelativeNonClosure_Pythia8Up;
  		m_mJetEnergyScale["JetEnergyScaleRelativeNonClosure_Pythia8Down"] = JESRelativeNonClosure_Pythia8Down;

		//Jet Pileup
  		m_mJetPileup["JetPileupNPVUp"] = JetPileupNPVUp;
  		m_mJetPileup["JetPileupNPVDown"] = JetPileupNPVDown;
  		m_mJetPileup["JetPileupMuUp"] = JetPileupMuUp;
  		m_mJetPileup["JetPileupMuDown"] = JetPileupMuDown;
  		m_mJetPileup["JetPileupPtUp"] = JetPileupPtUp;
  		m_mJetPileup["JetPileupPtDown"] = JetPileupPtDown;
  		m_mJetPileup["JetPileupRhoTopoUp"] = JetPileupRhoTopoUp;
  		m_mJetPileup["JetPileupRhoTopoDown"] = JetPileupRhoTopoDown;

		//JVF
  		m_mJVF["JetVertexFractionUp"] = JVFUp;
  		m_mJVF["JetVertexFractionDown"] = JVFDown;


		
		//Jet Tagging scale factor
  		m_mJetTagSF["JetCTTagSFUp"] = JetCTTagSFUp;
  		m_mJetTagSF["JetCTTagSFDown"] = JetCTTagSFDown;
  		m_mJetTagSF["JetMisTagSFUp"] = JetMisTagSFUp;
  		m_mJetTagSF["JetMisTagSFDown"] = JetMisTagSFDown;
  		m_mJetTagSF["JetBTagSFEV1Up"] = JetBTagSFEV1Up;
  		m_mJetTagSF["JetBTagSFEV1Down"] = JetBTagSFEV1Down;
  		m_mJetTagSF["JetBTagSFEV2Up"] = JetBTagSFEV2Up;
  		m_mJetTagSF["JetBTagSFEV2Down"] = JetBTagSFEV2Down;
  		m_mJetTagSF["JetBTagSFEV3Up"] = JetBTagSFEV3Up;
  		m_mJetTagSF["JetBTagSFEV3Down"] = JetBTagSFEV3Down;
  		m_mJetTagSF["JetBTagSFEV4Up"] = JetBTagSFEV4Up;
  		m_mJetTagSF["JetBTagSFEV4Down"] = JetBTagSFEV4Down;
  		m_mJetTagSF["JetBTagSFEV5Up"] = JetBTagSFEV5Up;
  		m_mJetTagSF["JetBTagSFEV5Down"] = JetBTagSFEV5Down;
  		m_mJetTagSF["JetBTagSFEV6Up"] = JetBTagSFEV6Up;
  		m_mJetTagSF["JetBTagSFEV6Down"] = JetBTagSFEV6Down;
		/*
  		m_mJetTagSF["JetBTagSFEV7Up"] = JetBTagSFEV7Up;
  		m_mJetTagSF["JetBTagSFEV7Down"] = JetBTagSFEV7Down;
  		m_mJetTagSF["JetBTagSFEV8Up"] = JetBTagSFEV8Up;
  		m_mJetTagSF["JetBTagSFEV8Down"] = JetBTagSFEV8Down;
  		m_mJetTagSF["JetBTagSFEV9Up"] = JetBTagSFEV9Up;
  		m_mJetTagSF["JetBTagSFEV9Down"] = JetBTagSFEV9Down;
  		m_mJetTagSF["JetBTagSFEV10Up"] = JetBTagSFEV10Up;
  		m_mJetTagSF["JetBTagSFEV10Down"] = JetBTagSFEV10Down;
		*/

		//Jet Flavor Composition
  		m_mJetFlavor["JetFlavorCompositionUp"] = JetFlavorCompositionUp;
  		m_mJetFlavor["JetFlavorCompositionDown"] = JetFlavorCompositionDown;
  		m_mJetFlavor["JetFlavorResponseUp"] = JetFlavorResponseUp;
  		m_mJetFlavor["JetFlavorResponseDown"] = JetFlavorResponseDown;
  		m_mJetFlavor["JetFlavorBJESUp"] = JetFlavorBJESUp;
  		m_mJetFlavor["JetFlavorBJESDown"] = JetFlavorBJESDown;
		
		//Jet Resolution
  		m_mJetResolution["JetResolution"] = JetResolutionSysOn;

		//Charge Mis-ID
		m_mChargeMisID["ChargeMisIDUp"] = ChargeMisIDUp;
		m_mChargeMisID["ChargeMisIDDown"] = ChargeMisIDDown;

		//Pileup
		m_mPileup["PileupUp"] = PileupUp;
		m_mPileup["PileupDown"] = PileupDown;

		//MxM
	  	m_mMxM["MxMElUp"] = MxMElUp;
	  	m_mMxM["MxMElDown"] = MxMElDown;
	  	m_mMxM["MxMMuUp"] = MxMMuUp;
	  	m_mMxM["MxMMuDown"] = MxMMuDown;
	  	m_mMxM["MxMBJetAlt"] = MxMBJetAlt;
	  	m_mMxM["MxMBJetAltFlipped"] = MxMBJetAltFlipped;
	  	//m_mMxM["MxMBJetGt0"] = MxMBJetGt0;

		m_sCurrentSystematic = "";
}
wwwAnalysis::SystematicsConfig::~SystematicsConfig() {
}

bool wwwAnalysis::SystematicsConfig::next(){
	
	mapit_type it;
	if (m_sCurrentSystematic == "")  it = m_mSwitchboard.begin();
	else it = m_mSwitchboard.find(m_sCurrentSystematic);

	if(m_sCurrentSystematic!="" && it!=m_mSwitchboard.end()) it++;

	for(; it != m_mSwitchboard.end(); it++){
		if (it->second==true){
			m_sCurrentSystematic = it->first;
			return true;
		}

	}

	//if call and reach the end then reset for the next time
	resetQueue();
	return false;
}

std::string wwwAnalysis::SystematicsConfig::getCurrentSystematic(){
	return m_sCurrentSystematic;

}

wwwAnalysis::ChargeMisIDSys wwwAnalysis::SystematicsConfig::getCurrentChargeMisIDSys(){
		std::map<std::string,wwwAnalysis::ChargeMisIDSys>::iterator mapit;
		mapit = m_mChargeMisID.find(m_sCurrentSystematic);
		if (mapit!= m_mChargeMisID.end()) return mapit->second;
		return ChargeMisIDSysOff;
}
wwwAnalysis::MuonEffSys wwwAnalysis::SystematicsConfig::getCurrentMuonEffSys(){
		std::map<std::string,wwwAnalysis::MuonEffSys>::iterator mapit;
		mapit = m_mMuonEff.find(m_sCurrentSystematic);
		if (mapit!= m_mMuonEff.end()) return mapit->second;
		return MuonEffSysOff;
}
wwwAnalysis::MuonMomSys wwwAnalysis::SystematicsConfig::getCurrentMuonMomSys(){
		std::map<std::string,wwwAnalysis::MuonMomSys >::iterator mapit;
		mapit = m_mMuonMom.find(m_sCurrentSystematic);
		if (mapit!= m_mMuonMom.end()) return mapit->second;
		return MuonMomSysOff;
}
wwwAnalysis::ElectronEffSys wwwAnalysis::SystematicsConfig::getCurrentElectronEffSys(){
		std::map<std::string,wwwAnalysis::ElectronEffSys >::iterator mapit;
		mapit = m_mElectronEff.find(m_sCurrentSystematic);
		if (mapit!= m_mElectronEff.end()) return mapit->second;
		return ElectronEffSysOff;
}
wwwAnalysis::ElectronEnergyScaleSys wwwAnalysis::SystematicsConfig::getCurrentElectronEnergyScaleSys(){
		std::map<std::string,wwwAnalysis::ElectronEnergyScaleSys >::iterator mapit;
		mapit = m_mElectronEnergyScale.find(m_sCurrentSystematic);
		if (mapit!= m_mElectronEnergyScale.end()) return mapit->second;
		return ElectronEnergyScaleSysOff;
}
wwwAnalysis::ElectronEnergySmearingSys wwwAnalysis::SystematicsConfig::getCurrentElectronEnergySmearingSys(){
		std::map<std::string,wwwAnalysis::ElectronEnergySmearingSys >::iterator mapit;
		mapit = m_mElectronEnergySmearing.find(m_sCurrentSystematic);
		if (mapit!= m_mElectronEnergySmearing.end()) return mapit->second;
		return ElectronEnergySmearingSysOff;
}
wwwAnalysis::METSoftTermsSys wwwAnalysis::SystematicsConfig::getCurrentMETSoftTermsSys(){
		std::map<std::string,wwwAnalysis::METSoftTermsSys >::iterator mapit;
		mapit = m_mMissingEtSoftTerms.find(m_sCurrentSystematic);
		if (mapit!= m_mMissingEtSoftTerms.end()) return mapit->second;
		return METSoftTermsSysOff;
}
wwwAnalysis::TriggerSFSys wwwAnalysis::SystematicsConfig::getCurrentTriggerSFSys(){
		std::map<std::string,wwwAnalysis::TriggerSFSys >::iterator mapit;
		mapit = m_mTriggerSF.find(m_sCurrentSystematic);
		if (mapit!= m_mTriggerSF.end()) return mapit->second;
		return TriggerSFSysOff;
}
wwwAnalysis::JESSys wwwAnalysis::SystematicsConfig::getCurrentJESSys(){
		std::map<std::string,wwwAnalysis::JESSys >::iterator mapit;
		mapit = m_mJetEnergyScale.find(m_sCurrentSystematic);
		if (mapit!= m_mJetEnergyScale.end()) return mapit->second;
		return JESSysOff;
}
wwwAnalysis::JetPileupSys wwwAnalysis::SystematicsConfig::getCurrentJetPileupSys(){
		std::map<std::string,wwwAnalysis::JetPileupSys >::iterator mapit;
		mapit = m_mJetPileup.find(m_sCurrentSystematic);
		if (mapit!= m_mJetPileup.end()) return mapit->second;
		return JetPileupSysOff;
}
wwwAnalysis::JVFSys wwwAnalysis::SystematicsConfig::getCurrentJVFSys(){
		std::map<std::string,wwwAnalysis::JVFSys >::iterator mapit;
		mapit = m_mJVF.find(m_sCurrentSystematic);
		if (mapit!= m_mJVF.end()) return mapit->second;
		return JVFSysOff;
}
wwwAnalysis::PileupSys wwwAnalysis::SystematicsConfig::getCurrentPileupSys(){
		std::map<std::string,wwwAnalysis::PileupSys >::iterator mapit;
		mapit = m_mPileup.find(m_sCurrentSystematic);
		if (mapit!= m_mPileup.end()) return mapit->second;
		return PileupSysOff;
}
wwwAnalysis::JetTagSFSys wwwAnalysis::SystematicsConfig::getCurrentJetTagSFSys(){
		std::map<std::string,wwwAnalysis::JetTagSFSys >::iterator mapit;
		mapit = m_mJetTagSF.find(m_sCurrentSystematic);
		if (mapit!= m_mJetTagSF.end()) return mapit->second;
		return JetTagSFSysOff;
}
wwwAnalysis::JetFlavorSys wwwAnalysis::SystematicsConfig::getCurrentJetFlavorSys(){
		std::map<std::string,wwwAnalysis::JetFlavorSys >::iterator mapit;
		mapit = m_mJetFlavor.find(m_sCurrentSystematic);
		if (mapit!= m_mJetFlavor.end()) return mapit->second;
		return JetFlavorSysOff;
}
wwwAnalysis::JetResolutionSys wwwAnalysis::SystematicsConfig::getCurrentJetResolutionSys(){
		std::map<std::string,wwwAnalysis::JetResolutionSys >::iterator mapit;
		mapit = m_mJetResolution.find(m_sCurrentSystematic);
		if (mapit!= m_mJetResolution.end()) return mapit->second;
		return JetResolutionSysOff;
}

wwwAnalysis::MxMSys wwwAnalysis::SystematicsConfig::getCurrentMxMSys(){
		std::map<std::string,wwwAnalysis::MxMSys >::iterator mapit;
		mapit = m_mMxM.find(m_sCurrentSystematic);
		if (mapit!= m_mMxM.end()) return mapit->second;
		return MxMSysOff;
}

void wwwAnalysis::SystematicsConfig::resetQueue(){
	m_sCurrentSystematic="";

}


bool wwwAnalysis::SystematicsConfig::switchExists(std::string switchKey){
	if(m_mSwitchboard.find(switchKey) == m_mSwitchboard.end()) return false;

	return true;

}

bool wwwAnalysis::SystematicsConfig::switchOn(std::string switchKey){
	if (!switchExists(switchKey)) {
		std::cout << "WARNING in SystematicsConfig::switchOn variation '"<<switchKey<<"' does not exist" << std::endl;
		return false;
	}
	m_mSwitchboard[switchKey] = true;
	return true;

}
bool wwwAnalysis::SystematicsConfig::switchOff(std::string switchKey){
	if (!switchExists(switchKey)) {
		std::cout << "WARNING in SystematicsConfig::switchOff variation '"<<switchKey<<"' does not exist" << std::endl;
		return false;
	}
	m_mSwitchboard[switchKey] = false;
	return true;

}
bool wwwAnalysis::SystematicsConfig::switchOnCategory(std::string category,bool switchValue){
	if (category=="MuonEff"){
		m_mSwitchboard["MuonEffUp"] = switchValue;
		m_mSwitchboard["MuonEffDown"] = switchValue;
		return true;
	}
	if (category=="MuonMom"){
		m_mSwitchboard["MuonMomMSUp"] = switchValue;
		m_mSwitchboard["MuonMomMSDown"] = switchValue;
		m_mSwitchboard["MuonMomIDUp"] = switchValue;
		m_mSwitchboard["MuonMomIDDown"] = switchValue;
		m_mSwitchboard["MuonMomScaleUp"] = switchValue;
		m_mSwitchboard["MuonMomScaleDown"] = switchValue;
		return true;
	}
	if (category=="ElectronEff"){
		m_mSwitchboard["ElectronEffRecoUp"] = switchValue;
		m_mSwitchboard["ElectronEffRecoDown"] = switchValue;
		m_mSwitchboard["ElectronEffIDUp"] = switchValue;
		m_mSwitchboard["ElectronEffIDDown"] = switchValue;
		return true;
	}
	if (category=="ElectronEnergyScale"){
		m_mSwitchboard["ElectronEnergyScaleZeeStatUp"] = switchValue;
		m_mSwitchboard["ElectronEnergyScaleZeeStatDown"] = switchValue;
		m_mSwitchboard["ElectronEnergyScaleZeeMethUp"] = switchValue;
		m_mSwitchboard["ElectronEnergyScaleZeeMethDown"] = switchValue;
		m_mSwitchboard["ElectronEnergyScaleZeeGenUp"] = switchValue;
		m_mSwitchboard["ElectronEnergyScaleZeeGenDown"] = switchValue;
		m_mSwitchboard["ElectronEnergyScaleMaterialUp"] = switchValue;
		m_mSwitchboard["ElectronEnergyScaleMaterialDown"] = switchValue;
		m_mSwitchboard["ElectronEnergyScalePresamplerUp"] = switchValue;
		m_mSwitchboard["ElectronEnergyScalePresamplerDown"] = switchValue;
		m_mSwitchboard["ElectronEnergyScaleLowPtUp"] = switchValue;
		m_mSwitchboard["ElectronEnergyScaleLowPtDown"] = switchValue;
		return true;
	}
	if (category=="ElectronEnergySmearing"){
		m_mSwitchboard["ElectronEnergySmearingUp"] = switchValue;
		m_mSwitchboard["ElectronEnergySmearingDown"] = switchValue;
		return true;
	}
	if (category=="MissingEtScale"){
		m_mSwitchboard["MissingEtSoftTermsScaleUp"] = switchValue;
		m_mSwitchboard["MissingEtSoftTermsScaleDown"] = switchValue;
		return true;
	}
	if (category=="MissingEtReso"){
		m_mSwitchboard["MissingEtSoftTermsResoUp"] = switchValue;
		m_mSwitchboard["MissingEtSoftTermsResoDown"] = switchValue;
		return true;
	}
	if (category=="TriggerSF"){
	  	m_mSwitchboard["TriggerSFElectronUp"] = switchValue;
	  	m_mSwitchboard["TriggerSFElectronDown"] = switchValue;
	  	m_mSwitchboard["TriggerSFMuonUp"] = switchValue;
	  	m_mSwitchboard["TriggerSFMuonDown"] = switchValue;
		return true;
	}
	if (category=="JetEnergyScale"){
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_1Up"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_1Down"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_2Up"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_2Down"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_3Up"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_3Down"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_4Up"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_4Down"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_5Up"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_5Down"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_6restTermUp"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEffectiveNP_6restTermDown"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEtaIntercalibration_ModellingUp"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEtaIntercalibration_ModellingDown"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEtaIntercalibration_StatAndMethodUp"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleEtaIntercalibration_StatAndMethodDown"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleSingleParticle_HighPtUp"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleSingleParticle_HighPtDown"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleRelativeNonClosure_Pythia8Up"] = switchValue;
	  	m_mSwitchboard["JetEnergyScaleRelativeNonClosure_Pythia8Down"] = switchValue;
		return true;
	}
	if (category=="JetPileup"){
  	  	m_mSwitchboard["JetPileupNPVUp"] = switchValue;
  	  	m_mSwitchboard["JetPileupNPVDown"] = switchValue;
  	  	m_mSwitchboard["JetPileupMuUp"] = switchValue;
  	  	m_mSwitchboard["JetPileupMuDown"] = switchValue;
  	  	m_mSwitchboard["JetPileupPtUp"] = switchValue;
  	  	m_mSwitchboard["JetPileupPtDown"] = switchValue;
  	  	m_mSwitchboard["JetPileupRhoTopoUp"] = switchValue;
  	  	m_mSwitchboard["JetPileupRhoTopoDown"] = switchValue;
		m_mSwitchboard["JetVertexFractionUp"] = switchValue;
		m_mSwitchboard["JetVertexFractionDown"] = switchValue;
		return true;
	}
	if (category=="Pileup"){
		m_mSwitchboard["PileupUp"] = switchValue;
		m_mSwitchboard["PileupDown"] = switchValue;
	}
	if (category=="JetTagSF"){
  		m_mSwitchboard["JetCTTagSFUp"] = switchValue;
  		m_mSwitchboard["JetCTTagSFDown"] = switchValue;
  		m_mSwitchboard["JetMisTagSFUp"] = switchValue;
  		m_mSwitchboard["JetMisTagSFDown"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV1Up"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV1Down"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV2Up"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV2Down"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV3Up"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV3Down"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV4Up"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV4Down"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV5Up"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV5Down"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV6Up"] = switchValue;
  		m_mSwitchboard["JetBTagSFEV6Down"] = switchValue;
		/*
  		m_mSwitchboard["JetBTagSFEV7Up"] = true;
  		m_mSwitchboard["JetBTagSFEV7Down"] = true;
  		m_mSwitchboard["JetBTagSFEV8Up"] = true;
  		m_mSwitchboard["JetBTagSFEV8Down"] = true;
  		m_mSwitchboard["JetBTagSFEV9Up"] = true;
  		m_mSwitchboard["JetBTagSFEV9Down"] = true;
  		m_mSwitchboard["JetBTagSFEV10Up"] = true;
  		m_mSwitchboard["JetBTagSFEV10Down"] = true;
		*/
		return true;
	}
	if (category=="JetFlavor"){
  		m_mSwitchboard["JetFlavorCompositionUp"] = switchValue;
  		m_mSwitchboard["JetFlavorCompositionDown"] = switchValue;
  		m_mSwitchboard["JetFlavorResponseUp"] = switchValue;
  		m_mSwitchboard["JetFlavorResponseDown"] = switchValue;
		m_mSwitchboard["JetFlavorBJESUp"] = switchValue;
		m_mSwitchboard["JetFlavorBJESDown"] = switchValue;
		return true;
	}
	if (category=="JetReso"){
		m_mSwitchboard["JetResolution"] = switchValue;
		return true;
	}

	if (category=="ChargeMisID"){
		m_mSwitchboard["ChargeMisIDUp"] = switchValue;
		m_mSwitchboard["ChargeMisIDDown"] = switchValue;
		return true;
	}

	if (category=="MxM"){
	  	m_mSwitchboard["MxMElUp"] = switchValue;
	  	m_mSwitchboard["MxMElDown"] = switchValue;
	  	m_mSwitchboard["MxMMuUp"] = switchValue;
	  	m_mSwitchboard["MxMMuDown"] = switchValue;
	  	m_mSwitchboard["MxMBJetAlt"] = switchValue;
	  	m_mSwitchboard["MxMBJetAltFlipped"] = switchValue;
	  	//m_mSwitchboard["MxMBJetGt0"] = true;
		return true;
	}


	return false;
}

bool wwwAnalysis::SystematicsConfig::switchOnAll(){
	for(mapit_type it = m_mSwitchboard.begin(); it != m_mSwitchboard.end(); it++)
		m_mSwitchboard[it->first]=true;
	return true;

}
bool wwwAnalysis::SystematicsConfig::switchOffAll(){
	for(mapit_type it = m_mSwitchboard.begin(); it != m_mSwitchboard.end(); it++)
		m_mSwitchboard[it->first]=false;
	//only do central value
	m_mSwitchboard["Central"] = true;
	return true;

}

void wwwAnalysis::SystematicsConfig::print() {
	std::cout << "***************************" << std::endl;
	std::cout << "Systematics configured for:" << std::endl;
	for(mapit_type it = m_mSwitchboard.begin(); it != m_mSwitchboard.end(); it++)
		if (it->second) std::cout << "\t" << it->first << std::endl;

	std::cout << "***************************" << std::endl;


}


