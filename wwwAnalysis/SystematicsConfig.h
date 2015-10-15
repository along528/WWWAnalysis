
#ifndef SYSTEMATICSCONFIG_H
#define SYSTEMATICSCONFIG_H

#include <map>
#include <string>
typedef std::map<std::string,bool>::iterator mapit_type;
namespace wwwAnalysis{
    enum Systematic{
    	up,down,off

    };
    	  enum MxMSys{
	  	MxMElUp,
	  	MxMElDown,
	  	MxMMuUp,
	  	MxMMuDown,
		MxMBJetAlt,
		MxMBJetAltFlipped,
	  	MxMSysOff
	  };
    	  enum ChargeMisIDSys{
	  	ChargeMisIDUp,
	  	ChargeMisIDDown,
	  	ChargeMisIDSysOff
	  };
	  enum JESSys{
		JESEffectiveNP_1Up,
		JESEffectiveNP_1Down,
		JESEffectiveNP_2Up,
		JESEffectiveNP_2Down,
		JESEffectiveNP_3Up,
		JESEffectiveNP_3Down,
		JESEffectiveNP_4Up,
		JESEffectiveNP_4Down,
		JESEffectiveNP_5Up,
		JESEffectiveNP_5Down,
		JESEffectiveNP_6restTermUp,
		JESEffectiveNP_6restTermDown,
		JESEtaIntercalibration_ModellingUp,
		JESEtaIntercalibration_ModellingDown,
		JESEtaIntercalibration_StatAndMethodUp,
		JESEtaIntercalibration_StatAndMethodDown,
		JESSingleParticle_HighPtUp,
		JESSingleParticle_HighPtDown,
		JESRelativeNonClosure_Pythia8Up,
		JESRelativeNonClosure_Pythia8Down,
		JESSysOff
	  };

	  enum JetPileupSys{
		JetPileupNPVUp,
		JetPileupNPVDown,
		JetPileupMuUp,
		JetPileupMuDown,
		JetPileupPtUp,
		JetPileupPtDown,
		JetPileupRhoTopoUp,
		JetPileupRhoTopoDown,
		JetPileupSysOff
	  };
	  enum JetFlavorSys{
		JetFlavorCompositionUp,
		JetFlavorCompositionDown,
		JetFlavorResponseUp,
		JetFlavorResponseDown,
		JetFlavorBJESUp,
		JetFlavorBJESDown,
		JetFlavorSysOff
	  };
	  enum PileupSys{
		PileupUp,
		PileupDown,
		PileupSysOff
	  };

	  enum JVFSys{
		JVFUp,
		JVFDown,
		JVFSysOff
	  };
	  enum JetTagSFSys{
		JetCTTagSFUp,
		JetCTTagSFDown,
		JetMisTagSFUp,
		JetMisTagSFDown,
		JetBTagSFEV1Up,
		JetBTagSFEV1Down,
		JetBTagSFEV2Up,
		JetBTagSFEV2Down,
		JetBTagSFEV3Up,
		JetBTagSFEV3Down,
		JetBTagSFEV4Up,
		JetBTagSFEV4Down,
		JetBTagSFEV5Up,
		JetBTagSFEV5Down,
		JetBTagSFEV6Up,
		JetBTagSFEV6Down,
		JetBTagSFEV7Up,
		JetBTagSFEV7Down,
		JetBTagSFEV8Up,
		JetBTagSFEV8Down,
		JetBTagSFEV9Up,
		JetBTagSFEV9Down,
		JetBTagSFEV10Up,
		JetBTagSFEV10Down,
		JetTagSFSysOff
	  };

