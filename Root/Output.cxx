#include "wwwAnalysis/Output.h"
#include "TTree.h"
#include <iostream>
#include <cmath>
#include "TMatrix.h"
#include "TVector2.h"
#include "TVector.h"
#include "TDirectory.h"

//=============================================================================
// Constructor
//=============================================================================
wwwAnalysis::Output::Output()
{
	ip_smear=0;
	rand=0;
}

//=============================================================================
// Destructor
//=============================================================================
wwwAnalysis::Output::~Output()
{
/*
if(ip_smear){ip_smear->Close();delete ip_smear; ip_smear=0;}
if(rand){delete rand;rand=0;}
*/
}

void wwwAnalysis::Output::initialize(const char *out_name)
{
	Jets = new std::vector<TLorentzVector>();
	bJets = new std::vector<bool>();
	JetsJVF = new std::vector<bool>();
	Lep = new std::vector<TLorentzVector>();
	/*
	Lep_inc = new std::vector<TLorentzVector>();
	Mu_inc_pt_loose = new std::vector<double>();
	Mu_inc_pt_medium = new std::vector<double>();
	Mu_inc_pt_tight = new std::vector<double>();
	El_inc_pt_loose = new std::vector<double>();
	El_inc_pt_medium = new std::vector<double>();
	El_inc_pt_tight = new std::vector<double>();
	El_inc_pt_veryLooseLL = new std::vector<double>();
	El_inc_pt_looseLL = new std::vector<double>();
	El_inc_pt_mediumLL = new std::vector<double>();
	El_inc_pt_tightLL = new std::vector<double>();
	El_inc_pt_veryTightLL = new std::vector<double>();
	*/


	Lep_ptiso = new std::vector<double>();
	Lep_etiso = new std::vector<double>();
	Lep_z0_exPV = new std::vector<double>();
		
	Lep_d0 = new std::vector<double>();
	Lep_sigmad0 = new std::vector<double>();
	Lep_track_z0 = new std::vector<double>();
	Lep_track_d0 = new std::vector<double>();
	Lep_track_sigz0 = new std::vector<double>();
	Lep_track_sigd0 = new std::vector<double>();
	Lep_track_theta = new std::vector<double>();
	Lep_track_d0_o_sigd0 = new std::vector<double>();
	Lep_track_z0_o_sinTheta = new std::vector<double>();


	Lep_isSignalLike = new std::vector<bool>();
	Lep_isFromHeavyFlavor = new std::vector<bool>();
	Lep_isFromLightFlavor = new std::vector<bool>();
	Lep_isFromPhotonConversion = new std::vector<bool>();

	Lep_eta = new std::vector<double>();
	Lep_phi = new std::vector<double>();
	Lep_pt = new std::vector<double>();
	Lep_mt = new std::vector<double>();
	Lep_mt_STVF = new std::vector<double>();
	Lep_charge = new std::vector<int>();		
	//Lep_inc_charge = new std::vector<int>();		
	Lep_isChargeFlipped = new std::vector<bool>();		
	//Lep_inc_isChargeFlipped = new std::vector<bool>();		
	Lep_isSFOS = new std::vector<bool>();		
	
	Lep_loose = new std::vector<bool>();	
	Lep_medium = new std::vector<bool>();	
	Lep_tight = new std::vector<bool>();	
	Lep_veryLooseLL = new std::vector<bool>();	
	Lep_looseLL = new std::vector<bool>();	
	Lep_mediumLL = new std::vector<bool>();	
	Lep_tightLL = new std::vector<bool>();	
	Lep_veryTightLL = new std::vector<bool>();	
	Lep_author = new std::vector<unsigned int>();
	Lep_recoAuthor = new std::vector<unsigned int>();
	Lep_isMuon = new std::vector<bool>();	
	Lep_isCombinedMuon = new std::vector<bool>();	
	AllLep_isMuon = new std::vector<bool>();	
	AllLep_isCombinedMuon = new std::vector<bool>();	
	Lep_isSpectroMuon = new std::vector<bool>();	
	AllLep_isSpectroMuon = new std::vector<bool>();	
	//Lep_inc_isMuon = new std::vector<bool>();	
	//Lep_inc_isCombined = new std::vector<bool>();	
	Lep_isFake = new std::vector<bool>();	
	AllLep_isFake = new std::vector<bool>();	
	//Lep_inc_isFake = new std::vector<bool>();	
	//
	//
	AllLep = new std::vector<TLorentzVector>();
	/*
	Lep_inc = new std::vector<TLorentzVector>();
	Mu_inc_pt_loose = new std::vector<double>();
	Mu_inc_pt_medium = new std::vector<double>();
	Mu_inc_pt_tight = new std::vector<double>();
	El_inc_pt_loose = new std::vector<double>();
	El_inc_pt_medium = new std::vector<double>();
	El_inc_pt_tight = new std::vector<double>();
	El_inc_pt_veryLooseLL = new std::vector<double>();
	El_inc_pt_looseLL = new std::vector<double>();
	El_inc_pt_mediumLL = new std::vector<double>();
	El_inc_pt_tightLL = new std::vector<double>();
	El_inc_pt_veryTightLL = new std::vector<double>();
	*/


	AllLep_ptiso = new std::vector<double>();
	AllLep_etiso = new std::vector<double>();
	AllLep_z0_exPV = new std::vector<double>();
		
	AllLep_d0 = new std::vector<double>();
	AllLep_sigmad0 = new std::vector<double>();
	AllLep_track_z0 = new std::vector<double>();
	AllLep_track_d0 = new std::vector<double>();
	AllLep_track_sigz0 = new std::vector<double>();
	AllLep_track_sigd0 = new std::vector<double>();
	AllLep_smeared_d0 = new std::vector<double>();


	AllLep_eta = new std::vector<double>();
	AllLep_phi = new std::vector<double>();
	AllLep_pt = new std::vector<double>();
	AllLep_charge = new std::vector<int>();		
	//Lep_inc_charge = new std::vector<int>();		
	AllLep_isChargeFlipped = new std::vector<bool>();		
	//Lep_inc_isChargeFlipped = new std::vector<bool>();		
	
	AllLep_loose = new std::vector<bool>();	
	AllLep_medium = new std::vector<bool>();	
	AllLep_tight = new std::vector<bool>();	
	AllLep_veryLooseLL = new std::vector<bool>();	
	AllLep_looseLL = new std::vector<bool>();	
	AllLep_mediumLL = new std::vector<bool>();	
	AllLep_tightLL = new std::vector<bool>();	
	AllLep_veryTightLL = new std::vector<bool>();	
	AllLep_author = new std::vector<unsigned int>();
	AllLep_recoAuthor = new std::vector<unsigned int>();

	
	Lep_LooseNotTight = new std::vector<TLorentzVector>();
	Lep_ptiso_LooseNotTight  = new std::vector<double>();
	Lep_etiso_LooseNotTight  = new std::vector<double>();
	Lep_z0_exPV_LooseNotTight  = new std::vector<double>();
		
	Lep_d0_LooseNotTight  = new std::vector<double>();
	Lep_sigmad0_LooseNotTight  = new std::vector<double>();
	Lep_track_z0_LooseNotTight  = new std::vector<double>();
	Lep_track_d0_LooseNotTight  = new std::vector<double>();
	Lep_track_sigz0_LooseNotTight  = new std::vector<double>();
	Lep_track_sigd0_LooseNotTight  = new std::vector<double>();
	Lep_smeared_d0_LooseNotTight  = new std::vector<double>();


	Lep_isSignalLike_LooseNotTight   = new std::vector<bool>();
	Lep_isFromHeavyFlavor_LooseNotTight   = new std::vector<bool>();
	Lep_isFromLightFlavor_LooseNotTight   = new std::vector<bool>();
	Lep_isFromPhotonConversion_LooseNotTight   = new std::vector<bool>();

	Lep_eta_LooseNotTight  = new std::vector<double>();
	Lep_phi_LooseNotTight  = new std::vector<double>();
	Lep_pt_LooseNotTight  = new std::vector<double>();
	Lep_mt_LooseNotTight  = new std::vector<double>();
	Lep_mt_STVF_LooseNotTight  = new std::vector<double>();
	Lep_charge_LooseNotTight  = new std::vector<int>();		
	//Lep_inc_charge = new std::vector<int>();		
	Lep_isChargeFlipped_LooseNotTight  = new std::vector<bool>();		
	//Lep_inc_isChargeFlipped = new std::vector<bool>();		
	
	Lep_loose_LooseNotTight  = new std::vector<bool>();	
	Lep_medium_LooseNotTight  = new std::vector<bool>();	
	Lep_tight_LooseNotTight  = new std::vector<bool>();	
	Lep_veryLooseLL_LooseNotTight  = new std::vector<bool>();	
	Lep_looseLL_LooseNotTight  = new std::vector<bool>();	
	Lep_mediumLL_LooseNotTight  = new std::vector<bool>();	
	Lep_tightLL_LooseNotTight  = new std::vector<bool>();	
	Lep_veryTightLL_LooseNotTight  = new std::vector<bool>();	
	Lep_author_LooseNotTight  = new std::vector<unsigned int>();
	Lep_recoAuthor_LooseNotTight  = new std::vector<unsigned int>();
	Lep_isMuon_LooseNotTight  = new std::vector<bool>();	
	Lep_isCombinedMuon_LooseNotTight  = new std::vector<bool>();	
	Lep_isSpectroMuon_LooseNotTight  = new std::vector<bool>();	
	//Lep_inc_isMuon = new std::vector<bool>();	
	//Lep_inc_isCombined = new std::vector<bool>();	
	Lep_isFake_LooseNotTight  = new std::vector<bool>();	
	//Lep_inc_isFake = new std::vector<bool>();	
	//
	//
	///
	Lep_track_d0_o_sigd0_Tag = new std::vector<double>();
	Lep_track_z0_o_sinTheta_Tag = new std::vector<double>();
	Lep_Tag = new std::vector<TLorentzVector>();
	Lep_ptiso_Tag  = new std::vector<double>();
	Lep_etiso_Tag  = new std::vector<double>();
	Lep_z0_exPV_Tag  = new std::vector<double>();
		
	Lep_d0_Tag  = new std::vector<double>();
	Lep_sigmad0_Tag  = new std::vector<double>();
	Lep_track_z0_Tag  = new std::vector<double>();
	Lep_track_d0_Tag  = new std::vector<double>();
	Lep_track_sigz0_Tag  = new std::vector<double>();
	Lep_track_sigd0_Tag  = new std::vector<double>();
	Lep_smeared_d0_Tag  = new std::vector<double>();


	Lep_isSignalLike_Tag = new std::vector<bool>();
	Lep_isFromHeavyFlavor_Tag = new std::vector<bool>();
	Lep_isFromLightFlavor_Tag = new std::vector<bool>();
	Lep_isFromPhotonConversion_Tag = new std::vector<bool>();

	Lep_eta_Tag  = new std::vector<double>();
	Lep_phi_Tag  = new std::vector<double>();
	Lep_pt_Tag  = new std::vector<double>();
	Lep_mt_Tag  = new std::vector<double>();
	Lep_mt_STVF_Tag  = new std::vector<double>();
	Lep_charge_Tag  = new std::vector<int>();		
	//Lep_inc_charge = new std::vector<int>();		
	Lep_isChargeFlipped_Tag  = new std::vector<bool>();		
	//Lep_inc_isChargeFlipped = new std::vector<bool>();		
	
	Lep_loose_Tag  = new std::vector<bool>();	
	Lep_medium_Tag  = new std::vector<bool>();	
	Lep_tight_Tag  = new std::vector<bool>();	
	Lep_veryLooseLL_Tag  = new std::vector<bool>();	
	Lep_looseLL_Tag  = new std::vector<bool>();	
	Lep_mediumLL_Tag  = new std::vector<bool>();	
	Lep_tightLL_Tag  = new std::vector<bool>();	
	Lep_veryTightLL_Tag  = new std::vector<bool>();	
	Lep_author_Tag  = new std::vector<unsigned int>();
	Lep_recoAuthor_Tag  = new std::vector<unsigned int>();
	Lep_isMuon_Tag  = new std::vector<bool>();	
	Lep_isCombinedMuon_Tag  = new std::vector<bool>();	
	Lep_isSpectroMuon_Tag  = new std::vector<bool>();	
	//Lep_inc_isMuon = new std::vector<bool>();	
	//Lep_inc_isCombined = new std::vector<bool>();	
	Lep_isFake_Tag  = new std::vector<bool>();	
	//Lep_inc_isFake = new std::vector<bool>();	
	//

	Lep_track_d0_o_sigd0_Tag2 = new std::vector<double>();
	Lep_track_z0_o_sinTheta_Tag2 = new std::vector<double>();
	Lep_Tag2 = new std::vector<TLorentzVector>();
	Lep_ptiso_Tag2  = new std::vector<double>();
	Lep_etiso_Tag2  = new std::vector<double>();
	Lep_z0_exPV_Tag2  = new std::vector<double>();
		
	Lep_d0_Tag2  = new std::vector<double>();
	Lep_sigmad0_Tag2  = new std::vector<double>();
	Lep_track_z0_Tag2  = new std::vector<double>();
	Lep_track_d0_Tag2  = new std::vector<double>();
	Lep_track_sigz0_Tag2  = new std::vector<double>();
	Lep_track_sigd0_Tag2  = new std::vector<double>();
	Lep_smeared_d0_Tag2  = new std::vector<double>();

	Lep_isSignalLike_Tag2 = new std::vector<bool>();
	Lep_isFromHeavyFlavor_Tag2 = new std::vector<bool>();
	Lep_isFromLightFlavor_Tag2 = new std::vector<bool>();
	Lep_isFromPhotonConversion_Tag2 = new std::vector<bool>();

	Lep_eta_Tag2  = new std::vector<double>();
	Lep_phi_Tag2  = new std::vector<double>();
	Lep_pt_Tag2  = new std::vector<double>();
	Lep_mt_Tag2  = new std::vector<double>();
	Lep_mt_STVF_Tag2  = new std::vector<double>();
	Lep_charge_Tag2  = new std::vector<int>();		
	//Lep_inc_charge = new std::vector<int>();		
	Lep_isChargeFlipped_Tag2  = new std::vector<bool>();		
	//Lep_inc_isChargeFlipped = new std::vector<bool>();		
	
	Lep_loose_Tag2  = new std::vector<bool>();	
	Lep_medium_Tag2  = new std::vector<bool>();	
	Lep_tight_Tag2  = new std::vector<bool>();	
	Lep_veryLooseLL_Tag2  = new std::vector<bool>();	
	Lep_looseLL_Tag2  = new std::vector<bool>();	
	Lep_mediumLL_Tag2  = new std::vector<bool>();	
	Lep_tightLL_Tag2  = new std::vector<bool>();	
	Lep_veryTightLL_Tag2  = new std::vector<bool>();	
	Lep_author_Tag2  = new std::vector<unsigned int>();
	Lep_recoAuthor_Tag2  = new std::vector<unsigned int>();
	Lep_isMuon_Tag2  = new std::vector<bool>();	
	Lep_isCombinedMuon_Tag2  = new std::vector<bool>();	
	Lep_isSpectroMuon_Tag2  = new std::vector<bool>();	
	//Lep_inc_isMuon = new std::vector<bool>();	
	//Lep_inc_isCombined = new std::vector<bool>();	
	Lep_isFake_Tag2  = new std::vector<bool>();	
	//Lep_inc_isFake = new std::vector<bool>();	
	//

	Lep_Probe = new std::vector<TLorentzVector>();
	Lep_ptiso_Probe  = new std::vector<double>();
	Lep_etiso_Probe  = new std::vector<double>();
	Lep_z0_exPV_Probe  = new std::vector<double>();
	Lep_track_d0_o_sigd0_Probe = new std::vector<double>();
	Lep_track_z0_o_sinTheta_Probe = new std::vector<double>();
		
	Lep_d0_Probe  = new std::vector<double>();
	Lep_sigmad0_Probe  = new std::vector<double>();
	Lep_track_z0_Probe  = new std::vector<double>();
	Lep_track_d0_Probe  = new std::vector<double>();
	Lep_track_sigz0_Probe  = new std::vector<double>();
	Lep_track_sigd0_Probe  = new std::vector<double>();
	Lep_smeared_d0_Probe  = new std::vector<double>();

	Lep_isSignalLike_Probe = new std::vector<bool>();
	Lep_isFromHeavyFlavor_Probe = new std::vector<bool>();
	Lep_isFromLightFlavor_Probe = new std::vector<bool>();
	Lep_isFromPhotonConversion_Probe = new std::vector<bool>();

	Lep_eta_Probe  = new std::vector<double>();
	Lep_phi_Probe  = new std::vector<double>();
	Lep_pt_Probe  = new std::vector<double>();
	Lep_mt_Probe  = new std::vector<double>();
	Lep_mt_STVF_Probe  = new std::vector<double>();
	Lep_charge_Probe  = new std::vector<int>();		
	//Lep_inc_charge = new std::vector<int>();		
	Lep_isChargeFlipped_Probe  = new std::vector<bool>();		
	//Lep_inc_isChargeFlipped = new std::vector<bool>();		
	
	Lep_loose_Probe  = new std::vector<bool>();	
	Lep_medium_Probe  = new std::vector<bool>();	
	Lep_tight_Probe  = new std::vector<bool>();	
	Lep_veryLooseLL_Probe  = new std::vector<bool>();	
	Lep_looseLL_Probe  = new std::vector<bool>();	
	Lep_mediumLL_Probe  = new std::vector<bool>();	
	Lep_tightLL_Probe  = new std::vector<bool>();	
	Lep_veryTightLL_Probe  = new std::vector<bool>();	
	Lep_author_Probe  = new std::vector<unsigned int>();
	Lep_recoAuthor_Probe  = new std::vector<unsigned int>();
	Lep_isMuon_Probe  = new std::vector<bool>();	
	Lep_isCombinedMuon_Probe  = new std::vector<bool>();	
	Lep_isSpectroMuon_Probe  = new std::vector<bool>();	
	//Lep_inc_isMuon = new std::vector<bool>();	
	//Lep_inc_isCombined = new std::vector<bool>();	
	Lep_isFake_Probe  = new std::vector<bool>();	
	//Lep_inc_isFake = new std::vector<bool>();	
	
	Lep_Loose = new std::vector<TLorentzVector>();
	Lep_ptiso_Loose  = new std::vector<double>();
	Lep_etiso_Loose  = new std::vector<double>();
	Lep_z0_exPV_Loose  = new std::vector<double>();
		
	Lep_d0_Loose  = new std::vector<double>();
	Lep_sigmad0_Loose  = new std::vector<double>();
	Lep_track_z0_Loose  = new std::vector<double>();
	Lep_track_d0_Loose  = new std::vector<double>();
	Lep_track_sigz0_Loose  = new std::vector<double>();
	Lep_track_sigd0_Loose  = new std::vector<double>();
	Lep_smeared_d0_Loose  = new std::vector<double>();

	Lep_isSignalLike_Loose = new std::vector<bool>();
	Lep_isFromHeavyFlavor_Loose = new std::vector<bool>();
	Lep_isFromLightFlavor_Loose = new std::vector<bool>();
	Lep_isFromPhotonConversion_Loose = new std::vector<bool>();

	Lep_eta_Loose  = new std::vector<double>();
	Lep_phi_Loose  = new std::vector<double>();
	Lep_pt_Loose  = new std::vector<double>();
	Lep_mt_Loose  = new std::vector<double>();
	Lep_mt_STVF_Loose  = new std::vector<double>();
	Lep_charge_Loose  = new std::vector<int>();		
	//Lep_inc_charge = new std::vector<int>();		
	Lep_isChargeFlipped_Loose  = new std::vector<bool>();		
	//Lep_inc_isChargeFlipped = new std::vector<bool>();		
	
	Lep_loose_Loose  = new std::vector<bool>();	
	Lep_medium_Loose  = new std::vector<bool>();	
	Lep_tight_Loose  = new std::vector<bool>();	
	Lep_veryLooseLL_Loose  = new std::vector<bool>();	
	Lep_looseLL_Loose  = new std::vector<bool>();	
	Lep_mediumLL_Loose  = new std::vector<bool>();	
	Lep_tightLL_Loose  = new std::vector<bool>();	
	Lep_veryTightLL_Loose  = new std::vector<bool>();	
	Lep_author_Loose  = new std::vector<unsigned int>();
	Lep_recoAuthor_Loose  = new std::vector<unsigned int>();
	Lep_isMuon_Loose  = new std::vector<bool>();	
	Lep_isCombinedMuon_Loose  = new std::vector<bool>();	
	Lep_isSpectroMuon_Loose  = new std::vector<bool>();	
	//Lep_inc_isMuon = new std::vector<bool>();	
	//Lep_inc_isCombined = new std::vector<bool>();	
	Lep_isFake_Loose  = new std::vector<bool>();	
	//Lep_inc_isFake = new std::vector<bool>();	

	Lep_4lpair = new std::vector<int>();

	massesSFOS = new std::vector<double>();
	massesSFOSAll = new std::vector<double>();

	massesElMu = new std::vector<double>();
	massesElEl = new std::vector<double>();
	massesMuMu = new std::vector<double>();




//	Lep[1] = new std::vector<TLorentzVector>();
//	Lep[2] = new std::vector<TLorentzVector>();
	//Jet_p[0] = new TLorentzVector();
	//Jet_p[1] = new TLorentzVector();
//	PassMVAVBF = const_cast<Root::TAccept *>(mvavbf);
//	PassMVABoosted = const_cast<Root::TAccept *>(mvaboosted);
//	PassMVAVH = const_cast<Root::TAccept *>(mvavh);
//	PassMVA1Jet = const_cast<Root::TAccept *>(mvajet1);
//	PassMVA0Jet = const_cast<Root::TAccept *>(mvajet0);
//	PassVBF = const_cast<Root::TAccept *>(vbf);
//	PassBoosted = const_cast<Root::TAccept *>(boosted);
//	PassVH = const_cast<Root::TAccept *>(vh);
//	Pass1Jet = const_cast<Root::TAccept *>(jet1);
//	Pass0Jet = const_cast<Root::TAccept *>(jet0);
	EventData::initialize(out_name,0,TREE_WRITE);
	/*
	if(!ip_smear)
	{
		std::string path = std::string(getenv("ROOTCOREDIR")) + "/../wwwAnalysis/Run/impact_parameter_smearing.root";
		TDirectory* home=gDirectory;
		ip_smear=TFile::Open(path.c_str());
		home->cd();
		
		smearD0[0] = (TH2F*)ip_smear->Get("smearD0_0");
		smearD0[1] = (TH2F*)ip_smear->Get("smearD0_1");
		smearD0[2] = (TH2F*)ip_smear->Get("smearD0_2");
	}
	if(!rand)rand =new TRandom3(342);
	*/

}
void wwwAnalysis::Output::FillLepton(int i, const PhysicsObject *lep,bool isSFOS)
{

	Lep->push_back(lep->momentum());

	Lep_isFake->push_back(lep->fake());

	Lep_pt->push_back(lep->momentum().Pt());
	Lep_eta->push_back(lep->momentum().Eta());
	Lep_phi->push_back(lep->momentum().Phi());
	Lep_charge->push_back(lep->charge());
	Lep_isChargeFlipped->push_back(lep->isChargeFlipped());
   Lep_isSFOS->push_back(isSFOS);

	
	if(lep->type() == MUON)
	{
		Muon *mu = (Muon *)lep;
		Lep_isMuon->push_back( true);
		Lep_isCombinedMuon->push_back( mu->d3pd().isCombinedMuon());
		//Lep_ptiso->at(i)  = mu->d3pd().ptcone40()/Lep->at(i)->Pt();
		//
		Lep_isSpectroMuon->push_back(mu->isSpectroMuon());

		Lep_ptiso->push_back(mu->d3pd().ptcone20()/lep->momentum().Pt());
		Lep_etiso->push_back(mu->Etcone20_corr()/lep->momentum().Pt());

		Lep_z0_exPV->push_back(mu->d3pd().id_z0_exPV());

		Lep_d0->push_back(mu->d3pd().trackd0pv());
		Lep_sigmad0->push_back(mu->d3pd().tracksigd0pv());
		Lep_loose->push_back(mu->d3pd().loose());
		Lep_medium->push_back(mu->d3pd().medium());
		Lep_tight->push_back(mu->d3pd().tight());
		//only relevant for electrons
		Lep_veryLooseLL->push_back(false);
		Lep_looseLL->push_back(false);
		Lep_mediumLL->push_back(false);
		Lep_tightLL->push_back(false);
		Lep_veryTightLL->push_back(false);
		Lep_author->push_back(mu->d3pd().author());
		//1 is Third Chain Muons, 2 is Staco
		Lep_recoAuthor->push_back((mu->useThirdChain() ? 1 : 2));
		Lep_track_z0->push_back(mu->d3pd().trackz0pvunbiased());
		Lep_track_d0->push_back(mu->d3pd().trackd0pvunbiased());
		Lep_track_sigz0->push_back(mu->d3pd().tracksigz0pvunbiased());
		Lep_track_sigd0->push_back(mu->d3pd().tracksigd0pvunbiased());
		Lep_track_theta->push_back(mu->d3pd().tracktheta());
		Lep_track_d0_o_sigd0->push_back(fabs(mu->d3pd().trackd0pvunbiased()/mu->d3pd().tracksigd0pvunbiased()));
		Lep_track_z0_o_sinTheta->push_back(fabs(mu->d3pd().trackz0pvunbiased()*sin(mu->d3pd().tracktheta())) );
//		Lep_smeared_d0->push_back(1.); //mu->d3pd().trackd0pvunbiased()-0.002+GetD0SmearSigma(mu->d3pd().nBLHits(),sin(mu->d3pd().id_theta())*fabs(1.0/mu->d3pd().id_qoverp()),-log(tan(mu->d3pd().id_theta()/2)));
//
		//Lep_charge->at(i) = mu->d3pd().charge();

		Lep_isSignalLike->push_back(mu->isSignalLike());
		Lep_isFromHeavyFlavor->push_back(mu->isFromHeavyFlavor());
		Lep_isFromLightFlavor->push_back(mu->isFromLightFlavor());
		Lep_isFromPhotonConversion->push_back(mu->isFromPhotonConversion());
	}
	else
	{
		Electron *el = (Electron *)lep;
		Lep_isMuon->push_back(false);
		Lep_isCombinedMuon->push_back(false);
		Lep_isSpectroMuon->push_back(false);

		Lep_ptiso->push_back(el->d3pd().ptcone20()/lep->momentum().Pt());
		Lep_etiso->push_back(el->Etcone20_corr()/lep->momentum().Pt());

		Lep_z0_exPV->push_back(el->d3pd().trackz0pv());

		Lep_d0->push_back(el->d3pd().trackd0pv());
		Lep_sigmad0->push_back(el->d3pd().tracksigd0pv());
		Lep_loose->push_back(el->loose());
		Lep_medium->push_back(el->medium());
		Lep_tight->push_back(el->tight());
		Lep_veryLooseLL->push_back(el->veryLooseLL());
		Lep_looseLL->push_back(el->looseLL());
		Lep_mediumLL->push_back(el->mediumLL());
		Lep_tightLL->push_back(el->tightLL());
		Lep_veryTightLL->push_back(el->veryTightLL());
		Lep_author->push_back(el->d3pd().author());
		//0 for electron reco.  This is mainly relevant for muons.
		Lep_recoAuthor->push_back(0.);
		Lep_track_z0->push_back(el->d3pd().trackz0pv());
		Lep_track_d0->push_back(el->d3pd().trackd0pv());
		Lep_track_sigz0->push_back(el->d3pd().tracksigz0pv());
		Lep_track_sigd0->push_back(el->d3pd().tracksigd0pv());
		Lep_track_theta->push_back(el->d3pd().tracktheta());
		Lep_track_d0_o_sigd0->push_back(fabs(el->d3pd().trackd0pvunbiased()/el->d3pd().tracksigd0pvunbiased()));
		Lep_track_z0_o_sinTheta->push_back(fabs(el->d3pd().trackz0pvunbiased()*sin(el->d3pd().tracktheta())) );
		Lep_isSignalLike->push_back(el->isSignalLike());
		Lep_isFromHeavyFlavor->push_back(el->isFromHeavyFlavor());
		Lep_isFromLightFlavor->push_back(el->isFromLightFlavor());
		Lep_isFromPhotonConversion->push_back(el->isFromPhotonConversion());


	
//		Lep_smeared_d0->push_back(1);//el->d3pd().trackd0pv()-0.001+GetD0SmearSigma(el->d3pd().nBLHits(), el->d3pd().trackpt(), el->d3pd().tracketa());
		//Lep_charge->at(i) = el->d3pd().charge();
	}
}

