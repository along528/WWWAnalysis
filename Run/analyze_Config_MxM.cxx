#include <map>
#include <iostream>
#include <stdio>
#include <sstream>
#include <string>
#include <vector>


void *ConfigureTool(const std::string &tool, const std::string &level)
{
  TString path = "$ROOTCOREBIN/python/wwwAnalysis/Configured"+tool+"s.py";
  gSystem->ExpandPathName (path);
  TPython::LoadMacro (path.Data());
  return (void*)TPython::Eval(("Configured"+tool+"_"+level+"()").c_str());
}
std::string getSource(const std::string &ds)
{
	return ds.substr(0, ds.find("NTUP_TAU"));
}
void analyze_Config_MxM(const std::string &ele_config, const std::string &mu_config, const std::string &event_config,const std::string &submit,const std::string &scandir="",const std::string &sysflag="",const std::string &elRealRateConfig = "", const std::string &muRealRateConfig = "", const std::string &elFakeRateConfig = "", const std::string &muFakeRateConfig = "",const std::string &ele_config_loose="", const std::string &mu_config_loose="")
//void analyze_Config_MxM(const std::string &ele_config, const std::string &mu_config, const std::string &event_config,const std::string &submit,const std::string &scandir="",const std::string &sysflag="",std::string elRealRateConfig = "", std::string muRealRateconfig = "", std::string elFakeRateConfig = "", std::string muFakeRateConfig = "")
{
  gSystem->Load("libPhysics");
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");
  if(sysflag!="") submit+="_"+sysflag;

  EL::Job job;

	//Find samples and add meta data
  SH::SampleHandler sh;

	  bool doFake=bool(event_config=="Baseline_PreselectionDilepton_Fakes");

if (scandir=="") SH::scanDir(sh,"/home/graduate/along528/gpfs1/www/www");
else SH::scanDir(sh,scandir.c_str());

  sh.print(); 
  sh.setMetaString("nc_tree","physics");
  for(std::size_t i = 0; i < sh.size(); i++)
  {     
        sh[i]->meta()->setString("sample_name",sh[i]->name());
  	
        //if(source.find("embedding") != string::npos) sh[i].meta()->setDouble("nc_isembedding",double(1));
        //else sh[i].meta()->setDouble("nc_isembedding",double(-1));
  }
  job.sampleHandler(sh);
	job.options()->setDouble(EL::Job::optCacheLearnEntries, 500);
  wwwAnalysis::Analysis *alg = new wwwAnalysis::Analysis();

  //wwwAnalysis::TElectronSelectorTool* electronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Medium"));

  wwwAnalysis::TElectronSelectorTool* noquality_noptreq_electronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","HW_NoQuality_NoPtReq"));
  wwwAnalysis::TElectronSelectorTool* electronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool",ele_config.c_str()));
  //wwwAnalysis::TMuonSelectorTool* noquality_nopreq_muonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","HW_NoQuality_NoPtReq));
  wwwAnalysis::TMuonSelectorTool* muonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool",mu_config.c_str()));
  wwwAnalysis::TTauSelectorTool* tauSelectorTool = static_cast<wwwAnalysis::TTauSelectorTool*>(ConfigureTool("TTauSelectorTool","Medium"));
  wwwAnalysis::TJetSelectorTool* jetSelectorTool = static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Medium"));

  if(doFake){
  wwwAnalysis::TElectronSelectorTool* fakeElectronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","HW_Custom_Fakes"));
  wwwAnalysis::TMuonSelectorTool* fakeMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","HW_Custom_Fakes"));
  }


  wwwAnalysis::TElectronSelectorTool* tauElectronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Loose"));
  wwwAnalysis::TMuonSelectorTool* tauMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","StacoLoose"));
  //wwwAnalysis::TMuonSelectorTool* tauMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Loose"));
  wwwAnalysis::TJetSelectorTool* jetLooseSelectorTool = static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Loose"));
  


  // Tell our analysis to use this selector.
  TString path = "$ROOTCOREBIN/../wwwAnalysis";
  gSystem->ExpandPathName (path);


  wwwAnalysis::SystematicsConfig *sysconfig  = new wwwAnalysis::SystematicsConfig();
  if(sysflag=="All") sysconfig->switchOnAll();
  else if(sysflag=="") {
  	//sysconfig->switchOffAll();
	sysconfig->switchOn("Central");
  }
  else if(sysflag=="Central") {
  	//sysconfig->switchOffAll();
	sysconfig->switchOn("Central");
  }
  else {
  	//try to switch on category
	//if category doesn't exist 
	//then returns false and nothing happens
  	if(!sysconfig->switchOnCategory(sysflag)){ 
		//assume if not category
		//then you really only want
		//that systematic and not even
		//the central value
		//this is is useful for debugging purposes
  		sysconfig->switchOn(sysflag);
  		sysconfig->switchOff("Central");
	}
	else{
		//assume that if the category exists
		//you also want the central value computed
  		sysconfig->switchOn("Central");
	}
  }
  //sysconfig->switchOn(sysflag);
  sysconfig->print();
  alg->setDoMxM(true);
  //alg->setMatrixMethodConfig(elRealRateConfig,muRealRateConfig,elFakeRateConfig,muFakeRateConfig);
  alg->setMatrixMethodConfig(elRealRateConfig.c_str(),muRealRateConfig.c_str(),elFakeRateConfig.c_str(),muFakeRateConfig.c_str());


  alg->m_pSystematics = sysconfig; //getSystematicsConfiguration(sysflag);

  while(alg->m_pSystematics->next()){
  	  TString var = alg->m_pSystematics->getCurrentSystematic();
	  alg->addObjectSelector("Electron" ,static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool",ele_config.c_str())), var);
	  alg->addObjectSelector("ElectronNoQuality" ,static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","HW_NoQuality_NoPtReq")), var);
	  if (ele_config_loose=="") {
	  	std::cout << "Using Loose Electron Object Selector" << std::endl;
	  	alg->addObjectSelector("ElectronLoose" ,static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Loose")), var);
	  }
	  else {
	  	std::cout << "Using " << ele_config_loose << " Electron Object Selector" << std::endl;
	  	alg->addObjectSelector("ElectronLoose" ,static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool",ele_config_loose.c_str())), var);
	  }

	  if (mu_config_loose=="") {
	  	std::cout << "Using Loose Muon Object Selector" << std::endl;
	  	alg->addObjectSelector("MuonLoose",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Loose")),var);
	  }
	  else {
	  	std::cout << "Using " << mu_config_loose << " Muon Object Selector" << std::endl;
	  	alg->addObjectSelector("MuonLoose",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool",mu_config_loose.c_str())),var);
	  }
	  alg->addObjectSelector("Muon",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool",mu_config.c_str())),var);
	  alg->addObjectSelector("MuonNoQuality",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","HW_NoQuality_NoPtReq")),var);
	  alg->addObjectSelector("Tau",static_cast<wwwAnalysis::TTauSelectorTool*>(ConfigureTool("TTauSelectorTool","Medium")),var);
	  alg->addObjectSelector("Jet",static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Medium")),var);
    	  if(doFake){
		  alg->addObjectSelector("FakeElectron",static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","HW_Custom_Fakes")),var);
		  alg->addObjectSelector("FakeMuon",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","HW_Custom_Fakes")),var);
     	  }
	  alg->addObjectSelector("TauElectron",static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Loose")),var);
	  alg->addObjectSelector("TauMuon",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","StacoLoose")),var);
	  alg->addObjectSelector("JetLoose",static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Loose")),var);
  }

  //char *evconfig;
  char *evconfig = strtok(event_config.c_str(),",");
  alg->saveTruthInfo(false);
  while(evconfig!=NULL){
	std::string evname  = evconfig;
	std::string evname_full = evname;
	std::string searchTerm = "Baseline_";
	if (evname.find(searchTerm.c_str())!=std::string::npos){
	    evname.replace(evname.find("Baseline_"),searchTerm.length(),"");
	}
	std::cout << evname << std::endl;
	while(alg->m_pSystematics->next()){
		std::string outname = evname+"_"+alg->m_pSystematics->getCurrentSystematic();
		std::cout << outname << std::endl;
		//bool save = false;
		bool save = true;
		if (alg->m_pSystematics->getCurrentSystematic()=="Central") save = true;
		if (save) std::cout << "save" << std::endl;
 		alg->addEventSelector(evname.c_str(),static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool",evname_full.c_str())),save,alg->m_pSystematics->getCurrentSystematic());
	}
	evconfig = strtok(NULL,",");
  }
 

  //configure jet cleaning
  TString jetcleaning_path = path+"/../JetSelectorTools/python/ConfiguredTJetCleaningTools.py";
  TPython::LoadMacro(jetcleaning_path.Data());
  alg->m_hJetCleaningTool = static_cast<Root::TJetCleaningTool*>((void*)TPython::Eval("ConfiguredTJetCleaningTool_VeryLoose()"));

  alg->m_hPileupTool=new Root::TPileupReweighting("PURWTOOL");
alg->m_hPileupTool->AddConfigFile((path+"/pileup/sm_ew_www.prw.root").Data());
  alg->m_hPileupTool->SetDataScaleFactors(1/1.09);
  alg->m_hPileupTool->AddLumiCalcFile((path+"/pileup/sm_ew_ilumicalc.root").Data());
  alg->m_hPileupTool->SetUnrepresentedDataAction(2);



  alg->m_hTriggerTool = new wwwAnalysis::TriggerTool();
  alg->m_bHybrid = true;

  job.algsAdd(alg);
EL::DirectDriver driver;
//EL::ProofDriver driver;
//  driver.numWorkers=30;

  driver.submit(job, submit);
}
