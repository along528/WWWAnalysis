#ifndef EventData_H
#define EventData_H

#include <vector>
#include <string>
#include <iostream>
#include <TTree.h>
#include <TVector2.h>
#include <TLorentzVector.h>
#include "PATCore/TAccept.h"


namespace wwwAnalysis {

enum TreeReadWrite
{
	TREE_READ, TREE_WRITE
};

template<class Type>
class EventItemBase
{
	protected:
		Type m_oData;
		TBranch *m_pBranch;
		std::string m_sBranchName;
	public:
		EventItemBase(const char *name = ""):m_oData(), m_pBranch(0), m_sBranchName(name){}
		EventItemBase(const Type &data, const char *name = ""):m_oData(data), m_pBranch(0), m_sBranchName(name){}

		Type &data() { return m_oData; }

		std::string name() const { return m_sBranchName; }
		void setName(const char *name) { m_sBranchName = name; }
		void setName(const std::string &name) { m_sBranchName = name; }
		void enable() { m_pBranch->GetTree()->SetBranchStatus((m_sBranchName+"*").c_str(), 1); }
		void disable() { m_pBranch->GetTree()->SetBranchStatus((m_sBranchName+"*").c_str(), 0); }
		
		TBranch * &branch() { return m_pBranch; }
};

template<class Type>
class EventItem : public EventItemBase<Type>
{
	public:
		static const char *TypeName;
	public:
		EventItem(const char *name = "") : EventItemBase<Type>(name){}
		EventItem(const Type &data, const char *name = "") : EventItemBase<Type>(data,name){}
		operator Type() { return this->m_oData; }
		operator Type*() { return &this->m_oData; }
		Type &operator=(const Type &data) { return this->m_oData = data; }
		Type &operator*() { return this->m_oData; }
		Type *operator->() { return &this->m_oData; }
		
		void setupBranch(TTree *, TreeReadWrite);
};
template<class Type>
class EventItem<Type *> : public EventItemBase<Type *>
{
	public:
		static const char *TypeName;
	public:
		EventItem(Type *data = 0, const char *name = "") : EventItemBase<Type *>(data,name){}
		operator Type() { return *this->m_oData; }
		operator Type*() { return this->m_oData; }
		Type *operator=(Type *data) { return this->m_oData = data; }
		Type &operator=(const Type &data) { return *(this->m_oData) = data; }
		Type &operator*() { return *this->m_oData; }
		Type *operator->() { return this->m_oData; }
		
		void setupBranch(TTree *, TreeReadWrite);
};
template<class Type>
void EventItem<Type>::setupBranch(TTree *tree, TreeReadWrite io)
{
	if(TypeName) {
		if(io == TREE_READ) {
			tree->SetBranchAddress(this->m_sBranchName.c_str(), &(this->data()), &(this->branch()));
		}
		else
			this->m_pBranch = tree->Branch(this->m_sBranchName.c_str(), TypeName, &(this->data()));
	}
	else {
		if(io == TREE_READ) {
			tree->SetBranchAddress(this->m_sBranchName.c_str(), &(this->data()), &(this->branch()));
		}
		else
			this->m_pBranch = tree->Branch(this->m_sBranchName.c_str(), &(this->data()));
	}
}
template<class Type>
void EventItem<Type *>::setupBranch(TTree *tree, TreeReadWrite io)
{
	if(TypeName) {
		if(io == TREE_READ)
			tree->SetBranchAddress(this->m_sBranchName.c_str(), &(this->data()), &(this->branch()));
		else
			this->m_pBranch = tree->Branch(this->m_sBranchName.c_str(), TypeName, (this->data()));
	}
	else {
		if(io == TREE_READ) {
			tree->SetBranchAddress(this->m_sBranchName.c_str(), (this->data()), &(this->branch()));
		}
		else
			this->m_pBranch = tree->Branch(this->m_sBranchName.c_str(), (this->data()));
	}
}

enum InitialState
{
	MC_INITIAL_DATA = 0,
	MC_INITIAL_ggH = 1,
	MC_INITIAL_VBFH = 2,
	MC_INITIAL_ZH = 4,
	MC_INITIAL_WH = 8,
	MC_INITIAL_VH = 12,
  MC_INITIAL_H = 15,
	MC_INITIAL_Z = 16,
	MC_INITIAL_W = 32,
	MC_INITIAL_ZZ = 64,
	MC_INITIAL_WW = 128,
	MC_INITIAL_WZ = 256,
	MC_INITIAL_t = 512,
	MC_INITIAL_tt = 1024,
  MC_INITIAL_tX = 1536,
	MC_INITIAL_Wgamma = 2048,
	MC_INITIAL_lnull = 4096,
  MC_INITIAL_VV = 6592
};
enum FinalState
{
	MC_FINAL_DATA = 0,
	MC_FINAL_tautau_leplep = 1,
	MC_FINAL_tautau = 2,
	MC_FINAL_ee = 4,
	MC_FINAL_mumu = 8,
	MC_FINAL_taunu = 16,
	MC_FINAL_munu = 32,
	MC_FINAL_enu = 64,
	MC_FINAL_eebb = 128,
	MC_FINAL_mumubb = 256,
	MC_FINAL_leplepbb = 384,
	MC_FINAL_leplep = 396,
	MC_FINAL_tautaubb = 512,
  MC_FINAL_tautau_inc = 515,
	MC_FINAL_any = 0xFFFF
};

class EventData
{
	private:
		TTree *m_pTree;
  
