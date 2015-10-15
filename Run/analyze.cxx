#include <map>
#include <iostream>

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
void analyze(const std::string &submit,const std::string &scandir="")
{
  gSystem->Load("libPhysics");
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

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
  std::string source = getSource(sh[i]->name());
        if(source.find("embedding") != string::npos)sh[i]->meta()->setDouble("nc_isembedding",double(1));
        else sh[i]->meta()->setDouble("nc_isembedding",double(-1));
  }
  job.sampleHandler(sh);
	job.options()->setDouble(EL::Job::optCacheLearnEntries, 500);
  wwwAnalysis::Analysis *alg = new wwwAnalysis::Analysis();
  //wwwAnalysis::TElectronSelectorTool* electronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Medium"));
  wwwAnalysis::TElectronSelectorTool* electronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Tight"));
  wwwAnalysis::TMuonSelectorTool* muonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","ThirdMuTight"));
  //wwwAnalysis::TMuonSelectorTool* muonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Tight"));
  wwwAnalysis::TTauSelectorTool* tauSelectorTool = static_cast<wwwAnalysis::TTauSelectorTool*>(ConfigureTool("TTauSelectorTool","Medium"));
  wwwAnalysis::TJetSelectorTool* jetSelectorTool = static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Medium"));

//  wwwAnalysis::TElectronSelectorTool* fakeElectronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Fake"));
//  wwwAnalysis::TMuonSelectorTool* fakeMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Fake"));

  wwwAnalysis::TElectronSelectorTool* tauElectronSelectorTool = static_cast<wwwAnalysis::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Loose"));
  wwwAnalysis::TMuonSelectorTool* tauMuonSelectorTool = static_cast<wwwAnalysis::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","StacoLoose"));
  std::cout << "before jetloose"<<std::endl;
  wwwAnalysis::TJetSelectorTool* jetLooseSelectorTool = static_cast<wwwAnalysis::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Loose"));
  std::cout << "before event"<<std::endl;

  wwwAnalysis::TEventSelectorTool* eventSelectorTool_SFOS = static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool","Preselection_SFOS"));
  wwwAnalysis::TEventSelectorTool* eventSelectorTool_NoSFOS = static_cast<wwwAnalysis::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool","Preselection_NoSFOS"));
  std::cout << "after event"<<std::endl;
  


  // Tell our analysis to use this selector.
  TString path = "$ROOTCOREBIN/../wwwAnalysis";
  gSystem->ExpandPathName (path);

  alg->m_hElectronSelectorTool=electronSelectorTool;
  alg->m_hMuonSelectorTool=muonSelectorTool;
  alg->m_hTauSelectorTool=tauSelectorTool;
  alg->m_hJetSelectorTool=jetSelectorTool;

//  alg->m_hFakeElectronSelectorTool=fakeElectronSelectorTool;
//  alg->m_hFakeMuonSelectorTool=fakeMuonSelectorTool;

  alg->m_hTauElectronSelectorTool=tauElectronSelectorTool;
  alg->m_hTauMuonSelectorTool=tauMuonSelectorTool;
  alg->m_hJetLooseSelectorTool=jetLooseSelectorTool;

  alg->addEventSelector("SFOS",eventSelectorTool_SFOS,true);
  alg->addEventSelector("NoSFOS",eventSelectorTool_NoSFOS,true);
 

  //configure jet cleaning
  TString jetcleaning_path = path+"/../JetSelectorTools/python/ConfiguredTJetCleaningTools.py";
  TPython::LoadMacro(jetcleaning_path.Data());
  alg->m_hJetCleaningTool = static_cast<Root::TJetCleaningTool*>((void*)TPython::Eval("ConfiguredTJetCleaningTool_VeryLoose()"));

  alg->m_hPileupTool=new Root::TPileupReweighting("PURWTOOL");
  alg->m_hPileupTool->SetDataScaleFactors(1/1.11);
  alg->m_hPileupTool->AddConfigFile((path+"/pileup/my_PileUpReweighting_mc12a.root").Data());
  alg->m_hPileupTool->AddLumiCalcFile((path+"/pileup/ilumicalc_histograms_None_200842-215643.root").Data());
//  alg->m_hPileupTool->AddLumiCalcFile((path+"/pileup/ilumicalc_histograms_None_200842-210308.root").Data());
  alg->m_hPileupTool->SetUnrepresentedDataAction(2);
  alg->m_hTriggerTool = new wwwAnalysis::TriggerTool();
//  wwwAnalysis::XSecTool::CrossSections = wwwAnalysis::XSecTool::defaultCrossSections();
//  wwwAnalysis::XSecTool::defaultCrossSections();
//  wwwAnalysis::XSecTool::normalizeCrossSections(sh);
//  wwwAnalysis::XSecTool::addHybrid_ttbar(105200,110001);
  alg->m_hSampleHandler = &sh;
  alg->m_hXSecTool = new wwwAnalysis::XSecTool();
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
