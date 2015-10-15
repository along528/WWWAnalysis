#ifndef TruthEventData_H
#define TruthEventData_H

#include <vector>
#include <string>
#include <iostream>
#include <TTree.h>
#include <TVector2.h>
#include <TLorentzVector.h>
#include "PATCore/TAccept.h"

namespace wwwAnalysis {

enum TruthTreeReadWrite
{
	TRUTH_TREE_READ, TRUTH_TREE_WRITE
};

template<class Type>
class TruthEventItemBase
{
	protected:
		Type m_oData;
		TBranch *m_pBranch;
		std::string m_sBranchName;
	public:
		TruthEventItemBase(const char *name = ""):m_oData(), m_pBranch(0), m_sBranchName(name){}
		TruthEventItemBase(const Type &data, const char *name = ""):m_oData(data), m_pBranch(0), m_sBranchName(name){}

		Type &data() { return m_oData; }

		std::string name() const { return m_sBranchName; }
		void setName(const char *name) { m_sBranchName = name; }
		void setName(const std::string &name) { m_sBranchName = name; }
		void enable() { m_pBranch->GetTree()->SetBranchStatus((m_sBranchName+"*").c_str(), 1); }
		void disable() { m_pBranch->GetTree()->SetBranchStatus((m_sBranchName+"*").c_str(), 0); }
		
		TBranch * &branch() { return m_pBranch; }
};

template<class Type>
class TruthEventItem : public TruthEventItemBase<Type>
{
	public:
		static const char *TypeName;
	public:
		TruthEventItem(const char *name = "") : TruthEventItemBase<Type>(name){}
		TruthEventItem(const Type &data, const char *name = "") : TruthEventItemBase<Type>(data,name){}
		operator Type() { return this->m_oData; }
		operator Type*() { return &this->m_oData; }
		Type &operator=(const Type &data) { return this->m_oData = data; }
		Type &operator*() { return this->m_oData; }
		Type *operator->() { return &this->m_oData; }
		
		void setupBranch(TTree *, TruthTreeReadWrite);
};
template<class Type>
class TruthEventItem<Type *> : public TruthEventItemBase<Type *>
{
	public:
		static const char *TypeName;
	public:
		TruthEventItem(Type *data = 0, const char *name = "") : TruthEventItemBase<Type *>(data,name){}
		operator Type() { return *this->m_oData; }
		operator Type*() { return this->m_oData; }
		Type *operator=(Type *data) { return this->m_oData = data; }
		Type &operator=(const Type &data) { return *(this->m_oData) = data; }
		Type &operator*() { return *this->m_oData; }
		Type *operator->() { return this->m_oData; }
		
		void setupBranch(TTree *, TruthTreeReadWrite);
};
template<class Type>
void TruthEventItem<Type>::setupBranch(TTree *tree, TruthTreeReadWrite io)
{
	if(TypeName) {
		if(io == TRUTH_TREE_READ) {
			tree->SetBranchAddress(this->m_sBranchName.c_str(), &(this->data()), &(this->branch()));
		}
		else
			this->m_pBranch = tree->Branch(this->m_sBranchName.c_str(), TypeName, &(this->data()));
	}
	else {
		if(io == TRUTH_TREE_READ) {
			tree->SetBranchAddress(this->m_sBranchName.c_str(), &(this->data()), &(this->branch()));
		}
		else
			this->m_pBranch = tree->Branch(this->m_sBranchName.c_str(), &(this->data()));
	}
}
template<class Type>
void TruthEventItem<Type *>::setupBranch(TTree *tree, TruthTreeReadWrite io)
{
	if(TypeName) {
		if(io == TRUTH_TREE_READ)
			tree->SetBranchAddress(this->m_sBranchName.c_str(), &(this->data()), &(this->branch()));
		else
			this->m_pBranch = tree->Branch(this->m_sBranchName.c_str(), TypeName, (this->data()));
	}
	else {
		if(io == TRUTH_TREE_READ) {
			tree->SetBranchAddress(this->m_sBranchName.c_str(), (this->data()), &(this->branch()));
		}
		else
			this->m_pBranch = tree->Branch(this->m_sBranchName.c_str(), (this->data()));
	}
}



class TruthEventData
{
	private:
		TTree *m_pTree;
  
	public:
    TruthEventData();

    void initialize(const char *out_name, TTree *, TruthTreeReadWrite = TRUTH_TREE_WRITE);
    void initialize2(const char *out_name, TTree *, TruthTreeReadWrite = TRUTH_TREE_WRITE);
		
		TTree* tree();
    ~TruthEventData();

	public:
/**** Raw Event Data ****/
	
		TruthEventItem<int> n;
		TruthEventItem<std::vector<double> *> pt;
		TruthEventItem<std::vector<double> *> m;
		TruthEventItem<std::vector<double> *> eta;
		TruthEventItem<std::vector<double> *> phi;
		TruthEventItem<std::vector<int> *> status;
		TruthEventItem<std::vector<int> *> barcode;
		TruthEventItem<std::vector<int> *> pdgId;
		TruthEventItem<std::vector<double> *> charge;
		TruthEventItem<std::vector<double> *> vx_x;
		TruthEventItem<std::vector<double> *> vx_y;
		TruthEventItem<std::vector<double> *> vx_z;
		TruthEventItem<std::vector<double> *> vx_barcode;
		TruthEventItem<std::vector<int> *> parents;
		TruthEventItem<std::vector<int> *> parent_index;
		TruthEventItem<int> RunNumber;
		TruthEventItem<int> EventNumber;
		TruthEventItem<int> lbn;

		//Event weights
		TruthEventItem<double> MonteCarloWeight;
		TruthEventItem<double> PileupWeight;
		TruthEventItem<double> RecoWeight;
		TruthEventItem<double> BTagWeightEff85;
		TruthEventItem<double> TriggerWeight;
		TruthEventItem<double> ChargeMisIDWeight;
		TruthEventItem<double> CorrectionWeight;
		TruthEventItem<double> XSecWeight;
		TruthEventItem<double> MxMWeight;
		TruthEventItem<double> FormFactorWeight;
		TruthEventItem<double> LumiWeight;
		TruthEventItem<double> AllWeight;
};

} // End: namespace wwwAnalysis

#endif

