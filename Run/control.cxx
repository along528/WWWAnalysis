void control(const char *in, const char *out, const char *norms)
{
  gSystem->Load("libPhysics");
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  EL::Job job;

  Htautau::Recalculate *generator = new Htautau::Recalculate();
	generator->m_bControlPlots = true;
	generator->m_bRecalculate = true;
//	generator->m_bCalculateMMC = true;
	generator->m_bRecalculateWeights = true;
//	generator->m_bSkim = true;
//	generator->m_bVBFSkim = true;
//	generator->m_bBoostedSkim = true;
//	generator->m_bVHSkim = true;
//	generator->m_b1JetSkim = true;
//	generator->m_b0JetSkim = true;

  TFile *file = new TFile(norms);
  if(!file->IsZombie())
  {
    TH1 *fnh = 0;
    TH1 *dfnh = 0;
    TH1 *tnh = 0;
    TH1 *znh = 0;
    TH1 *zttnh = 0;
    TH1 *dbnh = 0;
    file->GetObject("fakenorms",fnh);
    file->GetObject("difakenorms",dfnh);
    file->GetObject("topnorms",tnh);
    file->GetObject("zllnorms",znh);
    file->GetObject("ztautaunorms",zttnh);
    file->GetObject("dibosonnorms",dbnh);
    for(int i = 0; i < 4; i++)
    {
    	for(int j = 0; j < 2; j++)
    	{
    	for(int b = 0; b < 2; b++)
    	{
    		generator->m_fFakeNorm[b][j][i] = fnh->GetBinContent(i+1,j+1,b+1);
    		generator->m_fDiFakeNorm[b][j][i] = dfnh->GetBinContent(i+1,j+1,b+1);
    		generator->m_fTopNorm[b][j][i] = tnh->GetBinContent(i+1,j+1,b+1);
    		generator->m_fZllNorm[b][j][i] = znh->GetBinContent(i+1,j+1,b+1);
    		generator->m_fZtautauNorm[b][j][i] = zttnh->GetBinContent(i+1,j+1,b+1);
    		generator->m_fDibosonNorm[b][j][i] = dbnh->GetBinContent(i+1,j+1,b+1);
    		generator->m_fFakeNormErr[b][j][i] = fnh->GetBinError(i+1,j+1,b+1);
    		generator->m_fDiFakeNormErr[b][j][i] = dfnh->GetBinError(i+1,j+1,b+1);
    		generator->m_fTopNormErr[b][j][i] = tnh->GetBinError(i+1,j+1,b+1);
    		generator->m_fZllNormErr[b][j][i] = znh->GetBinError(i+1,j+1,b+1);
    		generator->m_fZtautauNormErr[b][j][i] = zttnh->GetBinError(i+1,j+1,b+1);
    		generator->m_fDibosonNormErr[b][j][i] = dbnh->GetBinError(i+1,j+1,b+1);
    	}
      }
    }
  }
  else
  {
    for(int i = 0; i < 4; i++)
    {
    	for(int j = 0; j < 2; j++)
    	{
        for(int b = 0; b < 2; b++)
        {
    		generator->m_fFakeNorm[b][j][i] = 0;
    		generator->m_fDiFakeNorm[b][j][i] = 0;
    		generator->m_fTopNorm[b][j][i] = 1;
    		generator->m_fZllNorm[b][j][i] = 1;
    		generator->m_fZtautauNorm[b][j][i] = 1;
    		generator->m_fDibosonNorm[b][j][i] = 1;
    		generator->m_fFakeNormErr[b][j][i] = 0;
    		generator->m_fDiFakeNormErr[b][j][i] = 0;
    		generator->m_fTopNormErr[b][j][i] = 0;
    		generator->m_fZllNormErr[b][j][i] = 0;
    		generator->m_fZtautauNormErr[b][j][i] = 0;
    		generator->m_fDibosonNormErr[b][j][i] = 0;
        }
    	}
    }
  }
  job.options()->setDouble(EL::Job::optCacheLearnEntries, 500);
  job.algsAdd(generator);

  SH::SampleHandler sh;
  SH::SampleLocal *sample = new SH::SampleLocal("sample");
  sample->add(in);
  sh.add(sample);
  sh.setMetaString("nc_tree","physics");
  sh.print();
  job.sampleHandler(sh);
  
  EL::DirectDriver driver;
//  EL::ProofDriver driver;
  driver.numWorkers=20;
  driver.submit(job, out);
}
