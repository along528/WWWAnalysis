#ifndef wwwAnalysis_Muon_H
#define wwwAnalysis_Muon_H

#include <D3PDReader/Event.h>
#include <MuonMomentumCorrections/SmearingClass.h>
#include <MuonIsolationCorrection/CorrectCaloIso.h>
#include <MuonEfficiencyCorrections/AnalysisMuonConfigurableScaleFactors.h>

#include "wwwAnalysis/PhysicsObject.h"
#include "wwwAnalysis/SystematicsConfig.h"

namespace wwwAnalysis
{

  class Muon : public PhysicsObject
  {
    private:
      static MuonSmear::SmearingClass *sm_pStacoSmearingTool; //!
      static MuonSmear::SmearingClass *sm_pThirdMuSmearingTool; //!
      static Analysis::AnalysisMuonConfigurableScaleFactors *sm_pStacoSFTool; //!
      static Analysis::AnalysisMuonConfigurableScaleFactors *sm_pThirdMuSFTool; //!
      static CorrectCaloIso *sm_pCorrectIsoTool; //!

      float m_fEtCone20;
      float m_fPtMS;
      const D3PDReader::MuonD3PDObjectElement *m_pD3PD;

      bool  m_bUseThirdChainMuon;
      bool  m_bIsSpectroMuon;

      bool m_bIsSignalLike;
      bool m_bIsFromHeavyFlavor;
      bool m_bIsFromLightFlavor;
      bool m_bIsFromPhotonConversion;



    public:

      /*
       * Initializes the global smearing tool.  TODO: add parameters to make this more adjustable
       */
      static void initialize();
      static bool initialized();

      /*
       * Finalizes the global smearing tool.
       */
      static void finalize();

      /*
       * Creates a Muon PhysicsObject, with smeared pT if the event is Monte Carlo
       */
      Muon();
      Muon(const D3PDReader::Event &, int, bool,int nPV_3trks,bool=false,wwwAnalysis::MuonMomSys = MuonMomSysOff);

      /*
       * Gives the corrected isolation parameter
       */
      float Etcone20_corr() const;

      float ptms() const;

      bool useThirdChain() const ;
      bool isSpectroMuon() const ;
      bool isSignalLike() const;
      bool isFromHeavyFlavor() const;
      bool isFromLightFlavor() const;
      bool isFromPhotonConversion() const;
      
      /*
       *
       */
      double scaleFactor(wwwAnalysis::MuonEffSys  = MuonEffSysOff) const;

      /*
       * Returns the raw d3pd data
       */
      const D3PDReader::MuonD3PDObjectElement &d3pd() const;
      
      double GetScaleFactor(int p_charge, const TLorentzVector& p_rawMomentum);
//      bool isTag() const;
//      bool isProb() const;
      
      ClassDef(Muon, 0);
      

      
  };

};



#endif
