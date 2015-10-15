void *ConfigureTool(const std::string &tool, const std::string &level)
{
  TString path = "$ROOTCOREBIN/python/Htautau_leplep_Analysis/Configured"+tool+"s.py";
  gSystem->ExpandPathName (path);
  TPython::LoadMacro (path.Data());
  std::cout << path << std::endl;
  return (void*)TPython::Eval(("Configured"+tool+"_"+level+"()").c_str());
}

void RunTest (const std::string& submitDir)
{
	// Load the libraries for all packages
	gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

	// create a new sample handler to describe the data files we use
	SH::SampleHandler sh;

	// scan for datasets in the given directory
	// this works if you are on lxplus, otherwise you'd want to copy over files
	// to your local machine and use a local path.
	//SH::scanDir (sh, "/afs/cern.ch/atlas/project/PAT/data/D3PD/");
	SH::scanDir (sh,"/afs/cern.ch/work/d/dellasta/Htautau_leplep/MyFiles/");

	// set the name of the tree in our files
	//sh.setMetaString ("nc_tree", "MyFirstD3PD");
	sh.setMetaString ("nc_tree", "physics");

	// further sample handler configuration may go here

	// print out the samples we found
	sh.print ();

	// this is the basic description of our job
	EL::Job job;
	job.sampleHandler (sh);

	// add our algorithm to the job
	Analysis *alg = new Analysis;


	// later on we'll add some configuration options for our algorithm that go here
	
	// *** Object selectors *************************************
	Root::TElectronSelectorTool* electronSelectorTool = static_cast<Root::TElectronSelectorTool*>(ConfigureTool("TElectronSelectorTool","Medium"));
	Root::TMuonSelectorTool* muonSelectorTool = static_cast<Root::TMuonSelectorTool*>(ConfigureTool("TMuonSelectorTool","Medium"));
	Root::TTauSelectorTool* tauSelectorTool = static_cast<Root::TTauSelectorTool*>(ConfigureTool("TTauSelectorTool","Medium"));
	Root::TJetSelectorTool* jetSelectorTool = static_cast<Root::TJetSelectorTool*>(ConfigureTool("TJetSelectorTool","Medium"));

	alg->m_hElectronSelectorTool = electronSelectorTool;
	alg->m_hMuonSelectorTool = muonSelectorTool;
	alg->m_hTauSelectorTool = tauSelectorTool;
	alg->m_hJetSelectorTool = jetSelectorTool;


	// *** GRL **************************************************
	Root::TGoodRunsListReader* grlReader = new Root::TGoodRunsListReader();
	grlReader->SetXMLFile ("../GRL/data11_7TeV.periodAllYear_DetStatus-v36-pro10_CoolRunQuery-00-04-08_All_Good.xml");
	grlReader->Interpret ();

	alg->m_oGoodRunsList = grlReader->GetMergedGoodRunsList();

	
	
	
	// after this line, do not configure anything!!
	job.algsAdd(alg);

	// make the driver we want to use:
	// this one works by running the algorithm directly
	EL::DirectDriver driver;

	// process the job using the driver
	driver.submit (job, submitDir);

	// Fetch and plot our histogram... Note that "AHist" is the name of
	// the histogram and that "data..." is the name of the sample
	// this is mostly for show, in a real analysis you would likely do this in a separate macro.
}
