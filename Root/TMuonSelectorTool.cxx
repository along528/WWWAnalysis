// Dear emacs, this is -*-c++-*-

/******************************************************************************
Name:        TMuonSelectorTool

Author:      Karsten Koeneke (CERN)
Created:     April 2011

Description: Example tool to select PhysicsObjects in pure ROOT
******************************************************************************/

// Preprocessor magic for debugging
#define XXX std::cout << "I am here: " << __FILE__ << ":" << __LINE__ << std::endl;

// This class header
#include "wwwAnalysis/TMuonSelectorTool.h"

// STL includes
#include <iostream>
#include <cfloat>
#include <math.h>

// ROOT includes
#include <TString.h>



//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::TMuonSelectorTool::TMuonSelectorTool(const char* name) :
  Root::TSelectorToolBase(name),
  CutPtIso(1),
  CutEtIso(1),
  CutD0(1),
  CutZ0(1),
  cutCombined(1),
  stacoLoose(0),
  stacoMedium(0),
  stacoTight(0),
  thirdMuLoose(0),
  thirdMuMedium(0),
  thirdMuTight(0),
  etaMax(DBL_MAX),
  bLayerHitsMin(0),
  pixelHitsMin(0),
  SCTHitsMin(0),
  SiHolesMax(DBL_MAX),
  TRTHitsMin(0),
  ptMin(0),
  ptIsoDeltaR20(0),
  z0ExpPVMax(DBL_MAX),
  PtIsoMax(DBL_MAX),
  PtIsoMin(-DBL_MAX),
  d0SigMax(DBL_MAX),
  z0SigMax(DBL_MAX),
  d0SigMin(-DBL_MAX),
  z0SigMin(-DBL_MAX),
  EtIsoMaxLowPt(DBL_MAX),
  EtIsoMinLowPt(-DBL_MAX),
  EtIsoMaxHighPt(DBL_MAX),
  EtIsoMinHighPt(-DBL_MAX),
  muDeltaRMin(-DBL_MAX),
  m_cutPositionStaco(-9),
  m_cutPositionThirdMu(-9),
  m_cutPositionStacoLoose(-9),
  m_cutPositionStacoMedium(-9),
  m_cutPositionStacoTight(-9),
  m_cutPositionThirdMuLoose(-9),
  m_cutPositionThirdMuMedium(-9),
  m_cutPositionThirdMuTight(-9),
  m_cutPositionCombined(-9),
  m_cutPositionEtaMax(-9),
  m_cutPositionBLayerHitsMin(-9),
  m_cutPositionPixelHitsMin(-9),
  m_cutPositionSCTHitsMin(-9),
  m_cutPositionSiHolesMax(-9),
  m_cutPositionTRT(-9),
  m_cutPositionPtMin(-9),
  m_cutPositionz0ExpPVMax(-9),
  m_cutPositiond0Significance(-9),
  m_cutPositionz0Significance(-9),
  m_cutPositionPtIso(-9),
  m_cutPositionEtIso(-9),
  m_cutPositionDuplicate(-9)
{
}



//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::TMuonSelectorTool::~TMuonSelectorTool()
{
}



