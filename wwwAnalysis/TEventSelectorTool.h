// Dear emacs, this is -*-c++-*-

#ifndef __TEVENTSELECTORTOOL__
#define __TEVENTSELECTORTOOL__

/**
   @class TEventSelectorTool
   @brief Example tool to select PhysicsObjects in pure ROOT

   @author Karsten Koeneke (CERN)
   @date   April 2011
*/


// ROOT includes
#include <TString.h>

#include <vector>
#include <map>

#include <D3PDReader/Event.h>

// Include the return PhysicsObject and the base class
#include "PATCore/TAccept.h"
#include "PATCore/TSelectorToolBase.h"

#include "wwwAnalysis/Electron.h"
#include "wwwAnalysis/Muon.h"
#include "wwwAnalysis/Tau.h"
#include "wwwAnalysis/Jet.h"
#include "wwwAnalysis/MissingEt.h"
#include "wwwAnalysis/Functions.h"


/*
#ifdef __MAKECINT__
#pragma link C++ class std::vector<std::pair<const wwwAnalysis::PhysicsObject *,const wwwAnalysis::PhysicsObject * > >;
#endif

*/
//typedef class std::vector < std::pair <const wwwAnalysis::PhysicsObject *,const wwwAnalysis::PhysicsObject * > > PhysicsObjectPair;
typedef std::pair <const wwwAnalysis::PhysicsObject *,const wwwAnalysis::PhysicsObject * > PhysicsObjectPair;
namespace wwwAnalysis {
  


  enum PairType
  {
  	SFOS=0, //Same Flavor opposite sign
  	SFSS, //Same Flavor same sign
	OFOS, //Opposite Flavor Opposite sign
	OFSS  //Opposite Flavor Same sign
  };
  class TEventSelectorTool : public Root::TSelectorToolBase
  {

  public: 
    /** Standard constructor */
    TEventSelectorTool(const char* name="TEventSelectorTool");

    /** Standard destructor */
    virtual ~TEventSelectorTool();

#ifdef ROOTCORE
    /** For PROOF streaming */
    ClassDef(TEventSelectorTool,1);
#endif

    // Main methods
  public:
    /** Initialize this class */
    int initialize();

    /** Finalize this class; everything that should be done after the event loop should go here */
    inline int finalize() { return 1; };

    /**
     * The main accept method: the actual cuts are applied here
     * Assumes that all the PhysicsObjects are sorted by descending Pt
     */
    const Root::TAccept& accept(const D3PDReader::Event &,
				const vector<wwwAnalysis::PhysicsObject *> &,
				const vector<wwwAnalysis::PhysicsObject *> &,
				const vector<wwwAnalysis::PhysicsObject *> &,
				const vector<wwwAnalysis::PhysicsObject *> &,
				const vector<wwwAnalysis::PhysicsObject *> &,
				const vector<wwwAnalysis::PhysicsObject *> &,
				const vector<wwwAnalysis::PhysicsObject *> &,
				const std::vector<wwwAnalysis::Tau> &,
				const std::vector<wwwAnalysis::Jet> &,
				const std::vector<wwwAnalysis::Jet> &, const std::vector<wwwAnalysis::Jet> &,
				const TVector2 &, const wwwAnalysis::MissingEt *,
				unsigned int, bool, bool,bool, int, bool, bool,  wwwAnalysis::OutputInformations &);
        
    void clear();


    // Public members (the cut values)
  public:
    int const getNSFOS() { return nSFOS; } ;
    int const getNSFOSAll() { return nSFOSAll; } ;

    vector<double> const getMassesSFOS() { return massesSFOS; } ;
    vector<double> const getMassesSFOSAll() { return massesSFOSAll; } ;
    bool IsLooserBadJet(  const float  &, const float  &, const float  &,
        		   const float  &, const float  &, const float  &,
			   const float  &, const float  &, const float  &,
			   const float  &, const float  &);

