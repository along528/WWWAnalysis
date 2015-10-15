// Dear emacs, this is -*-c++-*-

/******************************************************************************
Name:        TElectronSelectorTool

Author:      Karsten Koeneke (CERN)
Created:     April 2011

Description: Example tool to select PhysicsObjects in pure ROOT
******************************************************************************/

// Preprocessor magic for debugging
#define XXX std::cout << "I am here: " << __FILE__ << ":" << __LINE__ << std::endl;

// This class header
#include "wwwAnalysis/TElectronSelectorTool.h"

// STL includes
#include <iostream>
#include <cfloat>
#include <math.h>

// ROOT includes
#include <TString.h>



//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::TElectronSelectorTool::TElectronSelectorTool(const char* name) :
  Root::TSelectorToolBase(name),
  CutPtIso(1),
  CutEtIso(1),
  CutZ0(1),
  loosePP(0),
  mediumPP(0),
  tightPP(0),
  veryLooseLL(0),
  looseLL(0),
  mediumLL(0),
  tightLL(0),
  veryTightLL(0),
  ptMin(-DBL_MAX),
  etaMax(DBL_MAX),
  EtIsoMinHighPt(-DBL_MAX),
  EtIsoMaxHighPt(DBL_MAX),
  EtIsoMaxLowPt(DBL_MAX),
  EtIsoMinLowPt(-DBL_MAX),
  PtIsoMax(DBL_MAX),
  PtIsoMin(-DBL_MAX),
  ptIsoDeltaR20(0),
  muDeltaRMin(-DBL_MAX),
  elDeltaRMin(-DBL_MAX),
  d0SigMax(-DBL_MAX),
  z0SigMax(-DBL_MAX),
  m_cutPositionAuthor(-9),
  m_cutPositionLoosePP(-9),
  m_cutPositionMediumPP(-9),
  m_cutPositionTightPP(-9),
  m_cutPositionVeryLooseLL(-9),
  m_cutPositionLooseLL(-9),
  m_cutPositionMediumLL(-9),
  m_cutPositionTightLL(-9),
  m_cutPositionVeryTightLL(-9),
  m_cutPositionOQ(-9),
  m_cutPositionEtaMax(-9),
  m_cutPositionPtMin(-9),
  m_cutPositionEtIso(-9),
  m_cutPositionPtIso(-9),
  m_cutPositionMuOverlap(-9),
  m_cutPositionDuplicate(-9),
  m_cutPositiond0Significance(-9),
  m_cutPositionz0Significance(-9)
{
}



//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::TElectronSelectorTool::~TElectronSelectorTool()
{
}



