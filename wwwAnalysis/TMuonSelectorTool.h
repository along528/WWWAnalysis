// Dear emacs, this is -*-c++-*-

#ifndef __TMUONSELECTORTOOL__
#define __TMUONSELECTORTOOL__

/**
   @class TMuonSelectorTool
   @brief Example tool to select PhysicsObjects in pure ROOT

   @author Karsten Koeneke (CERN)
   @date   April 2011
*/


// ROOT includes
#include <TString.h>

// Include the return PhysicsObject and the base class
#include <PATCore/TAccept.h>
#include <PATCore/TSelectorToolBase.h>
#include <D3PDReader/MuonD3PDObject.h>

#include "wwwAnalysis/Muon.h"

namespace wwwAnalysis {
  class TMuonSelectorTool : public Root::TSelectorToolBase
  {

  public: 
    /** Standard constructor */
    TMuonSelectorTool(const char* name="TMuonSelectorTool");

    /** Standard destructor */
    virtual ~TMuonSelectorTool();

#ifdef ROOTCORE
    /** For PROOF streaming */
    ClassDef(TMuonSelectorTool,1);
#endif

    // Main methods
  public:
    /** Initialize this class */
    int initialize();

    /** Finalize this class; everything that should be done after the event loop should go here */
    inline int finalize() { return 1; };

    /** The main accept method: the actual cuts are applied here */
    const Root::TAccept& accept(const Muon &, const std::vector<wwwAnalysis::Muon> &);

    const bool useThirdMuonChain() { 
    	if (thirdMuLoose || thirdMuMedium || thirdMuTight) return true;
	return false;
    }
	double deltaR(double eta1,double eta2, double phi1, double phi2);

    // Public members (the cut values)
  public:
    /** cut Pt Iso **/
    int CutPtIso;

    /** cut Et Iso **/
    int CutEtIso;

    /** cut d0 significance**/
    int CutD0;

    /** cut z0 *sing theta**/
    int CutZ0;

    /** require combined muon */
    int cutCombined;

    /** require staco loose */
    int stacoLoose;

    /** require staco medium */
    int stacoMedium;

    /** require staco tight */
    int stacoTight;

    /** require third mu loose */
    int thirdMuLoose;

    /** require third mu medium */
    int thirdMuMedium;

    /** require thrid mu tight */
    int thirdMuTight;

    /** maximum  eta cut value */
    double etaMax;

    /** minimum b-layer hits value */
    double bLayerHitsMin;

    /** minimum pixel hits value */
    double pixelHitsMin;

    /** minimum SCT hits value */
    double SCTHitsMin;

    /** maximum Si holes value */
    double SiHolesMax;

    /** minimum TRT hits value */
    double TRTHitsMin;

    /** minimum  pt cut value */
    double ptMin;

    /** minimum  choose pt iso deltaR */
    bool ptIsoDeltaR20;

    /** maximum  z0ExpPV cut value */
    double z0ExpPVMax;

    /** maximum  PtIso cut value */
    double PtIsoMax;

    /** minimum  PtIso cut value */
    double PtIsoMin;

    /** maximum  d0 significance cut value */
    double d0SigMax;

    /** maximum  z0 significance cut value */
    double z0SigMax;

    /** minimum  d0 significance cut value */
    double d0SigMin;

    /** minimum  z0 significance cut value */
    double z0SigMin;

    /** maximum  EtIso cut value low pt*/
    double EtIsoMaxLowPt;

    /** minimum  EtIso cut value low pt*/
    double EtIsoMinLowPt;

    /** maximum  EtIso cut value high pt*/
    double EtIsoMaxHighPt;

    /** minimum  EtIso cut value high pt */
    double EtIsoMinHighPt;

    /** minimum muDeltaR cut value */
    double muDeltaRMin;

    // Private members
  private:
    
    /** Position of the staco requirements cut */
    int m_cutPositionStaco;

    /** Position of the thirdd muon requirements cut */
    int m_cutPositionThirdMu;

    /** Position of the staco loose requirements cut */
    int m_cutPositionStacoLoose;

    /** Position of the staco medium requirements cut */
    int m_cutPositionStacoMedium;

    /** Position of the staco tight requirements cut */
    int m_cutPositionStacoTight;

    /** Position of the third mu loose requirements cut */
    int m_cutPositionThirdMuLoose;

    /** Position of the third mu medium requirements cut */
    int m_cutPositionThirdMuMedium;

    /** Position of the third mu tight requirements cut */
    int m_cutPositionThirdMuTight;

    /** Position of the combined muon cut */
    int m_cutPositionCombined;

    /** Position of the etaMax cut */
    int m_cutPositionEtaMax;
    
    /** Position of the b-layer hits cut */
    int m_cutPositionBLayerHitsMin;

    /** Position of the pixel hits cut */
    int m_cutPositionPixelHitsMin;

    /** Position of the SCTHits cut */
    int m_cutPositionSCTHitsMin;

    /** Position of the SiHoles cut */
    int m_cutPositionSiHolesMax;

    /** Position of the TRT hits cut */
    int m_cutPositionTRT;

    /** Position of the ptMin cut */
    int m_cutPositionPtMin;

    /** Position of the z0ExpPVMax cut */
    int m_cutPositionz0ExpPVMax;

    /** Position of the d0 Signficance cut */
    int m_cutPositiond0Significance;

    /** Position of the z0 Signficance cut */
    int m_cutPositionz0Significance;

    /** Position of the PtIso cut */
    int m_cutPositionPtIso;

    /** Position of the EtIsoMax cut */
    int m_cutPositionEtIso;

    /** Position of the duplicate cut */
    int m_cutPositionDuplicate;

  }; // End: class definition

} // End: namespace Root

#endif