void wwwAnalysis::Output::FillAllLepton(int i, const PhysicsObject *lep)
{

	AllLep->push_back(lep->momentum());

	AllLep_isFake->push_back(lep->fake());

	AllLep_pt->push_back(lep->momentum().Pt());
	AllLep_eta->push_back(lep->momentum().Eta());
	AllLep_phi->push_back(lep->momentum().Phi());
	AllLep_charge->push_back(lep->charge());
	AllLep_isChargeFlipped->push_back(lep->isChargeFlipped());

	
	if(lep->type() == MUON)
	{
		Muon *mu = (Muon *)lep;
		AllLep_isMuon->push_back( true);
		AllLep_isCombinedMuon->push_back( mu->d3pd().isCombinedMuon());
		//Lep_ptiso->at(i)  = mu->d3pd().ptcone40()/Lep->at(i)->Pt();
		//
		AllLep_isSpectroMuon->push_back(mu->isSpectroMuon());

		AllLep_ptiso->push_back(mu->d3pd().ptcone20()/AllLep->at(i).Pt());
		AllLep_etiso->push_back(mu->Etcone20_corr()/AllLep->at(i).Pt());

		AllLep_z0_exPV->push_back(mu->d3pd().id_z0_exPV());

		AllLep_d0->push_back(mu->d3pd().trackd0pv());
		AllLep_sigmad0->push_back(mu->d3pd().tracksigd0pv());
		AllLep_loose->push_back(mu->d3pd().loose());
		AllLep_medium->push_back(mu->d3pd().medium());
		AllLep_tight->push_back(mu->d3pd().tight());
		//only relevant for electrons
		AllLep_veryLooseLL->push_back(false);
		AllLep_looseLL->push_back(false);
		AllLep_mediumLL->push_back(false);
		AllLep_tightLL->push_back(false);
		AllLep_veryTightLL->push_back(false);
		AllLep_author->push_back(mu->d3pd().author());
		//1 is Third Chain Muons, 2 is Staco
		AllLep_recoAuthor->push_back((mu->useThirdChain() ? 1 : 2));
		AllLep_track_z0->push_back(mu->d3pd().trackz0pvunbiased());
		AllLep_track_d0->push_back(mu->d3pd().trackd0pvunbiased());
		AllLep_track_sigz0->push_back(mu->d3pd().tracksigz0pvunbiased());
		AllLep_track_sigd0->push_back(mu->d3pd().tracksigd0pvunbiased());
		AllLep_smeared_d0->push_back(1.); //mu->d3pd().trackd0pvunbiased()-0.002+GetD0SmearSigma(mu->d3pd().nBLHits(),sin(mu->d3pd().id_theta())*fabs(1.0/mu->d3pd().id_qoverp()),-log(tan(mu->d3pd().id_theta()/2)));
		//Lep_charge->at(i) = mu->d3pd().charge();
	}
	else
	{
		Electron *el = (Electron *)lep;
		AllLep_isMuon->push_back(false);
		AllLep_isCombinedMuon->push_back(false);
		AllLep_isSpectroMuon->push_back(false);

		AllLep_ptiso->push_back(el->d3pd().ptcone20()/AllLep->at(i).Pt());
		AllLep_etiso->push_back(el->Etcone20_corr()/AllLep->at(i).Pt());

		AllLep_z0_exPV->push_back(el->d3pd().trackz0pv());

		AllLep_d0->push_back(el->d3pd().trackd0pv());
		AllLep_sigmad0->push_back(el->d3pd().tracksigd0pv());
		AllLep_loose->push_back(el->loose());
		AllLep_medium->push_back(el->medium());
		AllLep_tight->push_back(el->tight());
		AllLep_veryLooseLL->push_back(el->veryLooseLL());
		AllLep_looseLL->push_back(el->looseLL());
		AllLep_mediumLL->push_back(el->mediumLL());
		AllLep_tightLL->push_back(el->tightLL());
		AllLep_veryTightLL->push_back(el->veryTightLL());
		AllLep_author->push_back(el->d3pd().author());
		//0 for electron reco.  This is mainly relevant for muons.
		AllLep_recoAuthor->push_back(0.);
		AllLep_track_z0->push_back(el->d3pd().trackz0pv());
		AllLep_track_d0->push_back(el->d3pd().trackd0pv());
		AllLep_track_sigz0->push_back(el->d3pd().tracksigz0pv());
		AllLep_track_sigd0->push_back(el->d3pd().tracksigd0pv());
		AllLep_smeared_d0->push_back(1);//el->d3pd().trackd0pv()-0.001+GetD0SmearSigma(el->d3pd().nBLHits(), el->d3pd().trackpt(), el->d3pd().tracketa());
		//Lep_charge->at(i) = el->d3pd().charge();
	}
}