    int configuredForNSFOS();
    //std::vector < std::pair <const PhysicsObject *,const PhysicsObject * > >  getSFOSPairs( const std::vector<PhysicsObject*> &leptons);
    std::vector < PhysicsObjectPair >  getSFOSPairs( const std::vector<PhysicsObject*> &leptons);
    //int getNSFOSPairs( const std::vector<PhysicsObject*> &leptons);
    bool doZTagAndProbe(){return CutZTagAndProbe;};
    bool doZPlusJetsTagAndProbe(){return CutZPlusJetsTagAndProbe;};
    bool doZPlusGammaTagAndProbe(){return CutZPlusGammaTagAndProbe;};
    bool doFakeTagAndProbe(){return CutFakeTagAndProbe;};
    bool doFakeTagAndProbeInclusiveSign(){return CutFakeTagAndProbeInclusiveSign;};


    /** truth filter */
    bool CutTruthFilter;

    /** stream overlap cut */
    bool CutStreamOverlap;

    /** trigger cut */
    bool CutTrigger;

    /** do ee trigger cuts */
    bool includeEETrigger;

    /** do emu trigger cuts */
    bool includeEMuTrigger;
    
    /** do mumu trigger cuts */
    bool includeMuMuTrigger;

    /** nPV  cut */
    bool CutNPV;

    /** minimum nPV cut value */
    int nPVMin;


    /** jet cleaning cut */
    bool CutJetCleaning;

    /** HotTile  cut */
    bool CutHotTile;

    /** FCal  cut */
    bool CutFCal;

    /** LArError  cut */
    bool CutLArError;

    /** nLepton cut */
    bool CutDilepton;

    /** total number of muons (defaults to -1 for any) */
    int nMuon;

    /** invariant masses for SFOS pairs */
    vector < double > massesSFOS;

    /** invariant masses for SFOS pairs */
    vector < double > massesSFOSAll;

    /** # SFOS pairs for leptons selected in multi-lepton cut**/
    int nSFOS;

    /** # SFOS pairs for all leptons **/
    int nSFOSAll;

    /** triggermatching cut */
    bool CutTriggerMatching;

    /** three leptons  cut */
    bool CutMultiLeptonsInclusive;

    /** three leptons  cut */
    bool CutMultiLeptonsExclusive;

    /* lepton mult flavor quality */
    bool CutLeptonMultiplictyFlavorQuality;
     
    /* lepton mulitplicity requirements */
    int nLooseNotTightMuonsCut;
    int nLooseNotTightElectronsCut;
    int nLooseMuonsCut;
    int nLooseElectronsCut;
    int nTightMuonsCut;
    int nTightElectronsCut;
    

    /** loose dilepton cut */
    bool CutLooseDilepton;
    bool looseDileptonSameFlavor; 

    /**minimum number of leptons considered default will be three*/
    unsigned int nLeptonsCut;


    /** nTau cut */
    bool CutNTau;

    /** total number of taus (defaults to 0) */
    int nTau;

    /** charge cut */
    bool CutOppositeCharge;

    int CutFakeCharge;


    /** llMassCut */
    bool CutllMass;
    /** minimum  llMassSF cut value */
    double llMassSFMin;

    /** maximum  llMassSF cut value */
    double llMassSFMax;

    /** minimum  llMassDF cut value */
    double llMassDFMin;

    /** maximum  llMassDF cut value */
    double llMassDFMax;

    /** sumPtMin cut */
    bool CutsumPtMin;

    /** minimum  sumPt cut value */
    double sumPtMin;

    /** firstJetPtMin cut */
    bool CutfirstJetPtMin;

    /** minimum  firstJetPt cut value */
    double firstJetPtMin;

    /** minimum  jetJVF cut value */
    double jetJVFMin;

    /** metMin cut */
    bool CutmetMin;
    bool CutmetMinFirst;
    bool CutmetMinSecond;
    bool CutmetMinThird;

    /** switch to STVF in MET selection cut */
    bool useSTVFMetMin;

    /** minimum  met cut value */
    double metMin;

    /** minimum  metSF cut value */
    double metSFMin;

    /** minimum  metDF cut value */
    double metDFMin;

    /** hptoMetMin cut */
    bool CuthptoMetMin;

    /** minimum  hptoMetSF cut value */
    double hptoMetSFMin;

    /** minimum  hptoMetDF cut value */
    double hptoMetDFMin;

    /** x cut */
    bool Cutx;

    /** minimum x cut value */
    double xMin;

    /** maximum x cut value */
    double xMax;

    /** llDeltaPhi cut */
    bool CutllDeltaPhi;

    /** minimum  llDeltaPh cut value */
    double llDeltaPhiMin;

