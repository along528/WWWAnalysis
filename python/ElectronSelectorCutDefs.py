##=============================================================================
## Name:        ElectronSelectorCutDefs
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Define the cut values for the ElectronSelectorTools
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



def ElectronSelectorToolConfig_Fake(theTool) :
    """
    This defines the cut values for the Loose operating point.
    """
    theTool = GetTool(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
#    theTool.mediumPP = 1
#    theTool.tightPP = -1
    theTool.loosePP = 1
    theTool.mediumPP = 0
    theTool.tightPP = 0
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    theTool.ptMin = 15000
    theTool.etaMax = 2.47
#    theTool.EtIsoMin = 0.09
#    theTool.EtIsoMax = 0.30
    theTool.PtIsoMin = -100 #0.17
    #use DeltaR = .3
    theTool.ptIsoDeltaR20  = False
#    theTool.PtIsoMax = 0.17
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 10000 #0.5
    pass

def ElectronSelectorToolConfig_LoosePP_InvZ0_InvEtIso_InvPtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = False
    theTool.CutPtIso = False
    theTool.CutZ0 = False
    theTool.loosePP = True #loose quality
    theTool.mediumPP = False 
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass

def ElectronSelectorToolConfig_Loose(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = False
    theTool.CutPtIso = False
    theTool.CutZ0 = False
    theTool.loosePP = False
    theTool.mediumPP = True #medium quality
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass

def ElectronSelectorToolConfig_Loose_InvertedID(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted ID
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = True #medium quality
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass

def ElectronSelectorToolConfig_Loose_InvertedPtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted pt isolation
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = False
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False 
    theTool.tightPP = True #tight quality
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass
def ElectronSelectorToolConfig_Loose_InvertedEtIso_InvertedPtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted pt and et isolation
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = False
    theTool.CutPtIso = False
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False 
    theTool.tightPP = True #tight quality
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass
def ElectronSelectorToolConfig_Loose_InvertedID_InvertedEtIso_InvertedPtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted pt and et isolation and inverted ID
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = False
    theTool.CutPtIso = False
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = True  #medium quality
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass
def ElectronSelectorToolConfig_Loose_InvertedIDLoosepp_InvertedEtIso_InvertedPtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted pt and et isolation and inverted ID
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = False
    theTool.CutPtIso = False
    theTool.CutZ0 = True
    theTool.loosePP = True #loose quality
    theTool.mediumPP = False  
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass
def ElectronSelectorToolConfig_Loose_InvertedIDLoosepp(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted pt and et isolation and inverted ID
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = True #loose quality
    theTool.mediumPP = False  
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass
def ElectronSelectorToolConfig_Loose_InvertedID_InvertedEtIso_InvertedPtIso_Pt20GeV(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted pt and et isolation and inverted ID
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = False
    theTool.CutPtIso = False
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = True  #medium quality
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    theTool.ptMin = 20000
    pass
def ElectronSelectorToolConfig_Loose_InvertedID_InvertedPtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted pt isolation and identification
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = False
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = True #medium quaility 
    theTool.tightPP = False 
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass

def ElectronSelectorToolConfig_Loose_InvertedEtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted et isolation
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = False
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False 
    theTool.tightPP = True #tight quality
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass
def ElectronSelectorToolConfig_Loose_InvertedZ0(theTool) :
    """
    This defines the cut values for the loose matrix-method cuts only inverted z0 sin theta
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = False
    theTool.loosePP = False
    theTool.mediumPP = False 
    theTool.tightPP = True #tight quality
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass

def ElectronSelectorToolConfig_FakeRate_Tight(theTool):
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False 
    theTool.tightPP = True
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass
def ElectronSelectorToolConfig_RealRate_Tight(theTool):
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = True
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    theTool.ptMin = 10000
    pass

def ElectronSelectorToolConfig_Medium(theTool) :
    """
    This defines the cut values for the Medium operating point.
    """
    theTool = GetTool(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = True
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    theTool.ptMin = 10000
    theTool.etaMax = 2.47
    #use DeltaR = .3
    theTool.ptIsoDeltaR20  = False
    theTool.EtIsoMaxHightPt = 0.14
    theTool.EtIsoMaxLowPt = 0.14
    theTool.PtIsoMax = 0.13
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass


def ElectronSelectorToolConfig_Tight(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = True
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    theTool.ptMin = 10000
    #use DeltaR = .3
    theTool.ptIsoDeltaR20  = False
    theTool.etaMax = 2.47
    theTool.EtIsoMaxHighPt = 0.14
    theTool.EtIsoMaxLowPt = 0.14
    theTool.PtIsoMax = 0.13
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass

def ElectronSelectorToolConfig_VeryLooseLL(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = False
    theTool.veryLooseLL = True
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    theTool.ptMin = 10000
    theTool.etaMax = 2.47
    theTool.EtIsoMaxHighPt = 0.14
    theTool.EtIsoMaxLowPt = 0.14
    #use DeltaR = .3
    theTool.ptIsoDeltaR20  = False
    theTool.PtIsoMax = 0.13
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass

def ElectronSelectorToolConfig_LooseLL(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = True
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    theTool.ptMin = 10000
    theTool.etaMax = 2.47
    theTool.EtIsoMaxHighPt = 0.14
    theTool.EtIsoMaxLowPt = 0.14
    #use DeltaR = .3
    theTool.ptIsoDeltaR20  = False
    theTool.PtIsoMax = 0.13
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass

def ElectronSelectorToolConfig_MediumLL(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = True
    theTool.tightLL = False
    theTool.veryTightLL = False
    theTool.ptMin = 10000
    theTool.etaMax = 2.47
    theTool.EtIsoMaxHighPt = 0.14
    theTool.EtIsoMaxLowPt = 0.14
    #use DeltaR = .3
    theTool.ptIsoDeltaR20  = False
    theTool.PtIsoMax = 0.13
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass

def ElectronSelectorToolConfig_TightLL(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = True
    theTool.veryTightLL = False
    theTool.ptMin = 10000
    theTool.etaMax = 2.47
    theTool.EtIsoMaxHighPt = 0.14
    theTool.EtIsoMaxLowPt = 0.14
    #use DeltaR = .3
    theTool.ptIsoDeltaR20  = False
    theTool.PtIsoMax = 0.13
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass

def ElectronSelectorToolConfig_VeryTightLL(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = True
    theTool.ptMin = 10000
    theTool.etaMax = 2.47
    theTool.EtIsoMaxHighPt = 0.14
    theTool.EtIsoMaxLowPt = 0.14
    #use DeltaR = .3
    theTool.ptIsoDeltaR20  = False 
    theTool.PtIsoMax = 0.13
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass


def ElectronSelectorToolConfig_HW(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = True
    theTool.ptMin = 10000
    theTool.etaMax = 2.47
    theTool.EtIsoMaxHighPt = 0.10
    theTool.EtIsoMaxLowPt = 0.07
    theTool.ptIsoDeltaR20  = True # use Delta R = .2
    theTool.PtIsoMax = 0.04 #use tighter pt Iso
    theTool.elDeltaRMin = 0.1 #changed Delta R
    theTool.muDeltaRMin = 0.1 #changed Delta R
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass
def ElectronSelectorToolConfig_HW_NoQuality_NoPtReq(theTool) :
    """
    This defines the cut values for the No Quality NoPtReq operating point.
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = False
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    theTool.ptMin = 1000
    pass

def ElectronSelectorToolConfig_HW_Custom(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    ElectronSelectorToolConfig_HW(theTool)
    theTool.loosePP = False
    theTool.mediumPP = False
    theTool.tightPP = True
    theTool.veryLooseLL = False
    theTool.looseLL = False
    theTool.mediumLL = False
    theTool.tightLL = False
    theTool.veryTightLL = False
    pass
def ElectronSelectorToolConfig_HW_Custom_Pt20GeV(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    ElectronSelectorToolConfig_HW_Custom(theTool)
    theTool.ptMin = 20000
    pass

def ElectronSelectorToolConfig_HW_Custom_NoIsolCuts(theTool) :
    """
    This defines the cut values for the Tight operating point.
    remove isol cuts
    """
    ElectronSelectorToolConfig_HW_Custom(theTool)
    theTool.EtIsoMaxHighPt = 1000000.
    theTool.EtIsoMaxLowPt = 1000000.
    theTool.PtIsoMax = 1000000. #use tighter pt Iso
    theTool.d0SigMax = 100
    theTool.z0SigMax = 100
    pass

def ElectronSelectorToolConfig_HW_Custom_Fakes(theTool) :
    """
    This defines the cut values for the Tight operating point.
    remove isol cuts
    """
    ElectronSelectorToolConfig_HW_Custom(theTool)
    theTool.EtIsoMaxHighPt = 1000000.
    theTool.EtIsoMaxLowPt = 1000000.
    theTool.PtIsoMax = 1000000. #use tighter pt Iso
    theTool.d0SigMax = 100
    theTool.z0SigMax = 100
    theTool.mediumPP = True
    theTool.tightPP = False
    pass

def ElectronSelectorToolConfig_HW_Custom_NoIPCuts(theTool) :
    """
    This defines the cut values for the Tight operating point.
    remove IP cuts
    """
    ElectronSelectorToolConfig_HW_Custom(theTool)
    theTool.CutEtIso = True
    theTool.CutPtIso = True
    theTool.CutZ0 = True
    theTool.d0SigMax = 100
    theTool.z0SigMax = 100
    pass
