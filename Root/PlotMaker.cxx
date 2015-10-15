#include "wwwAnalysis/PlotMaker.h"
#include "TH1F.h"
#include "THStack.h"
#include "TCanvas.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <algorithm>

#include "TMath.h"
#include "TLegend.h"
#include "TFile.h"
#include "TGaxis.h"
#include "TLine.h"


PlotMaker::PlotMaker(string myimagedir){
cout << "myimage: " << myimagedir << endl;
	vCategoryNames.clear();
	vCategoryColors.clear();
	vCategoryNames.push_back("none");
	vCategoryColors.push_back(kBlack);
	vSignalCategoryNames.clear();
	vSignalCategoryColors.clear();
	vSignalCategoryNames.push_back("none");
	vSignalCategoryColors.push_back(kBlack);
	
	vDataNames.clear();
	vMCNames.clear();
	vSignalNames.clear();

	vDataLabels.clear();
	vMCLabels.clear();
	vSignalLabels.clear();

	vDataFiles.clear();
	vMCFiles.clear();
	vSignalFiles.clear();

	vMCCategory.clear();
	vSignalCategory.clear();


	vMCColors.clear();
	vSignalColors.clear();
	vMCNEvents.clear();
	vSignalNEvents.clear();
	vDataNEvents.clear();
	totDataEvents=0;
	totMCEvents=0;
	totSignalEvents=0;

	imagedir=myimagedir;

	mkdirRecursive(imagedir);

	Lumi = -1.;


}

PlotMaker::~PlotMaker(){
	if(vDataFiles.size()!=0){
		for(UInt_t i=0;i<vDataFiles.size();i++)
			vDataFiles[i]->Close();
	}
	if(vMCFiles.size()!=0){
		for(UInt_t i=0;i<vMCFiles.size();i++)
			vMCFiles[i]->Close();
	}
	
	

}

void PlotMaker::AddCategory(string name,Color_t color){
	vCategoryNames.push_back(name);
	vCategoryColors.push_back(color);
}
void PlotMaker::AddSignalCategory(string name,Color_t color){
	vSignalCategoryNames.push_back(name);
	vSignalCategoryColors.push_back(color);
}

int PlotMaker::FindCategory(string name){

	for(unsigned int i=0;i<vCategoryNames.size();i++){
		if(vCategoryNames[i]==name) return i;
	}

	cout << "Couldn't Find Category!" << endl;
	return -1;

}

int PlotMaker::FindSignalCategory(string name){

	for(unsigned int i=0;i<vSignalCategoryNames.size();i++){
		if(vSignalCategoryNames[i]==name) return i;
	}

	cout << "Couldn't Find Signal Category!" << endl;
	return -1;

}


void PlotMaker::AddData(string name,string label){
	vDataNames.push_back(name);
	vDataLabels.push_back(label);
/*
	string file=basesubmitdir+"/"+name+"/plots/"+rootfilename;
	vDataFiles.push_back(new TFile(file.c_str(),"READ"));
	double nEvents = ((TH1F*)vDataFiles.back()->Get("hCutFlow"))->GetBinContent(1);
	totDataEvents+=nEvents;
	vDataNEvents.push_back(nEvents);
*/

}
void PlotMaker::AddSignal(string name,string label, string category, Color_t color){
	vSignalNames.push_back(name);
	vSignalLabels.push_back(label);
	vSignalColors.push_back(color);

	if(FindSignalCategory(category)>=0) vSignalCategory.push_back(category);
	else {
		cout << "For Signal: " << name << " there is no category: " << category << endl;
		cout << "using 'none'" << endl;
		vSignalCategory.push_back("none");
	}
/*
	string file=basesubmitdir+"/"+name+"/plots/"+rootfilename;
	vSignalFiles.push_back(new TFile(file.c_str(),"READ"));

	double nEvents = 0.0;

	nEvents = ((TH1F*)vMCFiles.back()->Get("hMCWeightSum_AfterPreSkim"))->GetBinContent(1);

	totSignalEvents+=nEvents;
	cout << name << endl;
	cout << "\t"<<nEvents << endl;
	cout << "\t"<<"hMCWeightSum: "<< 
	((TH1F*)vSignalFiles.back()->Get("hMCWeightSum"))->GetBinContent(1)
	<<" hCutFlow: " << 
	((TH1F*)vSignalFiles.back()->Get("hCutFlow"))->GetBinContent(1)
	<<" hMCWeightSum_AfterPreSkim: "<<
	((TH1F*)vSignalFiles.back()->Get("hMCWeightSum_AfterPreSkim"))->GetBinContent(1) << endl;
	vSignalNEvents.push_back(nEvents);
*/


}
void PlotMaker::AddMC(string name,string label,string category,Color_t color){
	vMCNames.push_back(name);
	vMCLabels.push_back(label);
	vMCColors.push_back(color);
	if(FindCategory(category)>=0) vMCCategory.push_back(category);
	else {
		cout << "For MC: " << name << " there is no category: " << category << endl;
		cout << "using 'none'" << endl;
		vMCCategory.push_back("none");
	}
/*
	string file=basesubmitdir+"/"+name+"/plots/"+rootfilename;
	vMCFiles.push_back(new TFile(file.c_str(),"READ"));

	double nEvents = 0.0;

	nEvents = ((TH1F*)vMCFiles.back()->Get("hMCWeightSum_AfterPreSkim"))->GetBinContent(1);

	totMCEvents+=nEvents;
	cout << name << endl;
	cout << "\t"<<nEvents << endl;
	cout << "\t"<<"hMCWeightSum: "<< 
	((TH1F*)vMCFiles.back()->Get("hMCWeightSum"))->GetBinContent(1)
	<<" hCutFlow: " << 
	((TH1F*)vMCFiles.back()->Get("hCutFlow"))->GetBinContent(1)
	<<" hMCWeightSum_AfterPreSkim: "<<
	((TH1F*)vMCFiles.back()->Get("hMCWeightSum_AfterPreSkim"))->GetBinContent(1) << endl;
	vMCNEvents.push_back(nEvents);
*/

}