	  enum JetResolutionSys{
		JetResolutionSysOn,
		JetResolutionSysOff
	  };
	  enum MuonMomSys { IDUP,IDLOW,MSUP,MSLOW,SCALELOW,SCALEUP,MuonMomSysOff }; 
	  enum MuonEffSys { MuonEffUp,MuonEffDown,MuonEffSysOff }; 
	  enum ElectronEffSys { ElRecoEffUp,ElRecoEffDown,ElIDEffUp,ElIDEffDown,ElectronEffSysOff }; 
	  //Energy Scale uncertainties are symmetric
	  enum ElectronEnergyScaleSys { 
		ElScaleZeeStatUp,
		ElScaleZeeStatDown,
		ElScaleZeeMethUp,
		ElScaleZeeMethDown,
		ElScaleZeeGenUp,
		ElScaleZeeGenDown,
		ElScaleMaterialUp,
		ElScaleMaterialDown,
		ElScalePresamplerUp,
		ElScalePresamplerDown,
		ElScaleLowPtUp,
		ElScaleLowPtDown,
		ElectronEnergyScaleSysOff 
	  };
	  enum ElectronEnergySmearingSys {
		ElEnergySmearingUp,
		ElEnergySmearingDown,
		ElectronEnergySmearingSysOff
	  };
	  enum TriggerSFSys{
		TrigSFElUp,
		TrigSFElDown,
		TrigSFMuUp,
		TrigSFMuDown,
		TriggerSFSysOff
	  };
	  enum METSoftTermsSys{
		METSoftTermsScaleUp,
		METSoftTermsScaleDown,
		METSoftTermsResoUp,
		METSoftTermsResoDown,
		METSoftTermsSysOff
	  };

    class SystematicsConfig{
    	public:
		SystematicsConfig();
		~SystematicsConfig();

		bool next();
		void print();
		bool switchOnAll();
		bool switchOffAll();
		bool switchOnCategory(std::string,bool = true);
		bool switchOn(std::string);
		bool switchOff(std::string);
		bool switchExists(std::string );
		std::string getCurrentSystematic();
		void resetQueue();

		MuonEffSys getCurrentMuonEffSys();
		MuonMomSys getCurrentMuonMomSys();
		ElectronEffSys getCurrentElectronEffSys();
		ElectronEnergyScaleSys getCurrentElectronEnergyScaleSys();
		ElectronEnergySmearingSys getCurrentElectronEnergySmearingSys();
		METSoftTermsSys getCurrentMETSoftTermsSys();
		TriggerSFSys getCurrentTriggerSFSys();
		JESSys getCurrentJESSys();
		JetPileupSys getCurrentJetPileupSys();
		JVFSys getCurrentJVFSys();
		PileupSys getCurrentPileupSys();
		JetTagSFSys getCurrentJetTagSFSys();
		JetFlavorSys getCurrentJetFlavorSys();
		JetResolutionSys getCurrentJetResolutionSys();
		ChargeMisIDSys getCurrentChargeMisIDSys();
		MxMSys getCurrentMxMSys();
	protected:
		std::map<std::string,bool> m_mSwitchboard;
		std::map<std::string,wwwAnalysis::MuonEffSys> m_mMuonEff;
		std::map<std::string,wwwAnalysis::MuonMomSys> m_mMuonMom;
		std::map<std::string,wwwAnalysis::ElectronEffSys> m_mElectronEff;
		std::map<std::string,wwwAnalysis::ElectronEnergyScaleSys> m_mElectronEnergyScale;
		std::map<std::string,wwwAnalysis::ElectronEnergySmearingSys> m_mElectronEnergySmearing;
		std::map<std::string,wwwAnalysis::METSoftTermsSys> m_mMissingEtSoftTerms;
		std::map<std::string,wwwAnalysis::TriggerSFSys> m_mTriggerSF;
		std::map<std::string,wwwAnalysis::JESSys> m_mJetEnergyScale;
		std::map<std::string,wwwAnalysis::JetPileupSys> m_mJetPileup;
		std::map<std::string,wwwAnalysis::JVFSys> m_mJVF;
		std::map<std::string,wwwAnalysis::PileupSys> m_mPileup;
		std::map<std::string,wwwAnalysis::JetTagSFSys> m_mJetTagSF;
		std::map<std::string,wwwAnalysis::JetFlavorSys> m_mJetFlavor;
		std::map<std::string,wwwAnalysis::JetResolutionSys> m_mJetResolution;
		std::map<std::string,wwwAnalysis::ChargeMisIDSys> m_mChargeMisID;
		std::map<std::string,wwwAnalysis::MxMSys> m_mMxM;
		std::string m_sCurrentSystematic;

    };
};

#endif
