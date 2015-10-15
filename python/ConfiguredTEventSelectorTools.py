##=============================================================================
## Name:        ConfiguredTEventSelectorTools
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Apply the default configurations for the TEventSelectorTool.
##
## Usage: In your ROOT session (after loading the libraries from RootCore):
##        TPython::LoadMacro("./path/to/this/file/ConfiguredTEventSelectorTools.py");
##        Root::TEventSelectorTool* myLooseTool = (void*)TPython::Eval("ConfiguredTEventSelectorTool_Loose()");
##        myLooseTool->initialize();
##
##=============================================================================

# import the needed Reflex and ROOT stuff
import PyCintex
PyCintex.Cintex.Enable()
import ROOT

# Import the needed stuff specific to the EventSelectorTool
from wwwAnalysis.EventSelectorCutDefs import *

def ConfiguredTEventSelectorTool_Pass():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorPass")
    EventSelectorToolConfig_Pass(tool)
    return tool
###########################
#Define Control Regions selector:
def ConfiguredTEventSelectorTool_Baseline_PreselectionDilepton():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionDilepton")
    EventSelectorToolConfig_Baseline_PreselectionDilepton(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_PreselectionDilepton_Ztautau():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionDileptonZtautau")
    EventSelectorToolConfig_Baseline_PreselectionDilepton_Ztautau(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_PreselectionDilepton_Zee():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionDileptonZee")
    EventSelectorToolConfig_Baseline_PreselectionDilepton_Zee(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_PreselectionDilepton_Zmumu():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionDileptonZmumu")
    EventSelectorToolConfig_Baseline_PreselectionDilepton_Zmumu(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_PreselectionDilepton_top():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionDileptontop")
    EventSelectorToolConfig_Baseline_PreselectionDilepton_top(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_PreselectionDilepton_Fakes():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionDileptonFakes")
    EventSelectorToolConfig_Baseline_PreselectionDilepton_Fakes(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_WZ():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionWZ")
    EventSelectorToolConfig_Baseline_Preselection_WZ(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_WZ_Loose():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionWZLoose")
    EventSelectorToolConfig_Baseline_Preselection_WZ_Loose(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_0SFOS_SameSignZWindowCR(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection0SFOSSameSignZWindowCR")
    EventSelectorToolConfig_Baseline_Preselection_0SFOS_SameSignZWindowCR(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_WZ_2SFOS_Loose():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionWZ2SFOSLoose")
    EventSelectorToolConfig_Baseline_Preselection_WZ_2SFOS_Loose(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_InclusiveLeptonMultiplicity():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionInclusiveLeptonMultiplicity")
    EventSelectorToolConfig_Baseline_Preselection_InclusiveLeptonMultiplicity(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_PreselectionQuadrilepton():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionQuadrilepton")
    EventSelectorToolConfig_Baseline_PreselectionQuadrilepton(tool)
    return tool

##########################
def ConfiguredTEventSelectorTool_Baseline_Preselection_Trigger():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionTrigger")
    EventSelectorToolConfig_Baseline_Preselection_Trigger(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Optimized0SFOS(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionOptimized0SFOS")
    EventSelectorToolConfig_Baseline_Preselection_Optimized0SFOS(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Optimized1SFOS(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionOptimized1SFOS")
    EventSelectorToolConfig_Baseline_Preselection_Optimized1SFOS(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Optimized2SFOS(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionOptimized2SFOS")
    EventSelectorToolConfig_Baseline_Preselection_Optimized2SFOS(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_0SFOS(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection0SFOS")
    EventSelectorToolConfig_Baseline_Preselection_0SFOS(tool)
    return tool

def ConfiguredTEventSelectorTool_Baseline_Preselection_FakeTagAndProbe_SameSign(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorToolConfigBaselinePreselectionFakeTagAndProbeSameSign")
    EventSelectorToolConfig_Baseline_Preselection_FakeTagAndProbe_SameSign(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_FakeTagAndProbe_InclusiveSign(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorToolConfigBaselinePreselectionFakeTagAndProbeInclusiveSign")
    EventSelectorToolConfig_Baseline_Preselection_FakeTagAndProbe_InclusiveSign(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_FakeRates(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorToolConfigBaselinePreselectionFakeRates")
    EventSelectorToolConfig_Baseline_Preselection_FakeRates(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_ZPlusJetsTagAndProbe(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorToolConfigBaselinePreselectionZPlusJetsTagAndProbe")
    EventSelectorToolConfig_Baseline_Preselection_ZPlusJetsTagAndProbe(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_ZPlusGammaTagAndProbe(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorToolConfigBaselinePreselectionZPlusGammaTagAndProbe")
    EventSelectorToolConfig_Baseline_Preselection_ZPlusGammaTagAndProbe(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_FakeRates_SameFlavor(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorToolConfigBaselinePreselectionFakeRatesSameFlavor")
    EventSelectorToolConfig_Baseline_Preselection_FakeRates_SameFlavor(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_RealRates(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorToolConfigBaselinePreselectionRealRatesElectron")
    EventSelectorToolConfig_Baseline_Preselection_RealRates(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_1SFOS(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection1SFOS")
    EventSelectorToolConfig_Baseline_Preselection_1SFOS(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_2SFOS(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection2SFOS")
    EventSelectorToolConfig_Baseline_Preselection_2SFOS(tool)
    return tool

def ConfiguredTEventSelectorTool_Baseline_Preselection_0SFOS_BVeto85(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection0SFOSBVeto85")
    EventSelectorToolConfig_Baseline_Preselection_0SFOS_BVeto85(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_1SFOS_BVeto85(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection1SFOSBVeto85")
    EventSelectorToolConfig_Baseline_Preselection_1SFOS_BVeto85(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_2SFOS_BVeto85(): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection2SFOSBVeto85")
    EventSelectorToolConfig_Baseline_Preselection_2SFOS_BVeto85(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_BVeto85_JetLeq1_ZVeto15_NSFOSPtMtMetDPhi(nSFOS,pt,mt,met,dphi): 
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorToolConfigBaselinePreselectionScanBVeto85JetLeq1ZVeto15NSFOSPtMtMetDPhi")
    EventSelectorToolConfig_Baseline_Preselection_Scan_BVeto85_JetLeq1_ZVeto15_NSFOSPtMtMetDPhi(tool,nSFOS,pt,mt,met,dphi)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection")
    EventSelectorToolConfig_Baseline_Preselection(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Truth():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineTruth")
    EventSelectorToolConfig_Baseline_Truth(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_0Muons():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection0Muons")
    EventSelectorToolConfig_Baseline_Preselection_0Muons(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_1Muons():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection1Muons")
    EventSelectorToolConfig_Baseline_Preselection_1Muons(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_2Muons():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection2Muons")
    EventSelectorToolConfig_Baseline_Preselection_2Muons(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_3Muons():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselection3Muons")
    EventSelectorToolConfig_Baseline_Preselection_3Muons(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_PtMetMt( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanPtMetMt")
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMetMt(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_PtMtMet( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanPtMtMet")
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMet(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_PtMtMetBVeto( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanPtMtMetBVeto")
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetBVeto(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_PtMtMetZVeto( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanPtMtMetZVeto")
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetZVeto(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_PtMtMetZVetoScan( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanPtMtMetZVetoScan")
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetZVetoScan(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_PtMtMetBVetoZVetoScan( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanPtMtMetBVetoZVetoScan")
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetBVetoZVetoScan(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met,zwindow) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_PtMtMetBVetoZVeto( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanPtMtMetBVetoZVeto")
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetBVetoZVeto(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_PtMtMetDeltaPhi( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanPtMtMetBVetoZVetoDeltaPhi")
    EventSelectorToolConfig_Baseline_Preselection_Scan_PtMtMetDeltaPhi(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_MtPtMet( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanMtPtMet")
    EventSelectorToolConfig_Baseline_Preselection_Scan_MtPtMet(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_MtMetPt( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanMtMetPt")
    EventSelectorToolConfig_Baseline_Preselection_Scan_MtMetPt(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_MetPtMt( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanMetPtMt")
    EventSelectorToolConfig_Baseline_Preselection_Scan_MetPtMt(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_Scan_MetMtPt( nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) :
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionScanMetMtPt")
    EventSelectorToolConfig_Baseline_Preselection_Scan_MetMtPt(tool, nSFOS,pt1,pt2,pt3,mt1,mt2,mt3,met) 
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_ZControlRegion():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionZControlRegion")
    EventSelectorToolConfig_Baseline_Preselection_ZControlRegion(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_TopControlRegion():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionTopControlRegion")
    EventSelectorToolConfig_Baseline_Preselection_TopControlRegion(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_SignalRegion():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionSignalRegion")
    EventSelectorToolConfig_Baseline_Preselection_SignalRegion(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_NoTruthFilter():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionNoTruthFilter")
    EventSelectorToolConfig_Baseline_Preselection_NoTruthFilter(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_TopControlRegion_NoTruthFilter():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionTopControlRegionNoTruthFilter")
    EventSelectorToolConfig_Baseline_Preselection_TopControlRegion_NoTruthFilter(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_ZControlRegion_NoTruthFilter():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionZControlRegionNoTruthFilter")
    EventSelectorToolConfig_Baseline_Preselection_ZControlRegion_NoTruthFilter(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_Preselection_SignalRegion_NoTruthFilter():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselinePreselectionSignalRegionNoTruthFilter")
    EventSelectorToolConfig_Baseline_Preselection_SignalRegion_NoTruthFilter(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaseline")
    EventSelectorToolConfig_Baseline(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineSFOS")
    EventSelectorToolConfig_Baseline_SFOS(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS_mmm():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineSFOSmmm")
    EventSelectorToolConfig_Baseline_SFOS_mmm(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS_mme():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineSFOSmme")
    EventSelectorToolConfig_Baseline_SFOS_mme(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS_mee():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineSFOSmee")
    EventSelectorToolConfig_Baseline_SFOS_mee(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS_eee():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineSFOSeee")
    EventSelectorToolConfig_Baseline_SFOS_eee(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOS")
    EventSelectorToolConfig_Baseline_NoSFOS(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS_mmm():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOSmmm")
    EventSelectorToolConfig_Baseline_NoSFOS_mmm(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS_mme():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOSmme")
    EventSelectorToolConfig_Baseline_NoSFOS_mme(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS_mee():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOSmee")
    EventSelectorToolConfig_Baseline_NoSFOS_mee(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS_eee():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOSeee")
    EventSelectorToolConfig_Baseline_NoSFOS_eee(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS_STVF():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineSFOSSTVF")
    EventSelectorToolConfig_Baseline_SFOS_STVF(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS_STVF():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOSSTVF")
    EventSelectorToolConfig_Baseline_NoSFOS_STVF(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR1p2_SFOS():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1p2_SFOS")
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR3_NoSFOS():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR3_NoSFOS")
    EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS(tool)
    return tool

def ConfiguredTEventSelectorTool_Baseline_HW_SR1p2_SFOS_NJet():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1p2_SFOS_NJet")
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR3_NoSFOS_NJet():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR3_NoSFOS_NJet")
    EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR1p2_SFOS_NJet_TopVeto():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1p2_SFOS_NJet_TopVeto")
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR3_NoSFOS_NJet_TopVeto():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR3_NoSFOS_NJet_TopVeto")
    EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1p2_SFOS_NJet_TopVeto_MET")
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR3_NoSFOS_NJet_TopVeto_MET")
    EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto")
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto")
    EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass")
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto_InvMass():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto_InvMass")
    EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto_InvMass(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR")
    EventSelectorToolConfig_Baseline_HW_SR1p2_SFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR")
    EventSelectorToolConfig_Baseline_HW_SR3_NoSFOS_NJet_TopVeto_MET_ZVeto_InvMass_DeltaR(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR1p2():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1p2")
    EventSelectorToolConfig_Baseline_HW_SR1p2(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR1():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1")
    EventSelectorToolConfig_Baseline_HW_SR1(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR2():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR2")
    EventSelectorToolConfig_Baseline_HW_SR2(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR3():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR3")
    EventSelectorToolConfig_Baseline_HW_SR3(tool)
    return tool

def ConfiguredTEventSelectorTool_Baseline_HW_SR1p2_Alt():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1p2_Alt")
    EventSelectorToolConfig_Baseline_HW_SR1p2_Alt(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR1_Alt():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR1_Alt")
    EventSelectorToolConfig_Baseline_HW_SR1_Alt(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR2_Alt():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR2_Alt")
    EventSelectorToolConfig_Baseline_HW_SR2_Alt(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_HW_SR3_Alt():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineHW_SR3_Alt")
    EventSelectorToolConfig_Baseline_HW_SR3_Alt(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS_MinLepPt15():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorPreselectioSFOSMinLepPt15")
    EventSelectorToolConfig_Baseline_SFOS_MinLepPt15(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS_MinLepPt15():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOSMinLepPt15")
    EventSelectorToolConfig_Baseline_NoSFOS_MinLepPt15(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS_MinLepPt10():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineSFOSMinLepPt10")
    EventSelectorToolConfig_Baseline_SFOS_MinLepPt10(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS_MinLepPt10():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOSMinLepPt10")
    EventSelectorToolConfig_Baseline_NoSFOS_MinLepPt10(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS_MET30():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineSFOSMET30")
    EventSelectorToolConfig_Baseline_SFOS_MET30(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS_MET30():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOSMET30")
    EventSelectorToolConfig_Baseline_NoSFOS_MET30(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_SFOS_MET35():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineSFOSMET35")
    EventSelectorToolConfig_Baseline_SFOS_MET35(tool)
    return tool
def ConfiguredTEventSelectorTool_Baseline_NoSFOS_MET35():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBaselineNoSFOSMET35")
    EventSelectorToolConfig_Baseline_NoSFOS_MET35(tool)
    return tool

def ConfiguredTEventSelectorTool_VBFMVA():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVBFMVA")
    EventSelectorToolConfig_VBFMVA(tool)
    return tool
def ConfiguredTEventSelectorTool_BoostedMVA():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBoostedMVA")
    EventSelectorToolConfig_BoostedMVA(tool)
    return tool
def ConfiguredTEventSelectorTool_VHMVA():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVHMVA")
    EventSelectorToolConfig_VHMVA(tool)
    return tool
def ConfiguredTEventSelectorTool_N1JETMVA():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorN1JETMVA")
    EventSelectorToolConfig_N1JETMVA(tool)
    return tool
def ConfiguredTEventSelectorTool_N0JETMVA():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorN0JETMVA")
    EventSelectorToolConfig_N0JETMVA(tool)
    return tool

def ConfiguredTEventSelectorTool_VBF():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVBF")
    EventSelectorToolConfig_VBF(tool)
    return tool
def ConfiguredTEventSelectorTool_Boosted():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBoosted")
    EventSelectorToolConfig_Boosted(tool)
    return tool
def ConfiguredTEventSelectorTool_VH():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVH")
    EventSelectorToolConfig_VH(tool)
    return tool
def ConfiguredTEventSelectorTool_N1JET():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorN1JET")
    EventSelectorToolConfig_N1JET(tool)
    return tool
def ConfiguredTEventSelectorTool_N0JET():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorN0JET")
    EventSelectorToolConfig_N0JET(tool)
    return tool

def ConfiguredTEventSelectorTool_Data():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorData")
    EventSelectorToolConfig_Data(tool)
    return tool
def ConfiguredTEventSelectorTool_VBF_EE():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVBF_EE")
    EventSelectorToolConfig_VBF_EE(tool)
    return tool
def ConfiguredTEventSelectorTool_VBF_EMu():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVBF_EMu")
    EventSelectorToolConfig_VBF_EMu(tool)
    return tool
def ConfiguredTEventSelectorTool_VBF_MuMu():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVBF_MuMu")
    EventSelectorToolConfig_VBF_MuMu(tool)
    return tool
def ConfiguredTEventSelectorTool_Boosted_EE():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBoosted_EE")
    EventSelectorToolConfig_Boosted_EE(tool)
    return tool
def ConfiguredTEventSelectorTool_Boosted_EMu():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBoosted_EMu")
    EventSelectorToolConfig_Boosted_EMu(tool)
    return tool
def ConfiguredTEventSelectorTool_Boosted_MuMu():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorBoosted_MuMu")
    EventSelectorToolConfig_Boosted_MuMu(tool)
    return tool
def ConfiguredTEventSelectorTool_VH_EE():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVH_EE")
    EventSelectorToolConfig_VH_EE(tool)
    return tool
def ConfiguredTEventSelectorTool_VH_EMu():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVH_EMu")
    EventSelectorToolConfig_VH_EMu(tool)
    return tool
def ConfiguredTEventSelectorTool_VH_MuMu():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorVH_MuMu")
    EventSelectorToolConfig_VH_MuMu(tool)
    return tool
def ConfiguredTEventSelectorTool_N1JET_EE():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorN1JET_EE")
    EventSelectorToolConfig_N1JET_EE(tool)
    return tool
def ConfiguredTEventSelectorTool_N1JET_EMu():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorN1JET_EMu")
    EventSelectorToolConfig_N1JET_EMu(tool)
    return tool
def ConfiguredTEventSelectorTool_N1JET_MuMu():
    tool = ROOT.wwwAnalysis.TEventSelectorTool("EventSelectorN1JET_MuMu")
    EventSelectorToolConfig_N1JET_MuMu(tool)
    return tool

