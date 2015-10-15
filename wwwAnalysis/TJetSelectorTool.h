// Dear emacs, this is -*-c++-*-

#ifndef __TJETSELECTORTOOL__
#define __TJETSELECTORTOOL__

/**
   @class TJetSelectorTool
   @brief Example tool to select PhysicsObjects in pure ROOT

   @author Karsten Koeneke (CERN)
   @date   April 2011
*/


// ROOT includes
#include <TString.h>

// Include the return PhysicsObject and the base class
#include <PATCore/TAccept.h>
#include <PATCore/TSelectorToolBase.h>
#include <D3PDReader/JetD3PDObject.h>

#include "wwwAnalysis/Jet.h"
#include "wwwAnalysis/Muon.h"
#include "wwwAnalysis/Electron.h"
#include "wwwAnalysis/Tau.h"

namespace wwwAnalysis {
  class TJetSelectorTool : public Root::TSelectorToolBase
  {

  public: 
    /** Standard constructor */
    TJetSelectorTool(const char* name="TJetSelectorTool");

    /** Standard destructor */
    virtual ~TJetSelectorTool();

#ifdef ROOTCORE
    /** For PROOF streaming */
    ClassDef(TJetSelectorTool,1);
#endif

    // Main methods
  public:
    /** Initialize this class */
    int initialize();

    /** Finalize this class; everything that should be done after the event loop should go here */
    inline int finalize() { return 1; };

    /** The main accept method: the actual cuts are applied here */
    const Root::TAccept& accept(const Jet &, const std::vector<wwwAnalysis::Electron> &, const std::vector<wwwAnalysis::Muon> &, const std::vector<wwwAnalysis::Tau> &, const std::vector<wwwAnalysis::Jet> &,bool cleanjet, JVFSys  = JVFSysOff);

   bool IsLooserBadJet(  const float  &, const float  &, const float  &,
   			 const float  &, const float  &, const float  &,
   			 const float  &, const float  &, const float  &,
   			 const float  &, const float  &);

	double deltaR(double eta1,double eta2, double phi1, double phi2);


    // Public members (the cut values)
  public:

    /** minimum  pt cut value */
    double ptMin;

    /** maximum  et cut value */
    double etaMax;

    /** minimum muonDeltaR */
    double jetDeltaRMin;

    /** minimum electronDeltaR */
    double tauDeltaRMin;

    /** minimum muonDeltaR */
    double elDeltaRMin;

    /** minimum electronDeltaR */
    double muDeltaRMin;

    // Private members
  private:

    /** Position of the ptMin cut */
    int m_cutPositionptMin;


    /** Position of the etaMax cut */
    int m_cutPositionetaMax;

    /** Position of the Jet Cleaning cut */
    int m_cutPositionJetClean;

    /** Position of the JVF cut */
    int m_cutPositionJVF;

    /** Position of the muon overlap cut */
    int m_cutPositionMuOverlap;

    /** Position of the electron overlap cut */
    int m_cutPositionElOverlap;

    /** Position of the tau overlap cut */
    int m_cutPositionTauOverlap;

    /** Position of the duplicate cut */
    int m_cutPositionDuplicate;


  }; // End: class definition

} // End: namespace Root

#endif