void wwwAnalysis::Output::FillLeptonLooseNotTight(int i, const PhysicsObject *lep)
{

	Lep_LooseNotTight->push_back(lep->momentum());

	Lep_isFake_LooseNotTight->push_back(lep->fake());

	Lep_pt_LooseNotTight->push_back(lep->momentum().Pt());
	Lep_eta_LooseNotTight->push_back(lep->momentum().Eta());
	Lep_phi_LooseNotTight->push_back(lep->momentum().Phi());
	Lep_charge_LooseNotTight->push_back(lep->charge());
	Lep_isChargeFlipped_LooseNotTight->push_back(lep->isChargeFlipped());

	
	if(lep->type() == MUON)
	{
		Muon *mu = (Muon *)lep;
		Lep_isMuon_LooseNotTight->push_back( true);
		Lep_isCombinedMuon_LooseNotTight->push_back( mu->d3pd().isCombinedMuon());
		Lep_isSpectroMuon->push_back(mu->isSpectroMuon());
		//Lep_ptiso->at(i)  = mu->d3pd().ptcone40()/Lep->at(i)->Pt();

		Lep_ptiso_LooseNotTight->push_back(mu->d3pd().ptcone20()/Lep_LooseNotTight->at(i).Pt());
		Lep_etiso_LooseNotTight->push_back(mu->Etcone20_corr()/Lep_LooseNotTight->at(i).Pt());
		Lep_z0_exPV_LooseNotTight->push_back(mu->d3pd().id_z0_exPV());

		Lep_d0_LooseNotTight->push_back(mu->d3pd().trackd0pv());
		Lep_sigmad0_LooseNotTight->push_back(mu->d3pd().tracksigd0pv());
		Lep_loose_LooseNotTight->push_back(mu->d3pd().loose());
		Lep_medium_LooseNotTight->push_back(mu->d3pd().medium());
		Lep_tight_LooseNotTight->push_back(mu->d3pd().tight());
		//only relevant for electrons
		Lep_veryLooseLL_LooseNotTight->push_back(false);
		Lep_looseLL_LooseNotTight->push_back(false);
		Lep_mediumLL_LooseNotTight->push_back(false);
		Lep_tightLL_LooseNotTight->push_back(false);
		Lep_veryTightLL_LooseNotTight->push_back(false);
		Lep_author_LooseNotTight->push_back(mu->d3pd().author());
		//1 is Third Chain Muons, 2 is Staco
		Lep_recoAuthor_LooseNotTight->push_back((mu->useThirdChain() ? 1 : 2));
		Lep_track_z0_LooseNotTight->push_back(mu->d3pd().trackz0pvunbiased());
		Lep_track_d0_LooseNotTight->push_back(mu->d3pd().trackd0pvunbiased());
		Lep_track_sigz0_LooseNotTight->push_back(mu->d3pd().tracksigz0pvunbiased());
		Lep_track_sigd0_LooseNotTight->push_back(mu->d3pd().tracksigd0pvunbiased());
		Lep_smeared_d0_LooseNotTight->push_back(1.); //mu->d3pd().trackd0pvunbiased()-0.002+GetD0SmearSigma(mu->d3pd().nBLHits(),sin(mu->d3pd().id_theta())*fabs(1.0/mu->d3pd().id_qoverp()),-log(tan(mu->d3pd().id_theta()/2)));
		//Lep_charge->at(i) = mu->d3pd().charge();
		Lep_isSignalLike_LooseNotTight->push_back(mu->isSignalLike());
		Lep_isFromHeavyFlavor_LooseNotTight->push_back(mu->isFromHeavyFlavor());
		Lep_isFromLightFlavor_LooseNotTight->push_back(mu->isFromLightFlavor());
		Lep_isFromPhotonConversion_LooseNotTight->push_back(mu->isFromPhotonConversion());
	}
	else
	{
		Electron *el = (Electron *)lep;
		Lep_isMuon_LooseNotTight->push_back(false);
		Lep_isCombinedMuon_LooseNotTight->push_back(false);
		Lep_isSpectroMuon->push_back(false);

		Lep_ptiso_LooseNotTight->push_back(el->d3pd().ptcone20()/Lep_LooseNotTight->at(i).Pt());
		Lep_etiso_LooseNotTight->push_back(el->Etcone20_corr()/Lep_LooseNotTight->at(i).Pt());

		Lep_z0_exPV_LooseNotTight->push_back(el->d3pd().trackz0pv());

		Lep_d0_LooseNotTight->push_back(el->d3pd().trackd0pv());
		Lep_sigmad0_LooseNotTight->push_back(el->d3pd().tracksigd0pv());
		Lep_loose_LooseNotTight->push_back(el->loose());
		Lep_medium_LooseNotTight->push_back(el->medium());
		Lep_tight_LooseNotTight->push_back(el->tight());
		Lep_veryLooseLL_LooseNotTight->push_back(el->veryLooseLL());
		Lep_looseLL_LooseNotTight->push_back(el->looseLL());
		Lep_mediumLL_LooseNotTight->push_back(el->mediumLL());
		Lep_tightLL_LooseNotTight->push_back(el->tightLL());
		Lep_veryTightLL_LooseNotTight->push_back(el->veryTightLL());
		Lep_author_LooseNotTight->push_back(el->d3pd().author());
		//0 for electron reco.  This is mainly relevant for muons.
		Lep_recoAuthor_LooseNotTight->push_back(0.);
		Lep_track_z0_LooseNotTight->push_back(el->d3pd().trackz0pv());
		Lep_track_d0_LooseNotTight->push_back(el->d3pd().trackd0pv());
		Lep_track_sigz0_LooseNotTight->push_back(el->d3pd().tracksigz0pv());
		Lep_track_sigd0_LooseNotTight->push_back(el->d3pd().tracksigd0pv());
		Lep_smeared_d0_LooseNotTight->push_back(1);//el->d3pd().trackd0pv()-0.001+GetD0SmearSigma(el->d3pd().nBLHits(), el->d3pd().trackpt(), el->d3pd().tracketa());
		//Lep_charge->at(i) = el->d3pd().charge();
		Lep_isSignalLike_LooseNotTight->push_back(el->isSignalLike());
		Lep_isFromHeavyFlavor_LooseNotTight->push_back(el->isFromHeavyFlavor());
		Lep_isFromLightFlavor_LooseNotTight->push_back(el->isFromLightFlavor());
		Lep_isFromPhotonConversion_LooseNotTight->push_back(el->isFromPhotonConversion());
	}
}

void wwwAnalysis::Output::FillLeptonTag(int i, const PhysicsObject *lep)
{

	Lep_Tag->push_back(lep->momentum());

	Lep_isFake_Tag->push_back(lep->fake());

	Lep_pt_Tag->push_back(lep->momentum().Pt());
	Lep_eta_Tag->push_back(lep->momentum().Eta());
	Lep_phi_Tag->push_back(lep->momentum().Phi());
	Lep_charge_Tag->push_back(lep->charge());
	Lep_isChargeFlipped_Tag->push_back(lep->isChargeFlipped());

	
	if(lep->type() == MUON)
	{
		Muon *mu = (Muon *)lep;
		Lep_isMuon_Tag->push_back( true);
		Lep_isCombinedMuon_Tag->push_back( mu->d3pd().isCombinedMuon());
		//Lep_ptiso->at(i)  = mu->d3pd().ptcone40()/Lep->at(i)->Pt();

		Lep_ptiso_Tag->push_back(mu->d3pd().ptcone20()/Lep_Tag->at(i).Pt());
		Lep_etiso_Tag->push_back(mu->Etcone20_corr()/Lep_Tag->at(i).Pt());
		Lep_z0_exPV_Tag->push_back(mu->d3pd().id_z0_exPV());

		Lep_d0_Tag->push_back(mu->d3pd().trackd0pv());
		Lep_sigmad0_Tag->push_back(mu->d3pd().tracksigd0pv());
		Lep_loose_Tag->push_back(mu->d3pd().loose());
		Lep_medium_Tag->push_back(mu->d3pd().medium());
		Lep_tight_Tag->push_back(mu->d3pd().tight());
		//only relevant for electrons
		Lep_veryLooseLL_Tag->push_back(false);
		Lep_looseLL_Tag->push_back(false);
		Lep_mediumLL_Tag->push_back(false);
		Lep_tightLL_Tag->push_back(false);
		Lep_veryTightLL_Tag->push_back(false);
		Lep_author_Tag->push_back(mu->d3pd().author());
		//1 is Third Chain Muons, 2 is Staco
		Lep_recoAuthor_Tag->push_back((mu->useThirdChain() ? 1 : 2));
		Lep_track_z0_Tag->push_back(mu->d3pd().trackz0pvunbiased());
		Lep_track_d0_Tag->push_back(mu->d3pd().trackd0pvunbiased());
		Lep_track_sigz0_Tag->push_back(mu->d3pd().tracksigz0pvunbiased());
		Lep_track_sigd0_Tag->push_back(mu->d3pd().tracksigd0pvunbiased());
		Lep_smeared_d0_Tag->push_back(1.); //mu->d3pd().trackd0pvunbiased()-0.002+GetD0SmearSigma(mu->d3pd().nBLHits(),sin(mu->d3pd().id_theta())*fabs(1.0/mu->d3pd().id_qoverp()),-log(tan(mu->d3pd().id_theta()/2)));
		//Lep_charge->at(i) = mu->d3pd().charge();
		Lep_track_d0_o_sigd0_Tag->push_back(fabs(mu->d3pd().trackd0pvunbiased()/mu->d3pd().tracksigd0pvunbiased()));
		Lep_track_z0_o_sinTheta_Tag->push_back(fabs(mu->d3pd().trackz0pvunbiased()*sin(mu->d3pd().tracktheta())) );

		Lep_isSignalLike_Tag->push_back(mu->isSignalLike());
		Lep_isFromHeavyFlavor_Tag->push_back(mu->isFromHeavyFlavor());
		Lep_isFromLightFlavor_Tag->push_back(mu->isFromLightFlavor());
		Lep_isFromPhotonConversion_Tag->push_back(mu->isFromPhotonConversion());
	}
	else
	{
		Electron *el = (Electron *)lep;
		Lep_isMuon_Tag->push_back(false);
		Lep_isCombinedMuon_Tag->push_back(false);

		Lep_ptiso_Tag->push_back(el->d3pd().ptcone20()/Lep_Tag->at(i).Pt());
		Lep_etiso_Tag->push_back(el->Etcone20_corr()/Lep_Tag->at(i).Pt());

		Lep_z0_exPV_Tag->push_back(el->d3pd().trackz0pv());

		Lep_d0_Tag->push_back(el->d3pd().trackd0pv());
		Lep_sigmad0_Tag->push_back(el->d3pd().tracksigd0pv());
		Lep_loose_Tag->push_back(el->loose());
		Lep_medium_Tag->push_back(el->medium());
		Lep_tight_Tag->push_back(el->tight());
		Lep_veryLooseLL_Tag->push_back(el->veryLooseLL());
		Lep_looseLL_Tag->push_back(el->looseLL());
		Lep_mediumLL_Tag->push_back(el->mediumLL());
		Lep_tightLL_Tag->push_back(el->tightLL());
		Lep_veryTightLL_Tag->push_back(el->veryTightLL());
		Lep_author_Tag->push_back(el->d3pd().author());
		//0 for electron reco.  This is mainly relevant for muons.
		Lep_recoAuthor_Tag->push_back(0.);
		Lep_track_z0_Tag->push_back(el->d3pd().trackz0pv());
		Lep_track_d0_Tag->push_back(el->d3pd().trackd0pv());
		Lep_track_sigz0_Tag->push_back(el->d3pd().tracksigz0pv());
		Lep_track_sigd0_Tag->push_back(el->d3pd().tracksigd0pv());
		Lep_smeared_d0_Tag->push_back(1);//el->d3pd().trackd0pv()-0.001+GetD0SmearSigma(el->d3pd().nBLHits(), el->d3pd().trackpt(), el->d3pd().tracketa());
		//Lep_charge->at(i) = el->d3pd().charge();
		Lep_track_d0_o_sigd0_Tag->push_back(fabs(el->d3pd().trackd0pvunbiased()/el->d3pd().tracksigd0pvunbiased()));
		Lep_track_z0_o_sinTheta_Tag->push_back(fabs(el->d3pd().trackz0pvunbiased()*sin(el->d3pd().tracktheta())) );

		Lep_isSignalLike_Tag->push_back(el->isSignalLike());
		Lep_isFromHeavyFlavor_Tag->push_back(el->isFromHeavyFlavor());
		Lep_isFromLightFlavor_Tag->push_back(el->isFromLightFlavor());
		Lep_isFromPhotonConversion_Tag->push_back(el->isFromPhotonConversion());
	}
}
void wwwAnalysis::Output::FillLeptonTag2(int i, const PhysicsObject *lep)
{

	Lep_Tag2->push_back(lep->momentum());

	Lep_isFake_Tag2->push_back(lep->fake());

	Lep_pt_Tag2->push_back(lep->momentum().Pt());
	Lep_eta_Tag2->push_back(lep->momentum().Eta());
	Lep_phi_Tag2->push_back(lep->momentum().Phi());
	Lep_charge_Tag2->push_back(lep->charge());
	Lep_isChargeFlipped_Tag2->push_back(lep->isChargeFlipped());

	
	if(lep->type() == MUON)
	{
		Muon *mu = (Muon *)lep;
		Lep_isMuon_Tag2->push_back( true);
		Lep_isCombinedMuon_Tag2->push_back( mu->d3pd().isCombinedMuon());
		//Lep_ptiso->at(i)  = mu->d3pd().ptcone40()/Lep->at(i)->Pt();

		Lep_ptiso_Tag2->push_back(mu->d3pd().ptcone20()/Lep_Tag2->at(i).Pt());
		Lep_etiso_Tag2->push_back(mu->Etcone20_corr()/Lep_Tag2->at(i).Pt());
		Lep_z0_exPV_Tag2->push_back(mu->d3pd().id_z0_exPV());

		Lep_d0_Tag2->push_back(mu->d3pd().trackd0pv());
		Lep_sigmad0_Tag2->push_back(mu->d3pd().tracksigd0pv());
		Lep_loose_Tag2->push_back(mu->d3pd().loose());
		Lep_medium_Tag2->push_back(mu->d3pd().medium());
		Lep_tight_Tag2->push_back(mu->d3pd().tight());
		//only relevant for electrons
		Lep_veryLooseLL_Tag2->push_back(false);
		Lep_looseLL_Tag2->push_back(false);
		Lep_mediumLL_Tag2->push_back(false);
		Lep_tightLL_Tag2->push_back(false);
		Lep_veryTightLL_Tag2->push_back(false);
		Lep_author_Tag2->push_back(mu->d3pd().author());
		//1 is Third Chain Muons, 2 is Staco
		Lep_recoAuthor_Tag2->push_back((mu->useThirdChain() ? 1 : 2));
		Lep_track_z0_Tag2->push_back(mu->d3pd().trackz0pvunbiased());
		Lep_track_d0_Tag2->push_back(mu->d3pd().trackd0pvunbiased());
		Lep_track_sigz0_Tag2->push_back(mu->d3pd().tracksigz0pvunbiased());
		Lep_track_sigd0_Tag2->push_back(mu->d3pd().tracksigd0pvunbiased());
		Lep_smeared_d0_Tag2->push_back(1.); //mu->d3pd().trackd0pvunbiased()-0.002+GetD0SmearSigma(mu->d3pd().nBLHits(),sin(mu->d3pd().id_theta())*fabs(1.0/mu->d3pd().id_qoverp()),-log(tan(mu->d3pd().id_theta()/2)));
		//Lep_charge->at(i) = mu->d3pd().charge();
		Lep_track_d0_o_sigd0_Tag2->push_back(fabs(mu->d3pd().trackd0pvunbiased()/mu->d3pd().tracksigd0pvunbiased()));
		Lep_track_z0_o_sinTheta_Tag2->push_back(fabs(mu->d3pd().trackz0pvunbiased()*sin(mu->d3pd().tracktheta())) );

		Lep_isSignalLike_Tag2->push_back(mu->isSignalLike());
		Lep_isFromHeavyFlavor_Tag2->push_back(mu->isFromHeavyFlavor());
		Lep_isFromLightFlavor_Tag2->push_back(mu->isFromLightFlavor());
		Lep_isFromPhotonConversion_Tag2->push_back(mu->isFromPhotonConversion());
	}
	else
	{
		Electron *el = (Electron *)lep;
		Lep_isMuon_Tag2->push_back(false);
		Lep_isCombinedMuon_Tag2->push_back(false);

		Lep_ptiso_Tag2->push_back(el->d3pd().ptcone20()/Lep_Tag2->at(i).Pt());
		Lep_etiso_Tag2->push_back(el->Etcone20_corr()/Lep_Tag2->at(i).Pt());

		Lep_z0_exPV_Tag2->push_back(el->d3pd().trackz0pv());

		Lep_d0_Tag2->push_back(el->d3pd().trackd0pv());
		Lep_sigmad0_Tag2->push_back(el->d3pd().tracksigd0pv());
		Lep_loose_Tag2->push_back(el->loose());
		Lep_medium_Tag2->push_back(el->medium());
		Lep_tight_Tag2->push_back(el->tight());
		Lep_veryLooseLL_Tag2->push_back(el->veryLooseLL());
		Lep_looseLL_Tag2->push_back(el->looseLL());
		Lep_mediumLL_Tag2->push_back(el->mediumLL());
		Lep_tightLL_Tag2->push_back(el->tightLL());
		Lep_veryTightLL_Tag2->push_back(el->veryTightLL());
		Lep_author_Tag2->push_back(el->d3pd().author());
		//0 for electron reco.  This is mainly relevant for muons.
		Lep_recoAuthor_Tag2->push_back(0.);
		Lep_track_z0_Tag2->push_back(el->d3pd().trackz0pv());
		Lep_track_d0_Tag2->push_back(el->d3pd().trackd0pv());
		Lep_track_sigz0_Tag2->push_back(el->d3pd().tracksigz0pv());
		Lep_track_sigd0_Tag2->push_back(el->d3pd().tracksigd0pv());
		Lep_smeared_d0_Tag2->push_back(1);//el->d3pd().trackd0pv()-0.001+GetD0SmearSigma(el->d3pd().nBLHits(), el->d3pd().trackpt(), el->d3pd().tracketa());
		//Lep_charge->at(i) = el->d3pd().charge();
		Lep_track_d0_o_sigd0_Tag2->push_back(fabs(el->d3pd().trackd0pvunbiased()/el->d3pd().tracksigd0pvunbiased()));
		Lep_track_z0_o_sinTheta_Tag2->push_back(fabs(el->d3pd().trackz0pvunbiased()*sin(el->d3pd().tracktheta())) );

		Lep_isSignalLike_Tag2->push_back(el->isSignalLike());
		Lep_isFromHeavyFlavor_Tag2->push_back(el->isFromHeavyFlavor());
		Lep_isFromLightFlavor_Tag2->push_back(el->isFromLightFlavor());
		Lep_isFromPhotonConversion_Tag2->push_back(el->isFromPhotonConversion());
	}
}
void wwwAnalysis::Output::FillLeptonProbe(int i, const PhysicsObject *lep)
{

	Lep_Probe->push_back(lep->momentum());

	Lep_isFake_Probe->push_back(lep->fake());

	Lep_pt_Probe->push_back(lep->momentum().Pt());
	Lep_eta_Probe->push_back(lep->momentum().Eta());
	Lep_phi_Probe->push_back(lep->momentum().Phi());
	Lep_charge_Probe->push_back(lep->charge());
	Lep_isChargeFlipped_Probe->push_back(lep->isChargeFlipped());

	
	if(lep->type() == MUON)
	{
		Muon *mu = (Muon *)lep;
		Lep_isMuon_Probe->push_back( true);
		Lep_isCombinedMuon_Probe->push_back( mu->d3pd().isCombinedMuon());
		//Lep_ptiso->at(i)  = mu->d3pd().ptcone40()/Lep->at(i)->Pt();

		Lep_ptiso_Probe->push_back(mu->d3pd().ptcone20()/Lep_Probe->at(i).Pt());
		Lep_etiso_Probe->push_back(mu->Etcone20_corr()/Lep_Probe->at(i).Pt());
		Lep_z0_exPV_Probe->push_back(mu->d3pd().id_z0_exPV());

		Lep_d0_Probe->push_back(mu->d3pd().trackd0pv());
		Lep_sigmad0_Probe->push_back(mu->d3pd().tracksigd0pv());
		Lep_loose_Probe->push_back(mu->d3pd().loose());
		Lep_medium_Probe->push_back(mu->d3pd().medium());
		Lep_tight_Probe->push_back(mu->d3pd().tight());
		//only relevant for electrons
		Lep_veryLooseLL_Probe->push_back(false);
		Lep_looseLL_Probe->push_back(false);
		Lep_mediumLL_Probe->push_back(false);
		Lep_tightLL_Probe->push_back(false);
		Lep_veryTightLL_Probe->push_back(false);
		Lep_author_Probe->push_back(mu->d3pd().author());
		//1 is Third Chain Muons, 2 is Staco
		Lep_recoAuthor_Probe->push_back((mu->useThirdChain() ? 1 : 2));
		Lep_track_z0_Probe->push_back(mu->d3pd().trackz0pvunbiased());
		Lep_track_d0_Probe->push_back(mu->d3pd().trackd0pvunbiased());
		Lep_track_sigz0_Probe->push_back(mu->d3pd().tracksigz0pvunbiased());
		Lep_track_sigd0_Probe->push_back(mu->d3pd().tracksigd0pvunbiased());
		Lep_smeared_d0_Probe->push_back(1.); //mu->d3pd().trackd0pvunbiased()-0.002+GetD0SmearSigma(mu->d3pd().nBLHits(),sin(mu->d3pd().id_theta())*fabs(1.0/mu->d3pd().id_qoverp()),-log(tan(mu->d3pd().id_theta()/2)));
		//Lep_charge->at(i) = mu->d3pd().charge();
		Lep_track_d0_o_sigd0_Probe->push_back(fabs(mu->d3pd().trackd0pvunbiased()/mu->d3pd().tracksigd0pvunbiased()));
		Lep_track_z0_o_sinTheta_Probe->push_back(fabs(mu->d3pd().trackz0pvunbiased()*sin(mu->d3pd().tracktheta())) );

		Lep_isSignalLike_Probe->push_back(mu->isSignalLike());
		Lep_isFromHeavyFlavor_Probe->push_back(mu->isFromHeavyFlavor());
		Lep_isFromLightFlavor_Probe->push_back(mu->isFromLightFlavor());
		Lep_isFromPhotonConversion_Probe->push_back(mu->isFromPhotonConversion());

	}
	else
	{
		Electron *el = (Electron *)lep;
		Lep_isMuon_Probe->push_back(false);
		Lep_isCombinedMuon_Probe->push_back(false);

		Lep_ptiso_Probe->push_back(el->d3pd().ptcone20()/Lep_Probe->at(i).Pt());
		Lep_etiso_Probe->push_back(el->Etcone20_corr()/Lep_Probe->at(i).Pt());

		Lep_z0_exPV_Probe->push_back(el->d3pd().trackz0pv());

		Lep_d0_Probe->push_back(el->d3pd().trackd0pv());
		Lep_sigmad0_Probe->push_back(el->d3pd().tracksigd0pv());
		Lep_loose_Probe->push_back(el->loose());
		Lep_medium_Probe->push_back(el->medium());
		Lep_tight_Probe->push_back(el->tight());
		Lep_veryLooseLL_Probe->push_back(el->veryLooseLL());
		Lep_looseLL_Probe->push_back(el->looseLL());
		Lep_mediumLL_Probe->push_back(el->mediumLL());
		Lep_tightLL_Probe->push_back(el->tightLL());
		Lep_veryTightLL_Probe->push_back(el->veryTightLL());
		Lep_author_Probe->push_back(el->d3pd().author());
		//0 for electron reco.  This is mainly relevant for muons.
		Lep_recoAuthor_Probe->push_back(0.);
		Lep_track_z0_Probe->push_back(el->d3pd().trackz0pv());
		Lep_track_d0_Probe->push_back(el->d3pd().trackd0pv());
		Lep_track_sigz0_Probe->push_back(el->d3pd().tracksigz0pv());
		Lep_track_sigd0_Probe->push_back(el->d3pd().tracksigd0pv());
		Lep_smeared_d0_Probe->push_back(1);//el->d3pd().trackd0pv()-0.001+GetD0SmearSigma(el->d3pd().nBLHits(), el->d3pd().trackpt(), el->d3pd().tracketa());
		//Lep_charge->at(i) = el->d3pd().charge();
		Lep_track_d0_o_sigd0_Probe->push_back(fabs(el->d3pd().trackd0pvunbiased()/el->d3pd().tracksigd0pvunbiased()));
		Lep_track_z0_o_sinTheta_Probe->push_back(fabs(el->d3pd().trackz0pvunbiased()*sin(el->d3pd().tracktheta())) );
		Lep_isSignalLike_Probe->push_back(el->isSignalLike());
		Lep_isFromHeavyFlavor_Probe->push_back(el->isFromHeavyFlavor());
		Lep_isFromLightFlavor_Probe->push_back(el->isFromLightFlavor());
		Lep_isFromPhotonConversion_Probe->push_back(el->isFromPhotonConversion());
	}
}