vector<TH1*> PlotMaker::PrepareDataHistos(string &plotname,Int_t nbins, Double_t min, Double_t max, string weightoptions){

	//approx same as official but with lower range
	//vector<TH1*> DataHistos = RebinLog(GetDataHistos(plotname),nbins,min,max);
	vector<TH1*> DataHistos = GetDataHistos(plotname);


	return DataHistos;


}
vector<TH1*> PlotMaker::PrepareMCHistos(string &plotname,Int_t nbins, Double_t min, Double_t max, string weightoptions){
	if(weightoptions.find("K")!=string::npos) plotname+="_NoKFac";
	else if(weightoptions.find("T")!=string::npos) plotname+="_NoScaleFac";

	//approx same as official but with lower range
	//vector<TH1*> MCHistos = RebinLog(GetMCHistos(plotname),nbins,min,max);
	vector<TH1*> MCHistos = GetMCHistos(plotname);

	return MCHistos;


}
void PlotMaker::DrawStandard(string plotname, string options){
	vector<TH1*> DataHistos = GetDataHistos(plotname);
	vector<TH1*> MCHistos   = GetMCHistos(plotname);
	vector<TH1*> SignalHistos   = GetSignalHistos(plotname);
	Draw(plotname,DataHistos,MCHistos,options,SignalHistos);
}

void PlotMaker::DrawPt(string options){
	string plotname="hPt";
	
	//approx same as official but with lower range
	const int nbins=  49;
	Double_t  min  =  25.0;
	Double_t  max  =  1409.0;
	vector<TH1*> DataHistos = RebinLog(GetDataHistos(plotname),nbins,min,max);
	vector<TH1*> MCHistos = RebinLog(GetMCHistos(plotname),nbins,min,max);


	Draw(plotname,DataHistos,MCHistos,options);


}

void PlotMaker::DrawEtMiss(string options){
	string plotname="hEtMiss";

	const int nbins=  49;
	//approx same as official but with lower range
	Double_t  min  =  25.0;
	Double_t  max  =  1409.0;
	//vector<TH1*> DataHistos = PrepareDataHistos(plotname,nbins, min, max, weightoptions);
	//vector<TH1*> MCHistos = PrepareMCHistos(plotname,nbins, min, max, weightoptions);
	vector<TH1*> DataHistos = RebinLog(GetDataHistos(plotname),nbins,min,max);
	vector<TH1*> MCHistos = RebinLog(GetMCHistos(plotname),nbins,min,max);
	//vector<TH1*> DataHistos = GetDataHistos(plotname);//,nbins,min,max);
	//vector<TH1*> MCHistos = GetMCHistos(plotname);//,nbins,min,max);

//cxyl
	Draw(plotname,DataHistos,MCHistos,options);


}
void PlotMaker::DrawMt(string options){
	string plotname="hMt";
	
	const int nbins=  48;
	//approx same as official but with lower range
	Double_t  min  =  10.0;
	Double_t  max  =  1443.0;//10000.0;
	vector<TH1*> DataHistos = RebinLog(GetDataHistos(plotname),nbins,min,max);
	vector<TH1*> MCHistos = RebinLog(GetMCHistos(plotname),nbins,min,max);
	//vector<TH1*> DataHistos = GetDataHistos(plotname);//,nbins,min,max);
	//vector<TH1*> MCHistos = GetMCHistos(plotname);//,nbins,min,max);
	//vector<TH1*> DataHistos = PrepareDataHistos(plotname,nbins, min, max, weightoptions);
	//vector<TH1*> MCHistos = PrepareMCHistos(plotname,nbins, min, max, weightoptions);
//cxyl
	Draw(plotname,DataHistos,MCHistos,options);


}
void PlotMaker::DrawTruthZMass(string options){
	string plotname="hTruthZMass";

	const int nbins=  48;
	//approx same as official but with lower range
	Double_t  min  =  10.0;
	Double_t  max  =  1443.0;//10000.0;
	vector<TH1*> DataHistos ;//RebinLog(GetDataHistos(plotname),nbins,min,max);
	DataHistos.clear();
	//vector<TH1*> MCHistos   = GetMCHistos(plotname);//,nbins,min,max);
	vector<TH1*> MCHistos   = RebinLog(GetMCHistos(plotname),nbins,min,max);
	vector<TH1*> SignalHistos = vector<TH1*>();

//cxyl
	Draw(plotname,DataHistos,MCHistos,options,SignalHistos,false,.01);


}

void PlotMaker::DrawTruthWMass(string options){
	string plotname="hTruthWMass";

	const int nbins=  48;
	//approx same as official but with lower range
	Double_t  min  =  10.0;
	Double_t  max  =  1443.0;//10000.0;
	vector<TH1*> DataHistos ;//RebinLog(GetDataHistos(plotname),nbins,min,max);
	DataHistos.clear();

	vector<TH1*> MCHistos   = RebinLog(GetMCHistos(plotname),nbins,min,max);
	vector<TH1*> SignalHistos = vector<TH1*>();
	//vector<TH1*> MCHistos   = GetMCHistos(plotname);//,nbins,min,max);

//cxyl
	Draw(plotname,DataHistos,MCHistos,options,SignalHistos,false,.01);


}
void PlotMaker::DrawTruthZPt(string options){
	string plotname="hTruthZPt";

	const int nbins=  49;
	Double_t  min  =  25.0;
	Double_t  max  =  1409.0;
	vector<TH1*> DataHistos ;//RebinLog(GetDataHistos(plotname),nbins,min,max);
	DataHistos.clear();
	vector<TH1*> MCHistos   = RebinLog(GetMCHistos(plotname),nbins,min,max);
	vector<TH1*> SignalHistos = vector<TH1*>();
	//vector<TH1*> MCHistos   = GetMCHistos(plotname);//,nbins,min,max);

//cxyl
	Draw(plotname,DataHistos,MCHistos,options,SignalHistos,false);


}
void PlotMaker::DrawTruthPtMu(string options){
	string plotname="hTruthLeadingMuon_Pt";

	const int nbins=  49;
	Double_t  min  =  25.0;
	Double_t  max  =  1409.0;
	vector<TH1*> DataHistos ;//RebinLog(GetDataHistos(plotname),nbins,min,max);
	DataHistos.clear();
	vector<TH1*> MCHistos   = RebinLog(GetMCHistos(plotname),nbins,min,max);
	vector<TH1*> SignalHistos = vector<TH1*>();
	//vector<TH1*> MCHistos   = GetMCHistos(plotname);//,nbins,min,max);

//cxyl
	Draw(plotname,DataHistos,MCHistos,options,SignalHistos,false);


}


