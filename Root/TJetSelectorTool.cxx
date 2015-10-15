// Dear emacs, this is -*-c++-*-

/******************************************************************************
Name:        TJetSelectorTool

Author:      Karsten Koeneke (CERN)
Created:     April 2011

Description: Example tool to select PhysicsObjects in pure ROOT
******************************************************************************/

// Preprocessor magic for debugging
#define XXX std::cout << "I am here: " << __FILE__ << ":" << __LINE__ << std::endl;

// This class header
#include "wwwAnalysis/TJetSelectorTool.h"

// STL includes
#include <iostream>
#include <cfloat>
#include <math.h>

#include <TLorentzVector.h>
// ROOT includes
#include <TString.h>



//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::TJetSelectorTool::TJetSelectorTool(const char* name) :
  Root::TSelectorToolBase(name),
  ptMin(-DBL_MAX),
  etaMax(DBL_MAX),
  jetDeltaRMin(-DBL_MAX),
  tauDeltaRMin(-DBL_MAX),
  elDeltaRMin(-DBL_MAX),
  muDeltaRMin(-DBL_MAX),
  m_cutPositionptMin(-9),
  m_cutPositionetaMax(-9),
  m_cutPositionJetClean(-9),
  m_cutPositionJVF(-9),
  m_cutPositionMuOverlap(-9),
  m_cutPositionElOverlap(-9),
  m_cutPositionTauOverlap(-9),
  m_cutPositionDuplicate(-9)
{
}



//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::TJetSelectorTool::~TJetSelectorTool()
{
}



