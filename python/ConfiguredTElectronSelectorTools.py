##=============================================================================
## Name:        ConfiguredTElectronSelectorTools
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Apply the default configurations for the TElectronSelectorTool.
##
## Usage: In your ROOT session (after loading the libraries from RootCore):
##        TPython::LoadMacro("./path/to/this/file/ConfiguredTElectronSelectorTools.py");
##        Root::TElectronSelectorTool* myLooseTool = (void*)TPython::Eval("ConfiguredTElectronSelectorTool_Loose()");
##        myLooseTool->initialize();
##
##=============================================================================

# import the needed Reflex and ROOT stuff
import PyCintex
PyCintex.Cintex.Enable()
import ROOT

# Import the needed stuff specific to the ElectronSelectorTool
from wwwAnalysis.ElectronSelectorCutDefs import *

def ConfiguredTElectronSelectorTool_Fake():
    """
    Configure the TElectronSelectorTool with the default Loose cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Fake(tool)
    return tool

def ConfiguredTElectronSelectorTool_LoosePP_InvZ0_InvEtIso_InvPtIso():
    """
    Configure the TElectronSelectorTool with the default Loose cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_LoosePP_InvZ0_InvEtIso_InvPtIso(tool)
    return tool

def ConfiguredTElectronSelectorTool_Loose():
    """
    Configure the TElectronSelectorTool with the default Loose cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose(tool)
    return tool

def ConfiguredTElectronSelectorTool_Loose_InvertedID():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only Inverted ID Cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedID(tool)
    return tool
def ConfiguredTElectronSelectorTool_Loose_InvertedPtIso():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only Inverted pt isolation
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedPtIso(tool)
    return tool
def ConfiguredTElectronSelectorTool_Loose_InvertedEtIso_InvertedPtIso():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only Inverted pt and et isolation
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedEtIso_InvertedPtIso(tool)
    return tool
def ConfiguredTElectronSelectorTool_Loose_InvertedID_InvertedEtIso_InvertedPtIso():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only Inverted pt and et isolation and ID isolation
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedID_InvertedEtIso_InvertedPtIso(tool)
    return tool
def ConfiguredTElectronSelectorTool_Loose_InvertedIDLoosepp_InvertedEtIso_InvertedPtIso():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only Inverted pt and et isolation and ID isolation
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedIDLoosepp_InvertedEtIso_InvertedPtIso(tool)
    return tool
def ConfiguredTElectronSelectorTool_Loose_InvertedIDLoosepp():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only ID isolation
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedIDLoosepp(tool)
    return tool
def ConfiguredTElectronSelectorTool_Loose_InvertedID_InvertedEtIso_InvertedPtIso_Pt20GeV():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only Inverted pt and et isolation and ID isolation
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedID_InvertedEtIso_InvertedPtIso_Pt20GeV(tool)
    return tool
def ConfiguredTElectronSelectorTool_Loose_InvertedID_InvertedPtIso():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only Inverted pt isolation and ID
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedID_InvertedPtIso(tool)
    return tool
def ConfiguredTElectronSelectorTool_Loose_InvertedEtIso():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only Inverted et isolation
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedEtIso(tool)
    return tool

def ConfiguredTElectronSelectorTool_Loose_InvertedZ0():
    """
    Configure the TElectronSelectorTool with the default Loose cuts only Inverted z0 sin theta
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Loose_InvertedZ0(tool)
    return tool


def ConfiguredTElectronSelectorTool_FakeRate_Tight() :
    """
    Configure the TElectronSelectorTool with the tight fake rate selection
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_FakeRate_Tight(tool)
    return tool

def ConfiguredTElectronSelectorTool_RealRate_Tight() :
    """
    Configure the TElectronSelectorTool with the tight real rate selection
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_RealRate_Tight(tool)
    return tool

def ConfiguredTElectronSelectorTool_Medium():
    """
    Configure the TElectronSelectorTool with the default Medium cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Medium(tool)
    return tool



def ConfiguredTElectronSelectorTool_Tight():
    """
    Configure the TElectronSelectorTool with the default Tight cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_Tight(tool)
    return tool

def ConfiguredTElectronSelectorTool_VeryTightLL():
    """
    Configure the TElectronSelectorTool with the default log likelihoo very tight cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_VeryTightLL(tool)
    return tool
def ConfiguredTElectronSelectorTool_TightLL():
    """
    Configure the TElectronSelectorTool with the default log likelihoo tight cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_TightLL(tool)
    return tool
def ConfiguredTElectronSelectorTool_MediumLL():
    """
    Configure the TElectronSelectorTool with the default log likelihoo medium cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_MediumLL(tool)
    return tool
def ConfiguredTElectronSelectorTool_LooseLL():
    """
    Configure the TElectronSelectorTool with the default log likelihoo loose cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_LooseLL(tool)
    return tool
def ConfiguredTElectronSelectorTool_VeryLooseLL():
    """
    Configure the TElectronSelectorTool with the default log likelihoo very loose cuts
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_VeryLooseLL(tool)
    return tool

def ConfiguredTElectronSelectorTool_HW():
    """
    Configure the TElectronSelectorTool with the HW 3-lepton configuration
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_HW(tool)
    return tool
def ConfiguredTElectronSelectorTool_HW_NoQuality_NoPtReq():
    """
    Configure the TElectronSelectorTool with the HW 3-lepton configuration with no quality or 
    quality or pt requirements
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_HW_NoQuality_NoPtReq(tool)
    return tool

def ConfiguredTElectronSelectorTool_HW_Custom():
    """
    Configure the TElectronSelectorTool with the HW 3-lepton configuration plus custom changes
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_HW_Custom(tool)
    return tool
def ConfiguredTElectronSelectorTool_HW_Custom_Pt20GeV():
    """
    Configure the TElectronSelectorTool with the HW 3-lepton configuration plus custom changes
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_HW_Custom_Pt20GeV(tool)
    return tool
def ConfiguredTElectronSelectorTool_HW_Custom_NoIPCuts():
    """
    Configure the TElectronSelectorTool with the HW 3-lepton configuration plus custom changes
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_HW_Custom_NoIPCuts(tool)
    return tool
def ConfiguredTElectronSelectorTool_HW_Custom_NoIsolCuts():
    """
    Configure the TElectronSelectorTool with the HW 3-lepton configuration plus custom changes
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_HW_Custom_NoIsolCuts(tool)
    return tool
def ConfiguredTElectronSelectorTool_HW_Custom_Fakes():
    """
    Configure the TElectronSelectorTool with the HW 2-lepton configuration plus Fakes
    """    
    tool = ROOT.wwwAnalysis.TElectronSelectorTool()
    ElectronSelectorToolConfig_HW_Custom_Fakes(tool)
    return tool