void PlotMaker::DrawTruthWPt(string options){
	string plotname="hTruthWPt";

	const int nbins=  49;
	Double_t  min  =  25.0;
	Double_t  max  =  1409.0;
	vector<TH1*> DataHistos ;//RebinLog(GetDataHistos(plotname),nbins,min,max);
	DataHistos.clear();
	vector<TH1*> MCHistos   = RebinLog(GetMCHistos(plotname),nbins,min,max);
	vector<TH1*> SignalHistos = vector<TH1*>();
	//vector<TH1*> MCHistos   = GetMCHistos(plotname);//,nbins,min,max);

//cxyl
	Draw(plotname,DataHistos,MCHistos,options,SignalHistos,false);


}

void PlotMaker::DrawEta(string options){
	string plotname="hEta";
	
	//int ngroup = 4;
	const int nbins = 50;
	Double_t min    = -2.5;
	Double_t max    = 2.5;
	vector<TH1*> DataHistos = RebinLin(GetDataHistos(plotname),nbins,min,max);
	vector<TH1*> MCHistos = RebinLin(GetMCHistos(plotname),nbins,min,max);
	//vector<TH1*> DataHistos = GetDataHistos(plotname);//,nbins,min,max);
	//vector<TH1*> MCHistos = GetMCHistos(plotname);//,nbins,min,max);
	//bool uselogx=false;
	//bool uselogy=false;
	//c
	Draw(plotname,DataHistos,MCHistos,options);


}

void PlotMaker::DrawPhi(string options){
	string plotname="hPhi";

	//int ngroup = 4;
	const int nbins = 70;
	Double_t min = -3.5;
	Double_t max = 3.5;
	vector<TH1*> DataHistos = RebinLin(GetDataHistos(plotname),nbins,min,max);
	vector<TH1*> MCHistos = RebinLin(GetMCHistos(plotname),nbins,min,max);
	//vector<TH1*> DataHistos = GetDataHistos(plotname);//,nbins,min,max);
	//vector<TH1*> MCHistos = GetMCHistos(plotname);//,nbins,min,max);

	//bool uselogx=false;
	//bool uselogy=false;
	//c
	Draw(plotname,DataHistos,MCHistos,options);


}



TH1F* PlotMaker::DataHistoWrapper(TH1F* hist,UInt_t histnum){


	return hist;
}
TH1F* PlotMaker::MCHistoWrapper(UInt_t histnum,TH1F* hist){
	hist->SetLineColor(vMCColors[histnum]+2);
	hist->SetLineWidth(2);
	hist->SetFillColor(vMCColors[histnum]);
	Double_t scale = 1.0;
/*
	if(Lumi<0 && vDataNames.size()!=0) {
		scale*=((totDataEvents/totMCEvents)*totMCEvents/vMCNEvents[histnum]);

	}
	else if(Lumi<0 && vDataNames.size()==0) scale*=(totMCEvents/vMCNEvents[histnum]);//1/vMCNEvents[histnum]);
	else scale*=(Lumi);///(vMCNEvents[histnum]);//totMCEvents);//1/vMCNEvents[histnum]);
*/
	//else scale*=(Lumi/vMCNEvents[histnum]);//totMCEvents);//1/vMCNEvents[histnum]);
	//scale*=(1/0.000012687);//*(vMCNEvents[histnum]/30000);//*(19.371/0.246);
	//if(vMCNames[histnum]=="mc11_7TeV_McAtNlo_Jimmy_Top") scale*=(1/5.4259E-01);
	//if(vMCNames[histnum]=="mc11_7TeV_HerwigDiboson") scale*=(1/3.8947E-01);
	//if(vMCNames[histnum]=="mc11_7TeV_PythiaWemutau_MassBinned") scale*=3;
	/*
	if(vMCNames[histnum]=="mc11_7TeV_PythiaWmunu_no_filter") scale*=10460.0/8938.0;
	if(vMCNames[histnum]=="mc11_7TeV_PythiaZmumu_no_filter") scale*=10460.0/8938.0;
	*/
	/*
	else if(vMCNames[histnum]=="mc11_7TeV_PythiaZ_Pt100") scale*=Lumi/190033.0;
	else if(vMCNames[histnum]=="mc11_7TeV_PythiaW_Pt100") scale*=Lumi/190033.0;
	else if(vMCNames[histnum]=="mc11_7TeV_PythiaZ_Pt300") scale*=Lumi/26321.0;
	else if(vMCNames[histnum]=="mc11_7TeV_PythiaW_Pt300") scale*=Lumi/26321.0;
	*/

	//if(vMCNames[histnum]=="mc11_7TeV_Pythia6_DYmumu_MassBinned") scale*=10;

	//if(vMCNames[histnum]=="grid_mc11_7TeV_Pythia6_DYmumu_MassBinned") scale*=150.0;


	hist->Scale(scale);

	return hist;

}
TH1F* PlotMaker::SignalHistoWrapper(UInt_t histnum,TH1F* hist){
	hist->SetLineColor(vSignalColors[histnum]+2);
	hist->SetLineWidth(2);
	hist->SetFillColor(0);//Signal should be drawn with empty fill
	Double_t scale = 1.0;
/*
	//shouldn't be adding up events for all W' samples
	if(Lumi<0 && vDataNames.size()!=0) {
		scale*=((totDataEvents/totSignalEvents)*totMCEvents/vSignalNEvents[histnum]);

	}
	else if(Lumi<0 && vDataNames.size()==0) scale*=(totSignalEvents/vSignalNEvents[histnum]);//1/vMCNEvents[histnum]);
	else scale*=(Lumi);///(vMCNEvents[histnum]);//totMCEvents);//1/vMCNEvents[histnum]);

	if (vSignalNames[histnum]=="mc12_8TeV_Wprime_3000"){
		scale*=10.0;
	}
*/
	


	hist->Scale(scale);

	return hist;

}


