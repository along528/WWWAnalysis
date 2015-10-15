#ifndef wwwAnalysis_Jet_H
#define wwwAnalysis_Jet_H

#include <D3PDReader/Event.h>
#include <ApplyJetCalibration/ApplyJetCalibration.h>
#include <CalibrationDataInterface/CalibrationDataInterfaceROOT.h>
#include <JetUncertainties/JESUncertaintyProvider.h>
#include <JetUncertainties/MultijetJESUncertaintyProvider.h>
//#include <JetResolution/JERProvider.h>
#include <ApplyJetResolutionSmearing/ApplyJetSmearing.h>

#include <JVFUncertaintyTool/JVFUncertaintyTool.h>

#include "wwwAnalysis/PhysicsObject.h"
#include "wwwAnalysis/SystematicsConfig.h"

//#include "TRandom.h"

namespace wwwAnalysis
{

  enum ShoweringGenerator{
  	Pythia6,
	Pythia8,
	HerwigJimmy,
	Sherpa,
	Herwigpp
  };
  enum BTagJetOperatingPoint{
  	Eff60,
	Eff70,
	Eff80,
	Eff85

  };

  class Jet : public PhysicsObject
  {
    private:
      static JetAnalysisCalib::JetCalibrationTool *sm_pDataCalibrationTool; //!
      static JetAnalysisCalib::JetCalibrationTool *sm_pMC12aCalibrationTool; //!
      static JetAnalysisCalib::JetCalibrationTool *sm_pMC12bFullSimCalibrationTool; //!
      static JetAnalysisCalib::JetCalibrationTool *sm_pMC12bAFIICalibrationTool; //!
      static ::Analysis::CalibrationDataInterfaceROOT *sm_pBJetScalingTool; //!
      static JESUncertaintyProvider *sm_pMC12aJESUncertaintyTool; //!
      static MultijetJESUncertaintyProvider *sm_pMC12aMultijetJESUncertaintyTool; //!
      static JVFUncertaintyTool *sm_pJVFUncTool; //!
      static JetSmearingTool  *sm_pJERSmearingTool; //!
      //static TRandom *sm_pRandom; //!

      const D3PDReader::JetD3PDObjectElement *m_pD3PD;

      int  m_iJetTagSFMapIndex;
      int  m_iJetContainerIndex;

    public:

      /*
       * Initializes the global calibration tools.  TODO: add parameters to make this more adjustable
       */
      static void initialize();
      
      static bool initialized();

      /*
       * Finalizes the global calibration tools.
       */
      static void finalize();

      /*
       * Creates a Jet PhysicsObject, with calibrated 4-momentum
       */
      Jet();
      Jet(const D3PDReader::EventInfoD3PDObject &, const D3PDReader::JetD3PDObjectElement &, int nPV_2trks, double mu,ShoweringGenerator gen,JESSys jesSys = JESSysOff, JetPileupSys = JetPileupSysOff,JetFlavorSys = JetFlavorSysOff, JetResolutionSys = JetResolutionSysOff, int JetIndex = -1,bool doPrint = false);

      /*
       * Returns the raw D3PD data
       */
      const D3PDReader::JetD3PDObjectElement &d3pd() const;

      double scaleFactor(BTagJetOperatingPoint,JetTagSFSys = JetTagSFSysOff,JVFSys = JVFSysOff) const;
      bool jvf(JVFSys = JVFSysOff) const;
      bool btagged(BTagJetOperatingPoint, JVFSys = JVFSysOff) const;


      
      ClassDef(Jet, 0);
  };

};



#endif
