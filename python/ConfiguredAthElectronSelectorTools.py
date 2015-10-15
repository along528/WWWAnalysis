##=============================================================================
## Name:        ConfiguredAthElectronSelectorTools
##
## Author:      Karsten Koeneke (CERN)
## Created:     July 2011
##
## Description: Apply the default configurations for the AthElectronSelectorTool,
##              but allow for overwriting them with user-defined values.
##
##=============================================================================

# Import the needed general stuff
from ObjectSelectorCore.HelperUtils import *
from AthenaCommon import CfgMgr

# Import the needed stuff specific to the HTTAnalysis
from wwwAnalysis.HTTAnalysisConf import AthElectronSelectorTool
from wwwAnalysis.ElectronSelectorCutDefs import *



def ConfiguredAthElectronSelectorTool_Loose( name, **kw ):
    """
    Configure the AthElectronSelectorTool with the default Loose cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthElectronSelectorTool(name, **kw)

    # Configure it with the standard configuration
    ElectronSelectorToolConfig_Loose( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool




def ConfiguredAthElectronSelectorTool_Medium( name, **kw ):
    """
    Configure the AthElectronSelectorTool with the default Medium cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthElectronSelectorTool(name, **kw)

    # Configure it with the standard configuration
    ElectronSelectorToolConfig_Medium( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool




def ConfiguredAthElectronSelectorTool_Tight( name, **kw ):
    """
    Configure the AthElectronSelectorTool with the default Tight cuts
    and allow for (re-)setting of all provided cuts.
    """    
    # Create and instance of the tool
    tool = CfgMgr.AthElectronSelectorTool(name, **kw)

    # Configure it with the standard configuration
    ElectronSelectorToolConfig_Tight( tool )

    # Get all provided properties and overwrite the default values with them
    SetToolProperties( tool, **kw )
    
    return tool