vector<TH1*> PlotMaker::GetDataHistos(string plotname){
	vector<TH1*> histos;
	histos.clear();
	if(vDataNames.size()!=0){
		for(UInt_t i=0; i<vDataFiles.size();i++){
			histos.push_back(DataHistoWrapper((TH1F*)((TH1F*)vDataFiles[i]->Get(plotname.c_str()))->Clone()));
		}
	}

	return histos;


}
vector<TH1*> PlotMaker::GetMCHistos(string plotname){
	vector<TH1*> histos;
	histos.clear();
	if(vMCNames.size()!=0){
		for(UInt_t i=0; i<vMCFiles.size();i++){
			//since I am reweighting these histograms at the time of plotting
			//it is essential that these are cloned because otherwise
			//they would be reweighted every time you called them
			histos.push_back(MCHistoWrapper(i,(TH1F*)((TH1F*)vMCFiles[i]->Get(plotname.c_str()))->Clone()));
		}
	}

	return histos;


}
vector<TH1*> PlotMaker::GetSignalHistos(string plotname){
	vector<TH1*> histos;
	histos.clear();
	if(vSignalNames.size()!=0){
		for(UInt_t i=0; i<vSignalFiles.size();i++){
			//since I am reweighting these histograms at the time of plotting
			//it is essential that these are cloned because otherwise
			//they would be reweighted every time you called them
			histos.push_back(SignalHistoWrapper(i,(TH1F*)((TH1F*)vSignalFiles[i]->Get(plotname.c_str()))->Clone()));
		}
	}

	return histos;


}

vector<TH1*> PlotMaker::RebinLin(vector<TH1*> histos,const int nbins, Double_t min, Double_t max){

  	vector<TH1*> newhistos;
	newhistos.clear();
	if(max <= min) return newhistos;
	if(nbins <= 0) return newhistos;
	Double_t* bins = new Double_t[nbins+1];
	Double_t  x    = min;
	Double_t  nbins_d = nbins;
	Double_t binwidth = (max-min)/nbins_d;
	for( int ibin=0; ibin <= nbins;++ibin ){
		bins[ibin] = x;
		x+=binwidth;
	}



	if(histos.size()!=0){
  		for(UInt_t i=0;i<histos.size();i++){
			string newname = histos[i]->GetName();
			newname+="_rebin";
			newhistos.push_back((TH1F*)histos[i]->Rebin(nbins,newname.c_str(),bins));
		}

	}
	return newhistos;


}
vector<TH1*> PlotMaker::RebinLog(vector<TH1*> histos,const int nbins, Double_t min, Double_t max){
  	vector<TH1*> newhistos;
  	newhistos.clear();
	if(min <=0 ) return newhistos;
	if(max <= min) return newhistos;
	if(nbins <= 0) return newhistos;

	Double_t* bins = new Double_t[nbins+1];
	Double_t  fac  = pow(max/min,1.0/nbins);
	Double_t  x    = min;
	for( int ibin=0; ibin <= nbins;++ibin ){
		bins[ibin] = TMath::Floor(x);
		x*=fac;
	}

	if(histos.size()!=0){
  		for(UInt_t i=0;i<histos.size();i++){
			string newname = histos[i]->GetName();
			newname+="_rebin";
			newhistos.push_back((TH1F*)histos[i]->Rebin(nbins,newname.c_str(),bins));
		}

	}

	return newhistos;

}

/*
vector<TH1*> PlotMaker::RebinLog(vector<TH1*> histos,const int nbins, Double_t min, Double_t max){
  Double_t bins[nbins+1];
  Double_t nbins_d = nbins;
  Double_t lowbin=min; Double_t highbin=max;
  bins[0]=lowbin;
  Double_t logmin = TMath::Log10(lowbin);
  Double_t logmax = TMath::Log10(highbin);
  Double_t binwidth = (logmax-logmin)/nbins_d;
  for(int i=1;i<=nbins;i++){
	bins[i] = TMath::Floor(TMath::Power(10,logmin+i*binwidth));
  }

  vector<TH1*> newhistos;
  newhistos.clear();
  
  if(histos.size()!=0){
  	for(UInt_t i=0;i<histos.size();i++){
		string newname = histos[i]->GetName();
		newname+="_rebin";
		newhistos.push_back((TH1F*)histos[i]->Rebin(nbins,newname.c_str(),bins));

	}

  }

  return newhistos;


}
*/




vector<TH1*> PlotMaker::Rebin(vector<TH1*> histos,int ngroup){
  vector<TH1*> newhistos;
  newhistos.clear();
  
  if(histos.size()!=0){
  	for(UInt_t i=0;i<histos.size();i++){
		string newname = histos[i]->GetName();
		newname+="_rebin";
		newhistos.push_back((TH1F*)histos[i]->Rebin(ngroup,newname.c_str()));

	}

  }

  return newhistos;


}

TH1F* PlotMaker::GetSumHistos(vector<TH1*> histos){
	if(histos.size()==0) {
	
		cout << "EfficiencyCalculator::GetSumHistos There are no histos, but we expect some"<<endl;
		return NULL;
	}

	TH1F* sum = (TH1F*)histos.at(0)->Clone();
	for(unsigned int i=1;i<histos.size();i++) sum->Add((TH1F*)histos.at(i));

	return sum;

}