//=============================================================================
// Initialize this selector tool
//=============================================================================
int wwwAnalysis::TJetSelectorTool::initialize()
{
  // use an int as a StatusCode
  int sc(1);


  // --------------------------------------------------------------------------
  // Register the cuts and check that the registration worked:
  // NOTE: THE ORDER IS IMPORTANT!!! Cut0 corresponds to bit 0, Cut1 to bit 1,...

  // Cut ElOverlap
  m_cutPositionElOverlap = m_accept.addCut( "electron overlap", Form(" ") );
  if ( m_cutPositionElOverlap < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut MuOverlap
  m_cutPositionMuOverlap = m_accept.addCut( "muon overlap", Form(" ") );
  if ( m_cutPositionMuOverlap < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut ptMin
  m_cutPositionptMin = m_accept.addCut( "ptMin", Form("var > %g", ptMin) );
  if ( m_cutPositionptMin < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut etaMax
  m_cutPositionetaMax = m_accept.addCut( "etaMax", Form("var < %g", etaMax) );
  if ( m_cutPositionetaMax < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut Jet Cleaning (turned off)
  //m_cutPositionJetClean = m_accept.addCut( "JetClean", Form("") );
  //if ( m_cutPositionJetClean < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut Jet Vertex Fraction (JVF)
  m_cutPositionJVF = m_accept.addCut( "JetVertexFraction", Form(" ") );
  if ( m_cutPositionJVF < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut Duplicates (turned off)
  //m_cutPositionDuplicate = m_accept.addCut( "duplicate", Form("") );
  //if ( m_cutPositionDuplicate < 0 ) sc = 0; // Exceeded the number of allowed cuts

  /*
  // Cut TauOverlap
  m_cutPositionTauOverlap = m_accept.addCut( "Tau overlap", Form("") );
  if ( m_cutPositionTauOverlap < 0 ) sc = 0; // Exceeded the number of allowed cuts
  */

  return sc;
}



//=============================================================================
// Calculate the actual accept of each cut individually.
//=============================================================================
const Root::TAccept& wwwAnalysis::TJetSelectorTool::accept(const Jet &jet, const std::vector<wwwAnalysis::Electron> &els, const std::vector<wwwAnalysis::Muon> &mus, const std::vector<wwwAnalysis::Tau> &taus, const std::vector<wwwAnalysis::Jet> &jets,bool cleanjet, JVFSys  sysJVF)
{
  // Reset the cut result bits to zero (= fail cut)
  m_accept.clear();

  // -----------------------------------------------------------
  // Do the actual selection
  // Cut electron overlap
  bool overlap = false;
  for(unsigned int i = 0; i < els.size() && !overlap; i++){

    //TLorentzVector elmom;
    //elmom.SetPtEtaPhiM(els[i].momentum().Pt(),els[i].d3pd().cl_eta(),els[i].d3pd().cl_phi(),0.);
    //if(elmom.DeltaR(jet.momentum()) < elDeltaRMin)
    if(deltaR(els[i].d3pd().cl_eta(),jet.d3pd().constscale_eta(),els[i].d3pd().cl_phi(),jet.d3pd().constscale_phi()) < elDeltaRMin)
      overlap = true;
    //if (overlap) std::cout << "EVENT OVERLAP ELECTRON " << els[i].momentum().Pt() << "\t" << jet.momentum().Pt() << "\t" << 
    //deltaR(els[i].d3pd().cl_eta(),jet.d3pd().constscale_eta(),els[i].d3pd().cl_phi(),jet.d3pd().constscale_phi()) << std::endl;
    //if(deltaR(els[i].d3pd().tracketa(),jet.d3pd().eta(),els[i].d3pd().trackphi(),jet.d3pd().phi()) < elDeltaRMin)
    //if(els[i].momentum().DeltaR(jet.momentum()) < elDeltaRMin)
  }

  //m_accept.setCutResult(m_cutPositionElOverlap, jet.btagged(Eff70) ||  !overlap);
  m_accept.setCutResult(m_cutPositionElOverlap, !overlap);

  // Cut muon overlap
  overlap = false;
  for(unsigned int i = 0; i < mus.size() && !overlap; i++){
    //TLorentzVector mumom;
    //mumom.SetPtEtaPhiM(mus[i].momentum().Pt(),mus[i].d3pd().eta(),mus[i].d3pd().phi(),0.);
    if(deltaR(mus[i].d3pd().eta(),jet.d3pd().constscale_eta(),mus[i].d3pd().phi(),jet.d3pd().constscale_phi()) < muDeltaRMin)
       overlap = true;
    //if (overlap) std::cout << "EVENT OVERLAP MUONS " << mus[i].momentum().Pt() << "\t" << jet.momentum().Pt() << "\t" << 
    //deltaR(mus[i].d3pd().eta(),jet.d3pd().constscale_eta(),mus[i].d3pd().phi(),jet.d3pd().constscale_phi()) << std::endl; 
    //if(mus[i].momentum().DeltaR(jet.momentum()) < muDeltaRMin)
     // overlap = true;
  }
  //m_accept.setCutResult(m_cutPositionMuOverlap, jet.btagged(Eff70) || !overlap);
  m_accept.setCutResult(m_cutPositionMuOverlap,  !overlap);

  // Cut ptMin
  m_accept.setCutResult( m_cutPositionptMin, jet.momentum().Pt() > ptMin );

  // Cut etaMax
  m_accept.setCutResult( m_cutPositionetaMax, fabs(jet.momentum().Eta()) < etaMax );
  //m_accept.setCutResult( m_cutPositionetaMax, fabs(jet.d3pd().emscale_eta()) < etaMax );

  // Cut jet cleaning
  
  /*
  bool isLooserBadJet = IsLooserBadJet(
			   jet.d3pd().pt(),
			   jet.d3pd().emscale_eta(),
			   jet.d3pd().sumPtTrk(),
			   jet.d3pd().LArQuality(),
			   jet.d3pd().NegativeE(),
			   jet.d3pd().emfrac(),
			   jet.d3pd().hecf(),
			   jet.d3pd().Timing(),
			   jet.d3pd().fracSamplingMax(),
			   jet.d3pd().HECQuality(),
			   jet.d3pd().AverageLArQF());

  m_accept.setCutResult( m_cutPositionJetClean, !isLooserBadJet );
  */

  // Cut JVF

  //should also add uncertainty using JVFUncertaintyTool
  //needs truth jet info
  m_accept.setCutResult(m_cutPositionJVF,jet.jvf(sysJVF));



  // Cut duplicate
  /*
  overlap = false;
  for(int i = 0; i < jets.size() && !overlap; i++)
    if(jets[i].momentum().DeltaR(jet.momentum()) < jetDeltaRMin)
      overlap = true;
  m_accept.setCutResult(m_cutPositionDuplicate, !overlap);
  */


  /*
  // Cut tau overlap
  overlap = false;
  for(int i = 0; i < taus.size() && !overlap; i++)
    if(taus[i].momentum().DeltaR(jet.momentum()) < tauDeltaRMin)
      overlap = true;
  m_accept.setCutResult(m_cutPositionTauOverlap, !overlap);
  */
  return m_accept;
}

bool wwwAnalysis::TJetSelectorTool::IsLooserBadJet(  const float  &pt,
		      const float  &eta,
		      const float  &sumPtTrk,
		      const float  &LArQuality,
		      const float  &NegativeE,
		      const float  &emfrac,
		      const float  &hecf,
		      const float  &Timing,
		      const float  &fracSamplingMax,
		      const float  &HECQuality,
		      const float  &AverageLArQF )
{

  /*
    @author Haifeng Li <Haifeng.Li@cern.ch>

    All the unit should be MeV.
    The pT should be container variables without smearing
    
  */

  float chf      = pt != 0 ? sumPtTrk/pt : 0 ;
  float LArQmean = AverageLArQF / 65535; // typo in twiki page 65335. It's a small effect

  // HEC spike
  if( hecf>0.5 && fabs(HECQuality)>0.5 && LArQmean>0.8)           return true;
  if( fabs(NegativeE)>60000./*MeV*/)                              return true;
  // EM coherent noise
  if( emfrac>0.95 && fabs(LArQuality)>0.8 && LArQmean>0.8 && fabs(eta)<2.8 )   return true;
  // Cosmics and Beam background
  if( emfrac<0.05 && chf<0.05 && fabs(eta)<2. )             return true;
  if( emfrac<0.05 && fabs(eta)>2. )                         return true;
  if( fracSamplingMax>0.99&&fabs(eta)<2)                    return true;
  return false;
}

double wwwAnalysis::TJetSelectorTool::deltaR(double eta1,double eta2, double phi1, double phi2)
{
  double deta = eta1- eta2;
  double  dphi = fabs(phi1-phi2);
  while(dphi > 2.*TMath::Pi())
    dphi -= 2.*TMath::Pi();
  if(dphi > TMath::Pi())
    dphi = 2.*TMath::Pi() - dphi;

  return sqrt(deta*deta + dphi*dphi);

}


