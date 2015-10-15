#ifndef wwwAnalysis_Electron_H
#define wwwAnalysis_Electron_H

#include <D3PDReader/Event.h>
//#include <egammaAnalysisUtils/EnergyRescaler.h>
#include <egammaAnalysisUtils/EnergyRescalerUpgrade.h>
#include <ElectronEfficiencyCorrection/TElectronEfficiencyCorrectionTool.h>
#include <ElectronPhotonSelectorTools/TElectronLikelihoodTool.h>

#include "wwwAnalysis/PhysicsObject.h"
#include "wwwAnalysis/SystematicsConfig.h"

namespace wwwAnalysis
{



  class Electron : public PhysicsObject
  {
    private:
      //static eg2011::EnergyRescaler *sm_pEnergyTool;
      static egRescaler::EnergyRescalerUpgrade *sm_pEnergyTool; //!
      static Root::TElectronEfficiencyCorrectionTool *sm_pSFTool_reco; //!
      static Root::TElectronEfficiencyCorrectionTool *sm_pSFTool_id; //!
      static Root::TElectronLikelihoodTool *sm_pElectronLLTool; //!

      bool m_bLoosePP;
      bool m_bMediumPP;
      bool m_bTightPP;

      bool m_bVeryLooseLL;
      bool m_bLooseLL;
      bool m_bMediumLL;
      bool m_bTightLL;
      bool m_bVeryTightLL;

      bool m_bIsSignalLike;
      bool m_bIsFromHeavyFlavor;
      bool m_bIsFromLightFlavor;
      bool m_bIsFromPhotonConversion;



      float m_fEtCone20;
      const D3PDReader::ElectronD3PDObjectElement *m_pD3PD;
      int m_iRun;

    public:

      /*
       * Initializes the global energy scaling tool.  TODO: add parameters to make this more adjustable
       */
      static void initialize();
      static bool initialized();
      
      /*
       * Finalizes the global energy scaling tool.
       */
      static void finalize();
      
      /*
       * Calculated the ID scale factor for the electron
       */
      //double getIdScaleFactor(const D3PDReader::Event &) const;
      double getIdScaleFactor(int) const;
      
      /*
       *
       */
      double scaleFactor(wwwAnalysis::ElectronEffSys = ElectronEffSysOff) const;

      /*
       * Creates an Electron PhysicsObject, with corrected 4-momentum
       */
      Electron();
      Electron(const D3PDReader::Event &, int, int nPV_2Trks, int, bool = false,wwwAnalysis::ElectronEnergyScaleSys = ElectronEnergyScaleSysOff,wwwAnalysis::ElectronEnergySmearingSys = ElectronEnergySmearingSysOff, double = -999.);


      /*
       *
       */
      float Etcone20_corr() const;

      bool loose() const;
      bool medium() const;
      bool tight() const;
      bool veryLooseLL() const;
      bool looseLL() const;
      bool mediumLL() const;
      bool tightLL() const;
      bool veryTightLL() const;

      bool isSignalLike() const;
      bool isFromHeavyFlavor() const;
      bool isFromLightFlavor() const;
      bool isFromPhotonConversion() const;
      
      /*
       * Returns the raw d3pd data
       */
      const D3PDReader::ElectronD3PDObjectElement &d3pd() const;
      
      ClassDef(Electron, 0);
  };

};



#endif
