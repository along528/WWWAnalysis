##=============================================================================
## Name:        JetSelectorCutDefs
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Define the cut values for the JetSelectorTools
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



def JetSelectorToolConfig_Loose(theTool) :
    """
    This defines the cut values for the Loose operating point.
    """
    theTool = GetTool(theTool)
    theTool.ptMin = 25000 
    #theTool.etaMax = 
    theTool.elDeltaRMin = 0.3 #2
    theTool.muDeltaRMin = 0.3 #2
    theTool.CutJetCleaning = True
    #theTool.tauDeltaRMin = 0.2
    #theTool.jetDeltaRMin = 0.2
    pass




def JetSelectorToolConfig_Medium(theTool) :
    """
    This defines the cut values for the Medium operating point.
    """
    theTool = GetTool(theTool)
    theTool.ptMin = 25000
    theTool.etaMax = 4.5
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.tauDeltaRMin = 0.2
    theTool.jetDeltaRMin = 0.2
    theTool.CutJetCleaning = True
    pass


def JetSelectorToolConfig_Tight(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    theTool.ptMin = 25000
    theTool.etaMax = 4.5
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.tauDeltaRMin = 0.2
    theTool.jetDeltaRMin = 0.2
    theTool.CutJetCleaning = True
    pass

