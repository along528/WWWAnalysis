##=============================================================================
## Name:        MuonSelectorCutDefs
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Define the cut values for the MuonSelectorTools
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



def MuonSelectorToolConfig_Fake(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = True
    theTool.CutEtIso = True
    theTool.CutD0 = True
    theTool.CutZ0 = True
    #End Loose Inversion Cuts


    theTool.cutCombined = 1
    theTool.stacoLoose = 0
    theTool.stacoMedium = 0
    theTool.stacoTight = 1
    theTool.thirdMuLoose = 0
    theTool.thirdMuMedium = 0
    theTool.thirdMuTight = 0
    theTool.etaMax = 2.5
    theTool.bLayerHitsMin = 0
    theTool.pixelHitsMin = 0
    theTool.SCTHitsMin = 4
    theTool.TRTHitsMin = 5
    theTool.SiHolesMax = 3
    theTool.ptMin = 15000
    theTool.z0ExpPVMax = 10
    theTool.ptIsoDeltaR20 = False #DeltaR = .3
    theTool.PtIsoMin = -100 # 0.12
#    theTool.PtIsoMax = 0.30
#    theTool.EtIsoMin = 0.09
#    theTool.EtIsoMax = 0.30
    theTool.muDeltaRMin = 0.2
    #theTool.d0SigMax = 3
    #theTool.z0SigMax = 0.5
    #IS this what we want?
    theTool.d0SigMax = 10000 #3
    theTool.z0SigMax = 10000 #0.5
    pass

def MuonSelectorToolConfig_StacoLoose(theTool) :
    """
    This defines the cut values for the Staco Loose operating point.
    """
    theTool = GetTool(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = True
    theTool.CutEtIso = True
    theTool.CutD0 = True
    theTool.CutZ0 = True
    #End Loose Inversion Cuts
    theTool.cutCombined = 1
    theTool.stacoLoose = 1
    theTool.stacoMedium = 0
    theTool.stacoTight = 0
    theTool.thirdMuLoose = 0
    theTool.thirdMuMedium = 0
    theTool.thirdMuTight = 0
    theTool.etaMax = 2.5
    theTool.bLayerHitsMin = 0
    theTool.pixelHitsMin = 0
    theTool.SCTHitsMin = 4
    theTool.TRTHitsMin = 5
    theTool.SiHolesMax = 3
    theTool.ptMin = 10000
    theTool.z0ExpPVMax = 10
    theTool.ptIsoDeltaR20 = False #DeltaR = .3
    theTool.PtIsoMax = .12
    theTool.EtIsoMaxLowPt = .10
    theTool.EtIsoMaxHighPt = .10
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass




def MuonSelectorToolConfig_StacoMedium(theTool) :
    """
    This defines the cut values for the Staco Medium operating point.
    """
    theTool = GetTool(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = True
    theTool.CutEtIso = True
    theTool.CutD0 = True
    theTool.CutZ0 = True
    #End Loose Inversion Cuts
    theTool.cutCombined = 1
    theTool.stacoLoose = 0
    theTool.stacoMedium = 1
    theTool.stacoTight = 0
    theTool.thirdMuLoose = 0
    theTool.thirdMuMedium = 0
    theTool.thirdMuTight = 0
    theTool.etaMax = 2.5
    theTool.bLayerHitsMin = 0
    theTool.pixelHitsMin = 0
    theTool.SCTHitsMin = 4
    theTool.TRTHitsMin = 5
    theTool.SiHolesMax = 3
    theTool.ptMin = 10000
    theTool.z0ExpPVMax = 10
    theTool.ptIsoDeltaR20 = False #DeltaR = .3
    theTool.PtIsoMax = 0.12
    theTool.EtIsoMaxLowPt = .10
    theTool.EtIsoMaxHighPt = .10
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass


def MuonSelectorToolConfig_StacoTight(theTool) :
    """
    This defines the cut values for the Staco Tight operating point.
    """
#    theTool = GetTool(theTool)
#    theTool.stacoLoose = 0
#    theTool.stacoMedium = 0
#    theTool.stacoTight = 1
#    theTool.etaMax = 2.5
#    theTool.bLayerHitsMin = 0
#    theTool.pixelHitsMin = 0
#    theTool.SCTHitsMin = 0
#    theTool.TRTHitsMin = 0
#    theTool.SiHolesMax = 1000000
#    theTool.ptMin = 0
#    theTool.z0ExpPVMax = 100000
#    theTool.PtIsoMax = 100000
#    theTool.EtIsoMax = 100000
#    theTool.muDeltaRMin = 0.2
    theTool = GetTool(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = True
    theTool.CutEtIso = True
    theTool.CutD0 = True
    theTool.CutZ0 = True
    #End Loose Inversion Cuts
    theTool.cutCombined = 1
    theTool.stacoLoose = 0
    theTool.stacoMedium = 0
    theTool.stacoTight = 1
    theTool.thirdMuLoose = 0
    theTool.thirdMuMedium = 0
    theTool.thirdMuTight = 0
    theTool.etaMax = 2.5
    theTool.bLayerHitsMin = 0
    theTool.pixelHitsMin = 0
    theTool.SCTHitsMin = 4
    theTool.TRTHitsMin = 5
    theTool.SiHolesMax = 3
    theTool.ptMin = 10000
    theTool.z0ExpPVMax = 10
    theTool.ptIsoDeltaR20 = False #DeltaR = .3
    theTool.PtIsoMax = 0.12
    theTool.EtIsoMaxLowPt = .10
    theTool.EtIsoMaxHighPt = .10
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass

def MuonSelectorToolConfig_ThirdMuLoose(theTool) :
    """
    This defines the cut values for the Third Muon Loose operating point.
    """
    theTool = GetTool(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = True
    theTool.CutEtIso = True
    theTool.CutD0 = True
    theTool.CutZ0 = True
    #End Loose Inversion Cuts
    theTool.cutCombined = 1
    theTool.stacoLoose = 0
    theTool.stacoMedium = 0
    theTool.stacoTight = 0
    theTool.thirdMuLoose = 1
    theTool.thirdMuMedium = 0
    theTool.thirdMuTight = 0
    theTool.etaMax = 2.5
    theTool.bLayerHitsMin = 0
    theTool.pixelHitsMin = 0
    theTool.SCTHitsMin = 4
    theTool.TRTHitsMin = 5
    theTool.SiHolesMax = 3
    theTool.ptMin = 10000
    theTool.z0ExpPVMax = 10
    theTool.ptIsoDeltaR20 = False #DeltaR = .3
    theTool.PtIsoMax = .12
    theTool.EtIsoMaxLowPt = .10
    theTool.EtIsoMaxHighPt = .10
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass




def MuonSelectorToolConfig_ThirdMuMedium(theTool) :
    """
    This defines the cut values for the Third Muon Medium operating point.

    """
    theTool = GetTool(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = True
    theTool.CutEtIso = True
    theTool.CutD0 = True
    theTool.CutZ0 = True
    #End Loose Inversion Cuts
    theTool.cutCombined = 1
    theTool.stacoLoose = 0
    theTool.stacoMedium = 0
    theTool.stacoTight = 0
    theTool.thirdMuLoose = 0
    theTool.thirdMuMedium = 1
    theTool.thirdMuTight = 0
    theTool.etaMax = 2.5
    theTool.bLayerHitsMin = 0
    theTool.pixelHitsMin = 0
    theTool.SCTHitsMin = 4
    theTool.TRTHitsMin = 5
    theTool.SiHolesMax = 3
    theTool.ptMin = 10000
    theTool.z0ExpPVMax = 10
    theTool.ptIsoDeltaR20 = False #DeltaR = .3
    theTool.PtIsoMax = 0.12
    theTool.EtIsoMaxLowPt = .10
    theTool.EtIsoMaxHighPt = .10
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass


def MuonSelectorToolConfig_ThirdMuTight(theTool) :
    """
    This defines the cut values for the ThirdMu Tight operating point.
    """
#    theTool = GetTool(theTool)
#    theTool.stacoLoose = 0
#    theTool.stacoMedium = 0
#    theTool.stacoTight = 1
#    theTool.etaMax = 2.5
#    theTool.bLayerHitsMin = 0
#    theTool.pixelHitsMin = 0
#    theTool.SCTHitsMin = 0
#    theTool.TRTHitsMin = 0
#    theTool.SiHolesMax = 1000000
#    theTool.ptMin = 0
#    theTool.z0ExpPVMax = 100000
#    theTool.PtIsoMax = 100000
#    theTool.EtIsoMax = 100000
#    theTool.muDeltaRMin = 0.2
    theTool = GetTool(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = True
    theTool.CutEtIso = True
    theTool.CutD0 = True
    theTool.CutZ0 = True
    #End Loose Inversion Cuts
    theTool.cutCombined = 1
    theTool.stacoLoose = 0
    theTool.stacoMedium = 0
    theTool.stacoTight = 0
    theTool.thirdMuLoose = 0
    theTool.thirdMuMedium = 0
    theTool.thirdMuTight = 1
    theTool.etaMax = 2.5
    theTool.bLayerHitsMin = 0
    theTool.pixelHitsMin = 0
    theTool.SCTHitsMin = 4
    theTool.TRTHitsMin = 5
    theTool.SiHolesMax = 3
    theTool.ptMin = 10000
    theTool.z0ExpPVMax = 10
    theTool.ptIsoDeltaR20 = False #DeltaR = .3
    theTool.PtIsoMax = 0.12
    theTool.EtIsoMaxLowPt = .10
    theTool.EtIsoMaxHighPt = .10
    theTool.muDeltaRMin = 0.2
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass

def MuonSelectorToolConfig_HW(theTool) :
    """
    This defines the cut values for the HW 3lepton analysis
    """
#    theTool = GetTool(theTool)
#    theTool.stacoLoose = 0
#    theTool.stacoMedium = 0
#    theTool.stacoTight = 1
#    theTool.etaMax = 2.5
#    theTool.bLayerHitsMin = 0
#    theTool.pixelHitsMin = 0
#    theTool.SCTHitsMin = 0
#    theTool.TRTHitsMin = 0
#    theTool.SiHolesMax = 1000000
#    theTool.ptMin = 0
#    theTool.z0ExpPVMax = 100000
#    theTool.PtIsoMax = 100000
#    theTool.EtIsoMax = 100000
#    theTool.muDeltaRMin = 0.2
    theTool = GetTool(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = True
    theTool.CutEtIso = True
    theTool.CutD0 = True
    theTool.CutZ0 = True
    #End Loose Inversion Cuts
    theTool.cutCombined = 1
    theTool.stacoLoose = 0
    theTool.stacoMedium = 0
    theTool.stacoTight = 1
    theTool.thirdMuLoose = 0
    theTool.thirdMuMedium = 0
    theTool.thirdMuTight = 0
    theTool.etaMax = 2.5
    theTool.bLayerHitsMin = 0
    theTool.pixelHitsMin = 0
    theTool.SCTHitsMin = 4
    theTool.TRTHitsMin = 5
    theTool.SiHolesMax = 3
    theTool.ptMin = 10000
    theTool.ptIsoDeltaR20 = True #use tighter delta R
    theTool.z0ExpPVMax = 10
    theTool.PtIsoMax = 0.04 #use tigter pt iso
    theTool.EtIsoMaxLowPt = .07
    theTool.EtIsoMaxHighPt = .10
    theTool.muDeltaRMin = 0.1 #tigher Delta R
    theTool.d0SigMax = 3
    theTool.z0SigMax = 0.5
    pass
def MuonSelectorToolConfig_HW_NoQuality_NoPtReq(theTool) :
    """
    This defines the cut values for the HW 3lepton analysis but with no quality or pt requirements
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.cutCombined = 0 #don't demand combined muon
    theTool.stacoLoose = 0
    theTool.stacoMedium = 0
    theTool.stacoTight = 0
    theTool.thirdMuLoose = 0
    theTool.thirdMuMedium = 0
    theTool.thirdMuTight = 0
    theTool.ptMin = 1000 #1 GeV
    pass
def MuonSelectorToolConfig_Loose(theTool) :
    """
    This defines the cut values for the loose matrix-method selection
    """
    MuonSelectorToolConfig_HW(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = False
    theTool.CutEtIso = False
    theTool.CutD0 = False
    theTool.CutZ0 = False
    #End Loose Inversion Cuts
    pass
def MuonSelectorToolConfig_Loose_InvertedPtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method selection with only pt isolation inverted
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.CutPtIso = False
    pass
def MuonSelectorToolConfig_Loose_InvertedEtIso_InvertedPtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method selection with only pt and et isolation inverted
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.CutPtIso = False
    theTool.CutEtIso = False
    pass
def MuonSelectorToolConfig_Loose_InvertedEtIso_InvertedPtIso_Pt20GeV(theTool) :
    """
    This defines the cut values for the loose matrix-method selection with only pt and et isolation inverted
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.CutPtIso = False
    theTool.CutEtIso = False
    theTool.ptMin = 20000
    pass
def MuonSelectorToolConfig_Loose_InvertedEtIso_InvertedPtIso_InvertedCombination(theTool) :
    """
    This defines the cut values for the loose matrix-method selection with pt and et isolation inverted as well muon combination
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.CutPtIso = False
    theTool.CutEtIso = False
    theTool.cutCombined = 0
    pass
def MuonSelectorToolConfig_Loose_InvertedPtIso_InvertedD0(theTool) :
    """
    This defines the cut values for the loose matrix-method selection with only pt isolation and d0 cuts inverted
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.CutPtIso = False
    theTool.CutD0 = False
    pass
def MuonSelectorToolConfig_Loose_InvertedEtIso(theTool) :
    """
    This defines the cut values for the loose matrix-method selection with only et isolation inverted
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.CutEtIso = False
    pass
def MuonSelectorToolConfig_Loose_InvertedD0(theTool) :
    """
    This defines the cut values for the loose matrix-method selection with only d0 significnace cut inverted
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.CutD0 = False
    pass
def MuonSelectorToolConfig_Loose_InvertedZ0(theTool) :
    """
    This defines the cut values for the loose matrix-method selection with only z0 sin theta cut inverted
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.CutZ0 = False
    #End Loose Inversion Cuts
    pass
def MuonSelectorToolConfig_FakeRate_Tight(theTool) :
    """
    This defines the cut values for the tight matrix-method fake rateselection
    """
    MuonSelectorToolConfig_HW(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = False
    theTool.CutEtIso = False
    theTool.CutD0 = False
    theTool.CutZ0 = False
    #End Loose Inversion Cuts
    pass
def MuonSelectorToolConfig_RealRate_Tight(theTool) :
    """
    This defines the cut values for the tight matrix-method real rateselection
    """
    MuonSelectorToolConfig_HW(theTool)
    #Loose Inversion Cuts
    theTool.CutPtIso = False
    theTool.CutEtIso = False
    theTool.CutD0 = False
    theTool.CutZ0 = False
    #End Loose Inversion Cuts
    pass
def MuonSelectorToolConfig_HW_Custom(theTool) :
    """
    This defines the cut values for the HW 3lepton analysis plust custom changes
    """
    MuonSelectorToolConfig_HW(theTool)
    pass
def MuonSelectorToolConfig_HW_Custom_Pt20GeV(theTool) :
    """
    This defines the cut values for the HW 3lepton analysis plust custom changes
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.ptMin = 20000
    pass
def MuonSelectorToolConfig_HW_Custom_NoIPCuts(theTool) :
    """
    This defines the cut values for the HW 3lepton analysis plust custom changes
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.d0SigMax = 100
    theTool.z0SigMax = 100
    pass
def MuonSelectorToolConfig_HW_Custom_NoIsolCuts(theTool) :
    """
    This defines the cut values for the HW 3lepton analysis plust custom changes
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.PtIsoMax = 100000. #use tigter pt iso
    theTool.EtIsoMaxLowPt = 100000.
    theTool.EtIsoMaxHighPt = 100000.
    theTool.d0SigMax = 100
    theTool.z0SigMax = 100
    pass
def MuonSelectorToolConfig_HW_Custom_Fakes(theTool) :
    """
    This defines the cut values for the HW 3lepton analysis plust custom changes
    """
    MuonSelectorToolConfig_HW(theTool)
    theTool.PtIsoMax = 100000. #use tigter pt iso
    theTool.EtIsoMaxLowPt = 100000.
    theTool.EtIsoMaxHighPt = 100000.
    theTool.d0SigMax = 100
    theTool.z0SigMax = 100
    theTool.stacoLoose = 1
    theTool.stacoMedium = 1
    theTool.stacoTight = 1
    pass


