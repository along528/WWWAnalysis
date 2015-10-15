// Dear emacs, this is -*-c++-*-

#ifndef __TTAUSELECTORTOOL__
#define __TTAUSELECTORTOOL__

/**
   @class TTauSelectorTool
   @brief Example tool to select PhysicsObjects in pure ROOT

   @author Karsten Koeneke (CERN)
   @date   April 2011
*/


// ROOT includes
#include <TString.h>

// Include the return PhysicsObject and the base class
#include <PATCore/TAccept.h>
#include <PATCore/TSelectorToolBase.h>
#include <D3PDReader/TauD3PDObject.h>

#include "wwwAnalysis/Tau.h"
#include "wwwAnalysis/Muon.h"
#include "wwwAnalysis/Electron.h"

namespace wwwAnalysis {
  class TTauSelectorTool : public Root::TSelectorToolBase
  {

  public: 
    /** Standard constructor */
    TTauSelectorTool(const char* name="TTauSelectorTool");

    /** Standard destructor */
    virtual ~TTauSelectorTool();

#ifdef ROOTCORE
    /** For PROOF streaming */
    ClassDef(TTauSelectorTool,1);
#endif

    // Main methods
  public:
    /** Initialize this class */
    int initialize();

    /** Finalize this class; everything that should be done after the event loop should go here */
    inline int finalize() { return 1; };

    /** The main accept method: the actual cuts are applied here */
    const Root::TAccept& accept(const Tau &, const std::vector<wwwAnalysis::Electron> &, const std::vector<wwwAnalysis::Muon> &, const std::vector<wwwAnalysis::Tau> &);


    // Public members (the cut values)
  public:

    /** minimum  Et cut value */
    double EtMin;

    /** maximum  et cut value */
    double etaMax;

    /** minimum muonDeltaR */
    double tauDeltaRMin;

    /** minimum electronDeltaR */
    double elDeltaRMin;

    /** minimum muonDeltaR */
    double muDeltaRMin;

    // Private members
  private:

    /** Position of the author cut */
    int m_cutPositionAuthor;

    /** Position of the JetBDTSigMedium cut */
    int m_cutPositionJetBDTSigMedium;

    /** Position of the etaMax cut */
    int m_cutPositionEtaMax;

    /** Position of the EtMin cut */
    int m_cutPositionEtMin;

    /** Position of the numTrack cut */
    int m_cutPositionNumTrack;

    /** Position of the charge cut */
    int m_cutPositionCharge;

    /** Position of the EleBDTMedium cut */
    int m_cutPositionEleBDTMedium;

    /** Position of the muonVeto cut */
    int m_cutPositionMuonVeto;

    /** Position of the muon overlap cut */
    int m_cutPositionMuOverlap;

    /** Position of the electron overlap cut */
    int m_cutPositionElOverlap;

    /** Position of the duplicate cut */
    int m_cutPositionDuplicate;


  }; // End: class definition

} // End: namespace Root

#endif

