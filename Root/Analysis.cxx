#include "wwwAnalysis/Analysis.h"
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <EventLoop/Job.h>
#include <SampleHandler/MetaObject.h>
#include <TH2.h>
#include <TLorentzVector.h>

#include <TString.h>


#include <TTree.h>
#include <EventLoop/OutputStream.h>

#include <iostream>
#include <map>


// this is needed to distribute the algorithm to the workers
ClassImp(wwwAnalysis::Analysis);

std::map<int,std::map<int, int> > wwwAnalysis::Analysis::m_mRunEvents;
//mapEventSelectorIndexOuter_t wwwAnalysis::Analysis::m_mEventSelectorIndex; 

wwwAnalysis :: Analysis :: Analysis ()
{
  // put any variable initialization code here
  // e.g. initialize all pointers to 0
  // note that advanced variable intialization (e.g. histogram
  // creation) should be done in initialize
  m_hGoodRunsListReader = 0;
  m_hPileupTool = 0;
  m_hPileupToolUp = 0;
  m_hPileupToolDown = 0;
  m_hPileupWriteTool = 0;
  m_hJetCleaningTool = 0;
  m_hTriggerTool = 0;
  m_hFormFactorReweightingTool = 0;
  m_hCrossSectionTool = 0;
  m_hChargeMisIDTool = 0;
  m_pMET = 0;
  m_pSystematics = 0;

  m_pMatrixMethodWWW = 0;
  m_pMatrixMethodWWWAlt  = 0;
  m_pMatrixMethodWWWAltFlipped  = 0;

  m_bSaveTruthInfo = false;
  m_bDoMxM = false;
  m_bApplyUnitarization = false;
  m_bDoZTagAndProbe = false;
  m_bDoFakeTagAndProbe = false;
  m_bDoFakeTagAndProbeInclusiveSign = false;
  m_bDoZPlusJetsTagAndProbe = false;
  m_bDoZPlusGammaTagAndProbe = false;



};
wwwAnalysis :: Analysis :: ~Analysis()
{
  std::cout << "analysis destructor" << std::endl;
}
EL::StatusCode wwwAnalysis :: Analysis :: setupJob (EL::Job& job)
{
  std::cout << "setupJob" << std::endl;
  // create an output stream (for the grid)
  for(unsigned int i = 0; i < m_vEventSelectorBaseNames.size(); i++){
    //if(!m_vSave[i])
     // continue;
    std::cout << m_vEventSelectorBaseNames[i]<< std::endl;
    EL::OutputStream out ( (m_vEventSelectorBaseNames[i]+"_outFile").Data() );
    job.outputAdd( out );
    if(m_bSaveTruthInfo){
	    EL::OutputStream truthout ( (m_vEventSelectorBaseNames[i]+"_truthOutFile").Data() );
	    job.outputAdd( truthout );
    }
  }
  
  job.useD3PDReader ();

  
  return EL::StatusCode::SUCCESS;
};



EL::StatusCode wwwAnalysis :: Analysis :: changeInput (bool firstFile)
{
  // do everything you need to do when we change
  // to a new input file, e.g. reset branch addresses
  return EL::StatusCode::SUCCESS;
};
const Root::TAccept &wwwAnalysis :: Analysis :: fillCutFlow(TH1 *hist, const Root::TAccept &accept, double weight)
{
  //Fill cutflow histogram
  for(unsigned int i = 0; i < accept.getNCuts(); i++)
    {
      if(accept.getCutResult(i))
	hist->Fill(accept.getCutName(i).Data(), weight);
      else break;
    }
  return accept;
}
void wwwAnalysis :: Analysis :: printPassedEvents(const Root::TAccept &accept, std::string cutname,int eventnum,int runnum, int lbn)
{
  //Fill cutflow histogram
  for(unsigned int i = 0; i < accept.getNCuts(); i++)
    {
      //if(accept.getCutResultExcl(i))
      if(accept.getCutResult(i)){
        if(accept.getCutName(i).Data()==cutname) printf("Event#: %d\tRun#: %d\tlbn:%d\n",eventnum,runnum,lbn);
      }
      else
	break;
    }
}

void  wwwAnalysis :: Analysis :: resetAdditionnalInfo()
{
	AdditionnalInfo.dilep=false;
	AdditionnalInfo.quadlep=false;
	AdditionnalInfo.quad_lep1=-1;
	AdditionnalInfo.quad_lep2=-1;
	AdditionnalInfo.quad_lep3=-1;
	AdditionnalInfo.quad_lep4=-1;
	AdditionnalInfo.dilep_mll=-1;
	AdditionnalInfo.dilep_mT1=-1;
	AdditionnalInfo.dilep_mT2=-1;
	AdditionnalInfo.dilep_SumHPTO=-1;
	AdditionnalInfo.dilep_SumCosDphi=-1;
	AdditionnalInfo.quadlep_m12=-1;
	AdditionnalInfo.quadlep_m34=-1;
}

const Root::TAccept &wwwAnalysis :: Analysis :: fillCutFlow(std::map<TString,double> cutflow, const Root::TAccept &accept, double weight)
{
  //Fill cutflow histogram
  for(unsigned int i = 0; i < accept.getNCuts(); i++)
    {
      //if(accept.getCutResultExcl(i))
      if(accept.getCutResult(i))
        cutflow[accept.getCutName(i).Data()]+= weight;
      else
	break;
    }
  return accept;
}

std::map<TString,double> wwwAnalysis :: Analysis :: createCutFlow(const Root::TAccept &accept, bool PhysicsObject)
{

	std::map<TString, double> cutflow;
	int ncuts = accept.getNCuts()+(PhysicsObject ? 1: 2);
	cutflow["Raw"] = 0.;
	if(!PhysicsObject) cutflow["GRL"] = 0.;
	for(int i = 0;i < ncuts; i++)
		cutflow[accept.getCutName(i)] = 0.;

	return cutflow;
}

TH1 *wwwAnalysis :: Analysis :: createCutFlow(const Root::TAccept &accept, const char *name, bool PhysicsObject)
{
  TH1 *ret = new TH1F(name, name, accept.getNCuts()+(PhysicsObject ? 1 : 2), 0, accept.getNCuts()+(PhysicsObject ? 1 : 2));
  ret->GetXaxis()->SetBinLabel(1, "Raw");
  if(!PhysicsObject) {
    ret->GetXaxis()->SetBinLabel(2, "GRL");
  }
  for(unsigned int i = 0; i < accept.getNCuts(); i++)
    ret->GetXaxis()->SetBinLabel(i+(PhysicsObject ? 2 : 3), accept.getCutName(i));
  ret->Sumw2();
  return ret;
}
void wwwAnalysis :: Analysis :: fillCutFlows(int index, const Root::TAccept &pass, double mc, double sf, double pu, double btag, double trig, double xsec,double charge,double mxm,double formfactor)
{
	double weight = 1.0;
	fillCutFlow(m_vCutFlow[index], pass, weight *= 1);
	fillCutFlow(m_vCutFlowEvents[index], pass, weight *= mc);
	fillCutFlow(m_vCutFlowEventsTrig[index], pass, weight *= trig);
	fillCutFlow(m_vCutFlowEventsTrigPu[index], pass, weight *= pu);
	fillCutFlow(m_vCutFlowEventsTrigPuLep[index], pass, weight *= sf);
	fillCutFlow(m_vCutFlowEventsTrigPuLepBTag[index], pass, weight *= btag);
	fillCutFlow(m_vCutFlowEventsTrigPuLepBTagXSec[index], pass, weight *= xsec );//sf);//sf);
	fillCutFlow(m_vCutFlowEventsTrigPuLepBTagXSecCharge[index], pass, weight *= charge );//sf);//sf);
	fillCutFlow(m_vCutFlowEventsTrigPuLepBTagXSecChargeMxM[index], pass, weight *= mxm );//sf);//sf);
	fillCutFlow(m_vCutFlowEventsTrigPuLepBTagXSecChargeMxMFormFactor[index], pass, weight *= formfactor );//sf);//sf);
	//kept for backwards compatibility
	fillCutFlow(m_vCutFlowEventsLepLepPuBTagTrigXSec[index], pass, weight );
}
void wwwAnalysis :: Analysis :: fillCutFlows(const char *bin, double weight,std::string variation)
{
  for(unsigned int i = 0; i < m_vCutFlow.size(); i++){
        if (((string)m_vEventSelectorNames[i]).find(variation)==string::npos) continue;
  	m_vCutFlow[i]->Fill(bin, 1.);
  }
  for(unsigned int i = 0; i < m_vCutFlowEvents.size(); i++){
        if (((string)m_vEventSelectorNames[i]).find(variation)==string::npos) continue;
  	m_vCutFlowEvents[i]->Fill(bin, weight);
  }
}
void wwwAnalysis :: Analysis :: addObjectSelector(const TString & type, Root::TSelectorToolBase *tool , const TString & variation){
        std::cout << "Add Object Selector of type '" << type << "' and variation '"<<variation << "'"<<std::endl;
	if (type=="Electron") m_hElectronSelectorTools[variation] = (TElectronSelectorTool *)tool;
	else if (type=="ElectronLoose" ) m_hElectronLooseSelectorTools[variation] = (TElectronSelectorTool *)tool;
	else if (type=="Muon") m_hMuonSelectorTools[variation] = (TMuonSelectorTool *)tool;
	else if (type=="MuonLoose" ) m_hMuonLooseSelectorTools[variation] = (TMuonSelectorTool *)tool;
	else if (type=="Tau") m_hTauSelectorTools[variation] = (TTauSelectorTool *)tool;
	else if (type=="Jet") m_hJetSelectorTools[variation] = (TJetSelectorTool *)tool;
	else if (type=="FakeElectron") m_hFakeElectronSelectorTools[variation] = (TElectronSelectorTool *)tool;
	else if (type=="FakeMuon") m_hFakeMuonSelectorTools[variation] = (TMuonSelectorTool *)tool;
	else if (type=="TauElectron") m_hTauElectronSelectorTools[variation] = (TElectronSelectorTool *)tool;
	else if (type=="TauMuon") m_hTauMuonSelectorTools[variation] = (TMuonSelectorTool *)tool;
	else if (type=="JetLoose") m_hJetLooseSelectorTools[variation] = (TJetSelectorTool *)tool;
	else if (type=="ElectronNoQuality") m_hElectronNoQualitySelectorTools[variation] = (TElectronSelectorTool *)tool;
	else if (type=="MuonNoQuality") m_hMuonNoQualitySelectorTools[variation] = (TMuonSelectorTool *)tool;
	else{
		std::cout << "WARNING in addObjectSelector couldn't specify type '"<< type<<"' and variation '"<<variation<<"'"<<std::endl;
	}
}
void wwwAnalysis :: Analysis :: addJetSelector(const TString & type, TJetSelectorTool *tool , const TString & variation){
        std::cout << "Add Object Selector of type '" << type << "' and variation '"<<variation << "'"<<std::endl;
	if (type=="Jet") m_hJetSelectorTools[variation] = tool;
	else if (type=="JetLoose") m_hJetLooseSelectorTools[variation] = tool;
	else{
		std::cout << "WARNING in addObjectSelector couldn't specify type '"<< type<<"' and variation '"<<variation<<"'"<<std::endl;
	}
}
void wwwAnalysis :: Analysis :: addTauSelector(const TString & type, TTauSelectorTool *tool , const TString & variation){
        std::cout << "Add Object Selector of type '" << type << "' and variation '"<<variation << "'"<<std::endl;
	if (type=="Tau") m_hTauSelectorTools[variation] = tool;
	else{
		std::cout << "WARNING in addObjectSelector couldn't specify type '"<< type<<"' and variation '"<<variation<<"'"<<std::endl;
	}
}
void wwwAnalysis :: Analysis :: addMuonSelector(const TString & type, TMuonSelectorTool *tool , const TString & variation){
        std::cout << "Add Object Selector of type '" << type << "' and variation '"<<variation << "'"<<std::endl;
	if (type=="Muon") m_hMuonSelectorTools[variation] = tool;
	else if (type=="Loose") m_hMuonLooseSelectorTools[variation] = tool;
	else if (type=="MuonNoQuality") m_hMuonNoQualitySelectorTools[variation] = tool;
	else if (type=="FakeMuon") m_hFakeMuonSelectorTools[variation] = tool;
	else if (type=="TauMuon") m_hTauMuonSelectorTools[variation] = tool;
	else{
		std::cout << "WARNING in addObjectSelector couldn't specify type '"<< type<<"' and variation '"<<variation<<"'"<<std::endl;
	}
}
void wwwAnalysis :: Analysis :: addElectronSelector(const TString & type, TElectronSelectorTool *tool , const TString & variation){

        std::cout << "Add Object Selector of type '" << type << "' and variation '"<<variation << "'"<<std::endl;
	if (type=="Electron") m_hElectronSelectorTools[variation] = tool;
	else if (type=="Loose") m_hElectronLooseSelectorTools[variation] = tool;
	else if (type=="FakeElectron") m_hFakeElectronSelectorTools[variation] = tool;
	else if (type=="ElectronNoQuality") m_hElectronNoQualitySelectorTools[variation] = tool;
	else if (type=="TauElectron") m_hTauElectronSelectorTools[variation] = tool;
	else{
		std::cout << "WARNING in addObjectSelector couldn't specify type '"<< type<<"' and variation '"<<variation<<"'"<<std::endl;
	}
}
void wwwAnalysis :: Analysis :: addEventSelector(const TString &name, TEventSelectorTool *tool, bool save,const TString &variation)
{
	int i = m_vEventSelectorNames.size();
	m_hEventSelectorTools[i] = tool;
	TString fullname = name;
	if (variation!="") fullname =fullname + "_"+variation;

	m_mEventSelectorIndex[variation][name] = i;

	m_vEventSelectorNames.push_back(fullname);
	bool foundName = false;
	for (unsigned int j=0;j<m_vEventSelectorBaseNames.size();j++){
		if (m_vEventSelectorBaseNames[j]==name){
			foundName = true;
			break;
		}
	}

	if(!foundName) m_vEventSelectorBaseNames.push_back(name);

	m_vSave.push_back(save);
}

