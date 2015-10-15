void mva(const char *in, const char *out)
{
  gSystem->Load("libPhysics");
  gSystem->Load("libTMVA");
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");
  
  TFile *infile = new TFile(in);
//  TFile *bgfile = new TFile(bg);
  TFile *outfile = new TFile(out,"recreate");
  TTree *tree = 0;
//  TTree *background = 0;
//  infile->GetObject("physics_VBF_MVA",tree);
  infile->GetObject("physics",tree);
  
  TCut signalcut("Truth_initial > 0 && Truth_initial < 16 && Truth_final == 1");
  TCut backgroundcut("Truth_final != 1 || Truth_initial > 12");
  TCut pass("Truth_initial != 0");
  TCut vbf("PassCut7 && deltaeta_jj >= 2.2 && pt_H < 100000");
  TCut vh("PassCut7 && deltaeta_jj < 2.2 && pt_H < 100000");
  TCut boosted("PassCut6 && !PassCut7 && pt_H > 100000");
  TCut jet1("PassCut3 && !PassCut7 && pt_H < 100000");
//  TCut jet0("");
  m_pFactory = new TMVA::Factory("HtautauMVA", outfile, "V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");
  m_pFactory->SetInputTrees(tree, signalcut && pass && jet1, backgroundcut && pass && jet1);
//  m_pFactory->AddTree(signal, "Signal", 1.0, TCut(""), TMVA::Types::kMaxTreeType);
//  m_pFactory->AddTree(background, "Background", 1.0, TCut(""), TMVA::Types::kMaxTreeType);
  
	/* MIKE's training */
/*
  m_pFactory->AddVariable("lep1_momentum.fE",'F');
  m_pFactory->AddVariable("lep1_pt",'F');
  m_pFactory->AddVariable("lep1_eta",'F');
  m_pFactory->AddVariable("lep1_phi",'F');
  m_pFactory->AddVariable("lep1_tight",'F');
  m_pFactory->AddVariable("lep1_isMuon",'F');
  
  m_pFactory->AddVariable("lep2_momentum.fE",'F');
  m_pFactory->AddVariable("lep2_pt",'F');
  m_pFactory->AddVariable("lep2_eta",'F');
  m_pFactory->AddVariable("lep2_phi",'F');
  m_pFactory->AddVariable("lep2_tight",'F');
  m_pFactory->AddVariable("lep2_isMuon",'F');
  
  m_pFactory->AddVariable("jet1_momentum.fE",'F');
  m_pFactory->AddVariable("jet1_pt",'F');
  m_pFactory->AddVariable("jet1_eta",'F');
  m_pFactory->AddVariable("jet1_phi",'F');
  m_pFactory->AddVariable("jet2_momentum.fE",'F');
  m_pFactory->AddVariable("jet2_pt",'F');
  m_pFactory->AddVariable("jet2_eta",'F');
  m_pFactory->AddVariable("jet2_phi",'F');
  
  m_pFactory->AddVariable("MET_final_Et",'F');
  m_pFactory->AddVariable("MET_final_phi",'F');
  
  m_pFactory->AddVariable("MET_HPTO_Et",'F');
  m_pFactory->AddVariable("MET_HPTO_phi",'F');
//  m_pFactory->AddVariable("MET_mmc_Et",'F');
//  m_pFactory->AddVariable("MET_mmc_phi",'F');
//  m_pFactory->AddVariable("mass_mmc",'F');
  m_pFactory->AddVariable("mass_likely",'F');
  m_pFactory->AddVariable("mass_ll",'F'); //Decorrelate ERROR HERE
  m_pFactory->AddVariable("mass_jj",'F'); //Decorrelate ERROR HERE
  m_pFactory->AddVariable("pt_ll",'F'); //Decorrelate ERROR HERE
  m_pFactory->AddVariable("deltaphi_ll",'F'); //Decorrelate ERROR HERE
  m_pFactory->AddVariable("deltaeta_jj",'F'); //Decorrelate ERROR HERE
  m_pFactory->AddVariable("lep1_x",'F');
  m_pFactory->AddVariable("lep2_x",'F');
  
  m_pFactory->AddVariable("PassVBF_final",'I');
*/

  // === Morinaga ===
  m_pFactory->AddVariable("jet1_pt",'F');
//  m_pFactory->AddVariable("jet2_pt",'F');
//  m_pFactory->AddVariable("mass_jj",'F'); 
//  m_pFactory->AddVariable("mass_Hj",'F'); 
  m_pFactory->AddVariable("deltaphi_ll",'F');
  m_pFactory->AddVariable("deltaeta_ll",'F');
//  m_pFactory->AddVariable("deltaeta_jj",'F');
//  m_pFactory->AddVariable("etaj1etaj2",'F');
//  m_pFactory->AddVariable("c1c2",'F');
  m_pFactory->AddVariable("mindeltaeta_Hj",'F');
  
	// extra
  m_pFactory->AddVariable("MET_final_Et",'F');
  m_pFactory->AddVariable("MET_final_sumEt",'F');
  m_pFactory->AddVariable("MET_HPTO_Et",'F');
//  m_pFactory->AddVariable("sphericity",'F');
  m_pFactory->AddVariable("mass_ll",'F');
  m_pFactory->AddVariable("mass_likely",'F');
  m_pFactory->AddVariable("mass_colinear",'F');
//  m_pFactory->AddVariable("lep1_centrality",'F');
//  m_pFactory->AddVariable("lep2_centrality",'F');
//  m_pFactory->AddVariable("lep1_x",'F');
//  m_pFactory->AddVariable("lep2_x",'F');
  m_pFactory->AddVariable("pt_H",'F');
  m_pFactory->AddVariable("pt_ll",'F'); 

//  m_pFactory->AddVariable("lep1_pt",'F');
//  m_pFactory->AddVariable("lep1_eta",'F');
//  m_pFactory->AddVariable("lep2_pt",'F');
//  m_pFactory->AddVariable("lep2_eta",'F');
  m_pFactory->AddVariable("jet1_eta",'F');

//  m_pFactory->AddVariable("deltaphi_metl1",'F');
//  m_pFactory->AddVariable("deltaphi_metl2",'F');
  m_pFactory->AddVariable("deltaphi_metj1",'F');
  m_pFactory->AddVariable("deltaphi_Hmet",'F');
  m_pFactory->AddVariable("deltaphi_Hj",'F');
//  m_pFactory->AddVariable("mt_H",'F');
  m_pFactory->AddVariable("mt_l1",'F');
  m_pFactory->AddVariable("mt_l2",'F');
  m_pFactory->AddVariable("mt_metll",'F');

//  m_pFactory->AddVariable("mass_colinear_HPTO",'F');
//  m_pFactory->AddVariable("mass_likely_HPTO",'F');
//  m_pFactory->AddVariable("mass_Hj_HPTO",'F');

//  m_pFactory->AddVariable("mass_mmc",'F');
//  m_pFactory->AddVariable("MET_mmc_Et",'F');
/*  
  // === Boston === + all the rest
  m_pFactory->AddVariable("lep1_momentum.fE",'F');
  m_pFactory->AddVariable("lep1_pt",'F');
  m_pFactory->AddVariable("lep1_eta",'F');
  m_pFactory->AddVariable("lep1_phi",'F');
  m_pFactory->AddVariable("lep2_momentum.fE",'F');
  m_pFactory->AddVariable("lep2_pt",'F');
  m_pFactory->AddVariable("lep2_eta",'F');
  m_pFactory->AddVariable("lep2_phi",'F');
  m_pFactory->AddVariable("jet1_momentum.fE",'F');
  m_pFactory->AddVariable("jet1_pt",'F');
  m_pFactory->AddVariable("jet1_eta",'F');
  m_pFactory->AddVariable("jet1_phi",'F');
  m_pFactory->AddVariable("jet2_momentum.fE",'F');
  m_pFactory->AddVariable("jet2_pt",'F');
  m_pFactory->AddVariable("jet2_eta",'F');
  m_pFactory->AddVariable("jet2_phi",'F');
  m_pFactory->AddVariable("MET_final_Et",'F');
  m_pFactory->AddVariable("MET_final_phi",'F');
  m_pFactory->AddVariable("MET_HPTO_Et",'F');
  m_pFactory->AddVariable("MET_HPTO_phi",'F');
  
  // === Boston === + pt_Higgs
  m_pFactory->AddVariable("pt_ll",'F'); 
  
*/
  m_pFactory->SetWeightExpression("weight_all");
  
  m_pFactory->PrepareTrainingAndTestTree(TCut(""),TCut(""),"nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:V");
  

/*
      m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT",
                           "H:V:NTrees=850:nEventsMin=150:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
      m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT_lh",
                           "H:V:NTrees=850:nEventsMin=150:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
*/

  // BDT
  m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT1", "H:V:NTrees=500:nEventsMin=75:BoostType=Grad:Shrinkage=0.05:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=30:MaxDepth=5:CreateMVAPdfs");

  m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT2", "H:V:NTrees=1000:nEventsMin=250:BoostType=Grad:Shrinkage=0.05:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=30:MaxDepth=4:CreateMVAPdfs");

  m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT3", "H:V:NTrees=2000:nEventsMin=250:BoostType=Grad:Shrinkage=0.05:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=30:MaxDepth=4:CreateMVAPdfs");
  m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT4", "H:V:NTrees=4000:nEventsMin=250:BoostType=Grad:Shrinkage=0.05:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=30:MaxDepth=4:CreateMVAPdfs");
  m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT5", "H:V:NTrees=4000:nEventsMin=250:BoostType=Grad:Shrinkage=0.05:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=30:MaxDepth=3:CreateMVAPdfs");

//  m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT4", "H:V:NTrees=5000:nEventsMin=100:BoostType=Grad:Shrinkage=0.05:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=30:MaxDepth=3:CreateMVAPdfs");

//  m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT4", "H:V:NTrees=100:nEventsMin=150:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.2:SeparationType=GiniIndex:nCuts=100:PruneMethod=NoPruning:CreateMVAPdfs");

//  m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT3", "H:V:UseYesNoLeaf=False:NTrees=1000:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=10:PruneMethod=CostComplexity:PruneStrength=-1:PruneBeforeBoost=True" );
//  m_pFactory->BookMethod( TMVA::Types::kBDT, "BDT4", "H:V:UseYesNoLeaf=False:NTrees=1000:MaxDepth=20:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=100:PruneMethod=CostComplexity:PruneStrength=-1:PruneBeforeBoost=True:nEventsMin=50" );

  // MLP_NN
//  m_pFactory->BookMethod( TMVA::Types::kMLP, "MLP_ANN_BP", "H:V:TrainingMethod=BP:VarTransform=Norm:NCycles=2000:HiddenLayers=50:LearningRate=0.05:DecayRate=0.008" );
//  m_pFactory->BookMethod( TMVA::Types::kMLP, "MLP_ANN", "H:V:TrainingMethod=BFGS:VarTransform=Norm:NCycles=2000:HiddenLayers=50:LearningRate=0.05:DecayRate=0.008" );
//  m_pFactory->BookMethod( TMVA::Types::kMLP, "MLP_ANN_BP", "H:V:TrainingMethod=BP:VarTransform=Norm:NCycles=10000:HiddenLayers=20:LearningRate=0.05:DecayRate=0.0007" );
//  m_pFactory->BookMethod( TMVA::Types::kMLP, "MLP_ANN", "H:V:TrainingMethod=BFGS:VarTransform=Norm:NCycles=10000:HiddenLayers=20:LearningRate=0.05:DecayRate=0.0007" );
  
  // Cuts
//  m_pFactory->BookMethod( TMVA::Types::kCuts, "Cuts", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
  //m_pFactory->BookMethod( TMVA::Types::kCuts, "CutsD", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );
  //m_pFactory->BookMethod( TMVA::Types::kCuts, "CutsPCA", "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );
  //m_pFactory->BookMethod( TMVA::Types::kCuts, "CutsGA", "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );
  //m_pFactory->BookMethod( TMVA::Types::kCuts, "CutsSA", "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );
  
  // Likelihood
  m_pFactory->BookMethod( TMVA::Types::kLikelihood, "Likelihood", "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );
  //m_pFactory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD", "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );
  m_pFactory->TrainAllMethods();
  m_pFactory->TestAllMethods();
  m_pFactory->EvaluateAllMethods();
}
