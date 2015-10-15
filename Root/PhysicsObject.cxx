#include "wwwAnalysis/PhysicsObject.h"

ClassImp( wwwAnalysis::PhysicsObject )

wwwAnalysis::PhysicsObject::PhysicsObject()
  :TObject(), m_pEventInfo(0), m_oMomentum(0,0,0,0), m_oRawMomentum(0,0,0,0), m_eType(), m_fCharge(0), m_bFake(false),m_bIsChargeFlipped(false)
{
}
wwwAnalysis::PhysicsObject::PhysicsObject(const D3PDReader::EventInfoD3PDObject &eventinfo, ParticleType type, bool fake,int index)
  :TObject(), m_pEventInfo(&eventinfo), m_oMomentum(0,0,0,0), m_oRawMomentum(0,0,0,0), m_eType(type), m_fCharge(0), m_bFake(fake),m_bIsChargeFlipped(false),m_iIndex(index)

{
}
void wwwAnalysis::PhysicsObject::setMomentum(const TLorentzVector &momentum)
{
  m_oMomentum = momentum;
  m_oRawMomentum = momentum;
}
void wwwAnalysis::PhysicsObject::setMomentum(const TLorentzVector &momentum, const TLorentzVector &raw)
{
  m_oMomentum = momentum;
  m_oRawMomentum = raw;
}
int wwwAnalysis::PhysicsObject::index() const
{
  return m_iIndex;
}

void wwwAnalysis::PhysicsObject::flipCharge(){
  setCharge(charge()*-1);
  //m_fCharge *= -1;
  m_bIsChargeFlipped = true;
}

bool wwwAnalysis::PhysicsObject::isChargeFlipped() const {
	return m_bIsChargeFlipped;
}
void wwwAnalysis::PhysicsObject::setCharge(double charge)
{
  m_fCharge = charge;
}



TLorentzVector wwwAnalysis::PhysicsObject::rawMomentum() const
{
  return m_oRawMomentum;
}
TLorentzVector wwwAnalysis::PhysicsObject::momentum() const
{
  return m_oMomentum;
}
double wwwAnalysis::PhysicsObject::charge() const
{
  return m_fCharge;
}
bool wwwAnalysis::PhysicsObject::fake() const
{
  return m_bFake;
}
void wwwAnalysis::PhysicsObject::setFakeStatus(bool isfake)
{
  m_bFake= isfake;
}
wwwAnalysis::ParticleType wwwAnalysis::PhysicsObject::type() const
{
  return m_eType;
}
double wwwAnalysis::PhysicsObject::scaleFactor() const
{
  return 1.0;
}
const D3PDReader::EventInfoD3PDObject &wwwAnalysis::PhysicsObject::eventInfo() const
{
  return *m_pEventInfo;
}


