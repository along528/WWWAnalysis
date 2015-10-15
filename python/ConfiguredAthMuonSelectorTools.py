##=============================================================================
## Name:        ConfiguredAthMuonSelectorTools
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Apply the default configurations for the AthMuonSelectorTool,
##              but allow for overwriting them with user-defined values.
##
##=============================================================================

# Import the needed general stuff
from ObjectSelectorCore.HelperUtils import *
from AthenaCommon import CfgMgr

# Import the needed stuff specific to the HTTAnalysis
from wwwAnalysis.HTTAnalysisConf import AthMuonSelectorTool
from wwwAnalysis.MuonSelectorCutDefs import *



def ConfiguredAthMuonSelectorTool_Loose( name, **kw ):
    """
    Configure the AthMuonSelectorTool with the default Loose cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthMuonSelectorTool(name, **kw)

    # Configure it with the standard configuration
    MuonSelectorToolConfig_Loose( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool




def ConfiguredAthMuonSelectorTool_Medium( name, **kw ):
    """
    Configure the AthMuonSelectorTool with the default Medium cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthMuonSelectorTool(name, **kw)

    # Configure it with the standard configuration
    MuonSelectorToolConfig_Medium( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool




def ConfiguredAthMuonSelectorTool_Tight( name, **kw ):
    """
    Configure the AthMuonSelectorTool with the default Tight cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthMuonSelectorTool(name, **kw)

    # Configure it with the standard configuration
    MuonSelectorToolConfig_Tight( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool

