#ifndef TRIGGER_TOOL_H
#define TRIGGER_TOOL_H

#include "wwwAnalysis/PhysicsObject.h"
#include <HSG4LepLepTriggerSF/HSG4LepLepTriggerSF.h>
#include <TrigMuonEfficiency/LeptonTriggerSF.h>
#include <TrigMuonEfficiency/MuonTriggerMatching.h>
#include <TrigMuonEfficiency/ElectronTriggerMatching.h>
#include <ElectronEfficiencyCorrection/TElectronEfficiencyCorrectionTool.h>
#include <D3PDReader/Event.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2F.h>
#include <string>
#include "wwwAnalysis/SystematicsConfig.h"

namespace wwwAnalysis
{
  class TriggerTool
  {
    private:
      static LeptonTriggerSF *sm_pLepTrigSFTool; //!
      MuonTriggerMatching *m_pMuonMatchingTool; //!
      ElectronTriggerMatching *m_pElectronMatchingTool; //!
      TriggerNavigationVariables *m_pTrigNavVars; //!
      
    public:
      TriggerTool();
      ~TriggerTool();
      
      static void initialize();
      static bool initialized();
      static void finalize();
      
      double triggerSF(unsigned int,  const vector<wwwAnalysis::PhysicsObject *> &,bool = false,wwwAnalysis::TriggerSFSys = TriggerSFSysOff);
      bool match( D3PDReader::Event *, const wwwAnalysis::PhysicsObject* ,string );
  };
};


#endif