void PlotMaker::DrawKFactorRatio(string plot,string options){
	string plotname;
	string plotnokfacname;
	string kfactag="_NoKFac";
	TH1F* num = NULL;
	TH1F* denom = NULL;;
	if(plot=="Pt"){
		plotname="hPt";
		plotnokfacname=plotname+kfactag;
		//const int nbins=  49;
		//Double_t  min  =  25.0;
		//Double_t  max  =  1409.0;
		//num = GetSumHistos(RebinLog(GetMCHistos(plotname),nbins,min,max));
		//denom = GetSumHistos(RebinLog(GetMCHistos(plotnokfacname),nbins,min,max));
		num = GetSumHistos(GetMCHistos(plotname));
		denom = GetSumHistos(GetMCHistos(plotnokfacname));//,nbins,min,max));
	}
	else if(plot=="Mt"){
		plotname="hMt";
		plotnokfacname=plotname+kfactag;
		//const int nbins=  48;
		//Double_t  min  =  10.0;
		//Double_t  max  =  1443.0;//10000.0;
		//num = GetSumHistos(RebinLog(GetMCHistos(plotname),nbins,min,max));
		//denom = GetSumHistos(RebinLog(GetMCHistos(plotnokfacname),nbins,min,max));
		num = GetSumHistos(GetMCHistos(plotname));//,nbins,min,max));
		denom = GetSumHistos(GetMCHistos(plotnokfacname));//,nbins,min,max));
	}
	else if(plot=="TruthWMass"){
		plotname="hTruthWMass";
		plotnokfacname=plotname+kfactag;
		//const int nbins=  48;
		//Double_t  min  =  10.0;
		//Double_t  max  =  1443.0;//10000.0;
		num = GetSumHistos(GetMCHistos(plotname));//,nbins,min,max));
		denom = GetSumHistos(GetMCHistos(plotnokfacname));//,nbins,min,max));
	}
	string outplotname = plotname+"_KFacRatio";
	DrawRatio(outplotname,num,denom,options);
	

}
void PlotMaker::DrawRatio(string plottag, TH1F* numerator, TH1F* denominator, string options){
	bool uselogx      = false;
	bool uselogy      = false;
	bool drawleg      = false;
	if(options.find("X")!=string::npos) uselogx = true;
	if(options.find("Y")!=string::npos) uselogy = true;
	if(options.find("L")!=string::npos) drawleg = true;
	TCanvas* canvas = new TCanvas("canvas","canvas",1000,1000);
	canvas->Clear();
	TPad *p1=new TPad("p1","p1",0.01,0.325,0.99,0.99);
        p1->SetTopMargin(0.01);
        p1->SetBottomMargin(0.09);
        TPad *p2=new TPad("p2","p2",0.01,0.01,0.99,0.33);
        p2->SetTopMargin(0.03);
        p2->SetBottomMargin(0.25);
	
	TLegend* leg    = new TLegend(0.78,0.48,0.92,0.93);
	leg->SetShadowColor(0);
  	leg->SetFillColor(0);
  	leg->SetLineColor(0);

	/****************************/
	/*******Get Ratio*********/
	TH1F* ratio= (TH1F*)numerator->Clone();
	ratio->Divide(denominator);
	Double_t xmin = ratio->GetBinLowEdge(1);
	Double_t xmax = ratio->GetBinLowEdge(ratio->GetNbinsX())
			+ratio->GetBinWidth(ratio->GetNbinsX());
	Double_t ymin = 0.0;
	Double_t ymax = 2.0;
	//Double_t Actualymax = ratio->GetMaximum();
	//Double_t Actualymin = ratio->GetMinimum();
	//if(ymin>Actualymin && ymin>0) ymin=Actualymin;
	Double_t bincontent;
	for(int binnum = 1;binnum<ratio->GetNbinsX();binnum++){
		bincontent = ratio->GetBinContent(binnum);
		//if(( bincontent > ymax) && numerator->GetBinContent(binnum) > 10) ymax = bincontent+0.5;

	}
//		if(sumdata->GetBinContent(ratio->GetMaximumBin()) > 10) ymax=Actualymax+0.5;
	ratio->SetAxisRange(ymin-.05,ymax+.05,"Y");
	ratio->SetLineColor(kBlack);
	TGaxis *yAxisPt1;
	TGaxis *xAxisPt1;
	yAxisPt1=new TGaxis(xmin,ymin-0.05,xmin,ymax+0.05,ymin,ymax,303);
	if(uselogx) xAxisPt1=new TGaxis(xmin,ymin-0.05,xmax,ymin-0.05,xmin,xmax,510,"G");
	else xAxisPt1=new TGaxis(xmin,ymin-0.05,xmax,ymin-0.05,xmin,xmax,510);
	yAxisPt1->SetTitle("Ratio");
	xAxisPt1->SetTitle(numerator->GetXaxis()->GetTitle());
        yAxisPt1->SetTitleSize(1.75*numerator->GetYaxis()->GetTitleSize());	 
        yAxisPt1->SetTitleOffset(0.55*numerator->GetYaxis()->GetTitleOffset()); 
        yAxisPt1->SetLabelSize(1.1*numerator->GetYaxis()->GetTitleSize());	 
        yAxisPt1->SetLabelOffset(0.02*numerator->GetYaxis()->GetTitleOffset()); 
	yAxisPt1->SetNdivisions(5);
        xAxisPt1->SetTitleSize(2.25*numerator->GetXaxis()->GetTitleSize());	 
        xAxisPt1->SetTitleOffset(0.75*numerator->GetXaxis()->GetTitleOffset());
        xAxisPt1->SetLabelSize(2.*numerator->GetXaxis()->GetTitleSize());	 
        xAxisPt1->SetLabelOffset(0.01*numerator->GetXaxis()->GetTitleOffset());
	
	p1->Draw();
        p2->Draw();
	p1->cd();
	/*
        p1->cd();
        p1->SetLogy(true);
	*/
	/*************************/
	denominator->Draw("HIST");
	denominator->SetLineColor(1);
	denominator->SetFillColor(0);
	leg->AddEntry(denominator ,denominator->GetName(),"f");


		//for some reason the order of these matters
//		denominator->GetYaxis()->SetTitle(MC[0]->GetYaxis()->GetTitle());
//		denominator->GetXaxis()->SetTitle(MC[0]->GetXaxis()->GetTitle());
	/*************************/
	
	numerator->Draw("HISTsame"); 
	numerator->SetLineColor(2);
	numerator->SetFillColor(0);
	leg->AddEntry(numerator ,numerator->GetName(),"f");

	/**************************/

	//}

	/******Get Line***********/
	TLine *myline;
	myline=new TLine(xmin,1.,xmax,1.);

	/*************************/

	//need to add legend
	if(uselogx) {
        	p1->cd();
        	p1->SetLogx(true);
		p2->cd();
		p2->SetLogx(true);
		//gPad->SetLogx();
	}
	else {
		//gPad->SetLogx(0);
        	p1->cd();
        	p1->SetLogx(false);
		p2->cd();
		p2->SetLogx(false);
	}
	if(uselogy) {
	//	gPad->SetLogy();
        	p1->cd();
        	p1->SetLogy(true);
		p2->cd();
		p2->SetLogy(false);
	}
	else {
		//gPad->SetLogy(0);
        	p1->cd();
        	p1->SetLogy(false);
		p2->cd();
		p2->SetLogy(false);
	}
	p1->cd();

	if(drawleg) leg->Draw();

	/*******Draw Ratio*******/
	p2->cd();
	p2->SetTicks(1,1);
	ratio->Draw("A");
	yAxisPt1->Draw();
        xAxisPt1->Draw();
        p2->SetTicks(10.,10.);
        myline->Draw("same");

	/*************************/

	/************************/

	canvas->Update();
	string imagetype="png";
	string imagename=imagedir+"/"+plottag+"."+imagetype;
	canvas->Print(imagename.c_str(),imagetype.c_str());

	imagetype="pdf";
	imagename=imagedir+"/"+plottag+"."+imagetype;
	canvas->Print(imagename.c_str(),imagetype.c_str());

	canvas->Close();

}

