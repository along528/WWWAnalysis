##=============================================================================
## Name:        ConfiguredTMuonSelectorTools
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Apply the default configurations for the TMuonSelectorTool.
##
## Usage: In your ROOT session (after loading the libraries from RootCore):
##        TPython::LoadMacro("./path/to/this/file/ConfiguredTMuonSelectorTools.py");
##        Root::TMuonSelectorTool* myLooseTool = (void*)TPython::Eval("ConfiguredTMuonSelectorTool_Loose()");
##        myLooseTool->initialize();
##
##=============================================================================

# import the needed Reflex and ROOT stuff
import PyCintex
PyCintex.Cintex.Enable()
import ROOT

# Import the needed stuff specific to the MuonSelectorTool
from wwwAnalysis.MuonSelectorCutDefs import *

def ConfiguredTMuonSelectorTool_Fake():
    """
    Configure the TMuonSelectorTool with the default Loose cuts
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Fake(tool)
    return tool

def ConfiguredTMuonSelectorTool_StacoLoose():
    """
    Configure the TMuonSelectorTool with the default Staco Loose cuts
    """    
    print "STACO LOOSE"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_StacoLoose(tool)
    return tool



def ConfiguredTMuonSelectorTool_StacoMedium():
    """
    Configure the TMuonSelectorTool with the default Staco Medium cuts
    """    
    print "STACOMEDIUM"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_StacoMedium(tool)
    return tool



#def ConfiguredTMuonSelectorTool_Tight():
def ConfiguredTMuonSelectorTool_StacoTight():
    """
    Configure the TMuonSelectorTool with the default Staco Tight cuts
    """    
    print "STACOTIGHT"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_StacoTight(tool)
    return tool

def ConfiguredTMuonSelectorTool_ThirdMuLoose():
    print "THIRDMULOOSE"
    """
    Configure the TMuonSelectorTool with the default Third Mu Loose cuts
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_ThirdMuLoose(tool)
    return tool



def ConfiguredTMuonSelectorTool_ThirdMuMedium():
    """
    Configure the TMuonSelectorTool with the default Thrid Mu  Medium cuts
    """    
    print "THIRDMUMEDIUM"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_ThirdMuMedium(tool)
    return tool



def ConfiguredTMuonSelectorTool_ThirdMuTight():
    """
    Configure the TMuonSelectorTool with the default Third Mu Tight cuts
    """    
    print "THIRD MUTIGHT"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_ThirdMuTight(tool)
    return tool
def ConfiguredTMuonSelectorTool_HW():
    """
    Configure the TMuonSelectorTool with the HW 3-lepton configuration
    """    
    print "Muon HW "
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_HW(tool)
    return tool


def ConfiguredTMuonSelectorTool_HW_NoQuality_NoPtReq():
    """
    Configure the TMuonSelectorTool with the HW 3-lepton configuration
    but with no quality or pt requirements
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_HW_NoQuality_NoPtReq(tool)
    return tool
def ConfiguredTMuonSelectorTool_Loose():
    """
    Configure the TMuonSelectorTool with the loose matrix-method selection 
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Loose(tool)
    return tool
def ConfiguredTMuonSelectorTool_Loose_InvertedPtIso():
    """
    Configure the TMuonSelectorTool with the loose matrix-method selection  with only pt isolation inverted
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Loose_InvertedPtIso(tool)
    return tool
def ConfiguredTMuonSelectorTool_Loose_InvertedEtIso_InvertedPtIso():
    """
    Configure the TMuonSelectorTool with the loose matrix-method selection  with only pt and et isolation inverted
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Loose_InvertedEtIso_InvertedPtIso(tool)
    return tool
def ConfiguredTMuonSelectorTool_Loose_InvertedEtIso_InvertedPtIso_Pt20GeV():
    """
    Configure the TMuonSelectorTool with the loose matrix-method selection  with only pt and et isolation inverted
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Loose_InvertedEtIso_InvertedPtIso_Pt20GeV(tool)
    return tool
def ConfiguredTMuonSelectorTool_Loose_InvertedEtIso_InvertedPtIso_InvertedCombination():
    """
    Configure the TMuonSelectorTool with the loose matrix-method selection  with pt and et isolation inverted as well as combination
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Loose_InvertedEtIso_InvertedPtIso_InvertedCombination(tool)
    return tool
def ConfiguredTMuonSelectorTool_Loose_InvertedPtIso_InvertedD0():
    """
    Configure the TMuonSelectorTool with the loose matrix-method selection  with only pt isolation and d0 cuts inverted
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Loose_InvertedPtIso_InvertedD0(tool)
    return tool
def ConfiguredTMuonSelectorTool_Loose_InvertedEtIso():
    """
    Configure the TMuonSelectorTool with the loose matrix-method selection  with only et isolation inverted
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Loose_InvertedEtIso(tool)
    return tool
def ConfiguredTMuonSelectorTool_Loose_InvertedD0():
    """
    Configure the TMuonSelectorTool with the loose matrix-method selection  with only d0 significnace cut inverted
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Loose_InvertedD0(tool)
    return tool
def ConfiguredTMuonSelectorTool_Loose_InvertedZ0():
    """
    Configure the TMuonSelectorTool with the loose matrix-method selection  with only z0 sin theta cut inverted
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_Loose_InvertedZ0(tool)
    return tool

def ConfiguredTMuonSelectorTool_FakeRate_Tight() :
    """
    Configure the TMuonSelectorTool with the tight fake rate selection
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_FakeRate_Tight(tool)
    return tool

def ConfiguredTMuonSelectorTool_RealRate_Tight() :
    """
    Configure the TMuonSelectorTool with the tight real rate selection
    """    
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_RealRate_Tight(tool)
    return tool

def ConfiguredTMuonSelectorTool_HW_Custom():
    """
    Configure the TMuonSelectorTool with the HW 3-lepton configuration plus custom changes
    """    
    print "Muon HW Custom"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_HW_Custom(tool)
    return tool
def ConfiguredTMuonSelectorTool_HW_Custom_Pt20GeV():
    """
    Configure the TMuonSelectorTool with the HW 3-lepton configuration plus custom changes
    """    
    print "Muon HW Custom - Pt > 20 GeV"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_HW_Custom_Pt20GeV(tool)
    return tool
def ConfiguredTMuonSelectorTool_HW_Custom_NoIPCuts():
    """
    Configure the TMuonSelectorTool with the HW 3-lepton configuration plus custom changes
    """    
    print "Muon HW Custom"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_HW_Custom_NoIPCuts(tool)
    return tool
def ConfiguredTMuonSelectorTool_HW_Custom_NoIsolCuts():
    """
    Configure the TMuonSelectorTool with the HW 3-lepton configuration plus custom changes
    """    
    print "Muon HW Custom NoIsolCuts"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_HW_Custom_NoIsolCuts(tool)
    return tool
def ConfiguredTMuonSelectorTool_HW_Custom_Fakes():
    """
    Configure the TMuonSelectorTool with the HW 2-lepton configuration plus 1 fake changes
    """    
    print "Muon HW Custom HW custom-Fakes"
    tool = ROOT.wwwAnalysis.TMuonSelectorTool()
    MuonSelectorToolConfig_HW_Custom_Fakes(tool)
    return tool