void wwwAnalysis::Output::FillLeptonLoose(int i, const PhysicsObject *lep)
{

	Lep_Loose->push_back(lep->momentum());

	Lep_isFake_Loose->push_back(lep->fake());

	Lep_pt_Loose->push_back(lep->momentum().Pt());
	Lep_eta_Loose->push_back(lep->momentum().Eta());
	Lep_phi_Loose->push_back(lep->momentum().Phi());
	Lep_charge_Loose->push_back(lep->charge());
	Lep_isChargeFlipped_Loose->push_back(lep->isChargeFlipped());

	
	if(lep->type() == MUON)
	{
		Muon *mu = (Muon *)lep;
		Lep_isMuon_Loose->push_back( true);
		Lep_isCombinedMuon_Loose->push_back( mu->d3pd().isCombinedMuon());
		//Lep_ptiso->at(i)  = mu->d3pd().ptcone40()/Lep->at(i)->Pt();

		Lep_ptiso_Loose->push_back(mu->d3pd().ptcone20()/Lep_Loose->at(i).Pt());
		Lep_etiso_Loose->push_back(mu->Etcone20_corr()/Lep_Loose->at(i).Pt());
		Lep_z0_exPV_Loose->push_back(mu->d3pd().id_z0_exPV());

		Lep_d0_Loose->push_back(mu->d3pd().trackd0pv());
		Lep_sigmad0_Loose->push_back(mu->d3pd().tracksigd0pv());
		Lep_loose_Loose->push_back(mu->d3pd().loose());
		Lep_medium_Loose->push_back(mu->d3pd().medium());
		Lep_tight_Loose->push_back(mu->d3pd().tight());
		//only relevant for electrons
		Lep_veryLooseLL_Loose->push_back(false);
		Lep_looseLL_Loose->push_back(false);
		Lep_mediumLL_Loose->push_back(false);
		Lep_tightLL_Loose->push_back(false);
		Lep_veryTightLL_Loose->push_back(false);
		Lep_author_Loose->push_back(mu->d3pd().author());
		//1 is Third Chain Muons, 2 is Staco
		Lep_recoAuthor_Loose->push_back((mu->useThirdChain() ? 1 : 2));
		Lep_track_z0_Loose->push_back(mu->d3pd().trackz0pvunbiased());
		Lep_track_d0_Loose->push_back(mu->d3pd().trackd0pvunbiased());
		Lep_track_sigz0_Loose->push_back(mu->d3pd().tracksigz0pvunbiased());
		Lep_track_sigd0_Loose->push_back(mu->d3pd().tracksigd0pvunbiased());
		Lep_smeared_d0_Loose->push_back(1.); //mu->d3pd().trackd0pvunbiased()-0.002+GetD0SmearSigma(mu->d3pd().nBLHits(),sin(mu->d3pd().id_theta())*fabs(1.0/mu->d3pd().id_qoverp()),-log(tan(mu->d3pd().id_theta()/2)));
		//Lep_charge->at(i) = mu->d3pd().charge();
		Lep_isSignalLike_Loose->push_back(mu->isSignalLike());
		Lep_isFromHeavyFlavor_Loose->push_back(mu->isFromHeavyFlavor());
		Lep_isFromLightFlavor_Loose->push_back(mu->isFromLightFlavor());
		Lep_isFromPhotonConversion_Loose->push_back(mu->isFromPhotonConversion());
	}
	else
	{
		Electron *el = (Electron *)lep;
		Lep_isMuon_Loose->push_back(false);
		Lep_isCombinedMuon_Loose->push_back(false);
		Lep_isSpectroMuon->push_back(false);

		Lep_ptiso_Loose->push_back(el->d3pd().ptcone20()/Lep_Loose->at(i).Pt());
		Lep_etiso_Loose->push_back(el->Etcone20_corr()/Lep_Loose->at(i).Pt());

		Lep_z0_exPV_Loose->push_back(el->d3pd().trackz0pv());

		Lep_d0_Loose->push_back(el->d3pd().trackd0pv());
		Lep_sigmad0_Loose->push_back(el->d3pd().tracksigd0pv());
		Lep_loose_Loose->push_back(el->loose());
		Lep_medium_Loose->push_back(el->medium());
		Lep_tight_Loose->push_back(el->tight());
		Lep_veryLooseLL_Loose->push_back(el->veryLooseLL());
		Lep_looseLL_Loose->push_back(el->looseLL());
		Lep_mediumLL_Loose->push_back(el->mediumLL());
		Lep_tightLL_Loose->push_back(el->tightLL());
		Lep_veryTightLL_Loose->push_back(el->veryTightLL());
		Lep_author_Loose->push_back(el->d3pd().author());
		//0 for electron reco.  This is mainly relevant for muons.
		Lep_recoAuthor_Loose->push_back(0.);
		Lep_track_z0_Loose->push_back(el->d3pd().trackz0pv());
		Lep_track_d0_Loose->push_back(el->d3pd().trackd0pv());
		Lep_track_sigz0_Loose->push_back(el->d3pd().tracksigz0pv());
		Lep_track_sigd0_Loose->push_back(el->d3pd().tracksigd0pv());
		Lep_smeared_d0_Loose->push_back(1);//el->d3pd().trackd0pv()-0.001+GetD0SmearSigma(el->d3pd().nBLHits(), el->d3pd().trackpt(), el->d3pd().tracketa());
		//Lep_charge->at(i) = el->d3pd().charge();
		Lep_isSignalLike_Loose->push_back(el->isSignalLike());
		Lep_isFromHeavyFlavor_Loose->push_back(el->isFromHeavyFlavor());
		Lep_isFromLightFlavor_Loose->push_back(el->isFromLightFlavor());
		Lep_isFromPhotonConversion_Loose->push_back(el->isFromPhotonConversion());
	}
}
/*
void wwwAnalysis::Output::FillLeptonInc(int i, const PhysicsObject *lep)
{

	Lep_inc->push_back(lep->momentum());
	Lep_inc_charge->push_back(lep->charge());
	Lep_inc_isChargeFlipped->push_back(lep->isChargeFlipped());

	
	if(lep->type() == MUON)
	{
		Muon *mu = (Muon *)lep;
		Lep_inc_isMuon->push_back( true);
		//Lep_ptiso->at(i)  = mu->d3pd().ptcone40()/Lep->at(i)->Pt();
		Lep_inc_isCombined->push_back(mu->d3pd().isCombinedMuon());


		if (mu->d3pd().loose()) Mu_inc_pt_loose->push_back(lep->momentum().Pt());
		if (mu->d3pd().medium()) Mu_inc_pt_medium->push_back(lep->momentum().Pt());
		if (mu->d3pd().tight()) Mu_inc_pt_tight->push_back(lep->momentum().Pt());
	}
	else
	{
		Electron *el = (Electron *)lep;
		Lep_inc_isMuon->push_back(false);
		//meaningless for electrons
		//but we don't want it to be thrown away
		//because of this
		Lep_inc_isCombined->push_back(true); 



		if (el->loose()) El_inc_pt_loose->push_back(lep->momentum().Pt());
		if (el->medium()) El_inc_pt_medium->push_back(lep->momentum().Pt());
		if (el->tight()) El_inc_pt_tight->push_back(lep->momentum().Pt());
		if (el->veryLooseLL()) El_inc_pt_veryLooseLL->push_back(lep->momentum().Pt());
		if (el->looseLL()) El_inc_pt_looseLL->push_back(lep->momentum().Pt());
		if (el->mediumLL()) El_inc_pt_mediumLL->push_back(lep->momentum().Pt());
		if (el->tightLL()) El_inc_pt_tightLL->push_back(lep->momentum().Pt());
		if (el->veryTightLL()) El_inc_pt_veryTightLL->push_back(lep->momentum().Pt());
	}
}
*/
void wwwAnalysis::Output::Fill(const D3PDReader::Event &event, InitialState init, FinalState final, double lumi,
				int nsfos, int nsfos_all,
				const vector<double> &masses_sfos, const vector<double> &masses_sfos_all,
				 int nPV2, int nPV3, 
				 //int btsEff70,
				 int btsEff85,
				 double s2,
				 double mufix, const vector<wwwAnalysis::PhysicsObject *> &leps, 
				 const vector<wwwAnalysis::PhysicsObject *> &Fakeleps,
				 //const vector<wwwAnalysis::PhysicsObject *> &Incleps,
				 const vector<wwwAnalysis::PhysicsObject *> &looseNotTightleps,
				 const vector<wwwAnalysis::PhysicsObject *> &looseleps,
				 const vector<wwwAnalysis::PhysicsObject *> &allLeps,
				 const vector<wwwAnalysis::PhysicsObject *> &tags,
				 const vector<wwwAnalysis::PhysicsObject *> &tags2,
				 const vector<wwwAnalysis::PhysicsObject *> &probes,
				 bool evHasSpectroMu,
			   const std::vector<Jet> &jets, 
			   const MissingEt &met,
			   double mcWeight, double sfWeight, double puWeight, 
			   //double btagWeightEff70, 
			   double btagWeightEff85, 
			   double trigWeight, double xsecWeight, double chargeWeight, double mxmWeight, double ffWeight, bool doChargeFlip, bool is_fake,bool is_egamma_stream, JVFSys sysJVF, OutputInformations& AdditionnalInfo,bool hasLooseEl, bool hasLooseMu)
{
	nLep=0;
	//nLep_inc=0;
	nLep_fake=0;
	nAllLep=0;
	nLep_LooseNotTight=0;
	nLep_Tag=0;
	nLep_Tag2=0;
	nLep_Probe=0;
	nLep_Loose=0;
Lep->clear();
Lep_ptiso->clear();
Lep_etiso->clear();
Lep_z0_exPV->clear();
		
Lep_d0->clear();
Lep_sigmad0->clear();
Lep_track_z0->clear();
Lep_track_d0->clear();
Lep_track_sigz0->clear();
Lep_track_sigd0->clear();
Lep_track_theta->clear();
Lep_track_d0_o_sigd0->clear();
Lep_track_z0_o_sinTheta->clear();

Lep_isSignalLike->clear();
Lep_isFromHeavyFlavor->clear();
Lep_isFromLightFlavor->clear();
Lep_isFromPhotonConversion->clear();


Lep_eta->clear();
Lep_phi->clear();
Lep_pt->clear();
Lep_mt->clear();
Lep_mt_STVF->clear();
Lep_charge->clear();		
Lep_isChargeFlipped->clear();		
Lep_isSFOS->clear();	

Lep_loose->clear();	
Lep_medium->clear();	
Lep_tight->clear();	
Lep_veryLooseLL->clear();	
Lep_looseLL->clear();	
Lep_mediumLL->clear();	
Lep_tightLL->clear();	
Lep_veryTightLL->clear();	
Lep_author->clear();
Lep_recoAuthor->clear();
Lep_isMuon->clear();	
Lep_isCombinedMuon->clear();	
Lep_isSpectroMuon->clear();	
Lep_isFake->clear();	


AllLep->clear();
AllLep_ptiso->clear();
AllLep_etiso->clear();
AllLep_z0_exPV->clear();
		
AllLep_d0->clear();
AllLep_sigmad0->clear();
AllLep_track_z0->clear();
AllLep_track_d0->clear();
AllLep_track_sigz0->clear();
AllLep_track_sigd0->clear();
AllLep_smeared_d0->clear();


AllLep_eta->clear();
AllLep_phi->clear();
AllLep_pt->clear();
AllLep_charge->clear();		
AllLep_isChargeFlipped->clear();		
	
AllLep_loose->clear();	
AllLep_medium->clear();	
AllLep_tight->clear();	
AllLep_veryLooseLL->clear();	
AllLep_looseLL->clear();	
AllLep_mediumLL->clear();	
AllLep_tightLL->clear();	
AllLep_veryTightLL->clear();	
AllLep_author->clear();
AllLep_recoAuthor->clear();
AllLep_isMuon->clear();	
AllLep_isCombinedMuon->clear();	
AllLep_isSpectroMuon->clear();	
AllLep_isFake->clear();	

/*
Mu_inc_pt_loose->clear();
Mu_inc_pt_medium->clear();
Mu_inc_pt_tight->clear();
El_inc_pt_loose->clear();
El_inc_pt_medium->clear();
El_inc_pt_tight->clear();
El_inc_pt_veryLooseLL->clear();
El_inc_pt_looseLL->clear();
El_inc_pt_mediumLL->clear();
El_inc_pt_tightLL->clear();
El_inc_pt_veryTightLL->clear();

Lep_inc->clear();
Lep_inc_charge->clear();		
Lep_inc_isChargeFlipped->clear();		
	
Lep_inc_isMuon->clear();	
Lep_inc_isCombined->clear();	
Lep_inc_isFake->clear();	
*/

Lep_LooseNotTight->clear();
Lep_ptiso_LooseNotTight->clear();
Lep_etiso_LooseNotTight->clear();
Lep_z0_exPV_LooseNotTight->clear();
		
Lep_d0_LooseNotTight->clear();
Lep_sigmad0_LooseNotTight->clear();
Lep_track_z0_LooseNotTight->clear();
Lep_track_d0_LooseNotTight->clear();
Lep_track_sigz0_LooseNotTight->clear();
Lep_track_sigd0_LooseNotTight->clear();
Lep_smeared_d0_LooseNotTight->clear();


Lep_eta_LooseNotTight->clear();
Lep_phi_LooseNotTight->clear();
Lep_pt_LooseNotTight->clear();
Lep_mt_LooseNotTight->clear();
Lep_mt_STVF_LooseNotTight->clear();
Lep_charge_LooseNotTight->clear();		
Lep_isChargeFlipped_LooseNotTight->clear();		
	
Lep_loose_LooseNotTight->clear();	
Lep_medium_LooseNotTight->clear();	
Lep_tight_LooseNotTight->clear();	
Lep_veryLooseLL_LooseNotTight->clear();	
Lep_looseLL_LooseNotTight->clear();	
Lep_mediumLL_LooseNotTight->clear();	
Lep_tightLL_LooseNotTight->clear();	
Lep_veryTightLL_LooseNotTight->clear();	
Lep_author_LooseNotTight->clear();
Lep_recoAuthor_LooseNotTight->clear();
Lep_isMuon_LooseNotTight->clear();	
Lep_isCombinedMuon_LooseNotTight->clear();	
Lep_isSpectroMuon_LooseNotTight->clear();	
Lep_isFake_LooseNotTight->clear();	

Lep_isSignalLike_LooseNotTight->clear();
Lep_isFromHeavyFlavor_LooseNotTight->clear();
Lep_isFromLightFlavor_LooseNotTight->clear();
Lep_isFromPhotonConversion_LooseNotTight->clear();



Lep_Loose->clear();
Lep_ptiso_Loose->clear();
Lep_etiso_Loose->clear();
Lep_z0_exPV_Loose->clear();
		
Lep_d0_Loose->clear();
Lep_sigmad0_Loose->clear();
Lep_track_z0_Loose->clear();
Lep_track_d0_Loose->clear();
Lep_track_sigz0_Loose->clear();
Lep_track_sigd0_Loose->clear();
Lep_smeared_d0_Loose->clear();


Lep_eta_Loose->clear();
Lep_phi_Loose->clear();
Lep_pt_Loose->clear();
Lep_mt_Loose->clear();
Lep_mt_STVF_Loose->clear();
Lep_charge_Loose->clear();		
Lep_isChargeFlipped_Loose->clear();		
	
Lep_loose_Loose->clear();	
Lep_medium_Loose->clear();	
Lep_tight_Loose->clear();	
Lep_veryLooseLL_Loose->clear();	
Lep_looseLL_Loose->clear();	
Lep_mediumLL_Loose->clear();	
Lep_tightLL_Loose->clear();	
Lep_veryTightLL_Loose->clear();	
Lep_author_Loose->clear();
Lep_recoAuthor_Loose->clear();
Lep_isMuon_Loose->clear();	
Lep_isCombinedMuon_Loose->clear();	
Lep_isSpectroMuon_Loose->clear();	
Lep_isFake_Loose->clear();	

Lep_isSignalLike_Loose->clear();
Lep_isFromHeavyFlavor_Loose->clear();
Lep_isFromLightFlavor_Loose->clear();
Lep_isFromPhotonConversion_Loose->clear();

Lep_Tag->clear();
Lep_ptiso_Tag->clear();
Lep_etiso_Tag->clear();
Lep_z0_exPV_Tag->clear();
		
Lep_d0_Tag->clear();
Lep_sigmad0_Tag->clear();
Lep_track_z0_Tag->clear();
Lep_track_d0_Tag->clear();
Lep_track_sigz0_Tag->clear();
Lep_track_sigd0_Tag->clear();
Lep_smeared_d0_Tag->clear();
Lep_track_d0_o_sigd0_Tag->clear();
Lep_track_z0_o_sinTheta_Tag->clear();

Lep_isSignalLike_Tag->clear();
Lep_isFromHeavyFlavor_Tag->clear();
Lep_isFromLightFlavor_Tag->clear();
Lep_isFromPhotonConversion_Tag->clear();


Lep_eta_Tag->clear();
Lep_phi_Tag->clear();
Lep_pt_Tag->clear();
Lep_mt_Tag->clear();
Lep_mt_STVF_Tag->clear();
Lep_charge_Tag->clear();		
Lep_isChargeFlipped_Tag->clear();		
Lep_loose_Tag->clear();	
Lep_medium_Tag->clear();	
Lep_tight_Tag->clear();	
Lep_veryLooseLL_Tag->clear();	
Lep_looseLL_Tag->clear();	
Lep_mediumLL_Tag->clear();	
Lep_tightLL_Tag->clear();	
Lep_veryTightLL_Tag->clear();	
Lep_author_Tag->clear();
Lep_recoAuthor_Tag->clear();
Lep_isMuon_Tag->clear();	
Lep_isCombinedMuon_Tag->clear();	
Lep_isSpectroMuon_Tag->clear();	
Lep_isFake_Tag->clear();	

Lep_Tag2->clear();
Lep_ptiso_Tag2->clear();
Lep_etiso_Tag2->clear();
Lep_z0_exPV_Tag2->clear();
		
Lep_d0_Tag2->clear();
Lep_sigmad0_Tag2->clear();
Lep_track_z0_Tag2->clear();
Lep_track_d0_Tag2->clear();
Lep_track_sigz0_Tag2->clear();
Lep_track_sigd0_Tag2->clear();
Lep_smeared_d0_Tag2->clear();
Lep_track_d0_o_sigd0_Tag2->clear();
Lep_track_z0_o_sinTheta_Tag2->clear();

Lep_isSignalLike_Tag2->clear();
Lep_isFromHeavyFlavor_Tag2->clear();
Lep_isFromLightFlavor_Tag2->clear();
Lep_isFromPhotonConversion_Tag2->clear();


Lep_eta_Tag2->clear();
Lep_phi_Tag2->clear();
Lep_pt_Tag2->clear();
Lep_mt_Tag2->clear();
Lep_mt_STVF_Tag2->clear();
Lep_charge_Tag2->clear();		
Lep_isChargeFlipped_Tag2->clear();		
Lep_loose_Tag2->clear();	
Lep_medium_Tag2->clear();	
Lep_tight_Tag2->clear();	
Lep_veryLooseLL_Tag2->clear();	
Lep_looseLL_Tag2->clear();	
Lep_mediumLL_Tag2->clear();	
Lep_tightLL_Tag2->clear();	
Lep_veryTightLL_Tag2->clear();	
Lep_author_Tag2->clear();
Lep_recoAuthor_Tag2->clear();
Lep_isMuon_Tag2->clear();	
Lep_isCombinedMuon_Tag2->clear();	
Lep_isSpectroMuon_Tag2->clear();	
Lep_isFake_Tag2->clear();	


Lep_Probe->clear();
Lep_ptiso_Probe->clear();
Lep_etiso_Probe->clear();
Lep_z0_exPV_Probe->clear();
		
Lep_d0_Probe->clear();
Lep_sigmad0_Probe->clear();
Lep_track_z0_Probe->clear();
Lep_track_d0_Probe->clear();
Lep_track_sigz0_Probe->clear();
Lep_track_sigd0_Probe->clear();
Lep_smeared_d0_Probe->clear();


Lep_track_d0_o_sigd0_Probe->clear();
Lep_track_z0_o_sinTheta_Probe->clear();

Lep_isSignalLike_Probe->clear();
Lep_isFromHeavyFlavor_Probe->clear();
Lep_isFromLightFlavor_Probe->clear();
Lep_isFromPhotonConversion_Probe->clear();


Lep_eta_Probe->clear();
Lep_phi_Probe->clear();
Lep_pt_Probe->clear();
Lep_mt_Probe->clear();
Lep_mt_STVF_Probe->clear();
Lep_charge_Probe->clear();		
Lep_isChargeFlipped_Probe->clear();		
	
Lep_loose_Probe->clear();	
Lep_medium_Probe->clear();	
Lep_tight_Probe->clear();	
Lep_veryLooseLL_Probe->clear();	
Lep_looseLL_Probe->clear();	
Lep_mediumLL_Probe->clear();	
Lep_tightLL_Probe->clear();	
Lep_veryTightLL_Probe->clear();	
Lep_author_Probe->clear();
Lep_recoAuthor_Probe->clear();
Lep_isMuon_Probe->clear();	
Lep_isCombinedMuon_Probe->clear();	
Lep_isSpectroMuon_Probe->clear();	
Lep_isFake_Probe->clear();	

massesSFOS->clear();
massesSFOSAll->clear();
massesElMu->clear();
massesElEl->clear();
massesMuMu->clear();

	//the masses are always filled even if they don't match the criteria,
	//then it is just given a value of -1
	//this allows one to identify the pair combination bassed on the pair index.
	//with three leptons it should be 0-1, 0-2, 1-2
	//i.e. leading-subleading, leading-minimum, subleading-minimum
	for(int i =0;i<leps.size();i++){
	  for(int j=0;j<leps.size();j++){
	  	if (i >=j) continue;
		bool oppositeFlavor = false;
		bool ElEl = false;
		bool MuMu = true;
		double massElEl = -1;
		double massElMu = -1;
		double massMuMu = -1;
		TLorentzVector leplep;
		leplep = leps[i]->momentum() + leps[j]->momentum();
		if (leps[i]->type()!=leps[j]->type()) massElMu = leplep.M();
		else if (leps[i]->type()==ELECTRON) massElEl = leplep.M();
		else massMuMu = leplep.M();

		massesElEl->push_back(massElEl);
		massesElMu->push_back(massElMu);
		massesMuMu->push_back(massMuMu);
	  }
	}


	FakeLeptons = is_fake;
	if (leps.size()==2) OSLeptons = (leps[0]->charge() > 0 && leps[1]->charge() < 0) || 
					(leps[0]->charge() < 0 && leps[1]->charge() > 0);
	else OSLeptons = false;
  	//btagsEff60 = btsEff60;
  	//btagsEff70 = btsEff70;
  	//btagsEff80 = btsEff80;
  	btagsEff85 = btsEff85;

        isEGammaStream = is_egamma_stream;
	hasLooseNotTightElectrons = hasLooseEl;
	hasLooseNotTightMuons = hasLooseMu;
	//fill leptons
	
	nLep=int(leps.size());
	//nLep_inc = int(Incleps.size());
	nLep_fake=int(Fakeleps.size());
	
	nLep_LooseNotTight = int(looseNotTightleps.size());
	nLep_Loose = int(looseleps.size());
	nLep_Tag = int(tags.size());
	nLep_Tag2 = int(tags2.size());
	nLep_Probe = int(probes.size());
	nAllLep = int(allLeps.size());

	ComEnergySquared = s2;

   	vector<int> nlep_sfos;
   	vector<int> nlepfake_sfos;

   	nlep_sfos.clear();
   	nlepfake_sfos.clear();

   	bool SFOS=false;
	for(int ilep=0;ilep<leps.size();ilep++){
		SFOS=false;
		for( int jlep=0;jlep<leps.size();jlep++){
		if((leps[ilep]->type() ==leps[jlep]->type())&&(leps[ilep]->charge()*leps[jlep]->charge()==-1)){
			SFOS=true;
			break;
			}
		}
		if(!SFOS){
			for (int jlep=0;jlep<Fakeleps.size();jlep++){
			if((leps[ilep]->type() ==Fakeleps[jlep]->type())&&(leps[ilep]->charge()*Fakeleps[jlep]->charge()==-1)){
				SFOS=true;
				break;
				}
			}	
		}
		if(SFOS){
			nlep_sfos.push_back(true);
		}
		else{
			nlep_sfos.push_back(false);
		}

	}




	SFOS=false;
	for(int ilep=0;ilep<Fakeleps.size();ilep++){
		SFOS=false;
		for( int jlep=0;jlep<leps.size();jlep++){
		if((Fakeleps[ilep]->type() ==leps[jlep]->type())&&(Fakeleps[ilep]->charge()*leps[jlep]->charge()==-1)){
			SFOS=true;
			break;
			}
		}
		if(!SFOS){
			for (int jlep=0;jlep<Fakeleps.size();jlep++){
			if((Fakeleps[ilep]->type() ==Fakeleps[jlep]->type())&&(Fakeleps[ilep]->charge()*Fakeleps[jlep]->charge()==-1)){
				SFOS=true;
				break;
				}
			}	
		}
		if(SFOS){
			nlepfake_sfos.push_back(true);
		}
		else{
			nlepfake_sfos.push_back(false);
		}
	}


	TLorentzVector allLepTLV;
	for(int ilep=0;ilep<leps.size();ilep++){
		bool mu=leps[ilep]->type() == MUON;
		allLepTLV += leps[ilep]->momentum();
		Lep_mt_STVF->push_back(TMath::Sqrt(2*leps[ilep]->momentum().Pt()*met.momentumSTVF().Et()*(1-TMath::Cos(leps[ilep]->momentum().Phi()-met.momentumSTVF().Phi()))));
		Lep_mt->push_back(TMath::Sqrt(2*leps[ilep]->momentum().Pt()*met.Et()*(1-TMath::Cos(leps[ilep]->momentum().Phi()-met.phi()))));
		FillLepton(ilep,leps[ilep],nlep_sfos[ilep]);
	}
	for (int ilep=0;ilep<probes.size();ilep++){
		Lep_mt_STVF_Probe->push_back(TMath::Sqrt(2*probes[ilep]->momentum().Pt()*met.momentumSTVF().Et()*(1-TMath::Cos(probes[ilep]->momentum().Phi()-met.momentumSTVF().Phi()))));
		Lep_mt_Probe->push_back(TMath::Sqrt(2*probes[ilep]->momentum().Pt()*met.Et()*(1-TMath::Cos(probes[ilep]->momentum().Phi()-met.phi()))));
	}
	for (int ilep=0;ilep<tags.size();ilep++){
		Lep_mt_STVF_Tag->push_back(TMath::Sqrt(2*tags[ilep]->momentum().Pt()*met.momentumSTVF().Et()*(1-TMath::Cos(tags[ilep]->momentum().Phi()-met.momentumSTVF().Phi()))));
		Lep_mt_Tag->push_back(TMath::Sqrt(2*tags[ilep]->momentum().Pt()*met.Et()*(1-TMath::Cos(tags[ilep]->momentum().Phi()-met.phi()))));
	}

	for (int ilep=0;ilep<tags2.size();ilep++){
		Lep_mt_STVF_Tag2->push_back(TMath::Sqrt(2*tags2[ilep]->momentum().Pt()*met.momentumSTVF().Et()*(1-TMath::Cos(tags2[ilep]->momentum().Phi()-met.momentumSTVF().Phi()))));
		Lep_mt_Tag2->push_back(TMath::Sqrt(2*tags2[ilep]->momentum().Pt()*met.Et()*(1-TMath::Cos(tags2[ilep]->momentum().Phi()-met.phi()))));
	}

	AllLep_mt_STVF = TMath::Sqrt(2*allLepTLV.Pt()*met.momentumSTVF().Et()*(1-TMath::Cos(allLepTLV.Phi()-met.momentumSTVF().Phi())));
	AllLep_mt= TMath::Sqrt(2*allLepTLV.Pt()*met.Et()*(1-TMath::Cos(allLepTLV.Phi()-met.phi())));
	AllLep_deltaPhiMET = allLepTLV.DeltaPhi(met.momentum());
	AllLep_deltaPhiMET_STVF = allLepTLV.DeltaPhi(met.momentumSTVF());

	for(unsigned int ilep=0;ilep<allLeps.size();ilep++){
		FillAllLepton(ilep,allLeps[ilep]);
	}

	

	for(int ilep=0;ilep<Fakeleps.size();ilep++){
		bool mu=Fakeleps[ilep]->type() == MUON;
		Fakeleps[ilep]->setFakeStatus(true);
		FillLepton(ilep,Fakeleps[ilep],nlepfake_sfos[ilep]);//verifier que le bool fake est bien mit...
	}

	for(unsigned int ilep=0;ilep<looseleps.size();ilep++){
		FillLeptonLoose(ilep,looseleps[ilep]);
	}
	for(unsigned int ilep=0;ilep<looseNotTightleps.size();ilep++){
		FillLeptonLooseNotTight(ilep,looseNotTightleps[ilep]);
	}

	for(unsigned int ilep=0;ilep<tags.size();ilep++){
		FillLeptonTag(ilep,tags[ilep]);
	}
	for(unsigned int ilep=0;ilep<tags2.size();ilep++){
		FillLeptonTag2(ilep,tags2[ilep]);
	}
	for(unsigned int ilep=0;ilep<probes.size();ilep++){
		FillLeptonProbe(ilep,probes[ilep]);
	}
	
	//fill jets
	Jets->resize(jets.size());
	bJets->resize(jets.size());
	JetsJVF->resize(jets.size());
	for(unsigned int i = 0; i < jets.size(); i++)
  {
		Jets->at(i) = jets[i].momentum();
		bJets->at(i) = jets[i].btagged(Eff85,sysJVF);
		JetsJVF->at(i) = jets[i].jvf(sysJVF);
  }
	
	MET_final_Et = met.Et();
	MET_final_phi = met.phi();
	MET_final_sumEt = met.sumEt();

	MET_final_Et_raw = met.rawMomentum().Et();
	MET_final_phi_raw = met.rawMomentum().Phi();
	MET_final_sumEt_raw = met.sumEtRaw();

	MET_final_Et_STVF = met.momentumSTVF().Et();
	MET_final_phi_STVF = met.momentumSTVF().Phi();
	MET_final_sumEt_STVF = met.sumEtSTVF();

	nSFOS = nsfos;
	nSFOSAll = nsfos_all;

	massesSFOS->clear();
	massesSFOSAll->clear();
	for (unsigned int i =0;i < masses_sfos.size() ;i++)
		massesSFOS->push_back(masses_sfos.at(i));
	for (unsigned int i =0;i < masses_sfos_all.size() ;i++)
		massesSFOSAll->push_back(masses_sfos_all.at(i));

	nPV_3trks = nPV3;
	nPV_2trks = nPV2;
	mu = mufix;


	
	eventHasSpectroMuons = evHasSpectroMu;
	/*
	EF_mu36_tight = event.triggerbits.EF_mu36_tight() ? 1 : 0;
	EF_mu24i_tight = event.triggerbits.EF_mu24i_tight() ? 1 : 0 ;
	EF_e24vhi_medium1 = event.triggerbits.EF_e24vhi_medium1() ? 1 : 0;
	EF_e60_medium1 = event.triggerbits.EF_e60_medium1() ? 1 : 0 ;
	*/



	DiLepton = AdditionnalInfo.dilep;
	QuadriLepton = AdditionnalInfo.quadlep;
	mll = AdditionnalInfo.dilep_mll;
	mT1 = AdditionnalInfo.dilep_mT1;
	mT2 = AdditionnalInfo.dilep_mT2;
	m12 = AdditionnalInfo.quadlep_m12;
	m34 = AdditionnalInfo.quadlep_m34;
	if(QuadriLepton) m4l = (leps[0]->momentum()+leps[1]->momentum()+leps[2]->momentum()+leps[3]->momentum()).M();
	SumHPTO = AdditionnalInfo.dilep_SumHPTO;
	SumCosDphi = AdditionnalInfo.dilep_SumCosDphi;
	vector<int> tmp_pairs;
	tmp_pairs.clear();
	tmp_pairs.push_back(AdditionnalInfo.quad_lep1);
	tmp_pairs.push_back(AdditionnalInfo.quad_lep2);
	tmp_pairs.push_back(AdditionnalInfo.quad_lep3);
	tmp_pairs.push_back(AdditionnalInfo.quad_lep4);
	Lep_4lpair = tmp_pairs;	



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
  DoChargeFlip = doChargeFlip;
  XSecWeight = xsecWeight;
  CorrectionWeight = 1.0;

  MET_CellOut_Eflow_STVF_Et = event.MET_CellOut_Eflow_STVF.et();
  MET_CellOut_Eflow_STVF_Phi = event.MET_CellOut_Eflow_STVF.phi();
  MET_CellOut_Eflow_STVF_SumEt = event.MET_CellOut_Eflow_STVF.sumet();
  MET_CellOut_Eflow_Et = event.MET_CellOut_Eflow.et();
  MET_CellOut_Eflow_Phi = event.MET_CellOut_Eflow.phi();
  MET_CellOut_Eflow_SumEt = event.MET_CellOut_Eflow.sumet();

  MxMWeight = mxmWeight;
  FormFactorWeight = ffWeight;
  LumiWeight = lumi;

  if(event.eventinfo.mc_channel_number.IsAvailable() && event.eventinfo.mc_channel_number() > 0)
  	RunNumber = event.eventinfo.mc_channel_number();
  else
  	RunNumber = event.eventinfo.RunNumber();
  EventNumber=event.eventinfo.EventNumber();
  lbn=event.eventinfo.lbn();
  PrimaryVertexNTracks= event.vxp.n() > 0 ? event.vxp[0].nTracks() : 0;

  Truth_initial = init;
  Truth_final = final;

  tree()->Fill();
}

float wwwAnalysis::Output::GetD0SmearSigma(int nBL, float pt, float eta) {
  return 1.;

  /*
  if(nBL>=2) nBL = 2;

  float sinTheta = 1./cosh(eta);
  float p = pt*cosh(eta);
  float p_quant = 1./sqrt(pt/1000.*pt/1000.*sinTheta)/1000.; // 1./sqrt(p*p*sinTheta*sinTheta*sinTheta)

//  int Xbin = smear_X->FindFixBin(eta);
//  int Ybin = smear_Y->FindFixBin(p_quant);

  int Xbin = smearD0[nBL]->GetXaxis()->FindFixBin(eta);
  int Ybin = smearD0[nBL]->GetYaxis()->FindFixBin(p_quant);
  
  float sigma = smearD0[nBL]->GetBinContent(Xbin, Ybin);
  return rand->Gaus(0,sigma);
  */

}

void wwwAnalysis::Output::finalize()
{
	/*
	if(ip_smear){ip_smear->Close();delete ip_smear; ip_smear=0;}
	if(rand){delete rand;rand=0;}
	*/
}
