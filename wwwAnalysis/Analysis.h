#ifndef wwwAnalysis_Analysis_H
#define wwwAnalysis_Analysis_H

#include <EventLoop/Algorithm.h>
#include <D3PDReader/Event.h>


#include <TH1.h>
#include <TH3F.h>
#include <TString.h>
#include <TFile.h>


#include <GoodRunsLists/TGoodRunsListReader.h>
#include <MuonMomentumCorrections/SmearingClass.h>
#include <egammaAnalysisUtils/EnergyRescaler.h>
#include <ApplyJetCalibration/ApplyJetCalibration.h>
#include <PileupReweighting/TPileupReweighting.h>
#include <CalibrationDataInterface/CalibrationDataInterfaceROOT.h>
#include <JetSelectorTools/TJetCleaningTool.h>
#include "CrossSectionTool/CrossSectionTool.h"
#include "ChargeMisIDTool/ChargeMisIDTool.h"
#include "GeneralisedMatrixMethod/MatrixMethodWWW.h"
#include <SampleHandler/SampleHandler.h>
#include "FormFactorReweightingTool/FFReweight.h"


#include <vector>
#include <algorithm>

#include "TElectronSelectorTool.h"
#include "TMuonSelectorTool.h"
#include "TTauSelectorTool.h"
#include "TJetSelectorTool.h"
#include "TEventSelectorTool.h"
#include "TriggerTool.h"
//#include "XSecTool.h"
#include "Electron.h"
#include "Muon.h"
#include "Tau.h"
#include "Jet.h"
#include "MissingEt.h"
#include "Output.h"
#include "TruthOutput.h"
#include "SystematicsConfig.h"
#include "Functions.h"

typedef std::map<TString,int> mapEventSelectorIndexInner_t;
typedef std::map<TString,mapEventSelectorIndexInner_t> mapEventSelectorIndexOuter_t;
//#ifdef __MAKECINT__
//#endif

//template class std::vector< GeneralisedMatrixMethodWWW::MatrixMethodWWW::Result >;

class TFile;
class TTree;

// *****************************************************************
// **** Please note ************************************************
// *****************************************************************
// variables that don't get filled at submission time should be
// protected from being send from the submission node to the worker
// node (done by the //!)
// *****************************************************************

namespace wwwAnalysis
{


class Analysis : public EL::Algorithm
{
public:
  // this is needed to distribute the algorithm to the workers
  ClassDef(Analysis, 1);

  // *** Event related things here ***************************

  D3PDReader::Event *m_pEvent;  //!
  unsigned int m_iRunNumber; //!
  double m_fMu; //!
  bool m_bIsMC; //!
  bool m_bIsEGammaStream; //!

  ShoweringGenerator m_eShoweringGenerator; //!
  std::vector<Electron> m_vElectrons; //!
  std::vector<Electron> m_vElectronsAll; //!
  std::vector<Electron> m_vTauElectrons; //!
  std::vector<Electron> m_vElectronsFake; //!
  std::vector<Electron> m_vElectronsInc; //!
  std::vector<Electron> m_vElectronsTight; //!
  std::vector<Electron> m_vElectronsLoose; //!
  std::vector<Electron> m_vElectronsLooseNotTight; //!
  std::vector<Muon> m_vMuons; //!
  std::vector<Muon> m_vMuonsInc; //!
  std::vector<Muon> m_vMuonsTight; //!
  std::vector<Muon> m_vMuonsLoose; //!
  std::vector<Muon> m_vMuonsLooseNotTight; //!
  std::vector<Muon> m_vMuonsAll; //!
  std::vector<Muon> m_vTauMuons; //!
  std::vector<Muon> m_vMuonsFake; //!
  std::vector<Tau> m_vTaus; //!
  std::vector<Jet> m_vJets; //!
  std::vector<Jet> m_vJetsLoose; //!
  std::vector<Jet> m_vJetsAll; //!

  int m_nleptons;//!
  std::vector<PhysicsObject* > m_pTaggedLeptons; //!
  std::vector<PhysicsObject* > m_pAllLeptons; //!
  std::vector<PhysicsObject* > m_pTaggedLooseNotTightLeptons; //!
  std::vector<PhysicsObject* > m_pTaggedLooseLeptons; //!
  std::vector<PhysicsObject* > m_pTaggedLeptonsInc; //!
  std::vector<PhysicsObject* > m_pTaggedLeptonsFake; //!
  std::vector<PhysicsObject* > m_pTPTags; //!
  std::vector<PhysicsObject* > m_pTPTags2; //!
  std::vector<PhysicsObject* > m_pTPProbes; //!
  std::vector<PhysicsObject > m_vTaggedLeptonsMxM; //!
  std::vector<Muon > m_vTaggedMuonsMxM; //!
  std::vector<Electron > m_vTaggedElectronsMxM; //!
  std::vector<GeneralisedMatrixMethodWWW::MatrixMethodWWW::Lepton> m_vTaggedLeptons_MMLepton; //!


  MissingEt *m_pMET; //!
 
  // *** Tools here ****************************************** Remember that we need to configure them later.

  bool m_bHybrid;
  Root::TGoodRunsListReader *m_hGoodRunsListReader;
  Root::TPileupReweighting *m_hPileupTool;
  Root::TPileupReweighting *m_hPileupToolUp;
  Root::TPileupReweighting *m_hPileupToolDown;
  Root::TPileupReweighting *m_hPileupWriteTool; 
  Root::TJetCleaningTool *m_hJetCleaningTool;
  GeneralisedMatrixMethodWWW::MatrixMethodWWW * m_pMatrixMethodWWW;  
  GeneralisedMatrixMethodWWW::MatrixMethodWWW * m_pMatrixMethodWWWAlt;  
  GeneralisedMatrixMethodWWW::MatrixMethodWWW * m_pMatrixMethodWWWAltFlipped;  
  void setMatrixMethodConfig(std::string elReal,std::string muReal,std::string elFake,std::string muFake){
	  m_sElectronRealRate = elReal;
	  m_sMuonRealRate = muReal;
	  m_sElectronFakeRate = elFake;
	  m_sMuonFakeRate = muFake;
  	
  }
  std::map<TString,TElectronSelectorTool *> m_hElectronSelectorTools; 
  std::map<TString,TElectronSelectorTool *> m_hElectronLooseSelectorTools; 
  std::map<TString,TMuonSelectorTool *> m_hMuonSelectorTools; 
  std::map<TString,TMuonSelectorTool *> m_hMuonLooseSelectorTools; 
  std::map<TString,TMuonSelectorTool *> m_hMuonNoQualitySelectorTools; 
  std::map<TString,TTauSelectorTool *> m_hTauSelectorTools; 
  std::map<TString,TJetSelectorTool *> m_hJetSelectorTools; 
  std::map<TString,TElectronSelectorTool *> m_hFakeElectronSelectorTools;  
  std::map<TString,TElectronSelectorTool *> m_hElectronNoQualitySelectorTools;  
  std::map<TString,TMuonSelectorTool *> m_hFakeMuonSelectorTools; 
  std::map<TString,TElectronSelectorTool *> m_hTauElectronSelectorTools; 
  std::map<TString,TMuonSelectorTool *> m_hTauMuonSelectorTools; 
  std::map<TString,TJetSelectorTool *> m_hJetLooseSelectorTools; 
  FFReweight *m_hFormFactorReweightingTool;
  TriggerTool *m_hTriggerTool;
  SH::SampleHandler m_hSampleHandler;
  CrossSectionTool *m_hCrossSectionTool;  
  WWW::ChargeMisIDTool *m_hChargeMisIDTool;  
  struct SystematicsConfig *m_pSystematics; 

  std::string m_sElectronRealRate;
  std::string m_sMuonRealRate;
  std::string m_sElectronFakeRate;
  std::string m_sMuonFakeRate;


  wwwAnalysis::MuonEffSys m_sysMuonEff;
  wwwAnalysis::MuonMomSys m_sysMuonMom;
  wwwAnalysis::ElectronEffSys m_sysElectronEff;
  wwwAnalysis::ElectronEnergyScaleSys m_sysElectronEnergyScale;
  wwwAnalysis::ElectronEnergySmearingSys m_sysElectronEnergySmearing;
  wwwAnalysis::METSoftTermsSys m_sysMETSoftTerms;
  wwwAnalysis::TriggerSFSys m_sysTrigSF;
  wwwAnalysis::JESSys m_sysJES;
  wwwAnalysis::JetPileupSys m_sysJetPileup;
  wwwAnalysis::JVFSys m_sysJVF;
  wwwAnalysis::JetTagSFSys m_sysJetTagSF;
  wwwAnalysis::JetFlavorSys m_sysJetFlavor;
  wwwAnalysis::JetResolutionSys m_sysJetResolution;
  wwwAnalysis::ChargeMisIDSys m_sysChargeMisID;
  wwwAnalysis::PileupSys m_sysPileup;
  wwwAnalysis::MxMSys m_sysMxM;

  int m_iNPV_2trks;
  int m_iNPV_3trks;
  int m_iNBTag;
  double m_fMcWeight;
  double m_fSFWeight;
  double m_fPuWeight;
  double m_fJetTagWeight60;
  double m_fJetTagWeight70;
  double m_fJetTagWeight80;
  double m_fJetTagWeight85;
  double m_fTrigWeight;
  double m_fMxMWeight;
  double m_fXSecWeight;
  double m_fChargeMisIDWeight;
  double m_fFormFactorWeight;
  bool m_bHasLooseNotTightElectrons;
  bool m_bHasLooseNotTightMuons;
  bool m_bIsFake;
  bool m_bIsTriggerMatched;
  bool m_bDoChargeFlip;
  bool m_bElectronIsCentral ;
  bool m_bMuonIsCentral     ;
  bool m_bJetIsCentral      ;
  bool m_bTriggerIsCentral  ;
  bool m_bMETIsCentral      ;
  bool m_bJetTagSFIsCentral ;
  bool m_bMiscWeightIsCentral ;
  bool m_bLepMETSFIsCentral ;
  bool m_bUpdateElectrons;
  bool m_bUpdateMuons;
  bool m_bUpdateJets;
  bool m_bUpdateMET;
  bool m_bUpdateMiscWeights;
  bool m_bUpdateJetTagSFWeights;
  bool m_bUpdateTrigSFWeights;
  bool m_bUpdateLepMETSFWeights;
  int  m_iChargeFlipContainerIndex;


	void addObjectSelector(const TString & ,Root::TSelectorToolBase *, const TString & = "");
	void addElectronSelector(const TString & ,TElectronSelectorTool *, const TString & = "");
	void addMuonSelector(const TString & ,TMuonSelectorTool *, const TString & = "");
	void addTauSelector(const TString & ,TTauSelectorTool *, const TString & = "");
	void addJetSelector(const TString & ,TJetSelectorTool *, const TString & = "");
	void addEventSelector(const TString &, TEventSelectorTool *, bool = false,const TString & = "");
	std::vector<TString> m_vEventSelectorNames;
	std::vector<TString> m_vEventSelectorBaseNames;
  std::map<int, TEventSelectorTool *> m_hEventSelectorTools;
  mapEventSelectorIndexOuter_t m_mEventSelectorIndex; 
  std::vector<int> m_vMVA;
  std::vector<int> m_vCat;
  std::vector<bool> m_vSave;
  std::vector<GeneralisedMatrixMethodWWW::MatrixMethodWWW::Result> m_vMxMRawResults;
  bool m_bSaveTruthInfo;
  bool m_bDoMxM;
  bool m_bApplyUnitarization; 
  bool m_bDoZTagAndProbe;
  bool m_bDoZPlusJetsTagAndProbe;
  bool m_bDoZPlusGammaTagAndProbe;
  bool m_bDoFakeTagAndProbe;
  bool m_bDoFakeTagAndProbeInclusiveSign;
  void saveTruthInfo(bool save ){m_bSaveTruthInfo = save;};
  void setDoMxM(bool bSwitch); 
  void setApplyUnitarization(bool bSwitch){m_bApplyUnitarization = bSwitch;};

  // *** Tools here *****************************************
  Root::TGoodRunsList m_oGoodRunsList; //!
  // *** HISTOS here *****************************************

  // *** Cut Flows here **************************************
  std::map<TString,TH1 *> m_pCutFlowElectrons; //!
  std::map<TString,TH1 *> m_pCutFlowElectronsLoose; //!
  std::map<TString,TH1 *> m_pCutFlowElectronsNoQuality; //!
  std::map<TString,TH1 *> m_pCutFlowMuons; //!
  std::map<TString,TH1 *> m_pCutFlowMuonsLoose; //!
  std::map<TString,TH1 *> m_pCutFlowMuonsNoQuality; //!
  std::map<TString,TH1 *> m_pCutFlowTaus; //!
  std::map<TString,TH1 *> m_pCutFlowJets; //!