EL::StatusCode wwwAnalysis :: Analysis :: initialize ()
{
  std::cout << "initialize" << std::endl;
//Same here, need the absolute path and the constructor of this class is at least weird...
  if(!m_hGoodRunsListReader)
    {
      m_hGoodRunsListReader = new Root::TGoodRunsListReader();
      m_hGoodRunsListReader->SetXMLFile((std::string(getenv("ROOTCOREDIR"))+"/../wwwAnalysis/GRL/data12_8TeV.periodAllYear_DetStatus-v61-pro14-02_DQDefects-00-01-00_PHYS_StandardGRL_All_Good.xml"));	
      m_hGoodRunsListReader->Interpret();
      m_oGoodRunsList = m_hGoodRunsListReader->GetMergedGoodRunsList();
    }

  if(!m_hFormFactorReweightingTool){
        std::cout << "Setup FormFactorReweightingTool " << std::endl;
	if(m_bApplyUnitarization) std::cout << "Configured for unitarization application" << std::endl;
	else std::cout << "NOT  configured for unitarization application" << std::endl;
  	m_hFormFactorReweightingTool = new FFReweight((std::string(getenv("ROOTCOREDIR"))+"/data/FormFactorReweightingTool/"));

  }
  
  
  std::string sampleName = wk()->metaData()->getString("sample_name");
  std::cout << "Sample Name: " << sampleName << std::endl;
  m_eShoweringGenerator = wwwAnalysis::Pythia6;
  if(sampleName.find("Pythia8") != std::string::npos) m_eShoweringGenerator = wwwAnalysis::Pythia8;
  else if(sampleName.find("Pythia") != std::string::npos) m_eShoweringGenerator = wwwAnalysis::Pythia6;
  else if(sampleName.find("Jimmy") != std::string::npos) m_eShoweringGenerator = wwwAnalysis::HerwigJimmy;
  else if(sampleName.find("Sherpa") != std::string::npos) m_eShoweringGenerator = wwwAnalysis::Sherpa;
  else if(sampleName.find("Herwigpp") != std::string::npos) m_eShoweringGenerator = wwwAnalysis::Herwigpp;

  // do everything you need to do to set up initially
  // on the worker node, e.g. create histograms and
  // output trees.
  
  // *** Output tree init here *********************************
  // book the tree:
	
  for(mapEventSelectorIndexOuter_t::iterator variation_it = m_mEventSelectorIndex.begin();variation_it != m_mEventSelectorIndex.end(); variation_it++){
    mapEventSelectorIndexInner_t &variation_map = variation_it->second;
    for(mapEventSelectorIndexInner_t::iterator index_it = variation_map.begin();index_it != variation_map.end(); index_it++){
        unsigned int i = index_it->second;
	TString selectorName = index_it->first;
	TString variationName = variation_it->first;

	TString treeName = "physics";
	if (variationName!="Central") //leave alone for backwards compatibility if using central value
		treeName = treeName+"_"+variationName;
	std::cout << "treeName: " << treeName<< std::endl;
	std::cout << "variationName: " << variationName<< std::endl;
	std::cout << "selectorName: " << selectorName<< std::endl;

  	if(!m_vSave[i])
  		continue;
  	TFile *outfile = wk()->getOutputFile( (selectorName+"_outFile").Data() );
        Output *out = new Output();
  	out->initialize(treeName.Data());
  	out->tree()->SetDirectory(outfile); 
        m_pOut[m_vEventSelectorNames[i]] = out;

	if(m_bSaveTruthInfo){
		TFile *truthoutfile = wk()->getOutputFile( (selectorName+"_truthOutFile").Data() );
		TruthOutput *truthout = new TruthOutput();
		truthout->initialize(treeName.Data());
		truthout->tree()->SetDirectory(truthoutfile); 
		m_pTruthOut[m_vEventSelectorNames[i]] = truthout;
	}
    }
  }
  
		     
  
  // *** HISTOS added to job here ****************************
  // *** SELECTOR TOOLS check here ***************************
  //std::cout << m_hElectronSelectorTools.size() << "\t"<< m_hMuonSelectorTools.size() << "\t"<< m_hTauSelectorTools.size() << "\t"<< m_hJetSelectorTools.size() << "\t"<< m_hTauElectronSelectorTools.size() << "\t"<< m_hTauMuonSelectorTools.size() << "\t"<< m_hJetLooseSelectorTools.size() << "\t"<<std::endl;
  if(!m_hGoodRunsListReader)  throw std::string("EL::StatusCode Analysis::initialize \t No GRL Reader configured!");
  if(!m_hFormFactorReweightingTool)  throw std::string("EL::StatusCode Analysis::initialize \t No Form Factor Reweighting Tool configured!");
  if(!m_hPileupTool) throw std::string("EL::StatusCode Analysis::initialize \t No Pileup Tool configured!");
  if(!m_hPileupToolUp) throw std::string("EL::StatusCode Analysis::initialize \t No Up Pileup Tool configured!");
  if(!m_hPileupToolDown) throw std::string("EL::StatusCode Analysis::initialize \t No Down Pileup Tool configured!");
  //if(!m_hPileupWriteTool) throw std::string("EL::StatusCode Analysis::initialize \t No Pileup write Tool configured!");  //don't care if this isn't configured because usually won't be used
  if(!m_hJetCleaningTool) throw std::string("EL::StatusCode Analysis::initialize \t No Jet Cleaning Tool configured!");
  if(!m_hTriggerTool) throw std::string("EL::StatusCode Analysis::initialize \t No Trigger Tool configured!");
  if(m_hElectronSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not ElectronSelectorTool configured!");
  if(m_hElectronLooseSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not ElectronLooseSelectorTool configured!");
  if(m_hMuonLooseSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not MuonLooseSelectorTool configured!");
  if(m_hElectronNoQualitySelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not ElectronSelectorTool configured!");
  if(m_hElectronNoQualitySelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not ElectronSelectorTool configured!");
  if(m_hMuonSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not MuonSelectorTool configured!");
  if(m_hMuonNoQualitySelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not MuonSelectorTool configured!");
  if(m_hTauSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not TauSelectorTool configured!");
  if(m_hJetSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not JetSelectorTool configured!");
  if(m_hTauElectronSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not ElectronSelectorTool configured!");
  if(m_hTauMuonSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not MuonSelectorTool configured!");
  if(m_hJetLooseSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not JetSelectorTool configured!");

  if(m_hEventSelectorTools.size() == 0) throw std::string("EL::StatusCode Analysis::initialize \t Not EventSelectorTool configured!");
  //if(!m_pSystematics) throw std::string("EL::StatusCode Analysis::initialize \t No Systematics configured!");

  // *** SELECTOR TOOLS init here ****************************
  //m_hPileupTool->Initialize();
  m_hPileupTool->EnableDebugging(false);
  m_hPileupToolUp->EnableDebugging(false);
  m_hPileupToolDown->EnableDebugging(false);
  m_hPileupTool->initialize();  
  m_hPileupToolUp->initialize();  
  m_hPileupToolDown->initialize();  
  if (m_hPileupWriteTool) m_hPileupWriteTool->initialize();
  m_hJetCleaningTool->initialize();
  while(m_pSystematics->next()){
	  m_hElectronSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hElectronLooseSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hMuonLooseSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hElectronNoQualitySelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hMuonSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hMuonNoQualitySelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hTauSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hJetSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hTauElectronSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hTauMuonSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	  m_hJetLooseSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
  }

  //if an event selector uses the z tag and probe
  //switch on computation of z tag and probe for each event
  m_bDoZTagAndProbe = false;
  m_bDoFakeTagAndProbe = false;
  m_bDoFakeTagAndProbeInclusiveSign = false;
  m_bDoZPlusJetsTagAndProbe = false;
  m_bDoZPlusGammaTagAndProbe = false;
  
  for(unsigned int i = 0; i < m_hEventSelectorTools.size(); i++){
  	m_hEventSelectorTools[i]->initialize();
	if(m_hEventSelectorTools[i]->doZTagAndProbe()) m_bDoZTagAndProbe = true;
	if(m_hEventSelectorTools[i]->doFakeTagAndProbe()) m_bDoFakeTagAndProbe= true;
	if(m_hEventSelectorTools[i]->doFakeTagAndProbeInclusiveSign()) m_bDoFakeTagAndProbeInclusiveSign= true;
	if(m_hEventSelectorTools[i]->doZPlusJetsTagAndProbe()) m_bDoZPlusJetsTagAndProbe= true;
	if(m_hEventSelectorTools[i]->doZPlusGammaTagAndProbe()) m_bDoZPlusGammaTagAndProbe= true;
  }

  if(m_hFakeElectronSelectorTools.size()!=0 && m_hFakeMuonSelectorTools.size()!=0) {
    while(m_pSystematics->next()){
	    m_hFakeElectronSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
	    m_hFakeMuonSelectorTools[m_pSystematics->getCurrentSystematic()]->initialize();
    }
  }
  m_hCrossSectionTool = new CrossSectionTool(std::string(getenv("ROOTCOREDIR"))+"/data/CrossSectionTool/WWWSamples.csv");
  if(!m_hCrossSectionTool->isInitialized()) throw std::string("CrossSectionTool not initialized");
  m_hCrossSectionTool->print();
  
  
  if(m_sElectronRealRate=="" || m_sMuonRealRate=="" || m_sMuonFakeRate=="" || m_sElectronFakeRate==""){
	m_sElectronRealRate = "Loose_InvertedID_InvertedEtIso_InvertedPtIso";
 	m_sMuonRealRate = "Loose_InvertedID_InvertedEtIso_InvertedPtIso";
	//m_sElectronFakeRate = "OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2LooseLep_BJetGt0";
	m_sElectronFakeRate = "OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2Loose_SubtractPC_BJetGt0";
	//m_sElectronFakeRate = "OFSS_InvLoosepp_InvEtIso_InvPtIso_METGt10_PtGt40_LooseZVeto_BJetGt0";
	//m_sElectronFakeRate = "OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2LooseLep_BJetInc";
	//m_sElectronFakeRate = "OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_BJetInc";
	//m_sElectronFakeRate =  "ZPlusGamma_Electron_InvMediumpp_InvEtIso_InvPtIso";
	m_sMuonFakeRate = "SFSS_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2LooseLep_BJetGt0";
	
  }
  m_pMatrixMethodWWW  = new GeneralisedMatrixMethodWWW::MatrixMethodWWW::MatrixMethodWWW(std::string(getenv("ROOTCOREDIR"))+"/data/GeneralisedMatrixMethod/rates.root",
  			"Real/Electron/"+m_sElectronRealRate,
			"Real/Muon/"+m_sMuonRealRate,
			"Fake/Electron/"+m_sElectronFakeRate,
			"Fake/Muon/"+m_sMuonFakeRate);
			/*
  			"Real/Electron/Loose_InvertedID_InvertedEtIso_InvertedPtIso",
			"Real/Muon/Loose_InvertedID_InvertedEtIso_InvertedPtIso",
			"Fake/Electron/OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_BJetInc",
			"Fake/Muon/SFSS_InvEtIso_InvPtIso_METGt10_PtGt40_LooseZVeto_BJetInclusive");
			*/
  m_pMatrixMethodWWWAlt  = new GeneralisedMatrixMethodWWW::MatrixMethodWWW::MatrixMethodWWW(std::string(getenv("ROOTCOREDIR"))+"/data/GeneralisedMatrixMethod/rates.root",
  			"Real/Electron/Loose_InvertedID_InvertedEtIso_InvertedPtIso",
			"Real/Muon/Loose_InvertedID_InvertedEtIso_InvertedPtIso",
			//"Fake/Electron/OFSS_InvLoosepp_InvEtIso_InvPtIso_METGt10_PtGt40_LooseZVeto_BJetInc",
			//"Fake/Electron/OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_BJetGt0",
			"Fake/Electron/OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2Loose_SubtractPC_BJetInc",
			//"Fake/Electron/OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2LooseLep_BJetGt0",
			"Fake/Muon/SFSS_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2LooseLep_BJetInc");

  m_pMatrixMethodWWWAltFlipped  = new GeneralisedMatrixMethodWWW::MatrixMethodWWW::MatrixMethodWWW(std::string(getenv("ROOTCOREDIR"))+"/data/GeneralisedMatrixMethod/rates.root",
  			"Real/Electron/Loose_InvertedID_InvertedEtIso_InvertedPtIso",
			"Real/Muon/Loose_InvertedID_InvertedEtIso_InvertedPtIso",
			//"Fake/Electron/OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2LooseLep_BJetGt0--OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2LooseLep_BJetInc--Flipped",
			"Fake/Electron/OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2Loose_SubtractPC_BJetGt0--OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2Loose_SubtractPC_BJetInc--Flipped",

			//"Fake/Electron/OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_BJetInc--OFSS_InvMediumpp_InvEtIso_InvPtIso_METGt10_PtGt40_BJetGt0--Flipped",
			//OFSS_InvLoosepp_InvEtIso_InvPtIso_METGt10_PtGt40_LooseZVeto_BJetGt0--OFSS_InvLoosepp_InvEtIso_InvPtIso_METGt10_PtGt40_LooseZVeto_BJetInc--Flipped",
			"Fake/Muon/SFSS_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2LooseLep_BJetGt0--SFSS_InvEtIso_InvPtIso_METGt10_PtGt40_Exactly2LooseLep_BJetInc--Flipped");

  if(!m_pMatrixMethodWWW ) throw std::string("EL::StatusCode Analysis::initialize \t Not GeneralisdMatrixMethodWWW::MatrixMethodWWW configured!");
  else std::cout << "Initialization of matrix method tool successful" << std::endl;
  if(!m_pMatrixMethodWWWAlt ) throw std::string("EL::StatusCode Analysis::initialize \t Not GeneralisdMatrixMethodWWW::MatrixMethodWWW configured!");
  else std::cout << "Initialization of matrix method tool successful" << std::endl;
  if(!m_pMatrixMethodWWWAltFlipped ) throw std::string("EL::StatusCode Analysis::initialize \t Not GeneralisdMatrixMethodWWW::MatrixMethodWWW configured!");
  else std::cout << "Initialization of matrix method tool successful" << std::endl;

  //m_hChargeMisIDTool = new WWW::ChargeMisIDTool(std::string(getenv("ROOTCOREDIR"))+"/data/ChargeMisIDTool/ChargeMisIDRates.root");
  bool useMCRates = true;
  m_hChargeMisIDTool = new WWW::ChargeMisIDTool(std::string(getenv("ROOTCOREDIR"))+"/data/ChargeMisIDTool/WWWRates_Dec22_Final.root",!useMCRates,
                                                std::string(getenv("ROOTCOREDIR"))+"/data/ChargeMisIDTool/EnergyCorrections.root");
  //m_hChargeMisIDTool = new WWW::ChargeMisIDTool(std::string(getenv("ROOTCOREDIR"))+"/data/ChargeMisIDTool/WWWRates_MC.root");
  //m_hChargeMisIDTool = new WWW::ChargeMisIDTool(std::string(getenv("ROOTCOREDIR"))+"/data/ChargeMisIDTool/ChargeMisIDRates_Alternate.root");
  if(!m_hChargeMisIDTool->isInitialized()) throw std::string("WWW::ChargeMisIDTool not initialized");

  m_sysMuonEff = wwwAnalysis::MuonEffSysOff;
  m_sysMuonMom = wwwAnalysis::MuonMomSysOff;
  m_sysElectronEff = wwwAnalysis::ElectronEffSysOff;
  m_sysElectronEnergyScale = wwwAnalysis::ElectronEnergyScaleSysOff;
  m_sysElectronEnergySmearing = wwwAnalysis::ElectronEnergySmearingSysOff;
  m_sysMETSoftTerms = wwwAnalysis::METSoftTermsSysOff;
  m_sysTrigSF = wwwAnalysis::TriggerSFSysOff;
  m_sysJES = wwwAnalysis::JESSysOff;
  m_sysJetPileup = wwwAnalysis::JetPileupSysOff;
  m_sysJVF = wwwAnalysis::JVFSysOff;
  m_sysJetTagSF = wwwAnalysis::JetTagSFSysOff;
  m_sysJetFlavor = wwwAnalysis::JetFlavorSysOff;
  m_sysJetResolution = wwwAnalysis::JetResolutionSysOff;
  m_sysChargeMisID = wwwAnalysis::ChargeMisIDSysOff;
  m_sysPileup = wwwAnalysis::PileupSysOff;
  m_sysMxM  = wwwAnalysis::MxMSysOff;

  m_bHasLooseNotTightElectrons = false;
  m_bHasLooseNotTightMuons  = false;
  m_bIsTriggerMatched = false;
  m_bIsFake = false;
  m_bElectronIsCentral = false;
  m_bDoChargeFlip = false;
  m_bMuonIsCentral     = false;
  m_bJetIsCentral      = false;
  m_bTriggerIsCentral  = false;
  m_bMETIsCentral      = false;
  m_bJetTagSFIsCentral = false;
  m_bMiscWeightIsCentral = false;
  m_bLepMETSFIsCentral = false;
  m_bUpdateElectrons = false;
  m_bUpdateMuons     = false;
  m_bUpdateJets      = false;
  m_bUpdateMET       = false;
  m_bUpdateMiscWeights = false;
  m_bUpdateJetTagSFWeights  = false;
  m_bUpdateTrigSFWeights = false;
  m_bUpdateLepMETSFWeights = false;

  m_iChargeFlipContainerIndex = -1;

  m_fMcWeight = 1.;
  m_fSFWeight = 1.;
  m_fPuWeight = 1.;
  m_fJetTagWeight60 = 1.;
  m_fJetTagWeight70 = 1.;
  m_fJetTagWeight80 = 1.;
  m_fJetTagWeight85 = 1.;
  m_fTrigWeight = 1.;
  m_fFormFactorWeight = 1.;
  m_fMxMWeight  = 1.;
  m_fXSecWeight = 1.;
  m_fChargeMisIDWeight = 1.;



  m_hChargeMisIDTool->setVerbosity(false);
  
  // *** Cut Flows init here *********************************
  
  while(m_pSystematics->next()){
  	  TString var = m_pSystematics->getCurrentSystematic();
	  TString tag = "";
	  if (var!="Central") tag = "_"+var;
	  m_pCutFlowElectrons[var] = createCutFlow(m_hElectronSelectorTools[var]->getTAccept(), "cutFlowElectrons"+tag);

	  m_pCutFlowElectronsLoose[var] = createCutFlow(m_hElectronLooseSelectorTools[var]->getTAccept(), "cutFlowElectronsLoose"+tag);
	  m_pCutFlowMuonsLoose[var] = createCutFlow(m_hMuonLooseSelectorTools[var]->getTAccept(), "cutFlowMuonsLoose"+tag);
	  m_pCutFlowMuons[var] = createCutFlow(m_hMuonSelectorTools[var]->getTAccept(), "cutFlowMuons"+tag);
	  m_pCutFlowMuonsNoQuality[var] = createCutFlow(m_hMuonNoQualitySelectorTools[var]->getTAccept(), "cutFlowMuonsNoQuality"+tag);
	  m_pCutFlowTaus[var] = createCutFlow(m_hTauSelectorTools[var]->getTAccept(), "cutFlowTaus"+tag);
	  m_pCutFlowJets[var] = createCutFlow(m_hJetSelectorTools[var]->getTAccept(), "cutFlowJets"+tag);
          if(m_hFakeElectronSelectorTools[var])m_pCutFlowElectronsFake[var] = createCutFlow(m_hFakeElectronSelectorTools[var]->getTAccept(), "CutFlowElectronsFake"+tag);
	  m_pCutFlowElectronsNoQuality[var] = createCutFlow(m_hElectronNoQualitySelectorTools[var]->getTAccept(), "cutFlowElectronsNoQuality"+tag);
          if(m_hFakeMuonSelectorTools[var])m_pCutFlowMuonsFake[var] = createCutFlow(m_hFakeMuonSelectorTools[var]->getTAccept(), "CutFlowMuonsFake"+tag);

  
          if(m_hFakeElectronSelectorTools[var])wk()->addOutput(m_pCutFlowElectronsFake[var]);
	  wk()->addOutput(m_pCutFlowElectronsNoQuality[var]);
	  wk()->addOutput(m_pCutFlowMuonsNoQuality[var]);
          if(m_hFakeMuonSelectorTools[var])wk()->addOutput(m_pCutFlowMuonsFake[var]);
	  
	  wk()->addOutput(m_pCutFlowElectrons[var]);
	  wk()->addOutput(m_pCutFlowElectronsLoose[var]);
	  wk()->addOutput(m_pCutFlowMuonsLoose[var]);
	  wk()->addOutput(m_pCutFlowMuons[var]);
	  wk()->addOutput(m_pCutFlowTaus[var]);
	  wk()->addOutput(m_pCutFlowJets[var]);
  }
  
  
  for(unsigned int i = 0; i < m_vEventSelectorNames.size(); i++)
    {
      TString &name = m_vEventSelectorNames[i];
      m_vCutFlow.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlow").Data(), false));
      m_vCutFlowEvents.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents").Data(), false));
      m_vCutFlowEventsTrig.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents_trig").Data(), false));
      m_vCutFlowEventsTrigPu.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents_trig_pu").Data(), false));
      m_vCutFlowEventsTrigPuLep.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents_trig_pu_lep").Data(), false));
      m_vCutFlowEventsTrigPuLepBTag.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents_trig_pu_lep_btag").Data(), false));
      m_vCutFlowEventsTrigPuLepBTagXSec.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents_trig_pu_lep_btag_xsec").Data(), false));
      m_vCutFlowEventsTrigPuLepBTagXSecCharge.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents_trig_pu_lep_btag_xsec_charge").Data(), false));
      m_vCutFlowEventsTrigPuLepBTagXSecChargeMxM.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents_trig_pu_lep_btag_xsec_charge_mxm").Data(), false));
      m_vCutFlowEventsTrigPuLepBTagXSecChargeMxMFormFactor.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents_trig_pu_lep_btag_xsec_charge_mxm_formfactor").Data(), false));

      //kept for bacwards compatibility
      m_vCutFlowEventsLepLepPuBTagTrigXSec.push_back(createCutFlow(m_hEventSelectorTools[i]->getTAccept(), (name+"_cutFlowEvents_leplep_pu_btag_trig_xsec").Data(), false));

      
      wk()->addOutput(m_vCutFlow[i]);
      wk()->addOutput(m_vCutFlowEvents[i]);
      wk()->addOutput(m_vCutFlowEventsTrig[i]);
      wk()->addOutput(m_vCutFlowEventsTrigPu[i]);
      wk()->addOutput(m_vCutFlowEventsTrigPuLep[i]);
      wk()->addOutput(m_vCutFlowEventsTrigPuLepBTag[i]);
      wk()->addOutput(m_vCutFlowEventsTrigPuLepBTagXSec[i]);
      wk()->addOutput(m_vCutFlowEventsTrigPuLepBTagXSecCharge[i]);
      wk()->addOutput(m_vCutFlowEventsTrigPuLepBTagXSecChargeMxM[i]);
      wk()->addOutput(m_vCutFlowEventsTrigPuLepBTagXSecChargeMxMFormFactor[i]);
      wk()->addOutput(m_vCutFlowEventsLepLepPuBTagTrigXSec[i]);


    }
  
  
  

  
  //Needed to add information from the original tree:
  m_pEvent = wk()->d3pdreader();

  std::cout << "init done" << std::endl;

  std::cout << "OPEN FILES:"<<std::endl;
  for (int i = 0;i<gROOT->GetListOfFiles()->GetEntries();i++)
  	std::cout << gROOT->GetListOfFiles()->At(i)->GetName() << std::endl;


  return EL::StatusCode::SUCCESS;
};

void wwwAnalysis::Analysis::tagObjects()
{

  //First clean the tagged container:
  m_pTaggedLeptons.clear(); 
	// Tag Leptons
  for(unsigned int i = 0; i < m_vMuons.size(); i++) m_pTaggedLeptons.push_back(&m_vMuons[i]);
  for(unsigned int i = 0; i < m_vElectrons.size(); i++) m_pTaggedLeptons.push_back(&m_vElectrons[i]);
	//Sort them by pT
  sortPt_p(m_pTaggedLeptons);


  m_pAllLeptons.clear(); 
	// Tag Leptons
  for(unsigned int i = 0; i < m_vMuonsAll.size(); i++) m_pAllLeptons.push_back(&m_vMuonsAll[i]);
  for(unsigned int i = 0; i < m_vElectronsAll.size(); i++) m_pAllLeptons.push_back(&m_vElectronsAll[i]);
	//Sort them by pT
  sortPt_p(m_pTaggedLeptons);

  m_pTaggedLeptonsInc.clear(); 
  for(unsigned int i = 0; i < m_vMuonsInc.size(); i++) m_pTaggedLeptonsInc.push_back(&m_vMuonsInc[i]);
  for(unsigned int i = 0; i < m_vElectronsInc.size(); i++) m_pTaggedLeptonsInc.push_back(&m_vElectronsInc[i]);
  sortPt_p(m_pTaggedLeptonsInc);
  m_bHasLooseNotTightElectrons  = false;
  m_bHasLooseNotTightMuons   	= false;

  //Evaluate loose and tight criteria for matrix method
  bool isElectron = true; 
  bool isTight = true; 
  m_vTaggedLeptonsMxM.clear();
  m_vTaggedLeptons_MMLepton.clear();
  m_vTaggedMuonsMxM.clear();
  m_vTaggedElectronsMxM.clear();
  m_pTaggedLooseNotTightLeptons.clear(); 
  m_pTaggedLooseLeptons.clear(); 

  //there should be different leptons in each one of these loops
  //Loose (not tight) Muons
  for(unsigned int i = 0; i < m_vMuonsLooseNotTight.size(); i++) {
	m_vTaggedLeptons_MMLepton.push_back( GeneralisedMatrixMethodWWW::MatrixMethodWWW::Lepton(m_vMuonsLooseNotTight[i].momentum().Pt()/1000., m_vMuonsLooseNotTight[i].momentum().Eta(), !isElectron, !isTight));
	m_vTaggedLeptonsMxM.push_back(m_vMuonsLooseNotTight[i]);
	m_pTaggedLooseNotTightLeptons.push_back(&m_vMuonsLooseNotTight[i]);
	m_pTaggedLooseLeptons.push_back(&m_vMuonsLooseNotTight[i]);
	m_vTaggedMuonsMxM.push_back(m_vMuonsLooseNotTight[i]);
	m_vTaggedElectronsMxM.push_back(Electron());//placeholder
	m_bHasLooseNotTightMuons = true;
  }

  //Tight (and loose) Muons
  for(unsigned int i = 0; i < m_vMuonsTight.size(); i++) {
	m_vTaggedLeptons_MMLepton.push_back( GeneralisedMatrixMethodWWW::MatrixMethodWWW::Lepton(m_vMuonsTight[i].momentum().Pt()/1000., m_vMuonsTight[i].momentum().Eta(), !isElectron, isTight));
	m_vTaggedLeptonsMxM.push_back(m_vMuonsTight[i]);
	m_pTaggedLooseLeptons.push_back(&m_vMuonsTight[i]);  //Inclusive
	m_vTaggedMuonsMxM.push_back(m_vMuonsTight[i]);
	m_vTaggedElectronsMxM.push_back(Electron());//placeholder

  }

  //Loose (not tight) Electrons
  //Use calo Eta since that is the variable used for the eta cut in object selection
  for(unsigned int i = 0; i < m_vElectronsLooseNotTight.size(); i++) {
	m_vTaggedLeptons_MMLepton.push_back( GeneralisedMatrixMethodWWW::MatrixMethodWWW::Lepton(m_vElectronsLooseNotTight[i].momentum().Pt()/1000., m_vElectronsLooseNotTight[i].d3pd().cl_eta(), isElectron, !isTight));
	m_vTaggedLeptonsMxM.push_back(m_vElectronsLooseNotTight[i]);
	m_vTaggedMuonsMxM.push_back(Muon());//placeholder
	m_pTaggedLooseNotTightLeptons.push_back(&m_vElectronsLooseNotTight[i]);
	m_pTaggedLooseLeptons.push_back(&m_vElectronsLooseNotTight[i]);
	m_vTaggedElectronsMxM.push_back(m_vElectronsLooseNotTight[i]);
	m_bHasLooseNotTightElectrons = true;
  }

  //Tight (and loose) Electrons
  //Use calo Eta since that is the variable used for the eta cut in object selection
  for(unsigned int i = 0; i < m_vElectronsTight.size(); i++) {
	m_vTaggedLeptons_MMLepton.push_back( GeneralisedMatrixMethodWWW::MatrixMethodWWW::Lepton(m_vElectronsTight[i].momentum().Pt()/1000., m_vElectronsTight[i].d3pd().cl_eta(), isElectron, isTight));
	m_vTaggedLeptonsMxM.push_back(m_vElectronsTight[i]);
	m_vTaggedMuonsMxM.push_back(Muon());//placeholder
	m_pTaggedLooseLeptons.push_back(&m_vElectronsTight[i]); //Inclusive
	m_vTaggedElectronsMxM.push_back(m_vElectronsTight[i]);
  }

  sortPt_p(m_pTaggedLooseNotTightLeptons);
  sortPt_p(m_pTaggedLooseLeptons);

}
EL::StatusCode wwwAnalysis :: Analysis :: execute (){
	
	m_bElectronIsCentral = false;
	m_bMuonIsCentral     = false;
	m_bJetIsCentral      = false;
	m_bTriggerIsCentral  = false;
	m_bMETIsCentral      = false;
	m_bJetTagSFIsCentral = false;
	m_bMiscWeightIsCentral = false;
	m_bLepMETSFIsCentral = false;

	while(m_pSystematics->next()){
		if(buildEvent(m_pSystematics->getCurrentSystematic()) == EL::StatusCode::FAILURE) continue;
		if(m_bDoMxM){
		    for(unsigned int i = 0; i< m_vMxMRawResults.size(); i++){

		  	selectObjectsMxM(i, m_pSystematics->getCurrentSystematic());
		   	selectEvent(m_pSystematics->getCurrentSystematic());
		    }
		}
		else selectEvent(m_pSystematics->getCurrentSystematic());
	}
  return EL::StatusCode::SUCCESS;
}

int wwwAnalysis :: Analysis :: buildEvent (std::string sysVariation)
{
  if(sysVariation != m_pSystematics->getCurrentSystematic()){
  	std::cout << "wwwAnalysis::Analysis::Execute(string) ERROR sysVariation does not match" << std::endl;
  	return EL::StatusCode::FAILURE;

  }
  /*
    if(!((m_pEvent->eventinfo.RunNumber()==204474 && m_pEvent->eventinfo.EventNumber()==131944906 && m_pEvent->eventinfo.lbn()==711) ))
    if(!((m_pEvent->eventinfo.RunNumber()==204026 && m_pEvent->eventinfo.EventNumber()==95078870 && m_pEvent->eventinfo.lbn()==506) ||
    (m_pEvent->eventinfo.RunNumber()==203258 && m_pEvent->eventinfo.EventNumber()==75318091 && m_pEvent->eventinfo.lbn()==512)||
    (m_pEvent->eventinfo.RunNumber()==203335 && m_pEvent->eventinfo.EventNumber()==31789820 && m_pEvent->eventinfo.lbn()==176)||
    (m_pEvent->eventinfo.RunNumber()==203524 && m_pEvent->eventinfo.EventNumber()==54814253 && m_pEvent->eventinfo.lbn()==314)||
    (m_pEvent->eventinfo.RunNumber()==205017 && m_pEvent->eventinfo.EventNumber()==87862859 && m_pEvent->eventinfo.lbn()==369)))
    {
  	return EL::StatusCode::FAILURE;
    }
  */

  m_sysMuonEff = m_pSystematics->getCurrentMuonEffSys();
  m_sysMuonMom = m_pSystematics->getCurrentMuonMomSys();
  m_sysElectronEff = m_pSystematics->getCurrentElectronEffSys();
  m_sysElectronEnergyScale = m_pSystematics->getCurrentElectronEnergyScaleSys();
  m_sysElectronEnergySmearing = m_pSystematics->getCurrentElectronEnergySmearingSys();
  m_sysMETSoftTerms = m_pSystematics->getCurrentMETSoftTermsSys();
  m_sysTrigSF = m_pSystematics->getCurrentTriggerSFSys();
  m_sysJES = m_pSystematics->getCurrentJESSys();
  m_sysJetPileup = m_pSystematics->getCurrentJetPileupSys();
  m_sysJVF = m_pSystematics->getCurrentJVFSys();
  m_sysJetTagSF = m_pSystematics->getCurrentJetTagSFSys();
  m_sysJetFlavor = m_pSystematics->getCurrentJetFlavorSys();
  m_sysJetResolution = m_pSystematics->getCurrentJetResolutionSys();
  m_sysChargeMisID = m_pSystematics->getCurrentChargeMisIDSys();
  m_sysPileup = m_pSystematics->getCurrentPileupSys();
  m_sysMxM = m_pSystematics->getCurrentMxMSys();

  //record previous status
  bool electronWasCentral = m_bElectronIsCentral;
  bool muonWasCentral     = m_bMuonIsCentral;
  bool jetWasCentral      = m_bJetIsCentral;
  bool triggerWasCentral  = m_bTriggerIsCentral;
  bool metWasCentral      = m_bMETIsCentral;
  bool jetTagSFWasCentral = m_bJetTagSFIsCentral;
  bool miscWeightWasCentral = m_bMiscWeightIsCentral;
  bool lepMETSFWasCentral = m_bLepMETSFIsCentral;

  //update status
  m_bElectronIsCentral = (m_sysChargeMisID == wwwAnalysis::ChargeMisIDSysOff)
  		      && (m_sysElectronEnergyScale == wwwAnalysis::ElectronEnergyScaleSysOff)
                      && (m_sysElectronEnergySmearing == wwwAnalysis::ElectronEnergySmearingSysOff);
  m_bMuonIsCentral = (m_sysMuonMom == wwwAnalysis::MuonMomSysOff);
  m_bJetIsCentral = (m_sysJES == wwwAnalysis::JESSysOff)
  		 && (m_sysJetPileup == wwwAnalysis::JetPileupSysOff)
  		 && (m_sysJVF == wwwAnalysis::JVFSysOff)
  		 && (m_sysJetFlavor == wwwAnalysis::JetFlavorSysOff)
  		 && (m_sysJetResolution == wwwAnalysis::JetResolutionSysOff);
  m_bTriggerIsCentral = m_bElectronIsCentral && m_bMuonIsCentral 
  	         && (m_sysTrigSF == wwwAnalysis::TriggerSFSysOff);
  m_bMETIsCentral = m_bElectronIsCentral && m_bMuonIsCentral && m_bJetIsCentral 
  		&& (m_sysMETSoftTerms == wwwAnalysis::METSoftTermsSysOff);
  m_bJetTagSFIsCentral = m_bJetIsCentral 
  		      && (m_sysJVF == wwwAnalysis::JVFSysOff)
  		      && (m_sysJetTagSF == wwwAnalysis::JetTagSFSysOff);
  m_bMiscWeightIsCentral = (m_sysPileup == wwwAnalysis::PileupSysOff);
  m_bLepMETSFIsCentral = m_bElectronIsCentral && m_bMuonIsCentral && m_bMETIsCentral 
  		      && (m_sysMuonEff == wwwAnalysis::MuonEffSysOff) 
  		      && (m_sysElectronEff == wwwAnalysis::ElectronEffSysOff);


  //always update if object is not configured for central value
  //if the object is configured to be central, check if it already was, if not then reevaluate, otherwise leave alone
  m_bUpdateElectrons = !m_bElectronIsCentral || !electronWasCentral;
  m_bUpdateMuons     = !m_bMuonIsCentral     || !muonWasCentral;
  m_bUpdateJets      = !m_bJetIsCentral      || !jetWasCentral;
  m_bUpdateMET       = !m_bMETIsCentral      || !metWasCentral;
  m_bUpdateMiscWeights = !m_bMiscWeightIsCentral  || !miscWeightWasCentral;
  m_bUpdateJetTagSFWeights  = !m_bJetTagSFIsCentral  || !jetTagSFWasCentral;
  m_bUpdateTrigSFWeights = !m_bTriggerIsCentral  || !triggerWasCentral;
  m_bUpdateLepMETSFWeights = !m_bLepMETSFIsCentral || !lepMETSFWasCentral;

  /*
  std::cout << sysVariation 
  	    << " e " << (m_bUpdateElectrons ? "true" : "false" )
  	    << " mu " << (m_bUpdateMuons ? "true" : "false" )
  	    << " j " << (m_bUpdateJets ? "true" : "false" )
  	    << " met " << (m_bUpdateMET ? "true" : "false" )  << std::endl;
  std::cout << "\tw " << (m_bUpdateMiscWeights ? "true" : "false" ) 
	    << " trigsf " << (m_bUpdateTrigSFWeights ? "true" : "false") 
	    << " lepsf " << (m_bUpdateLepMETSFWeights ? "true" : "false") 
	    << " jetsf " << (m_bUpdateJetTagSFWeights ? "true" : "false")  << std::endl;
  */

  //clear data from previous event
  //object selections are always re-evaluated so only conditionally clear the container with all objects
  m_pTaggedLeptonsFake.clear(); 
  m_pTaggedLeptonsInc.clear(); 
  m_vElectronsFake.clear();
  m_vElectronsInc.clear();
  m_vElectronsLoose.clear();
  m_vElectronsLooseNotTight.clear();
  m_vElectronsTight.clear();
  m_pTPTags.clear();
  m_pTPTags2.clear();
  m_pTPProbes.clear();

  m_vMuonsFake.clear();
  m_pTaggedLeptons.clear();
  m_pTaggedLooseNotTightLeptons.clear();
  m_pTaggedLooseLeptons.clear();
  m_vTaggedLeptonsMxM.clear();

  m_vElectrons.clear();
  m_vTauElectrons.clear();
  m_vMuons.clear();
  m_vMuonsLoose.clear();
  m_vMuonsLooseNotTight.clear();
  m_vMuonsTight.clear();
  m_vMuonsInc.clear();
  m_vTauMuons.clear();
  m_vTaus.clear();
  m_vJets.clear();
  m_vJetsLoose.clear();

  this->resetAdditionnalInfo();

  if(m_bUpdateElectrons) m_vElectronsAll.clear();
  if(m_bUpdateMuons) m_vMuonsAll.clear();
  if(m_bUpdateJets) m_vJetsAll.clear();
  if(m_bUpdateMET){
	  if(m_pMET) {
	    delete m_pMET;
	    m_pMET = 0;
	  }
  }


  // process the next event in line, i.e. read in variables,
  // apply cuts, and then fill histograms and n-tuples

  //Check if this is an MC event
  m_bIsMC = m_pEvent->eventinfo.mc_channel_number.IsAvailable() && m_pEvent->eventinfo.mc_channel_number() > 0;

  m_bIsEGammaStream = !m_bIsMC && wk()->metaData()->getString("sample_name").find("physics_EGamma") != std::string::npos;

  m_fMcWeight = 1.0;
  if(m_bIsMC)
  {
    m_fMcWeight = m_pEvent->eventinfo.mc_event_weight();
  }



  //Calculate a random run number (MC ONLY)
  m_iRunNumber = m_pEvent->eventinfo.RunNumber();

  //Fix averageIntPerXing
  m_fMu = m_pEvent->eventinfo.averageIntPerXing();
  if(m_bIsMC && m_pEvent->eventinfo.lbn() == 1 && int(m_fMu+0.5) == 1)
    m_fMu = 0;


  if(m_bIsMC){
    m_hPileupTool->SetRandomSeed(314159+m_pEvent->eventinfo.mc_channel_number()*2718+m_pEvent->eventinfo.EventNumber());
    m_hPileupToolUp->SetRandomSeed(314159+m_pEvent->eventinfo.mc_channel_number()*2718+m_pEvent->eventinfo.EventNumber());
    m_hPileupToolDown->SetRandomSeed(314159+m_pEvent->eventinfo.mc_channel_number()*2718+m_pEvent->eventinfo.EventNumber());
    m_iRunNumber = m_hPileupTool->GetRandomRunNumber(m_iRunNumber);
  }
  //if write tool is set, fill
  if(m_bIsMC && m_hPileupWriteTool){
  	m_hPileupWriteTool->Fill(m_pEvent->eventinfo.RunNumber(),m_pEvent->eventinfo.mc_channel_number(),m_fMcWeight ,m_fMu);
	//tell tool to return and do nothing with event
  	return EL::StatusCode::FAILURE;
  }
  //Calculate PV tracks
  m_iNPV_3trks = 0;
  m_iNPV_2trks = 0;
  for(int i = 0; i < m_pEvent->vxp.n(); i++){
    if(m_pEvent->vxp[i].nTracks() >= 3)
      m_iNPV_3trks++;
    if(m_pEvent->vxp[i].nTracks() >= 2)
      m_iNPV_2trks++;
  }
  //Make Preselection of Physics PhysicsObjects
  int nMuons = m_pEvent->mu_staco.n();
  if (m_hMuonSelectorTools[sysVariation]->useThirdMuonChain()) nMuons = m_pEvent->mu.n();

  //Fill in raw PhysicsObjects
  m_pCutFlowElectrons[sysVariation]->Fill("Raw", m_pEvent->el.n()*m_fMcWeight );

  m_pCutFlowElectronsLoose[sysVariation]->Fill("Raw", m_pEvent->el.n()*m_fMcWeight );
  m_pCutFlowMuonsLoose[sysVariation]->Fill("Raw", nMuons*m_fMcWeight );
  m_pCutFlowMuons[sysVariation]->Fill("Raw", nMuons*m_fMcWeight );
  m_pCutFlowTaus[sysVariation]->Fill("Raw", m_pEvent->tau.n()*m_fMcWeight );
//  m_pCutFlowJets->Fill("Raw", m_pEvent->jet.n());
//WZ:
    m_pCutFlowJets[sysVariation]->Fill("Raw", m_pEvent->jet_AntiKt4LCTopo.n()*m_fMcWeight );

  //boolean for handling fake background
  m_bIsFake = false;


  
  if(m_bUpdateMuons)
     for(int i = 0; i < nMuons; i++) 
        m_vMuonsAll.push_back(Muon(*m_pEvent, i, m_hMuonSelectorTools[sysVariation]->useThirdMuonChain(),m_iNPV_3trks,false,m_sysMuonMom));

  for(int i = 0; i < nMuons; i++) { //Muons
    Muon mu = m_vMuonsAll[i];
    const Root::TAccept &pass = m_hMuonSelectorTools[sysVariation]->accept(mu, m_vMuons);
    const Root::TAccept &noqualitypass = m_hMuonNoQualitySelectorTools[sysVariation]->accept(mu, m_vMuonsInc);

    const Root::TAccept &loosepass = m_hMuonLooseSelectorTools[sysVariation]->accept(mu, m_vMuonsLoose);
    fillCutFlow(m_pCutFlowMuonsLoose[sysVariation], loosepass,m_fMcWeight );
    if(pass) m_vMuonsTight.push_back(mu);
    if(loosepass) m_vMuonsLoose.push_back(mu);
    if(loosepass && !pass) m_vMuonsLooseNotTight.push_back(mu);
    const Root::TAccept &tpass = m_hTauMuonSelectorTools[sysVariation]->accept(mu, m_vTauMuons);
    fillCutFlow(m_pCutFlowMuons[sysVariation], pass,m_fMcWeight );
    fillCutFlow(m_pCutFlowMuonsNoQuality[sysVariation], noqualitypass,m_fMcWeight );
    if(pass) m_vMuons.push_back(mu);
    if(noqualitypass) m_vMuonsInc.push_back(mu);
    if(tpass) m_vTauMuons.push_back(mu);

    if(m_hFakeMuonSelectorTools[sysVariation]){
	const Root::TAccept &fpass = m_hFakeMuonSelectorTools[sysVariation]->accept(mu, m_vMuons);


//	cout<<"Mu loop "<<int(m_pEvent->eventinfo.EventNumber())<<" n:"<<i<<"  passtightsel:"<<bool(pass)<<"  passfakesel:"<<bool(fpass)<<"  tight:"<<int(mu.tight())<<"  medium:"<<int(mu.medium())<<"   pt:"<<float(mu.momentum().Pt())<<"   eta:"<<float(mu.momentum().Eta())<<"   phi:"<<float(mu.momentum().Phi())<<"   d0:"<<fabs(mu.d3pd().trackd0pvunbiased()/mu.d3pd().tracksigd0pvunbiased())<<"   z0:"<<fabs(mu.d3pd().trackz0pvunbiased()*sin(mu.d3pd().tracktheta()))<<"  isolpt:"<<mu.d3pd().ptcone30()/float(mu.momentum().Pt())<<"  caloisol:"<<mu.Etcone20_corr()/float(mu.momentum().Pt())<<endl;

 	   if(fpass){
		m_vMuonsFake.push_back(mu);
		}	
	}
  }
  //We do a first pass at evaluating the electrons
  //anticipating that we may reweight the electrons according to their charge
  //mis-id.  See we also may apply energy corrections to the electrons,
  //we will evaluate this again later
  if(m_bUpdateElectrons)
    for(int i = 0; i < m_pEvent->el.n(); i++) {
      m_vElectronsAll.push_back(Electron (*m_pEvent, i, m_iNPV_2trks, m_iRunNumber,false,m_sysElectronEnergyScale ,m_sysElectronEnergySmearing));

    }

  for(int i = 0; i < m_pEvent->el.n(); i++) { //Electrons
    Electron el = m_vElectronsAll[i];
    const Root::TAccept &pass = m_hElectronSelectorTools[sysVariation]->accept(el, m_vElectrons, m_vMuons);
    const Root::TAccept &noqualitypass = m_hElectronNoQualitySelectorTools[sysVariation]->accept(el, m_vElectronsInc, m_vMuonsInc);
    const Root::TAccept &tpass = m_hTauElectronSelectorTools[sysVariation]->accept(el, m_vTauElectrons, m_vTauMuons);
    if(pass){
      m_vElectrons.push_back(el);
    }
    if (noqualitypass){
      m_vElectronsInc.push_back(el);
    }
    const Root::TAccept &loosepass = m_hElectronLooseSelectorTools[sysVariation]->accept(el, m_vElectronsLoose, m_vMuons);//Loose);
    if (pass) m_vElectronsTight.push_back(el);
    if (loosepass) m_vElectronsLoose.push_back(el);
    if (loosepass && !pass) m_vElectronsLooseNotTight.push_back(el);

    if(tpass)
      m_vTauElectrons.push_back(el);
     if(m_hFakeElectronSelectorTools[sysVariation]){
	    const Root::TAccept &fpass = m_hFakeElectronSelectorTools[sysVariation]->accept(el, m_vElectrons, m_vMuons);

//	cout<<"El loop "<<int(m_pEvent->eventinfo.EventNumber())<<" n:"<<i<<"  passtightsel:"<<bool(pass)<<"  passfakesel:"<<bool(fpass)<<"  tight:"<<int(el.tight())<<"  medium:"<<int(el.medium())<<"   pt:"<<float(el.momentum().Pt())<<"   eta:"<<float(el.momentum().Eta())<<"   phi:"<<float(el.momentum().Phi())<<"   d0:"<<fabs(el.d3pd().trackd0pvunbiased()/el.d3pd().tracksigd0pvunbiased())<<"   z0:"<<fabs(el.d3pd().trackz0pvunbiased()*sin(el.d3pd().tracktheta()))<<"  isolpt:"<<el.d3pd().ptcone30()/float(el.momentum().Pt())<<"  caloisol:"<<el.Etcone20_corr()/float(el.momentum().Pt())<<endl;

		if(fpass){
		  m_vElectronsFake.push_back(el);
		}
	}


  }

  //Sort PhysicsObject by Pt
  sortPt(m_vElectrons);
  sortPt(m_vElectronsInc);
  sortPt(m_vElectronsLoose);
  sortPt(m_vElectronsLooseNotTight);
  sortPt(m_vElectronsTight);

  sortPt(m_vElectronsAll);
  sortPt(m_vMuons);
  sortPt(m_vMuonsInc);
  sortPt(m_vMuonsLoose);
  sortPt(m_vMuonsLooseNotTight);
  sortPt(m_vMuonsTight);
  sortPt(m_vMuonsAll);

     if(m_hFakeElectronSelectorTools[sysVariation]&&m_hFakeMuonSelectorTools[sysVariation]){
//		cout<<"fake Size in analysis::"<<m_vMuonsFake.size()+m_vElectronsFake.size()<<endl;
	sortPt(m_vElectronsFake);
        sortPt(m_vMuonsFake);
	// Tag fake Leptons
	for(unsigned int i = 0; i < m_vMuonsFake.size(); i++)
 	   m_pTaggedLeptonsFake.push_back(&m_vMuonsFake[i]);
	for(unsigned int i = 0; i < m_vElectronsFake.size(); i++)
 	   m_pTaggedLeptonsFake.push_back(&m_vElectronsFake[i]);
	//Sort them by pT
	sortPt_p(m_pTaggedLeptonsFake);
	}


  //Calculate all the important objects
  tagObjects();
  int chargeFlipIndex = -1;
  double  chargeFlipEnergy = -999;
  //Perform ChargeMisID reweighting after leptons have been determined
  //std::cout << "nsfos " << m_hEventSelectorTools[0]->nSFOS() << "\t tagged lep " << m_pTaggedLeptons.size() << std::endl; //"\t n lep " << m_nleptons << std::endl;
  if(m_bIsMC && m_bUpdateElectrons && m_hEventSelectorTools[0]->configuredForNSFOS()==0 && m_pTaggedLeptons.size()==3) {// &&m_nleptons==3 ){
     m_hChargeMisIDTool->setSystematics(WWW::Central);
     if (m_sysChargeMisID == wwwAnalysis::ChargeMisIDUp) m_hChargeMisIDTool->setSystematics(WWW::SysUp);
     else if (m_sysChargeMisID == wwwAnalysis::ChargeMisIDDown) m_hChargeMisIDTool->setSystematics(WWW::SysDown);
     vector<TLorentzVector> leptons;
     vector<int> charges;
     vector<bool> areElectrons;
     for (int ilep=0;ilep<3;ilep++){
	leptons.push_back(m_pTaggedLeptons[ilep]->rawMomentum());
	charges.push_back(m_pTaggedLeptons[ilep]->charge());
	areElectrons.push_back(m_pTaggedLeptons[ilep]->type()==ELECTRON);
     }



     m_fChargeMisIDWeight = m_hChargeMisIDTool->getWeight(m_pEvent->eventinfo.mc_channel_number(),
     				m_pEvent->eventinfo.EventNumber(),m_pEvent->mc, leptons,charges,areElectrons);
     //std::cout << "weight " << m_fChargeMisIDWeight << std::endl;
     m_bDoChargeFlip = m_hChargeMisIDTool->doChargeFlip();
     //std::cout << "do charge flip: " << (m_bDoChargeFlip ? "true" : "false" )<< std::endl;
     //std::cout << "misid weight: " << m_fChargeMisIDWeight << std::endl; 
     if(m_bDoChargeFlip){
      	  chargeFlipIndex = m_hChargeMisIDTool->getChargeFlippedLeptonIndex(); 
	  //std::cout << "charge flip index = " << chargeFlipIndex << std::endl;
	  PhysicsObject *flippedLepton = NULL;
	  if(chargeFlipIndex==0) flippedLepton = m_pTaggedLeptons[0];
	  if(chargeFlipIndex==1) flippedLepton = m_pTaggedLeptons[1];
	  if(chargeFlipIndex==2) flippedLepton = m_pTaggedLeptons[2];

	  m_iChargeFlipContainerIndex = flippedLepton->index();
          chargeFlipEnergy = m_hChargeMisIDTool->getChargeFlippedLeptonEnergy(m_pEvent->eventinfo.EventNumber(),flippedLepton->rawMomentum());

     }

  }

  //Now start over and electrons taking into account possible charge flip and energy corrections
  if(m_bUpdateElectrons){
	  m_vElectrons.clear();
	  m_vElectronsInc.clear();
	  m_vElectronsLoose.clear();
	  m_vElectronsLooseNotTight.clear();
	  m_vElectronsTight.clear();
	  m_vTauElectrons.clear();
	  m_vElectronsAll.clear();
  	  for(int i = 0; i < m_pEvent->el.n(); i++) {
    	    double alternateEnergy = -999;
    	    if(m_bDoChargeFlip && m_iChargeFlipContainerIndex == i) alternateEnergy = chargeFlipEnergy;
	    m_vElectronsAll.push_back( Electron (*m_pEvent, i, m_iNPV_2trks, m_iRunNumber,false,m_sysElectronEnergyScale ,m_sysElectronEnergySmearing,alternateEnergy));
            if(m_bDoChargeFlip && m_iChargeFlipContainerIndex == i) m_vElectronsAll[i].flipCharge();
	  }
  }
  for(int i = 0; i < m_pEvent->el.n(); i++) { //Electrons
    //if alternateEnergy is < 0 it isn't used and the cluster energy is used instead
    //alternateEnergy isn't defined currently
    //I need to figure out a good way of implementing energy corrections
    //to the charge flipped electrons
    //I could calculate it above and then pass it along
    //double alternateEnergy = -999;
    //if(m_bDoChargeFlip && m_iChargeFlipContainerIndex == i) alternateEnergy = chargeFlipEnergy;
    Electron el = m_vElectronsAll[i];
    //if(m_bDoChargeFlip && m_iChargeFlipContainerIndex == i) el.flipCharge();
    const Root::TAccept &pass = m_hElectronSelectorTools[sysVariation]->accept(el, m_vElectrons, m_vMuons);
    const Root::TAccept &noqualitypass = m_hElectronNoQualitySelectorTools[sysVariation]->accept(el, m_vElectronsInc, m_vMuonsInc);
    const Root::TAccept &tpass = m_hTauElectronSelectorTools[sysVariation]->accept(el, m_vTauElectrons, m_vTauMuons);
    fillCutFlow(m_pCutFlowElectrons[sysVariation], pass,m_fMcWeight );
    fillCutFlow(m_pCutFlowElectronsNoQuality[sysVariation], noqualitypass,m_fMcWeight );
    if(pass) m_vElectrons.push_back(el);
    if (noqualitypass) m_vElectronsInc.push_back(el);
    if(tpass) m_vTauElectrons.push_back(el);
    const Root::TAccept &loosepass = m_hElectronLooseSelectorTools[sysVariation]->accept(el, m_vElectronsLoose, m_vMuons);//Loose);
    fillCutFlow(m_pCutFlowElectronsLoose[sysVariation], loosepass,m_fMcWeight );
    if(pass) m_vElectronsTight.push_back(el);
    if (loosepass) m_vElectronsLoose.push_back(el);
    if (loosepass && !pass) m_vElectronsLooseNotTight.push_back(el);
  }



  for(int i = 0; i < m_pEvent->tau.n(); i++) { //Taus
    Tau tau(m_pEvent->eventinfo, m_pEvent->tau[i]);
    const Root::TAccept &pass = m_hTauSelectorTools[sysVariation]->accept(tau, m_vTauElectrons, m_vTauMuons, m_vTaus);
    fillCutFlow(m_pCutFlowTaus[sysVariation],pass,m_fMcWeight );
    if(pass)
      m_vTaus.push_back(tau);
  }

  if(m_bUpdateJets)
    for(int i = 0; i < m_pEvent->jet_AntiKt4LCTopo.n(); i++) {
      m_vJetsAll.push_back(Jet(m_pEvent->eventinfo, m_pEvent->jet_AntiKt4LCTopo[i], m_iNPV_2trks, m_fMu, m_eShoweringGenerator,m_sysJES , m_sysJetPileup, m_sysJetFlavor,m_sysJetResolution,i,true));
  }

    sortPt(m_vJetsAll);
  //for (int i = 0;i<m_vJetsAll.size();i++) std::cout << m_vJetsAll[i].index() << "\t" << m_vJetsAll[i].momentum().Pt() << "\t" << m_vJetsAll[i].rawMomentum().Pt() << std::endl;

  for(int i = 0; i < m_pEvent->jet_AntiKt4LCTopo.n(); i++) { //Jets

	
    Jet jet = m_vJetsAll[i];

    //test for clean jets
   //implement jet cleaning at TEventSelector stage using D3PD variable
   bool cleanjet=true;

    const Root::TAccept &pass = m_hJetSelectorTools[sysVariation]->accept(jet, m_vElectrons, m_vMuons, m_vTaus, m_vJets,cleanjet,m_sysJVF);

    const Root::TAccept &lpass = m_hJetLooseSelectorTools[sysVariation]->accept(jet, m_vElectrons, m_vMuons, m_vTaus, m_vJetsLoose,cleanjet,m_sysJVF);
    fillCutFlow(m_pCutFlowJets[sysVariation], pass,m_fMcWeight );
    if(pass)
      m_vJets.push_back(jet);
    if(lpass)
      m_vJetsLoose.push_back(jet);
    //m_vJetsAll.push_back(jet);
   vector<int> EventPrintList;
   //EventPrintList.push_back(5336);
   //bool Found = false;
   
   }

  if(m_bUpdateMET){
  	//m_pMET = new MissingEt(*m_pEvent, m_pEvent->MET_RefFinal_STVF, m_vElectronsAll, m_vMuonsAll, m_hMuonSelectorTools[sysVariation]->useThirdMuonChain(),m_vJetsAll,m_sysMETSoftTerms ); //MET
  	m_pMET = new MissingEt(*m_pEvent, m_pEvent->MET_RefFinal, m_vElectronsAll, m_vMuonsAll, m_hMuonSelectorTools[sysVariation]->useThirdMuonChain(),m_vJetsAll,m_sysMETSoftTerms ); //MET
  }
  /*
    if((m_pEvent->eventinfo.RunNumber()==204026 && m_pEvent->eventinfo.EventNumber()==95078870 && m_pEvent->eventinfo.lbn()==506) ||
    (m_pEvent->eventinfo.RunNumber()==203258 && m_pEvent->eventinfo.EventNumber()==75318091 && m_pEvent->eventinfo.lbn()==512)||
    (m_pEvent->eventinfo.RunNumber()==203335 && m_pEvent->eventinfo.EventNumber()==31789820 && m_pEvent->eventinfo.lbn()==176)||
    (m_pEvent->eventinfo.RunNumber()==203524 && m_pEvent->eventinfo.EventNumber()==54814253 && m_pEvent->eventinfo.lbn()==314)||
    (m_pEvent->eventinfo.RunNumber()==205017 && m_pEvent->eventinfo.EventNumber()==87862859 && m_pEvent->eventinfo.lbn()==369)){
    	std::cout << "EVENTBLAH: "<<m_pEvent->eventinfo.RunNumber() << "\t" << m_pEvent->eventinfo.EventNumber() << "\t"<< m_pEvent->eventinfo.lbn() <<"\n";
	double STVF=0.;
	//if (m_pEvent->MET_CellOut_Eflow.sumet()!=0.) STVF =  m_pEvent->MET_CellOut_Eflow_STVF.sumet()/m_pEvent->MET_CellOut_Eflow.sumet();
	std::cout << "\t" << m_pMET->Et() << "\t" << m_pMET->momentumSTVF().Et() << "\t"<<m_pMET->rawMomentum().Et()<< "\t"<<m_fMu<< "\t"<<STVF<< std::endl;
    */
    //}
    //return EL::StatusCode::FAILURE;

  //Sort PhysicsObject by Pt
  ////now look at everything
  sortPt(m_vElectrons);
  sortPt(m_vElectronsInc);
  sortPt(m_vElectronsLoose);
  sortPt(m_vElectronsLooseNotTight);
  sortPt(m_vElectronsTight);
  sortPt(m_vElectronsAll);
  sortPt(m_vMuons);
  sortPt(m_vMuonsLoose);
  sortPt(m_vMuonsLooseNotTight);
  sortPt(m_vMuonsTight);
  sortPt(m_vMuonsInc);
  sortPt(m_vMuonsAll);
  sortPt(m_vTaus);
  sortPt(m_vJets);
  sortPt(m_vJetsLoose);
  sortPt(m_vJetsAll);
  
  //Calculate all the important objects
  tagObjects();
  
  //b-tag veto
  m_iNBTag = 0;
  for(unsigned int i = 0; i < m_vJets.size(); i++)
    if(m_vJets[i].btagged(Eff85,m_sysJVF))
      m_iNBTag++;
  


  if(m_bDoMxM){
    m_vMxMRawResults.clear();
    if(m_sysMxM == MxMBJetAlt) m_vMxMRawResults = m_pMatrixMethodWWWAlt->weightsForInput(m_vTaggedLeptons_MMLepton,m_iNBTag );
    else if(m_sysMxM == MxMBJetAltFlipped) m_vMxMRawResults = m_pMatrixMethodWWWAltFlipped->weightsForInput(m_vTaggedLeptons_MMLepton,m_iNBTag );
    else m_vMxMRawResults = m_pMatrixMethodWWW->weightsForInput(m_vTaggedLeptons_MMLepton,m_iNBTag );
  }





  return EL::StatusCode::SUCCESS;
};
	
int wwwAnalysis :: Analysis :: selectEvent (std::string sysVariation){
  //trigger matching cut
  bool m_bIsTriggerMatched = false;
  std::vector<bool> vTaggedLeptonIsTriggerMatched;
  vTaggedLeptonIsTriggerMatched.clear();
  for(unsigned int i = 0; i< m_pTaggedLeptons.size() ; i++){
	  	bool matchedLep = false;
    		if (m_pTaggedLeptons.at(i) && m_pTaggedLeptons.at(i)->type() == MUON){
			
			matchedLep = 
			(m_hTriggerTool->match(m_pEvent, m_pTaggedLeptons.at(i),"EF_mu24i_tight") && m_pTaggedLeptons.at(i)->momentum().Pt() > 25000.)
			||
			(m_hTriggerTool->match(m_pEvent, m_pTaggedLeptons.at(i),"EF_mu36_tight")  && m_pTaggedLeptons.at(i)->momentum().Pt() > 37000.);
		}
    		else if (m_pTaggedLeptons.at(i) && m_pTaggedLeptons.at(i)->type() == ELECTRON){
			matchedLep = 
			(m_hTriggerTool->match(m_pEvent, m_pTaggedLeptons.at(i),"EF_e60_medium1")  && m_pTaggedLeptons.at(i)->momentum().Pt() > 61000.) 
			||
			(m_hTriggerTool->match(m_pEvent, m_pTaggedLeptons.at(i),"EF_e24vhi_medium1") && m_pTaggedLeptons.at(i)->momentum().Pt() > 25000.);

		}

		if (matchedLep) {
			m_bIsTriggerMatched=true;
			vTaggedLeptonIsTriggerMatched.push_back(true);
			//break;
		} else vTaggedLeptonIsTriggerMatched.push_back(false);

  }


  if( (m_bDoZTagAndProbe || m_bDoFakeTagAndProbe || m_bDoFakeTagAndProbeInclusiveSign || m_bDoZPlusJetsTagAndProbe || m_bDoZPlusGammaTagAndProbe) && (m_bUpdateElectrons || m_bUpdateMuons) ){
    m_pTPTags.clear();
    m_pTPTags2.clear();
    m_pTPProbes.clear();

    if(m_bDoZTagAndProbe){
      //std::cout << "==============================" << std::endl;
      for (unsigned int i = 0 ; i < m_pTaggedLeptons.size() ; i++){
  	bool tagIsTriggerMatched = vTaggedLeptonIsTriggerMatched[i];
	    //don't consider tags that are not trigger matched
	if(!tagIsTriggerMatched) continue;
        for (unsigned int j = 0 ; j < m_pTaggedLooseLeptons.size() ; j++){
	    wwwAnalysis::PhysicsObject * candTag   = m_pTaggedLeptons[i];
	    wwwAnalysis::PhysicsObject * candProbe = m_pTaggedLooseLeptons[j];
	    //std::cout << "-----------------------------------" << std::endl;
	    //std::cout << "cand tag " << i << " cand probe " << j << std::endl;
	    //std::cout << "\ttag " << i << " " << candTag->momentum().Pt() <<  "\t" << candTag->momentum().Eta()  << "\t" << candTag->momentum().Phi() << std::endl;
	    //std::cout << "\tprobe " << j << " " << candProbe->momentum().Pt() <<  "\t" << candProbe->momentum().Eta()  << "\t" << candProbe->momentum().Phi() << std::endl;

	    //Remove overlaps and make sure not using same lepton
	    double deltaR = candTag->momentum().DeltaR(candProbe->momentum());
	    //std::cout << "\tdeltaR " << deltaR<<std::endl;
	    if(deltaR < 0.1) continue;


	    //Select for SFOS pairs
	    if(candTag->type()!=candProbe->type()) continue;
	    if(candTag->charge()*candProbe->charge()==1) continue;

	    TLorentzVector tlv = candTag->momentum() + candProbe->momentum();
	    double pairMass = tlv.M();

	    //std::cout << "\tmass " << pairMass<<std::endl;

            //veto pairs outside the z-peak
	    double zwindow = 15000;
	    double zmass = 90000;
	    if ( TMath::Abs(pairMass - zmass) > zwindow) continue;
	    //std::cout << "\t*******PASS*********" << std::endl;

	    m_pTPTags.push_back(candTag);
	    m_pTPProbes.push_back(candProbe);


	    }
	  }
	}
	else if(m_bDoZPlusJetsTagAndProbe || m_bDoZPlusGammaTagAndProbe){
	      //This looks for two leptons coming from a Z as the tag
	      // and a third looser lepton as the probe
	      //std::cout << "==============================" << std::endl;
	      for (unsigned int i = 0 ; i < m_pTaggedLeptons.size() ; i++){
		bool tag1IsTriggerMatched = vTaggedLeptonIsTriggerMatched[i];
	        for (unsigned int j = 0 ; j < m_pTaggedLeptons.size() ; j++){
		  //don't look at same lepton and don't look at opposite permutation
		  if (j >= i) continue;
		  bool tag2IsTriggerMatched = vTaggedLeptonIsTriggerMatched[j];
		  //don't consider tags that are not trigger matched
		  if(!tag1IsTriggerMatched || !tag2IsTriggerMatched) continue;
		  wwwAnalysis::PhysicsObject * candTag1   = m_pTaggedLeptons[i];
		  wwwAnalysis::PhysicsObject * candTag2   = m_pTaggedLeptons[j];
		  //Remove overlaps and make sure not using same lepton
		  double deltaR = candTag1->momentum().DeltaR(candTag2->momentum());
		  if(deltaR < 0.1) continue;
		  //Select for SFOS pairs
		  if(candTag1->type()!=candTag2->type()) continue;
	          if(candTag1->charge()*candTag2->charge()==1) continue;

		  if(m_bDoZPlusJetsTagAndProbe){
		  	  //Invariant mass requirement is particular to Z+Jets
		   	  TLorentzVector tlv = candTag1->momentum() + candTag2->momentum();
			  double pairMass = tlv.M();

			  //veto pairs outside the z-peak
			  double zwindow = 15000;
			  double zmass = 90000;
			  if ( TMath::Abs(pairMass - zmass) > zwindow) continue;
		  }

		  for (unsigned int k = 0 ; k < m_pTaggedLooseLeptons.size() ; k++){
		    wwwAnalysis::PhysicsObject * candProbe = m_pTaggedLooseLeptons[k];
		    double deltaR1 = candTag1->momentum().DeltaR(candProbe->momentum());
		    double deltaR2 = candTag2->momentum().DeltaR(candProbe->momentum());
		    //don't consider probe leptons that overlap with tag leptons
		    //for z plus jets selection only
		    //Allowing that mis-id'd photon is collinear with lepton
		    if(m_bDoZPlusJetsTagAndProbe){
		      if (deltaR1 < 0.1 || deltaR2 < 0.1) continue;
		    }

		    if(m_bDoZPlusGammaTagAndProbe){
		    	//only consider Z->mu mu events for Z+gamma
		    	if (candTag1->type()==ELECTRON) continue;

			//probe should be electron for Z+gamma
			if (candProbe->type()==MUON) continue;

			//veto considers invariant mass of all three leptons
		   	TLorentzVector tlv = candTag1->momentum() + candTag2->momentum() + candProbe->momentum();
			double pairMass = tlv.M();
			double zwindow = 10000.;  //to match WZ
			double zmass = 90000.; //may want to consider using mass that WZ is using: 91.1876 GeV
			if ( TMath::Abs(pairMass - zmass) > zwindow) continue;
		    }


		    //only consider probe leptons with opposite flavor from tags
		    //this should always pass for Z+gamma
		    if (candProbe->type()==candTag1->type() || candProbe->type()==candTag2->type()) continue;



		    m_pTPTags.push_back(candTag1);
		    m_pTPTags2.push_back(candTag2);
		    m_pTPProbes.push_back(candProbe);
		  } //end loop over probes
	        } //end loop over tag 2
	      } //end loop over tag 1

	}  //end if do Z+X tag and probe
	else if(m_bDoFakeTagAndProbe || m_bDoFakeTagAndProbeInclusiveSign ){
          for (unsigned int i = 0 ; i < m_pTaggedLeptons.size() ; i++){
  	    bool tagIsTriggerMatched = vTaggedLeptonIsTriggerMatched[i];
	    //don't consider tags that are not trigger matched
	    if(!tagIsTriggerMatched) continue;

            for (unsigned int j = 0 ; j < m_pTaggedLooseLeptons.size() ; j++){
	      wwwAnalysis::PhysicsObject * candTag   = m_pTaggedLeptons[i];
 	      wwwAnalysis::PhysicsObject * candProbe = m_pTaggedLooseLeptons[j];


	      //Remove overlaps and make sure not using same lepton
	      double deltaR = candTag->momentum().DeltaR(candProbe->momentum());
	      if(deltaR < 0.1) continue;

	      //do not consider tag and probe pairs of the same flavor
	      //if (candTag->type() == candProbe->type()) continue;

	      //do not consider tag and probe pairs of the opposite charge
	      if(!m_bDoFakeTagAndProbeInclusiveSign ) 
	      	if (candTag->charge() != candProbe->charge()) continue;


	      m_pTPTags.push_back(candTag);
	      m_pTPProbes.push_back(candProbe);


	    }
	  }
	}

  } // end do Tag and Probe



  int btagEff60=0;
  int btagEff70=0;
  int btagEff80=0;
  int btagEff85=0;
  for(unsigned int i = 0; i < m_vJets.size(); i++){
    if(m_vJets[i].btagged(Eff60,m_sysJVF)) btagEff60++;
    if(m_vJets[i].btagged(Eff70,m_sysJVF)) btagEff70++;
    if(m_vJets[i].btagged(Eff80,m_sysJVF)) btagEff80++;
    if(m_vJets[i].btagged(Eff85,m_sysJVF)) btagEff85++;
  }

  InitialState init = MC_INITIAL_DATA;
  FinalState final = MC_FINAL_DATA;
  if(m_bUpdateMiscWeights && m_bIsMC)
  {
    m_fMcWeight = m_pEvent->eventinfo.mc_event_weight();
    m_fXSecWeight = m_hCrossSectionTool->getEffectiveLuminosityWeight(m_pEvent->eventinfo.mc_channel_number());
    if(m_bIsFake) m_fXSecWeight *= -1;

    if(m_sysPileup == wwwAnalysis::PileupUp) m_fPuWeight = m_hPileupToolUp->GetCombinedWeight(m_pEvent->eventinfo.RunNumber(), m_pEvent->eventinfo.mc_channel_number(), m_fMu);
    else if(m_sysPileup == wwwAnalysis::PileupDown) m_fPuWeight = m_hPileupToolDown->GetCombinedWeight(m_pEvent->eventinfo.RunNumber(), m_pEvent->eventinfo.mc_channel_number(), m_fMu);
    else m_fPuWeight = m_hPileupTool->GetCombinedWeight(m_pEvent->eventinfo.RunNumber(), m_pEvent->eventinfo.mc_channel_number(), m_fMu);
  }
    
  if(m_bUpdateLepMETSFWeights && m_bIsMC){

    m_fSFWeight = 1.0;
    for(int i = 0; i < (int)m_vElectrons.size(); i++) 
      m_fSFWeight *= m_vElectrons[i].scaleFactor(m_sysElectronEff);
    for(int i = 0; i < (int)m_vMuons.size(); i++)
      m_fSFWeight *= m_vMuons[i].scaleFactor(m_sysMuonEff);
    for(int i = 0; i < (int)m_vTaus.size(); i++)
      m_fSFWeight *= m_vTaus[i].scaleFactor();

    m_fSFWeight  *= m_pMET->scaleFactor();
  }
  



  if(m_bUpdateTrigSFWeights && m_bIsMC) m_fTrigWeight = m_hTriggerTool->triggerSF(m_iRunNumber, m_pTaggedLeptons, m_bIsFake,m_sysTrigSF);


  if(m_bUpdateJetTagSFWeights && m_bIsMC){
    m_fJetTagWeight60 = 1.;
    m_fJetTagWeight70 = 1.;
    m_fJetTagWeight80 = 1.;
    m_fJetTagWeight85 = 1.;
    for (unsigned int i = 0; i < m_vJets.size(); ++i){
      m_fJetTagWeight60 *= m_vJets[i].scaleFactor(Eff60,m_sysJetTagSF,m_sysJVF);
      m_fJetTagWeight70 *= m_vJets[i].scaleFactor(Eff70,m_sysJetTagSF,m_sysJVF);
      m_fJetTagWeight80 *= m_vJets[i].scaleFactor(Eff80,m_sysJetTagSF,m_sysJVF);
      m_fJetTagWeight85 *= m_vJets[i].scaleFactor(Eff85,m_sysJetTagSF,m_sysJVF);
    }
  }

  double s2 = 0.;
  if(m_bApplyUnitarization && m_pEvent->eventinfo.mc_channel_number.IsAvailable() && m_pEvent->eventinfo.mc_channel_number() >=185398 && m_pEvent->eventinfo.mc_channel_number() <= 185469){
	//std::cout << s2 << "\t" << m_fFormFactorWeight << std::endl;
  	double pdfx1 = m_pEvent->mcevt.pdf_x1()->at(0);
  	double pdfx2 = m_pEvent->mcevt.pdf_x2()->at(0);
  	s2    = 4*pdfx1*pdfx2*4000.*4000.;
  	m_fFormFactorWeight = m_hFormFactorReweightingTool->weight(m_pEvent->eventinfo.mc_channel_number(),s2);
  }


  bool hasSpectroMuons = false;
  for (int i=0;i<m_pEvent->mu_staco.n();i++){
  	for(unsigned int j=0;j<m_pEvent->mu_staco_MET[i].statusWord().size();j++){
    		hasSpectroMuons = hasSpectroMuons || (m_pEvent->mu_staco_MET[i].statusWord().at(j) & 0x0002); //SPECTRO CODE
	}
  }




  fillCutFlows("Raw",m_fMcWeight ,sysVariation);

  //Event check
  if ((m_bIsMC) || m_oGoodRunsList.HasRunLumiBlock(m_iRunNumber,m_pEvent->eventinfo.lbn()))
  {
   	fillCutFlows("GRL",m_fMcWeight ,sysVariation);

    double lumi = m_hPileupTool->GetIntegratedLumi()/1000.0;
    std::vector<int> save;
    
    	
    
    mapEventSelectorIndexOuter_t::iterator variation_it = m_mEventSelectorIndex.find(sysVariation);
    mapEventSelectorIndexInner_t variation_map = variation_it->second;
    for(mapEventSelectorIndexInner_t::iterator index_it = variation_map.begin();index_it != variation_map.end(); index_it++){
    	unsigned int i = index_it->second;
	const Root::TAccept &eventpass = m_hEventSelectorTools[i]->accept(*m_pEvent, m_pTaggedLeptons,m_pTaggedLeptonsFake,
									  m_pTaggedLooseNotTightLeptons,
									  m_pTaggedLooseLeptons,
									  m_pTPTags,
									  m_pTPTags2,
									  m_pTPProbes,
									  m_vTaus, 
									  m_vJets, m_vJetsLoose, m_vJetsAll, 
									  m_pMET->pt(), m_pMET,m_iRunNumber, m_bIsMC, 
									  m_bIsEGammaStream,m_bIsFake, m_iNPV_3trks, m_bIsTriggerMatched, m_iNBTag == 0, 
									  AdditionnalInfo);

	//if(eventpass) std::cout << "PASSED" << std::endl;
	if(!m_bIsFake)
	  fillCutFlows(i, eventpass, m_fMcWeight , m_fSFWeight , m_fPuWeight, m_fJetTagWeight85,  m_fTrigWeight, m_fXSecWeight,m_fChargeMisIDWeight,m_fMxMWeight,m_fFormFactorWeight );
	if (false && eventpass){
		std::cout << "************" << std::endl;
		for (int lep = 0;lep< m_pTaggedLeptons.size();lep++){
			if (m_pTaggedLeptons[lep]->type()==MUON){
				//std::cout << ((Muon*)m_pTaggedLeptons[lep])->d3pd().type() << "\t";
				std::cout << lep << "\t Muon, type"  << ((Muon*)m_pTaggedLeptons[lep])->d3pd().type() << "\t";
				std::cout << (((Muon*)m_pTaggedLeptons[lep])->isSignalLike() ? "SL" : "") <<
				(((Muon*)m_pTaggedLeptons[lep])->isFromHeavyFlavor() ? "HF" : "")<<
				(((Muon*)m_pTaggedLeptons[lep])->isFromLightFlavor() ? "LF" : "")<<
				(((Muon*)m_pTaggedLeptons[lep])->isFromPhotonConversion() ? "PC" : "") << std::endl;
			}
			else{
				std::cout << lep << "\t Electron, type "  ;
				std::cout << ((Electron*)m_pTaggedLeptons[lep])->d3pd().type() << "\t";
				std::cout << ((Electron*)m_pTaggedLeptons[lep])->d3pd().typebkg() << "\t";
				std::cout << ((Electron*)m_pTaggedLeptons[lep])->d3pd().originbkg() << "\t";
				std::cout << (((Electron*)m_pTaggedLeptons[lep])->isSignalLike() ? "SL" : "") <<

				(((Electron*)m_pTaggedLeptons[lep])->isFromHeavyFlavor() ? "HF" : "")<<
				(((Electron*)m_pTaggedLeptons[lep])->isFromLightFlavor() ? "LF" : "")<<
				(((Electron*)m_pTaggedLeptons[lep])->isFromPhotonConversion() ? "PC" : "") << std::endl;
			}
		}

	}
	
	if(eventpass && m_vSave[i])
	  save.push_back(i);

    }

    
    for(unsigned int i = 0; i < save.size(); i++){
      int nsfos = m_hEventSelectorTools[save[i]]->getNSFOS();
      int nsfos_all = m_hEventSelectorTools[save[i]]->getNSFOSAll();
      const vector<double> masses_sfos = m_hEventSelectorTools[save[i]]->getMassesSFOS();
      const vector<double> masses_sfos_all = m_hEventSelectorTools[save[i]]->getMassesSFOSAll();
      m_pOut[m_vEventSelectorNames[save[i]]]->Fill(*m_pEvent, init, final, lumi, nsfos, nsfos_all, 
      						   masses_sfos,masses_sfos_all,
      						   m_iNPV_2trks, m_iNPV_3trks, 
						   //btagEff70, 
						   btagEff85,
						   s2,
						   m_fMu,
						   m_pTaggedLeptons,m_pTaggedLeptonsFake,
						   m_pTaggedLooseNotTightLeptons,
						   m_pTaggedLooseLeptons,
						   m_pAllLeptons,
						   m_pTPTags,
						   m_pTPTags2,
						   m_pTPProbes,
						   hasSpectroMuons,
						   //m_pTaggedLeptonsInc, 
						   m_vJets, 
						   *m_pMET, m_fMcWeight , m_fSFWeight, m_fPuWeight, 
						   //m_fJetTagWeight70, 
						   m_fJetTagWeight85,
						   m_fTrigWeight, m_fXSecWeight, m_fChargeMisIDWeight,m_fMxMWeight,m_fFormFactorWeight ,
						   m_bDoChargeFlip,m_bIsFake,m_bIsEGammaStream,m_sysJVF, AdditionnalInfo,m_bHasLooseNotTightElectrons,m_bHasLooseNotTightMuons); 
      if(m_bIsMC&& m_bSaveTruthInfo) m_pTruthOut[m_vEventSelectorNames[save[i]]]->Fill(*m_pEvent, lumi,m_fMcWeight, 
      												       m_fSFWeight, 
												       m_fPuWeight, 
												       m_fJetTagWeight85,
												       m_fTrigWeight, 
												       m_fXSecWeight, 
												       m_fChargeMisIDWeight,
												       m_fMxMWeight,
												       m_fFormFactorWeight );
    }
  
  }

  return EL::StatusCode::SUCCESS;
};

EL::StatusCode wwwAnalysis :: Analysis :: finalize ()
{
  std::cout << "finalize" << std::endl;
  // do everything you need to do before the job on the
  // worker node ends.  so far I have no example of what
  // that would be, but the hook is here just in case.
  TriggerTool::finalize();

  
  for(unsigned int i = 0; i < m_vEventSelectorNames.size(); i++) {
    if(m_vSave[i]) {
      Output *&out = m_pOut[m_vEventSelectorNames[i]];
      out->finalize();
      if(out)delete out;
      out = 0;

      if(m_bSaveTruthInfo){
	      TruthOutput *&truthout = m_pTruthOut[m_vEventSelectorNames[i]];
	      truthout->finalize();
	      if(truthout)delete truthout;
	      truthout = 0;
      }

    }
  }

  if(m_pMatrixMethodWWW) delete m_pMatrixMethodWWW;
  m_pMatrixMethodWWW = 0;
  if(m_pMatrixMethodWWWAlt) delete m_pMatrixMethodWWWAlt;
  m_pMatrixMethodWWWAlt = 0;
  if(m_pMatrixMethodWWWAltFlipped) delete m_pMatrixMethodWWWAltFlipped;  
  m_pMatrixMethodWWWAltFlipped = 0;
  if(m_hChargeMisIDTool) delete m_hChargeMisIDTool;
  m_hChargeMisIDTool = 0;
  if(m_hFormFactorReweightingTool) delete  m_hFormFactorReweightingTool;
  m_hFormFactorReweightingTool = 0;

  if(m_hGoodRunsListReader)delete m_hGoodRunsListReader;
  m_hGoodRunsListReader = 0;

  if(m_hPileupWriteTool) {
  	TString filename = wk()->metaData()->getString("sample_name") +".prw.root";
  	m_hPileupWriteTool->WriteToFile(filename);
	delete m_hPileupWriteTool;
	m_hPileupWriteTool = 0;
  }

  
  D3PDReader::D3PDReadStats stat = m_pEvent->GetStatistics();
  std::vector< TString > branchNames = stat.GetBranchesByEntries( 1 );
  std::cout << "******************************"<<std::endl;
  std::cout << "BRANCH NAMES USED"<<std::endl;
  for (unsigned int i=0;i<branchNames.size();i++) std::cout << branchNames[i] << std::endl;
  std::cout << "******************************"<<std::endl;
  std::cout << "end finalize" << std::endl;
  return EL::StatusCode::SUCCESS;
};

int wwwAnalysis :: Analysis :: selectObjectsMxM (unsigned int resultIndex, std::string sysVariation){
  if(resultIndex >= m_vMxMRawResults.size()) {
    std::cout << "ERROR in selectObjectsMxM: resultIndex = " << resultIndex << " is invalid" << std::endl;
    return EL::StatusCode::FAILURE;
  }

  m_pTaggedLeptons.clear();
  m_vElectrons.clear();
  m_vMuons.clear();
  m_vJets.clear();
  m_vJetsLoose.clear();


  //std::cout << sysVariation << std::endl;
  m_fMxMWeight =  m_vMxMRawResults[resultIndex].weight;
  //std::cout << "weight " << m_fMxMWeight << std::endl;
  double var = 0.;
  if(m_sysMxM == MxMElUp || m_sysMxM ==  MxMElDown) {
  	var = m_vMxMRawResults[resultIndex].varElCorr;
	//std::cout << "El Corr " << var << std::endl;
  }
  if(m_sysMxM == MxMMuUp || m_sysMxM ==  MxMMuDown) {
  	var = m_vMxMRawResults[resultIndex].varMuCorr;
	//std::cout << "Mu Corr " << var << std::endl;
  }


  if(m_sysMxM == MxMElUp || m_sysMxM ==  MxMElDown || m_sysMxM == MxMMuUp || m_sysMxM ==  MxMMuDown) {
  	//Bins below this threshold contribute to the electron uncertainty 
	//while those >= this threshold contributes to the muon uncertainty
  	//int binThreshold = 16; 
  	unsigned int binThreshold = m_pMatrixMethodWWW->getWWWEfficiencyLoader()->numFakeBinsEl()+1; 
  	for (unsigned int i = 0; i < m_vMxMRawResults[resultIndex].varBins.size(); i++){
  		if((m_sysMxM == MxMElUp || m_sysMxM ==  MxMElDown) && (i >= binThreshold)) continue;
  		if((m_sysMxM == MxMMuUp || m_sysMxM ==  MxMMuDown) && (i < binThreshold)) continue;

  		//if (m_vMxMRawResults[resultIndex].varBins[i] > .1) continue;

  		//if((m_sysMxM == MxMElUp || m_sysMxM ==  MxMElDown) ) std::cout << "El uncorr " << i <<"\t"<< m_vMxMRawResults[resultIndex].varBins[i] << std::endl;
  		//if((m_sysMxM == MxMMuUp || m_sysMxM ==  MxMMuDown) ) std::cout << "Mu uncorr " << i << "\t"<<m_vMxMRawResults[resultIndex].varBins[i] << std::endl;
			
  		var += m_vMxMRawResults[resultIndex].varBins[i];
	}
  }


  if(m_sysMxM == MxMElUp || m_sysMxM == MxMMuUp) m_fMxMWeight+=TMath::Sqrt(var);
  if(m_sysMxM ==  MxMElDown || m_sysMxM ==  MxMMuDown) m_fMxMWeight-=TMath::Sqrt(var);
  //std::cout << "Weight + sys " << m_fMxMWeight << std::endl;

  for(unsigned int i = 0;i< m_vMxMRawResults[resultIndex].leptonTightList.size() ; i++){
  	if(m_vMxMRawResults[resultIndex].leptonTightList[i]==0) continue; //not tight


	if(m_vTaggedLeptonsMxM[i].type()==ELECTRON) m_vElectrons.push_back(m_vTaggedElectronsMxM[i]);
	else m_vMuons.push_back(m_vTaggedMuonsMxM[i]);
  }

  for(int i = 0; i < m_pEvent->jet_AntiKt4LCTopo.n(); i++) { //Jets

	
    Jet jet = m_vJetsAll[i];

    //test for clean jets
   //implement jet cleaning at TEventSelector stage using D3PD variable
   bool cleanjet=true;

    const Root::TAccept &pass = m_hJetSelectorTools[sysVariation]->accept(jet, m_vElectrons, m_vMuons, m_vTaus, m_vJets,cleanjet,m_sysJVF);

    const Root::TAccept &lpass = m_hJetLooseSelectorTools[sysVariation]->accept(jet, m_vElectrons, m_vMuons, m_vTaus, m_vJetsLoose,cleanjet,m_sysJVF);
    fillCutFlow(m_pCutFlowJets[sysVariation], pass,m_fMcWeight );
    if(pass)
      m_vJets.push_back(jet);
    if(lpass)
      m_vJetsLoose.push_back(jet);
    //m_vJetsAll.push_back(jet);
   vector<int> EventPrintList;
   //EventPrintList.push_back(5336);
   //bool Found = false;
   
   }


  //b-tag veto
  m_iNBTag = 0;
  for(unsigned int i = 0; i < m_vJets.size(); i++)
    if(m_vJets[i].btagged(Eff85,m_sysJVF))
      m_iNBTag++;
  
  sortPt(m_vElectrons);
  sortPt(m_vMuons);
  sortPt(m_vJets);
  sortPt(m_vJetsLoose);

  tagObjects();
  
  return EL::StatusCode::SUCCESS;

};


void wwwAnalysis::Analysis::setDoMxM(bool bSwitch) { 
	m_bDoMxM = bSwitch; 
	std::cout << "Setting MxM Weighting to " << (m_bDoMxM ? "ON" : "OFF") << std::endl;
	//std::cout << "MxM Weighting will only take effect if processing data" << std::endl;;
};


