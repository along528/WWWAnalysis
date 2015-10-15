#ifndef wwwAnalysis_PhysicsObject_h
#define wwwAnalysis_PhysicsObject_h

#include <TLorentzVector.h>
#include <D3PDReader/Event.h>

namespace wwwAnalysis
{
  enum ParticleType
  {
    ELECTRON = 0,
    MUON,
    TAU,
    JET,
    PHOTON,
    MISSING_ET
  };

  class PhysicsObject : public TObject
  {
    private:
      const D3PDReader::EventInfoD3PDObject *m_pEventInfo;
      TLorentzVector m_oMomentum;
      TLorentzVector m_oRawMomentum;
      ParticleType m_eType;
      double m_fCharge;
      bool m_bFake;
      bool m_bIsChargeFlipped;
      int m_iIndex;
    protected:
    	PhysicsObject();
    public:
      PhysicsObject(const D3PDReader::EventInfoD3PDObject &, ParticleType type, bool = false,int = -1);

      void setMomentum(const TLorentzVector &);
      void setMomentum(const TLorentzVector &, const TLorentzVector &);
      void setCharge(double);
      void setMomentumOri(const TLorentzVector &);
      void flipCharge();
      void setFakeStatus(bool);
    public:
      int index() const;
      bool isChargeFlipped() const ;
      TLorentzVector rawMomentum() const;
      TLorentzVector momentum() const;
      double charge() const;
      bool fake() const;
      virtual double scaleFactor() const;
      ParticleType type() const;

      const D3PDReader::EventInfoD3PDObject &eventInfo() const;
      
      ClassDef(PhysicsObject, 0);


      bool isTrueElecMatch(int mc_channel_number, int Type, int Typebkg, int Originbkg, int choice);
      bool isTrueMuonMatch(int mc_channel_number, int Type, int choice);

  };

};

namespace FakeComposition{
  enum ParticleType {
    Unknown         =  0, 
    UnknownElectron =  1, 
    IsoElectron     =  2,
    NonIsoElectron  =  3,
    BkgElectron     =  4,
    UnknownMuon     =  5, 
    IsoMuon         =  6,
    NonIsoMuon      =  7,
    BkgMuon         =  8,
    UnknownTau      =  9, 
    IsoTau          =  10,
    NonIsoTau       =  11,
    BkgTau          =  12,
    UnknownPhoton   =  13, 
    IsoPhoton       =  14,
    NonIsoPhoton    =  15,
    BkgPhoton       =  16,
    Hadron          =  17,
    Neutrino        =  18,
    NuclFrag        =  19,
    NonPrimary      =  20,
    GenParticle     =  21,
    SUSYParticle    =  22 
  };
  
  enum ParticleOrigin {
    
    NonDefined    = 0,	
    SingleElec    = 1,
    SingleMuon    = 2,
    SinglePhot    = 3,
    SingleTau     = 4,
    PhotonConv    = 5,
    DalitzDec     = 6,
    ElMagProc     = 7,
    Mu            = 8,
    TauLep        = 9,
    top           = 10,
    QuarkWeakDec  = 11,
    WBoson        = 12,
    ZBoson        = 13,
    Higgs         = 14,
    HiggsMSSM     = 15,
    HeavyBoson    = 16,
    WBosonLRSM    = 17,
    NuREle        = 18,
    NuRMu         = 19,
    NuRTau        = 20,
    LQ            = 21,	
    SUSY          = 22,
    LightMeson    = 23,
    StrangeMeson  = 24,
    CharmedMeson  = 25,
    BottomMeson   = 26,
    CCbarMeson    = 27,
    JPsi          = 28,
    BBbarMeson    = 29, 
    LightBaryon   = 30,
    StrangeBaryon = 31,
    CharmedBaryon = 32, 
    BottomBaryon  = 33,
    PionDecay     = 34,
    KaonDecay     = 35,
    BremPhot      = 36,
    PromptPhot    = 37,
    UndrPhot      = 38,
    ISRPhot       = 39,
    FSRPhot       = 40, 
    NucReact      = 41,
    PiZero        = 42,
    DiBoson       = 43,
    ZorHeavyBoson = 44
  };
  
  enum ParticleOutCome {
    NonDefinedOutCome  =  0, 
    UnknownOutCome     =  1, 
    UnConverted        =  2,
    Converted          =  3,
    NonInteract        =  4,
    NuclInteraction    =  5,
    ElectrMagInter     =  6,
    DecaytoElectron    =  7,
    DecaytoMuon        =  8,
    OneProng           =  9,
    ThreeProng         = 10,
    FiveProng          = 11
  };
};

#endif