  std::map<TString,TH1 *> m_pCutFlowElectronsFake; //!
  std::map<TString,TH1 *> m_pCutFlowMuonsFake; //!

  std::vector<TH1 *> m_vCutFlow; //!
  std::vector<TH1 *> m_vCutFlowEvents; //!
  std::vector<TH1 *> m_vCutFlowEventsTrig; //!
  std::vector<TH1 *> m_vCutFlowEventsTrigPu; //!
  std::vector<TH1 *> m_vCutFlowEventsTrigPuLep; //!
  std::vector<TH1 *> m_vCutFlowEventsTrigPuLepBTag; //!
  std::vector<TH1 *> m_vCutFlowEventsTrigPuLepBTagXSec; //!
  std::vector<TH1 *> m_vCutFlowEventsTrigPuLepBTagXSecCharge; //!
  std::vector<TH1 *> m_vCutFlowEventsTrigPuLepBTagXSecChargeMxM; //!
  std::vector<TH1 *> m_vCutFlowEventsTrigPuLepBTagXSecChargeMxMFormFactor; //!
  //kept for backwards compatibility
  std::vector<TH1 *> m_vCutFlowEventsLepLepPuBTagTrigXSec; //!
  
  /*
  std::vector<std::map< TString,double> > m_vCutFlowEventsMap; //!
  std::vector<std::map< TString,double> > m_vCutFlowEventsLepLepMap; //!
  std::vector<std::map< TString,double> > m_vCutFlowEventsLepLepPuMap; //!
  std::vector<std::map< TString,double> > m_vCutFlowEventsLepLepPuBTagMap; //!
  std::vector<std::map< TString,double> > m_vCutFlowEventsLepLepPuBTagTrigMap; //!
  std::vector<std::map< TString,double> > m_vCutFlowEventsLepLepPuBTagTrigXSecMap; //!
  */
	
  // *** Other things ****************************************
  std::map<TString, Output *> m_pOut; //!
  std::map<TString, TruthOutput *> m_pTruthOut; //!
  static std::map<int,std::map<int, int> > m_mRunEvents; //!

  //Add a structure to pass information from TEventSelector to the output avoid recomputing info multiple times..
  //structure location in Functions.h:
  OutputInformations AdditionnalInfo;
  
 
  // this is a standard constructor
  Analysis ();
  virtual ~Analysis();
  
  // helper functions to setup the event PhysicsObjects
  template<class T>
  static void sortPt(std::vector<T> &);
  template<class T>
  static void sortPt_p(std::vector<T*> &);
  template<class T>
  static bool compare(const T &, const T &);
  template<class T>
  static bool compare_p(const T *, const T *);
  void tagObjects();


  // cutflow helper functions
  static const Root::TAccept &fillCutFlow(TH1 *, const Root::TAccept &, double = 1.0);
  static const Root::TAccept &fillCutFlow(std::map<TString,double> , const Root::TAccept &, double  = 1.0);
  static TH1 *createCutFlow(const Root::TAccept &, const char *, bool = true);
  static std::map<TString,double> createCutFlow(const Root::TAccept &, bool = true);

  void fillCutFlows(int, const Root::TAccept &, double, double, double, double, double, double,double,double,double);
  void fillCutFlows(const char *, double,std::string);
  void printPassedEvents(const Root::TAccept &, std::string ,int ,int , int );
  void resetAdditionnalInfo();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  int selectEvent (std::string);
  int selectObjectsMxM (unsigned int , std::string );
  int buildEvent (std::string);

  virtual EL::StatusCode finalize ();



};

template<class T>
void Analysis :: sortPt(std::vector<T> &PhysicsObjects)
{
  std::sort(PhysicsObjects.begin(), PhysicsObjects.end(), compare<T>);
}
template<class T>
bool Analysis :: compare(const T &o1, const T&o2)
{
  return o1.momentum().Pt() > o2.momentum().Pt();
}

template<class T>
void Analysis :: sortPt_p(std::vector<T*> &PhysicsObjects)
{
  std::sort(PhysicsObjects.begin(), PhysicsObjects.end(), compare_p<T>);
}
template<class T>
bool Analysis :: compare_p(const T *o1, const T *o2)
{
  return o1->momentum().Pt() > o2->momentum().Pt();
}

}
#endif