void PlotMaker::Draw(string plottag,vector<TH1*> Data, vector<TH1*> MC,string options,vector<TH1*> Signal,bool DrawData,double plotymin){
//,bool uselogx,bool uselogy,bool drawleg){
	bool doratio = false;
	bool haveMC = false;
	bool haveData= false;
	bool haveSignal = false;
	if(MC.size()>0) haveMC = true;
	if(Data.size()>0) haveData = true;
	if(Signal.size()>0) haveSignal = true;
	if(haveMC && haveData) doratio=true;

	bool docategorize = false;
	bool uselogx      = false;
	bool uselogy      = false;
	bool drawleg      = false;
	bool drawsingle   = false;
	if(options.find("C")!=string::npos) docategorize = true;
	if(options.find("X")!=string::npos) uselogx = true;
	if(options.find("Y")!=string::npos) uselogy = true;
	if(options.find("L")!=string::npos) drawleg = true;
	if(options.find("S")!=string::npos) drawsingle = true;
	



	if(!drawsingle){
	TCanvas* canvas = new TCanvas("canvas","canvas",1000,1000);
	canvas->Clear();
	TPad *p1 = NULL;
	TPad *p2 = NULL;
	p1=new TPad("p1","p1",0.01,0.325,0.99,0.99);
        p1->SetTopMargin(0.01);
        p1->SetBottomMargin(0.09);
	if(doratio){
        p2=new TPad("p2","p2",0.01,0.01,0.99,0.33);
        p2->SetTopMargin(0.03);
        p2->SetBottomMargin(0.25);
	}
	
	TLegend * leg = new TLegend(0.78,0.48,0.92,0.93);
	leg->SetShadowColor(0);
  	leg->SetFillColor(0);
  	leg->SetLineColor(0);

	//if have a signal then need a stacked histogram for each one
	//if no signal then only need one stacked histogram
	vector<THStack*> vMCStack;
	if(haveSignal && !docategorize){
		for(unsigned int sigcount=0;sigcount<Signal.size();sigcount++){
			char name[100];
			sprintf(name,"mcstack%d",sigcount);
			vMCStack.push_back(new THStack(name,name));
		}
	}
	else if(haveSignal && docategorize){
		for(unsigned int sigcount=0;sigcount<vSignalCategoryNames.size();sigcount++){
			char name[100];
			sprintf(name,"mcstack%d",sigcount);
			vMCStack.push_back(new THStack(name,name));
		}
	}
	else {
		vMCStack.push_back(new THStack("mcstack0","mcstack0")); 
	}

	TH1F* sumbg = 0;
	/******Get MC Sum*****************/
//	if(MC.size()!=0){
		if(docategorize){
			vector<TH1*> mccat;
			bool initializedsum = false;
			for(unsigned int i=1;i<vCategoryNames.size();i++){//don't plot the first one
				bool alreadyfound = false;
				for(unsigned int j=0;j<vMCCategory.size();j++){
					if(vMCCategory[j]==vCategoryNames[i] && !alreadyfound){
						mccat.push_back((TH1*)MC[j]->Clone());

						if(!initializedsum){
							sumbg = (TH1F*)MC[j]->Clone();
							initializedsum=true;
						}
						else sumbg->Add(MC[j]);

						alreadyfound=true;
					}
					else if(vMCCategory[j]==vCategoryNames[i]){
						mccat.back()->Add(MC[j]);
						sumbg->Add(MC[j]);
					}

				}

				if(!alreadyfound) continue;

				mccat.back()->SetLineColor(vCategoryColors[i]+2);
				mccat.back()->SetFillColor(vCategoryColors[i]);
				
				for(unsigned int stackcount=0;stackcount<vMCStack.size();stackcount++) vMCStack[stackcount]->Add(mccat.back());
			}//end loop over category names
			for(unsigned int i=0;i<mccat.size();i++){
				leg->AddEntry(mccat[mccat.size()-i-1],vCategoryNames[mccat.size()-i].c_str(),"f");
			}

			vector<TH1*> signalcat;
			//begin signal processing
			for(unsigned int i=1;i<vSignalCategoryNames.size();i++){//don't plot the first one
				bool alreadyfound = false;
				for(unsigned int j=0;j<vSignalCategory.size();j++){
					if(vSignalCategory[j]==vSignalCategoryNames[i] && !alreadyfound){
						signalcat.push_back((TH1*)Signal[j]->Clone());
						alreadyfound=true;

						/*
						if(!initializedsum){
							sumbg = (TH1F*)MC[j]->Clone();
							initializedsum=true;
						}
						else sumbg->Add(MC[j]);
						*/

					}
					else if(vSignalCategory[j]==vSignalCategoryNames[i]){
						signalcat.back()->Add(Signal[j]);
					}

				}

				if(!alreadyfound) continue;

				signalcat.back()->SetLineColor(vCategoryColors[i]+2);
				signalcat.back()->SetFillColor(0);
				
				vMCStack[i]->Add(signalcat.back());
			}//end loop over signal category names
			for(unsigned int i=0;i<signalcat.size();i++){
				leg->AddEntry(signalcat[i],vSignalCategoryNames[i+1].c_str(),"f");
			}
			///end of signal prt
		}//end if docategorize
		else{
			for(unsigned int stackcount=0;stackcount<vMCStack.size();stackcount++){
				for(UInt_t i=0;i<MC.size();i++){
					vMCStack[stackcount]->Add(MC[i]);
					if(i==0 && stackcount==0) sumbg = (TH1F*)MC[i]->Clone();
					else if( stackcount==0) sumbg->Add(MC[i]);
				}
			}

			for(UInt_t i=0;i<MC.size();i++){
				leg->AddEntry(MC[MC.size()-i-1] ,vMCLabels[MC.size()-i-1].c_str(),"f");
			}

			for(UInt_t i=0;i<Signal.size();i++){
				vMCStack[i]->Add(Signal[i]);
			}
			for(unsigned int i=0;i<Signal.size();i++){
				leg->AddEntry(Signal[Signal.size()-i-1],vSignalLabels[Signal.size()-i-1].c_str(),"f");
			}
		}

	//}
	/************************************/

	/******Get Data Sum**********/
	TH1F *sumdata = NULL;
		for(UInt_t i=0;i<Data.size();i++){
			if(i==0) sumdata=(TH1F*)Data[i]->Clone();
			else sumdata->Add(Data[i]);
		}
	/****************************/
	/*******Get Ratio*********/
	TH1F* ratio = NULL;
	Double_t xmin,xmax,ymin,ymax;
	xmin = 0.;
	xmax = 0.;
	TGaxis *yAxisPt1 =  NULL;
	TGaxis *xAxisPt1 = NULL;
	if(doratio){
	ratio= (TH1F*)sumdata->Clone();
	ratio->Divide(sumbg);
	xmin = ratio->GetBinLowEdge(1);
	xmax = ratio->GetBinLowEdge(ratio->GetNbinsX())
			+ratio->GetBinWidth(ratio->GetNbinsX());
	ymin = 0.0;
	ymax = 2.0;
	//Double_t Actualymax = ratio->GetMaximum();
	//Double_t Actualymin = ratio->GetMinimum();
	//if(ymin>Actualymin && ymin>0) ymin=Actualymin;
	Double_t bincontent;
	for(int binnum = 1;binnum<ratio->GetNbinsX();binnum++){
		bincontent = ratio->GetBinContent(binnum);
		//if(( bincontent > ymax) && sumdata->GetBinContent(binnum) > 10) ymax = bincontent+0.5;

	}
//		if(sumdata->GetBinContent(ratio->GetMaximumBin()) > 10) ymax=Actualymax+0.5;
	ratio->SetAxisRange(ymin-.05,ymax+.05,"Y");
	ratio->SetLineColor(kBlack);
	yAxisPt1=new TGaxis(xmin,ymin-0.05,xmin,ymax+0.05,ymin,ymax,303);
	if(uselogx) xAxisPt1=new TGaxis(xmin,ymin-0.05,xmax,ymin-0.05,xmin,xmax,510,"G");
	else xAxisPt1=new TGaxis(xmin,ymin-0.05,xmax,ymin-0.05,xmin,xmax,510);
	yAxisPt1->SetTitle("Data/BG");
	xAxisPt1->SetTitle(sumdata->GetXaxis()->GetTitle());
        yAxisPt1->SetTitleSize(1.75*sumdata->GetYaxis()->GetTitleSize());	 
        yAxisPt1->SetTitleOffset(0.55*sumdata->GetYaxis()->GetTitleOffset()); 
        yAxisPt1->SetLabelSize(1.1*sumdata->GetYaxis()->GetTitleSize());	 
        yAxisPt1->SetLabelOffset(0.02*sumdata->GetYaxis()->GetTitleOffset()); 
	yAxisPt1->SetNdivisions(5);
        xAxisPt1->SetTitleSize(2.25*sumdata->GetXaxis()->GetTitleSize());	 
        xAxisPt1->SetTitleOffset(0.75*sumdata->GetXaxis()->GetTitleOffset());
        xAxisPt1->SetLabelSize(2.*sumdata->GetXaxis()->GetTitleSize());	 
        xAxisPt1->SetLabelOffset(0.01*sumdata->GetXaxis()->GetTitleOffset());
	
	}
	p1->Draw();
        if(doratio)p2->Draw();
	p1->cd();
	/*
        p1->cd();
        p1->SetLogy(true);
	*/
	/*************************/

	//}

	/******Get Line***********/
	TLine *myline = NULL;
	if(doratio) myline=new TLine(xmin,1.,xmax,1.);

	/*************************/

	//need to add legend
	if(uselogx) {
        	p1->cd();
        	p1->SetLogx(true);
		if(doratio){
		p2->cd();
		p2->SetLogx(true);
		}
		//gPad->SetLogx();
	}
	else {
		//gPad->SetLogx(0);
        	p1->cd();
        	p1->SetLogx(false);
		if(doratio){
		p2->cd();
		p2->SetLogx(false);
		}
	}
	if(uselogy) {
	//	gPad->SetLogy();
		//datahist->GetYaxis()->SetRangeUser(datahist->GetMinimum(),datahist->GetMaximum());
        	p1->cd();
        	p1->SetLogy(true);
		if(doratio){
		p2->cd();
		p2->SetLogy(false);
		}
	}
	else {
		//gPad->SetLogy(0);
        	p1->cd();
        	p1->SetLogy(false);
		if(doratio){
		p2->cd();
		p2->SetLogy(false);
		}
	}
	p1->cd();
	/******Draw MC************/
	/*
		mcstack->Draw("HIST");
		//for some reason the order of these matters
		mcstack->GetYaxis()->SetTitle(MC[0]->GetYaxis()->GetTitle());
		mcstack->GetXaxis()->SetTitle(MC[0]->GetXaxis()->GetTitle());
		*/
	/*************************/
	/***Draw Data*************/
	//draw data first to get range right, and then draw mc and data again
	TH1F *datahist = NULL;
	bool diddrawdata= false;
	if(Data.size()!=0 && DrawData){
		for(UInt_t i=0;i<Data.size();i++){
			datahist=(TH1F*)Data[i]->Clone();
			if(plotymin>0){
				//datahist->GetYaxis()->SetRangeUser(plotymin,datahist->GetMaximum()*1.1);
				datahist->SetAxisRange(plotymin,datahist->GetMaximum()*1.1);
			}
			double min = std::max(std::min(datahist->GetMinimum()*0.1, vMCStack[0]->GetMinimum()*0.1),1e-3);
			double max = std::max(datahist->GetMaximum()*10, vMCStack[0]->GetMaximum()*10);
			datahist->GetYaxis()->SetRangeUser(min, max);
			if(MC.size()!=0 || i!=0) {
				datahist->Draw();//"same");
				diddrawdata=true;
			}
			else{
				datahist->Draw("HIST");
				diddrawdata=true;
			}
			leg->AddEntry(datahist ,vDataLabels[i].c_str(),"p");

		}
	}
	/**************************/
	/******Draw MC************/
	if(haveMC){
		for(unsigned int stackcount=0;stackcount<vMCStack.size();stackcount++){
//				cout << vMCStack[stackcount]->GetMinimum() << "\t" << vMCStack[stackcount]->GetMaximum() << endl;
//			if(vMCStack[stackcount] && vMCStack[stackcount]->GetYaxis())
//				vMCStack[stackcount]->GetYaxis()->SetRangeUser(std::min(vMCStack[stackcount]->GetMinimum()*0.9,1e-9),vMCStack[stackcount]->GetMaximum()*1.1);
			if(diddrawdata) vMCStack[stackcount]->Draw("HISTsame");
			else  {
				if(plotymin>0){
					cout << plotymin<< "\t"<<vMCStack[stackcount]->GetMaximum()<<endl;
					//mcstack->GetYaxis()->SetRangeUser(plotymin,1e8);//mcstack->GetMaximum()*1.1);
					vMCStack[stackcount]->SetMinimum(plotymin);//,mcstack->GetMaximum()*1.1);
				}
				if(stackcount==0) vMCStack[stackcount]->Draw("HIST");
				else if(stackcount!=0) vMCStack[stackcount]->Draw("HISTsame");
			}
			//for some reason the order of these matters
			vMCStack[stackcount]->GetYaxis()->SetTitle(MC[0]->GetYaxis()->GetTitle());
			vMCStack[stackcount]->GetXaxis()->SetTitle(MC[0]->GetXaxis()->GetTitle());
			if(datahist!= NULL && DrawData)datahist->Draw("same");
		}
	}
	/*************************/

	if(drawleg) leg->Draw();

	/*******Draw Ratio*******/
	if(doratio){
	p2->cd();
	p2->SetTicks(1,1);
	ratio->Draw("A");
	yAxisPt1->Draw();
        xAxisPt1->Draw();
        p2->SetTicks(10.,10.);
        myline->Draw("same");
	}

	/*************************/

	/************************/

	canvas->Update();
	string catstr="";
	if(docategorize) catstr="categorized";
	else catstr="stacked";

	string imagetype="png";
	string finalimagedir=imagedir+"/"+imagetype+"/"+catstr+"/";
	mkdirRecursive(finalimagedir);
	string imagename=finalimagedir+plottag+"_"+catstr+"."+imagetype;
	canvas->Print(imagename.c_str(),imagetype.c_str());

	imagetype="pdf";
	finalimagedir=imagedir+"/"+imagetype+"/"+catstr+"/";
	mkdirRecursive(finalimagedir);
	imagename=finalimagedir+plottag+"_"+catstr+"."+imagetype;
	canvas->Print(imagename.c_str(),imagetype.c_str());

	imagetype="eps";
	finalimagedir=imagedir+"/"+imagetype+"/"+catstr+"/";
	mkdirRecursive(finalimagedir);
	imagename=finalimagedir+plottag+"_"+catstr+"."+imagetype;
	canvas->Print(imagename.c_str(),imagetype.c_str());

	canvas->Close();
	}//end if!drawsingle
	else{
	vector<TH1*> histos;
	vector<string> names;
	if(MC.size()!=0){
		if(docategorize){
			for(unsigned int i=1;i<vCategoryNames.size();i++){//don't plot the first one
				bool alreadyfound = false;
				for(unsigned int j=0;j<vMCCategory.size();j++){
					if(vMCCategory[j]==vCategoryNames[i] && !alreadyfound){
						histos.push_back((TH1*)MC[j]->Clone());
						names.push_back(vCategoryNames[i]);
						alreadyfound=true;
					}
					else if(vMCCategory[j]==vCategoryNames[i]){
						histos.back()->Add(MC[j]);
					}

				}

				if(!alreadyfound) continue;
				
			}

		}
		else{
			for(UInt_t i=0;i<MC.size();i++){
				histos.push_back((TH1*)MC[i]->Clone());
				names.push_back(vMCLabels[i]);
			}
		}

	}
	if(Signal.size()!=0){
		if(docategorize){
			for(unsigned int i=1;i<vSignalCategoryNames.size();i++){//don't plot the first one
				bool alreadyfound = false;
				for(unsigned int j=0;j<vSignalCategory.size();j++){
					if(vSignalCategory[j]==vSignalCategoryNames[i] && !alreadyfound){
						histos.push_back((TH1*)Signal[j]->Clone());
						names.push_back(vSignalCategoryNames[i]);
						alreadyfound=true;
					}
					else if(vSignalCategory[j]==vSignalCategoryNames[i]){
						histos.back()->Add(Signal[j]);
					}

				}

				if(!alreadyfound) continue;
				
			}
		}
		else{
			for(UInt_t i=0;i<Signal.size();i++){
				histos.push_back((TH1*)Signal[i]->Clone());
				names.push_back(vSignalLabels[i]);
			}
		}
	}

	if(Data.size()!=0){
		for(UInt_t i=0;i<Data.size();i++){
			histos.push_back((TH1*)Data[i]->Clone());
			names.push_back(vDataLabels[i]);

		}

	}
	TCanvas* singlecanvas ;
	for(unsigned int i=0;i<histos.size();i++){
		singlecanvas = new TCanvas("singlecanvas","singlecanvas",1000,1000);
		if(uselogx) gPad->SetLogx();
		else gPad->SetLogx(0);
		if(uselogy) gPad->SetLogy();
		else gPad->SetLogy(0);

		histos[i]->Draw("HIST");


		singlecanvas->Update();
		string imagetype="png";
		string catstr="";
		string finalimagedir= imagedir+"/"+imagetype+"/single/"+plottag+"/";
		mkdirRecursive(finalimagedir);
		string imagename=finalimagedir+"Single_"+names[i]+"."+imagetype;
		singlecanvas->Print(imagename.c_str(),imagetype.c_str());

		imagetype="pdf";
		finalimagedir= imagedir+"/"+imagetype+"/single/"+plottag+"/";
		mkdirRecursive(finalimagedir);
		imagename=finalimagedir+"Single_"+names[i]+"."+imagetype;
		singlecanvas->Print(imagename.c_str(),imagetype.c_str());

		imagetype="eps";
		finalimagedir= imagedir+"/"+imagetype+"/single/"+plottag+"/";
		mkdirRecursive(finalimagedir);
		imagename=finalimagedir+"Single_"+names[i]+"."+imagetype;
		singlecanvas->Print(imagename.c_str(),imagetype.c_str());

		singlecanvas->Close();
		delete singlecanvas;
	}


	}


}
void PlotMaker::mkdir(string dir){

	string command="if [ ! -d  "+dir+" ];then mkdir "+dir+"; fi;";
  	system(command.c_str());

}
void PlotMaker::mkdirRecursive(string path){

	vector<string> splitPath;
	size_t locRight=string::npos;
	do{
		if(locRight!=string::npos){
			
			size_t length = locRight+1;
			splitPath.push_back(path.substr(0,length));
			path = path.erase(0,length);

			
		}

		locRight=path.find("/");
	} while (locRight!=string::npos);
	
	string fullpath = "";
	for(unsigned int count=0;count<splitPath.size();count++) {
		
			
		fullpath+=splitPath[count];
		if (fullpath=="/") continue;
		mkdir(fullpath);
	}




}


