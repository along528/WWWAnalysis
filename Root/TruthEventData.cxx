#include "wwwAnalysis/TruthEventData.h"
#include "wwwAnalysis/Functions.h"
#include "TMatrix.h"
#include "TVector2.h"
#include "TVector.h"
#include "TDirectory.h"
#include <cmath>

template<class T> const char *wwwAnalysis::TruthEventItem<T>::TypeName = 0;
template<> const char *wwwAnalysis::TruthEventItem<TLorentzVector *>::TypeName = "TLorentzVector";
template<> const char *wwwAnalysis::TruthEventItem<std::vector<TLorentzVector> *>::TypeName = "std::vector<TLorentzVector>";
template<> const char *wwwAnalysis::TruthEventItem<std::vector<bool> *>::TypeName = "std::vector<bool>";
template<> const char *wwwAnalysis::TruthEventItem<std::vector<int> *>::TypeName = "std::vector<int>";
template<> const char *wwwAnalysis::TruthEventItem<std::vector<double> *>::TypeName = "std::vector<double>";
//


//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::TruthEventData::TruthEventData()
:m_pTree(0)
{
	n.setName("n");
	pt.setName("pt");
	m.setName("m");
	eta.setName("eta");
	phi.setName("phi");
	status.setName("status");
	barcode.setName("barcode");
	pdgId.setName("pdgId");
	charge.setName("charge");
	vx_x.setName("vx_x");
	vx_y.setName("vx_y");
	vx_z.setName("vx_z");
	vx_barcode.setName("vx_barcode");
	parents.setName("parents");
	parent_index.setName("parent_index");


	AllWeight.setName("weight_all");
	MonteCarloWeight.setName("weight_mc");
	PileupWeight.setName("weight_pileup");
	RecoWeight.setName("weight_reco");
	//BTagWeightEff60.setName("weight_btag_eff60");
	//BTagWeightEff70.setName("weight_btag_eff70");
	//BTagWeightEff80.setName("weight_btag_eff80");
	BTagWeightEff85.setName("weight_btag_eff85");
	TriggerWeight.setName("weight_trigger");
	ChargeMisIDWeight.setName("weight_chargemisid");
	XSecWeight.setName("weight_xsec");
	MxMWeight.setName("weight_mxm");
	FormFactorWeight.setName("weight_formfactor");
	CorrectionWeight.setName("weight_correction");
	LumiWeight.setName("weight_lumi");
	
	RunNumber.setName("RunNumber");
	EventNumber.setName("EventNumber");
	lbn.setName("lbn");

	/*
	EF_mu36_tight.setName("EF_mu36_tight");
	EF_mu24i_tight.setName("EF_mu24i_tight");
	EF_e24vhi_medium1.setName("EF_e24vhi_medium1");
	EF_e60_medium1.setName("EF_e60_medium1");
	*/
	
}

void wwwAnalysis::TruthEventData::initialize2(const char *out_name, TTree *tree, TruthTreeReadWrite io)
{
	initialize(out_name,tree,io);
}
void wwwAnalysis::TruthEventData::initialize(const char *out_name, TTree *tree, TruthTreeReadWrite io)
{
  //Declare the TTree:
  m_pTree = tree;
  if(tree == 0)
    //      m_pTree= new TTree("physics","physics");
    m_pTree= new TTree(out_name,out_name);
  if(io == TRUTH_TREE_WRITE)
  {
	  m_pTree->SetAutoSave(100000000);
  	m_pTree->SetAutoFlush( 30000000 );
  	TTree::SetBranchStyle(1);
  }

	
	n.setupBranch(m_pTree,io);
	pt.setupBranch(m_pTree,io);
	m.setupBranch(m_pTree,io);
	eta.setupBranch(m_pTree,io);
	phi.setupBranch(m_pTree,io);
	status.setupBranch(m_pTree, io);
	barcode.setupBranch(m_pTree,io);
	pdgId.setupBranch(m_pTree,io);
	charge.setupBranch(m_pTree,io);
	vx_x.setupBranch(m_pTree,io);
	vx_y.setupBranch(m_pTree,io);
	vx_z.setupBranch(m_pTree,io);
	vx_barcode.setupBranch(m_pTree,io);
	parents.setupBranch(m_pTree,io);
	parent_index.setupBranch(m_pTree,io);

	RunNumber.setupBranch(m_pTree, io);
	EventNumber.setupBranch(m_pTree, io);
	lbn.setupBranch(m_pTree, io);


	MonteCarloWeight.setupBranch(m_pTree, io);
	PileupWeight.setupBranch(m_pTree, io);
	RecoWeight.setupBranch(m_pTree, io);
	//BTagWeightEff60.setupBranch(m_pTree, io);
	//BTagWeightEff70.setupBranch(m_pTree, io);
	//BTagWeightEff80.setupBranch(m_pTree, io);
	BTagWeightEff85.setupBranch(m_pTree, io);
	TriggerWeight.setupBranch(m_pTree, io);
	ChargeMisIDWeight.setupBranch(m_pTree, io);
	XSecWeight.setupBranch(m_pTree, io);
	MxMWeight.setupBranch(m_pTree, io);
	FormFactorWeight.setupBranch(m_pTree, io);
	LumiWeight.setupBranch(m_pTree, io);
 	CorrectionWeight.setupBranch(m_pTree, io);
	AllWeight.setupBranch(m_pTree, io);

}

//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::TruthEventData::~TruthEventData()
{

}

TTree* wwwAnalysis::TruthEventData::tree()
{
	return m_pTree;
}

