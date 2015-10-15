##=============================================================================
## Name:        TauSelectorCutDefs
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Define the cut values for the TauSelectorTools
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



def TauSelectorToolConfig_Loose(theTool) :
    """
    This defines the cut values for the Loose operating point.
    """
    theTool = GetTool(theTool)
    theTool.EtMin = 20000
    theTool.etaMax = 2.47
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.tauDeltaRMin = 0.2
    pass




def TauSelectorToolConfig_Medium(theTool) :
    """
    This defines the cut values for the Medium operating point.
    """
    theTool = GetTool(theTool)
    theTool.EtMin = 20000
    theTool.etaMax = 2.47
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.tauDeltaRMin = 0.2
    pass


def TauSelectorToolConfig_Tight(theTool) :
    """
    This defines the cut values for the Tight operating point.
    """
    theTool = GetTool(theTool)
    theTool.EtMin = 20000
    theTool.etaMax = 2.47
    theTool.elDeltaRMin = 0.2
    theTool.muDeltaRMin = 0.2
    theTool.tauDeltaRMin = 0.2
    pass

