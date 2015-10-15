##=============================================================================
## Name:        EventSelectorCutDefs
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Define the cut values for the EventSelectorTools
##
##=============================================================================

# import the needed Reflex and ROOT stuff
import PyCintex
PyCintex.Cintex.Enable()
import ROOT

# Import a needed helper
from PATCore.HelperUtils import *

# Define GeV
GeV = 1000.0

def EventSelectorToolConfig_Pass(theTool) :
    theTool = GetTool(theTool)
    pass
def EventSelectorToolConfig_Baseline_Preselection_Trigger(theTool) :
    theTool = GetTool(theTool)
    theTool.CutTruthFilter = True
    theTool.CutTrigger = True
    theTool.CutStreamOverlap = True
    theTool.includeEMuTrigger = True
    theTool.includeEETrigger = True
    theTool.includeMuMuTrigger = True
    theTool.CutNPV = True
    theTool.nPVMin = 1
    theTool.CutJetCleaning = False
    theTool.CutHotTile = False
    theTool.CutFCal = False
    theTool.CutLArError = False
    theTool.CutDilepton = False
    theTool.CutOppositeCharge = False
    theTool.CutFakeCharge = -1
    theTool.nMuon = -1
    theTool.CutTriggerMatching = False
    theTool.CutMultiLeptonsExclusive = False
    theTool.CutLeptonMultiplictyFlavorQuality = False
    theTool.nLooseNotTightMuonsCut = -1
    theTool.nLooseNotTightElectronsCut = -1
    theTool.nLooseMuonsCut = -1
    theTool.nLooseElectronsCut = -1
    theTool.nTightMuonsCut = -1
    theTool.nTightElectronsCut = -1

    theTool.CutLooseDilepton= False
    theTool.looseDileptonSameFlavor  = False
    theTool.nLeptonsCut=3
    theTool.CutNTau = False
    theTool.nTau = 0
    theTool.CutZTagAndProbe  = False
    theTool.CutZPlusJetsTagAndProbe  = False
    theTool.CutZPlusGammaTagAndProbe  = False
    theTool.CutFakeTagAndProbe = False
    theTool.CutFakeTagAndProbeInclusiveSign = False

    theTool.CutThreeLeptonPt = False
    theTool.CutThreeLeptonPtFirst = False
    theTool.CutThreeLeptonPtSecond = False
    theTool.CutThreeLeptonPtThird = False
    theTool.lep1PtMin = 25000
    theTool.lep2PtMin = 20000
    theTool.lep3PtMin = 20000
    theTool.CutmetMin = False
    theTool.CutmetMinFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutmetMinThird = False
    theTool.useSTVFMetMin = True
    theTool.metMin    = 25000
    theTool.CutZVeto = False
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.CutbTagVeto = False
    theTool.CutbTagVeto = False
    theTool.zVetoMassMin    =  75000
    theTool.zVetoMassMax    = 105000
    theTool.CutPairType  = False
    theTool.reqSFOS  = 0 #False
    theTool.reqSFSS  = 0 #False
    theTool.reqOFOS  = 0 #False
    theTool.reqOFSS  = 0 #False
    theTool.CutNJet = False
    theTool.nJetMax = -1
    theTool.CutDeltaPhi = False
    theTool.DeltaPhiLowEdge = -1
    theTool.DeltaPhiHighEdge = -1
    theTool.CutTopVeto = False
    theTool.CutHWMET = False
    theTool.CutHWZVeto = False
    theTool.hwZVetoMassMin    =  -1 #75000
    theTool.hwZVetoMassMax    = -1 #105000
    theTool.CutHWInvMass = False
    theTool.hwInvMassMin    =  -1 
    theTool.hwInvMassMax    = -1 
    theTool.CutHWDeltaR = False
    theTool.hwDeltaRMax = -1
    theTool.CutFlavor = False
    theTool.eeeFlavor = True
    theTool.mmmFlavor = True
    theTool.mmeFlavor = True
    theTool.meeFlavor = True
    theTool.CutHWChargeSum = False
    theTool.CutThreeLepMtMin = False
    pass
def EventSelectorToolConfig_Baseline_Truth(theTool) :
    theTool = GetTool(theTool)
    theTool.CutTruthFilter = True
    theTool.CutTrigger = False
    theTool.CutStreamOverlap = True
    theTool.CutNPV = False
    pass


def EventSelectorToolConfig_Baseline_Preselection(theTool) :
    theTool = GetTool(theTool)
    theTool.CutTruthFilter = True
    theTool.CutTrigger = True
    theTool.CutStreamOverlap = True
    theTool.includeEMuTrigger = True
    theTool.includeEETrigger = True
    theTool.includeMuMuTrigger = True
    theTool.CutNPV = True
    theTool.nPVMin = 1
    theTool.CutJetCleaning = True
    theTool.CutHotTile = True
    theTool.CutFCal = True
    theTool.CutLArError = True
    theTool.CutDilepton = False
    theTool.CutOppositeCharge = False
    theTool.CutFakeCharge = -1
    theTool.nMuon = -1
    theTool.CutTriggerMatching = True
    theTool.CutMultiLeptonsExclusive = True
    theTool.CutLeptonMultiplictyFlavorQuality = False
    theTool.nLooseNotTightMuonsCut = -1
    theTool.nLooseNotTightElectronsCut = -1
    theTool.nLooseMuonsCut = -1
    theTool.nLooseElectronsCut = -1
    theTool.nTightMuonsCut = -1
    theTool.nTightElectronsCut = -1
    theTool.CutLooseDilepton= False
    theTool.looseDileptonSameFlavor  = False
    theTool.nLeptonsCut=3
    theTool.CutNTau = False
    theTool.nTau = 0
    theTool.CutZTagAndProbe  = False
    theTool.CutZPlusJetsTagAndProbe  = False
    theTool.CutZPlusGammaTagAndProbe  = False
    theTool.CutFakeTagAndProbe = False
    theTool.CutFakeTagAndProbeInclusiveSign = False
    theTool.CutThreeLeptonPt = False
    theTool.CutThreeLeptonPtFirst = False
    theTool.CutThreeLeptonPtSecond = False
    theTool.CutThreeLeptonPtThird = False
    theTool.lep1PtMin = 25000
    theTool.lep2PtMin = 20000
    theTool.lep3PtMin = 20000
    theTool.CutmetMin = False
    theTool.CutmetMinFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutmetMinThird = False
    theTool.useSTVFMetMin = True
    theTool.metMin    = 25000
    theTool.CutZVeto = False
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.zVetoMassMin    =  75000
    theTool.zVetoMassMax    = 105000
    theTool.CutbTagVeto = False
    theTool.CutbTagVeto = False
    theTool.CutPairType  = False
    theTool.reqSFOS  = 0 #False
    theTool.reqSFSS  = 0 #False
    theTool.reqOFOS  = 0 #False
    theTool.reqOFSS  = 0 #False
    theTool.CutNJet = False
    theTool.nJetMax = -1
    theTool.CutDeltaPhi = False
    theTool.DeltaPhiLowEdge = -1
    theTool.DeltaPhiHighEdge = -1
    theTool.CutTopVeto = False
    theTool.CutHWMET = False
    theTool.CutHWZVeto = False
    theTool.hwZVetoMassMin    =  -1 #75000
    theTool.hwZVetoMassMax    = -1 #105000
    theTool.CutHWInvMass = False
    theTool.hwInvMassMin    =  -1 
    theTool.hwInvMassMax    = -1 
    theTool.CutHWDeltaR = False
    theTool.hwDeltaRMax = -1
    theTool.CutFlavor = False
    theTool.eeeFlavor = True
    theTool.mmmFlavor = True
    theTool.mmeFlavor = True
    theTool.meeFlavor = True
    #theTool.CutHWChargeSum = True
    theTool.CutHWChargeSum = False
    theTool.CutThreeLepMtMin = False
    pass
