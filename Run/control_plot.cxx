#include<vector>
#include<cstdlib>

std::string randomStrGen(int length)
{
    static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string result;
    result.resize(length);

    for (int i = 0; i < length; i++)
      result[i] = charset[rand() % charset.length()];

    return result;
}
TH1 * overflow(TH1 *h)
{
      // This function paint the histogram h with an extra bin for overflows
   UInt_t nx    = h->GetNbinsX()+1;
   Double_t *xbins= new Double_t[nx+1];
   for (UInt_t i=0;i<nx;i++)
     xbins[i]=h->GetBinLowEdge(i+1);
   xbins[nx]=xbins[nx-1]+h->GetBinWidth(nx);
   char *tempName= new char[strlen(h->GetName())+11];
   sprintf(tempName,"%s_%s",h->GetName(),randomStrGen(10));
   // Book a temporary histogram having ab extra bin for overflows
   TH1F *htmp = new TH1F(tempName, h->GetTitle(), nx, xbins);
   // Reset the axis labels
   htmp->SetXTitle(h->GetXaxis()->GetTitle());
   htmp->SetYTitle(h->GetYaxis()->GetTitle());
   // Fill the new hitogram including the extra bin for overflows
   for (UInt_t i=0; i<=nx; i++) {
     htmp->SetBinContent(i, h->GetBinContent(i));
     htmp->SetBinError(i, h->GetBinError(i));
    }
   // Restore the number of entries
   htmp->SetEntries(h->GetEntries());
   // FillStyle and color
	htmp->SetFillColor(h->GetFillColor());
	htmp->SetLineColor(h->GetLineColor());
	htmp->SetLineWidth(h->GetLineWidth());
	
	delete xbins;
	delete tempName;
  return htmp;
}

