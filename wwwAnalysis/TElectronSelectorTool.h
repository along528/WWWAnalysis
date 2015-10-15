// Dear emacs, this is -*-c++-*-

#ifndef __TELECTRONSELECTORTOOL__
#define __TELECTRONSELECTORTOOL__

/**
   @class TElectronSelectorTool
   @brief Example tool to select PhysicsObjects in pure ROOT

   @author Karsten Koeneke (CERN)
   @date   April 2011
*/

// ROOT includes
#include <TString.h>

// Include the return PhysicsObject and the base class
#include <PATCore/TAccept.h>
#include <PATCore/TSelectorToolBase.h>
#include <D3PDReader/ElectronD3PDObject.h>

#include "wwwAnalysis/Electron.h"
#include "wwwAnalysis/Muon.h"

namespace wwwAnalysis {
  class TElectronSelectorTool : public Root::TSelectorToolBase
  {

  public: 
    /** Standard constructor */
    TElectronSelectorTool(const char* name="TElectronSelectorTool");

    /** Standard destructor */
    virtual ~TElectronSelectorTool();

#ifdef ROOTCORE
    /** For PROOF streaming */
    ClassDef(TElectronSelectorTool,1);
#endif

    // Main methods
  public:
    /** Initialize this class */
    int initialize();

    /** Finalize this class; everything that should be done after the event loop should go here */
    inline int finalize() { return 1; };

    /** The main accept method: the actual cuts are applied here */
    const Root::TAccept& accept(const Electron &, const std::vector<wwwAnalysis::Electron> &, const std::vector<wwwAnalysis::Muon> &);
    
    /** returns the ID set for scale factor calculations */
    int getId();

    // Public members (the cut values)
  public:
	double deltaR(double eta1,double eta2, double phi1, double phi2);

    /** Cut Et Iso */
    bool CutEtIso;

    /** Cut Pt Iso */
    bool CutPtIso;

    /** Cut Z0 sin theta */
    bool CutZ0;

    /** loose++ requirement */
    int loosePP;

    /** medium++ requirement */
    int mediumPP;

    /** tight++ requirement */
    int tightPP;


    /** veryLooseLL requirement */
    int veryLooseLL;
    /** looseLL requirement */
    int looseLL;

    /** mediumLL requirement */
    int mediumLL;

    /** tightLL requirement */
    int tightLL;

    /** veryTightLL requirement */
    int veryTightLL;

    /** minimum  pt cut value */
    double ptMin;

    /** maximum  et cut value */
    double etaMax;
    /** minimum  EtIso cut value high pt*/
    double EtIsoMinHighPt;
    /** maximum  EtIso cut value high pt*/
    double EtIsoMaxHighPt;

    /** maximum  EtIso cut value low pt*/
    double EtIsoMaxLowPt;

    /** minimum  EtIso cut value low pt*/
    double EtIsoMinLowPt;



    /** maximum  PtIso cut value */
    double PtIsoMax;

    /** minimum  PtIso cut value */
    double PtIsoMin;
    /** minimum  choose pt iso deltaR */
    bool ptIsoDeltaR20;

    /** minimum muonDeltaR */
    double muDeltaRMin;

    /** minimum electronDeltaR */
    double elDeltaRMin;

    /** maximum  d0 significance cut value */
    double d0SigMax;

    /** maximum  z0 significance cut value */
    double z0SigMax;

    // Private members
  private:

    /** Position of the author cut */
    int m_cutPositionAuthor;

    /** Position of the lose++ cut */
    int m_cutPositionLoosePP;

    /** Position of the medium++ cut */
    int m_cutPositionMediumPP;

    /** Position of the tight++ cut */
    int m_cutPositionTightPP;

    /** Position of the very lose ll cut */
    int m_cutPositionVeryLooseLL;

    /** Position of the loseLL cut */
    int m_cutPositionLooseLL;

    /** Position of the mediumll cut */
    int m_cutPositionMediumLL;

    /** Position of the tight ll cut */
    int m_cutPositionTightLL;

    /** Position of the very tight ll cut */
    int m_cutPositionVeryTightLL;

    /** Position of the OQ cut */
    int m_cutPositionOQ;

    /** Position of the EtaMax cut */
    int m_cutPositionEtaMax;

    /** Position of the ptMin cut */
    int m_cutPositionPtMin;

    /** Position of the EtIso cuts */
    int m_cutPositionEtIso;

    /** Position of the PtIso cut */
    int m_cutPositionPtIso;

    /** Position of the overlap cut */
    int m_cutPositionMuOverlap;

    /** Position of the overlap cut */
    int m_cutPositionJetOverlap;
    /** Position of the duplicate cut */
    int m_cutPositionDuplicate;

    /** Position of the d0 Signficance cut */
    int m_cutPositiond0Significance;

    /** Position of the z0 Signficance cut */
    int m_cutPositionz0Significance;


  }; // End: class definition

}; // End: namespace Root

#endif