    /** maximum  llDeltaPh cut value */
    double llDeltaPhiMax;

    /** earlybTagVeto cut */
    bool CutearlybTagVeto;

    /** secondJetPtMin cut */
    bool CutsecondJetPtMin;

    /** minimum  secondJetPt cut value */
    double secondJetPtMin;

    /** failing Boosted cut */
    bool CutfailedCutBasedBoosted;

    /** failing VBF MVA cut */
    bool CutfailedMVAVBF;

    /** failing Boosted MVA cut */
    bool CutfailedMVABoosted;

    /** jjDeltaEta Cut */
    bool CutjjDeltaEta;

    /** minimum  jjDeltaEta cut value */
    double jjDeltaEtaMin;

    /** maximum  jjDeltaEta cut value */
    double jjDeltaEtaMax;

    /** jjMass Cut */
    bool CutjjMass;

    /** minimum  jjMass cut value */
    double jjMassMin;

    /** maximum  jjMass cut value */
    double jjMassMax;

    /** failing VBF cut */
    bool CutfailedCutBasedVBF;

   /** higgsPtMin cut */
    bool CuthiggsPtMin;

    /** minimum  higgsPt cut value */
    double higgsPtMin;



    /** failing 2JET Cut */
    bool CutfailedCutBased2JET;

    /** failing VH MVA Cut */
    bool CutfailedMVAVH;

    /** higgsjetMassMin cut */
    bool CuthiggsjetMassMin;

    /** minimum  higgsjetMass cut value */
    double higgsjetMassMin;

    /** 3-lepton Pt cut */
    bool CutThreeLeptonPt;
    bool CutThreeLeptonPtFirst;
    bool CutThreeLeptonPtSecond;
    bool CutThreeLeptonPtThird;
    bool CutThreeLeptonPtFourth;


    /** minimum pt value for lepton 1 */
    double lep1PtMin;  //highest pt

    /** minimum pt value for lepton 2 */
    double lep2PtMin; //medium pt

    /** minimum pt value for lepton 3 */
    double lep3PtMin; //lowest pt

    /** minimum pt value for lepton 3 */
    double lep4PtMin; //lowest pt

    /** Mt cut */
    bool CutThreeLepMtMin;
    double threeLepMtMin;

    bool CutMtMin;
    bool CutMtMinFirst;
    bool CutMtMinSecond;
    bool CutMtMinThird;


    /** minimum mt value for lepton 1 */
    double lep1MtMin;  //highest pt

    /** minimum mt value for lepton 2 */
    double lep2MtMin; //medium pt

    /** minimum mt value for lepton 3 */
    double lep3MtMin; //lowest pt

    /** Pair Type cut */
    bool CutPairType;


    /** require Same Flavor Same Sign pair */
    int reqSFSS;

    /** require Same Flavor Opposite Sign pair */
    int reqSFOS;

    /** require Opposite Flavor Same Sign pair */
    int reqOFSS;

    /** require Opposite Flavor Opposite Sign pair */
    int reqOFOS;

    /** lepton flavor cut */
    bool CutFlavor;

    /** require mu mu mu */
    bool mmmFlavor;

    /** require mu mu e */
    bool mmeFlavor;

    /** require mu e e */
    bool meeFlavor;

    /** require e e e */
    bool eeeFlavor;

    /** N-jet cuts */
    bool CutNJet;

    /** maximum number of allowed jets */
    int nJetMax;

    /** HW Charge Sum Cut */
    bool CutHWChargeSum;

    /** top veto cuts */
    bool CutTopVeto;

    /** HW MET cut */
    bool CutHWMET;

    /** HW MET STVF threshold */
    double hwMETSTVFMin;

    /** HW Z veto */
    bool CutHWZVeto;

    /** minimum hw  Z veto Mass cut value */
    double hwZVetoMassMin;

    /** maximum hw  Z veto Mass cut value */
    double hwZVetoMassMax;

    /** HW Inv Mass  cut */
    bool CutHWInvMass;

    /** minimum hw  Inv Mass cut value */
    double hwInvMassMin;

    /** maximum hw  Inv  Mass cut value */
    double hwInvMassMax;

    /** HW Delta R Cut */
    bool CutHWDeltaR;

    /** maximum Delta R for HW Delta R cut */
    double hwDeltaRMax;

    /** maximum  bTagVetoMV1 cut value */
    double bTagVetoMV1Max;

    /** minimum btagJetPtMin cut value */
    double bTagJetPtMin;

    /** maximum btagJetEtaMax cut value */
    double bTagJetEtaMax;

    /** centralJetVeto  cut */
    bool CutCentralJetVeto;

    /** minimum CJVPtMin cut value */
    double CJVPtMin;

    /** maximum CJVEtaMax cut value */
    double CJVEtaMax;

    /** leptonCentrality  cut */
    bool CutLeptonCentrality;

    /** Z veto */
    bool CutZVeto;

    /** Inverted Z veto */
    bool CutInvZVeto;

    /** Allow z-veto/inverted z-veto to be applied to SF pairs with no requirement on sign*/
    bool allowZVetoInclusiveSign;

    /** Z Tag and Probe  cut */
    bool CutZTagAndProbe;

    /** Fake Tag and Probe  cut */
    bool CutFakeTagAndProbe;
    bool CutFakeTagAndProbeInclusiveSign;

    /** Z+Jets Tag and Probe cut */
    bool CutZPlusJetsTagAndProbe;
    /** Z+Gamma Tag and Probe cut */
    bool CutZPlusGammaTagAndProbe;

    /** bTagVeto cut */
    bool CutbTagVeto;

    /**Inv  bTagVeto cut */
    bool CutInvbTagVeto;

    /** Delta Phi (MET,lll) cut */
    bool CutDeltaPhi;

    /** Delta Phi cut Lower edge */
    double DeltaPhiLowEdge;

    /** Delta Phi cut High edge */
    double DeltaPhiHighEdge;

    /** minimum  Z veto Mass cut value */
    double zVetoMassMin;

    /** maximum  Z veto Mass cut value */
    double zVetoMassMax;


    /** di leptons CR cuts */
    bool CutSameFlavour;
    bool CutOppositeSign;
    //Note: Need to define nMuon simultaneously otherwise doesn't work..
    bool CutDiLepFlavour;
    bool CutDiLepInvMass;
    bool CutSumPtObject;
    bool CutCosDphi;
    bool CutTransversMass;
    bool CutFakeLeptons;

    /** 4 leptons CR cuts */
    bool Cut4LepOppositeSign;
    bool Cut4LepFlavour;
    bool Cut4LepInvMass;

    /**cuts def for 2lep CRs */
    double SumHPTO;
    double SumCosDphi;
    double TransversMass;
    unsigned int nFakeLeptons;

    /**cuts def for 4lep CRs */
    double Mass12Min;
    double Mass12Max;
    double Mass34Min;
    double Mass34Max;

    bool isSameFlavour;
    bool isOppositeSign;


    // Private members
  private:

    /** Position of the truth filter  cut */
    int m_cutPositionTruthFilter;

    /** Position of the stream overlap removal cut */
    int m_cutPositionStreamOverlap;

    /** Position of the trigger cut */
    int m_cutPositionTrigger;

    /** Position of the nPV  cut */
    int m_cutPositionNPV;

    /** Position of the jet cleaning cut */
    int m_cutPositionJetCleaning;

    /** Position of the HotTile  cut */
    int m_cutPositionHotTile;

    /** Position of the FCal  cut */
    int m_cutPositionFCal;

    /** Position of the larError  cut */
    int m_cutPositionLArError;

    /** Position of the HW lepton charge sum cut */
    int m_cutPositionHWChargeSum;

    /** Position of the N Jet cut */
    int m_cutPositionNJet;

    /** Position of the Top Veto cut */
    int m_cutPositionTopVeto;

    /** Position of the HW MET cut */
    int m_cutPositionHWMET;

    /** Position of the HW Z veto cut */
    int m_cutPositionHWZVeto;

    /** Position of the HW Inv mass veto cut */
    int m_cutPositionHWInvMass;

    /** Position of the HW Delta R cut */
    int m_cutPositionHWDeltaR;

    /** Position of the nLepton cut */
    int m_cutPositionDilepton;

    /** Position of the nMuon cut */
    int m_cutPositionNMuon;

    /** Position of the nElectron cut */
    int m_cutPositionNElectron;

    /** Position of the three leptons  cut */
    int m_cutPositionMultiLeptonsInclusive ;

    /** Position of the three leptons  cut */
    int m_cutPositionMultiLeptonsExclusive ;

    /* Position of lepton flavor quality multiplicity cut */
    int m_cutPositionLeptonMultiplicityFlavorQuality ;

    /** Position of the loose dilepton el-mu cut */
    int m_cutPositionLooseDilepton;

    /** Position of the triggermatching cut */
    int m_cutPositionTriggerMatching;

    /** Position of the 3-lepton pt cut */
    int m_cutPositionThreeLeptonPt;

    /** Position of the 3-lepton mt cut */
    int m_cutPositionMtMin;

    /** Position of the pair type cut */
    int m_cutPositionPairType;

    /** Position of the lepton flavor  cut */
    int m_cutPositionFlavor;

    /** Position of the delta phi cut */
    int m_cutPositionDeltaPhi;

    /** Position of the nTau cut */
    int m_cutPositionNTau;

    /** Position of the charge cut */
    int m_cutPositionOppositeCharge;

    /** Position of the Z Veto cut */
    int m_cutPositionZVeto;


    /** Position of the Z Tag And Probe Cut */
    int m_cutPositionZTagAndProbe;

    /** Position of the Z +Jets Tag And Probe Cut */
    int m_cutPositionZPlusJetsTagAndProbe;

    /** Position of the Z +Gamma Tag And Probe Cut */
    int m_cutPositionZPlusGammaTagAndProbe;

    /** Position of the Fake Tag And Probe Cut */
    int m_cutPositionFakeTagAndProbe;

    /** Position of the bTagVeto cut */
    int m_cutPositionbTagVeto;

    /** Position of the Inv bTagVeto cut */
    int m_cutPositionInvbTagVeto;

    /** Position of the llMass cut */
    int m_cutPositionllMass;

    /** Position of the sumPtMin cut */
    int m_cutPositionsumPtMin;

    /** Position of the firstJetPtMin cut */
    int m_cutPositionfirstJetPtMin;

    /** Position of the Three Lepton Mt Cut */
    int m_cutPositionThreeLepMtMin;

    /** Position of the metMin cut */
    int m_cutPositionmetMin;

    /** Position of the hptoMetMin cut */
    int m_cutPositionhptoMetMin;

    /** Position of the x cut */
    int m_cutPositionx;

    /** Position of the llDeltaPhi cut */
    int m_cutPositionllDeltaPhi;

    /** Position of the earlybTagVeto cut */
    int m_cutPositionearlybTagVeto;

    /** Position of the secondJetPtMin cut */
    int m_cutPositionsecondJetPtMin;

    /** Position of failing Boosted cut */
    int m_cutPositionfailedCutBasedBoosted;

    /** Position of failing VBF MVA cut */
    int m_cutPositionfailedMVAVBF;

    /** Position of failing Boosted MVA cut */
    int m_cutPositionfailedMVABoosted;

    /** Position of the jjDeltaEta cut */
    int m_cutPositionjjDeltaEta;

    /** Position of the jjMass cut */
    int m_cutPositionjjMass;

    /** Position of failing VBF cut */
    int m_cutPositionfailedCutBasedVBF;

    /** Position of the higgsPtMin cut */
    int m_cutPositionhiggsPtMin;

    /** Position of failing 2JET cut */
    int m_cutPositionfailedCutBased2JET;

    /** Position of failing VH MVA cut */
    int m_cutPositionfailedMVAVH;

    /** Position of the higgsjetMassMin cut */
    int m_cutPositionhiggsjetMassMin;


    /** Position of the centralJetVeto  cut */
    int m_cutPositionCentralJetVeto;

    /** Position of the leptonCentrality  cut */
    int m_cutPositionLeptonCentrality;



    /** dilepton CRs cuts */
  int m_cutPositionSameFlavour;
  int m_cutPositionOppositeSign;
  int m_cutPositionDiLepFlavour;
  int m_cutPositionDiLepInvMass;
  int m_cutPositionSumPtObject;
  int m_cutPositionCosDphi;
  int m_cutPositionTransversMass;
  int m_cutPositionFakeLeptons;

    /** 4lepton CRs cuts */
  int m_cutPosition4LepOppositeSign;
  int m_cutPosition4LepFlavour;
  int m_cutPosition4LepInvMass;

  }; // End: class definition

} // End: namespace Root

#endif


