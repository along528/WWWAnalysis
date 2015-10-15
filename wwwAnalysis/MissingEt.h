#ifndef wwwAnalysis_MissingEt_h
#define wwwAnalysis_MissingEt_h

#include "wwwAnalysis/PhysicsObject.h"
#include "wwwAnalysis/Electron.h"
#include "wwwAnalysis/Muon.h"
#include "wwwAnalysis/Jet.h"
#include "MissingETUtility/METUtility.h"
#include "wwwAnalysis/SystematicsConfig.h"

#include <vector>

#include <TVector2.h>

namespace wwwAnalysis
{

  class MissingEt : public PhysicsObject
  {
    private:
      double m_fSumEtRaw;
      double m_fSumEt;
      double m_fSumEtSTVF;
      const D3PDReader::RefFinalMETD3PDObject *m_pD3PD;
      std::vector<float>* m_mu_energyLossPar_STVF;
      static void correctPt(TLorentzVector &, const TLorentzVector &, const TLorentzVector &);
      static METUtility *sm_pMETTool;
      static METUtility *sm_pMETSTVFTool;
      TLorentzVector m_oMomentumSTVF;
    public:
      /*  
       * Creates an Electron PhysicsObject, with corrected 4-momentum
       */
      MissingEt(const D3PDReader::Event &, const D3PDReader::RefFinalMETD3PDObject &, const std::vector<Electron> &, const std::vector<Muon> &, bool use_third_chain_muon, const std::vector<Jet> &,METSoftTermsSys = METSoftTermsSysOff);
      ~MissingEt();

      static void initialize();
      static bool initialized();

      void setMomentumSTVF(const TLorentzVector &);
      TLorentzVector momentumSTVF() const;
      /*  
       *
       */
      double Et() const;

      /*  
       *
       */
      double phi() const;

      /*
       */
      TVector2 pt() const;
      
      /*  
       *
       */
      double Ex() const;

      /*  
       *
       */
      double Ey() const;

      /*  
       *
       */
      double sumEt() const;
      double sumEtRaw() const;
      double sumEtSTVF() const;

      /*  
       * Returns the raw d3pd data
       */
      const D3PDReader::RefFinalMETD3PDObject &d3pd() const;

      ClassDef(MissingEt, 0);
  };
};



#endif
