##=============================================================================
## Name:        ConfiguredTJetSelectorTools
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Apply the default configurations for the TJetSelectorTool.
##
## Usage: In your ROOT session (after loading the libraries from RootCore):
##        TPython::LoadMacro("./path/to/this/file/ConfiguredTJetSelectorTools.py");
##        Root::TJetSelectorTool* myLooseTool = (void*)TPython::Eval("ConfiguredTJetSelectorTool_Loose()");
##        myLooseTool->initialize();
##
##=============================================================================

# import the needed Reflex and ROOT stuff
import PyCintex
PyCintex.Cintex.Enable()
import ROOT

# Import the needed stuff specific to the JetSelectorTool
from wwwAnalysis.JetSelectorCutDefs import *

def ConfiguredTJetSelectorTool_Loose():
    """
    Configure the TJetSelectorTool with the default Loose cuts
    """    
    tool = ROOT.wwwAnalysis.TJetSelectorTool()
    JetSelectorToolConfig_Loose(tool)
    return tool



def ConfiguredTJetSelectorTool_Medium():
    """
    Configure the TJetSelectorTool with the default Medium cuts
    """    
    tool = ROOT.wwwAnalysis.TJetSelectorTool()
    JetSelectorToolConfig_Medium(tool)
    return tool



def ConfiguredTJetSelectorTool_Tight():
    """
    Configure the TJetSelectorTool with the default Tight cuts
    """    
    tool = ROOT.wwwAnalysis.TJetSelectorTool()
    JetSelectorToolConfig_Tight(tool)
    return tool