bool wwwAnalysis::PhysicsObject::isTrueElecMatch(int mc_channel_number, int Type, int Typebkg, int Originbkg, int choice)
{
  //
  // check if a reconstructed electron matches a true one
  //

  bool truthMatchOK = false;
  bool isElectronFromb = false;
  bool isElectronFromConversion = false;
  bool isSignalElectron = false;
  bool isHadron = false;
  bool passPC = false;
  bool passLF = false;

  //std::cout << " Type= " << Type << " " << Typebkg << " " << Originbkg << std::endl;

  // b->e
  if (Type == FakeComposition::NonIsoElectron && mc_channel_number != 147772) isElectronFromb = true;
  
  // conversions
/*  if (mc_channel_number == 145161 || mc_channel_number == 145162) {
    passPC = ((Type == FakeComposition::BkgElectron)  || (Type == FakeComposition::UnknownElectron));
  } else {
    passPC = (Type == FakeComposition::BkgElectron);
  }
  if (passPC) {
*/
  if (Type == FakeComposition::BkgElectron) {
    //if (Originbkg == FakeComposition::PhotonConv) truthMatchOK = true;
    //if (Originbkg == FakeComposition::DalitzDec) truthMatchOK = true;
    isElectronFromConversion = true;
    if (Originbkg == FakeComposition::WBoson) isElectronFromConversion = false;
    else if (Originbkg == FakeComposition::ZBoson) isElectronFromConversion = false;
    else if (Typebkg == FakeComposition::NonIsoPhoton && 
    Originbkg == FakeComposition::FSRPhot) isElectronFromConversion = false;  
  }
  
  
  // if it is isolated electron it is ok (type=2)
  if (Type == FakeComposition::IsoElectron || 
     ((mc_channel_number == 145161 || mc_channel_number == 145162) && Type == FakeComposition::UnknownElectron) ||
      (mc_channel_number == 147772 && Type == FakeComposition::NonIsoElectron)) isSignalElectron = true;
  // in case it is a "BkgElectron" (type=4)
  else if (Type == FakeComposition::BkgElectron ) {
    if (Originbkg == FakeComposition::WBoson ||
	Originbkg == FakeComposition::ZBoson) isSignalElectron = true;
    else if (Typebkg == FakeComposition::NonIsoPhoton && 
	     Originbkg == FakeComposition::FSRPhot) isSignalElectron = true;
  }

  // u/d->e
  if ((mc_channel_number == 167007 || mc_channel_number == 167008) && (Type == FakeComposition::UnknownElectron)) {
    isHadron = true;
  }   
  // QCD 
  if (!isElectronFromb && !isElectronFromConversion && !isSignalElectron && !isHadron) {
    isHadron = true;
  }

  // select signal electrons
  if (choice==1) truthMatchOK = isSignalElectron;
  // select electrons from b
  if (choice==2) truthMatchOK = isElectronFromb;
  // select electrons from conversion
  if (choice==3) truthMatchOK = isElectronFromConversion;
  // select hadrons
  if (choice==4) truthMatchOK = isHadron;

/*
  if(isSignalElectron) cout<<"************************ E: Prompt electron"<<endl;
  if(isElectronFromb) cout<<"************************ E: Heavy Jets"<<endl;
  if(isElectronFromConversion) cout<<"************************ E: Photon Conversion"<<endl;
  if(isHadron) cout<<"************************ E: Light Jets"<<endl;
*/

  return truthMatchOK;

 
}

bool wwwAnalysis::PhysicsObject::isTrueMuonMatch(int mc_channel_number, int Type, int choice)
{
  //
  // check if a reconstructed electron matches a true one
  //

  bool truthMatchOK = false;
 

  bool isHF = false;
  bool isLF = false;
  bool isPC = false;
  bool isSignalMuon = false;
  bool passLF = false;

  //Heavy Flavour
  if (Type == FakeComposition::NonIsoMuon && mc_channel_number != 147772) isHF = true;
  //Light Flavour 
  if (mc_channel_number == 167007 || mc_channel_number == 167008) {
    passLF = ((Type == FakeComposition::Hadron) || (Type == FakeComposition::BkgMuon) || (Type == FakeComposition::UnknownMuon));
  } else {
    passLF = ((Type == FakeComposition::Hadron) || (Type == FakeComposition::BkgMuon));
  } 
  if (passLF) isLF = true; 
  //Photon Conversions 
  if (Type == FakeComposition::BkgElectron) isPC = true;
  //Signal
  if (Type == FakeComposition::IsoMuon || 
     ((mc_channel_number == 145161 || mc_channel_number == 145162) && Type == FakeComposition::UnknownMuon) || 
      (mc_channel_number == 147772 && Type == FakeComposition::NonIsoMuon)) isSignalMuon = true;
  
  // QCD
  if (!isHF && !isPC && !isLF && !isSignalMuon) {
    isLF = true;
  }

  // select signal muons
  if (choice==1) truthMatchOK = isSignalMuon;
  // select Heavy Flavour b jets
  if (choice==2) truthMatchOK = isHF;
  // select conversions
  if (choice==3) truthMatchOK = isPC;
  // selectLight Flavor jets
  if (choice==4) truthMatchOK = isLF;

/*
  if(isSignalMuon) cout<<"************************ M: Prompt muon"<<endl;
  if(isHF) cout<<"************************ M: Heavy Jets"<<endl;
  if(isPC) cout<<"************************ M: Comversions"<<endl;
  if(isLF) cout<<"************************ M: Light Jets"<<endl;
*/
 
  return truthMatchOK;
}

