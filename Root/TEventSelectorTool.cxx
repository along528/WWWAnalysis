// Dear emacs, this is -*-c++-*- 
/******************************************************************************
Name:        TEventSelectorTool

Author:      Karsten Koeneke (CERN)
Created:     April 2011

Description: Example tool to select PhysicsObjects in pure ROOT
******************************************************************************/

// Preprocessor magic for debugging
#define XXX std::cout << "I am here: " << __FILE__ << ":" << __LINE__ << std::endl;

// This class header
#include "wwwAnalysis/TEventSelectorTool.h"

// STL includes
#include <iostream>
#include <cfloat>
#include <math.h>
#include <utility>

// ROOT includes
#include <TString.h>






//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::TEventSelectorTool::TEventSelectorTool(const char* name) :
  Root::TSelectorToolBase(name),
  CutTruthFilter(0),
  CutStreamOverlap(0),
  CutTrigger(0),
  includeEETrigger(0),
  includeEMuTrigger(0),
  includeMuMuTrigger(0),
  CutNPV(0),
  nPVMin(-1),
  CutJetCleaning(0),
  CutHotTile(0),
  CutFCal(0),
  CutLArError(0),
  CutDilepton(0),
  nMuon(-1),
  nSFOS(-1),
  nSFOSAll(-1),
  CutTriggerMatching(0),
  CutMultiLeptonsInclusive(0),
  CutMultiLeptonsExclusive(0),
  CutLeptonMultiplictyFlavorQuality(0),
  nLooseNotTightMuonsCut(-1),
  nLooseNotTightElectronsCut(-1),
  nLooseMuonsCut(-1),
  nLooseElectronsCut(-1),
  nTightMuonsCut(-1),
  nTightElectronsCut(-1),
  CutLooseDilepton(0),
  looseDileptonSameFlavor(0),
  nLeptonsCut(3),
  CutNTau(0),
  nTau(0),
  CutOppositeCharge(0),
  CutFakeCharge(-1),
  CutllMass(0),
  llMassSFMin(-DBL_MAX),
  llMassSFMax(DBL_MAX),
  llMassDFMin(-DBL_MAX),
  llMassDFMax(DBL_MAX),
  CutsumPtMin(0),
  sumPtMin(-DBL_MAX),
  CutfirstJetPtMin(0),
  firstJetPtMin(-DBL_MAX),
  jetJVFMin(-DBL_MAX),
  CutmetMin(0),
  CutmetMinFirst(0),
  CutmetMinSecond(0),
  CutmetMinThird(0),
  useSTVFMetMin(0),
  metMin(-DBL_MAX),
  metSFMin(-DBL_MAX),
  metDFMin(-DBL_MAX),
  CuthptoMetMin(0),
  hptoMetSFMin(-DBL_MAX),
  hptoMetDFMin(-DBL_MAX),
  Cutx(0),
  xMin(-DBL_MAX),
  xMax(DBL_MAX),
  CutllDeltaPhi(0),
  llDeltaPhiMin(-DBL_MAX),
  llDeltaPhiMax(DBL_MAX),
  CutearlybTagVeto(0),
  CutsecondJetPtMin(0),
  secondJetPtMin(-DBL_MAX),
  CutfailedCutBasedBoosted(0),
  CutfailedMVAVBF(0),
  CutfailedMVABoosted(0),
  CutjjDeltaEta(0),
  jjDeltaEtaMin(-DBL_MAX),
  jjDeltaEtaMax(DBL_MAX),
  CutjjMass(0),
  jjMassMin(-DBL_MAX),
  jjMassMax(DBL_MAX),
  CutfailedCutBasedVBF(0),
  CuthiggsPtMin(0),
  higgsPtMin(-DBL_MAX),
  CutfailedCutBased2JET(0),
  CutfailedMVAVH(0),
  CuthiggsjetMassMin(0),
  higgsjetMassMin(-DBL_MAX),
  CutThreeLeptonPt(0),
  CutThreeLeptonPtFirst(0),
  CutThreeLeptonPtSecond(0),
  CutThreeLeptonPtThird(0),
  CutThreeLeptonPtFourth(0),
  lep1PtMin(-DBL_MAX),
  lep2PtMin(-DBL_MAX),
  lep3PtMin(-DBL_MAX),
  lep4PtMin(-DBL_MAX),
  CutThreeLepMtMin(0),
  threeLepMtMin(-DBL_MAX),
  CutMtMin(0),
  CutMtMinFirst(0),
  CutMtMinSecond(0),
  CutMtMinThird(0),
  lep1MtMin(-DBL_MAX),
  lep2MtMin(-DBL_MAX),
  lep3MtMin(-DBL_MAX),
  CutPairType(0),
  reqSFSS(0),
  reqSFOS(0),
  reqOFSS(0),
  reqOFOS(0),
  CutFlavor(0),
  mmmFlavor(0),
  mmeFlavor(0),
  meeFlavor(0),
  eeeFlavor(0),
  CutNJet(0),
  nJetMax(0),
  CutHWChargeSum(0),
  CutTopVeto(0),
  CutHWMET(-DBL_MAX),
  hwMETSTVFMin(0),
  CutHWZVeto(0),
  hwZVetoMassMin(-DBL_MAX),
  hwZVetoMassMax(-DBL_MAX),
  CutHWInvMass(0),
  hwInvMassMin(-DBL_MAX),
  hwInvMassMax(-DBL_MAX),
  CutHWDeltaR(0),
  hwDeltaRMax(0),
  bTagVetoMV1Max(DBL_MAX),
  bTagJetPtMin(-DBL_MAX),
  bTagJetEtaMax(DBL_MAX),
  CutCentralJetVeto(0),
  CJVPtMin(-DBL_MAX),
  CJVEtaMax(-DBL_MAX),
  CutLeptonCentrality(0),
  CutZVeto(0),
  CutInvZVeto(0),
  allowZVetoInclusiveSign(0),
  CutZTagAndProbe(0),
  CutZPlusJetsTagAndProbe(0),
  CutZPlusGammaTagAndProbe(0),
  CutFakeTagAndProbe(0),
  CutFakeTagAndProbeInclusiveSign(0),
  CutbTagVeto(0),
  CutInvbTagVeto(0),
  CutDeltaPhi(0),
  DeltaPhiLowEdge(-DBL_MAX),
  DeltaPhiHighEdge(-DBL_MAX),
  zVetoMassMin(-DBL_MAX),
  zVetoMassMax(-DBL_MAX),
  CutSameFlavour(0),
  CutOppositeSign(0),
  CutDiLepFlavour(0),
  CutDiLepInvMass(0),
  CutSumPtObject(0),
  CutCosDphi(0),
  CutTransversMass(0),
  CutFakeLeptons(0),
  Cut4LepOppositeSign(0),
  Cut4LepFlavour(0),
  Cut4LepInvMass(0),
  SumHPTO(0),
  SumCosDphi(0),
  TransversMass(0),
  nFakeLeptons(0),
  Mass12Min(0),
  Mass12Max(0),
  Mass34Min(0),
  Mass34Max(0),
  isSameFlavour(0),
  isOppositeSign(0),
  m_cutPositionTruthFilter(-9),
  m_cutPositionStreamOverlap(-9),
  m_cutPositionTrigger(-9),
  m_cutPositionNPV(-9),
  m_cutPositionJetCleaning(-9),
  m_cutPositionHotTile(-9),
  m_cutPositionFCal(-9),
  m_cutPositionLArError(-9),
  m_cutPositionHWChargeSum(-9),
  m_cutPositionNJet(-9),
  m_cutPositionHWZVeto(-9),
  m_cutPositionHWInvMass(-9),
  m_cutPositionHWDeltaR(-9),
  m_cutPositionDilepton(-9),
  m_cutPositionNMuon(-9),
  m_cutPositionNElectron(-9),
  m_cutPositionMultiLeptonsInclusive(-9),
  m_cutPositionMultiLeptonsExclusive(-9),
  m_cutPositionLeptonMultiplicityFlavorQuality(-9),
  m_cutPositionLooseDilepton(-9),
  m_cutPositionTriggerMatching(-9),
  m_cutPositionThreeLeptonPt(-9),
  m_cutPositionMtMin(-9),
  m_cutPositionPairType(-9),
  m_cutPositionFlavor(-9),
  m_cutPositionDeltaPhi(-9),
  m_cutPositionNTau(-9),
  m_cutPositionOppositeCharge(-9),
  m_cutPositionZVeto(-9),
  m_cutPositionZTagAndProbe(-9),
  m_cutPositionZPlusJetsTagAndProbe(-9),
  m_cutPositionZPlusGammaTagAndProbe(-9),
  m_cutPositionFakeTagAndProbe(-9),
  m_cutPositionbTagVeto(-9),
  m_cutPositionInvbTagVeto(-9),
  m_cutPositionllMass(-9),
  m_cutPositionsumPtMin(-9),
  m_cutPositionfirstJetPtMin(-9),
  m_cutPositionThreeLepMtMin(-9),
  m_cutPositionmetMin(-9),
  m_cutPositionhptoMetMin(-9),
  m_cutPositionx(-9),
  m_cutPositionllDeltaPhi(-9),
  m_cutPositionearlybTagVeto(-9),
  m_cutPositionsecondJetPtMin(-9),
  m_cutPositionfailedCutBasedBoosted(-9),
  m_cutPositionfailedMVAVBF(-9),
  m_cutPositionfailedMVABoosted(-9),
  m_cutPositionjjDeltaEta(-9),
  m_cutPositionjjMass(-9),
  m_cutPositionfailedCutBasedVBF(-9),
  m_cutPositionhiggsPtMin(-9),
  m_cutPositionfailedCutBased2JET(-9),
  m_cutPositionfailedMVAVH(-9),
  m_cutPositionhiggsjetMassMin(-9),
  m_cutPositionCentralJetVeto(-9),
  m_cutPositionLeptonCentrality(-9),
  m_cutPositionSameFlavour(-9),
  m_cutPositionOppositeSign(-9),
  m_cutPositionDiLepFlavour(-9),
  m_cutPositionDiLepInvMass(-9),
  m_cutPositionSumPtObject(-9),
  m_cutPositionCosDphi(-9),
  m_cutPositionTransversMass(-9),
  m_cutPositionFakeLeptons(-9),
  m_cutPosition4LepOppositeSign(-9),
  m_cutPosition4LepFlavour(-9),
  m_cutPosition4LepInvMass(-9)
{
  //massesSFOS = NULL;
  //massesSFOSAll = NULL;
}



//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::TEventSelectorTool::~TEventSelectorTool()
{
}


void wwwAnalysis::TEventSelectorTool::clear()
{
	m_accept.clear();
}

