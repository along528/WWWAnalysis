##=============================================================================
## Name:        ConfiguredAthEventSelectorTools
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Apply the default configurations for the AthEventSelectorTool,
##              but allow for overwriting them with user-defined values.
##
##=============================================================================

# Import the needed general stuff
from PATCore.HelperUtils import *
from AthenaCommon import CfgMgr

# Import the needed stuff specific to the wwwAnalysis
from wwwAnalysis.wwwAnalysisConf import AthEventSelectorTool
from wwwAnalysis.EventSelectorCutDefs import *



def ConfiguredAthEventSelectorTool_Loose( name, **kw ):
    """
    Configure the AthEventSelectorTool with the default Loose cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthEventSelectorTool(name, **kw)

    # Configure it with the standard configuration
    EventSelectorToolConfig_Loose( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool




def ConfiguredAthEventSelectorTool_Medium( name, **kw ):
    """
    Configure the AthEventSelectorTool with the default Medium cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthEventSelectorTool(name, **kw)

    # Configure it with the standard configuration
    EventSelectorToolConfig_Medium( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool




def ConfiguredAthEventSelectorTool_Tight( name, **kw ):
    """
    Configure the AthEventSelectorTool with the default Tight cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthEventSelectorTool(name, **kw)

    # Configure it with the standard configuration
    EventSelectorToolConfig_Tight( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool

