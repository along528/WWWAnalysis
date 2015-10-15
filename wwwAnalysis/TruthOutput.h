#ifndef TruthOutput_H
#define TruthOutput_H

#include <vector>
#include <TVector2.h>
#include "PATCore/TAccept.h"
#include "wwwAnalysis/Electron.h"
#include "wwwAnalysis/Muon.h"
#include "wwwAnalysis/Tau.h"
#include "wwwAnalysis/Jet.h"
#include "wwwAnalysis/MissingEt.h"
#include "wwwAnalysis/EventData.h"
#include "wwwAnalysis/TruthEventData.h"
#include "TFile.h"

namespace wwwAnalysis
{

class TruthOutput : public TruthEventData
{
 private:

  
 public:
  TruthOutput();
  
  void Fill(const D3PDReader::Event & , double,double,double,double,double,
  				        double,double,double,double,double);
  void Fill(TTree *tree);
  void initialize(const char *);
  void finalize();
  ~TruthOutput();
  
};

} // End: namespace wwwAnalysis

#endif