//=============================================================================
// Initialize this selector tool
//=============================================================================
int wwwAnalysis::TElectronSelectorTool::initialize()
{
  // use an int as a StatusCode
  int sc(1);


  // --------------------------------------------------------------------------
  // Register the cuts and check that the registration worked:
  // NOTE: THE ORDER IS IMPORTANT!!! Cut0 corresponds to bit 0, Cut1 to bit 1,...
  std::cout << "ELECTRON SELECTOR TOOL " << loosePP << mediumPP << tightPP << veryLooseLL << looseLL << mediumLL << tightLL << veryTightLL << std::endl;

  // Cut author
  m_cutPositionAuthor = m_accept.addCut( "author", Form("author = 1 || 3") );
  if ( m_cutPositionAuthor < 0 ) sc = 0; // Exceeded the number of allowed cuts
  // Cut etaMax
  m_cutPositionEtaMax = m_accept.addCut( "etaMax", Form("var < %g", etaMax) );
  if ( m_cutPositionEtaMax < 0 ) sc = 0; // Exceeded the number of allowed cuts
  // Cut OQ
  m_cutPositionOQ = m_accept.addCut( "OQ", Form("OQ&1446 = 0") );
  if ( m_cutPositionOQ < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut ptMin
  m_cutPositionPtMin = m_accept.addCut( "ptMin", Form("var < %g", ptMin) );
  if ( m_cutPositionPtMin < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut loose++
  if(loosePP) {
    m_cutPositionLoosePP = m_accept.addCut( "loose++", Form("loose++ = %s",loosePP > 0 ? "true" : "false") );
    if ( m_cutPositionLoosePP < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut medium++
  if(mediumPP) {
    m_cutPositionMediumPP = m_accept.addCut( "medium++", Form("medium++ = %s",mediumPP > 0 ? "true" : "false") );
    if ( m_cutPositionMediumPP < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut tight++
  if(tightPP) {
    m_cutPositionTightPP = m_accept.addCut( "tight++", Form("tight++ = %s",tightPP > 0 ? "true" : "false") );
    if ( m_cutPositionTightPP < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut Log-Likelihood very tight
  if(veryTightLL) {
    m_cutPositionVeryTightLL = m_accept.addCut( "veryTightLL", Form("veryTightLL = %s",veryTightLL > 0 ? "true" : "false") );
    if ( m_cutPositionVeryTightLL < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut Log-Likelihood tight
  if(tightLL) {
    m_cutPositionTightLL = m_accept.addCut( "tightLL", Form("tightLL = %s",tightLL > 0 ? "true" : "false") );
    if ( m_cutPositionTightLL < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut Log-Likelihood medium
  if(mediumLL) {
    m_cutPositionMediumLL = m_accept.addCut( "mediumLL", Form("mediumLL = %s",mediumLL > 0 ? "true" : "false") );
    if ( m_cutPositionMediumLL < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  // Cut Log-Likelihood loose
  if(looseLL) {
    m_cutPositionLooseLL = m_accept.addCut( "looseLL", Form("looseLL = %s",looseLL > 0 ? "true" : "false") );
    if ( m_cutPositionLooseLL < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut Log-Likelihood very loose
  if(veryLooseLL) {
    m_cutPositionVeryLooseLL = m_accept.addCut( "veryLooseLL", Form("veryLooseLL = %s",veryLooseLL > 0 ? "true" : "false") );
    if ( m_cutPositionVeryLooseLL < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut d0 Significance
  m_cutPositiond0Significance = m_accept.addCut( "d0Significance", Form("var < %g", d0SigMax) );
  if ( m_cutPositiond0Significance < 0 ) sc = 0; // Exceeded the number of allowed cuts

  /***** BEGIN Loose Inversion ******/
  if(CutEtIso){
	  // Cut EtIso
	  m_cutPositionEtIso = m_accept.addCut( "EtIso", Form("var pass") );
	  if ( m_cutPositionEtIso < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  if(CutPtIso){

	  // Cut PtIsoMax
	  m_cutPositionPtIso = m_accept.addCut( "PtIso", Form("%g < var < %g", PtIsoMin, PtIsoMax) );
	  if ( m_cutPositionPtIso < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }


  if(CutZ0){
	  // Cut z0 Significance
	  std::cout << "Electron z0 sig max " << z0SigMax << std::endl;
	  m_cutPositionz0Significance = m_accept.addCut( "z0Significance", Form("var < %g", z0SigMax) );
	  if ( m_cutPositionz0Significance < 0 ) sc = 0; // Exceeded the number of allowed cuts

  }
  /***** END Loose Inversion ******/
  // Cut Overlap
  m_cutPositionMuOverlap = m_accept.addCut( "muon overlap", Form(" ") );
  if ( m_cutPositionMuOverlap < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut Duplicates
  m_cutPositionDuplicate = m_accept.addCut( "duplicate", Form(" ") );
  if ( m_cutPositionDuplicate < 0 ) sc = 0; // Exceeded the number of allowed cuts


  return sc;
}


int wwwAnalysis::TElectronSelectorTool::getId()
{
	//this could be used to get the appropriate scale factor configuration
	//should include log likelihood version
	if(tightPP) return 7;
	else if(mediumPP) return 6;
	else if(loosePP) return 5;

	return -1;
}
//=============================================================================
// Calculate the actual accept of each cut individually.
//=============================================================================
const Root::TAccept& wwwAnalysis::TElectronSelectorTool::accept(const wwwAnalysis::Electron &el, const std::vector<wwwAnalysis::Electron> &els, const std::vector<wwwAnalysis::Muon> &mus)
{
  // Reset the cut result bits to zero (= fail cut)
  m_accept.clear();

  // -----------------------------------------------------------
  // Do the actual selection
  const D3PDReader::ElectronD3PDObjectElement &data = el.d3pd();
  double pt = el.momentum().Pt();

  // Cut author
  m_accept.setCutResult( m_cutPositionAuthor, ( data.author() == 1 || data.author() == 3 ) ? true : false );
  // Cut etaMax
  double eta = data.cl_eta();//el.momentum().Eta();
  //double eta = el.momentum().Eta();
  m_accept.setCutResult( m_cutPositionEtaMax, ( fabs(eta) < etaMax && !(fabs(eta) >= 1.37 && fabs(eta) <= 1.52) ) ? true : false );
  // Cut OQ
  m_accept.setCutResult( m_cutPositionOQ, ( (data.OQ()&1446) == 0 ) ? true : false );
  // Cut ptMin
  m_accept.setCutResult( m_cutPositionPtMin, ( pt > ptMin ) ? true : false );
  // Cut loose++
  if(loosePP)
    m_accept.setCutResult( m_cutPositionLoosePP, (loosePP > 0 && el.loose()) || (loosePP < 0 && !el.loose()));
  // Cut medium++
  if(mediumPP)
    m_accept.setCutResult( m_cutPositionMediumPP, (mediumPP > 0 && el.medium()) || (mediumPP < 0 && !el.medium()));
  // Cut tight++
  if(tightPP)
    m_accept.setCutResult( m_cutPositionTightPP, (tightPP > 0 && el.tight()) || (tightPP < 0 && !el.tight()));
  // Cut log likelihood very loose
  if(veryLooseLL)
    m_accept.setCutResult( m_cutPositionVeryLooseLL, (veryLooseLL > 0 && el.veryLooseLL()) || (veryLooseLL < 0 && !el.veryLooseLL()));
  // Cut log likelihood loose
  if(looseLL)
    m_accept.setCutResult( m_cutPositionLooseLL, (looseLL > 0 && el.looseLL()) || (looseLL < 0 && !el.looseLL()));
  // Cut log likelihood medium
  if(mediumLL)
    m_accept.setCutResult( m_cutPositionMediumLL, (mediumLL > 0 && el.mediumLL()) || (mediumLL < 0 && !el.mediumLL()));
  // Cut log likelihood tight
  if(tightLL)
    m_accept.setCutResult( m_cutPositionTightLL, (tightLL > 0 && el.tightLL()) || (tightLL < 0 && !el.tightLL()));
  // Cut log likelihood very tight
  if(veryTightLL)
    m_accept.setCutResult( m_cutPositionVeryTightLL, (veryTightLL > 0 && el.veryTightLL()) || (veryTightLL < 0 && !el.veryTightLL()));

  // Cut d0 Significance
  bool cutd0=false;
  if(d0SigMax>0)cutd0=(fabs(data.trackd0pvunbiased()/data.tracksigd0pvunbiased()) < d0SigMax);
  else cutd0=(fabs(data.trackd0pvunbiased()/data.tracksigd0pvunbiased()) >= d0SigMax);
  m_accept.setCutResult( m_cutPositiond0Significance, cutd0);
  //  m_accept.setCutResult( m_cutPositiond0Significance, 
  //   ( fabs(data.trackd0pvunbiased()/data.tracksigd0pvunbiased()) < d0SigMax ) ? true : false);


  if(CutEtIso){

	  // Cut EtIsoMax
	  bool passEtIso = ( pt < 20000.  && el.Etcone20_corr()/pt < EtIsoMaxLowPt  && el.Etcone20_corr()/pt > EtIsoMinLowPt  ) ||
			   ( pt >= 20000. && el.Etcone20_corr()/pt < EtIsoMaxHighPt && el.Etcone20_corr()/pt > EtIsoMinHighPt );
	  m_accept.setCutResult( m_cutPositionEtIso, passEtIso );
  }
  if(CutPtIso){
	  // Cut PtIsoMax
	  double ptiso = data.ptcone30()/pt;
	  if (ptIsoDeltaR20) ptiso = data.ptcone20()/pt;
	  m_accept.setCutResult( m_cutPositionPtIso, ( ptiso < PtIsoMax && ptiso > PtIsoMin ) ? true : false );
  }

  if(CutZ0){
	  // Cut z0 Significance
	  bool cutz0=false;
	  if(z0SigMax>0)cutz0=(fabs(data.trackz0pvunbiased()*sin(data.tracktheta())) < z0SigMax);
	  else cutz0=(fabs(data.trackz0pvunbiased()*sin(data.tracktheta())) >= z0SigMax);
	  m_accept.setCutResult( m_cutPositionz0Significance, cutz0);
	//  m_accept.setCutResult( m_cutPositionz0Significance, 
	//  ( fabs(data.trackz0pvunbiased()*sin(data.tracktheta())) < z0SigMax ) ? true : false);

  }
  // Cut muon overlap
  bool overlap = false;
  for(unsigned int i = 0; i < mus.size() && !overlap; i++)
    if(deltaR(el.d3pd().cl_eta(),mus[i].d3pd().eta(),el.d3pd().cl_phi(),mus[i].d3pd().phi()) < muDeltaRMin)
      overlap = true;
    //if(mus[i].momentum().DeltaR(el.momentum()) < muDeltaRMin)
  m_accept.setCutResult(m_cutPositionMuOverlap, !overlap);
  // Cut duplicate
  overlap = false;
  for(unsigned int i = 0; i < els.size() && !overlap; i++)
    if(deltaR(els[i].d3pd().cl_eta(),el.d3pd().cl_eta(),els[i].d3pd().cl_phi(),el.d3pd().cl_phi()) < elDeltaRMin)
    //if(els[i].momentum().DeltaR(el.momentum()) < elDeltaRMin)
      overlap = true;
  m_accept.setCutResult(m_cutPositionDuplicate, !overlap);


  return m_accept;
}

double wwwAnalysis::TElectronSelectorTool::deltaR(double eta1,double eta2, double phi1, double phi2)
{
  double deta = eta1- eta2;
  double  dphi = fabs(phi1-phi2);
  while(dphi > 2.*TMath::Pi())
    dphi -= 2.*TMath::Pi();
  if(dphi > TMath::Pi())
    dphi = 2.*TMath::Pi() - dphi;
  return sqrt(deta*deta + dphi*dphi);

}
