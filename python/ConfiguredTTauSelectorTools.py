##=============================================================================
## Name:        ConfiguredTTauSelectorTools
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Apply the default configurations for the TTauSelectorTool.
##
## Usage: In your ROOT session (after loading the libraries from RootCore):
##        TPython::LoadMacro("./path/to/this/file/ConfiguredTTauSelectorTools.py");
##        Root::TTauSelectorTool* myLooseTool = (void*)TPython::Eval("ConfiguredTTauSelectorTool_Loose()");
##        myLooseTool->initialize();
##
##=============================================================================

# import the needed Reflex and ROOT stuff
import PyCintex
PyCintex.Cintex.Enable()
import ROOT

# Import the needed stuff specific to the TauSelectorTool
from wwwAnalysis.TauSelectorCutDefs import *

def ConfiguredTTauSelectorTool_Loose():
    """
    Configure the TTauSelectorTool with the default Loose cuts
    """    
    tool = ROOT.wwwAnalysis.TTauSelectorTool()
    TauSelectorToolConfig_Loose(tool)
    return tool



def ConfiguredTTauSelectorTool_Medium():
    """
    Configure the TTauSelectorTool with the default Medium cuts
    """    
    tool = ROOT.wwwAnalysis.TTauSelectorTool()
    TauSelectorToolConfig_Medium(tool)
    return tool



def ConfiguredTTauSelectorTool_Tight():
    """
    Configure the TTauSelectorTool with the default Tight cuts
    """    
    tool = ROOT.wwwAnalysis.TTauSelectorTool()
    TauSelectorToolConfig_Tight(tool)
    return tool
