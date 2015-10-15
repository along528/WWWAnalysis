#ifndef Output_H
#define Output_H

#include <vector>
#include <TVector2.h>
#include "PATCore/TAccept.h"
#include "wwwAnalysis/Electron.h"
#include "wwwAnalysis/Muon.h"
#include "wwwAnalysis/Tau.h"
#include "wwwAnalysis/Jet.h"
#include "wwwAnalysis/MissingEt.h"
#include "wwwAnalysis/EventData.h"
#include "wwwAnalysis/Functions.h"
#include "TFile.h"


namespace wwwAnalysis
{

class Output : public EventData
{
 private:
  TFile* ip_smear;  //!
  TH2F *smearD0[3];  //!
  //  	 TAxis *smear_X;  //!
  //  	 TAxis *smear_Y;  //!
  TRandom3 *rand; //!

  
 public:
  Output();
  
  void Fill(const D3PDReader::Event &, InitialState, FinalState, double, int,int, 
  const vector<double> &, const vector<double> &,
  	    //int, 
	    int, int, int, double, double, 
	    const vector<wwwAnalysis::PhysicsObject *> &, 
	    const vector<wwwAnalysis::PhysicsObject *> &, 
	    //const vector<wwwAnalysis::PhysicsObject *> &,
	    const vector<wwwAnalysis::PhysicsObject *> &,
	    const vector<wwwAnalysis::PhysicsObject *> &,
	    const vector<wwwAnalysis::PhysicsObject *> &,
	    const vector<wwwAnalysis::PhysicsObject *> &,
	    const vector<wwwAnalysis::PhysicsObject *> &,
	    const vector<wwwAnalysis::PhysicsObject *> &,
	    bool ,
	    const std::vector<Jet> &,const MissingEt &,
	    //double, 
	    double, double, double, double, double, double, double,double,double,bool,bool,bool,JVFSys, wwwAnalysis::OutputInformations&,bool,bool);
  void Fill(TTree *tree);
  void initialize(const char *);
  float  GetD0SmearSigma(int nBL, float pt, float eta);
  void finalize();
  ~Output();
  
 private:
  void FillLepton(int i, const PhysicsObject *, bool);
  void FillAllLepton(int i, const PhysicsObject *);
  void FillLeptonLooseNotTight(int i, const PhysicsObject *);
  void FillLeptonTag(int i, const PhysicsObject *);
  void FillLeptonTag2(int i, const PhysicsObject *);
  void FillLeptonProbe(int i, const PhysicsObject *);
  void FillLeptonLoose(int i, const PhysicsObject *);
  //void FillLeptonInc(int i, const PhysicsObject *);
};

} // End: namespace wwwAnalysis

#endif
