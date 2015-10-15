#include "wwwAnalysis/TruthOutput.h"
#include "TTree.h"
#include "wwwAnalysis/Functions.h"
#include <iostream>
#include <cmath>
#include "TMatrix.h"
#include "TVector2.h"
#include "TVector.h"
#include "TDirectory.h"

//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::TruthOutput::TruthOutput()
{
}

//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::TruthOutput::~TruthOutput()
{
/*
if(ip_smear){ip_smear->Close();delete ip_smear; ip_smear=0;}
if(rand){delete rand;rand=0;}
*/
}

void wwwAnalysis::TruthOutput::initialize(const char *out_name)
{
	status = new std::vector<int>();
	pt = new std::vector<double>() ;
	m = new std::vector<double>() ;
	eta = new std::vector<double>() ;
	phi = new std::vector<double>() ;
	status = new std::vector<int>() ;
	barcode = new std::vector<int>() ;
	pdgId = new std::vector<int>() ;
	charge = new std::vector<double>() ;
	vx_x = new std::vector<double>() ;
	vx_y = new std::vector<double>() ;
	vx_z = new std::vector<double>() ;
	vx_barcode = new std::vector<double>() ;
	parents= new std::vector<int>() ;
	parent_index = new std::vector<int>()  ;
	TruthEventData::initialize(out_name,0,TRUTH_TREE_WRITE);

}
void wwwAnalysis::TruthOutput::Fill(const D3PDReader::Event &event, double lumi,
			   double mcWeight, double sfWeight, double puWeight, 
			   double btagWeightEff85, 
			   double trigWeight, double xsecWeight, double chargeWeight, double mxmWeight, double ffWeight){
  pt->resize(event.mc.n());
  m->resize(event.mc.n());
  eta->resize(event.mc.n());
  phi->resize(event.mc.n());
  status->resize(event.mc.n());
  barcode->resize(event.mc.n());
  pdgId->resize(event.mc.n());
  charge->resize(event.mc.n());
  vx_x->resize(event.mc.n());
  vx_y->resize(event.mc.n());
  vx_z->resize(event.mc.n());
  vx_barcode->resize(event.mc.n());
  //ignore parents except for 0th
  //
  parents->resize(event.mc.n());
  parent_index->resize(event.mc.n());

  for (int i = 0 ; i < event.mc.n(); i++){
  	status->at(i) = event.mc[i].status();
  	pt->at(i) = event.mc[i].pt();
  	m->at(i) = event.mc[i].m();
  	eta->at(i) = event.mc[i].eta();
  	phi->at(i) = event.mc[i].phi();
  	status->at(i) = event.mc[i].status();
  	barcode->at(i) = event.mc[i].barcode();
  	pdgId->at(i) = event.mc[i].pdgId();
  	charge->at(i) = event.mc[i].charge();
  	vx_x->at(i) = event.mc[i].vx_x();
  	vx_y->at(i) = event.mc[i].vx_y();
  	vx_z->at(i) = event.mc[i].vx_z();
  	vx_barcode->at(i) = event.mc[i].vx_barcode();
        if ( event.mc[i].parent_index().size() > 0 ){
		parents->at(i) = event.mc[i].parents()[0];
		parent_index->at(i) = event.mc[i].parent_index()[0];
	}
	else{
		parents->at(i) = 99999;
		parent_index->at(i) = -1;

	}

  }
  AllWeight = mcWeight*sfWeight*puWeight*btagWeightEff85*trigWeight*xsecWeight*chargeWeight*mxmWeight*ffWeight;
  MonteCarloWeight = mcWeight;
  RecoWeight = sfWeight;
  PileupWeight = puWeight;
  //BTagWeightEff60 = btagWeightEff60;
  //BTagWeightEff70 = btagWeightEff70;
  //BTagWeightEff80 = btagWeightEff80;
  BTagWeightEff85 = btagWeightEff85;
  TriggerWeight = trigWeight;
  ChargeMisIDWeight = chargeWeight;
  XSecWeight = xsecWeight;
  CorrectionWeight = 1.0;
  MxMWeight = mxmWeight;
  FormFactorWeight = ffWeight;
  LumiWeight = lumi;

  if(event.eventinfo.mc_channel_number.IsAvailable() && event.eventinfo.mc_channel_number() > 0)
  	RunNumber = event.eventinfo.mc_channel_number();
  else
  	RunNumber = event.eventinfo.RunNumber();
  EventNumber=event.eventinfo.EventNumber();
  lbn=event.eventinfo.lbn();

  tree()->Fill();
}


void wwwAnalysis::TruthOutput::finalize()
{
/*
 */
}
