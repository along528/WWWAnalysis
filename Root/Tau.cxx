#include "wwwAnalysis/Tau.h"

ClassImp( wwwAnalysis::Tau )

wwwAnalysis::Tau::Tau(const D3PDReader::EventInfoD3PDObject &eventinfo, const D3PDReader::TauD3PDObjectElement &tau)
  :PhysicsObject(eventinfo, TAU), m_pD3PD(&tau)
{
  TLorentzVector p;
  p.SetPtEtaPhiM(d3pd().pt(), d3pd().eta(), d3pd().phi(), d3pd().m());
  setMomentum(p);
  setCharge(d3pd().charge());
}

const D3PDReader::TauD3PDObjectElement &wwwAnalysis::Tau::d3pd() const
{
  return *m_pD3PD;
}