	public:
    EventData();

    void initialize(const char *out_name, TTree *, TreeReadWrite = TREE_WRITE);
    void initialize2(const char *out_name, TTree *, TreeReadWrite = TREE_WRITE);
		
		TTree* tree();
    ~EventData();

	public:
/**** Raw Event Data ****/

	
		//TLV:
		EventItem<std::vector<TLorentzVector> *> Lep;
		EventItem<std::vector<TLorentzVector> *> Lep_LooseNotTight;
		EventItem<std::vector<TLorentzVector> *> Lep_Tag;
		EventItem<std::vector<TLorentzVector> *> Lep_Tag2;
		EventItem<std::vector<TLorentzVector> *> Lep_Probe;
		EventItem<std::vector<TLorentzVector> *> Lep_Loose;
		EventItem<std::vector<TLorentzVector> *> AllLep;
		/*
		EventItem<std::vector<TLorentzVector> *> Lep_inc;
		EventItem<std::vector<double> *> Mu_inc_pt_loose;
		EventItem<std::vector<double> *> Mu_inc_pt_medium;
		EventItem<std::vector<double> *> Mu_inc_pt_tight;
		EventItem<std::vector<double> *> El_inc_pt_loose;
		EventItem<std::vector<double> *> El_inc_pt_medium;
		EventItem<std::vector<double> *> El_inc_pt_tight;
		EventItem<std::vector<double> *> El_inc_pt_veryLooseLL;
		EventItem<std::vector<double> *> El_inc_pt_looseLL;
		EventItem<std::vector<double> *> El_inc_pt_mediumLL;
		EventItem<std::vector<double> *> El_inc_pt_tightLL;
		EventItem<std::vector<double> *> El_inc_pt_veryTightLL;
		*/
	
		//Isol:
		EventItem<std::vector<double> *> Lep_ptiso;
		EventItem<std::vector<double> *> Lep_etiso;
		EventItem<std::vector<double> *> Lep_z0_exPV;
		
		//track significance:
		EventItem<std::vector<double> *> Lep_d0;
		EventItem<std::vector<double> *> Lep_sigmad0;
		EventItem<std::vector<double> *> Lep_track_z0;
		EventItem<std::vector<double> *> Lep_track_d0;
		EventItem<std::vector<double> *> Lep_track_sigz0;
		EventItem<std::vector<double> *> Lep_track_sigd0;
		EventItem<std::vector<double> *> Lep_track_theta;
		EventItem<std::vector<double> *> Lep_track_d0_o_sigd0;
		EventItem<std::vector<double> *> Lep_track_z0_o_sinTheta;