##########################################
def EventSelectorToolConfig_Baseline_Preselection_InclusiveLeptonMultiplicity(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutMultiLeptonsExclusive = False
    theTool.CutMultiLeptonsInclusive = True
    pass
##########################################
#4lepton selection:
def EventSelectorToolConfig_Baseline_PreselectionQuadrilepton(theTool) :
    theTool = GetTool(theTool)
    theTool.CutTruthFilter = True
    theTool.CutTrigger = True
    theTool.CutStreamOverlap = True
    theTool.includeEMuTrigger = True
    theTool.includeEETrigger = True
    theTool.includeMuMuTrigger = True
    theTool.CutNPV = True
    theTool.nPVMin = 1
    theTool.CutJetCleaning = True
    theTool.CutHotTile = True
    theTool.CutFCal = True
    theTool.CutLArError = True
    theTool.CutZTagAndProbe  = False
    theTool.CutZPlusJetsTagAndProbe  = False
    theTool.CutZPlusGammaTagAndProbe  = False
    theTool.CutFakeTagAndProbe = False
    theTool.CutFakeTagAndProbeInclusiveSign = False
    theTool.CutDilepton = False
    theTool.CutOppositeCharge = False
    theTool.CutFakeCharge = -1
    theTool.CutTriggerMatching = True
    theTool.CutMultiLeptonsExclusive = True
    theTool.CutLeptonMultiplictyFlavorQuality = False
    theTool.nLooseNotTightMuonsCut = -1
    theTool.nLooseNotTightElectronsCut = -1
    theTool.nLooseMuonsCut = -1
    theTool.nLooseElectronsCut = -1
    theTool.nTightMuonsCut = -1
    theTool.nTightElectronsCut = -1
    theTool.CutLooseDilepton= False
    theTool.looseDileptonSameFlavor  = False
    theTool.nLeptonsCut=4
    theTool.CutNTau = False
    theTool.nTau = 0
    theTool.CutThreeLeptonPt = True
    theTool.CutThreeLeptonPtFirst = True
    theTool.CutThreeLeptonPtSecond = True
    theTool.CutThreeLeptonPtThird = True
    theTool.CutThreeLeptonPtFourth = True
    theTool.lep1PtMin = 25000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 10000
    theTool.lep4PtMin = 10000
    theTool.CutmetMin = False
    theTool.CutmetMinFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutmetMinThird = False
    theTool.useSTVFMetMin = True
    theTool.metMin    = 25000
    theTool.CutZVeto = False
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.zVetoMassMin    =  75000
    theTool.zVetoMassMax    = 105000
    theTool.CutbTagVeto = False
    theTool.CutbTagVeto = False
    theTool.CutPairType  = False
    theTool.reqSFOS  = 0 #False
    theTool.reqSFSS  = 0 #False
    theTool.reqOFOS  = 0 #False
    theTool.reqOFSS  = 0 #False
    theTool.CutNJet = False
    theTool.nJetMax = -1
    theTool.CutDeltaPhi = False
    theTool.DeltaPhiLowEdge = -1
    theTool.DeltaPhiHighEdge = -1
    theTool.CutTopVeto = False
    theTool.CutHWMET = False
    theTool.CutHWZVeto = False
    theTool.hwZVetoMassMin    =  -1 #75000
    theTool.hwZVetoMassMax    = -1 #105000
    theTool.CutHWInvMass = False
    theTool.hwInvMassMin    =  -1 
    theTool.hwInvMassMax    = -1 
    theTool.CutHWDeltaR = False
    theTool.hwDeltaRMax = -1
    theTool.CutFlavor = False
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    #theTool.CutHWChargeSum = True
    theTool.CutHWChargeSum = False
    #Dilepton specific stuffs:
    theTool.CutSameFlavour = False
    theTool.CutOppositeSign = False
    theTool.CutDiLepFlavour = False
    theTool.CutDiLepInvMass = False
    theTool.CutSumPtObject = False
    theTool.CutCosDphi = False
    theTool.CutTransversMass = False
    theTool.CutFakeLeptons = False
    #Define Dilepton cuts values:
    theTool.nMuon = 0
    theTool.zVetoMassMin    =  75000
    theTool.zVetoMassMax    = 105000
    theTool.isSameFlavour = False
    theTool.isOppositeSign = False
    theTool.SumHPTO = 150000
    theTool.SumCosDphi = -0.7
    theTool.TransversMass = 50000
    theTool.nFakeLeptons = -1
    #4lepton specific stuffs:
    theTool.Cut4LepOppositeSign = True
    theTool.Cut4LepFlavour = True
    theTool.Cut4LepInvMass = True
    theTool.Mass12Min=66000
    theTool.Mass12Max=116000
    theTool.Mass34Min=66000
    theTool.Mass34Max=116000
    theTool.CutThreeLepMtMin = False
    pass
##########################################
##########################################
#Dilepton selection:
def EventSelectorToolConfig_Baseline_PreselectionDilepton(theTool) :
    theTool = GetTool(theTool)
    theTool.CutTruthFilter = True
    theTool.CutTrigger = True
    theTool.CutStreamOverlap = True
    theTool.includeEMuTrigger = True
    theTool.includeEETrigger = True
    theTool.includeMuMuTrigger = True
    theTool.CutZTagAndProbe  = False
    theTool.CutZPlusJetsTagAndProbe  = False
    theTool.CutZPlusGammaTagAndProbe  = False
    theTool.CutFakeTagAndProbe = False
    theTool.CutFakeTagAndProbeInclusiveSign = False
    theTool.CutNPV = True
    theTool.nPVMin = 1
    theTool.CutJetCleaning = True
    theTool.CutHotTile = True
    theTool.CutFCal = True
    theTool.CutLArError = True
    theTool.CutDilepton = False
    theTool.CutOppositeCharge = False
    theTool.CutFakeCharge = -1
    theTool.CutTriggerMatching = True
    theTool.CutMultiLeptonsExclusive = True
    theTool.CutLeptonMultiplictyFlavorQuality = False
    theTool.nLooseNotTightMuonsCut = -1
    theTool.nLooseNotTightElectronsCut = -1
    theTool.nLooseMuonsCut = -1
    theTool.nLooseElectronsCut = -1
    theTool.nTightMuonsCut = -1
    theTool.nTightElectronsCut = -1
    theTool.CutLooseDilepton= False
    theTool.looseDileptonSameFlavor  = False
    theTool.nLeptonsCut=2
    theTool.CutNTau = False
    theTool.nTau = 0
    theTool.CutPairType  = False
    theTool.reqSFOS  = 0 #False
    theTool.reqSFSS  = 0 #False
    theTool.reqOFOS  = 0 #False
    theTool.reqOFSS  = 0 #False
    theTool.CutNJet = False
    theTool.nJetMax = -1
    theTool.CutDeltaPhi = False
    theTool.DeltaPhiLowEdge = -1
    theTool.DeltaPhiHighEdge = -1
    theTool.CutTopVeto = False
    theTool.CutHWMET = False
    theTool.CutHWZVeto = False
    theTool.hwZVetoMassMin    =  -1 #75000
    theTool.hwZVetoMassMax    = -1 #105000
    theTool.CutHWInvMass = False
    theTool.hwInvMassMin    =  -1 
    theTool.hwInvMassMax    = -1 
    theTool.CutHWDeltaR = False
    theTool.hwDeltaRMax = -1
    theTool.CutFlavor = False
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    #theTool.CutHWChargeSum = True
    theTool.CutHWChargeSum = False
    #4lepton specific stuffs:
    theTool.Cut4LepOppositeSign = False
    theTool.Cut4LepFlavour = False
    theTool.Cut4LepInvMass = False
    theTool.Mass12Min=66000
    theTool.Mass12Max=116000
    theTool.Mass34Min=66000
    theTool.Mass34Max=116000
    theTool.CutThreeLepMtMin = False
    pass
def EventSelectorToolConfig_Baseline_PreselectionDilepton_Ztautau(theTool) :
    EventSelectorToolConfig_Baseline_PreselectionDilepton(theTool)
    theTool.CutThreeLeptonPt = True
    theTool.CutThreeLeptonPtFirst = True
    theTool.CutThreeLeptonPtSecond = True
    theTool.CutThreeLeptonPtThird = False
    theTool.lep1PtMin = 25000
    theTool.lep2PtMin = 25000
    theTool.lep3PtMin = 20000
    theTool.CutmetMin = False
    theTool.CutmetMinFirst = False
    theTool.CutZTagAndProbe  = False
    theTool.CutZPlusJetsTagAndProbe  = False
    theTool.CutZPlusGammaTagAndProbe  = False
    theTool.CutFakeTagAndProbe = False
    theTool.CutFakeTagAndProbeInclusiveSign = False
    theTool.CutmetMinSecond = False
    theTool.CutmetMinThird = False
    theTool.useSTVFMetMin = True
    theTool.metMin    = 25000
    theTool.CutZVeto = False
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.CutbTagVeto = True
    theTool.CutInvbTagVeto = False
    #Dilepton specific stuffs:
    theTool.CutSameFlavour = False
    theTool.CutOppositeSign = True
    theTool.CutDiLepFlavour = True
    theTool.CutDiLepInvMass = True
    theTool.CutSumPtObject = True
    theTool.CutCosDphi = True
    theTool.CutTransversMass = False
    theTool.CutFakeLeptons = False
    theTool.nMuon = 1
    theTool.zVetoMassMin    =  40000
    theTool.zVetoMassMax    = 80000
    theTool.isSameFlavour = False
    theTool.isOppositeSign = True
    theTool.SumHPTO = 150000
    theTool.SumCosDphi = -0.7
    theTool.TransversMass = 50000
    theTool.nFakeLeptons = 1
    pass
def EventSelectorToolConfig_Baseline_PreselectionDilepton_Zee(theTool) :
    EventSelectorToolConfig_Baseline_PreselectionDilepton(theTool)
    theTool.CutThreeLeptonPt = True
    theTool.CutThreeLeptonPtFirst = True
    theTool.CutThreeLeptonPtSecond = True
    theTool.CutThreeLeptonPtThird = False
    theTool.lep1PtMin = 25000
    theTool.lep2PtMin = 20000
    theTool.lep3PtMin = 20000
    theTool.CutmetMin = True
    theTool.CutmetMinFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutmetMinThird = False
    theTool.useSTVFMetMin = True
    theTool.metMin    = -30000 #if metMin<0 will make the cut MET<abs(MetMin)
    theTool.CutZVeto = False
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.CutbTagVeto = True
    theTool.CutInvbTagVeto = False
    #Dilepton specific stuffs:
    theTool.CutSameFlavour = True
    theTool.CutOppositeSign = True
    theTool.CutDiLepFlavour = True
    theTool.CutDiLepInvMass = True
    theTool.CutSumPtObject = False
    theTool.CutCosDphi = False
    theTool.CutTransversMass = False
    theTool.CutFakeLeptons = False
    theTool.nMuon = 0
    theTool.zVetoMassMin    =  66000
    theTool.zVetoMassMax    = 116000
    theTool.isSameFlavour = True
    theTool.isOppositeSign = True
    theTool.SumHPTO = 150000
    theTool.SumCosDphi = -0.7
    theTool.TransversMass = 50000
    theTool.nFakeLeptons = 1
    pass
def EventSelectorToolConfig_Baseline_PreselectionDilepton_Zmumu(theTool) :
    EventSelectorToolConfig_Baseline_PreselectionDilepton(theTool)
    theTool.CutThreeLeptonPt = True
    theTool.CutThreeLeptonPtFirst = True
    theTool.CutThreeLeptonPtSecond = True
    theTool.CutThreeLeptonPtThird = False
    theTool.lep1PtMin = 25000
    theTool.lep2PtMin = 20000
    theTool.lep3PtMin = 20000
    theTool.CutmetMin = True
    theTool.CutmetMinFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutmetMinThird = False
    theTool.useSTVFMetMin = True
    theTool.metMin    = -30000 #if metMin<0 will make the cut MET<abs(MetMin)
    theTool.CutZVeto = False
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.CutbTagVeto = True
    theTool.CutInvbTagVeto = False
    #Dilepton specific stuffs:
    theTool.CutSameFlavour = True
    theTool.CutOppositeSign = True
    theTool.CutDiLepFlavour = True
    theTool.CutDiLepInvMass = True
    theTool.CutSumPtObject = False
    theTool.CutCosDphi = False
    theTool.CutTransversMass = False
    theTool.CutFakeLeptons = False
    theTool.nMuon = 2
    theTool.zVetoMassMin    =  66000
    theTool.zVetoMassMax    = 116000
    theTool.isSameFlavour = True
    theTool.isOppositeSign = True
    theTool.SumHPTO = 150000
    theTool.SumCosDphi = -0.7
    theTool.TransversMass = 50000
    theTool.nFakeLeptons = 1
    pass
def EventSelectorToolConfig_Baseline_PreselectionDilepton_top(theTool) :
    EventSelectorToolConfig_Baseline_PreselectionDilepton(theTool)
    theTool.CutThreeLeptonPt = True
    theTool.CutThreeLeptonPtFirst = True
    theTool.CutThreeLeptonPtSecond = True
    theTool.CutThreeLeptonPtThird = False
    theTool.lep1PtMin = 35000
    theTool.lep2PtMin = 30000
    theTool.lep3PtMin = 20000
    theTool.CutmetMin = False
    theTool.CutmetMinFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutmetMinThird = False
    theTool.useSTVFMetMin = True
    theTool.metMin    = 25000
    theTool.CutZVeto = False
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.CutbTagVeto = False
    theTool.CutInvbTagVeto = True
    #Dilepton specific stuffs:
    theTool.CutSameFlavour = False
    theTool.CutOppositeSign = True
    theTool.CutDiLepFlavour = True
    theTool.CutDiLepInvMass = True
    theTool.CutSumPtObject = False
    theTool.CutCosDphi = False
    theTool.CutTransversMass = False
    theTool.CutFakeLeptons = False
    theTool.nMuon = 1
    theTool.zVetoMassMin    =  100000
    theTool.zVetoMassMax    = 8000000
    theTool.isSameFlavour = False
    theTool.isOppositeSign = True
    theTool.SumHPTO = 150000
    theTool.SumCosDphi = -0.7
    theTool.TransversMass = 50000
    theTool.nFakeLeptons = 1
    pass
def EventSelectorToolConfig_Baseline_PreselectionDilepton_Fakes(theTool) :
    EventSelectorToolConfig_Baseline_PreselectionDilepton(theTool)
    theTool.CutThreeLeptonPt = True
    theTool.CutThreeLeptonPtFirst = True
    theTool.CutThreeLeptonPtSecond = True
    theTool.CutThreeLeptonPtThird = False
    theTool.lep1PtMin = 25000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutmetMin = False
    theTool.CutmetMinFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutmetMinThird = False
    theTool.useSTVFMetMin = True
    theTool.metMin    = 0
    theTool.CutZVeto = False
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.CutbTagVeto = False
    theTool.CutInvbTagVeto = False
    #Dilepton specific stuffs:
    theTool.CutSameFlavour = True
    theTool.CutOppositeSign = True
    theTool.CutDiLepFlavour = True
    theTool.CutDiLepInvMass = True
    theTool.CutSumPtObject = False
    theTool.CutCosDphi = False
    theTool.CutTransversMass = False
    theTool.CutFakeLeptons = True
    theTool.nMuon = -1
    theTool.zVetoMassMin    =  000000
    theTool.zVetoMassMax    = 8000000
    theTool.isSameFlavour = False
    theTool.isOppositeSign = True
    theTool.SumHPTO = 150000
    theTool.SumCosDphi = -0.7
    theTool.TransversMass = 50000
    theTool.nFakeLeptons = 1
    pass
##########################################
def EventSelectorToolConfig_Baseline_Preselection_0Muons(theTool) :
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutFlavor  = True
    theTool.eeeFlavor = True
    theTool.mmmFlavor = False
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    pass
def EventSelectorToolConfig_Baseline_Preselection_1Muons(theTool) :
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutFlavor  = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = False
    theTool.meeFlavor = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_2Muons(theTool) :
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutFlavor  = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = True
    theTool.meeFlavor = False
    pass
def EventSelectorToolConfig_Baseline_Preselection_3Muons(theTool) :
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutFlavor  = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = True
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    pass

def EventSelectorToolConfig_Baseline_Preselection_Scan_PtMetMt(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    if nSFOS==0:
    	    theTool.CutPairType  = True
    	    theTool.reqSFOS = -1 
    	    theTool.CutFlavor = True
	    theTool.eeeFlavor = True
	    theTool.mmmFlavor = True
	    theTool.mmeFlavor = True
	    theTool.meeFlavor = True
    elif nSFOS==1:
    	    theTool.CutPairType  = True
    	    theTool.reqSFOS = 1
    	    theTool.CutFlavor = True
	    theTool.eeeFlavor = False
	    theTool.mmmFlavor = False
	    theTool.mmeFlavor = True
	    theTool.meeFlavor = True
    elif nSFOS==2:
    	    theTool.CutPairType  = True
    	    theTool.reqSFOS = 1
    	    theTool.CutFlavor = True
	    theTool.eeeFlavor = True
	    theTool.mmmFlavor = True
	    theTool.mmeFlavor = False
	    theTool.meeFlavor = False
    	
    theTool.CutThreeLeptonPtFirst = True
    theTool.lep1PtMin = float(pt1)*1000
    theTool.lep2PtMin = float(pt2)*1000
    theTool.lep3PtMin = float(pt3)*1000
    theTool.CutmetMinSecond = True
    theTool.metMin    = float(met)*1000
    theTool.CutMtMinThird = True
    theTool.lep1MtMin = float(mt1)*1000
    theTool.lep2MtMin = float(mt2)*1000
    theTool.lep3MtMin = float(mt3)*1000
    print theTool.lep1PtMin, theTool.lep2PtMin, theTool.lep3PtMin, theTool.lep1MtMin, theTool.lep2MtMin, theTool.lep3MtMin, theTool.metMin
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMetMt(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutThreeLeptonPtFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutMtMinThird = False
    theTool.CutThreeLeptonPtFirst = True
    theTool.CutMtMinSecond = True
    theTool.CutmetMinThird = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetBVeto(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetZVeto(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutZVeto = True
    theTool.zVetoMassMin    =  75000
    theTool.zVetoMassMax    = 105000
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetZVetoScan(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutZVeto = True
    theTool.zVetoMassMin    =  90000  - zwindow*1000
    theTool.zVetoMassMax    =  90000  + zwindow*1000
    pass
def EventSelectorToolConfig_Baseline_Preselection_FakeTagAndProbe_SameSign(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutMultiLeptonsExclusive = False
    theTool.CutMultiLeptonsInclusive = False
    theTool.CutTriggerMatching = False
    #no flavor reqs on Tag and Probe
    #theTool.CutLooseDilepton= True
    #theTool.looseDileptonSameFlavor  = False
    theTool.CutFakeTagAndProbe = True
    #cut on tight lepton mt
    #theTool.CutMtMin = True
    #theTool.lep1MtMin = float(40000)
    #theTool.lep2MtMin = float(0)
    #theTool.lep3MtMin = float(0)
    #theTool.CutmetMin = True
    #theTool.useSTVFMetMin = True
    #theTool.metMin    = 25000
    #theTool.CutbTagVeto = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_FakeTagAndProbe_InclusiveSign(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutMultiLeptonsExclusive = False
    theTool.CutMultiLeptonsInclusive = False
    theTool.CutTriggerMatching = False
    #no flavor reqs on Tag and Probe
    #theTool.CutLooseDilepton= True
    #theTool.looseDileptonSameFlavor  = False
    theTool.CutFakeTagAndProbeInclusiveSign = True
    #cut on tight lepton mt
    #theTool.CutMtMin = True
    #theTool.lep1MtMin = float(40000)
    #theTool.lep2MtMin = float(0)
    #theTool.lep3MtMin = float(0)
    #theTool.CutmetMin = True
    #theTool.useSTVFMetMin = True
    #theTool.metMin    = 25000
    #theTool.CutbTagVeto = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_FakeRates(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutMultiLeptonsExclusive = False
    theTool.CutMultiLeptonsInclusive = False
    theTool.CutTriggerMatching = False
    theTool.CutLooseDilepton= True
    theTool.looseDileptonSameFlavor  = False
    theTool.CutFakeTagAndProbe = True
    #cut on tight lepton mt
    #theTool.CutMtMin = True
    #theTool.lep1MtMin = float(40000)
    #theTool.lep2MtMin = float(0)
    #theTool.lep3MtMin = float(0)
    #theTool.CutmetMin = True
    #theTool.useSTVFMetMin = True
    #theTool.metMin    = 25000
    #theTool.CutbTagVeto = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_ZPlusJetsTagAndProbe(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutMultiLeptonsExclusive = False
    theTool.CutMultiLeptonsInclusive = False
    theTool.CutTriggerMatching = False
    theTool.CutZPlusJetsTagAndProbe = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_ZPlusGammaTagAndProbe(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutMultiLeptonsExclusive = False
    theTool.CutMultiLeptonsInclusive = False
    theTool.CutTriggerMatching = False
    theTool.CutZPlusGammaTagAndProbe = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_FakeRates_SameFlavor(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutMultiLeptonsExclusive = False
    theTool.CutMultiLeptonsInclusive = False
    theTool.CutTriggerMatching = False
    theTool.CutLooseDilepton= True
    theTool.looseDileptonSameFlavor  = True
    theTool.CutFakeTagAndProbe = True
    #cut on tight lepton mt
    #theTool.CutMtMin = True
    #theTool.lep1MtMin = float(40000)
    #theTool.lep2MtMin = float(0)
    #theTool.lep3MtMin = float(0)
    #theTool.CutmetMin = True
    #theTool.useSTVFMetMin = True
    #theTool.metMin    = 25000
    #theTool.CutbTagVeto = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_RealRates(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutMultiLeptonsExclusive = False
    theTool.CutMultiLeptonsInclusive = False
    theTool.CutTriggerMatching = False
    theTool.CutZTagAndProbe = True
    theTool.CutZPlusJetsTagAndProbe  = False
    theTool.CutZPlusGammaTagAndProbe  = False
    pass

def EventSelectorToolConfig_Baseline_Preselection_0SFOS(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    theTool.CutFlavor = True
    theTool.eeeFlavor = True
    theTool.mmmFlavor = True
    theTool.mmeFlavor = True
    theTool.meeFlavor = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_0SFOS_BVeto85(theTool): 
    EventSelectorToolConfig_Baseline_Preselection_0SFOS(theTool)
    theTool.CutbTagVeto = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_1SFOS(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutPairType  = True
    theTool.reqSFOS = 1
    theTool.CutFlavor = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = True
    theTool.meeFlavor = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_1SFOS_BVeto85(theTool): 
    EventSelectorToolConfig_Baseline_Preselection_1SFOS(theTool)
    theTool.CutbTagVeto = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_2SFOS(theTool): 
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutPairType  = True
    theTool.reqSFOS = 1
    theTool.CutFlavor = True
    theTool.eeeFlavor = True
    theTool.mmmFlavor = True
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    pass
def EventSelectorToolConfig_Baseline_Preselection_2SFOS_BVeto85(theTool): 
    EventSelectorToolConfig_Baseline_Preselection_2SFOS(theTool)
    theTool.CutbTagVeto = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_BVeto85_JetLeq1_ZVeto15_NSFOSPtMtMetDPhi(theTool,nSFOS,pt,mt,met,dphi): 
    #enter values in GeV
    if nSFOS==0:   EventSelectorToolConfig_Baseline_Preselection_0SFOS(theTool)
    elif nSFOS==1: EventSelectorToolConfig_Baseline_Preselection_1SFOS(theTool)
    elif nSFOS==2: EventSelectorToolConfig_Baseline_Preselection_2SFOS(theTool)
    theTool.CutbTagVeto = True
    theTool.CutZVeto = True
    zwindow = 15.
    theTool.zVetoMassMin    =  90000  - zwindow*1000
    theTool.zVetoMassMax    =  90000  + zwindow*1000
    theTool.CutThreeLeptonPt = True
    theTool.lep1PtMin = float(pt)*1000
    theTool.lep2PtMin = float(pt)*1000
    theTool.lep3PtMin = float(pt)*1000
    theTool.CutmetMin = True
    theTool.useSTVFMetMin = True
    theTool.metMin    = float(met)*1000
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutThreeLepMtMin = True
    theTool.threeLepMtMin = float(mt)*1000
    theTool.CutDeltaPhi = True
    theTool.DeltaPhiLowEdge = float(dphi)
    pass
def EventSelectorToolConfig_Baseline_Preselection_Optimized0SFOS(theTool): #,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) :
    nSFOS = 0
    pt1 = 20.
    pt2 = 20.
    pt3 = 20.
    mt1=0.
    mt2=0.
    mt3=0.
    met=0.
    zwindow = 15.
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = True
    theTool.CutZVeto = True
    theTool.zVetoMassMin    =  90000  - zwindow*1000
    theTool.zVetoMassMax    =  90000  + zwindow*1000
    pass
def EventSelectorToolConfig_Baseline_Preselection_0SFOS_SameSignZWindowCR(theTool): #,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) :
    nSFOS = 0
    pt1 = 20.
    pt2 = 20.
    pt3 = 20.
    mt1=0.
    mt2=0.
    mt3=0.
    met=0.
    zwindow = 15.
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = True
    theTool.CutZVeto = False
    theTool.CutInvZVeto = True
    theTool.allowZVetoInclusiveSign = True
    theTool.zVetoMassMin    =  91187.6  - zwindow*1000
    theTool.zVetoMassMax    =  91187.6  + zwindow*1000
    pass
def EventSelectorToolConfig_Baseline_Preselection_Optimized1SFOS(theTool): #,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) :
    nSFOS = 1
    pt1 = 20.
    pt2 = 20.
    pt3 = 20.
    mt1=0.
    mt2=0.
    mt3=0.
    met=40.
    zwindow=15.
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = True
    theTool.CutZVeto = True
    theTool.zVetoMassMin    =  90000  - zwindow*1000
    theTool.zVetoMassMax    =  90000  + zwindow*1000
    pass
def EventSelectorToolConfig_Baseline_Preselection_Optimized2SFOS(theTool): #,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) :
    nSFOS = 2
    pt1 = 20.
    pt2 = 20.
    pt3 = 20.
    mt1=0.
    mt2=0.
    mt3=0.
    met=40.
    zwindow=15.
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = True
    theTool.CutZVeto = True
    theTool.zVetoMassMin    =  90000  - zwindow*1000
    theTool.zVetoMassMax    =  90000  + zwindow*1000
    pass
#3lepton CR WZ:
def EventSelectorToolConfig_Baseline_Preselection_WZ(theTool): 
    nSFOS = 1
    pt1 = 30.
    pt2 = 30.
    pt3 = 30.
    mt1=0.
    mt2=0.
    mt3=0.
    met=0.
    zwindow=15.
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = True
    theTool.CutZVeto = False
    theTool.CutInvZVeto = True
    theTool.allowZVetoInclusiveSign = False
    theTool.zVetoMassMin    =  90000  - zwindow*1000
    theTool.zVetoMassMax    =  90000  + zwindow*1000
    pass
def EventSelectorToolConfig_Baseline_Preselection_WZ_Loose(theTool): 
    nSFOS = 1
    pt1 = 20.
    pt2 = 20.
    pt3 = 20.
    mt1=0.
    mt2=0.
    mt3=0.
    met=0.
    zwindow=15.
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = False
    theTool.CutZVeto = False
    theTool.CutInvZVeto = True
    theTool.allowZVetoInclusiveSign = False
    theTool.zVetoMassMin    =  90000  - zwindow*1000
    theTool.zVetoMassMax    =  90000  + zwindow*1000
    pass
def EventSelectorToolConfig_Baseline_Preselection_WZ_2SFOS_Loose(theTool): 
    nSFOS = 2
    pt1 = 20.
    pt2 = 20.
    pt3 = 20.
    mt1=0.
    mt2=0.
    mt3=0.
    met=0.
    zwindow=15.
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = False
    theTool.CutZVeto = False
    theTool.CutInvZVeto = True
    theTool.allowZVetoInclusiveSign = False
    theTool.zVetoMassMin    =  90000  - zwindow*1000
    theTool.zVetoMassMax    =  90000  + zwindow*1000
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetBVetoZVetoScan(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = True
    theTool.CutZVeto = True
    theTool.zVetoMassMin    =  90000  - zwindow*1000
    theTool.zVetoMassMax    =  90000  + zwindow*1000
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetBVetoZVeto(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutbTagVeto = True
    theTool.CutZVeto = True
    theTool.zVetoMassMin    =  75000
    theTool.zVetoMassMax    = 105000
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetDeltaPhi(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutDeltaPhi = True
    theTool.DeltaPhiLowEdge = 1.
    theTool.DeltaPhiHighEdge = 4
    pass

def EventSelectorToolConfig_Baseline_Preselection_Scan_MtPtMet(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMetMt(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutThreeLeptonPtFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutMtMinThird = False
    theTool.CutMtMinFirst = True
    theTool.CutThreeLeptonPtSecond = True
    theTool.CutmetMinThird = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_MtMetPt(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMetMt(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutThreeLeptonPtFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutMtMinThird = False
    theTool.CutMtMinFirst = True
    theTool.CutmetMinSecond = True
    theTool.CutThreeLeptonPtThird = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_MetPtMt(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMetMt(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutThreeLeptonPtFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutMtMinThird = False
    theTool.CutmetMinFirst = True
    theTool.CutThreeLeptonPtSecond = True
    theTool.CutMtMinFirstThird = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_Scan_MetMtPt(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMetMt(theTool,nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met)
    theTool.CutThreeLeptonPtFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutMtMinThird = False
    theTool.CutmetMinFirst = True
    theTool.CutMtMinFirstSecond = True
    theTool.CutThreeLeptonPtThird = True
    pass
def EventSelectorToolConfig_Baseline_Preselection_ZControlRegion(theTool) :
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutInvZVeto = True
    theTool.allowZVetoInclusiveSign = False
    theTool.CutZVeto = False
    theTool.zVetoMassMin    =  75000
    theTool.zVetoMassMax    = 105000
    pass
def EventSelectorToolConfig_Baseline_Preselection_TopControlRegion(theTool) :
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutInvbTagVeto = True
    theTool.allowZVetoInclusiveSign = False
    pass
def EventSelectorToolConfig_Baseline_Preselection_SignalRegion(theTool) :
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutZVeto = True
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.zVetoMassMin    =  75000
    theTool.zVetoMassMax    = 105000
    pass
def EventSelectorToolConfig_Baseline_Preselection_NoTruthFilter(theTool) :
    EventSelectorToolConfig_Baseline_Preselection(theTool)
    theTool.CutTruthFilter = False
    pass
def EventSelectorToolConfig_Baseline_Preselection_TopControlRegion_NoTruthFilter(theTool) :
    EventSelectorToolConfig_Baseline_Preselection_TopControlRegion(theTool)
    theTool.CutTruthFilter = False
    pass
def EventSelectorToolConfig_Baseline_Preselection_ZControlRegion_NoTruthFilter(theTool) :
    EventSelectorToolConfig_Baseline_Preselection_ZControlRegion(theTool)
    theTool.CutTruthFilter = False
    pass
def EventSelectorToolConfig_Baseline_Preselection_SignalRegion_NoTruthFilter(theTool) :
    EventSelectorToolConfig_Baseline_Preselection_SignalRegion(theTool)
    theTool.CutTruthFilter = False
    pass

def EventSelectorToolConfig_Baseline(theTool) :
    theTool = GetTool(theTool)
    theTool.CutTruthFilter = True
    theTool.CutTrigger = True
    theTool.CutStreamOverlap = True
    theTool.includeEMuTrigger = True
    theTool.includeEETrigger = True
    theTool.includeMuMuTrigger = True
    theTool.CutNPV = True
    theTool.nPVMin = 1
    theTool.CutJetCleaning = True
    theTool.CutHotTile = True
    theTool.CutFCal = True
    theTool.CutLArError = True
    theTool.CutDilepton = True
    theTool.CutOppositeCharge = True
    theTool.CutZTagAndProbe  = False
    theTool.CutZPlusJetsTagAndProbe  = False
    theTool.CutZPlusGammaTagAndProbe  = False
    theTool.CutFakeTagAndProbe = False
    theTool.CutFakeTagAndProbeInclusiveSign = False
    theTool.CutFakeCharge = -1
    theTool.nMuon = -1
    theTool.CutTriggerMatching = True
    theTool.CutMultiLeptonsExclusive = True
    theTool.CutLeptonMultiplictyFlavorQuality = False
    theTool.nLooseNotTightMuonsCut = -1
    theTool.nLooseNotTightElectronsCut = -1
    theTool.nLooseMuonsCut = -1
    theTool.nLooseElectronsCut = -1
    theTool.nTightMuonsCut = -1
    theTool.nTightElectronsCut = -1
    theTool.CutLooseDilepton= False
    theTool.looseDileptonSameFlavor  = False
    theTool.nLeptonsCut=3
    theTool.CutNTau = True
    theTool.nTau = 0
    theTool.CutThreeLeptonPt = True
    theTool.CutThreeLeptonPtFirst = False
    theTool.CutThreeLeptonPtSecond = False
    theTool.CutThreeLeptonPtThird = False
    theTool.lep1PtMin = 25000
    theTool.lep2PtMin = 20000
    theTool.lep3PtMin = 20000
    theTool.CutmetMin = True
    theTool.CutmetMinFirst = False
    theTool.CutmetMinSecond = False
    theTool.CutmetMinThird = False
    theTool.useSTVFMetMin = True
    theTool.metMin    = 25000
    theTool.CutZVeto = True
    theTool.CutInvZVeto = False
    theTool.allowZVetoInclusiveSign = False
    theTool.zVetoMassMin    =  75000
    theTool.zVetoMassMax    = 105000
    theTool.CutPairType  = False
    theTool.reqSFOS  = 0 #False
    theTool.reqSFSS  = 0 #False
    theTool.reqOFOS  = 0 #False
    theTool.reqOFSS  = 0 #False
    theTool.CutNJet = False
    theTool.nJetMax = -1
    theTool.CutDeltaPhi = False
    theTool.DeltaPhiLowEdge = -1
    theTool.DeltaPhiHighEdge = -1
    theTool.CutTopVeto = False
    theTool.CutHWMET = False
    theTool.CutHWZVeto = False
    theTool.hwZVetoMassMin    =  -1 #75000
    theTool.hwZVetoMassMax    = -1 #105000
    theTool.CutHWInvMass = False
    theTool.hwInvMassMin    =  -1 
    theTool.hwInvMassMax    = -1 
    theTool.CutHWDeltaR = False
    theTool.hwDeltaRMax = -1
    theTool.CutFlavor = False
    theTool.eeeFlavor = True
    theTool.mmmFlavor = True
    theTool.mmeFlavor = True
    theTool.meeFlavor = True
    theTool.CutHWChargeSum = False
    pass

def EventSelectorToolConfig_Baseline_SFOS(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.CutPairType  = True
    theTool.reqSFOS = 1 
    pass
def EventSelectorToolConfig_Baseline_NoSFOS(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    pass

def EventSelectorToolConfig_Baseline_SFOS_STVF(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.CutPairType  = True
    theTool.reqSFOS = 1 
    theTool.useSTVFMetMin = True
    pass
def EventSelectorToolConfig_Baseline_NoSFOS_STVF(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    theTool.useSTVFMetMin = True
    pass

def EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = 1 
    pass
def EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    pass

def EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = 1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    pass

def EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    pass

def EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = 1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    pass

def EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    pass

def EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = 1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    theTool.CutHWMET = True
    theTool.hwMETSTVFMin = 30000
    pass

def EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    theTool.CutHWMET = False #no MET cut in SR3
    pass

def EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = 1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    theTool.CutHWMET = True
    theTool.hwMETSTVFMin = 30000
    theTool.CutHWZVeto = True
    theTool.hwZVetoMassMin    =  65000
    theTool.hwZVetoMassMax    = 115000
    pass

def EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    theTool.CutHWMET = False #no MET cut in SR3
    theTool.CutHWZVeto = False #no z veto in SR3
    theTool.hwZVetoMassMin    =  65000
    theTool.hwZVetoMassMax    = 115000
    pass

def EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = 1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    theTool.CutHWMET = True
    theTool.hwMETSTVFMin = 30000
    theTool.CutHWZVeto = True
    theTool.hwZVetoMassMin    =  65000
    theTool.hwZVetoMassMax    = 115000
    theTool.CutHWInvMass = True
    theTool.hwInvMassMin    =  12000
    theTool.hwInvMassMax    = 200000
    pass

def EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto_InvMass(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    theTool.CutHWMET = False #no MET cut in SR3
    theTool.CutHWZVeto = False
    theTool.hwZVetoMassMin    =  65000
    theTool.hwZVetoMassMax    = 115000
    theTool.CutHWInvMass = True
    theTool.hwInvMassMin    =  6000
    theTool.hwInvMassMax    = 200000
    pass

def EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = 1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    theTool.CutHWMET = True
    theTool.hwMETSTVFMin = 30000
    theTool.CutHWZVeto = True
    theTool.hwZVetoMassMin    =  65000
    theTool.hwZVetoMassMax    = 115000
    theTool.CutHWInvMass = True
    theTool.hwInvMassMin    =  12000
    theTool.hwInvMassMax    = 200000
    theTool.CutHWDeltaR = True
    theTool.hwDeltaRMax = 2
    pass

def EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.lep1PtMin = 15000
    theTool.lep2PtMin = 15000
    theTool.lep3PtMin = 15000
    theTool.CutZVeto = False
    theTool.CutmetMin = False #use alternate MET Cut
    theTool.CutPairType  = True
    theTool.reqSFOS = -1 
    theTool.CutNJet = True
    theTool.nJetMax = 1
    theTool.CutTopVeto = True
    theTool.CutHWMET = False #no MET cut in SR3
    theTool.CutHWZVeto = False
    theTool.hwZVetoMassMin    =  65000
    theTool.hwZVetoMassMax    = 115000
    theTool.CutHWInvMass = True
    theTool.hwInvMassMin    =  6000
    theTool.hwInvMassMax    = 200000
    theTool.CutHWDeltaR = True
    theTool.hwDeltaRMax = 2
    pass
def EventSelectorToolConfig_Baseline_HW_SR1p2(theTool) :
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR(theTool)
    theTool
    pass
def EventSelectorToolConfig_Baseline_HW_SR1(theTool) :
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = True
    theTool.mmmFlavor = True
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    pass
def EventSelectorToolConfig_Baseline_HW_SR2(theTool) :
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = True
    theTool.meeFlavor = True
    pass
def EventSelectorToolConfig_Baseline_HW_SR3(theTool) :
    EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = True
    theTool.mmmFlavor = True
    theTool.mmeFlavor = True
    theTool.meeFlavor = True
    pass
def EventSelectorToolConfig_Baseline_HW_SR1p2_Alt(theTool) :
    EventSelectorToolConfig_Baseline_HW_SR1p2(theTool)
    theTool.CutHWChargeSum = True
    theTool
    pass
def EventSelectorToolConfig_Baseline_HW_SR1_Alt(theTool) :
    EventSelectorToolConfig_Baseline_HW_SR1(theTool)
    theTool.CutHWChargeSum = True
    pass
def EventSelectorToolConfig_Baseline_HW_SR2_Alt(theTool) :
    EventSelectorToolConfig_Baseline_HW_SR2(theTool)
    theTool.CutHWChargeSum = True
    pass
def EventSelectorToolConfig_Baseline_HW_SR3_Alt(theTool) :
    EventSelectorToolConfig_Baseline_HW_SR3(theTool)
    theTool.CutHWChargeSum = True
    pass
def EventSelectorToolConfig_Baseline_SFOS_mmm(theTool) :
    EventSelectorToolConfig_Baseline_SFOS(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = True
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    pass

def EventSelectorToolConfig_Baseline_SFOS_mme(theTool) :
    EventSelectorToolConfig_Baseline_SFOS(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = True
    theTool.meeFlavor = False
    pass
def EventSelectorToolConfig_Baseline_SFOS_mee(theTool) :
    EventSelectorToolConfig_Baseline_SFOS(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = False
    theTool.meeFlavor = True
    pass
def EventSelectorToolConfig_Baseline_SFOS_eee(theTool) :
    EventSelectorToolConfig_Baseline_SFOS(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = True
    theTool.mmmFlavor = False
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    pass

def EventSelectorToolConfig_Baseline_NoSFOS_mmm(theTool) :
    EventSelectorToolConfig_Baseline_NoSFOS(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = True
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    pass

def EventSelectorToolConfig_Baseline_NoSFOS_mme(theTool) :
    EventSelectorToolConfig_Baseline_NoSFOS(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = True
    theTool.meeFlavor = False
    pass
def EventSelectorToolConfig_Baseline_NoSFOS_mee(theTool) :
    EventSelectorToolConfig_Baseline_NoSFOS(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = False
    theTool.mmmFlavor = False
    theTool.mmeFlavor = False
    theTool.meeFlavor = True
    pass
def EventSelectorToolConfig_Baseline_NoSFOS_eee(theTool) :
    EventSelectorToolConfig_Baseline_NoSFOS(theTool)
    theTool.CutFlavor = True
    theTool.eeeFlavor = True
    theTool.mmmFlavor = False
    theTool.mmeFlavor = False
    theTool.meeFlavor = False
    pass

def EventSelectorToolConfig_Baseline_SFOS_MinLepPt15(theTool) :
    EventSelectorToolConfig_Baseline_SFOS(theTool)
    theTool.lep3PtMin = 15000
    pass
def EventSelectorToolConfig_Baseline_NoSFOS_MinLepPt15(theTool) :
    EventSelectorToolConfig_Baseline_NoSFOS(theTool)
    theTool.lep3PtMin = 15000
    pass
def EventSelectorToolConfig_Baseline_SFOS_MinLepPt10(theTool) :
    EventSelectorToolConfig_Baseline_SFOS(theTool)
    theTool.lep3PtMin = 10000
    pass
def EventSelectorToolConfig_Baseline_NoSFOS_MinLepPt10(theTool) :
    EventSelectorToolConfig_Baseline_NoSFOS(theTool)
    theTool.lep3PtMin = 10000
    pass
def EventSelectorToolConfig_Baseline_SFOS_MET30(theTool) :
    EventSelectorToolConfig_Baseline_SFOS(theTool)
    theTool.metMin = 30000
    pass
def EventSelectorToolConfig_Baseline_NoSFOS_MET30(theTool) :
    EventSelectorToolConfig_Baseline_NoSFOS(theTool)
    theTool.metMin = 30000
    pass
def EventSelectorToolConfig_Baseline_SFOS_MET35(theTool) :
    EventSelectorToolConfig_Baseline_SFOS(theTool)
    theTool.metMin = 35000
    pass
def EventSelectorToolConfig_Baseline_NoSFOS_MET35(theTool) :
    EventSelectorToolConfig_Baseline_NoSFOS(theTool)
    theTool.metMin = 35000
    pass


def EventSelectorToolConfig_Selection(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.CutllMass = True
    theTool.llMassSFMin = 30000
    theTool.llMassSFMax = 75000
    theTool.llMassDFMin = 30000
    theTool.llMassDFMax = 100000
    theTool.CutsumPtMin = True
    theTool.sumPtMin = 35000
    theTool.CutfirstJetPtMin = True
    theTool.firstJetPtMin = 40000
    theTool.jetJVFMin = 0.5
    theTool.CutmetMin = True
    theTool.metSFMin = 40000
    theTool.metDFMin = 20000
    theTool.CuthptoMetMin = True
    theTool.hptoMetSFMin = 40000
    theTool.hptoMetDFMin = 0
    theTool.Cutx = True
    theTool.xMin = 0.1
    theTool.xMax = 1
    theTool.CutllDeltaPhi = True
    theTool.llDeltaPhiMin = 0.
    theTool.llDeltaPhiMax = 2.5
    pass

def EventSelectorToolConfig_VBFMVA(theTool) :
    EventSelectorToolConfig_Selection(theTool)
    theTool.CutearlybTagVeto = True
    theTool.CutsecondJetPtMin = True
    theTool.secondJetPtMin = 30000
    theTool.CutjjDeltaEta = True
    theTool.jjDeltaEtaMin = 2.2
    pass

def EventSelectorToolConfig_BoostedMVA(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.CutfailedMVAVBF = True
    theTool.CuthiggsPtMin = True
    theTool.higgsPtMin = 100000
    pass

def EventSelectorToolConfig_VHMVA(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.CutfailedMVAVBF = True
    theTool.CutfailedMVABoosted = True
    theTool.CutjjMass = True
    theTool.jjMassMin = 30000
    theTool.jjMassMax = 160000
    pass

def EventSelectorToolConfig_N1JETMVA(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.CutfailedMVAVBF = True
    theTool.CutfailedMVABoosted = True
    theTool.CutfailedMVAVH = True
    pass

def EventSelectorToolConfig_N0JETMVA(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.CutfailedMVAVBF = True
    theTool.CutfailedMVABoosted = True
    theTool.CutfailedMVAVH = True
    pass

def EventSelectorToolConfig_VBF(theTool) :
    EventSelectorToolConfig_Selection(theTool)
    theTool.CutsecondJetPtMin = True
    theTool.secondJetPtMin = 25000
    theTool.CutjjDeltaEta = True
    theTool.jjDeltaEtaMin = 3.0
    theTool.CutjjMass = True
    theTool.jjMassMin = 400000
    theTool.CutbTagVeto = True
    #theTool.bTagVetoMV1Max = 0.795
    #theTool.bTagJetPtMin = 25000
    #theTool.bTagJetEtaMax = 2.5
    theTool.CutCentralJetVeto = True
    theTool.CJVPtMin = 25000
    theTool.CJVEtaMax = 2.4
    theTool.CutLeptonCentrality = True
    pass

def EventSelectorToolConfig_Boosted(theTool) :
    EventSelectorToolConfig_Selection(theTool)
    theTool.CutfailedCutBasedVBF = True
    theTool.CuthiggsPtMin = True
    theTool.higgsPtMin = 100000
    theTool.CutbTagVeto = True
    pass

def EventSelectorToolConfig_VH(theTool) :
    EventSelectorToolConfig_Selection(theTool)
    theTool.CutsecondJetPtMin = True
    theTool.secondJetPtMin = 25000
    theTool.CutfailedCutBasedBoosted = True
    theTool.CutjjDeltaEta = True
    theTool.jjDeltaEtaMax = 2.0 
    theTool.CutjjMass = True
    theTool.jjMassMin = 30000
    theTool.jjMassMax = 160000
    theTool.CutbTagVeto = True
    pass

def EventSelectorToolConfig_N1JET(theTool) :
    EventSelectorToolConfig_Selection(theTool)
    theTool.CutfailedCutBased2JET = True
    theTool.CuthiggsjetMassMin = True
    theTool.higgsjetMassMin = 225000
    theTool.CutbTagVeto = True
    pass

def EventSelectorToolConfig_N0JET(theTool) :
    EventSelectorToolConfig_Baseline(theTool)
    theTool.nMuon = 1
    theTool.CutllMass = True
    theTool.llMassDFMin = 30000
    theTool.llMassDFMax = 100000
    theTool.CutsumPtMin = True
    theTool.sumPtMin = 35000
    theTool.CutllDeltaPhi = True
    theTool.llDeltaPhiMin = 2.5
    theTool.CutbTagVeto = True
    pass


#########################################
## Is this actually used somewhere???
#########################################

def EventSelectorToolConfig_Data(theTool) :
    theTool = GetTool(theTool)
    theTool.nTau = 0
    theTool.nMuon = 1
    theTool.includeEMuTrigger = True
    theTool.cutJetBadLooseMinus = True
    theTool.cutLArError = True
    theTool.nPVMin = 1
    theTool.llMassSFMin = 30000
    theTool.llMassSFMax = 75000
    theTool.llMassDFMin = 30000
    theTool.llMassDFMax = 100000
    theTool.firstJetPtMin = 40000
    theTool.jetJVFMin = 0.5
    theTool.metDFMin = 20000
    pass

#########################################
## Channel by channel
#########################################

def EventSelectorToolConfig_VBF_EE(theTool) :
    EventSelectorToolConfig_VBF(theTool)
    theTool.includeEMuTrigger = False
    theTool.includeMuMuTrigger = False
    theTool.nMuon = 0
    pass

def EventSelectorToolConfig_VBF_EMu(theTool) :
    EventSelectorToolConfig_VBF(theTool)
    theTool.includeEETrigger = False
    theTool.includeMuMuTrigger = False
    theTool.nMuon = 1
    pass

def EventSelectorToolConfig_VBF_MuMu(theTool) :
    EventSelectorToolConfig_VBF(theTool)
    theTool.includeEMuTrigger = False
    theTool.includeEETrigger = False
    theTool.nMuon = 2
    pass

def EventSelectorToolConfig_Boosted_EE(theTool) :
    EventSelectorToolConfig_Boosted(theTool)
    theTool.includeEMuTrigger = False
    theTool.includeMuMuTrigger = False
    theTool.nMuon = 0
    pass

def EventSelectorToolConfig_Boosted_EMu(theTool) :
    EventSelectorToolConfig_Boosted(theTool)
    theTool.includeEETrigger = False
    theTool.includeMuMuTrigger = False
    theTool.nMuon = 1
    pass

def EventSelectorToolConfig_Boosted_MuMu(theTool) :
    EventSelectorToolConfig_Boosted(theTool)
    theTool.includeEMuTrigger = False
    theTool.includeEETrigger = False
    theTool.nMuon = 2
    pass

def EventSelectorToolConfig_VH_EE(theTool) :
    EventSelectorToolConfig_VH(theTool)
    theTool.includeEMuTrigger = False
    theTool.includeMuMuTrigger = False
    theTool.nMuon = 0
    pass

def EventSelectorToolConfig_VH_EMu(theTool) :
    EventSelectorToolConfig_VH(theTool)
    theTool.includeEETrigger = False
    theTool.includeMuMuTrigger = False
    theTool.nMuon = 1
    pass

def EventSelectorToolConfig_VH_MuMu(theTool) :
    EventSelectorToolConfig_VH(theTool)
    theTool.includeEMuTrigger = False
    theTool.includeEETrigger = False
    theTool.nMuon = 2
    pass

def EventSelectorToolConfig_N1JET_EE(theTool) :
    EventSelectorToolConfig_N1JET(theTool)
    theTool.includeEMuTrigger = False
    theTool.includeMuMuTrigger = False
    theTool.nMuon = 0
    pass

def EventSelectorToolConfig_N1JET_EMu(theTool) :
    EventSelectorToolConfig_N1JET(theTool)
    theTool.includeEETrigger = False
    theTool.includeMuMuTrigger = False
    theTool.nMuon = 1
    pass

def EventSelectorToolConfig_N1JET_MuMu(theTool) :
    EventSelectorToolConfig_N1JET(theTool)
    theTool.includeEMuTrigger = False
    theTool.includeEETrigger = False
    theTool.nMuon = 2
    pass