//=============================================================================
// Initialize this selector tool
//=============================================================================
int wwwAnalysis::TEventSelectorTool::initialize()
{
	// use an int as a StatusCode
  int sc(1);


  // --------------------------------------------------------------------------
  // Register the cuts and check that the registration worked:
  // NOTE: THE ORDER IS IMPORTANT!!! Cut0 corresponds to bit 0, Cut1 to bit 1,...
  //
  // Cut Truth Filter (remove Z+Jets FSR)
  if(CutTruthFilter){
    m_cutPositionTruthFilter = m_accept.addCut("truth_filter", Form("var = pass"));
    if( m_cutPositionTruthFilter < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut stream overlap
  if(CutStreamOverlap ){
    m_cutPositionStreamOverlap = m_accept.addCut("stream_overlap", Form("var = pass"));
    if( m_cutPositionStreamOverlap < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut trigger
  if(CutTrigger && (includeEETrigger || includeEMuTrigger || includeMuMuTrigger)) {
    m_cutPositionTrigger = m_accept.addCut("trigger", Form("var = pass"));
    if( m_cutPositionTrigger < 0) sc = 0; //Exceeded the number of allowed cuts
  }


  // Cut  three leptons inclusive
  if(CutMultiLeptonsInclusive){
    m_cutPositionMultiLeptonsInclusive = m_accept.addCut("multi_leptons_inclusive", Form("var = pass"));
    if( m_cutPositionMultiLeptonsInclusive  < 0) sc = 0; //Exceeded the number of allowed cuts
  }
  if(CutMultiLeptonsExclusive){
    m_cutPositionMultiLeptonsExclusive = m_accept.addCut("multi_leptons_exclusive", Form("var = pass"));
    if( m_cutPositionMultiLeptonsExclusive  < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  if(CutLooseDilepton){
    m_cutPositionLooseDilepton= m_accept.addCut("loose_dilepton_cut", Form("var = pass"));
    if( m_cutPositionLooseDilepton< 0) sc = 0; //Exceeded the number of allowed cuts
  }

  if(CutLeptonMultiplictyFlavorQuality){
    m_cutPositionLeptonMultiplicityFlavorQuality = m_accept.addCut("multi_leptons_flavor_quality", Form("var = pass"));
    if( m_cutPositionLeptonMultiplicityFlavorQuality  < 0) sc = 0; //Exceeded the number of allowed cuts
  }


  // Cut trigger matching
  if(CutTriggerMatching){
    m_cutPositionTriggerMatching = m_accept.addCut("trigger_matching", Form("var = pass"));
    if( m_cutPositionTriggerMatching < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut jet cleaning
  if(CutJetCleaning) {
    m_cutPositionJetCleaning = m_accept.addCut("jet_cleaning", Form("var = pass"));
    if( m_cutPositionJetCleaning < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut HotTile
  if(CutHotTile) {
    m_cutPositionHotTile = m_accept.addCut("HotTile", Form("var = pass"));
    if( m_cutPositionHotTile < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut FCal
  if(CutFCal) {
    m_cutPositionFCal = m_accept.addCut("FCal", Form("var = pass"));
    if( m_cutPositionFCal < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut LArError
  if(CutLArError) {
    m_cutPositionLArError = m_accept.addCut("LArError", Form("var = pass"));
    if( m_cutPositionLArError < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut 3-lepton Pt 1st
  if(CutThreeLeptonPtFirst){
    m_cutPositionThreeLeptonPt = m_accept.addCut("Three_Lepton_Pt", Form("var = pass"));
    if( m_cutPositionThreeLeptonPt < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  if(CutThreeLepMtMin){
    m_cutPositionThreeLepMtMin = m_accept.addCut("Three_Lepton_Mt_Min",Form("var < %g",threeLepMtMin));
    if( m_cutPositionThreeLepMtMin  < 0) sc = 0;
  }

  // Cut metMin 1st
  if(CutmetMinFirst) {
    m_cutPositionmetMin = m_accept.addCut( "MET_Min", Form("var < %g", metMin) );
    if ( m_cutPositionmetMin < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut Mt Min 1st
  if(CutMtMinFirst) {
    m_cutPositionMtMin = m_accept.addCut( "Mt_Min", Form("var < %g", metMin) );
    if ( m_cutPositionMtMin < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut 3-lepton Pt 2nd
  if(CutThreeLeptonPtSecond){
    m_cutPositionThreeLeptonPt = m_accept.addCut("Three_Lepton_Pt", Form("var = pass"));
    if( m_cutPositionThreeLeptonPt < 0) sc = 0; //Exceeded the number of allowed cuts
  }
  // Cut metMin 2nd
  if(CutmetMinSecond) {
    m_cutPositionmetMin = m_accept.addCut( "MET_Min", Form("var < %g", metMin) );
    if ( m_cutPositionmetMin < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut Mt Min 2nd
  if(CutMtMinSecond) {
    m_cutPositionMtMin = m_accept.addCut( "Mt_Min", Form("var < %g", metMin) );
    if ( m_cutPositionMtMin < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut 3-lepton Pt 3rd
  if(CutThreeLeptonPtThird){
    m_cutPositionThreeLeptonPt = m_accept.addCut("Three_Lepton_Pt", Form("var = pass"));
    if( m_cutPositionThreeLeptonPt < 0) sc = 0; //Exceeded the number of allowed cuts
  }
  // Cut metMin 3rd
  if(CutmetMinThird) {
    m_cutPositionmetMin = m_accept.addCut( "MET_Min", Form("var < %g", metMin) );
    if ( m_cutPositionmetMin < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut Mt Min 3rd
  if(CutMtMinThird) {
    m_cutPositionMtMin = m_accept.addCut( "Mt_Min", Form("var < %g", metMin) );
    if ( m_cutPositionMtMin < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut 3-lepton Pt
  if(CutThreeLeptonPt){
    m_cutPositionThreeLeptonPt = m_accept.addCut("Three_Lepton_Pt", Form("var = pass"));
    if( m_cutPositionThreeLeptonPt < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut metMin
  if(CutmetMin) {
    m_cutPositionmetMin = m_accept.addCut( "MET_Min", Form("var < %g", metMin) );
    if ( m_cutPositionmetMin < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut Mt Min
  if(CutMtMin) {
    m_cutPositionMtMin = m_accept.addCut( "Mt_Min", Form("var < %g", metMin) );
    if ( m_cutPositionMtMin < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut Z Veto
  if(CutZVeto || CutInvZVeto){
    if(CutZVeto) m_cutPositionZVeto = m_accept.addCut( "ZVeto", Form("!(%g < var < %g)", zVetoMassMin, zVetoMassMax)) ;
    else if(CutInvZVeto) m_cutPositionZVeto = m_accept.addCut( "InvZVeto", Form("(%g < var < %g)", zVetoMassMin, zVetoMassMax)) ;

    if ( m_cutPositionZVeto < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut bTagVeto
  if(CutbTagVeto) {
    m_cutPositionbTagVeto = m_accept.addCut( "bTagVeto", Form("var = pass") );
    if ( m_cutPositionbTagVeto < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  //Cut Tag and Probe
  if(CutZTagAndProbe){
    m_cutPositionZTagAndProbe = m_accept.addCut( "ZTagAndProbe", Form("var = pass") );
    if ( m_cutPositionZTagAndProbe < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  //Cut Fake Tag and Probe
  if(CutFakeTagAndProbe || CutFakeTagAndProbeInclusiveSign){
    m_cutPositionFakeTagAndProbe = m_accept.addCut( "FakeTagAndProbe", Form("var = pass") );
    if ( m_cutPositionFakeTagAndProbe < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  //Cut Z +jets  Tag and Probe
  if(CutZPlusJetsTagAndProbe){
    m_cutPositionZPlusJetsTagAndProbe = m_accept.addCut( "ZPlusJetsTagAndProbe", Form("var = pass") );
    if ( m_cutPositionZPlusJetsTagAndProbe < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  //Cut Z +gamma  Tag and Probe
  if(CutZPlusGammaTagAndProbe){
    m_cutPositionZPlusGammaTagAndProbe = m_accept.addCut( "ZPlusGammaTagAndProbe", Form("var = pass") );
    if ( m_cutPositionZPlusGammaTagAndProbe < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut inverse bTagVeto
  if(CutInvbTagVeto) {
    m_cutPositionInvbTagVeto = m_accept.addCut( "InvbTagVeto", Form("var = pass") );
    if ( m_cutPositionInvbTagVeto < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }


  //Cut Delta Phi
  if(CutDeltaPhi) {
    m_cutPositionDeltaPhi = m_accept.addCut( "DeltaPhi", Form("var = pass") );
    if ( m_cutPositionDeltaPhi < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }


  // Cut require a certain pair type in the event
  if(CutPairType) {
    m_cutPositionPairType = m_accept.addCut("PairType", Form("var = pass"));
    if( m_cutPositionPairType < 0) sc = 0; //Exceeded the number of allowed cuts
  }
  // Cut require a certain flavor compositition
  if(CutFlavor) {
    m_cutPositionFlavor = m_accept.addCut("Lepton Flavor", Form("var = pass"));
    if( m_cutPositionFlavor< 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut HW Charge sum
  if(CutHWChargeSum) {
    m_cutPositionHWChargeSum = m_accept.addCut("HW Charge Sum", Form("lepton charge sum  == +/- 1"));
    if( m_cutPositionHWChargeSum < 0) sc = 0; //Exceeded the number of allowed cuts
  }
  // Cut N Jets
  if(CutNJet) {
    m_cutPositionNJet = m_accept.addCut("NJets", Form("njet <= %d",nJetMax));
    if( m_cutPositionNJet < 0) sc = 0; //Exceeded the number of allowed cuts
  }
  // Cut Top Veto
  if(CutTopVeto) {
    m_cutPositionTopVeto = m_accept.addCut("TopVeto", Form(" var = pass")); 
    if( m_cutPositionTopVeto < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut HW MET
  if(CutHWMET) {
    m_cutPositionHWMET = m_accept.addCut("HWMET", Form(" var = pass")); 
    if( m_cutPositionHWMET < 0) sc = 0; //Exceeded the number of allowed cuts
  }
  // Cut  HW Z Veto
  if(CutHWZVeto){
    m_cutPositionHWZVeto = m_accept.addCut( "HW ZVeto", Form("!(%g < var < %g)", hwZVetoMassMin, hwZVetoMassMax)) ;
    if ( m_cutPositionHWZVeto < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut  HW Inv Mass
  if(CutHWInvMass){
    m_cutPositionHWInvMass = m_accept.addCut( "HW Inv Mass", Form("var > %g AND var < %g", hwInvMassMin, hwInvMassMax)) ;
    if ( m_cutPositionHWInvMass < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut  HW Delta R
  if(CutHWDeltaR){
    m_cutPositionHWDeltaR = m_accept.addCut( "HW Delta R", Form("var < %g ", hwDeltaRMax)) ;
    if ( m_cutPositionHWDeltaR < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }


  //Dileptons CR cuts:
  //Cut Same Flavour
  if(CutSameFlavour){
    m_cutPositionSameFlavour = m_accept.addCut( "Same Flavour dilepton",  Form(" var = pass")) ;
    if ( m_cutPositionSameFlavour < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  //Cut Opposite Sign
  if(CutOppositeSign){
    m_cutPositionOppositeSign = m_accept.addCut( "Opposite Sign dilepton",  Form(" var = pass")) ;
    if ( m_cutPositionOppositeSign < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  //Select only certain flavour combinations
  if(CutDiLepFlavour){
    m_cutPositionDiLepFlavour = m_accept.addCut( "Di-Lep Flavour dilepton",  Form("nEl == %d AND nMuons == %d", nMuon-2, nMuon)) ;
    if ( m_cutPositionDiLepFlavour < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut  Di-Lep Inv Mass
  if(CutDiLepInvMass){
    m_cutPositionDiLepInvMass = m_accept.addCut( "Di-Lep Inv Mass", Form("var > %g AND var < %g", hwInvMassMin, hwInvMassMax)) ;
    if ( m_cutPositionDiLepInvMass < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut  SumPtObject
  if(CutSumPtObject){
    m_cutPositionSumPtObject = m_accept.addCut( "Sum High pT object", Form("var < %g ", SumHPTO)) ;
    if ( m_cutPositionSumPtObject < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut  CosDphi
  if(CutCosDphi){
    m_cutPositionCosDphi = m_accept.addCut( "Cos dphi", Form("var > %g ", SumCosDphi)) ;
    if ( m_cutPositionCosDphi < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut TransversMass
  if(CutTransversMass){
    m_cutPositionTransversMass = m_accept.addCut( "Transvers Mass", Form("var > %g ", TransversMass)) ;
    if ( m_cutPositionTransversMass < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut FakeLeptons
  if(CutFakeLeptons){
    m_cutPositionFakeLeptons = m_accept.addCut( "Fake Leptons", Form("var ==  %d", nFakeLeptons)) ;
    if ( m_cutPositionFakeLeptons < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  //4 leptons CR cuts:

  //Cut Opposite Sign
  if(Cut4LepOppositeSign){
    m_cutPosition4LepOppositeSign = m_accept.addCut( "Opposite Sign 4lepton",  Form(" var = pass")) ;
    if ( m_cutPosition4LepOppositeSign < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  //Select only certain flavour combinations
  if(Cut4LepFlavour){
    m_cutPosition4LepFlavour = m_accept.addCut( "Di-Lep Flavour 4leptons",   Form(" var = pass")) ;
    if ( m_cutPosition4LepFlavour < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut  Di-Lep Inv Mass
  if(Cut4LepInvMass){
    m_cutPosition4LepInvMass = m_accept.addCut( "4-Lep Inv Mass", Form("m12 > %g AND m12 < %g AND m34 >%g AND m34 <%g", Mass12Min, Mass12Max, Mass34Min, Mass34Max)) ;
    if ( m_cutPosition4LepInvMass < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut nPV
  if(CutNPV) {
    m_cutPositionNPV = m_accept.addCut("nPV_3trks", Form("var >= %g",nPVMin));
    if( m_cutPositionNPV < 0) sc = 0; //Exceeded the number of allowed cuts
  }
/*
  // Cut dilepton
  if(CutDilepton && nMuon < 0) {
    m_cutPositionDilepton = m_accept.addCut("dilepton", Form("var = pass"));
    if( m_cutPositionDilepton < 0) sc = 0; //Exceeded the number of allowed cuts
  } else {
  // Cut nMuon
    m_cutPositionNMuon = m_accept.addCut("nMuon", Form("var = %g",nMuon));
    if( m_cutPositionNMuon < 0) sc = 0; //Exceeded the number of allowed cuts

  // Cut nElectron
    m_cutPositionNElectron = m_accept.addCut("nElectron", Form("var = %g",2 - nMuon));
    if( m_cutPositionNElectron < 0) sc = 0; //Exceeded the number of allowed cuts
  }

  // Cut earlybTagVeto
  if(CutearlybTagVeto) {
    m_cutPositionearlybTagVeto = m_accept.addCut( "earlybTagVeto", Form("var = pass") );
    if ( m_cutPositionearlybTagVeto < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }


  */

  return sc;
}



//=============================================================================
// Calculate the actual accept of each cut individually.
//=============================================================================
const Root::TAccept& wwwAnalysis::TEventSelectorTool::accept(const D3PDReader::Event &event,
							 const vector<wwwAnalysis::PhysicsObject *> &leps,
							 const vector<wwwAnalysis::PhysicsObject *> &fakes,
							 const vector<wwwAnalysis::PhysicsObject *> &leps_LooseNotTight,
							 const vector<wwwAnalysis::PhysicsObject *> &leps_Loose,
							 const vector<wwwAnalysis::PhysicsObject *> &tags,
							 const vector<wwwAnalysis::PhysicsObject *> &tags2,
							 const vector<wwwAnalysis::PhysicsObject *> &probes,
							 const std::vector<Tau> &tau,
							 const std::vector<Jet> &jet, const std::vector<Jet> &jet_loose, const std::vector<Jet> &jet_all,
							 const TVector2 &met, 
							 const MissingEt *oMET,
							 unsigned int runNumber, bool isMC, bool isEGammaStream, bool is_fake, int nPV_3trks, bool triggerMatch, 
							 bool btagveto,
							 OutputInformations &AdditionnalInfo)
{
  // Reset the cut result bits to zero (= fail cut)
  m_accept.clear();
  bool pass = true;

  
  
  //count number of SFOS pairs from all leptons
  vector < PhysicsObjectPair > pairsAll = getSFOSPairs(leps);
  nSFOSAll= pairsAll.size(); 
  massesSFOSAll.clear();
  massesSFOS.clear();
  for (unsigned int i = 0; i < pairsAll.size() ; i++)
  	massesSFOSAll.push_back( (pairsAll[i].first->momentum() + pairsAll[i].second->momentum()).M() );


  //count number of SFOS pairs for 
  //leptons which pass mutli-lepton requirement
  //evaluate later when the multi lepton cut is applied
  //if multi-lepton cut fails then this is left as -1.
  nSFOS = -1;

  // -----------------------------------------------------------
  // Do the actual selection
  //
  //Cut Truth Filter (Z+Jets FSR veto)
  bool passTruthFilter = true;
  if(CutTruthFilter){
     if(isMC){
  	UInt_t chan =  event.eventinfo.mc_channel_number();
     	//Alpgen W+Jets overlap removal with Wgamma
	const int nAlpgenWplusJetChannels  = 18;
	UInt_t AlpgenWplusJetChannels []= { 107680, 107681, 107682, 107683, 107684, 107685,
					    107690, 107691, 107692, 107693, 107694, 107695,
					    107700, 107701, 107702, 107703, 107704, 107705};
	
	for (int iChan=0;iChan<nAlpgenWplusJetChannels;iChan++){
		if(chan!=AlpgenWplusJetChannels[iChan]) continue;
		//std::cout << "********" << std::endl;
		for (int iParticle = 0; iParticle< event.mc.n();iParticle++){
			int pdgid = TMath::Abs(event.mc[iParticle].pdgId());
			if(pdgid!=22) continue; //select photon
			//std::cout << event.mc[iParticle].status() << "\t"<<event.mc[iParticle].pt()/1000. << std::endl;
			if (event.mc[iParticle].pt() > 8000.) {
				//std::cout << "fail" << std::endl;
				passTruthFilter = false;
				break;
			}
		}
	}

        //Sherpa Z+Jets overlap removal with Zgamma
	const int nSherpaZplusJetChannels = 3; //42;
	UInt_t SherpaZplusJetChannels []= { 147770, 147771, 147772};

	//const int nSherpaZplusJetChannels = 0; //42;
	//UInt_t SherpaZplusJetChannels []= { };//147770, 147771, 147772};
	/*
	{107650, 107651, 107652, 107653, 107654, 107655, 107660, 107661,
	 107662, 107663, 107664, 107665, 107670, 107671, 107672, 107673,
	 107674, 107675, 117650, 117651, 117652, 117653, 117654, 117655,
	 117660, 117661, 117662, 117663, 117664, 117665, 146835, 146845,
	 146860, 146861, 146862, 146863, 146864, 146870, 146871, 146872, 
	 146873, 146874};
	 */
	for (int iChan=0;iChan<nSherpaZplusJetChannels;iChan++){
		if(chan==SherpaZplusJetChannels[iChan]){
		        vector<int> vBeforeFSRLeptons;
		        vector<int> vFSRPhotons;
			for (int iParticle = 0; iParticle< event.mc.n();iParticle++){
				int pdgid = TMath::Abs(event.mc[iParticle].pdgId());
				if ( (pdgid==11 || pdgid ==13) && event.mc[iParticle].status()==1){
					if ( event.mc[iParticle].parent_index().size() > 0 ){
					 	if( (TMath::Abs(event.mc[event.mc[iParticle].parent_index()[0]].pdgId()) == 11 ||
					 	    TMath::Abs(event.mc[event.mc[iParticle].parent_index()[0]].pdgId()) == 13 ) &&
						    event.mc[event.mc[iParticle].parent_index()[0]].status()==11){
						    	vBeforeFSRLeptons.push_back(iParticle);
						    }

					}

				}
				if(pdgid==22){  //find photon
					if ( event.mc[iParticle].parent_index().size() > 0 ){
					 	if( (TMath::Abs(event.mc[event.mc[iParticle].parent_index()[0]].pdgId()) == 11 ||
					 	    TMath::Abs(event.mc[event.mc[iParticle].parent_index()[0]].pdgId()) == 13 ) &&
						    event.mc[event.mc[iParticle].parent_index()[0]].status()==11){
						        vFSRPhotons.push_back(iParticle);
						 }
					 }
				}//end if photon
			}//end loop over particles

			for(unsigned int pho =0; pho<vFSRPhotons.size();pho++){
				int photonIndex = vFSRPhotons.at(pho);
				for(unsigned int lep =0; lep<vBeforeFSRLeptons.size();lep++){
					int leptonIndex = vBeforeFSRLeptons.at(lep);
					if(event.mc[photonIndex].parent_index()[0] == event.mc[leptonIndex].parent_index()[0] && event.mc[photonIndex].pt()/1000. > 10){
						passTruthFilter = false;
						break;
					}
						
				}
				if(!passTruthFilter) break;
			}

			break;
		}// end if found channel
	}// end loop over channels

        //Low-mass Alpgen Z+Jets removal of overlap with Sherpa
	const int nAlpgenLowMassZplusJetChannels = 12; 
	UInt_t AlpgenLowMassZplusJetChannels [] = { 146830, 146831, 146832, 146833, 
						    146834, 146835, 146840, 146841, 
						    146842, 146843, 146844, 146845};
	for (int iChan=0;iChan<nAlpgenLowMassZplusJetChannels ;iChan++){
		if(chan==AlpgenLowMassZplusJetChannels[iChan]){
			int lepPlusIndex  = -1;
			int lepMinusIndex = -1;
			for (int iParticle = 0; iParticle< event.mc.n();iParticle++){
				int pdgid = TMath::Abs(event.mc[iParticle].pdgId());
				if( (pdgid==11 && (chan == 146830 || chan == 146831 || 
				                   chan == 146832 || chan == 146833 || 
				                   chan == 146834 || chan == 146835 ) ) ||
				    (pdgid==13 && (chan == 146840 || chan == 146841 || 
				                   chan == 146842 || chan == 146843 || 
				                   chan == 146844 || chan == 146845 ) ) ) {
					if ( event.mc[iParticle].parent_index().size() > 0 ){
					 	if( TMath::Abs(event.mc[event.mc[iParticle].parent_index()[0]].pdgId()) == 23){
							if(lepPlusIndex < 0 && event.mc[iParticle].pdgId() < 0) lepPlusIndex = iParticle;
							if(lepMinusIndex < 0 && event.mc[iParticle].pdgId() > 0) lepMinusIndex = iParticle;
						}
					}
				}

				if(lepPlusIndex>=0 && lepMinusIndex>=0) break;

			}//end loop over particles

			if(lepPlusIndex>=0 && lepMinusIndex>=0){
				TLorentzVector tlvLepPlus;
				tlvLepPlus.SetPtEtaPhiM( event.mc[lepPlusIndex].pt(), event.mc[lepPlusIndex].eta(), event.mc[lepPlusIndex].phi(),event.mc[lepPlusIndex].m()  );
				TLorentzVector tlvLepMinus;
				tlvLepMinus.SetPtEtaPhiM( event.mc[lepMinusIndex].pt(), event.mc[lepMinusIndex].eta(), event.mc[lepMinusIndex].phi(),event.mc[lepMinusIndex].m()  );
				TLorentzVector tlvZ = tlvLepPlus+tlvLepMinus;
				if(tlvZ.M()/1000. > 40 ) passTruthFilter = false;
			}
			else passTruthFilter = false;

			break;
		}// end if found channel
	}// end loop over channels

	//bulk z heavy flavor overlap removal
	/*
	const int nSherpaZChannels = 5; //42;
	UInt_t SherpaZChannels []= { 147770, 147771, 147772,145161,145162};
	for (unsigned int iChan=0;iChan<nSherpaZChannels;iChan++){
		if(chan==SherpaZChannels[iChan]){
			std::cout << event.top.hfor_type()<<std::endl;
			if (event.top.hfor_type()==4  || //kill
			    !event.top.hfor_type()==3 ){//light flavor
			      passTruthFilter = false;
			 }
		}//end if found channel
	}//end loop over channels

	*/

	//Z+bb+Jets and Z+cc+Jets overlap removal with Z+Jets
	//prescription listed on
	//https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/HforTool
	const int nZPlusBBPlusJetChannels = 12;
	UInt_t ZPlusBBPlusJetChannels [] = 
	{ 109300, 109301, 109302, 109303, 
	  109305, 109306, 109307, 109308,
	  109310, 109311, 109312, 109313};
	for (int iChan=0;iChan<nZPlusBBPlusJetChannels;iChan++){
		if(chan==ZPlusBBPlusJetChannels[iChan]){
			if (event.top.hfor_type()==4  || //kill
			    event.top.hfor_type()==3 ){//light flavor
			      passTruthFilter = false;
			 }
			
		}// end if found channel
	}// end loop over channels
	const int nZPlusCCPlusJetChannels = 12;
	UInt_t ZPlusCCPlusJetChannels [] = 
	{ 126414, 126415, 126416, 126417, 
	  126418, 126419, 126420, 126421, 
	  117706, 117707, 117708, 117709 };
	for (int iChan=0;iChan<nZPlusCCPlusJetChannels;iChan++){
		if(chan==ZPlusCCPlusJetChannels[iChan]){
			if (event.top.hfor_type()==4  || //kill
			    event.top.hfor_type()==3 ){//light flavor
			      passTruthFilter = false;
			 }
			
		}// end if found channel
	}// end loop over channels
      }//end if mc

      m_accept.setCutResult(m_cutPositionTruthFilter, pass = passTruthFilter);
  }//end truth filter


  //cut egamma/muon stream overlap in data
  if(CutStreamOverlap){
  	bool passStreamOverlap = true;
  	if(isEGammaStream) passStreamOverlap = !event.eventinfo.streamDecision_Muons();

	m_accept.setCutResult(m_cutPositionStreamOverlap,pass = passStreamOverlap);
  }

  // Cut trigger
  bool trig = false;
  if(CutTrigger && (includeEETrigger || includeEMuTrigger || includeMuMuTrigger)) {
    //to remove overlaps between muon and egamma streams in data, require that egamma stream doesn't pass muon stream

    //if (isEGammaStream) trig= (event.triggerbits.EF_e24vhi_medium1() || event.triggerbits.EF_e60_medium1()) && 
    //	       		     !(event.triggerbits.EF_mu24i_tight()    || event.triggerbits.EF_mu36_tight());
    //
    trig= event.triggerbits.EF_e24vhi_medium1() || event.triggerbits.EF_e60_medium1() ||
    	       event.triggerbits.EF_mu24i_tight()    || event.triggerbits.EF_mu36_tight() ;//|| 
//    event.triggerbits.EF_mu18_tight_mu8_EFFS() || event.triggerbits.EF_2e12Tvh_loose1() || event.triggerbits.EF_e12Tvh_medium1_mu8() ;
    //	       event.triggerbits.EF_mu24i_tight()    || event.triggerbits.EF_mu36_tight() ;
    	//event.triggerbits.EF_e12Tvh_medium1_mu8() || event.triggerbits.EF_e24vhi_medium1()||event.triggerbits.EF_2e12Tvh_loose1() || event.triggerbits.EF_e24vhi_medium1()||event.triggerbits.EF_mu18_tight_mu8_EFFS()||event.triggerbits.EF_mu24i_tight()||event.triggerbits.EF_mu36_tight()||event.triggerbits.EF_e60_medium1();
    m_accept.setCutResult(m_cutPositionTrigger, pass = trig);
   }

   if(CutNPV){
   	bool passNPV = false;
	if (event.vxp.n() > 0 && event.vxp[0].nTracks() >= 3) passNPV = true;
   	m_accept.setCutResult(m_cutPositionNPV, pass = passNPV);
   }




  if(CutMultiLeptonsInclusive){
    m_accept.setCutResult(m_cutPositionMultiLeptonsInclusive , pass = (nLeptonsCut<=leps.size()));
    if(pass) {
        //only pass the minimum leptons necessary to pass the cut
    	vector <wwwAnalysis::PhysicsObject * > sub(&leps[0],&leps[nLeptonsCut]);
	vector< PhysicsObjectPair > pairs = getSFOSPairs(sub);
    	nSFOS= pairs.size(); 
	massesSFOS.clear();
  	for (unsigned int i = 0; i < pairs.size() ; i++)
  		massesSFOS.push_back( (pairs[i].first->momentum() + pairs[i].second->momentum()).M() );

    }
  }

  if(CutMultiLeptonsExclusive){
    m_accept.setCutResult(m_cutPositionMultiLeptonsExclusive , pass = (nLeptonsCut==leps.size()));
    if(pass){
	vector< PhysicsObjectPair > pairs = getSFOSPairs(leps);
    	nSFOS= pairs.size(); 
	massesSFOS.clear();
  	for (unsigned int i = 0; i < pairs.size() ; i++)
  		massesSFOS.push_back( (pairs[i].first->momentum() + pairs[i].second->momentum()).M() );
    }
  }
  if(CutLooseDilepton){
  	
	bool passDilepton = false;
	int nlep = leps_Loose.size();
	int nMu = 0;
	int nEl = 0;
	if (nlep==2){
  	  for (int i = 0; i< nlep; i++){
	  	if(leps_Loose[i]->type()==ELECTRON) nEl+=1;
	  	else if(leps_Loose[i]->type()==MUON) nMu+=1;
	  }
	  if(looseDileptonSameFlavor && ((nMu==2 && nEl==0) || (nMu==0 && nEl==2))) passDilepton = true;
	  else if (!looseDileptonSameFlavor && nMu==1 && nEl==1) passDilepton = true;  //opposite flavor

	}

    	m_accept.setCutResult(m_cutPositionLooseDilepton, pass = passDilepton);
  }

  if(CutLeptonMultiplictyFlavorQuality){

	int countLooseNotTightElectrons = 0;
	int countLooseNotTightMuons = 0;
  	for(unsigned int i = 0; i < leps_LooseNotTight.size() ; i++){
		if(leps_LooseNotTight[i]->type()==ELECTRON)  countLooseNotTightElectrons+=1;
		else if(leps_LooseNotTight[i]->type()==MUON) countLooseNotTightMuons+=1;
	}

	//includes tight
	int countLooseElectrons = 0;
	int countLooseMuons = 0;
  	for(unsigned int i = 0; i < leps_Loose.size() ; i++){
		if(leps_Loose[i]->type()==ELECTRON)  countLooseElectrons+=1;
		else if(leps_Loose[i]->type()==MUON) countLooseMuons+=1;
	}

	int countTightElectrons = 0;
	int countTightMuons = 0;
  	for(unsigned int i = 0; i < leps.size() ; i++){
		if(leps[i]->type()==ELECTRON)  countTightElectrons+=1;
		else if(leps[i]->type()==MUON) countTightMuons+=1;
	}
	bool passLepCount = true;
	if(nLooseNotTightMuonsCut >=0 && nLooseNotTightMuonsCut!=countLooseNotTightMuons) passLepCount = false;
	if(nLooseNotTightElectronsCut >=0 && nLooseNotTightElectronsCut!=countLooseNotTightElectrons) passLepCount = false;
	if(nTightMuonsCut >=0 && nTightMuonsCut!=countTightMuons) passLepCount = false;
	if(nTightElectronsCut >=0 && nTightElectronsCut!=countTightElectrons) passLepCount = false;
	if(nLooseMuonsCut >=0 && nLooseMuonsCut!=countLooseMuons) passLepCount = false;
	if(nLooseElectronsCut >=0 && nLooseElectronsCut!=countLooseElectrons) passLepCount = false;

        m_accept.setCutResult(m_cutPositionLeptonMultiplicityFlavorQuality , pass = passLepCount);

  }



  if(CutTriggerMatching){
    m_accept.setCutResult(m_cutPositionTriggerMatching, pass = triggerMatch);
  }

  // Cut jet cleaning
  //switching from jet_loose to jet
   bool foundIsLooserBadJet = false;
   if(CutJetCleaning){

     for(unsigned int i = 0;i<jet_all.size() && !foundIsLooserBadJet;i++)
   	foundIsLooserBadJet = foundIsLooserBadJet  || 
		IsLooserBadJet( jet_all[i].d3pd().pt(), 
				jet_all[i].d3pd().emscale_eta(), 
				jet_all[i].d3pd().sumPtTrk(), 
				jet_all[i].d3pd().LArQuality(), 
				jet_all[i].d3pd().NegativeE(), 
				jet_all[i].d3pd().emfrac(), 
				jet_all[i].d3pd().hecf(), 
				jet_all[i].d3pd().Timing(), 
				jet_all[i].d3pd().fracSamplingMax(), 
				jet_all[i].d3pd().HECQuality(), 
				jet_all[i].d3pd().AverageLArQF()); 

    m_accept.setCutResult( m_cutPositionJetCleaning,pass =!foundIsLooserBadJet);
  }

  // Cut HotTile
  if(CutHotTile) {
    bool reject = false;
    if(!isMC && (runNumber == 202660 || runNumber == 202668 || runNumber == 202712 || runNumber == 202740 ||
		 runNumber == 202965 || runNumber == 202987 || runNumber == 202991 || runNumber == 203027 || runNumber == 203169)) {
      for(unsigned int i = 0; i < jet_all.size() && !reject; i++) {
        double eta = jet_all[i].d3pd().eta();
        double phi = jet_all[i].d3pd().phi();
        double fmax = jet_all[i].d3pd().fracSamplingMax();
        double smax = jet_all[i].d3pd().SamplingMax();
        if(fmax>0.6 && smax==13 && eta>-0.2 && eta<-0.1 && phi>2.65 && phi<2.75)
          reject = true;
      }
    }
    m_accept.setCutResult( m_cutPositionHotTile, pass = !reject);
  }
  
  // Cut FCal
  if(CutFCal) {
    bool reject = false;
    /*
    if(runNumber >= 206248 && runNumber <= 207332) {
      for(int i = 0; i < jet_all.size() && !reject; i++) {
        double eta = jet_all[i].momentum().Eta();
        double phi = jet_all[i].momentum().Phi();
        double pt = jet_all[i].momentum().Pt();
        if(fabs(eta) > 3.2 && phi < 3.1 && phi > 1.6 && pt > 20000)
          reject = true;
      }
    }
    */
    m_accept.setCutResult( m_cutPositionFCal, pass = !reject);
  }

  // Cut LArError
  if(CutLArError){
    m_accept.setCutResult( m_cutPositionLArError, pass = 
    (event.eventinfo.larError() == 0 || event.eventinfo.larError() == 1));
    
  }
  
  //The leptons are assumed to be pt ordered with lep1 having the highest
  //pt and lep3 having the lowest
  if(CutThreeLeptonPt || CutThreeLeptonPtFirst  || CutThreeLeptonPtSecond  || CutThreeLeptonPtThird || CutThreeLeptonPtFourth){
   bool threelep;
  if(nLeptonsCut==2 &&leps.size()>=2)      threelep= (leps[0]->momentum().Pt() > lep1PtMin && leps[1]->momentum().Pt() > lep2PtMin); 
  else if(nLeptonsCut==3&&leps.size()>=3)  threelep= (leps[0]->momentum().Pt() > lep1PtMin && leps[1]->momentum().Pt() > lep2PtMin && leps[2]->momentum().Pt() > lep3PtMin); 
  else if(nLeptonsCut==4&&leps.size()>=4)  threelep= (leps[0]->momentum().Pt() > lep1PtMin && leps[1]->momentum().Pt() > lep2PtMin && leps[2]->momentum().Pt() > lep3PtMin && leps[3]->momentum().Pt() > lep4PtMin); 
  else threelep= false; //let's leave the 3 leptons case a default...
    m_accept.setCutResult(m_cutPositionThreeLeptonPt, pass = threelep);
  }

  // Cut metMin
    double MET = 0.;
    double METPhi = 0.;
  if(CutmetMin || CutmetMinFirst || CutmetMinSecond  || CutmetMinThird  ) {

    if (useSTVFMetMin) {
    	MET=oMET->momentumSTVF().Et();
	METPhi=oMET->momentumSTVF().Phi();
    }
    else {
    	MET=oMET->momentum().Et(); //event.MET_RefFinal.et(); //met.Mod();
	METPhi=oMET->momentum().Phi();
    }
    bool metpass;
	 if(metMin<0)metpass= (MET  < fabs(metMin));
	 else metpass= (MET  > metMin);
    m_accept.setCutResult( m_cutPositionmetMin, pass = metpass );

    //What is the purpose of the logic below
    //m_accept.setCutResult( m_cutPositionmetMin, pass = ((isSF && MET > metSFMin) || (!isSF && MET > metDFMin)));
  }

  if(CutThreeLepMtMin){
  	bool threelepmtpass = false;
  	if(leps.size()<3) threelepmtpass =false;
	else {
            TLorentzVector tlvLep123 = leps[0]->momentum()+leps[1]->momentum()+leps[2]->momentum();
	    double metEt = 0.;
	    double metPhi = 0.;
	    if (useSTVFMetMin) {
	    	metEt = oMET->momentumSTVF().Pt();
	    	metPhi = oMET->momentumSTVF().Phi();
	    }
   	    else {
	    	metEt = oMET->momentum().Pt();
	    	metPhi = oMET->momentum().Phi();
	    }
    	    double mt = TMath::Sqrt(2.*tlvLep123.Pt()*metEt*(1.-TMath::Cos(tlvLep123.Phi()-metPhi)));
	    if (mt > threeLepMtMin) threelepmtpass = true;

	}
  	m_accept.setCutResult(m_cutPositionThreeLepMtMin, pass = threelepmtpass);

  }
  //Mt min
  if(CutMtMin || CutMtMinFirst || CutMtMinSecond  || CutMtMinThird  ) {
    bool mtpass = false;
    double mt1 = -1;
    double mt2 = -1;
    double mt3 = -1;
    //allows for configuration of 1,2 or 3 lepton mt cuts
    if ( lep1MtMin >0 && lep2MtMin > 0 && lep3MtMin >0 && leps.size()<3) mtpass = false;
    else if ( lep1MtMin >0 && lep2MtMin > 0 && leps.size()<2) mtpass = false;
    else if ( lep1MtMin >0 && leps.size()<1) mtpass = false;
    else{
    	mtpass = true;
    	if(lep1MtMin > 0) {
		mt1=TMath::Sqrt(2.*leps[0]->momentum().Pt()*MET*(1.-TMath::Cos(leps[0]->momentum().Phi()-METPhi)));
		mtpass = mtpass && mt1 > lep1MtMin;
	}
    	if(lep2MtMin > 0) {
		mt2=TMath::Sqrt(2.*leps[1]->momentum().Pt()*MET*(1.-TMath::Cos(leps[1]->momentum().Phi()-METPhi)));
		mtpass = mtpass && mt2 > lep2MtMin;
	}
    	if(lep3MtMin > 0) {
		mt3=TMath::Sqrt(2.*leps[2]->momentum().Pt()*MET*(1.-TMath::Cos(leps[2]->momentum().Phi()-METPhi)));
		mtpass = mtpass && mt3 > lep3MtMin;
	}
    }
    m_accept.setCutResult( m_cutPositionMtMin, pass = mtpass );
  }

  //Classify pairs 
  vector < std::pair <const PhysicsObject *,const PhysicsObject * > > vPairs;
  vPairs.clear();
  vector < PairType > vPairType;
  vPairType.clear();
  vector < string > vPairTypeString;
  vPairTypeString.clear();
  if(leps.size()>=3){
	vPairs.push_back(std::make_pair(leps[0],leps[1]));
	vPairs.push_back(std::make_pair(leps[0],leps[2]));
	vPairs.push_back(std::make_pair(leps[1],leps[2]));


	bool sameSign = false;
	bool sameFlavor = false;
	for(unsigned int i=0;i<vPairs.size();i++){
		sameFlavor = 
			vPairs.at(i).first->type()==vPairs.at(i).second->type();
		sameSign =
			(vPairs.at(i).first->charge()
			 *vPairs.at(i).second->charge() > 0.) 
			? true : false;
		if (sameFlavor && sameSign) {
			vPairType.push_back(SFSS);
			vPairTypeString.push_back("SFSS");
		}
		else if (sameFlavor && !sameSign) {
			vPairType.push_back(SFOS);
			vPairTypeString.push_back("SFOS");
		}
		else if (!sameFlavor && sameSign) {
			vPairType.push_back(OFSS);
			vPairTypeString.push_back("OFSS");

		}
		else if (!sameFlavor && !sameSign) {
			vPairType.push_back(OFOS);
			vPairTypeString.push_back("OFOS");
		}
		else std::cout << "WARNING!  Couldn't classify pair" << std::endl;
		//should exit if fails, although it shouldn't...

		
		

	}
  }

  // Cut Z Veto or inverted Z Veto
  double invMass = -DBL_MAX;
    bool passInvZVeto = false;
    bool passZVeto = true;
    bool threePairs = true;
    //if(CutZVeto) std::cout << "z veto"<<std::endl;
    //if(CutInvZVeto) std::cout << "inv z veto"<<std::endl;
  if(CutZVeto || CutInvZVeto){
    	//assume true unless catch at least one pair or not 3 pairs

	if (vPairs.size()!=3) threePairs=false;
	else{
		for(unsigned int i=0;i<vPairs.size();i++){
			if(allowZVetoInclusiveSign){
				if(vPairType.at(i)!=SFOS && vPairType.at(i)!=SFSS) continue;
				//only really interested in same-sign ee pairs
				if(vPairType.at(i)==SFSS && vPairs.at(i).first->type()==MUON ) continue;
			}
			else{
				if(vPairType.at(i)!=SFOS) continue;
			}

			invMass = ( vPairs.at(i).first->momentum()
				    + vPairs.at(i).second->momentum() ).M();
			if( invMass > zVetoMassMin  && invMass < zVetoMassMax){
				if(CutZVeto) passZVeto = false;
				if(CutInvZVeto) passInvZVeto = true;
			}

		}
	}

    if(CutZVeto) {
    	m_accept.setCutResult(m_cutPositionZVeto, pass = threePairs && passZVeto);
	//if(threePairs && passZVeto) std::cout << "pass cut zveto" << std::endl;
	//else std::cout << "fail cut zveto" << std::endl;
    }
    else if(CutInvZVeto) {
    	m_accept.setCutResult(m_cutPositionZVeto, pass = threePairs && passInvZVeto);
	//if(threePairs && passInvZVeto) std::cout << "pass cut inv zveto" << std::endl;
	//else std::cout << "fail cut inv zveto" << std::endl;
    }
  }


  if(CutZTagAndProbe || CutFakeTagAndProbe || CutFakeTagAndProbeInclusiveSign){
  	//Require that there is at least one z tag and probe pair
	bool passTP = false;
	if (tags.size() != probes.size()) {
		std::cout << "WARNING! Tags and Probes aren't paired properly" << std::endl;
		passTP = false;
	}
	else if ( tags.size()>0 ) passTP = true;

	if(CutZTagAndProbe) m_accept.setCutResult(m_cutPositionZTagAndProbe, pass = passTP);
	if(CutFakeTagAndProbe) m_accept.setCutResult(m_cutPositionFakeTagAndProbe, pass = passTP);
	if(CutFakeTagAndProbeInclusiveSign) m_accept.setCutResult(m_cutPositionFakeTagAndProbe, pass = passTP);
  	
  }

  if(CutZPlusJetsTagAndProbe || CutZPlusGammaTagAndProbe){
  	//Require that there is at least one z tag and probe pair
	bool passTP = false;
	if (tags.size() != probes.size() || tags2.size() != probes.size()) {
		std::cout << "WARNING! Tags and Probes aren't paired properly" << std::endl;
		passTP = false;
	}
	else if ( tags.size()>0 && tags2.size()>0 ) passTP = true;

	if(CutZPlusJetsTagAndProbe) m_accept.setCutResult(m_cutPositionZPlusJetsTagAndProbe, pass = passTP);
	if(CutZPlusGammaTagAndProbe) m_accept.setCutResult(m_cutPositionZPlusGammaTagAndProbe, pass = passTP);
  }

  

  // Cut bTagVeto
  if(CutbTagVeto) {
    m_accept.setCutResult( m_cutPositionbTagVeto, pass = btagveto);
  }
  // Cut Inverted bTagVeto
  if(CutInvbTagVeto) {
    m_accept.setCutResult( m_cutPositionInvbTagVeto, pass = !btagveto);
  }
  

  //Cut Delta Phi
  if(CutDeltaPhi){
        bool passDeltaPhi = true;
	double deltaPhi = -1.;
  	if(! (leps.size()==3) ) passDeltaPhi = false;
	else {
            TLorentzVector tlvLep123 = leps[0]->momentum()+leps[1]->momentum()+leps[2]->momentum();
	    if (useSTVFMetMin) deltaPhi = oMET->momentumSTVF().DeltaPhi(tlvLep123);
   	    else deltaPhi = oMET->momentum().DeltaPhi(tlvLep123);

	    if( DeltaPhiLowEdge > 0 && TMath::Abs(deltaPhi) < DeltaPhiLowEdge)  passDeltaPhi = false;
	    if( DeltaPhiHighEdge > 0 && TMath::Abs(deltaPhi) > DeltaPhiHighEdge)  passDeltaPhi = false;

	}
        m_accept.setCutResult( m_cutPositionDeltaPhi, pass = passDeltaPhi);
  }

  //Cut to leave only events with certain pair type
  if(CutPairType){
  	bool foundPairType = false;
	//Can only demand one pair type for now
	PairType reqPairType = SFOS; //Default
	if(reqSFSS != 0) reqPairType = SFSS;
	else if(reqOFSS != 0 ) reqPairType = OFSS;
	else if(reqOFOS != 0 ) reqPairType = OFOS;

        //allow to invert the requirement
        bool invertReq = false;
	if ( (reqPairType==SFOS && reqSFOS==-1) ||
	     (reqPairType==SFSS && reqSFSS==-1) ||
	     (reqPairType==OFSS && reqOFSS==-1) ||
	     (reqPairType==OFOS && reqOFOS==-1) ) invertReq = true;
	//std::cout << reqPairType << "\t" << reqSFOS << "\t"<<(invertReq ? "true" : "false") << std::endl;


  	for (unsigned int i=0;i<vPairType.size();i++){
		if (vPairType.at(i) == reqPairType) {
			foundPairType = true;
			break;
		}
	}
	if (invertReq) m_accept.setCutResult( m_cutPositionPairType, pass = !foundPairType);
	else m_accept.setCutResult( m_cutPositionPairType, pass = foundPairType);
  }

  //Cut to leave only events with certain flavor composition
  if(CutFlavor){
  	bool foundFlavor = false;
	int nMu = 0;
	if(leps.size()>=3) {
		if(leps[0]->type()==MUON) nMu+=1;
		if(leps[1]->type()==MUON) nMu+=1;
		if(leps[2]->type()==MUON) nMu+=1;

		if(mmmFlavor && nMu==3) foundFlavor = true;
		else if(mmeFlavor && nMu==2) foundFlavor = true;
		else if(meeFlavor && nMu==1) foundFlavor = true;
		else if(eeeFlavor && nMu==0) foundFlavor = true;
		else foundFlavor = false;
	}
	else foundFlavor = false;

	m_accept.setCutResult( m_cutPositionFlavor, pass = foundFlavor);
  }
  

  // HW Charge sum. require sum of lepton charges = +/- 1
  bool passHWChargeSum = false;
  if(CutHWChargeSum){
   if(leps.size()>=3){
   	int chargeSum = leps[0]->charge() + leps[1]->charge() + leps[2]->charge();
	if (chargeSum == 1 || chargeSum == -1) passHWChargeSum = true;
   }
   else passHWChargeSum = false;
   m_accept.setCutResult(m_cutPositionHWChargeSum,pass = passHWChargeSum);

  }
  //N-jet cut
  if(CutNJet){
   //should I loop only over those jets passing our selection?
   bool passNJet = false;
   int jetSize = jet.size();
   if (jetSize <= nJetMax) passNJet = true;
   else passNJet = false;
   m_accept.setCutResult(m_cutPositionNJet,pass = passNJet);
  }
  // Top Veto Cut
  if(CutTopVeto){
   m_accept.setCutResult(m_cutPositionTopVeto,pass = btagveto);
  }
  // HW MET Cut
  if(CutHWMET){
   bool passHWMET = false;
   if(oMET->momentumSTVF().Et() > hwMETSTVFMin) passHWMET = true;
   //if(oMET->rawMomentum().Et() > hwMETSTVFMin) passHWMET = true;
   m_accept.setCutResult(m_cutPositionHWMET,pass = passHWMET);
  }
 // Cut HW Z Veto
  double hwInvMass = -DBL_MAX;
  bool passHWZVeto = true;
  if(CutHWZVeto){
    	//assume true unless catch at least one pair or not 3 pairs
	if (vPairs.size()!=3) passHWZVeto=false;
	for(unsigned int i=0;i<vPairs.size();i++){
		if(vPairType.at(i)!=SFOS) continue;

		hwInvMass = ( vPairs.at(i).first->momentum()
			    + vPairs.at(i).second->momentum() ).M();
		if( hwInvMass > hwZVetoMassMin  && hwInvMass < hwZVetoMassMax){
			passHWZVeto=false;
			break;
		}

	}
    m_accept.setCutResult(m_cutPositionHWZVeto, pass = passHWZVeto);
  }

 // Cut HW Inv Mass
  hwInvMass = -DBL_MAX;
  bool passHWInvMass = false;
  double highestInvMass= -DBL_MAX;
  double lowestInvMass= DBL_MAX;
  if(CutHWInvMass){
    	//assume true unless catch at least one pair or not 3 pairs
	if (vPairs.size()!=3) passHWInvMass=false;
	else{
		for(unsigned int i=0;i<vPairs.size();i++){
			//only look at pairs with opposite sign
			if(vPairType.at(i)!=SFOS && vPairType.at(i)!=OFOS) continue;

			hwInvMass = ( vPairs.at(i).first->momentum()
				    + vPairs.at(i).second->momentum() ).M();
			if (hwInvMass > highestInvMass) highestInvMass = hwInvMass;
			if (hwInvMass < lowestInvMass) lowestInvMass = hwInvMass;

		}
		if( highestInvMass <  hwInvMassMax  && lowestInvMass > hwInvMassMin){
				passHWInvMass=true;
		}
		else {
			passHWInvMass = false;
		}
	}

    	m_accept.setCutResult(m_cutPositionHWInvMass, pass = passHWInvMass);
  }

 // Cut HW DeltaR
  bool passHWDeltaR = true;
  const PhysicsObject* hwLep0 = NULL;
  const PhysicsObject* hwLep1 = NULL;
  const PhysicsObject* hwLep2 = NULL;
  if(CutHWDeltaR){
    	//assume true unless catch at least one pair or not 3 pairs
	//
	
	if(leps.size()==3){
		//find the HW lep0 which is the one with a unique charge
		//lep1 is closest in Delta R to lep0, and lep2 is the remaining lepton
		if(leps[0]->charge()!=leps[1]->charge()  && leps[0]->charge()!=leps[2]->charge()) {
			hwLep0 = leps[0];
			if ( TMath::Abs(hwLep0->momentum().DeltaR(leps[1]->momentum())) < 
			     TMath::Abs(hwLep0->momentum().DeltaR(leps[2]->momentum())) ){
			     hwLep1 = leps[1];
			     hwLep2 = leps[2];
			}
			else {
			     hwLep1 = leps[2];
			     hwLep2 = leps[1];
			}
		}
		else if(leps[0]->charge()!=leps[1]->charge() && leps[1]->charge()!=leps[2]->charge() ){
			hwLep0 = leps[1];
			if ( TMath::Abs(hwLep0->momentum().DeltaR(leps[0]->momentum())) < 
			     TMath::Abs(hwLep0->momentum().DeltaR(leps[2]->momentum())) ){
			     hwLep1 = leps[0];
			     hwLep2 = leps[2];
			}
			else {
			     hwLep1 = leps[2];
			     hwLep2 = leps[0];
			}
		}
		else { 
			hwLep0 = leps[2];
			if ( TMath::Abs(hwLep0->momentum().DeltaR(leps[0]->momentum())) < 
			     TMath::Abs(hwLep0->momentum().DeltaR(leps[1]->momentum())) ){
			     hwLep1 = leps[0];
			     hwLep2 = leps[1];
			}
			else {
			     hwLep1 = leps[1];
			     hwLep2 = leps[0];
			}
		}
		
		//deltaR requirement is on HW lep0 and HW lep1
		if (hwLep0->momentum().DeltaR(hwLep1->momentum()) < hwDeltaRMax) passHWDeltaR = true;
		else passHWDeltaR = false;

	}
	else passHWDeltaR = false;


    	m_accept.setCutResult(m_cutPositionHWDeltaR, pass = passHWDeltaR);
  }

  hwLep0 = NULL;
  hwLep1 = NULL;
  hwLep2 = NULL;

  delete hwLep0;
  delete hwLep1;
  delete hwLep2;

  //di-lepton selections:
  //Fill in the informations needed for output:
  if(leps.size()==2&&nLeptonsCut==2){
	AdditionnalInfo.dilep=(nLeptonsCut==2);
  
    if (useSTVFMetMin) {
   MET=oMET->momentumSTVF().Et();
	METPhi=oMET->momentumSTVF().Phi();
    }
    else {
   MET=oMET->rawMomentum().Et(); //event.MET_RefFinal.et(); //met.Mod();
	METPhi=oMET->momentum().Phi();
    }


  // Flavour Cut
  if(CutSameFlavour){
  	bool SFdilep=(leps[0]->type() == leps[1]->type());
  	bool passSFDilep=(SFdilep==isSameFlavour); //Need to define isSameFlavour;
  	m_accept.setCutResult(m_cutPositionSameFlavour,pass = passSFDilep);
  }

  //Check if the pair is opposite sign.
  if(CutOppositeSign){
  	bool OSdilep=(leps[0]->charge() * leps[1]->charge()==-1);
  	bool passOSDilep=(OSdilep==isOppositeSign); //Need to define isOppositeSign;
  	m_accept.setCutResult(m_cutPositionOppositeSign,pass = passOSDilep);
  }  

  //Check the flavour cases
  if(CutDiLepFlavour){
	bool passDiLepFlavour=false;
	if(nMuon==2){
		passDiLepFlavour=(leps[0]->type() == MUON&&leps[1]->type() == MUON);
	}
	else if(nMuon==1){
		passDiLepFlavour=((leps[0]->type() == MUON&&leps[1]->type() == ELECTRON)||(leps[1]->type() == MUON&&leps[0]->type() == ELECTRON));
	}
	else if(nMuon==0){
		passDiLepFlavour=(leps[0]->type() == ELECTRON&&leps[1]->type() == ELECTRON);
	}
	else passDiLepFlavour=true;
  	m_accept.setCutResult(m_cutPositionDiLepFlavour,pass = passDiLepFlavour);
  }  

  //Check Inv mass :
  if(CutDiLepInvMass){
	bool passDiLepInvMass=false;
	double Zmass=(leps[0]->momentum()+leps[1]->momentum()).M();
	if(Zmass>=zVetoMassMin&&Zmass<=zVetoMassMax)passDiLepInvMass=true;
   //Fill in the informations needed for output:
	AdditionnalInfo.dilep_mll=Zmass;
  	m_accept.setCutResult(m_cutPositionDiLepInvMass,pass = passDiLepInvMass);
  }



  // Cut  SumPtObject
  if(CutSumPtObject){
	bool passSumPtObject=false;
	double sumHighPtObject=MET+leps[0]->momentum().Pt()+leps[1]->momentum().Pt();
	for (unsigned int ijet=0;ijet<jet.size();ijet++){
		sumHighPtObject+=jet[ijet].momentum().Pt();
	}
  //Fill in the informations needed for output:
	AdditionnalInfo.dilep_SumHPTO=sumHighPtObject;

	if(sumHighPtObject<=SumHPTO)passSumPtObject=true;
  	m_accept.setCutResult(m_cutPositionSumPtObject,pass = passSumPtObject);
  }

  // Cut  CosDphi
  if(CutCosDphi){	
	double cosDphi=cos(METPhi-leps[0]->momentum().Phi())+cos(METPhi-leps[1]->momentum().Phi());
	bool passCosDphi=false;
	//Fill in the informations needed for output:
	AdditionnalInfo.dilep_SumCosDphi=cosDphi;
	if(cosDphi>SumCosDphi)passCosDphi=true;
  	m_accept.setCutResult(m_cutPositionCosDphi,pass = passCosDphi);
  }

  // Cut TransversMass
  if(CutTransversMass){
    bool mtpass = false;
    double mt1 = -1;
    double mt2 = -1;
    if (leps.size()!=2) mtpass = false;
    else{
//		cout<<MET<<"  "<<METPhi<<endl;

    	mt1=TMath::Sqrt(2.*leps[0]->momentum().Pt()*MET*(1.-TMath::Cos(leps[0]->momentum().Phi()-METPhi)));
    	mt2=TMath::Sqrt(2.*leps[1]->momentum().Pt()*MET*(1.-TMath::Cos(leps[1]->momentum().Phi()-METPhi)));
  		//Fill in the informations needed for output:
		AdditionnalInfo.dilep_mT1=mt1;
		AdditionnalInfo.dilep_mT2=mt2;
    	if (mt1 > lep1MtMin && mt2 > lep2MtMin) mtpass=true;
    }
    m_accept.setCutResult( m_cutPositionTransversMass, pass = mtpass );
  }

  }

  // Cut FakeLeptons
  if(CutFakeLeptons){
    bool passNfakeLeptons=false;
//	cout<<"fake Size in EventSelector::"<<fakes.size()<<endl;
    if(nFakeLeptons==(fakes.size()))passNfakeLeptons=true;
    m_accept.setCutResult( m_cutPositionFakeLeptons, pass = passNfakeLeptons );
  }

  //End di-lepton selections


  //Begining 4-lepton selection:
  if(leps.size()==4&&nLeptonsCut==4){
   //Fill in the informations needed for output:
	AdditionnalInfo.quadlep=(nLeptonsCut==4);
  double mass12=-1;
  double mass34=-1;
  int pair12=-1;
  int pair34=-1;
  vector<const PhysicsObject*> Lep_p;
  vector<const PhysicsObject*> Lep_m;
  vector < std::pair <const PhysicsObject *,const PhysicsObject * > > lep_pairs;
  Lep_p.clear();
  Lep_m.clear();
  lep_pairs.clear();

  //Cut Opposite Sign
  if(Cut4LepOppositeSign){
//   cout<<"4lep OS"<<endl;
    bool pass4LepOS=false;
    int sumCharge=0;
    int prodCharge=1;
    for (unsigned int ilep=0;ilep<leps.size();ilep++){
	sumCharge +=leps[ilep]->charge();
	prodCharge*=int(fabs(leps[ilep]->charge())/leps[ilep]->charge());
//	cout<<ilep<<" sumchage "<<sumCharge<<" prodcharge "<<prodCharge<<"  "<<Lep_p.size()<<"  "<<Lep_m.size()<<endl;

	if(leps[ilep]->charge()>=0)Lep_p.push_back(leps[ilep]);
	else Lep_m.push_back(leps[ilep]);
    }
//   cout<<"End sumchage "<<sumCharge<<" prodcharge "<<prodCharge<<"  "<<Lep_p.size()<<"  "<<Lep_m.size()<<endl;
    //Check if the charge sum=0 and the charge product =1, then it means that we have a double OS pair.
    if(sumCharge==0&&prodCharge==1)pass4LepOS=true;
    m_accept.setCutResult( m_cutPosition4LepOppositeSign, pass = pass4LepOS );
  }

  //Select only certain flavour combinations: eeee,mumumumu,eemumu,mumuee
  if(Cut4LepFlavour){

    bool is4LepOF=false;
    bool useLepp1=false;
    bool useLepp2=false;
    bool useLepm1=false;
    bool useLepm2=false;
    
	for (unsigned int iplep=0;iplep<Lep_p.size();iplep++){
		for (unsigned int imlep=0;imlep<Lep_m.size();imlep++){
			if(Lep_p[iplep]->type()==Lep_m[imlep]->type()){
				lep_pairs.push_back(std::make_pair(Lep_p[iplep],Lep_m[imlep]));
			if(iplep==0)useLepp1=true;
			if(iplep==1)useLepp2=true;
			if(imlep==0)useLepm1=true;
			if(imlep==1)useLepm2=true;
			}
		}
	}
    if(useLepp1&&useLepp2&&useLepm1&&useLepm2)is4LepOF=true;
//    if(Lep_p.size()==2&&Lep_m.size()==2&&lep_pairs.size()!=4){
//		cout<<"1FLav::"<<useLepp1<<"  "<<useLepp2<<"  "<<useLepm1<<"  "<<useLepm2<<"  "<<lep_pairs.size()<<"  "<<is4LepOF<<endl;
//		cout<<"2FLav::"<<bool(Lep_p[0]->type()==MUON)<<"  "<<bool(Lep_p[1]->type()==MUON)<<"  "<<bool(Lep_m[0]->type()==MUON)<<"  "<<bool(Lep_m[1]->type()==MUON)<<"  "<<lep_pairs.size()<<"  "<<is4LepOF<<endl;
//		}
    m_accept.setCutResult( m_cutPosition4LepFlavour, pass = is4LepOF );
  }

  // Cut  Di-Lep Inv Mass
  if(Cut4LepInvMass){
    bool pass4LepInvMass=false;
    if(lep_pairs.size()==2){
	double massfirstpair=(lep_pairs[0].first->momentum()+lep_pairs[0].second->momentum()).M();
	double masssecondpair=(lep_pairs[1].first->momentum()+lep_pairs[1].second->momentum()).M();
	
	if(massfirstpair>masssecondpair){
		mass12=massfirstpair;
  		mass34=masssecondpair;
		pair12=0;
		pair34=1;
	}
	else{
		mass34=massfirstpair;
  		mass12=masssecondpair;
		pair12=1;
		pair34=0;
	}

    }


    else if(lep_pairs.size()==4){
	double mtrial1=fabs((lep_pairs[0].first->momentum()+lep_pairs[0].second->momentum()).M()-91187.6)+fabs((lep_pairs[3].first->momentum()+lep_pairs[3].second->momentum()).M()-91187.6);
	double mtrial2=fabs((lep_pairs[1].first->momentum()+lep_pairs[1].second->momentum()).M()-91187.6)+fabs((lep_pairs[2].first->momentum()+lep_pairs[2].second->momentum()).M()-91187.6);
	
	int selected1=-1;
	int selected2=-1;	

	if(mtrial1>mtrial2){	
	selected1=1;
	selected2=2;
	}
	else{
	selected1=0;
	selected2=3;
	}

	double massfirstpair=(lep_pairs[selected1].first->momentum()+lep_pairs[selected1].second->momentum()).M();
	double masssecondpair=(lep_pairs[selected2].first->momentum()+lep_pairs[selected2].second->momentum()).M();
	
	if(massfirstpair>masssecondpair){
		mass12=massfirstpair;
  		mass34=masssecondpair;
		pair12=selected1;
		pair34=selected2;
	}
	else{
		mass34=massfirstpair;
  		mass12=masssecondpair;
		pair12=selected2;
		pair34=selected1;
	}


    }
    else pass4LepInvMass=false;
    
//    if(mass12>Mass12Min&&mass12<Mass12Max&&mass34>Mass34Min&&mass34<Mass34Max)pass4LepInvMass=true;

   if(pair12>=0&&pair34>=0){

	AdditionnalInfo.quadlep_m12=mass12;
	AdditionnalInfo.quadlep_m34=mass34;
		for (unsigned int jlep=0;jlep<leps.size();jlep++){
			if(leps[jlep]->momentum().DeltaR(lep_pairs[pair12].first->momentum())<0.001)AdditionnalInfo.quad_lep1=jlep;
			if(leps[jlep]->momentum().DeltaR(lep_pairs[pair12].second->momentum())<0.001)AdditionnalInfo.quad_lep2=jlep;
			if(leps[jlep]->momentum().DeltaR(lep_pairs[pair34].first->momentum())<0.001)AdditionnalInfo.quad_lep3=jlep;
			if(leps[jlep]->momentum().DeltaR(lep_pairs[pair34].second->momentum())<0.001)AdditionnalInfo.quad_lep4=jlep;
		}
	}
//	if((pair12>=0&&pair34>=0)&&(AdditionnalInfo.quad_lep1<0||AdditionnalInfo.quad_lep2<0||AdditionnalInfo.quad_lep3<0||AdditionnalInfo.quad_lep4<0))cout<<"last::"<<AdditionnalInfo.quad_lep1<<"  "<<AdditionnalInfo.quad_lep2<<"  "<<AdditionnalInfo.quad_lep3<<"  "<<AdditionnalInfo.quad_lep4<<endl;
    pass4LepInvMass=true;
//    cout<<"Event"<<pass4LepInvMass<<"  "<<lep_pairs.size()<<"  "<<Lep_p.size()<<"  "<<Lep_m.size()<<endl;
    m_accept.setCutResult( m_cutPosition4LepInvMass, pass = pass4LepInvMass );
  }

 }
  //End 4-lepton selection.


  vector<unsigned int> EventPrintList;
  /*
  EventPrintList.push_back(36344585);
  EventPrintList.push_back(18279228);
  EventPrintList.push_back(22450072);
  EventPrintList.push_back(44722629);
  EventPrintList.push_back(98330585);
  EventPrintList.push_back(65049560);
  EventPrintList.push_back(65628053);
  EventPrintList.push_back(84945977);
  EventPrintList.push_back(22758949);
  EventPrintList.push_back(57761483);
  EventPrintList.push_back(87724604);
  */


  //EventPrintList.push_back(5336);
for (unsigned int iEvent =0 ;iEvent < EventPrintList.size();iEvent++) 
	if (EventPrintList[iEvent]==event.eventinfo.EventNumber()){
		printf("Event#: %d\tRun#: %d\tlbn:%d\n",event.eventinfo.EventNumber(),event.eventinfo.RunNumber(),event.eventinfo.lbn());
		printf("Trigger Pass: %s\tEF_e24vhi_medium1: %s\tEF_e60_medium1: %s\tEF_mu24i_tight: %s\tEF_mu36_tight: %s\n",
			(trig ? "true" : "false"),
			(event.triggerbits.EF_e24vhi_medium1() ? "true" : "false"),
			(event.triggerbits.EF_e60_medium1() ? "true" : "false"),
			(event.triggerbits.EF_mu24i_tight() ? "true" : "false"),
			(event.triggerbits.EF_mu36_tight() ? "true" : "false"));
		printf("Pass TriggerMatching: %s\n",(triggerMatch ? "true" : "false"));
		printf("Lepton Pt [MeV] - Leading: %3.4e\tSubleading: %3.4e\tMinimum: %3.4e\n", 
			(leps[0] ? leps[0]->momentum().Pt() : 0.),
			(leps[1] ? leps[1]->momentum().Pt() : 0.),
			(leps[2] ? leps[2]->momentum().Pt() : 0.));
		printf("MET  = %3.4e [MeV]\n",MET);

		if(leps.size()==3){
			printf("Lepton Type - Leading: %s\tSubleading: %s\tMinimum: %s\n",
				(leps[0]->type()==MUON ? "MUON" : "ELECTRON"),
				(leps[1]->type()==MUON ? "MUON" : "ELECTRON"),
				(leps[2]->type()==MUON ? "MUON" : "ELECTRON"));
			printf("Lepton Charge - Leading: %1.0f\tSubleading: %1.0f\tMinimum: %1.0f\n",
				leps[0]->charge(),
				leps[1]->charge(),
				leps[2]->charge());
			printf("Pair Type - Leading,Subleading: %s\t Leading,Minimum: %s\t Subleading,Minimum:  %s\n", 
				vPairTypeString[0].c_str(), vPairTypeString[1].c_str(), vPairTypeString[2].c_str());
			printf("Pair Invariant Mass [MeV]- Leading,Subleading: %3.4e\t Leading,Minimum: %3.4e\t Subleading,Minimum:  %3.4e\n", 
				( vPairs.at(0).first->momentum() + vPairs.at(0).second->momentum() ).M(),
				( vPairs.at(1).first->momentum() + vPairs.at(1).second->momentum() ).M(),
				( vPairs.at(2).first->momentum() + vPairs.at(2).second->momentum() ).M());
			printf("Pass Z Veto = %s\n",(passZVeto ? "true" : "false"));
	
		}
		printf("# Jets: %d\n",jet.size());
		for (unsigned int ijet = 0;ijet<jet.size();ijet++){
			printf("Jet #%d: jet_AntiKt4LCTopo_pt: %3.4e\tjet_AntiKt4LCTopo_eta: %3.4e\tjet_AntiKt4LCTopo_phi: %3.4e\n",
			ijet, jet[ijet].d3pd().pt(), jet[ijet].d3pd().eta(), jet[ijet].d3pd().phi());
			printf("\tjet_AntiKt4LCTopo_isBadLooseMinus: %d\n",jet[ijet].d3pd().isBadLooseMinus());
		}
		printf("Pass Jet Cleaning: %s",((!foundIsLooserBadJet) ? "true" : "false"));


	
	}


  return m_accept;
}


bool wwwAnalysis::TEventSelectorTool::IsLooserBadJet(  const float  &pt,
		      const float  &eta,
		      const float  &sumPtTrk,
		      const float  &LArQuality,
		      const float  &NegativeE,
		      const float  &emfrac,
		      const float  &hecf,
		      const float  &Timing,
		      const float  &fracSamplingMax,
		      const float  &HECQuality,
		      const float  &AverageLArQF )
{

  /*
    @author Haifeng Li <Haifeng.Li@cern.ch>

    All the unit should be MeV.
    The pT should be container variables without smearing
    
  */

  float chf      = pt != 0 ? sumPtTrk/pt : 0 ;
  float LArQmean = AverageLArQF / 65535; // typo in twiki page 65335. It's a small effect

  // HEC spike
  if( hecf>0.5 && fabs(HECQuality)>0.5 && LArQmean>0.8)           return true;
  if( fabs(NegativeE)>60000./*MeV*/)                              return true;
  // EM coherent noise
  if( emfrac>0.95 && fabs(LArQuality)>0.8 && LArQmean>0.8 && fabs(eta)<2.8 )   return true;
  // Cosmics and Beam background
  if( emfrac<0.05 && chf<0.05 && fabs(eta)<2. )             return true;
  if( emfrac<0.05 && fabs(eta)>2. )                         return true;
  if( fracSamplingMax>0.99&&fabs(eta)<2)                    return true;
  return false;
}


int wwwAnalysis::TEventSelectorTool::configuredForNSFOS(){
    if(CutPairType && CutFlavor && eeeFlavor &&
    	mmmFlavor  && mmeFlavor && meeFlavor &&
	reqSFOS == -1) return 0;

    if(CutPairType && CutFlavor && !eeeFlavor &&
    	!mmmFlavor  && mmeFlavor && meeFlavor &&
	reqSFOS == 1) return 1;

    if(CutPairType && CutFlavor && eeeFlavor &&
    	mmmFlavor  && !mmeFlavor && !meeFlavor &&
	reqSFOS == 1) return 2;
     
     return -1;

}

//std::vector < std::pair <const wwwAnalysis::PhysicsObject *,const wwwAnalysis::PhysicsObject * > >  wwwAnalysis::TEventSelectorTool::getSFOSPairs( const std::vector<wwwAnalysis::PhysicsObject*> &leptons){
std::vector < PhysicsObjectPair>  wwwAnalysis::TEventSelectorTool::getSFOSPairs( const std::vector<wwwAnalysis::PhysicsObject*> &leptons){
  //Classify pairs 
  //std::vector < std::pair <const wwwAnalysis::PhysicsObject *,const wwwAnalysis::PhysicsObject * > > vPairs;
  std::vector < PhysicsObjectPair > vPairs;
  vPairs.clear();
  for (unsigned int i=0; i < leptons.size(); i++){
    for (unsigned int j=0; j < leptons.size(); j++){
      if( j <= i ) continue;
      if(leptons.at(i)->type()!=leptons.at(j)->type()) continue;
      if(leptons.at(i)->charge()*leptons.at(j)->charge() > 0 ) continue;
      vPairs.push_back(std::make_pair(leptons.at(i),leptons.at(j)));
    }
  }
  return vPairs;
}


/*
int wwwAnalysis::TEventSelectorTool::getNSFOSPairs( const std::vector<PhysicsObject*> &leptons){

	//split up by electrons or muons
	std::vector<int> muonCharges;
	std::vector<int> electronCharges;
	for (unsigned int k=0; k < leptons.size(); k++){
		if(leptons[k]->type()==MUON) muonCharges.push_back(leptons[k]->charge());
		else if(leptons[k]->type()==ELECTRON) electronCharges.push_back(leptons[k]->charge());
		else{
			std::cerr << "ERROR in wwwAnalysis::TEventSelectorTool::getNSFOS type not understood" << std::endl;
			return -1;
		}
	}

	int nOppositeSign = 0;
	//std::cout << "el size: " << electronCharges.size() << std::endl;
	//std::cout << "mu size: " << muonCharges.size() << std::endl;

	//count nsfos pairs found in electrons
	for (unsigned int i=0; i < electronCharges.size(); i++){
		for (unsigned int j=0; j < electronCharges.size(); j++){
			if( j <= i ) continue;
			
			//std::cout << "charges " << electronCharges[i] << "\t" << electronCharges[j] << std::endl;
			int chargeProd = electronCharges[i]*electronCharges[j];
			bool isOppositeSign = false;
			if (chargeProd == 1) isOppositeSign = false;
			else if (chargeProd == -1) isOppositeSign = true;
			else{
				std::cerr << "ERROR in wwwAnalysis::TEventSelectorTool::getNSFOS chargeProd = "  
					  << chargeProd << " not understood" << std::endl;
				return -1;
			}

			if(isOppositeSign) nOppositeSign+=1;
			
		}
	}

	//count nsfos pairs found in muons
	for (unsigned int i=0; i < muonCharges.size(); i++){
		for (unsigned int j=0; j < muonCharges.size(); j++){
			if( j <= i ) continue;
			
			int chargeProd = muonCharges[i] * muonCharges[j];
			bool isOppositeSign = false;
			if (chargeProd == 1) isOppositeSign = false;
			else if (chargeProd == -1) isOppositeSign = true;
			else{
				std::cerr << "ERROR in wwwAnalysis::TEventSelectorTool::getNSFOS chargeProd = "  
					  << chargeProd << "not understood" << std::endl;
				return -1;
			}
			if(isOppositeSign) nOppositeSign+=1;
		}
	}

	return nOppositeSign;
};
*/
										 