		EventItem<std::vector<bool> *> Lep_isSignalLike;
		EventItem<std::vector<bool> *> Lep_isFromHeavyFlavor;
		EventItem<std::vector<bool> *> Lep_isFromLightFlavor;
		EventItem<std::vector<bool> *> Lep_isFromPhotonConversion;

		//lep coords
		EventItem<std::vector<double> *> Lep_eta;
		EventItem<std::vector<double> *> Lep_phi;
		EventItem<std::vector<double> *> Lep_pt;
		EventItem<std::vector<double> *> Lep_mt;
		EventItem<std::vector<double> *> Lep_mt_STVF;
		EventItem<std::vector<int> *>    Lep_charge;		
		EventItem<std::vector<bool> *>    Lep_isChargeFlipped;		
		/*
		EventItem<std::vector<int> *>    Lep_inc_charge;		
		EventItem<std::vector<bool> *>    Lep_inc_isChargeFlipped;		
		*/

		EventItem<double> ComEnergySquared;
	
		EventItem<double> AllLep_mt;
		EventItem<double> AllLep_mt_STVF;
		EventItem<double> AllLep_deltaPhiMET;
		EventItem<double> AllLep_deltaPhiMET_STVF;
		//Quality:
		EventItem<std::vector<bool> *> Lep_loose;
		EventItem<std::vector<bool> *> Lep_medium;
		EventItem<std::vector<bool> *> Lep_tight;
		EventItem<std::vector<bool> *> Lep_veryLooseLL;
		EventItem<std::vector<bool> *> Lep_looseLL;
		EventItem<std::vector<bool> *> Lep_mediumLL;
		EventItem<std::vector<bool> *> Lep_tightLL;
		EventItem<std::vector<bool> *> Lep_veryTightLL;
		EventItem<std::vector<unsigned int> *> Lep_author;
		EventItem<std::vector<unsigned int> *> Lep_recoAuthor;


		EventItem<std::vector<bool> *> Lep_isMuon;
		EventItem<std::vector<bool> *> Lep_isCombinedMuon;
		EventItem<std::vector<bool> *> Lep_isSpectroMuon;
		EventItem<std::vector<bool> *> Lep_isFake;
		EventItem<std::vector<bool> *> Lep_isSFOS;

		EventItem<std::vector<bool> *> AllLep_isMuon;
		EventItem<std::vector<bool> *> AllLep_isCombinedMuon;
		EventItem<std::vector<bool> *> AllLep_isSpectroMuon;
		EventItem<std::vector<bool> *> AllLep_isFake;

		//Isol:
		EventItem<std::vector<double> *> AllLep_ptiso;
		EventItem<std::vector<double> *> AllLep_etiso;
		EventItem<std::vector<double> *> AllLep_z0_exPV;
		
		//track significance:
		EventItem<std::vector<double> *> AllLep_d0;
		EventItem<std::vector<double> *> AllLep_sigmad0;
		EventItem<std::vector<double> *> AllLep_track_z0;
		EventItem<std::vector<double> *> AllLep_track_d0;
		EventItem<std::vector<double> *> AllLep_track_sigz0;
		EventItem<std::vector<double> *> AllLep_track_sigd0;
		EventItem<std::vector<double> *> AllLep_smeared_d0;

		//lep coords
		EventItem<std::vector<double> *> AllLep_eta;
		EventItem<std::vector<double> *> AllLep_phi;
		EventItem<std::vector<double> *> AllLep_pt;
		EventItem<std::vector<int> *>    AllLep_charge;		
		EventItem<std::vector<bool> *>    AllLep_isChargeFlipped;		
		/*
		EventItem<std::vector<int> *>    Lep_inc_charge;		
		EventItem<std::vector<bool> *>    Lep_inc_isChargeFlipped;		
		*/
	