void control_plot(const char *in, const char *out)
{
  srand(time(NULL));
  gROOT->LoadMacro("AtlasStyle.C");
  gROOT->LoadMacro("AtlasUtils.C");
  SetAtlasStyle();
  TFile *file = new TFile(in);
  
  TH1 *names = 0;
  TH1 *data = 0;
  THStack *background = new THStack();
  THStack *signal = new THStack();
  THStack *temp_background = 0;
  THStack *temp_signal = 0;
  file->GetObject("names", names);

  TCanvas *canvas = new TCanvas("canvas","canvas",0,0,800,600);
  TPad *upper_pad = new TPad("upper_pad","upper",0,0.18,1,1);
  TPad *lower_pad = new TPad("lower_pad","lower",0,0,1,0.30);
  canvas->cd();
  upper_pad->Draw();
  lower_pad->Draw();
  
  for(int i = 0; i < names->GetXaxis()->GetNbins(); i++)
  {
  	TString data_key("plot");
  	TString background_key("plot");
  	TString signal_key("plot");
  	TString outFilename(out);
  	data_key += (i+1);
  	background_key += (i+1);
  	signal_key += (i+1);
  	data_key += "_data";
  	background_key += "_background";
  	signal_key += "_signal";
  	outFilename = outFilename + "/" + names->GetXaxis()->GetBinLabel(i+1) + ".png";
  	
  	file->GetObject(data_key.Data(), data);
  	file->GetObject(background_key.Data(), temp_background);
  	file->GetObject(signal_key.Data(), temp_signal);

		data = overflow(data);
		if(background->GetHists())
			background->GetHists()->Clear();
		for(int j = 0; j < temp_background->GetHists()->GetEntries(); j++) {
			TH1 *hist = (TH1*)temp_background->GetHists()->At(j);
			background->Add(overflow(hist));
		}
		if(signal->GetHists())
			signal->GetHists()->Clear();
		for(int j = 0; j < temp_signal->GetHists()->GetEntries(); j++) {
			TH1 *hist = (TH1*)temp_signal->GetHists()->At(j);
			signal->Add(overflow(hist));
		}
		

		//******** Draw Upper Pad
  	
		upper_pad->cd();
		upper_pad->SetLogx(false);
		if(data->GetMinimum() <= 0)
			upper_pad->SetLogy(false);
		else
			upper_pad->SetLogy(true);
		
		data->SetMarkerStyle(20);
		data->SetMarkerColor(kBlack);
		data->SetMarkerSize(0.9);
		data->GetXaxis()->SetTitle(names->GetXaxis()->GetBinLabel(i+1));
		data->GetXaxis()->SetNoExponent(kTRUE);
		data->GetYaxis()->SetTitle("Events");
//		if(TString(names->GetXaxis()->GetBinLabel(i+1)).Contains("Mass") && TString(names->GetXaxis()->GetBinLabel(i+1)).Contains("c1"))
//			data->GetXaxis()->SetRangeUser(30,200);
		data->SetMinimum(data->GetMinimum()/100);
		data->Draw("e");
		
		for(int j = 0; j < background->GetHists()->GetEntries(); j++)
		{
			TH1 *hist = (TH1*)background->GetHists()->At(j);
			hist->SetFillStyle(3004+j);
			hist->SetFillColor(hist->GetLineColor());
		}
		for(int j = 0; j < background->GetHists()->GetEntries(); j++)
		{
			TH1 *h1 = (TH1 *)background->GetHists()->At(j);
			int min_index = j;
			double min = h1->Integral(1, h1->GetNbinsX());
			for(int j2 = j+1; j2 < background->GetHists()->GetEntries(); j2++)
			{
				TH1 *h2 = (TH1 *)background->GetHists()->At(j2);
				double n = h2->Integral(1, h2->GetNbinsX());
				if(n < min)
				{
					min_index = j2;
					min = n;
					h1 = h2;
				}
			}
			if(min_index > j)
			{
				background->GetHists()->Remove(h1);
				background->GetHists()->AddAt(h1,j);
			}
		}
//		((TH1*)background->GetHists()->At(0))->Scale(0.2);
//		background->GetHists()->Remove(stack->GetHists()->At(3));

		background->Draw("histsame");
		for(int j = 0; j < signal->GetHists()->GetEntries(); j++)
		{
			TH1 *hist = ((TH1 *)signal->GetHists()->At(j));
			hist->Scale(100);
		}
		signal->Draw("histsamenostack");
		data->Draw("esame");
		
		upper_pad->RedrawAxis();
		TLegend *leg = new TLegend(0.72,0.55,0.89,0.92,NULL,"brNDC");
		leg->SetTextSize(0.04);
		leg->SetLineColor(0);
		leg->SetLineStyle(1);
		leg->SetLineWidth(1);
		leg->SetFillColor(0);
		leg->SetFillStyle(1001);
		leg->SetBorderSize(0);
		leg->AddEntry(data, data->GetTitle(), "P");
		for(int j = 0; j < background->GetHists()->GetEntries(); j++)
		{
			TH1 *hist = (TH1 *)background->GetHists()->At(j);
			leg->AddEntry(hist, hist->GetTitle(), "F");
		}
		for(int j = 0; j < signal->GetHists()->GetEntries(); j++)
		{
			TH1 *hist = (TH1 *)signal->GetHists()->At(j);
			leg->AddEntry(hist, hist->GetTitle(), "F");
		}
		leg->Draw();
		
		//******** Draw Latex Info
		
		
		//******** Draw Lower Pad
		
		lower_pad->cd();
		lower_pad->SetBottomMargin(0.3);
		lower_pad->SetLogx(false);
		lower_pad->SetLogy(false);
		lower_pad->SetGridy(true);
		
		TH1 *sumMC = (TH1 *)background->GetHists()->At(0)->Clone("sumMC");
//		sumMC->Sumw2();
		for(int j = 1; j < background->GetHists()->GetEntries(); j++)
			sumMC->Add((TH1 *)background->GetHists()->At(j));
		TH1 *ratio = data->Clone("ratio");
//		ratio->Sumw2();
		ratio->Divide(sumMC);

		ratio->SetMarkerStyle(20);
		ratio->SetMarkerColor(kBlack);
		ratio->SetMarkerSize(0.9);
		ratio->SetMaximum(1.5);
		ratio->SetMinimum(0.5);
//		ratio->SetMaximum(10);
//		ratio->SetMinimum(0);
		ratio->GetXaxis()->SetTitle(names->GetXaxis()->GetBinLabel(i+1));
		ratio->GetYaxis()->SetTitle("Data/MC");
		
		ratio->GetYaxis()->SetDecimals(kTRUE);
		ratio->GetXaxis()->SetTitleOffset(1.);
		ratio->GetYaxis()->SetTitleOffset(0.5);
		ratio->GetXaxis()->SetTitleSize(0.14);
		ratio->GetXaxis()->SetLabelSize(0.14);
		ratio->GetYaxis()->SetTitleSize(0.14);
		ratio->GetYaxis()->SetLabelSize(0.1);
		ratio->GetYaxis()->SetNdivisions(8);
		ratio->GetXaxis()->SetTickLength(0.05);  
		ratio->Draw("e");
		
		TH1 *errors = sumMC->Clone("ratio");
		errors->Divide(sumMC);
		errors->SetFillStyle(1001);
		errors->SetFillColor(kYellow);
		errors->SetMarkerColor(kYellow);
		errors->Draw("e3same");
		lower_pad->RedrawAxis("g");
		ratio->Draw("esame");
		
		canvas->Print(outFilename.Data());
  }
}
