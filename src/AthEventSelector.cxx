// Dear emacs, this is -*-c++-*-

/**
   @class AthEventSelector
   @brief Example tool to select objects in AthenaRootAccess using an underlying pure ROOT tool.

   @author Karsten Koeneke (CERN)
   @date   April 2011

*/

// Include this class's header
#include "wwwAnalysis/AthEventSelector.h"

// STL includes
#include <string>
#include <cfloat>
#include <iostream>

// Include the return object
#include "PATCore/TAccept.h"

// Include the pure ROOT tool
#include "wwwAnalysis/TEventSelector"

// Atlas includes
#include "EventKernel/INavigable4Momentum.h"


//=============================================================================
// Standard constructor
//=============================================================================
AthEventSelector::AthEventSelector( const std::string& type,
                                  const std::string& name,
                                  const IInterface* parent ):
 AthAlgTool(type, name, parent),
 m_rootTool(0)
{
  // Declare to the framework which interface this tools has
  declareInterface<IAthSelectorTool>(this);

  // Create an instance of the underlying ROOT tool
  m_rootTool = new Root::TEventSelector();
  // Declare the needed properties
  declareProperty( "llMassSFMin",              m_rootTool->llMassSFMin,              "Cut llMassSFMin");
  declareProperty( "llMassSFMax",              m_rootTool->llMassSFMax,              "Cut llMassSFMax");
  declareProperty( "llMassDFMin",              m_rootTool->llMassDFMin,              "Cut llMassDFMin");
  declareProperty( "llMassDFMax",              m_rootTool->llMassDFMax,              "Cut llMassDFMax");
  declareProperty( "sumPtMin",              m_rootTool->sumPtMin,              "Cut sumPtMin");
  declareProperty( "firstJetPtMin",              m_rootTool->firstJetPtMin,              "Cut firstJetPtMin");
  declareProperty( "metMin",              m_rootTool->metMin,              "Cut metMin");
  declareProperty( "hptoMetSFMin",              m_rootTool->hptoMetSFMin,              "Cut hptoMetSFMin");
  declareProperty( "hptoMetDFMin",              m_rootTool->hptoMetDFMin,              "Cut hptoMetDFMin");
  declareProperty( "xMin",              m_rootTool->xMin,              "Cut xMin");
  declareProperty( "xMax",              m_rootTool->xMax,              "Cut xMax");
  declareProperty( "llDeltaPhiMin",              m_rootTool->llDeltaPhiMin,              "Cut llDeltaPhiMin");
  declareProperty( "llDeltaPhiMax",              m_rootTool->llDeltaPhiMax,              "Cut llDeltaPhiMax");
  declareProperty( "secondJetPtMin",              m_rootTool->secondJetPtMin,              "Cut secondJetPtMin");
  declareProperty( "jjDeltaEtaMin",              m_rootTool->jjDeltaEtaMin,              "Cut jjDeltaEtaMin");
  declareProperty( "jjMassMin",              m_rootTool->jjMassMin,              "Cut jjMassMin");
  declareProperty( "jjMassMax",              m_rootTool->jjMassMax,              "Cut jjMassMax");
  declareProperty( "higgsPtMin",              m_rootTool->higgsPtMin,              "Cut higgsPtMin");
  declareProperty( "bTagVetoMV1Max",              m_rootTool->bTagVetoMV1Max,              "Cut bTagVetoMV1Max");
}


//=============================================================================
// Standard destructor
//=============================================================================
AthEventSelector::~AthEventSelector()
{
  if ( m_rootTool ) delete m_rootTool;
}


//=============================================================================
// Athena initialize method
//=============================================================================
StatusCode AthEventSelector::initialize()
{
  // We need to initialize the underlying ROOT TSelectorTool
  if ( 0 == m_rootTool->initialize() )
    {
      ATH_MSG_ERROR ( "ERROR! Could not initialize the TEventSelector!" );
      return StatusCode::FAILURE;
    }

  return StatusCode::SUCCESS;
}


//=============================================================================
// Athena finalize method
//=============================================================================
StatusCode AthEventSelector::finalize()
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
const Root::TAccept& AthEventSelector::accept( const INavigable4Momentum* part )
{
  if ( !part )
    {
      ATH_MSG_ERROR ( "Did not get a valid pointer!" );
      return m_acceptDummy;
    }


  // Here, you have to make the translation from the ATLAS EDM object to the variables of simple type
  return m_rootTool->accept( /*Here, you need to put your translation from the ATLAS EDM to the doubles*/ );
}