		//Quality:
		EventItem<std::vector<bool> *> AllLep_loose;
		EventItem<std::vector<bool> *> AllLep_medium;
		EventItem<std::vector<bool> *> AllLep_tight;
		EventItem<std::vector<bool> *> AllLep_veryLooseLL;
		EventItem<std::vector<bool> *> AllLep_looseLL;
		EventItem<std::vector<bool> *> AllLep_mediumLL;
		EventItem<std::vector<bool> *> AllLep_tightLL;
		EventItem<std::vector<bool> *> AllLep_veryTightLL;
		EventItem<std::vector<unsigned int> *> AllLep_author;
		EventItem<std::vector<unsigned int> *> AllLep_recoAuthor;
		/*
		EventItem<std::vector<bool> *> Lep_inc_isMuon;
		EventItem<std::vector<bool> *> Lep_inc_isCombined;
		EventItem<std::vector<bool> *> Lep_inc_isFake;
		*/

		//EventItem<int> nLep_inc;
		//
		//
		//


		//Isol:
		EventItem<std::vector<double> *> Lep_ptiso_LooseNotTight;
		EventItem<std::vector<double> *> Lep_etiso_LooseNotTight;
		EventItem<std::vector<double> *> Lep_z0_exPV_LooseNotTight;
		
		//track significance:
		EventItem<std::vector<double> *> Lep_d0_LooseNotTight;
		EventItem<std::vector<double> *> Lep_sigmad0_LooseNotTight;
		EventItem<std::vector<double> *> Lep_track_z0_LooseNotTight;
		EventItem<std::vector<double> *> Lep_track_d0_LooseNotTight;
		EventItem<std::vector<double> *> Lep_track_sigz0_LooseNotTight;
		EventItem<std::vector<double> *> Lep_track_sigd0_LooseNotTight;
		EventItem<std::vector<double> *> Lep_smeared_d0_LooseNotTight;

		EventItem<std::vector<bool> *> Lep_isSignalLike_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_isFromHeavyFlavor_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_isFromLightFlavor_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_isFromPhotonConversion_LooseNotTight;
		//lep coords
		EventItem<std::vector<double> *> Lep_eta_LooseNotTight;
		EventItem<std::vector<double> *> Lep_phi_LooseNotTight;
		EventItem<std::vector<double> *> Lep_pt_LooseNotTight;
		EventItem<std::vector<double> *> Lep_mt_LooseNotTight;
		EventItem<std::vector<double> *> Lep_mt_STVF_LooseNotTight;
		EventItem<std::vector<int> *>    Lep_charge_LooseNotTight;		
		EventItem<std::vector<bool> *>    Lep_isChargeFlipped_LooseNotTight;		
		//Quality:
		EventItem<std::vector<bool> *> Lep_loose_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_medium_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_tight_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_veryLooseLL_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_looseLL_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_mediumLL_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_tightLL_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_veryTightLL_LooseNotTight;
		EventItem<std::vector<unsigned int> *> Lep_author_LooseNotTight;
		EventItem<std::vector<unsigned int> *> Lep_recoAuthor_LooseNotTight;


		EventItem<std::vector<bool> *> Lep_isMuon_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_isCombinedMuon_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_isSpectroMuon_LooseNotTight;
		EventItem<std::vector<bool> *> Lep_isFake_LooseNotTight;

		//Isol:
		EventItem<std::vector<double> *> Lep_ptiso_Tag;
		EventItem<std::vector<double> *> Lep_etiso_Tag;
		EventItem<std::vector<double> *> Lep_z0_exPV_Tag;
		EventItem<std::vector<double> *> Lep_track_d0_o_sigd0_Tag;
		EventItem<std::vector<double> *> Lep_track_z0_o_sinTheta_Tag;
		
		//track significance:
		EventItem<std::vector<double> *> Lep_d0_Tag;
		EventItem<std::vector<double> *> Lep_sigmad0_Tag;
		EventItem<std::vector<double> *> Lep_track_z0_Tag;
		EventItem<std::vector<double> *> Lep_track_d0_Tag;
		EventItem<std::vector<double> *> Lep_track_sigz0_Tag;
		EventItem<std::vector<double> *> Lep_track_sigd0_Tag;
		EventItem<std::vector<double> *> Lep_smeared_d0_Tag;

		EventItem<std::vector<bool> *> Lep_isSignalLike_Tag;
		EventItem<std::vector<bool> *> Lep_isFromHeavyFlavor_Tag;
		EventItem<std::vector<bool> *> Lep_isFromLightFlavor_Tag;
		EventItem<std::vector<bool> *> Lep_isFromPhotonConversion_Tag;

		//lep coords
		EventItem<std::vector<double> *> Lep_eta_Tag;
		EventItem<std::vector<double> *> Lep_phi_Tag;
		EventItem<std::vector<double> *> Lep_pt_Tag;
		EventItem<std::vector<double> *> Lep_mt_Tag;
		EventItem<std::vector<double> *> Lep_mt_STVF_Tag;
		EventItem<std::vector<int> *>    Lep_charge_Tag;		
		EventItem<std::vector<bool> *>    Lep_isChargeFlipped_Tag;		
		//Quality:
		EventItem<std::vector<bool> *> Lep_loose_Tag;
		EventItem<std::vector<bool> *> Lep_medium_Tag;
		EventItem<std::vector<bool> *> Lep_tight_Tag;
		EventItem<std::vector<bool> *> Lep_veryLooseLL_Tag;
		EventItem<std::vector<bool> *> Lep_looseLL_Tag;
		EventItem<std::vector<bool> *> Lep_mediumLL_Tag;
		EventItem<std::vector<bool> *> Lep_tightLL_Tag;
		EventItem<std::vector<bool> *> Lep_veryTightLL_Tag;
		EventItem<std::vector<unsigned int> *> Lep_author_Tag;
		EventItem<std::vector<unsigned int> *> Lep_recoAuthor_Tag;


		EventItem<std::vector<bool> *> Lep_isMuon_Tag;
		EventItem<std::vector<bool> *> Lep_isCombinedMuon_Tag;
		EventItem<std::vector<bool> *> Lep_isSpectroMuon_Tag;
		EventItem<std::vector<bool> *> Lep_isFake_Tag;

		//Isol:
		EventItem<std::vector<double> *> Lep_ptiso_Tag2;
		EventItem<std::vector<double> *> Lep_etiso_Tag2;
		EventItem<std::vector<double> *> Lep_z0_exPV_Tag2;
		EventItem<std::vector<double> *> Lep_track_d0_o_sigd0_Tag2;
		EventItem<std::vector<double> *> Lep_track_z0_o_sinTheta_Tag2;
		
		//track significance:
		EventItem<std::vector<double> *> Lep_d0_Tag2;
		EventItem<std::vector<double> *> Lep_sigmad0_Tag2;
		EventItem<std::vector<double> *> Lep_track_z0_Tag2;
		EventItem<std::vector<double> *> Lep_track_d0_Tag2;
		EventItem<std::vector<double> *> Lep_track_sigz0_Tag2;
		EventItem<std::vector<double> *> Lep_track_sigd0_Tag2;
		EventItem<std::vector<double> *> Lep_smeared_d0_Tag2;

		EventItem<std::vector<bool> *> Lep_isSignalLike_Tag2;
		EventItem<std::vector<bool> *> Lep_isFromHeavyFlavor_Tag2;
		EventItem<std::vector<bool> *> Lep_isFromLightFlavor_Tag2;
		EventItem<std::vector<bool> *> Lep_isFromPhotonConversion_Tag2;

		//lep coords
		EventItem<std::vector<double> *> Lep_eta_Tag2;
		EventItem<std::vector<double> *> Lep_phi_Tag2;
		EventItem<std::vector<double> *> Lep_pt_Tag2;
		EventItem<std::vector<double> *> Lep_mt_Tag2;
		EventItem<std::vector<double> *> Lep_mt_STVF_Tag2;
		EventItem<std::vector<int> *>    Lep_charge_Tag2;		
		EventItem<std::vector<bool> *>    Lep_isChargeFlipped_Tag2;		
		//Quality:
		EventItem<std::vector<bool> *> Lep_loose_Tag2;
		EventItem<std::vector<bool> *> Lep_medium_Tag2;
		EventItem<std::vector<bool> *> Lep_tight_Tag2;
		EventItem<std::vector<bool> *> Lep_veryLooseLL_Tag2;
		EventItem<std::vector<bool> *> Lep_looseLL_Tag2;
		EventItem<std::vector<bool> *> Lep_mediumLL_Tag2;
		EventItem<std::vector<bool> *> Lep_tightLL_Tag2;
		EventItem<std::vector<bool> *> Lep_veryTightLL_Tag2;
		EventItem<std::vector<unsigned int> *> Lep_author_Tag2;
		EventItem<std::vector<unsigned int> *> Lep_recoAuthor_Tag2;


		EventItem<std::vector<bool> *> Lep_isMuon_Tag2;
		EventItem<std::vector<bool> *> Lep_isCombinedMuon_Tag2;
		EventItem<std::vector<bool> *> Lep_isSpectroMuon_Tag2;
		EventItem<std::vector<bool> *> Lep_isFake_Tag2;

		//Isol:
		EventItem<std::vector<double> *> Lep_ptiso_Probe;
		EventItem<std::vector<double> *> Lep_etiso_Probe;
		EventItem<std::vector<double> *> Lep_z0_exPV_Probe;
		EventItem<std::vector<double> *> Lep_track_d0_o_sigd0_Probe;
		EventItem<std::vector<double> *> Lep_track_z0_o_sinTheta_Probe;
		
		//track significance:
		EventItem<std::vector<double> *> Lep_d0_Probe;
		EventItem<std::vector<double> *> Lep_sigmad0_Probe;
		EventItem<std::vector<double> *> Lep_track_z0_Probe;
		EventItem<std::vector<double> *> Lep_track_d0_Probe;
		EventItem<std::vector<double> *> Lep_track_sigz0_Probe;
		EventItem<std::vector<double> *> Lep_track_sigd0_Probe;
		EventItem<std::vector<double> *> Lep_smeared_d0_Probe;

		EventItem<std::vector<bool> *> Lep_isSignalLike_Probe;
		EventItem<std::vector<bool> *> Lep_isFromHeavyFlavor_Probe;
		EventItem<std::vector<bool> *> Lep_isFromLightFlavor_Probe;
		EventItem<std::vector<bool> *> Lep_isFromPhotonConversion_Probe;

		//lep coords
		EventItem<std::vector<double> *> Lep_eta_Probe;
		EventItem<std::vector<double> *> Lep_phi_Probe;
		EventItem<std::vector<double> *> Lep_pt_Probe;
		EventItem<std::vector<double> *> Lep_mt_Probe;
		EventItem<std::vector<double> *> Lep_mt_STVF_Probe;
		EventItem<std::vector<int> *>    Lep_charge_Probe;		
		EventItem<std::vector<bool> *>    Lep_isChargeFlipped_Probe;		
		//Quality:
		EventItem<std::vector<bool> *> Lep_loose_Probe;
		EventItem<std::vector<bool> *> Lep_medium_Probe;
		EventItem<std::vector<bool> *> Lep_tight_Probe;
		EventItem<std::vector<bool> *> Lep_veryLooseLL_Probe;
		EventItem<std::vector<bool> *> Lep_looseLL_Probe;
		EventItem<std::vector<bool> *> Lep_mediumLL_Probe;
		EventItem<std::vector<bool> *> Lep_tightLL_Probe;
		EventItem<std::vector<bool> *> Lep_veryTightLL_Probe;
		EventItem<std::vector<unsigned int> *> Lep_author_Probe;
		EventItem<std::vector<unsigned int> *> Lep_recoAuthor_Probe;


		EventItem<std::vector<bool> *> Lep_isMuon_Probe;
		EventItem<std::vector<bool> *> Lep_isCombinedMuon_Probe;
		EventItem<std::vector<bool> *> Lep_isSpectroMuon_Probe;
		EventItem<std::vector<bool> *> Lep_isFake_Probe;


		//Isol:
		EventItem<std::vector<double> *> Lep_ptiso_Loose;
		EventItem<std::vector<double> *> Lep_etiso_Loose;
		EventItem<std::vector<double> *> Lep_z0_exPV_Loose;
		
		//track significance:
		EventItem<std::vector<double> *> Lep_d0_Loose;
		EventItem<std::vector<double> *> Lep_sigmad0_Loose;
		EventItem<std::vector<double> *> Lep_track_z0_Loose;
		EventItem<std::vector<double> *> Lep_track_d0_Loose;
		EventItem<std::vector<double> *> Lep_track_sigz0_Loose;
		EventItem<std::vector<double> *> Lep_track_sigd0_Loose;
		EventItem<std::vector<double> *> Lep_smeared_d0_Loose;

		EventItem<std::vector<bool> *> Lep_isSignalLike_Loose;
		EventItem<std::vector<bool> *> Lep_isFromHeavyFlavor_Loose;
		EventItem<std::vector<bool> *> Lep_isFromLightFlavor_Loose;
		EventItem<std::vector<bool> *> Lep_isFromPhotonConversion_Loose;

		//lep coords
		EventItem<std::vector<double> *> Lep_eta_Loose;
		EventItem<std::vector<double> *> Lep_phi_Loose;
		EventItem<std::vector<double> *> Lep_pt_Loose;
		EventItem<std::vector<double> *> Lep_mt_Loose;
		EventItem<std::vector<double> *> Lep_mt_STVF_Loose;
		EventItem<std::vector<int> *>    Lep_charge_Loose;		
		EventItem<std::vector<bool> *>    Lep_isChargeFlipped_Loose;		
		//Quality:
		EventItem<std::vector<bool> *> Lep_loose_Loose;
		EventItem<std::vector<bool> *> Lep_medium_Loose;
		EventItem<std::vector<bool> *> Lep_tight_Loose;
		EventItem<std::vector<bool> *> Lep_veryLooseLL_Loose;
		EventItem<std::vector<bool> *> Lep_looseLL_Loose;
		EventItem<std::vector<bool> *> Lep_mediumLL_Loose;
		EventItem<std::vector<bool> *> Lep_tightLL_Loose;
		EventItem<std::vector<bool> *> Lep_veryTightLL_Loose;
		EventItem<std::vector<unsigned int> *> Lep_author_Loose;
		EventItem<std::vector<unsigned int> *> Lep_recoAuthor_Loose;


		EventItem<std::vector<bool> *> Lep_isMuon_Loose;
		EventItem<std::vector<bool> *> Lep_isCombinedMuon_Loose;
		EventItem<std::vector<bool> *> Lep_isSpectroMuon_Loose;
		EventItem<std::vector<bool> *> Lep_isFake_Loose;

		/*
		EventItem<std::vector<bool> *> Lep_inc_isMuon;
		EventItem<std::vector<bool> *> Lep_inc_isCombined;
		EventItem<std::vector<bool> *> Lep_inc_isFake;
		*/

		EventItem<int> nLep;
		EventItem<int> nAllLep;
		EventItem<int> nLep_fake;
		EventItem<int> nLep_LooseNotTight;
		EventItem<int> nLep_Tag;
		EventItem<int> nLep_Tag2;
		EventItem<int> nLep_Probe;
		EventItem<int> nLep_Loose;


		EventItem<int> nSFOS;
		EventItem<int> nSFOSAll;
		
		EventItem<std::vector<double> *> massesSFOS;
		EventItem<std::vector<double> *> massesSFOSAll;
		EventItem<std::vector<double> *> massesElEl;
		EventItem<std::vector<double> *> massesMuMu;
		EventItem<std::vector<double> *> massesElMu;
	
		//jets
		EventItem<std::vector<TLorentzVector> *> Jets;
		EventItem<std::vector<bool> *> bJets;
		EventItem<std::vector<bool> *> JetsJVF;
		/*
		EventItem<TLorentzVector *> Jet_p[2];
		
		//jet coords
		EventItem<double> Jet_eta[2];
		EventItem<double> Jet_phi[2];
		EventItem<double> Jet_pt[2];
		*/
	
		//MET
		EventItem<double> MET_final_Et;
		EventItem<double> MET_final_phi;
		EventItem<double> MET_final_sumEt;

		EventItem<double> MET_final_Et_raw;
		EventItem<double> MET_final_phi_raw;
		EventItem<double> MET_final_sumEt_raw;

		EventItem<double> MET_final_Et_STVF;
		EventItem<double> MET_final_phi_STVF;
		EventItem<double> MET_final_sumEt_STVF;

		EventItem<double> MET_HPTO_Et;
		EventItem<double> MET_HPTO_phi;
		EventItem<double> MET_HPTO_sumEt;
		
		//Event Information
		EventItem<int> RunNumber;
		EventItem<int> EventNumber;
		EventItem<int> lbn;
		EventItem<int> PrimaryVertexNTracks;
		EventItem<bool> eventHasSpectroMuons;
		EventItem<bool> isEGammaStream;
		EventItem<bool> hasLooseNotTightElectrons;
		EventItem<bool> hasLooseNotTightMuons;
		EventItem<int> nPV_3trks;
		EventItem<int> nPV_2trks;
		//EventItem<int> btagsEff60;
		//EventItem<int> btagsEff70;
		//EventItem<int> btagsEff80;
		EventItem<int> btagsEff85;
		EventItem<double> mu;
		EventItem<bool> FakeLeptons;
		EventItem<bool> OSLeptons;
      EventItem<bool> DiLepton;
      EventItem<bool> TriLepton;
      EventItem<bool> QuadriLepton;
		EventItem<double> mll;
		EventItem<double> mT1;
		EventItem<double> mT2;
		EventItem<double> m12;
		EventItem<double> m34;
		EventItem<double> m4l;
		EventItem<double> SumHPTO;
		EventItem<double> SumCosDphi;
		EventItem<std::vector<int> *>    Lep_4lpair;		

		//Event weights
		EventItem<double> MonteCarloWeight;
		EventItem<double> PileupWeight;
		EventItem<double> RecoWeight;
		//EventItem<double> BTagWeightEff60;
		//EventItem<double> BTagWeightEff70;
		//EventItem<double> BTagWeightEff80;
		EventItem<double> BTagWeightEff85;
		EventItem<double> TriggerWeight;
		EventItem<double> ChargeMisIDWeight;
		EventItem<bool>   DoChargeFlip;
		EventItem<double> CorrectionWeight;
		EventItem<double> XSecWeight;
		EventItem<double> MxMWeight;
		EventItem<double> FormFactorWeight;
		EventItem<double> LumiWeight;
		EventItem<double> AllWeight;

		//MET Info

		EventItem<double> MET_CellOut_Eflow_STVF_Et;
		EventItem<double> MET_CellOut_Eflow_STVF_Phi;
		EventItem<double> MET_CellOut_Eflow_STVF_SumEt;
		EventItem<double> MET_CellOut_Eflow_Et;
		EventItem<double> MET_CellOut_Eflow_Phi;
		EventItem<double> MET_CellOut_Eflow_SumEt;
		
		//Truth
		EventItem<int> Truth_initial;
		EventItem<int> Truth_final;


		//Trigger Info
		/*
		EventItem<double> EF_mu36_tight;
		EventItem<double> EF_mu24i_tight;
		EventItem<double> EF_e24vhi_medium1;
		EventItem<double> EF_e60_medium1;
		*/




/**** Calculated Data ****/

//		void calculate_all();
//		void calculate_fast();
//		
//		void null_all();
//		void null_fast();
		

		
};

} // End: namespace wwwAnalysis

#endif
