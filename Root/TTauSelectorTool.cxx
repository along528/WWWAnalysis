// Dear emacs, this is -*-c++-*-

/******************************************************************************
Name:        TTauSelectorTool

Author:      Karsten Koeneke (CERN)
Created:     April 2011

Description: Example tool to select PhysicsObjects in pure ROOT
******************************************************************************/

// Preprocessor magic for debugging
#define XXX std::cout << "I am here: " << __FILE__ << ":" << __LINE__ << std::endl;

// This class header
#include "wwwAnalysis/TTauSelectorTool.h"

// STL includes
#include <iostream>
#include <cfloat>
#include <math.h>

// ROOT includes
#include <TString.h>



//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::TTauSelectorTool::TTauSelectorTool(const char* name) :
  Root::TSelectorToolBase(name),
  EtMin(-DBL_MAX),
  etaMax(DBL_MAX),
  tauDeltaRMin(-DBL_MAX),
  elDeltaRMin(-DBL_MAX),
  muDeltaRMin(-DBL_MAX),
  m_cutPositionAuthor(-9),
  m_cutPositionJetBDTSigMedium(-9),
  m_cutPositionEtaMax(-9),
  m_cutPositionEtMin(-9),
  m_cutPositionNumTrack(-9),
  m_cutPositionCharge(-9),
  m_cutPositionEleBDTMedium(-9),
  m_cutPositionMuonVeto(-9),
  m_cutPositionMuOverlap(-9),
  m_cutPositionElOverlap(-9),
  m_cutPositionDuplicate(-9)
{
}



//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::TTauSelectorTool::~TTauSelectorTool()
{
}



//=============================================================================
// Initialize this selector tool
//=============================================================================
int wwwAnalysis::TTauSelectorTool::initialize()
{
  // use an int as a StatusCode
  int sc(1);


  // --------------------------------------------------------------------------
  // Register the cuts and check that the registration worked:
  // NOTE: THE ORDER IS IMPORTANT!!! Cut0 corresponds to bit 0, Cut1 to bit 1,...

  // Cut author
  m_cutPositionAuthor = m_accept.addCut( "author", Form("var = 1|3") );
  if ( m_cutPositionAuthor < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut JetBDTSigMedium
  m_cutPositionJetBDTSigMedium = m_accept.addCut( "JetBDTSigMedium", Form("var = 1") );
  if ( m_cutPositionJetBDTSigMedium < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut etaMax
  //m_cutPositionEtaMax = m_accept.addCut( "etaMax", Form("var < %g", etaMax) );
  m_cutPositionEtaMax = m_accept.addCut( "etaMax", Form(" ") );
  if ( m_cutPositionEtaMax < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut EtMi
  m_cutPositionEtMin = m_accept.addCut( "EtMin", Form("var > %g", EtMin) );
  if ( m_cutPositionEtMin < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut numTracks
  m_cutPositionNumTrack = m_accept.addCut( "numTrack", Form("var = 1|3") );
  if ( m_cutPositionNumTrack < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut charge
  m_cutPositionCharge = m_accept.addCut( "charge", Form("var = 1") );
  if ( m_cutPositionCharge < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut EleBDTMedium
  m_cutPositionEleBDTMedium = m_accept.addCut( "EleBDTMedium", Form("var = 0") );
  if ( m_cutPositionEleBDTMedium < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut muonVeto
  m_cutPositionMuonVeto = m_accept.addCut( "muonVeto", Form("var = 0") );
  if ( m_cutPositionMuonVeto < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut MuOverlap
  m_cutPositionMuOverlap = m_accept.addCut( "muon overlap", Form(" ") );
  if ( m_cutPositionMuOverlap < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut ElOverlap
  m_cutPositionElOverlap = m_accept.addCut( "electron overlap", Form(" ") );
  if ( m_cutPositionElOverlap < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut Duplicates
  m_cutPositionDuplicate = m_accept.addCut( "duplicate", Form(" ") );
  if ( m_cutPositionDuplicate < 0 ) sc = 0; // Exceeded the number of allowed cuts


  return sc;
}



//=============================================================================
// Calculate the actual accept of each cut individually.
//=============================================================================
const Root::TAccept& wwwAnalysis::TTauSelectorTool::accept(const Tau &tau, const std::vector<wwwAnalysis::Electron> &els, const std::vector<wwwAnalysis::Muon> &mus, const std::vector<wwwAnalysis::Tau> &taus)
{
  // Reset the cut result bits to zero (= fail cut)
  m_accept.clear();

  // -----------------------------------------------------------
  // Do the actual selection

  // Cut author
  m_accept.setCutResult( m_cutPositionAuthor, tau.d3pd().author() == 1 || tau.d3pd().author() == 3 );
  // Cut JetBDTSigMedium
  m_accept.setCutResult( m_cutPositionJetBDTSigMedium, tau.d3pd().JetBDTSigMedium() == 1 );
  // Cut etaMax
//  m_accept.setCutResult( m_cutPositionEtaMax, (fabs(tau.momentum().Eta()) < 2.47) && (tau.d3pd().track_n() > 0) && (fabs(tau.d3pd().track_eta().at(0)) < 2.47) );
//For WZ:
  m_accept.setCutResult( m_cutPositionEtaMax, (fabs(tau.momentum().Eta()) < 2.47) && (tau.d3pd().track_n() > 0) );
  // Cut EtMin
  m_accept.setCutResult( m_cutPositionEtMin, tau.momentum().Et() > EtMin );
  // Cut numTrack
  m_accept.setCutResult( m_cutPositionNumTrack, tau.d3pd().numTrack() == 1 || tau.d3pd().numTrack() == 3 );
  // Cut charge
  m_accept.setCutResult( m_cutPositionCharge, fabs(tau.d3pd().charge()) == 1 );
  // Cut EleBDTMedium
  m_accept.setCutResult( m_cutPositionEleBDTMedium, tau.d3pd().EleBDTMedium() == 0 );
  // Cut muonVeto
  m_accept.setCutResult( m_cutPositionMuonVeto, tau.d3pd().muonVeto() == 0 );
  // Cut muon overlap
  bool overlap = false;
  for(unsigned int i = 0; i < mus.size() && !overlap; i++)
    if(mus[i].momentum().DeltaR(tau.momentum()) < muDeltaRMin)
      overlap = true;
  m_accept.setCutResult(m_cutPositionMuOverlap, !overlap);
  // Cut electron overlap
  overlap = false;
  for(unsigned int i = 0; i < els.size() && !overlap; i++)
    if(els[i].momentum().DeltaR(tau.momentum()) < elDeltaRMin)
      overlap = true;
  m_accept.setCutResult(m_cutPositionElOverlap, !overlap);
  // Cut duplicate
  overlap = false;
  for(unsigned int i = 0; i < taus.size() && !overlap; i++)
    if(taus[i].momentum().DeltaR(tau.momentum()) < tauDeltaRMin)
      overlap = true;
  m_accept.setCutResult(m_cutPositionDuplicate, !overlap);


  return m_accept;
}

