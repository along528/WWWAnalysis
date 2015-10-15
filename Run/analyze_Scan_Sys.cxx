#include <map>
#include <iostream>
#include <stdio>
#include <sstream>
#include <string>
#include <vector>


/*
wwwAnalysis::SystematicsConfig *getSystematicsConfiguration(const std::string sysflag){
	wwwAnalysis::SystematicsConfig *sysconfig = new SystematicsConfig();
	sysconfig->chargeMisIDUp = (sysflag=="ChargeMisIDUp" ? true : false);
	sysconfig->chargeMisIDDown = (sysflag=="ChargeMisIDDown" ? true : false);
	return sysconfig;
}
*/

void *ConfigureTool(const std::string &tool, const std::string &level)
{
  TString path = "$ROOTCOREBIN/python/wwwAnalysis/Configured"+tool+"s.py";
  gSystem->ExpandPathName (path);
  TPython::LoadMacro (path.Data());
  return (void*)TPython::Eval(("Configured"+tool+"_"+level+"()").c_str());
}
void *ConfigureToolScan(const std::string &tool, const std::string &level,
						 const std::string &nsfos,
						 const std::string &pt1min,
						 const std::string &pt2min,
						 const std::string &pt3min,
						 const std::string &mt1min,
						 const std::string &mt2min,
						 const std::string &mt3min,
						 const std::string &metmin)
{
  TString path = "$ROOTCOREBIN/python/wwwAnalysis/Configured"+tool+"s.py";
  gSystem->ExpandPathName (path);
  TPython::LoadMacro (path.Data());
  std::cout << "Configured"+tool+"_"+level+"("+
  		nsfos+","+ pt1min+","+ pt2min+","+ pt3min+","+
		mt1min+","+ mt2min+","+ mt3min+","+ metmin +")"<<std::endl;
  return (void*)TPython::Eval(("Configured"+tool+"_"+level+"("+
  		nsfos+","+ pt1min+","+ pt2min+","+ pt3min+","+ 
		mt1min+","+ mt2min+","+ mt3min+","+ metmin +")").c_str());
}
std::string getSource(const std::string &ds)
{
	return ds.substr(0, ds.find("NTUP_TAU"));
}
void analyze_Scan_Sys(const std::string &ele_config, const std::string &mu_config, const std::string &eventconfig,const std::string &submit,const std::string &scandir="",const std::string &sysflag="")
{
  gSystem->Load("libPhysics");
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");
  //gROOT->ProcessLine(".L $ROOTCOREDIR/../wwwAnalysis/wwwAnalysis.h+");
  //gROOT->ProcessLine(".L /home/graduate/along528/analysis/www/wwwAnalysis/wwwAnalysis/SystematicsConfig.h+")

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
  sysconfig->chargeMisIDUp = (sysflag=="ChargeMisIDUp" ? true : false);
  sysconfig->chargeMisIDDown = (sysflag=="ChargeMisIDDown" ? true : false);

  alg->m_pSystematics = sysconfig; //getSystematicsConfiguration(sysflag);
  std::cout << 5 << std::endl;

  alg->m_hElectronSelectorTool=electronSelectorTool;
  alg->m_hMuonSelectorTool=muonSelectorTool;
  alg->m_hTauSelectorTool=tauSelectorTool;
  alg->m_hJetSelectorTool=jetSelectorTool;

//  alg->m_hFakeElectronSelectorTool=fakeElectronSelectorTool;
//  alg->m_hFakeMuonSelectorTool=fakeMuonSelectorTool;

  alg->m_hTauElectronSelectorTool=tauElectronSelectorTool;
  alg->m_hTauMuonSelectorTool=tauMuonSelectorTool;
  alg->m_hJetLooseSelectorTool=jetLooseSelectorTool;
    std::cout<<  eventconfig <<std::endl;
    std::string eventconfigs [200] ;
    int nconfigs=0;
    char *evconfig = strtok(eventconfig.c_str(),";");
      while(evconfig!=NULL){
	std::string evconfig_string = evconfig;
	eventconfigs[nconfigs]=evconfig_string;
	nconfigs++;
	evconfig = strtok(NULL,";");
      }


    for(int j=0;j<nconfigs;j++){
	char *evargs = strtok(eventconfigs[j].c_str(),",");
	int count=0;
	std::string args [9];
	while(evargs!=NULL){
	   std::string arg = evargs;
	   args[count] = arg;
	   count+=1;
	   evargs = strtok(NULL,",");
	}
	std::string evname = args[0];
	/*
	std::string evname_full = evname;
	std::string searchTerm = "Baseline_";
	if (evname.find(searchTerm.c_str())!=std::string::npos){
		evname.replace(evname.find("Baseline_"),searchTerm.length(),"");
	}
	*/

	std::string nsfos = args[1];
	std::string pt1min = args[2];
	std::string pt2min = args[3];
	std::string pt3min = args[4];
	std::string mt1min = args[5];
	std::string mt2min = args[6];
	std::string mt3min = args[7];
	std::string metmin = args[8];
	//std::cout << (evname+"_SFOS"+nsfos+"_Pt"+pt1min+pt2min+pt3min+"_Mt"+mt1min+mt2min+mt3min+"_Met"+metmin).c_str() << std::endl;
	alg->addEventSelector(("Preselection_Scan_"+evname+"_SFOS"+nsfos+"_Pt"+pt1min+pt2min+pt3min+"_Mt"+mt1min+mt2min+mt3min+"_Met"+metmin).c_str(),static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureToolScan("TEventSelectorTool",("Baseline_Preselection_Scan_"+evname).c_str(),
					nsfos.c_str(),
					pt1min.c_str(),
					pt2min.c_str(),
					pt3min.c_str(),
					mt1min.c_str(),
					mt2min.c_str(),
					mt3min.c_str(),
					metmin.c_str()
					)),true);
    }

								 	//alg->addEventSelector("SFOS",static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool","Preselection_SFOS")),true);
									//	evconfig = strtok(NULL,",");
									//	  }
									//


 	//alg->addEventSelector("SFOS",static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool","Preselection")),true);
 	//alg->addEventSelector("SFOS",static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool","Preselection_SFOS")),true);
 

  //configure jet cleaning
  TString jetcleaning_path = path+"/../JetSelectorTools/python/ConfiguredTJetCleaningTools.py";
  TPython::LoadMacro(jetcleaning_path.Data());
  alg->m_hJetCleaningTool = static_cast<Root::TJetCleaningTool*>((void*)TPython::Eval("ConfiguredTJetCleaningTool_VeryLoose()"));

  alg->m_hPileupTool=new Root::TPileupReweighting("PURWTOOL");
  alg->m_hPileupTool->SetDataScaleFactors(1/1.11);
  alg->m_hPileupTool->AddConfigFile((path+"/pileup/sm_ew_www.prw.root").Data());
  alg->m_hPileupTool->AddLumiCalcFile((path+"/pileup/sm_ew_ilumicalc.root").Data());
//  alg->m_hPileupTool->AddLumiCalcFile((path+"/pileup/ilumicalc_histograms_None_200842-210308.root").Data());
  alg->m_hPileupTool->SetUnrepresentedDataAction(2);
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
  //EL::DirectDriver driver;
  EL::ProofDriver driver;
  driver.numWorkers=30;

  driver.submit(job, submit);
}
