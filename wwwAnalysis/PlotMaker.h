#ifndef PLOTMAKER_H
#define PLOTMAKER_H

#include "TH1F.h"
#include "TFile.h"
#include "TColor.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include<iostream>
using std::cout;
using std::endl;

#include <stdio.h>
#include <stdlib.h>

class PlotMaker{
	public:
		PlotMaker(string myimagedir = "images");
		~PlotMaker();

		void SetLumi(Double_t lumi){Lumi = lumi;};//in 1/pb
		void AddData(string name,string label);
		void AddMC(string name,string label, string category="none", Color_t color=kBlack);
		void AddSignal(string name,string label, string category="none", Color_t color=kBlack);
		int  FindCategory(string name);
		int  FindSignalCategory(string name);
		void AddCategory(string name,Color_t color);
		void AddSignalCategory(string name,Color_t color);
		TH1F* GetSumHistos(vector<TH1*> histos);
		void DrawKFactorRatio(string plot,string options);
		void DrawRatio(string plottag, TH1F* numerator, TH1F* denominator, string options);
		void DrawStandard(string plotname, string options = "CXYL");
		void DrawEtMiss(string options = "CXYL");//,string weightoptions="");
		void DrawPt(string options = "CXYL");//,string weightoptions="");
		void DrawMt(string options = "CXYL");//,string weightoptions="");
		void DrawTruthWMass(string options = "CXYL");
		void DrawTruthZMass(string options = "CXYL");
		void DrawTruthPtMu(string options = "CXYL");
		void DrawTruthWPt(string options = "CXYL");
		void DrawTruthZPt(string options = "CXYL");
		void DrawEta(string options = "C");//,string weightoptions="");
		void DrawPhi(string options = "C");//,string weightoptions="");
		void Draw(string plottag,vector<TH1*> Data, vector<TH1*> MC,string options="CXYL",vector<TH1*> Signal=vector<TH1*>(),bool DrawData=true,double plotymin=-1);//bool docategorize=true,bool uselogx=true,bool uselogy=true,bool drawleg = true);
		
		TH1F* DataHistoWrapper(TH1F* hist,UInt_t histnum=0);
		TH1F* MCHistoWrapper(UInt_t histnum,TH1F* hist);
		TH1F* SignalHistoWrapper(UInt_t histnum,TH1F* hist);
	protected:
		vector<TH1*> GetDataHistos(string plotname);
		vector<TH1*> GetMCHistos(string plotname);
		vector<TH1*> GetSignalHistos(string plotname);
		vector<TH1*> PrepareDataHistos(string &plotname,Int_t nbins, Double_t min, Double_t max, string weightoptions);
		vector<TH1*> PrepareMCHistos(string &plotname,Int_t nbins, Double_t min, Double_t max, string weightoptions);
		vector<TH1*> Rebin(vector<TH1*> histos,int ngroup);
		vector<TH1*> RebinLog(vector<TH1*> histos,const int nbins, Double_t min, Double_t max);
		vector<TH1*> RebinLin(vector<TH1*> histos,const int nbins, Double_t min, Double_t max);
		void mkdir(string dir);
		void mkdirRecursive(string path);

		vector<string> vDataNames;
		vector<string> vMCNames;
		vector<string> vSignalNames;

		vector<string> vDataLabels;
		vector<string> vMCLabels;
		vector<string> vSignalLabels;

		vector<TFile*> vDataFiles;
		vector<TFile*> vMCFiles;
		vector<TFile*> vSignalFiles;

		vector<Double_t> vMCNEvents;
		vector<Double_t> vDataNEvents;
		vector<Double_t> vSignalNEvents;


		vector<Color_t> vMCColors;
		vector<Color_t> vSignalColors;
		vector<string> vMCCategory;
		vector<string> vSignalCategory;

		vector<string>  vCategoryNames;
		vector<Color_t> vCategoryColors;
		vector<string>  vSignalCategoryNames;
		vector<Color_t> vSignalCategoryColors;

		Double_t Lumi;

		Double_t totMCEvents;
		Double_t totSignalEvents;
		Double_t totDataEvents;

		string rootfilename;
		string basesubmitdir;
		string baseoutputdir;

		string imagedir;
};


#endif
