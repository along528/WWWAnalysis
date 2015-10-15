// Dear emacs, this is -*-c++-*-

/**
   @class AthMuonSelectorTool
   @brief Example tool to select objects in AthenaRootAccess using an underlying pure ROOT tool.

   @author Karsten Koeneke (CERN)
   @date   April 2011

*/

// Include this class's header
#include "wwwAnalysis/AthMuonSelectorTool.h"

// STL includes
#include <string>
#include <cfloat>
#include <iostream>

// Include the return object
#include "ObjectSelectorCore/TAccept.h"

// Include the pure ROOT tool
#include "wwwAnalysis/TMuonSelectorTool"

// Atlas includes
#include "EventKernel/INavigable4Momentum.h"


//=============================================================================
// Standard constructor
//=============================================================================
AthMuonSelectorTool::AthMuonSelectorTool( const std::string& type,
                                  const std::string& name,
                                  const IInterface* parent ):
 AthAlgTool(type, name, parent),
 m_rootTool(0)
{
  // Declare to the framework which interface this tools has
  declareInterface<IAthSelectorTool>(this);

  // Create an instance of the underlying ROOT tool
  m_rootTool = new Root::TMuonSelectorTool();
  // Declare the needed properties
  declareProperty( "ptMin",              m_rootTool->ptMin,              "Cut ptMin");
  declareProperty( "etaMax",              m_rootTool->etaMax,              "Cut etaMax");
  declareProperty( "EtIsoMax",              m_rootTool->EtIsoMax,              "Cut EtIsoMax");
  declareProperty( "PtIsoMax",              m_rootTool->PtIsoMax,              "Cut PtIsoMax");
  declareProperty( "z0ExpPVMax",              m_rootTool->z0ExpPVMax,              "Cut z0ExpPVMax");
}


//=============================================================================
// Standard destructor
//=============================================================================
AthMuonSelectorTool::~AthMuonSelectorTool()
{
  if ( m_rootTool ) delete m_rootTool;
}


//=============================================================================
// Athena initialize method
//=============================================================================
StatusCode AthMuonSelectorTool::initialize()
{
  // We need to initialize the underlying ROOT TSelectorTool
  if ( 0 == m_rootTool->initialize() )
    {
      ATH_MSG_ERROR ( "ERROR! Could not initialize the TMuonSelectorTool!" );
      return StatusCode::FAILURE;
    }

  return StatusCode::SUCCESS;
}


//=============================================================================
// Athena finalize method
//=============================================================================
StatusCode AthMuonSelectorTool::finalize()
{
  if ( !(m_rootTool->finalize()) )
    {
      ATH_MSG_ERROR ( "ERROR! Something went wrong at finalize!" );
      return StatusCode::FAILURE;
    }

  return StatusCode::SUCCESS;
}


//=============================================================================
// The main accept method: the actual cuts are applied here 
//=============================================================================
const Root::TAccept& AthMuonSelectorTool::accept( const INavigable4Momentum* part )
{
  if ( !part )
    {
      ATH_MSG_ERROR ( "Did not get a valid pointer!" );
      return m_acceptDummy;
    }


  // Here, you have to make the translation from the ATLAS EDM object to the variables of simple type
  return m_rootTool->accept( /*Here, you need to put your translation from the ATLAS EDM to the doubles*/ );
}

