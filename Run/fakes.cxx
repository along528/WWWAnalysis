//void fakes(const char *, const char *, double=13);

void fakes(const char *in, const char *out)
{
  gSystem->Load("libPhysics");
  gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");

  EL::Job job;

  Htautau::NormalizeFakes *generator = new Htautau::NormalizeFakes();
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
//  driver.numWorkers=1;
  driver.submit(job, out);
}
