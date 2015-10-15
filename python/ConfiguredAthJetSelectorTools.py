##=============================================================================
## Name:        ConfiguredAthJetSelectorTools
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Apply the default configurations for the AthJetSelectorTool,
##              but allow for overwriting them with user-defined values.
##
##=============================================================================

# Import the needed general stuff
from ObjectSelectorCore.HelperUtils import *
from AthenaCommon import CfgMgr

# Import the needed stuff specific to the HTTAnalysis
from wwwAnalysis.HTTAnalysisConf import AthJetSelectorTool
from wwwAnalysis.JetSelectorCutDefs import *



def ConfiguredAthJetSelectorTool_Loose( name, **kw ):
    """
    Configure the AthJetSelectorTool with the default Loose cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthJetSelectorTool(name, **kw)

    # Configure it with the standard configuration
    JetSelectorToolConfig_Loose( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool




def ConfiguredAthJetSelectorTool_Medium( name, **kw ):
    """
    Configure the AthJetSelectorTool with the default Medium cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthJetSelectorTool(name, **kw)

    # Configure it with the standard configuration
    JetSelectorToolConfig_Medium( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool




def ConfiguredAthJetSelectorTool_Tight( name, **kw ):
    """
    Configure the AthJetSelectorTool with the default Tight cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthJetSelectorTool(name, **kw)

    # Configure it with the standard configuration
    JetSelectorToolConfig_Tight( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool

