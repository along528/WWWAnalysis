#include "wwwAnalysis/EventData.h"
#include "wwwAnalysis/Functions.h"
#include "TMatrix.h"
#include "TVector2.h"
#include "TVector.h"
#include "TDirectory.h"
#include <cmath>

template<class T> const char *wwwAnalysis::EventItem<T>::TypeName = 0;
//template<> const char *wwwAnalysis::EventItem<wwwAnalysis::InitialState>::TypeName = "wwwAnalysis::InitialState";
//template<> const char *wwwAnalysis::EventItem<wwwAnalysis::FinalState>::TypeName = "wwwAnalysis::FinalState";
template<> const char *wwwAnalysis::EventItem<TLorentzVector *>::TypeName = "TLorentzVector";
template<> const char *wwwAnalysis::EventItem<std::vector<TLorentzVector> *>::TypeName = "std::vector<TLorentzVector>";
template<> const char *wwwAnalysis::EventItem<std::vector<bool> *>::TypeName = "std::vector<bool>";
template<> const char *wwwAnalysis::EventItem<std::vector<double> *>::TypeName = "std::vector<double>";
template<> const char *wwwAnalysis::EventItem<std::vector<int> *>::TypeName = "std::vector<int>";
template<> const char *wwwAnalysis::EventItem<std::vector<unsigned int> *>::TypeName = "std::vector<unsigned int>";
//template<> const char *wwwAnalysis::EventItem<Root::TAccept *>::TypeName = "Root::TAccept";


//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::EventData::EventData()
:m_pTree(0)
{
//	for(int i = 0; i < 3; i++)
//	{
//		Lep[i].setName(std::string("lep")+(char)('1'+i)+"_momentum.");
////		Lep_centrality[i].setName(std::string("lep")+(char)('1'+i)+"_centrality");
//		Lep_ptiso[i].setName(std::string("lep")+(char)('1'+i)+"_ptiso");
//		Lep_etiso[i].setName(std::string("lep")+(char)('1'+i)+"_etiso");
//		Lep_z0_exPV[i].setName(std::string("lep")+(char)('1'+i)+"_z0pv");
//		Lep_loose[i].setName(std::string("lep")+(char)('1'+i)+"_loose");
//		Lep_medium[i].setName(std::string("lep")+(char)('1'+i)+"_medium");
//		Lep_tight[i].setName(std::string("lep")+(char)('1'+i)+"_tight");
//		Lep_veryLooseLL[i].setName(std::string("lep")+(char)('1'+i)+"_veryLooseLL");
//		Lep_looseLL[i].setName(std::string("lep")+(char)('1'+i)+"_looseLL");
//		Lep_mediumLL[i].setName(std::string("lep")+(char)('1'+i)+"_mediumLL");
//		Lep_tightLL[i].setName(std::string("lep")+(char)('1'+i)+"_tightLL");
//		Lep_veryTightLL[i].setName(std::string("lep")+(char)('1'+i)+"_veryTightLL");
//		Lep_isMuon[i].setName(std::string("lep")+(char)('1'+i)+"_isMuon");
//		Lep_isFake[i].setName(std::string("lep")+(char)('1'+i)+"_isFake");
//		Lep_author[i].setName(std::string("lep")+(char)('1'+i)+"_author");
//		Lep_recoAuthor[i].setName(std::string("lep")+(char)('1'+i)+"_recoAuthor");
//		Lep_eta[i].setName(std::string("lep")+(char)('1'+i)+"_eta");
//		Lep_phi[i].setName(std::string("lep")+(char)('1'+i)+"_phi");
//		Lep_pt[i].setName(std::string("lep")+(char)('1'+i)+"_pt");
//		Lep_d0[i].setName(std::string("lep")+(char)('1'+i)+"_d0");
//		Lep_sigmad0[i].setName(std::string("lep")+(char)('1'+i)+"_sigmad0");
//		Lep_track_z0[i].setName(std::string("lep")+(char)('1'+i)+"_track_z0");
//		Lep_track_d0[i].setName(std::string("lep")+(char)('1'+i)+"_track_d0");
//		Lep_track_sigz0[i].setName(std::string("lep")+(char)('1'+i)+"_track_sigz0");
//		Lep_track_sigd0[i].setName(std::string("lep")+(char)('1'+i)+"_track_sigd0");
//		Lep_smeared_d0[i].setName(std::string("lep")+(char)('1'+i)+"_smeared_sigd0");
//		Lep_charge[i].setName(std::string("lep")+(char)('1'+i)+"_charge");
//		Lep_isChargeFlipped[i].setName(std::string("lep")+(char)('1'+i)+"_isChargeFlipped");


		
		/*
		if(i<2){
		Jet_p[i].setName(std::string("jet")+(char)('1'+i)+"_momentum.");
		Jet_eta[i].setName(std::string("jet")+(char)('1'+i)+"_eta");
		Jet_pt[i].setName(std::string("jet")+(char)('1'+i)+"_pt");
		Jet_phi[i].setName(std::string("jet")+(char)('1'+i)+"_phi");
		}
		*/

//	}


	nLep.setName("nLep");
	nLep_fake.setName("nLep_fake");
	nAllLep.setName("nAllLep");
	nLep_LooseNotTight.setName("nLep_LooseNotTight");
	nLep_Tag.setName("nLep_Tag");
	nLep_Tag2.setName("nLep_Tag2");
	nLep_Probe.setName("nLep_Probe");
	nLep_Loose.setName("nLep_Loose");
	//nLep_inc.setName("nLep_inc");

	Lep.setName("lep_momentum");
	//Lep_inc.setName("lep_inc_momentum");
	Lep_ptiso.setName("lep_ptiso");
	Lep_etiso.setName("lep_etiso");
	Lep_z0_exPV.setName("lep_z0pv");
	Lep_loose.setName("lep_loose");
	Lep_medium.setName("lep_medium");
	Lep_tight.setName("lep_tight");
	Lep_veryLooseLL.setName("lep_veryLooseLL");
	Lep_looseLL.setName("lep_looseLL");
	Lep_mediumLL.setName("lep_mediumLL");
	Lep_tightLL.setName("lep_tightLL");
	Lep_veryTightLL.setName("lep_veryTightLL");
	Lep_author.setName("lep_author");
	Lep_recoAuthor.setName("lep_recoAuthor");
	Lep_isSignalLike.setName("lep_isSignalLike");
	Lep_isFromHeavyFlavor.setName("lep_isFromHeavyFlavor");
	Lep_isFromLightFlavor.setName("lep_isFromLightFlavor");
	Lep_isFromPhotonConversion.setName("lep_isFromPhotonConversion");

	Lep_eta.setName("lep_eta");
	Lep_phi.setName("lep_phi");
	Lep_pt.setName("lep_pt");
	Lep_mt.setName("lep_mt");
	Lep_mt_STVF.setName("lep_mt_STVF");
	ComEnergySquared.setName("comEnergySquared");
	AllLep_mt.setName("allLep_mt");
	AllLep_mt_STVF.setName("allLep_mt_STVF");
	AllLep_deltaPhiMET.setName("allLep_deltaPhiMET");
	AllLep_deltaPhiMET_STVF.setName("allLep_deltaPhiMET_STVF");
	Lep_d0.setName("lep_d0");
	Lep_sigmad0.setName("lep_sigmad0");
	Lep_track_z0.setName("lep_track_z0");
	Lep_track_d0.setName("lep_track_d0");
	Lep_track_sigz0.setName("lep_track_sigz0");
	Lep_track_sigd0.setName("lep_track_sigd0");
	Lep_track_theta.setName("lep_track_theta");
	Lep_track_d0_o_sigd0.setName("lep_track_d0_o_sigd0");
	Lep_track_z0_o_sinTheta.setName("lep_track_z0_o_sinTheta");
	Lep_charge.setName("lep_charge");
	//Lep_inc_charge.setName("lep_inc_charge");
	Lep_isChargeFlipped.setName("lep_isChargeFlipped");
	//Lep_inc_isChargeFlipped.setName("lep_inc_isChargeFlipped");
	
	AllLep.setName("allLep_momentum");
	//Lep_inc.setName("lep_inc_momentum");
	AllLep_ptiso.setName("allLep_ptiso");
	AllLep_etiso.setName("allLep_etiso");
	AllLep_z0_exPV.setName("allLep_z0pv");
	AllLep_loose.setName("allLep_loose");
	AllLep_medium.setName("allLep_medium");
	AllLep_tight.setName("allLep_tight");
	AllLep_veryLooseLL.setName("allLep_veryLooseLL");
	AllLep_looseLL.setName("allLep_looseLL");
	AllLep_mediumLL.setName("allLep_mediumLL");
	AllLep_tightLL.setName("allLep_tightLL");
	AllLep_veryTightLL.setName("allLep_veryTightLL");
	AllLep_author.setName("allLep_author");
	AllLep_recoAuthor.setName("allLep_recoAuthor");
	AllLep_eta.setName("allLep_eta");
	AllLep_phi.setName("allLep_phi");
	AllLep_pt.setName("allLep_pt");
	AllLep_d0.setName("allLep_d0");
	AllLep_sigmad0.setName("allLep_sigmad0");
	AllLep_track_z0.setName("allLep_track_z0");
	AllLep_track_d0.setName("allLep_track_d0");
	AllLep_track_sigz0.setName("allLep_track_sigz0");
	AllLep_track_sigd0.setName("allLep_track_sigd0");
	AllLep_smeared_d0.setName("allLep_smeared_sigd0");
	AllLep_charge.setName("allLep_charge");
	//Lep_inc_charge.setName("lep_inc_charge");
	AllLep_isChargeFlipped.setName("allLep_isChargeFlipped");
	//Lep_inc_isChargeFlipped.setName("lep_inc_isChargeFlipped");
	
   Lep_isSFOS.setName("lep_isSFOS");


	//
	//
	//
	//
	Lep_LooseNotTight.setName("lep_momentum_LooseNotTight");
	//Lep_inc.setName("lep_inc_momentum");
	Lep_ptiso_LooseNotTight.setName("lep_ptiso_LooseNotTight");
	Lep_etiso_LooseNotTight.setName("lep_etiso_LooseNotTight");
	Lep_z0_exPV_LooseNotTight.setName("lep_z0pv_LooseNotTight");
	Lep_loose_LooseNotTight.setName("lep_loose_LooseNotTight");
	Lep_medium_LooseNotTight.setName("lep_medium_LooseNotTight");
	Lep_tight_LooseNotTight.setName("lep_tight_LooseNotTight");
	Lep_veryLooseLL_LooseNotTight.setName("lep_veryLooseLL_LooseNotTight");
	Lep_looseLL_LooseNotTight.setName("lep_looseLL_LooseNotTight");
	Lep_mediumLL_LooseNotTight.setName("lep_mediumLL_LooseNotTight");
	Lep_tightLL_LooseNotTight.setName("lep_tightLL_LooseNotTight");
	Lep_veryTightLL_LooseNotTight.setName("lep_veryTightLL_LooseNotTight");
	Lep_author_LooseNotTight.setName("lep_author_LooseNotTight");
	Lep_recoAuthor_LooseNotTight.setName("lep_recoAuthor_LooseNotTight");

	Lep_isSignalLike_LooseNotTight.setName("lep_isSignalLike_LooseNotTight");
	Lep_isFromHeavyFlavor_LooseNotTight.setName("lep_isFromHeavyFlavor_LooseNotTight");
	Lep_isFromLightFlavor_LooseNotTight.setName("lep_isFromLightFlavor_LooseNotTight");
	Lep_isFromPhotonConversion_LooseNotTight.setName("lep_isFromPhotonConversion_LooseNotTight");
	Lep_eta_LooseNotTight.setName("lep_eta_LooseNotTight");
	Lep_phi_LooseNotTight.setName("lep_phi_LooseNotTight");
	Lep_pt_LooseNotTight.setName("lep_pt_LooseNotTight");
	Lep_mt_LooseNotTight.setName("lep_mt_LooseNotTight");
	Lep_mt_STVF_LooseNotTight.setName("lep_mt_STVF_LooseNotTight");

	Lep_d0_LooseNotTight.setName("lep_d0_LooseNotTight");
	Lep_sigmad0_LooseNotTight.setName("lep_sigmad0_LooseNotTight");
	Lep_track_z0_LooseNotTight.setName("lep_track_z0_LooseNotTight");
	Lep_track_d0_LooseNotTight.setName("lep_track_d0_LooseNotTight");
	Lep_track_sigz0_LooseNotTight.setName("lep_track_sigz0_LooseNotTight");
	Lep_track_sigd0_LooseNotTight.setName("lep_track_sigd0_LooseNotTight");
	Lep_smeared_d0_LooseNotTight.setName("lep_smeared_sigd0_LooseNotTight");
	Lep_charge_LooseNotTight.setName("lep_charge_LooseNotTight");
	//Lep_inc_charge.setName("lep_inc_charge");
	Lep_isChargeFlipped_LooseNotTight.setName("lep_isChargeFlipped_LooseNotTight");
	//Lep_inc_isChargeFlipped.setName("lep_inc_isChargeFlipped");
	//
	//
	Lep_Tag.setName("lep_momentum_Tag");
	//Lep_inc.setName("lep_inc_momentum");
	Lep_ptiso_Tag.setName("lep_ptiso_Tag");
	Lep_etiso_Tag.setName("lep_etiso_Tag");
	Lep_z0_exPV_Tag.setName("lep_z0pv_Tag");
	Lep_loose_Tag.setName("lep_loose_Tag");
	Lep_medium_Tag.setName("lep_medium_Tag");
	Lep_tight_Tag.setName("lep_tight_Tag");
	Lep_veryLooseLL_Tag.setName("lep_veryLooseLL_Tag");
	Lep_looseLL_Tag.setName("lep_looseLL_Tag");
	Lep_mediumLL_Tag.setName("lep_mediumLL_Tag");
	Lep_tightLL_Tag.setName("lep_tightLL_Tag");
	Lep_veryTightLL_Tag.setName("lep_veryTightLL_Tag");
	Lep_author_Tag.setName("lep_author_Tag");
	Lep_recoAuthor_Tag.setName("lep_recoAuthor_Tag");

	Lep_isSignalLike_Tag.setName("lep_isSignalLike_Tag");
	Lep_isFromHeavyFlavor_Tag.setName("lep_isFromHeavyFlavor_Tag");
	Lep_isFromLightFlavor_Tag.setName("lep_isFromLightFlavor_Tag");
	Lep_isFromPhotonConversion_Tag.setName("lep_isFromPhotonConversion_Tag");

	Lep_eta_Tag.setName("lep_eta_Tag");
	Lep_phi_Tag.setName("lep_phi_Tag");
	Lep_pt_Tag.setName("lep_pt_Tag");
	Lep_mt_Tag.setName("lep_mt_Tag");
	Lep_mt_STVF_Tag.setName("lep_mt_STVF_Tag");
	Lep_track_d0_o_sigd0_Tag.setName("lep_track_d0_o_sigd0_Tag");
	Lep_track_z0_o_sinTheta_Tag.setName("lep_track_z0_o_sinTheta_Tag");

	Lep_d0_Tag.setName("lep_d0_Tag");
	Lep_sigmad0_Tag.setName("lep_sigmad0_Tag");
	Lep_track_z0_Tag.setName("lep_track_z0_Tag");
	Lep_track_d0_Tag.setName("lep_track_d0_Tag");
	Lep_track_sigz0_Tag.setName("lep_track_sigz0_Tag");
	Lep_track_sigd0_Tag.setName("lep_track_sigd0_Tag");
	Lep_smeared_d0_Tag.setName("lep_smeared_sigd0_Tag");
	Lep_charge_Tag.setName("lep_charge_Tag");
	//Lep_inc_charge.setName("lep_inc_charge");
	Lep_isChargeFlipped_Tag.setName("lep_isChargeFlipped_Tag");

	Lep_Tag2.setName("lep_momentum_Tag2");
	//Lep_inc.setName("lep_inc_momentum");
	Lep_ptiso_Tag2.setName("lep_ptiso_Tag2");
	Lep_etiso_Tag2.setName("lep_etiso_Tag2");
	Lep_z0_exPV_Tag2.setName("lep_z0pv_Tag2");
	Lep_loose_Tag2.setName("lep_loose_Tag2");
	Lep_medium_Tag2.setName("lep_medium_Tag2");
	Lep_tight_Tag2.setName("lep_tight_Tag2");
	Lep_veryLooseLL_Tag2.setName("lep_veryLooseLL_Tag2");
	Lep_looseLL_Tag2.setName("lep_looseLL_Tag2");
	Lep_mediumLL_Tag2.setName("lep_mediumLL_Tag2");
	Lep_tightLL_Tag2.setName("lep_tightLL_Tag2");
	Lep_veryTightLL_Tag2.setName("lep_veryTightLL_Tag2");
	Lep_author_Tag2.setName("lep_author_Tag2");
	Lep_recoAuthor_Tag2.setName("lep_recoAuthor_Tag2");
	Lep_isSignalLike_Tag2.setName("lep_isSignalLike_Tag2");
	Lep_isFromHeavyFlavor_Tag2.setName("lep_isFromHeavyFlavor_Tag2");
	Lep_isFromLightFlavor_Tag2.setName("lep_isFromLightFlavor_Tag2");
	Lep_isFromPhotonConversion_Tag2.setName("lep_isFromPhotonConversion_Tag2");
	Lep_eta_Tag2.setName("lep_eta_Tag2");
	Lep_phi_Tag2.setName("lep_phi_Tag2");
	Lep_pt_Tag2.setName("lep_pt_Tag2");
	Lep_mt_Tag2.setName("lep_mt_Tag2");
	Lep_mt_STVF_Tag2.setName("lep_mt_STVF_Tag2");
	Lep_track_d0_o_sigd0_Tag2.setName("lep_track_d0_o_sigd0_Tag2");
	Lep_track_z0_o_sinTheta_Tag2.setName("lep_track_z0_o_sinTheta_Tag2");

	Lep_d0_Tag2.setName("lep_d0_Tag2");
	Lep_sigmad0_Tag2.setName("lep_sigmad0_Tag2");
	Lep_track_z0_Tag2.setName("lep_track_z0_Tag2");
	Lep_track_d0_Tag2.setName("lep_track_d0_Tag2");
	Lep_track_sigz0_Tag2.setName("lep_track_sigz0_Tag2");
	Lep_track_sigd0_Tag2.setName("lep_track_sigd0_Tag2");
	Lep_smeared_d0_Tag2.setName("lep_smeared_sigd0_Tag2");
	Lep_charge_Tag2.setName("lep_charge_Tag2");
	//Lep_inc_charge.setName("lep_inc_charge");
	Lep_isChargeFlipped_Tag2.setName("lep_isChargeFlipped_Tag2");


	Lep_Probe.setName("lep_momentum_Probe");
	//Lep_inc.setName("lep_inc_momentum");
	Lep_ptiso_Probe.setName("lep_ptiso_Probe");
	Lep_etiso_Probe.setName("lep_etiso_Probe");
	Lep_z0_exPV_Probe.setName("lep_z0pv_Probe");
	Lep_loose_Probe.setName("lep_loose_Probe");
	Lep_medium_Probe.setName("lep_medium_Probe");
	Lep_tight_Probe.setName("lep_tight_Probe");
	Lep_veryLooseLL_Probe.setName("lep_veryLooseLL_Probe");
	Lep_looseLL_Probe.setName("lep_looseLL_Probe");
	Lep_mediumLL_Probe.setName("lep_mediumLL_Probe");
	Lep_tightLL_Probe.setName("lep_tightLL_Probe");
	Lep_veryTightLL_Probe.setName("lep_veryTightLL_Probe");
	Lep_author_Probe.setName("lep_author_Probe");
	Lep_recoAuthor_Probe.setName("lep_recoAuthor_Probe");
	Lep_isSignalLike_Probe.setName("lep_isSignalLike_Probe");
	Lep_isFromHeavyFlavor_Probe.setName("lep_isFromHeavyFlavor_Probe");
	Lep_isFromLightFlavor_Probe.setName("lep_isFromLightFlavor_Probe");
	Lep_isFromPhotonConversion_Probe.setName("lep_isFromPhotonConversion_Probe");
	Lep_eta_Probe.setName("lep_eta_Probe");
	Lep_phi_Probe.setName("lep_phi_Probe");
	Lep_pt_Probe.setName("lep_pt_Probe");
	Lep_mt_Probe.setName("lep_mt_Probe");
	Lep_mt_STVF_Probe.setName("lep_mt_STVF_Probe");

	Lep_d0_Probe.setName("lep_d0_Probe");
	Lep_sigmad0_Probe.setName("lep_sigmad0_Probe");
	Lep_track_z0_Probe.setName("lep_track_z0_Probe");
	Lep_track_d0_Probe.setName("lep_track_d0_Probe");
	Lep_track_sigz0_Probe.setName("lep_track_sigz0_Probe");
	Lep_track_sigd0_Probe.setName("lep_track_sigd0_Probe");
	Lep_smeared_d0_Probe.setName("lep_smeared_sigd0_Probe");
	Lep_charge_Probe.setName("lep_charge_Probe");
	//Lep_inc_charge.setName("lep_inc_charge");
	Lep_isChargeFlipped_Probe.setName("lep_isChargeFlipped_Probe");
	Lep_track_d0_o_sigd0_Probe.setName("lep_track_d0_o_sigd0_Probe");
	Lep_track_z0_o_sinTheta_Probe.setName("lep_track_z0_o_sinTheta_Probe");

	
	Lep_Loose.setName("lep_momentum_Loose");
	//Lep_inc.setName("lep_inc_momentum");
	Lep_ptiso_Loose.setName("lep_ptiso_Loose");
	Lep_etiso_Loose.setName("lep_etiso_Loose");
	Lep_z0_exPV_Loose.setName("lep_z0pv_Loose");
	Lep_loose_Loose.setName("lep_loose_Loose");
	Lep_medium_Loose.setName("lep_medium_Loose");
	Lep_tight_Loose.setName("lep_tight_Loose");
	Lep_veryLooseLL_Loose.setName("lep_veryLooseLL_Loose");
	Lep_looseLL_Loose.setName("lep_looseLL_Loose");
	Lep_mediumLL_Loose.setName("lep_mediumLL_Loose");
	Lep_tightLL_Loose.setName("lep_tightLL_Loose");
	Lep_veryTightLL_Loose.setName("lep_veryTightLL_Loose");
	Lep_author_Loose.setName("lep_author_Loose");
	Lep_recoAuthor_Loose.setName("lep_recoAuthor_Loose");

	Lep_isSignalLike_Loose.setName("lep_isSignalLike_Loose");
	Lep_isFromHeavyFlavor_Loose.setName("lep_isFromHeavyFlavor_Loose");
	Lep_isFromLightFlavor_Loose.setName("lep_isFromLightFlavor_Loose");
	Lep_isFromPhotonConversion_Loose.setName("lep_isFromPhotonConversion_Loose");

	Lep_eta_Loose.setName("lep_eta_Loose");
	Lep_phi_Loose.setName("lep_phi_Loose");
	Lep_pt_Loose.setName("lep_pt_Loose");
	Lep_mt_Loose.setName("lep_mt_Loose");
	Lep_mt_STVF_Loose.setName("lep_mt_STVF_Loose");

	Lep_d0_Loose.setName("lep_d0_Loose");
	Lep_sigmad0_Loose.setName("lep_sigmad0_Loose");
	Lep_track_z0_Loose.setName("lep_track_z0_Loose");
	Lep_track_d0_Loose.setName("lep_track_d0_Loose");
	Lep_track_sigz0_Loose.setName("lep_track_sigz0_Loose");
	Lep_track_sigd0_Loose.setName("lep_track_sigd0_Loose");
	Lep_smeared_d0_Loose.setName("lep_smeared_sigd0_Loose");
	Lep_charge_Loose.setName("lep_charge_Loose");
	//Lep_inc_charge.setName("lep_inc_charge");
	Lep_isChargeFlipped_Loose.setName("lep_isChargeFlipped_Loose");

	/*
	Mu_inc_pt_loose.setName("Mu_inc_pt_loose");
	Mu_inc_pt_medium.setName("Mu_inc_pt_medium");
	Mu_inc_pt_tight.setName("Mu_inc_pt_tight");
	El_inc_pt_loose.setName("El_inc_pt_loose");
	El_inc_pt_medium.setName("El_inc_pt_medium");
	El_inc_pt_tight.setName("El_inc_pt_tight");
	El_inc_pt_veryLooseLL.setName("El_inc_pt_veryLooseLL");
	El_inc_pt_looseLL.setName("El_inc_pt_looseLL");
	El_inc_pt_mediumLL.setName("El_inc_pt_mediumLL");
	El_inc_pt_tightLL.setName("El_inc_pt_tightLL");
	El_inc_pt_veryTightLL.setName("El_inc_pt_veryTightLL");
	*/



	Lep_isMuon.setName("lep_isMuon");
	Lep_isCombinedMuon.setName("lep_isCombinedMuon");
	AllLep_isMuon.setName("allLep_isMuon");
	AllLep_isCombinedMuon.setName("allLep_isCombinedMuon");
	Lep_isSpectroMuon.setName("lep_isSpectroMuon");
	AllLep_isSpectroMuon.setName("allLep_isSpectroMuon");
	Lep_isMuon_LooseNotTight.setName("lep_isMuon_LooseNotTight");
	Lep_isCombinedMuon_LooseNotTight.setName("lep_isCombinedMuon_LooseNotTight");
	Lep_isMuon_Tag.setName("lep_isMuon_Tag");
	Lep_isCombinedMuon_Tag.setName("lep_isCombinedMuon_Tag");
	Lep_isMuon_Tag2.setName("lep_isMuon_Tag2");
	Lep_isCombinedMuon_Tag2.setName("lep_isCombinedMuon_Tag2");
	Lep_isMuon_Probe.setName("lep_isMuon_Probe");
	Lep_isCombinedMuon_Probe.setName("lep_isCombinedMuon_Probe");
	Lep_isSpectroMuon_LooseNotTight.setName("lep_isSpectroMuon_LooseNotTight");
	Lep_isMuon_Loose.setName("lep_isMuon_Loose");
	Lep_isCombinedMuon_Loose.setName("lep_isCombinedMuon_Loose");
	Lep_isSpectroMuon_Loose.setName("lep_isSpectroMuon_Loose");
	//Lep_inc_isMuon.setName("lep_inc_isMuon");
	//Lep_inc_isCombined.setName("lep_inc_isCombined");
	Lep_isFake.setName("lep_isFake");
	AllLep_isFake.setName("allLep_isFake");
	Lep_isFake_LooseNotTight.setName("lep_isFake_LooseNotTight");
	Lep_isFake_Loose.setName("lep_isFake_Loose");
	//Lep_inc_isFake.setName("lep_inc_isFake");

	Jets.setName("jets_momentum");
	bJets.setName("jets_btagged");
	JetsJVF.setName("jets_jvf");
	
	MET_final_Et.setName("MET_final_Et");
	MET_final_phi.setName("MET_final_phi");
	MET_final_sumEt.setName("MET_final_sumEt");

	MET_final_Et_raw.setName("MET_final_Et_raw");
	MET_final_phi_raw.setName("MET_final_phi_raw");
	MET_final_sumEt_raw.setName("MET_final_sumEt_raw");

	MET_final_Et_STVF.setName("MET_final_Et_STVF");
	MET_final_phi_STVF.setName("MET_final_phi_STVF");
	MET_final_sumEt_STVF.setName("MET_final_sumEt_STVF");
	mu.setName("mu");
	//btagsEff60.setName("btagEff60");
	//btagsEff70.setName("btagEff70");
	//btagsEff80.setName("btagEff80");
	btagsEff85.setName("btagEff85");
	nPV_2trks.setName("nPV2");
	nPV_3trks.setName("nPV3");
	FakeLeptons.setName("fake");
        TriLepton.setName("trilepton");
	OSLeptons.setName("os");

	nSFOS.setName("nSFOS");
	nSFOSAll.setName("nSFOS_all");

	massesSFOS.setName("masses_SFOS");
	massesSFOSAll.setName("masses_SFOS_all");
	massesElEl.setName("masses_ElEl");
	massesElMu.setName("masses_ElMu");
	massesMuMu.setName("masses_MuMu");

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
	DoChargeFlip.setName("doChargeFlip");
	XSecWeight.setName("weight_xsec");
	MxMWeight.setName("weight_mxm");
	FormFactorWeight.setName("weight_formfactor");
	CorrectionWeight.setName("weight_correction");
	LumiWeight.setName("weight_lumi");
	MET_CellOut_Eflow_STVF_Et.setName("MET_CellOut_Eflow_STVF_Et");
	MET_CellOut_Eflow_STVF_Phi.setName("MET_CellOut_Eflow_STVF_Phi");
	MET_CellOut_Eflow_STVF_SumEt.setName("MET_CellOut_Eflow_STVF_SumEt");
	MET_CellOut_Eflow_Et.setName("MET_CellOut_Eflow_Et");
	MET_CellOut_Eflow_Phi.setName("MET_CellOut_Eflow_Phi");
	MET_CellOut_Eflow_SumEt.setName("MET_CellOut_Eflow_SumEt");

	
	RunNumber.setName("RunNumber");
	EventNumber.setName("EventNumber");
	lbn.setName("lbn");

	PrimaryVertexNTracks.setName("primary_vertex_ntracks");

	hasLooseNotTightMuons.setName("hasLooseNotTightMuons");
	hasLooseNotTightElectrons.setName("hasLooseNotTightElectrons");

	isEGammaStream.setName("isEGammaStream");
	eventHasSpectroMuons.setName("eventHasSpectroMuons");
	Truth_initial.setName("Truth_initial");
	Truth_final.setName("Truth_final");

	Lep_4lpair.setName("Lep_4lpair");
	DiLepton.setName("DiLepton");
	QuadriLepton.setName("QuadriLepton");
	mll.setName("mll");
	mT1.setName("mT1");
	mT2.setName("mT2");
	m12.setName("m12");
	m34.setName("m34");
	m4l.setName("m4l");
	SumHPTO.setName("SumHPTO");
	SumCosDphi.setName("SumCosDphi");


	/*
	EF_mu36_tight.setName("EF_mu36_tight");
	EF_mu24i_tight.setName("EF_mu24i_tight");
	EF_e24vhi_medium1.setName("EF_e24vhi_medium1");
	EF_e60_medium1.setName("EF_e60_medium1");
	*/
	
}

void wwwAnalysis::EventData::initialize2(const char *out_name, TTree *tree, TreeReadWrite io)
{
	initialize(out_name,tree,io);
}
void wwwAnalysis::EventData::initialize(const char *out_name, TTree *tree, TreeReadWrite io)
{
  //Declare the TTree:
  m_pTree = tree;
  if(tree == 0)
    //      m_pTree= new TTree("physics","physics");
    m_pTree= new TTree(out_name,out_name);
  if(io == TREE_WRITE)
  {
	  m_pTree->SetAutoSave(100000000);
  	m_pTree->SetAutoFlush( 30000000 );
  	TTree::SetBranchStyle(1);
  }
	nLep.setupBranch(m_pTree, io);
	nLep_fake.setupBranch(m_pTree, io);
	nAllLep.setupBranch(m_pTree, io);
	nLep_LooseNotTight.setupBranch(m_pTree, io);
	nLep_Tag.setupBranch(m_pTree, io);
	nLep_Tag2.setupBranch(m_pTree, io);
	nLep_Probe.setupBranch(m_pTree, io);
	nLep_Loose.setupBranch(m_pTree, io);

	//nLep_inc.setupBranch(m_pTree, io);
	Lep.setupBranch(m_pTree, io);
	//Lep_inc.setupBranch(m_pTree, io);
	Lep_ptiso.setupBranch(m_pTree, io);
	Lep_etiso.setupBranch(m_pTree, io);
	Lep_z0_exPV.setupBranch(m_pTree, io);
	Lep_loose.setupBranch(m_pTree, io);
	Lep_medium.setupBranch(m_pTree, io);
	Lep_tight.setupBranch(m_pTree, io);
	Lep_veryLooseLL.setupBranch(m_pTree, io);
	Lep_looseLL.setupBranch(m_pTree, io);
	Lep_mediumLL.setupBranch(m_pTree, io);
	Lep_tightLL.setupBranch(m_pTree, io);
	Lep_veryTightLL.setupBranch(m_pTree, io);

	Lep_author.setupBranch(m_pTree, io);
	Lep_recoAuthor.setupBranch(m_pTree, io);

	Lep_isSignalLike.setupBranch(m_pTree,io);
	Lep_isFromHeavyFlavor.setupBranch(m_pTree,io);
	Lep_isFromLightFlavor.setupBranch(m_pTree,io);
	Lep_isFromPhotonConversion.setupBranch(m_pTree,io);
	Lep_eta.setupBranch(m_pTree, io);
	Lep_phi.setupBranch(m_pTree, io);
	Lep_pt.setupBranch(m_pTree, io);
	ComEnergySquared.setupBranch(m_pTree, io);
	AllLep_mt.setupBranch(m_pTree, io);
	AllLep_mt_STVF.setupBranch(m_pTree, io);
	AllLep_deltaPhiMET.setupBranch(m_pTree, io);
	AllLep_deltaPhiMET_STVF.setupBranch(m_pTree, io);
	Lep_mt.setupBranch(m_pTree, io);
	Lep_mt_STVF.setupBranch(m_pTree, io);
	Lep_d0.setupBranch(m_pTree, io);
	Lep_sigmad0.setupBranch(m_pTree, io);
	Lep_track_z0.setupBranch(m_pTree, io);
	Lep_track_d0.setupBranch(m_pTree, io);
	Lep_track_sigz0.setupBranch(m_pTree, io);
	Lep_track_sigd0.setupBranch(m_pTree, io);
	Lep_track_theta.setupBranch(m_pTree, io);
	Lep_track_d0_o_sigd0.setupBranch(m_pTree, io);
	Lep_track_z0_o_sinTheta.setupBranch(m_pTree, io);
	Lep_charge.setupBranch(m_pTree, io);
	//Lep_inc_charge.setupBranch(m_pTree, io);
	Lep_isChargeFlipped.setupBranch(m_pTree, io);
	//Lep_inc_isChargeFlipped.setupBranch(m_pTree, io);
	//
	AllLep.setupBranch(m_pTree, io);
	//Lep_inc.setupBranch(m_pTree, io);
	AllLep_ptiso.setupBranch(m_pTree, io);
	AllLep_etiso.setupBranch(m_pTree, io);
	AllLep_z0_exPV.setupBranch(m_pTree, io);
	AllLep_loose.setupBranch(m_pTree, io);
	AllLep_medium.setupBranch(m_pTree, io);
	AllLep_tight.setupBranch(m_pTree, io);
	AllLep_veryLooseLL.setupBranch(m_pTree, io);
	AllLep_looseLL.setupBranch(m_pTree, io);
	AllLep_mediumLL.setupBranch(m_pTree, io);
	AllLep_tightLL.setupBranch(m_pTree, io);
	AllLep_veryTightLL.setupBranch(m_pTree, io);
   Lep_isSFOS.setupBranch(m_pTree, io);

	AllLep_author.setupBranch(m_pTree, io);
	AllLep_recoAuthor.setupBranch(m_pTree, io);
	AllLep_eta.setupBranch(m_pTree, io);
	AllLep_phi.setupBranch(m_pTree, io);
	AllLep_d0.setupBranch(m_pTree, io);
	AllLep_sigmad0.setupBranch(m_pTree, io);
	AllLep_track_z0.setupBranch(m_pTree, io);
	AllLep_track_d0.setupBranch(m_pTree, io);
	AllLep_track_sigz0.setupBranch(m_pTree, io);
	AllLep_track_sigd0.setupBranch(m_pTree, io);
	AllLep_smeared_d0.setupBranch(m_pTree, io);
	AllLep_charge.setupBranch(m_pTree, io);
	//Lep_inc_charge.setupBranch(m_pTree, io);
	AllLep_isChargeFlipped.setupBranch(m_pTree, io);
	//Lep_inc_isChargeFlipped.setupBranch(m_pTree, io);
	
	Lep_LooseNotTight.setupBranch(m_pTree, io);
	//Lep_inc.setupBranch(m_pTree, io);
	Lep_ptiso_LooseNotTight.setupBranch(m_pTree, io);
	Lep_etiso_LooseNotTight.setupBranch(m_pTree, io);
	Lep_z0_exPV_LooseNotTight.setupBranch(m_pTree, io);
	Lep_loose_LooseNotTight.setupBranch(m_pTree, io);
	Lep_medium_LooseNotTight.setupBranch(m_pTree, io);
	Lep_tight_LooseNotTight.setupBranch(m_pTree, io);
	Lep_veryLooseLL_LooseNotTight.setupBranch(m_pTree, io);
	Lep_looseLL_LooseNotTight.setupBranch(m_pTree, io);
	Lep_mediumLL_LooseNotTight.setupBranch(m_pTree, io);
	Lep_tightLL_LooseNotTight.setupBranch(m_pTree, io);
	Lep_veryTightLL_LooseNotTight.setupBranch(m_pTree, io);

	Lep_author_LooseNotTight.setupBranch(m_pTree, io);
	Lep_recoAuthor_LooseNotTight.setupBranch(m_pTree, io);

	Lep_isSignalLike_LooseNotTight.setupBranch(m_pTree,io);
	Lep_isFromHeavyFlavor_LooseNotTight.setupBranch(m_pTree,io);
	Lep_isFromLightFlavor_LooseNotTight.setupBranch(m_pTree,io);
	Lep_isFromPhotonConversion_LooseNotTight.setupBranch(m_pTree,io);

	Lep_eta_LooseNotTight.setupBranch(m_pTree, io);
	Lep_phi_LooseNotTight.setupBranch(m_pTree, io);
	Lep_pt_LooseNotTight.setupBranch(m_pTree, io);
	Lep_mt_LooseNotTight.setupBranch(m_pTree, io);
	Lep_mt_STVF_LooseNotTight.setupBranch(m_pTree, io);
	Lep_d0_LooseNotTight.setupBranch(m_pTree, io);
	Lep_sigmad0_LooseNotTight.setupBranch(m_pTree, io);
	Lep_track_z0_LooseNotTight.setupBranch(m_pTree, io);
	Lep_track_d0_LooseNotTight.setupBranch(m_pTree, io);
	Lep_track_sigz0_LooseNotTight.setupBranch(m_pTree, io);
	Lep_track_sigd0_LooseNotTight.setupBranch(m_pTree, io);
	Lep_smeared_d0_LooseNotTight.setupBranch(m_pTree, io);
	Lep_charge_LooseNotTight.setupBranch(m_pTree, io);
	//Lep_inc_charge.setupBranch(m_pTree, io);
	Lep_isChargeFlipped_LooseNotTight.setupBranch(m_pTree, io);


	Lep_Tag.setupBranch(m_pTree, io);
	//Lep_inc.setupBranch(m_pTree, io);
	Lep_ptiso_Tag.setupBranch(m_pTree, io);
	Lep_etiso_Tag.setupBranch(m_pTree, io);
	Lep_z0_exPV_Tag.setupBranch(m_pTree, io);
	Lep_loose_Tag.setupBranch(m_pTree, io);
	Lep_medium_Tag.setupBranch(m_pTree, io);
	Lep_tight_Tag.setupBranch(m_pTree, io);
	Lep_veryLooseLL_Tag.setupBranch(m_pTree, io);
	Lep_looseLL_Tag.setupBranch(m_pTree, io);
	Lep_mediumLL_Tag.setupBranch(m_pTree, io);
	Lep_tightLL_Tag.setupBranch(m_pTree, io);
	Lep_veryTightLL_Tag.setupBranch(m_pTree, io);
	Lep_track_d0_o_sigd0_Tag.setupBranch(m_pTree, io);
	Lep_track_z0_o_sinTheta_Tag.setupBranch(m_pTree, io);

	Lep_author_Tag.setupBranch(m_pTree, io);
	Lep_recoAuthor_Tag.setupBranch(m_pTree, io);
	Lep_isSignalLike_Tag.setupBranch(m_pTree,io);
	Lep_isFromHeavyFlavor_Tag.setupBranch(m_pTree,io);
	Lep_isFromLightFlavor_Tag.setupBranch(m_pTree,io);
	Lep_isFromPhotonConversion_Tag.setupBranch(m_pTree,io);
	Lep_eta_Tag.setupBranch(m_pTree, io);
	Lep_phi_Tag.setupBranch(m_pTree, io);
	Lep_pt_Tag.setupBranch(m_pTree, io);
	Lep_mt_Tag.setupBranch(m_pTree, io);
	Lep_mt_STVF_Tag.setupBranch(m_pTree, io);
	Lep_d0_Tag.setupBranch(m_pTree, io);
	Lep_sigmad0_Tag.setupBranch(m_pTree, io);
	Lep_track_z0_Tag.setupBranch(m_pTree, io);
	Lep_track_d0_Tag.setupBranch(m_pTree, io);
	Lep_track_sigz0_Tag.setupBranch(m_pTree, io);
	Lep_track_sigd0_Tag.setupBranch(m_pTree, io);
	Lep_smeared_d0_Tag.setupBranch(m_pTree, io);
	Lep_charge_Tag.setupBranch(m_pTree, io);
	//Lep_inc_charge.setupBranch(m_pTree, io);
	Lep_isChargeFlipped_Tag.setupBranch(m_pTree, io);

	Lep_Tag2.setupBranch(m_pTree, io);
	//Lep_inc.setupBranch(m_pTree, io);
	Lep_ptiso_Tag2.setupBranch(m_pTree, io);
	Lep_etiso_Tag2.setupBranch(m_pTree, io);
	Lep_z0_exPV_Tag2.setupBranch(m_pTree, io);
	Lep_loose_Tag2.setupBranch(m_pTree, io);
	Lep_medium_Tag2.setupBranch(m_pTree, io);
	Lep_tight_Tag2.setupBranch(m_pTree, io);
	Lep_veryLooseLL_Tag2.setupBranch(m_pTree, io);
	Lep_looseLL_Tag2.setupBranch(m_pTree, io);
	Lep_mediumLL_Tag2.setupBranch(m_pTree, io);
	Lep_tightLL_Tag2.setupBranch(m_pTree, io);
	Lep_veryTightLL_Tag2.setupBranch(m_pTree, io);
	Lep_track_d0_o_sigd0_Tag2.setupBranch(m_pTree, io);
	Lep_track_z0_o_sinTheta_Tag2.setupBranch(m_pTree, io);

	Lep_author_Tag2.setupBranch(m_pTree, io);
	Lep_recoAuthor_Tag2.setupBranch(m_pTree, io);
	Lep_isSignalLike_Tag2.setupBranch(m_pTree,io);
	Lep_isFromHeavyFlavor_Tag2.setupBranch(m_pTree,io);
	Lep_isFromLightFlavor_Tag2.setupBranch(m_pTree,io);
	Lep_isFromPhotonConversion_Tag2.setupBranch(m_pTree,io);
	Lep_eta_Tag2.setupBranch(m_pTree, io);
	Lep_phi_Tag2.setupBranch(m_pTree, io);
	Lep_pt_Tag2.setupBranch(m_pTree, io);
	Lep_mt_Tag2.setupBranch(m_pTree, io);
	Lep_mt_STVF_Tag2.setupBranch(m_pTree, io);
	Lep_d0_Tag2.setupBranch(m_pTree, io);
	Lep_sigmad0_Tag2.setupBranch(m_pTree, io);
	Lep_track_z0_Tag2.setupBranch(m_pTree, io);
	Lep_track_d0_Tag2.setupBranch(m_pTree, io);
	Lep_track_sigz0_Tag2.setupBranch(m_pTree, io);
	Lep_track_sigd0_Tag2.setupBranch(m_pTree, io);
	Lep_smeared_d0_Tag2.setupBranch(m_pTree, io);
	Lep_charge_Tag2.setupBranch(m_pTree, io);
	//Lep_inc_charge.setupBranch(m_pTree, io);
	Lep_isChargeFlipped_Tag2.setupBranch(m_pTree, io);

	Lep_Probe.setupBranch(m_pTree, io);
	//Lep_inc.setupBranch(m_pTree, io);
	Lep_ptiso_Probe.setupBranch(m_pTree, io);
	Lep_etiso_Probe.setupBranch(m_pTree, io);
	Lep_z0_exPV_Probe.setupBranch(m_pTree, io);
	Lep_loose_Probe.setupBranch(m_pTree, io);
	Lep_medium_Probe.setupBranch(m_pTree, io);
	Lep_tight_Probe.setupBranch(m_pTree, io);
	Lep_veryLooseLL_Probe.setupBranch(m_pTree, io);
	Lep_looseLL_Probe.setupBranch(m_pTree, io);
	Lep_mediumLL_Probe.setupBranch(m_pTree, io);
	Lep_tightLL_Probe.setupBranch(m_pTree, io);
	Lep_veryTightLL_Probe.setupBranch(m_pTree, io);
	Lep_track_d0_o_sigd0_Probe.setupBranch(m_pTree, io);
	Lep_track_z0_o_sinTheta_Probe.setupBranch(m_pTree, io);

	Lep_author_Probe.setupBranch(m_pTree, io);
	Lep_recoAuthor_Probe.setupBranch(m_pTree, io);
	Lep_isSignalLike_Probe.setupBranch(m_pTree,io);
	Lep_isFromHeavyFlavor_Probe.setupBranch(m_pTree,io);
	Lep_isFromLightFlavor_Probe.setupBranch(m_pTree,io);
	Lep_isFromPhotonConversion_Probe.setupBranch(m_pTree,io);
	Lep_eta_Probe.setupBranch(m_pTree, io);
	Lep_phi_Probe.setupBranch(m_pTree, io);
	Lep_pt_Probe.setupBranch(m_pTree, io);
	Lep_mt_Probe.setupBranch(m_pTree, io);
	Lep_mt_STVF_Probe.setupBranch(m_pTree, io);
	Lep_d0_Probe.setupBranch(m_pTree, io);
	Lep_sigmad0_Probe.setupBranch(m_pTree, io);
	Lep_track_z0_Probe.setupBranch(m_pTree, io);
	Lep_track_d0_Probe.setupBranch(m_pTree, io);
	Lep_track_sigz0_Probe.setupBranch(m_pTree, io);
	Lep_track_sigd0_Probe.setupBranch(m_pTree, io);
	Lep_smeared_d0_Probe.setupBranch(m_pTree, io);
	Lep_charge_Probe.setupBranch(m_pTree, io);
	//Lep_inc_charge.setupBranch(m_pTree, io);
	Lep_isChargeFlipped_Probe.setupBranch(m_pTree, io);

	Lep_Loose.setupBranch(m_pTree, io);
	//Lep_inc.setupBranch(m_pTree, io);
	Lep_ptiso_Loose.setupBranch(m_pTree, io);
	Lep_etiso_Loose.setupBranch(m_pTree, io);
	Lep_z0_exPV_Loose.setupBranch(m_pTree, io);
	Lep_loose_Loose.setupBranch(m_pTree, io);
	Lep_medium_Loose.setupBranch(m_pTree, io);
	Lep_tight_Loose.setupBranch(m_pTree, io);
	Lep_veryLooseLL_Loose.setupBranch(m_pTree, io);
	Lep_looseLL_Loose.setupBranch(m_pTree, io);
	Lep_mediumLL_Loose.setupBranch(m_pTree, io);
	Lep_tightLL_Loose.setupBranch(m_pTree, io);
	Lep_veryTightLL_Loose.setupBranch(m_pTree, io);

	Lep_author_Loose.setupBranch(m_pTree, io);
	Lep_recoAuthor_Loose.setupBranch(m_pTree, io);
	Lep_isSignalLike_Loose.setupBranch(m_pTree,io);
	Lep_isFromHeavyFlavor_Loose.setupBranch(m_pTree,io);
	Lep_isFromLightFlavor_Loose.setupBranch(m_pTree,io);
	Lep_isFromPhotonConversion_Loose.setupBranch(m_pTree,io);
	Lep_eta_Loose.setupBranch(m_pTree, io);
	Lep_phi_Loose.setupBranch(m_pTree, io);
	Lep_pt_Loose.setupBranch(m_pTree, io);
	Lep_mt_Loose.setupBranch(m_pTree, io);
	Lep_mt_STVF_Loose.setupBranch(m_pTree, io);
	Lep_d0_Loose.setupBranch(m_pTree, io);
	Lep_sigmad0_Loose.setupBranch(m_pTree, io);
	Lep_track_z0_Loose.setupBranch(m_pTree, io);
	Lep_track_d0_Loose.setupBranch(m_pTree, io);
	Lep_track_sigz0_Loose.setupBranch(m_pTree, io);
	Lep_track_sigd0_Loose.setupBranch(m_pTree, io);
	Lep_smeared_d0_Loose.setupBranch(m_pTree, io);
	Lep_charge_Loose.setupBranch(m_pTree, io);
	//Lep_inc_charge.setupBranch(m_pTree, io);
	Lep_isChargeFlipped_Loose.setupBranch(m_pTree, io);

	/*
	Mu_inc_pt_loose.setupBranch(m_pTree,io);
	Mu_inc_pt_medium.setupBranch(m_pTree,io);
	Mu_inc_pt_tight.setupBranch(m_pTree,io);
	El_inc_pt_loose.setupBranch(m_pTree,io);
	El_inc_pt_medium.setupBranch(m_pTree,io);
	El_inc_pt_tight.setupBranch(m_pTree,io);
	El_inc_pt_veryLooseLL.setupBranch(m_pTree,io);
	El_inc_pt_looseLL.setupBranch(m_pTree,io);
	El_inc_pt_mediumLL.setupBranch(m_pTree,io);
	El_inc_pt_tightLL.setupBranch(m_pTree,io);
	El_inc_pt_veryTightLL.setupBranch(m_pTree,io);
	*/

	Lep_isMuon.setupBranch(m_pTree, io);
	Lep_isCombinedMuon.setupBranch(m_pTree, io);
	Lep_isMuon_Tag.setupBranch(m_pTree, io);
	Lep_isCombinedMuon_Tag.setupBranch(m_pTree, io);
	Lep_isMuon_Tag2.setupBranch(m_pTree, io);
	Lep_isCombinedMuon_Tag2.setupBranch(m_pTree, io);
	Lep_isMuon_Probe.setupBranch(m_pTree, io);
	Lep_isCombinedMuon_Probe.setupBranch(m_pTree, io);
	AllLep_isMuon.setupBranch(m_pTree, io);
	AllLep_isCombinedMuon.setupBranch(m_pTree, io);
	Lep_isSpectroMuon.setupBranch(m_pTree, io);
	AllLep_isSpectroMuon.setupBranch(m_pTree, io);
	Lep_isMuon_LooseNotTight.setupBranch(m_pTree, io);
	Lep_isCombinedMuon_LooseNotTight.setupBranch(m_pTree, io);
	Lep_isSpectroMuon_LooseNotTight.setupBranch(m_pTree, io);
	Lep_isMuon_Loose.setupBranch(m_pTree, io);
	Lep_isCombinedMuon_Loose.setupBranch(m_pTree, io);
	Lep_isSpectroMuon_Loose.setupBranch(m_pTree, io);
	//Lep_inc_isMuon.setupBranch(m_pTree, io);
	//Lep_inc_isCombined.setupBranch(m_pTree, io);
	Lep_isFake.setupBranch(m_pTree, io);
	AllLep_isFake.setupBranch(m_pTree, io);
	Lep_isFake_LooseNotTight.setupBranch(m_pTree, io);
	Lep_isFake_Loose.setupBranch(m_pTree, io);
	//Lep_inc_isFake.setupBranch(m_pTree, io);
	
//	for(int i = 0; i < 3; i++)
//	{
//		Lep[i].setupBranch(m_pTree, io);
////		Lep_centrality[i].setupBranch(m_pTree, io);
//		Lep_ptiso[i].setupBranch(m_pTree, io);
//		Lep_etiso[i].setupBranch(m_pTree, io);
//		Lep_z0_exPV[i].setupBranch(m_pTree, io);
//		Lep_loose[i].setupBranch(m_pTree, io);
//		Lep_medium[i].setupBranch(m_pTree, io);
//		Lep_tight[i].setupBranch(m_pTree, io);
//		Lep_veryLooseLL[i].setupBranch(m_pTree, io);
//		Lep_looseLL[i].setupBranch(m_pTree, io);
//		Lep_mediumLL[i].setupBranch(m_pTree, io);
//		Lep_tightLL[i].setupBranch(m_pTree, io);
//		Lep_veryTightLL[i].setupBranch(m_pTree, io);
//		Lep_isMuon[i].setupBranch(m_pTree, io);
//		Lep_isFake[i].setupBranch(m_pTree, io);
//		Lep_author[i].setupBranch(m_pTree, io);
//		Lep_recoAuthor[i].setupBranch(m_pTree, io);
////		Lep_x[i].setupBranch(m_pTree, io);
////		Lep_x_HPTO[i].setupBranch(m_pTree, io);
//		Lep_eta[i].setupBranch(m_pTree, io);
//		Lep_phi[i].setupBranch(m_pTree, io);
//		Lep_pt[i].setupBranch(m_pTree, io);
//		Lep_d0[i].setupBranch(m_pTree, io);
//		Lep_sigmad0[i].setupBranch(m_pTree, io);
//		Lep_track_z0[i].setupBranch(m_pTree, io);
//		Lep_track_d0[i].setupBranch(m_pTree, io);
//		Lep_track_sigz0[i].setupBranch(m_pTree, io);
//		Lep_track_sigd0[i].setupBranch(m_pTree, io);
//		Lep_smeared_d0[i].setupBranch(m_pTree, io);
//		Lep_charge[i].setupBranch(m_pTree, io);
//		Lep_isChargeFlipped[i].setupBranch(m_pTree, io);
//		/*
//		if(i<2){
//		Jet_p[i].setupBranch(m_pTree, io);
//		Jet_eta[i].setupBranch(m_pTree, io);
//		Jet_phi[i].setupBranch(m_pTree, io);
//		Jet_pt[i].setupBranch(m_pTree, io);
//		}
//		*/
//	}

	Jets.setupBranch(m_pTree, io);
	bJets.setupBranch(m_pTree, io);
	JetsJVF.setupBranch(m_pTree, io);
	
	MET_final_Et.setupBranch(m_pTree, io);
	MET_final_phi.setupBranch(m_pTree, io);
	MET_final_sumEt.setupBranch(m_pTree, io);

	MET_final_Et_raw.setupBranch(m_pTree, io);
	MET_final_phi_raw.setupBranch(m_pTree, io);
	MET_final_sumEt_raw.setupBranch(m_pTree, io);

	MET_final_Et_STVF.setupBranch(m_pTree, io);
	MET_final_phi_STVF.setupBranch(m_pTree, io);
	MET_final_sumEt_STVF.setupBranch(m_pTree, io);
	nPV_3trks.setupBranch(m_pTree, io);
	nPV_2trks.setupBranch(m_pTree, io);
	mu.setupBranch(m_pTree, io);
	//btagsEff60.setupBranch(m_pTree, io);
	//btagsEff70.setupBranch(m_pTree, io);
	//btagsEff80.setupBranch(m_pTree, io);
	btagsEff85.setupBranch(m_pTree, io);
	RunNumber.setupBranch(m_pTree, io);
	EventNumber.setupBranch(m_pTree, io);
	lbn.setupBranch(m_pTree, io);
	PrimaryVertexNTracks.setupBranch(m_pTree,io);
	isEGammaStream.setupBranch(m_pTree, io);
	eventHasSpectroMuons.setupBranch(m_pTree, io);

	hasLooseNotTightMuons.setupBranch(m_pTree,io);
	hasLooseNotTightElectrons.setupBranch(m_pTree,io);

	FakeLeptons.setupBranch(m_pTree, io);
  	TriLepton.setupBranch(m_pTree, io);
	OSLeptons.setupBranch(m_pTree, io);

	nSFOS.setupBranch(m_pTree, io);
	nSFOSAll.setupBranch(m_pTree, io);

	massesSFOS.setupBranch(m_pTree,io);
	massesSFOSAll.setupBranch(m_pTree,io);
	massesElEl.setupBranch(m_pTree,io);
	massesElMu.setupBranch(m_pTree,io);
	massesMuMu.setupBranch(m_pTree,io);

	MonteCarloWeight.setupBranch(m_pTree, io);
	PileupWeight.setupBranch(m_pTree, io);
	RecoWeight.setupBranch(m_pTree, io);
	//BTagWeightEff60.setupBranch(m_pTree, io);
	//BTagWeightEff70.setupBranch(m_pTree, io);
	//BTagWeightEff80.setupBranch(m_pTree, io);
	BTagWeightEff85.setupBranch(m_pTree, io);
	TriggerWeight.setupBranch(m_pTree, io);
	ChargeMisIDWeight.setupBranch(m_pTree, io);
	DoChargeFlip.setupBranch(m_pTree, io);
	XSecWeight.setupBranch(m_pTree, io);
	MxMWeight.setupBranch(m_pTree, io);
	FormFactorWeight.setupBranch(m_pTree, io);
	LumiWeight.setupBranch(m_pTree, io);
 	CorrectionWeight.setupBranch(m_pTree, io);
	AllWeight.setupBranch(m_pTree, io);
	MET_CellOut_Eflow_STVF_Et.setupBranch(m_pTree,io);
	MET_CellOut_Eflow_STVF_Phi.setupBranch(m_pTree,io);
	MET_CellOut_Eflow_STVF_SumEt.setupBranch(m_pTree,io);
	MET_CellOut_Eflow_Et.setupBranch(m_pTree,io);
	MET_CellOut_Eflow_Phi.setupBranch(m_pTree,io);
	MET_CellOut_Eflow_SumEt.setupBranch(m_pTree,io);
	
	Truth_initial.setupBranch(m_pTree, io);
	Truth_final.setupBranch(m_pTree, io);

	Lep_4lpair.setupBranch(m_pTree, io);
	DiLepton.setupBranch(m_pTree, io);
	QuadriLepton.setupBranch(m_pTree, io);
	mll.setupBranch(m_pTree, io);
	mT1.setupBranch(m_pTree, io);
	mT2.setupBranch(m_pTree, io);
	m12.setupBranch(m_pTree, io);
	m34.setupBranch(m_pTree, io);
	m4l.setupBranch(m_pTree, io);
	SumHPTO.setupBranch(m_pTree, io);
	SumCosDphi.setupBranch(m_pTree, io);

	/*
	EF_mu36_tight.setupBranch(m_pTree,io);
	EF_mu24i_tight.setupBranch(m_pTree,io);
	EF_e24vhi_medium1.setupBranch(m_pTree,io);
	EF_e60_medium1.setupBranch(m_pTree,io);
	*/

}

//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::EventData::~EventData()
{

}

TTree* wwwAnalysis::EventData::tree()
{
	return m_pTree;
}

