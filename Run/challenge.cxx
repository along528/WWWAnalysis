void *ConfigureTool(const std::string &tool, const std::string &level)
{
  TString path = "$ROOTCOREBIN/python/Htautau_leplep_Analysis/Configured"+tool+"s.py";
  gSystem->ExpandPathName (path);
  TPython::LoadMacro (path.Data());
  std::cout << path << std::endl;
  return (void*)TPython::Eval(("Configured"+tool+"_"+level+"()").c_str());
}

void challenge(const std::string &submit, const std::string &analysis)
{
  gSystem->Load("libPhysics");
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");
  SH::SampleHandler sh;
  SH::scanDir(sh,"../../data"); //M.Kruskal
//  SH::scanDir(sh,"../../../Htautau_leplep/MyFiles/MC"); //
//  SH::scanDir(sh,"../../../Htautau_leplep/NewAcceptance/MC"); //
  sh.setMetaString("nc_tree","tau");
  sh.print();
  EL::Job job;
  job.sampleHandler(sh);
  Htautau::Analysis *alg = new Htautau::Analysis();
/*
  TString path = "$ROOTCOREBIN/python/Htautau_leplep_Analysis/ConfiguredTElectronSelectorTools.py";
  gSystem->ExpandPathName (path);
  TPython::LoadMacro (path.Data());
  Root::TElectronSelectorTool* electronSelectorTool = static_cast<Root::TElectronSelectorTool*>((void*)TPython::Eval("ConfiguredTElectronSelectorTool_Medium()"));
  path = "$ROOTCOREBIN/python/Htautau_leplep_Analysis/ConfiguredTMuonSelectorTools.py";
  gSystem->ExpandPathName (path);
  TPython::LoadMacro (path.Data());
  Root::TMuonSelectorTool* muonSelectorTool = static_cast<Root::TMuonSelectorTool*>((void*)TPython::Eval("ConfiguredTMuonSelectorTool_Medium()"));
*/
  Htautau::TElectronSelectorTool* electronSelectorTool = static_cast<Htautau::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Medium"));
  Htautau::TMuonSelectorTool* muonSelectorTool = static_cast<Htautau::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Tight"));
  Htautau::TElectronSelectorTool* tauElectronSelectorTool = static_cast<Htautau::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Loose"));
  Htautau::TMuonSelectorTool* tauMuonSelectorTool = static_cast<Htautau::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Loose"));
  Htautau::TTauSelectorTool* tauSelectorTool = static_cast<Htautau::TTauSelectorTool*>(ConfigureTool("TTauSelectorTool","Medium"));
  Htautau::TJetSelectorTool* jetSelectorTool = static_cast<Htautau::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Medium"));
  Htautau::TJetSelectorTool* jetLooseSelectorTool = static_cast<Htautau::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Loose"));
  Htautau::TEventSelectorTool* minSelectorTool = static_cast<Htautau::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool","Min"));
  Htautau::TEventSelectorTool* eventSelectorTool = static_cast<Htautau::TEventSelectorTool*>(ConfigureTool("TEventSelectorTool",analysis.c_str()));

  // Tell our analysis to use this selector.
  alg->m_hElectronSelectorTool=electronSelectorTool;
  alg->m_hMuonSelectorTool=muonSelectorTool;
  alg->m_hTauElectronSelectorTool=tauElectronSelectorTool;
  alg->m_hTauMuonSelectorTool=tauMuonSelectorTool;
  alg->m_hTauSelectorTool=tauSelectorTool;
  alg->m_hJetSelectorTool=jetSelectorTool;
  alg->m_hJetLooseSelectorTool=jetLooseSelectorTool;
  alg->m_hEventSelectorTool=eventSelectorTool;
  alg->m_hVBFSelectorTool=minSelectorTool;
  alg->m_hVBFMVASelectorTool=minSelectorTool;
  alg->m_hVBFSelectorTool=minSelectorTool;
  alg->m_hBoostedSelectorTool=minSelectorTool;
  alg->m_hVHSelectorTool=minSelectorTool;
  alg->m_hN1JETSelectorTool=minSelectorTool;
  alg->m_hN0JETSelectorTool=minSelectorTool;
  alg->m_hPileupTool=new Root::TPileupReweighting("PURWTOOL");
  alg->m_hPileupTool->SetDataScaleFactors(1/1.11);
  alg->m_hPileupTool->AddConfigFile("../pileup/mc12a_defaults.prw.root");
  alg->m_hPileupTool->AddLumiCalcFile("../pileup/ilumicalc_histograms_None_200842-210308.root");
  alg->m_hPileupTool->SetUnrepresentedDataAction(2);
  alg->m_hTriggerTool = new Htautau::TriggerTool();
//  alg->m_hBJetScalingTool = new Analysis::CalibrationDataInterfaceROOT("MV1");

  // Read the GRL.  if you don't have AFS on your local machine, copy
  // the file over and change the path accordingly.
  Root::TGoodRunsListReader* grlR = new Root::TGoodRunsListReader();
  grlR->SetXMLFile("../GRL/data12_8TeV.periodAllYear_DetStatus-v53-pro13-04_CoolRunQuery-00-04-08_All_Good.xml");
//  grlR->AddXMLFile("../GRL/data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_All_Good.xml");
//  grlR->AddXMLFile("../GRL/data10_7TeV.periodAllYear_DetStatus-v21-pro05_CoolRunQuery-00-04-00_WZjets_allchannels.xml");
  grlR->Interpret();

  // Tell our analysis to use this GRL
  alg->m_oGoodRunsList = grlR->GetMergedGoodRunsList();

  job.algsAdd(alg);
  EL::DirectDriver driver;
  driver.submit(job, submit);
}