//=============================================================================
// Initialize this selector tool
//=============================================================================
int wwwAnalysis::TMuonSelectorTool::initialize()
{
  // use an int as a StatusCode
  int sc(1);


  // --------------------------------------------------------------------------
  // Register the cuts and check that the registration worked:
  // NOTE: THE ORDER IS IMPORTANT!!! Cut0 corresponds to bit 0, Cut1 to bit 1,...


  if(thirdMuLoose || thirdMuMedium || thirdMuTight){ //Cut Third Muons
	  m_cutPositionThirdMu = m_accept.addCut( "ThirdMuons", Form("var = true") );
	  if ( m_cutPositionThirdMu < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  else{ // Cut Staco
	  m_cutPositionStaco = m_accept.addCut( "Staco", Form("var = true") );
	  if ( m_cutPositionStaco < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut Combined
  if(cutCombined){
    m_cutPositionCombined = m_accept.addCut( "Combined", Form("var = true") );
    if ( m_cutPositionCombined < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut Staco Loose
  if(stacoLoose)
  {
    m_cutPositionStacoLoose = m_accept.addCut( "Staco Loose", Form("var = true") );
    if ( m_cutPositionStacoLoose < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut Staco Medium
  if(stacoMedium)
  {
    m_cutPositionStacoMedium = m_accept.addCut( "Staco Medium", Form("var = true") );
    if ( m_cutPositionStacoMedium < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut Staco Tight
  if(stacoTight)
  {
    m_cutPositionStacoTight = m_accept.addCut( "Staco Tight", Form("var = true") );
    if ( m_cutPositionStacoTight < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut third chain Loose
  if(thirdMuLoose)
  {
    m_cutPositionThirdMuLoose = m_accept.addCut( "Third Mu Loose", Form("var = true") );
    if ( m_cutPositionThirdMuLoose < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut third chain Medium
  if(thirdMuMedium)
  {
    m_cutPositionThirdMuMedium = m_accept.addCut( "Third Mu Medium", Form("var = true") );
    if ( m_cutPositionThirdMuMedium < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut third chain Tight
  if(thirdMuTight)
  {
    m_cutPositionThirdMuTight = m_accept.addCut( "Third Mu Tight", Form("var = true") );
    if ( m_cutPositionThirdMuTight < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }

  // Cut ptMin
  m_cutPositionPtMin = m_accept.addCut( "ptMin", Form("var > %g", ptMin) );
  if ( m_cutPositionPtMin < 0 ) sc = 0; // Exceeded the number of allowed cuts

  /*****BEGIN Loose Inverted **********/
  if(CutPtIso){//just maintain order (other !cutLoose cuts later)
	  // Cut PtIso
	  m_cutPositionPtIso = m_accept.addCut( "PtIso", Form("%g < var < %g", PtIsoMin, PtIsoMax) );
	  if ( m_cutPositionPtIso < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }
  /***** END Loose Inverted **********/

  // Cut etaMax
  m_cutPositionEtaMax = m_accept.addCut( "etaMax", Form("var < %g", etaMax) );
  if ( m_cutPositionEtaMax < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut bLayerHitsMin
  m_cutPositionBLayerHitsMin = m_accept.addCut( "bLayerHitsMin", Form("var > %g",bLayerHitsMin) );
  if ( m_cutPositionBLayerHitsMin < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut pixelHitsMin
  m_cutPositionPixelHitsMin = m_accept.addCut( "pixelHitsMin", Form("var > %g",pixelHitsMin) );
  if ( m_cutPositionPixelHitsMin < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut SCTHitsMin
  m_cutPositionSCTHitsMin = m_accept.addCut( "SCTHitsMin", Form("var > %g",SCTHitsMin) );
  if ( m_cutPositionSCTHitsMin < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut SiHolesMax
  m_cutPositionSiHolesMax = m_accept.addCut( "SiHolesMax", Form("var < %g",SiHolesMax) );
  if ( m_cutPositionSiHolesMax < 0 ) sc = 0; // Exceeded the number of allowed cuts

  // Cut TRT
  m_cutPositionTRT = m_accept.addCut( "TRT", Form("var = pass") );
  if ( m_cutPositionTRT < 0 ) sc = 0; // Exceeded the number of allowed cuts


  /*****BEGIN Loose Inverted **********/

  if(CutEtIso){

	  // Cut EtIsoMax
	  m_cutPositionEtIso = m_accept.addCut( "EtIso", Form("var = pass") );
	  if ( m_cutPositionEtIso < 0 ) sc = 0; // Exceeded the number of allowed cuts
  }


	  //pbunbiased?

	  // Cut z0ExpPVMax
	  //m_cutPositionz0ExpPVMax = m_accept.addCut( "z0ExpPVMax", Form("var < %g", z0ExpPVMax) );
	  //if ( m_cutPositionz0ExpPVMax < 0 ) sc = 0; // Exceeded the number of allowed cuts

   if(CutD0){
	  // Cut d0 Significance
	  m_cutPositiond0Significance = m_accept.addCut( "d0Significance", Form("var < %g", d0SigMax) );
	  if ( m_cutPositiond0Significance < 0 ) sc = 0; // Exceeded the number of allowed cuts
    }

    if(CutZ0){
	  // Cut z0 Significance
	  std::cout << "Muon z0 sig max " << z0SigMax << std::endl;
	  m_cutPositionz0Significance = m_accept.addCut( "z0Significance", Form("var < %g", z0SigMax) );
	  if ( m_cutPositionz0Significance < 0 ) sc = 0; // Exceeded the number of allowed cuts
     }

  /*****END Loose Inverted **********/
  // Cut Duplicates
  m_cutPositionDuplicate = m_accept.addCut( "duplicate", Form(" ") );
  if ( m_cutPositionDuplicate < 0 ) sc = 0; // Exceeded the number of allowed cuts

  return sc;
}


//=============================================================================
// Calculate the actual accept of each cut individually.
//=============================================================================
const Root::TAccept& wwwAnalysis::TMuonSelectorTool::accept(const Muon &muon, const std::vector<wwwAnalysis::Muon> &mus)
{
  // Reset the cut result bits to zero (= fail cut)
  m_accept.clear();

  // -----------------------------------------------------------
  // Do the actual selection

  const D3PDReader::MuonD3PDObjectElement &data = muon.d3pd();

//  double eta = data.eta();//muon.momentum().Eta();
  double eta = muon.momentum().Eta();
  double pt = muon.momentum().Pt();


  // Cut Third Chain Combined *** Should already be STACO
  //m_accept.setCutResult( m_cutPositionStaco, true );//(data.author() == 6) ? true : false );
  if(thirdMuLoose || thirdMuMedium || thirdMuTight){
  	m_accept.setCutResult( m_cutPositionThirdMu, (data.author() == 6 || data.author()==12) ? true : false );  //combined Muid or Staco
  }
  else{ // Cut Staco Combined *** Should already be STACO
  	//m_accept.setCutResult( m_cutPositionStaco, true );//(data.author() == 6) ? true : false );
  	m_accept.setCutResult( m_cutPositionStaco, (data.author() == 6) ? true : false );
  }


  // Cut Combined Muon
  if(cutCombined){
    m_accept.setCutResult( m_cutPositionCombined, (data.isCombinedMuon()));
  }
  
  // Cut Staco Loose
  if(stacoLoose)
    m_accept.setCutResult( m_cutPositionStacoLoose, (stacoLoose > 0 && data.loose()) || (stacoLoose < 0 && !data.loose()));
  
  // Cut Staco Medium
  if(stacoMedium)
    m_accept.setCutResult( m_cutPositionStacoMedium, (stacoMedium > 0 && data.medium()) || (stacoMedium < 0 && !data.medium()));
  
  // Cut Staco Tight
  if(stacoTight)
    m_accept.setCutResult( m_cutPositionStacoTight, (stacoTight > 0 && data.tight()) || (stacoTight < 0 && !data.tight()));

  // Cut Third Mu  Loose
  if(thirdMuLoose)
    m_accept.setCutResult( m_cutPositionThirdMuLoose, (thirdMuLoose > 0 && data.loose()) || (thirdMuLoose < 0 && !data.loose()));
  
  // Cut Third Mu Medium
  if(thirdMuMedium)
    m_accept.setCutResult( m_cutPositionThirdMuMedium, (thirdMuMedium > 0 && data.medium()) || (thirdMuMedium < 0 && !data.medium()));
  
  // Cut Third Mu Tight
  if(thirdMuTight)
    m_accept.setCutResult( m_cutPositionThirdMuTight, (thirdMuTight > 0 && data.tight()) || (thirdMuTight < 0 && !data.tight()));

  // Cut ptMin
  m_accept.setCutResult( m_cutPositionPtMin, ( pt > ptMin) ? true : false );

  /*****BEGIN Loose Inverted **********/
  // Cut PtIsoMax
  if(CutPtIso){
	  double ptiso = data.ptcone30()/pt;
	  if (ptIsoDeltaR20) ptiso = data.ptcone20()/pt;
	  m_accept.setCutResult( m_cutPositionPtIso, ( ptiso < PtIsoMax && ptiso > PtIsoMin ) ? true : false );
  }
  /*****END Loose Inverted **********/
  
  // Cut etaMax
  m_accept.setCutResult( m_cutPositionEtaMax, ( fabs(eta) < etaMax ) ? true : false );
  // Cut bLayerHitsMin
//  m_accept.setCutResult( m_cutPositionBLayerHitsMin, data.nBLHits() > bLayerHitsMin);
  //Updated recommendations remove b-layer hit requirement
  m_accept.setCutResult( m_cutPositionBLayerHitsMin, true);//data.expectBLayerHit() == 0 || data.nBLHits() > bLayerHitsMin);
  // Cut pixelHitsMin
  m_accept.setCutResult( m_cutPositionPixelHitsMin, data.nPixHits() + data.nPixelDeadSensors() > pixelHitsMin);
  
  // Cut SCTHitsMin
  m_accept.setCutResult( m_cutPositionSCTHitsMin, data.nSCTHits() + data.nSCTDeadSensors() > SCTHitsMin);
  
  // Cut SiHolesMax
  m_accept.setCutResult( m_cutPositionSiHolesMax, data.nPixHoles() + data.nSCTHoles() < SiHolesMax);
  
  // Cut TRT
  double nTRT = data.nTRTHits() + data.nTRTOutliers();
  if((0.1 < fabs(eta)) && (fabs(eta) < 1.9))
    m_accept.setCutResult( m_cutPositionTRT, (nTRT > TRTHitsMin) && (data.nTRTOutliers() < 0.9*nTRT));
  //else if(nTRT > TRTHitsMin)  //updated requirements remove trt requirements outside 0.1 < |eta| < 1.9
  // m_accept.setCutResult( m_cutPositionTRT, data.nTRTOutliers() < 0.9*nTRT);
  else
    m_accept.setCutResult( m_cutPositionTRT, true);

    
  /*****BEGIN Loose Inverted **********/
  if(CutEtIso){
	  // Cut EtIsoMax
	  bool passEtIso = ( pt < 20000.  && muon.Etcone20_corr()/pt < EtIsoMaxLowPt  && muon.Etcone20_corr()/pt > EtIsoMinLowPt  ) ||
			   ( pt >= 20000. && muon.Etcone20_corr()/pt < EtIsoMaxHighPt && muon.Etcone20_corr()/pt > EtIsoMinHighPt );
	  m_accept.setCutResult( m_cutPositionEtIso, passEtIso );
   }

	  
   if(CutD0){
	  // Cut d0 Significance
	  bool cutd0=false;
	  if(d0SigMax>0)cutd0=(fabs(data.trackd0pvunbiased()/data.tracksigd0pvunbiased()) < d0SigMax);
	  else cutd0=(fabs(data.trackd0pvunbiased()/data.tracksigd0pvunbiased()) >= d0SigMax);
	  m_accept.setCutResult( m_cutPositiond0Significance, cutd0);
   }
   if(CutZ0){

	  // Cut z0 Significance
	  bool cutz0=false;
	  if(z0SigMax>0)cutz0=(fabs(data.trackz0pvunbiased()*sin(data.tracktheta())) < z0SigMax);
	  else cutz0=(fabs(data.trackz0pvunbiased()*sin(data.tracktheta())) >= z0SigMax);
	  m_accept.setCutResult( m_cutPositionz0Significance, cutz0);
   }
  /*****END Loose Inverted **********/

  // Cut duplicate
  bool overlap = false;
  for(unsigned int i = 0; i < mus.size() && !overlap; i++)
    //if(mus[i].momentum().DeltaR(muon.momentum()) < muDeltaRMin)
    if(deltaR(mus[i].d3pd().eta(),muon.d3pd().eta(),mus[i].d3pd().phi(),muon.d3pd().phi()) < muDeltaRMin)
      overlap = true;
  m_accept.setCutResult(m_cutPositionDuplicate, !overlap);

  return m_accept;
}
double wwwAnalysis::TMuonSelectorTool::deltaR(double eta1,double eta2, double phi1, double phi2)
{
  double deta = eta1- eta2;
  double  dphi = fabs(phi1-phi2);
  while(dphi > 2.*TMath::Pi())
    dphi -= 2.*TMath::Pi();
  if(dphi > TMath::Pi())
    dphi = 2.*TMath::Pi() - dphi;
  return sqrt(deta*deta + dphi*dphi);

}
