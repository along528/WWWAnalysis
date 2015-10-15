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
void analyze_Config_WritePRW(const std::string &ele_config, const std::string &mu_config, const std::string &event_config,const std::string &submit,const std::string &scandir="",const std::string &sysflag="")
{
  gSystem->Load("libPhysics");
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");
  if(sysflag!="") submit+="_"+sysflag;

  EL::Job job;

	//Find samples and add meta data
  SH::SampleHandler sh;

//  SH::scanDir(sh,"/gpfs1/bu/lhelary/WorkDir/lhelaryNtuple/LastProc/Embedding/");//Louis
//  SH::scanDir(sh,"/home2/graduate/mkruskal/wwwAnalysis/data/XinData");//Mike
//  SH::scanDir(sh,"/home2/graduate/mkruskal/wwwAnalysis/data/XinAll_MC");//Mike
//  SH::scanDir(sh,"/home2/graduate/mkruskal/wwwAnalysis/data/XinAll_nohybrid");//Mike
//  SH::scanDir(sh,"/home2/graduate/mkruskal/wwwAnalysis/data/temp");//Mike
//  SH::scanDir(sh,"/home2/graduate/mkruskal/wwwAnalysis/data/Winter2013AC");//Mike

//  SH::scanDir(sh,"/gpfs1/bu/lhelary/WorkDir/SignalACPLHCXinFile/");//Louis

//   SH::scanDir(sh,"./quickerTest/");
//   SH::scanDir(sh,"./quickTestWZ/");
//   SH::scanDir(sh,"./AllSamples2/");
//if (scandir=="") SH::scanDir(sh,"/home/graduate/along528/SkimNTUP/test15/WorkArea/run/www_Nov30_3Lep");
//if (scandir=="") SH::scanDir(sh,"/home/graduate/along528/gpfs1/SMN2N/SMN2N-00-00-08/Loose/v1/user.along528.mc12_8TeV.167006.MadGraphPythia_AUET2BCTEQ6L1_WWWStar_lnulnulnu.merge.NTUP_SMWWW.p1328.SMN2N-08_Loose_v1.131207060441_EXT0/");
//if (scandir=="") SH::scanDir(sh,"/home/graduate/along528/gpfs1/SMN2N/louis/SMN2N-09_Loose_v1/Categorized/Signal");
if (scandir=="") SH::scanDir(sh,"/home/graduate/along528/gpfs1/www/www");
else SH::scanDir(sh,scandir.c_str());

//SH::scanDir(sh,"/home/graduate/along528/SkimNTUP/test8/WorkArea/run/www_Nov11_3Lep");
//SH::scanDir(sh,"/home/graduate/along528/gpfs1/www/ttbar");
//SH::scanDir(sh,"/home/graduate/along528/SkimNTUP/test8/WorkArea/run/www");
//SH::scanDir(sh,"/home/graduate/along528/SkimNTUP/test8/WorkArea/run/www_smearing");
//SH::scanDir(sh,"/home/graduate/along528/SkimNTUP/test8/WorkArea/run/wz");
//SH::scanDir(sh,"/home/graduate/along528/SkimNTUP/test8/WorkArea/run/wz_smearing");
//SH::scanDir(sh,"/home/graduate/along528/SkimNTUP/test8/WorkArea/run/ttbar");
//SH::scanDir(sh,"/home/graduate/along528/SkimNTUP/test8/WorkArea/run/ttbar_smearing");

/*
SH::scanDir(sh,"/home/graduate/along528/gpfs1/www/data12/p1328_p1329/207528/Egamma");
SH::scanDir(sh,"/home/graduate/along528/gpfs1/www/data12/p1328_p1329/207528/Muons");
*/
//SH::scanDir(sh,"/home/graduate/along528/gpfs1/SLIMS/WWWSLIM.003/wwwWWWSLIM.003.38");
//SH::scanDir(sh,"/gpfs1/bu/lhelary/WorkDir/WWWAnalysis");
//SH::scanDir(sh,"/gpfs1/bu/lhelary/WorkDir/WWWSamples");


//    SH::scanDir(sh,"../../../data_AC_data_muons/");//Lidia
//    SH::scanDir(sh,"../../../data_AC_data_egamma/");//Lidia
//    SH::scanDir(sh,"../../../data_AC_mc/");//Lidia


//On the T2 all the WZ ntuples are stored there: /gpfs1/bu/lhelary/WorkDir/TauTauNtuples/
//I have set four directories, 
//one for El data :/gpfs1/bu/lhelary/WorkDir/wwwAnalysis_leplep/AllDataEgamma/
//one for Mu data :/gpfs1/bu/lhelary/WorkDir/wwwAnalysis_leplep/AllDataMuon/
//one for all MC samples that are long to process :/gpfs1/bu/lhelary/WorkDir/wwwAnalysis_leplep/AllLongMC/
//one for all MC samples that are short to process :/gpfs1/bu/lhelary/WorkDir/wwwAnalysis_leplep/AllMC/
//Using 30 worker nodes below, one can get 30 min for El/Mu, and about 1h for short/long MC...
//The output ntuple is stored in data-output with the histograms
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
  wwwAnalysis::TElectronSelectorTool* electronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool",ele_config.c_str()));
  wwwAnalysis::TMuonSelectorTool* muonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool",mu_config.c_str()));
  wwwAnalysis::TTauSelectorTool* tauSelectorTool = static_cast<wwwAnalysis::TTauSelectorTool*>(ConfigureTool("TTauSelectorTool","Medium"));
  wwwAnalysis::TJetSelectorTool* jetSelectorTool = static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Medium"));

//  wwwAnalysis::TElectronSelectorTool* fakeElectronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Fake"));
//  wwwAnalysis::TMuonSelectorTool* fakeMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Fake"));

  wwwAnalysis::TElectronSelectorTool* tauElectronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Loose"));
  wwwAnalysis::TMuonSelectorTool* tauMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","StacoLoose"));
  //wwwAnalysis::TMuonSelectorTool* tauMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Loose"));
  wwwAnalysis::TJetSelectorTool* jetLooseSelectorTool = static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Loose"));
  /*
  1166   char*str;
  1167   str=strtok (const_cast<char*>(inputFiles.Data()),",");
  1168   while (str!=NULL){
  1169     inputs.push_back(str);
  1170     str=strtok(NULL,",");
  1171   }
  */


  
 //wwwAnalysis::TEventSelectorTool* eventSelectorTool = static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool",event_config.c_str()));
  


  // Tell our analysis to use this selector.
  TString path = "$ROOTCOREBIN/../wwwAnalysis";
  gSystem->ExpandPathName (path);


  wwwAnalysis::SystematicsConfig *sysconfig  = new wwwAnalysis::SystematicsConfig();
  sysconfig->switchOn("Central");
  /*
sysconfig->switchOn("JetPileupNPVUp");
sysconfig->switchOn("JetPileupNPVDown");
sysconfig->switchOn("JetPileupMuUp");
sysconfig->switchOn("JetPileupMuDown");
sysconfig->switchOn("JetPileupPtUp");
sysconfig->switchOn("JetPileupPtDown");
sysconfig->switchOn("JetPileupRhoTopoUp");
sysconfig->switchOn("JetPileupRhoTopoDown");
sysconfig->switchOn("JetVertexFractionUp");
sysconfig->switchOn("JetVertexFractionDown");
*/
  /*sysconfig->switchOn("Central");
  if(sysflag=="All") sysconfig->switchOnAll();
  else if(sysflag=="") {
  	//sysconfig->switchOffAll();
  }
  else if(sysflag=="Central") {
  	//sysconfig->switchOffAll();
	sysconfig->switchOn("Central");
  }
  else {
  	sysconfig->switchOn(sysflag);
  	sysconfig->switchOff("Central");
  }
  */
  //sysconfig->switchOn(sysflag);
  //sysconfig->switchOn("JetVertexFractionUp");
  sysconfig->print();
  /*
  sysconfig->chargeMisIDUp = (sysflag=="ChargeMisIDUp" ? true : false);
  sysconfig->chargeMisIDDown = (sysflag=="ChargeMisIDDown" ? true : false);
  sysconfig->muonEffUp = (sysflag=="MuonEffUp" ? true : false);
  sysconfig->muonEffDown = (sysflag=="MuonEffDown" ? true : false);
  sysconfig->muonMomMSUp = (sysflag=="MuonMomMSUp" ? true : false);
  sysconfig->muonMomMSDown = (sysflag=="MuonMomMSDown" ? true : false);
  sysconfig->muonMomIDUp = (sysflag=="MuonMomIDUp" ? true : false);
  sysconfig->muonMomIDDown = (sysflag=="MuonMomIDDown" ? true : false);
  sysconfig->muonMomScaleUp = (sysflag=="MuonMomScaleUp" ? true : false);
  sysconfig->muonMomScaleDown = (sysflag=="MuonMomScaleDown" ? true : false);
  sysconfig->electronEffRecoUp = (sysflag=="ElectronEffRecoUp" ? true : false);
  sysconfig->electronEffRecoDown = (sysflag=="ElectronEffRecoDown" ? true : false);
  sysconfig->electronEffIDUp = (sysflag=="ElectronEffIDUp" ? true : false);
  sysconfig->electronEffIDDown = (sysflag=="ElectronEffIDDown" ? true : false);
  sysconfig->electronEnergyScaleZeeStat = (sysflag == "ElectronEnergyScaleZeeStat" ? true : false);
  sysconfig->electronEnergyScaleZeeMeth = (sysflag == "ElectronEnergyScaleZeeMeth" ? true : false);
  sysconfig->electronEnergyScaleZeeGen = (sysflag == "ElectronEnergyScaleZeeGen" ? true : false);
  sysconfig->electronEnergyScaleMaterial = (sysflag == "ElectronEnergyScaleMaterial" ? true : false);
  sysconfig->electronEnergyScalePresampler = (sysflag == "ElectronEnergyScalePresampler" ? true : false);
  sysconfig->electronEnergyScaleLowPt = (sysflag == "ElectronEnergyScaleLowPt" ? true : false);
  sysconfig->electronEnergySmearingUp = (sysflag == "ElectronEnergySmearingUp" ? true : false);
  sysconfig->electronEnergySmearingDown = (sysflag == "ElectronEnergySmearingDown" ? true : false);
  sysconfig->missingEtSoftTermsScaleUp = (sysflag == "MissingEtSoftTermsScaleUp" ? true: false);
  sysconfig->missingEtSoftTermsScaleDown = (sysflag == "MissingEtSoftTermsScaleDown" ? true : false);
  sysconfig->missingEtSoftTermsResoUp = (sysflag == "MissingEtSoftTermsResoUp" ? true : false);
  sysconfig->missingEtSoftTermsResoDown = (sysflag == "MissingEtSoftTermsResoDown" ? true : false);
  */



  alg->m_pSystematics = sysconfig; //getSystematicsConfiguration(sysflag);

  while(alg->m_pSystematics->next()){
  	  TString var = alg->m_pSystematics->getCurrentSystematic();
	  //alg->m_hElectronSelectorTools[var] = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool",ele_config.c_str()));
	  alg->addObjectSelector("Electron" ,static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool",ele_config.c_str())), var);
	  alg->addObjectSelector("ElectronNoQuality" ,static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","HW_NoQuality_NoPtReq")), var);
	  alg->addObjectSelector("MuonNoQuality",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","HW_NoQuality_NoPtReq")),var);
	  alg->addObjectSelector("ElectronLoose" ,static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Loose")), var);
	  alg->addObjectSelector("MuonLoose",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Loose")),var);
	  alg->addObjectSelector("Muon",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool",mu_config.c_str())),var);
	  alg->addObjectSelector("Tau",static_cast<wwwAnalysis::TTauSelectorTool*>(ConfigureTool("TTauSelectorTool","Medium")),var);
	  alg->addObjectSelector("Jet",static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Medium")),var);
	//  alg->m_hFakeElectronSelectorTool=fakeElectronSelectorTool;
	//  alg->m_hFakeMuonSelectorTool=fakeMuonSelectorTool;
	  alg->addObjectSelector("TauElectron",static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Loose")),var);
	  alg->addObjectSelector("TauMuon",static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","StacoLoose")),var);
	  alg->addObjectSelector("JetLoose",static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Loose")),var);
  //wwwAnalysis::TElectronSelectorTool* electronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Medium"));

//  wwwAnalysis::TElectronSelectorTool* fakeElectronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Fake"));
//  wwwAnalysis::TMuonSelectorTool* fakeMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Fake"));

  //wwwAnalysis::TMuonSelectorTool* tauMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Loose"));
  }

  alg->saveTruthInfo(false);

  //char *evconfig;
  char *evconfig = strtok(event_config.c_str(),",");
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
 		//alg->addEventSelector(evname.c_str(),static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool",evname_full.c_str())),true);
 	//alg->addEventSelector("SFOS",static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool","Preselection_SFOS")),true);
	evconfig = strtok(NULL,",");
  }
 	//alg->addEventSelector("SFOS",static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool","Preselection")),true);
 	//alg->addEventSelector("SFOS",static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool","Preselection_SFOS")),true);
 

  //configure jet cleaning
  TString jetcleaning_path = path+"/../JetSelectorTools/python/ConfiguredTJetCleaningTools.py";
  TPython::LoadMacro(jetcleaning_path.Data());
  alg->m_hJetCleaningTool = static_cast<Root::TJetCleaningTool*>((void*)TPython::Eval("ConfiguredTJetCleaningTool_VeryLoose()"));

  alg->m_hPileupTool=new Root::TPileupReweighting("PURWTOOL");
  alg->m_hPileupTool->AddConfigFile((path+"/pileup/my_PileUpReweighting_mc12a.root").Data());
  //alg->m_hPileupTool->AddConfigFile((path+"/pileup/MC12_SMEW_prw_v10.root").Data());
  //alg->m_hPileupTool->AddConfigFile((path+"/pileup/mc12a_defaults.prw.root").Data());
  alg->m_hPileupTool->SetDataScaleFactors(1/1.09);
  //alg->m_hPileupTool->AddLumiCalcFile((path+"/pileup/ilumicalc_histograms_None_200842-215643.root").Data());
  alg->m_hPileupTool->AddLumiCalcFile((path+"/pileup/ilumicalc_histograms_None_200842-215643_v4.root").Data());
//  alg->m_hPileupTool->AddLumiCalcFile((path+"/pileup/ilumicalc_histograms_None_200842-210308.root").Data());
  alg->m_hPileupTool->SetUnrepresentedDataAction(2);

  alg->m_hPileupToolUp=new Root::TPileupReweighting("PURWTOOLUP");
  alg->m_hPileupToolUp->AddConfigFile((path+"/pileup/my_PileUpReweighting_mc12a.root").Data());
  alg->m_hPileupToolUp->SetDataScaleFactors(1.1/1.09);
  alg->m_hPileupToolUp->AddLumiCalcFile((path+"/pileup/ilumicalc_histograms_None_200842-215643_v4.root").Data());
  alg->m_hPileupToolUp->SetUnrepresentedDataAction(2);

  alg->m_hPileupToolDown=new Root::TPileupReweighting("PURWTOOLDOWN");
  alg->m_hPileupToolDown->AddConfigFile((path+"/pileup/my_PileUpReweighting_mc12a.root").Data());
  alg->m_hPileupToolDown->SetDataScaleFactors(0.9/1.09);
  alg->m_hPileupToolDown->AddLumiCalcFile((path+"/pileup/ilumicalc_histograms_None_200842-215643_v4.root").Data());
  alg->m_hPileupToolDown->SetUnrepresentedDataAction(2);

  alg->m_hPileupWriteTool=new Root::TPileupReweighting("www_pileup_config");
  alg->m_hPileupWriteTool->UsePeriodConfig("MC12b");


  alg->m_hTriggerTool = new wwwAnalysis::TriggerTool();
//  wwwAnalysis::XSecTool::CrossSections = wwwAnalysis::XSecTool::defaultCrossSections();
//  wwwAnalysis::XSecTool::defaultCrossSections();
//  wwwAnalysis::XSecTool::normalizeCrossSections(sh);
//  wwwAnalysis::XSecTool::addHybrid_ttbar(105200,110001);
  //alg->m_hSampleHandler = &sh;
  //alg->m_hXSecTool = new wwwAnalysis::XSecTool();
  alg->m_bHybrid = true;
//	alg->m_hBJetScalingTool = new Analysis::CalibrationDataInterfaceROOT("MV1",(path+"/Run/BTagCalibration.env").Data(),(path+"/Run/").Data());

  // Read the GRL.  if you don't have AFS on your local machine, copy
  // the file over and change the path accordingly.
/*
  alg->m_hGoodRunsListReader = new Root::TGoodRunsListReader();
  alg->m_hGoodRunsListReader->SetXMLFile((std::string(getenv("ROOTCOREDIR"))+"/../wwwAnalysis/GRL/data12_8TeV.periodAllYear_DetStatus-v58-pro14-01_DQDefects-00-00-33_PHYS_StandardGRL_All_Good.xml"));
  alg->m_hGoodRunsListReader->Interpret();
	alg->m_oGoodRunsList = alg->m_hGoodRunsListReader->GetMergedGoodRunsList();
*/
  job.algsAdd(alg);
  EL::DirectDriver driver;
  //EL::ProofDriver driver;
  //driver.numWorkers=30;

  driver.submit(job, submit);
}
