#include<vector>

TH1 * overflow(TH1 *h)
{
/*
      // This function paint the histogram h with an extra bin for overflows
   UInt_t nx    = h->GetNbinsX()+1;
   Double_t *xbins= new Double_t[nx+1];
   for (UInt_t i=0;i<nx;i++)
     xbins[i]=h->GetBinLowEdge(i+1);
   xbins[nx]=xbins[nx-1]+h->GetBinWidth(nx);
   char *tempName= new char[strlen(h->GetName())+10];
   sprintf(tempName,"%swtOverFlow",h->GetName());
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
   htmp->SetFillStyle(h->GetFillStyle());
   htmp->SetFillColor(h->GetFillColor());
   return htmp;
  */
  return h;
}

void fakes_plot(const char *in, const char *out)
{
  gROOT->LoadMacro("AtlasStyle.C");
  gROOT->LoadMacro("AtlasUtils.C");
  SetAtlasStyle();
  TFile *file = new TFile(in);
  
  TH1 *data = 0;
  TH1 *mc = 0;
  TH1 *mc_fake = 0;
  TH1 *mc_difake = 0;
  TH1 *fake = 0;
  TH1 *difake = 0;
  TH1 *top = 0;
  TH1 *top_fake = 0;
  TH1 *top_difake = 0;
  TH1 *zll = 0;
  TH1 *zll_fake = 0;
  TH1 *zll_difake = 0;
  TH2 *fnorms = 0;
  TH2 *dfnorms = 0;
  TH2 *tnorms = 0;
  TH2 *znorms = 0;
  file->GetObject("fakenorms", fnorms);
  file->GetObject("difakenorms", dfnorms);
  file->GetObject("topnorms", tnorms);
  file->GetObject("zllnorms", znorms);

  TCanvas *canvas = new TCanvas("canvas","canvas",0,0,800,600);
  TPad *upper_pad = new TPad("upper_pad","upper",0,0.18,1,1);
  TPad *lower_pad = new TPad("lower_pad","lower",0,0,1,0.30);
  canvas->cd();
  upper_pad->Draw();
  lower_pad->Draw();
  
  TString region[] = {"fake","zll","test_mll_c2","test_met_c2", "test_ptl1_c2", "test_ptl2_c2","test_x1_c2","test_x2_c2",
  										"test_ptH_c2", "test_dphill_c2","test_detall_c2"};
  TString channels[] = {"mm","em","me","ee"};
  TString jets[] = {"0jet","1jet"};
  
  for(int t = 0; t < 10; t++)
  {
		for(int c = 0; c < 4; c++)
		{
			for(int j = 0; j < 2; j++)
			{
				TString name("");
				TString data_key(region[t]+"_");
				TString mc_key(region[t]+"_");
				TString mc_fake_key(region[t]+"_");
				TString mc_difake_key(region[t]+"_");
				TString fake_key(region[t]+"_");
				TString difake_key(region[t]+"_");
				TString top_key(region[t]+"_");
				TString top_fake_key(region[t]+"_");
				TString top_difake_key(region[t]+"_");
				TString zll_key(region[t]+"_");
				TString zll_fake_key(region[t]+"_");
				TString zll_difake_key(region[t]+"_");
				TString outFilename(out);
				data_key += jets[j]+"_"+channels[c]+"_data";
				mc_key += jets[j]+"_"+channels[c]+"_mc";
				mc_fake_key += jets[j]+"_"+channels[c]+"_mc_fake";
				mc_difake_key += jets[j]+"_"+channels[c]+"_mc_difake";
				fake_key += jets[j]+"_"+channels[c]+"_fake";
				difake_key += jets[j]+"_"+channels[c]+"_difake";
				top_key += jets[j]+"_"+channels[c]+"_top";
				top_fake_key += jets[j]+"_"+channels[c]+"_top_fake";
				top_difake_key += jets[j]+"_"+channels[c]+"_top_difake";
				zll_key += jets[j]+"_"+channels[c]+"_zll";
				zll_fake_key += jets[j]+"_"+channels[c]+"_zll_fake";
				zll_difake_key += jets[j]+"_"+channels[c]+"_zll_difake";
				outFilename += "/" + region[t] + "_" + jets[j]+"_"+channels[c]+"_fake.png";
				name += jets[j]+" "+channels[c];
				
				double fnorm = fnorms->GetBinContent(fnorms->GetXaxis()->FindBin(channels[c]),fnorms->GetYaxis()->FindBin(jets[j]));
				double dfnorm = dfnorms->GetBinContent(dfnorms->GetXaxis()->FindBin(channels[c]),dfnorms->GetYaxis()->FindBin(jets[j]));
				double tnorm = tnorms->GetBinContent(tnorms->GetXaxis()->FindBin(channels[c]),tnorms->GetYaxis()->FindBin(jets[j]));
				double znorm = znorms->GetBinContent(znorms->GetXaxis()->FindBin(channels[c]),znorms->GetYaxis()->FindBin(jets[j]));
				double fnormerr = fnorms->GetBinError(fnorms->GetXaxis()->FindBin(channels[c]),fnorms->GetYaxis()->FindBin(jets[j]));
				double dfnormerr = fnorms->GetBinError(fnorms->GetXaxis()->FindBin(channels[c]),fnorms->GetYaxis()->FindBin(jets[j]));
				double tnormerr = tnorms->GetBinError(tnorms->GetXaxis()->FindBin(channels[c]),tnorms->GetYaxis()->FindBin(jets[j]));
				double znormerr = znorms->GetBinError(znorms->GetXaxis()->FindBin(channels[c]),znorms->GetYaxis()->FindBin(jets[j]));
				
				file->GetObject(data_key.Data(), data);
				file->GetObject(mc_key.Data(), mc);
				file->GetObject(mc_fake_key.Data(), mc_fake);
				file->GetObject(mc_difake_key.Data(), mc_difake);
				file->GetObject(fake_key.Data(), fake);
				file->GetObject(difake_key.Data(), difake);
				file->GetObject(top_key.Data(), top);
				file->GetObject(top_fake_key.Data(), top_fake);
				file->GetObject(top_difake_key.Data(), top_difake);
				file->GetObject(zll_key.Data(), zll);
				file->GetObject(zll_fake_key.Data(), zll_fake);
				file->GetObject(zll_difake_key.Data(), zll_difake);
		
				TH1 *fnormhist = new TH1F("fnormhist","fnormhist",fake->GetNbinsX(), fake->GetXaxis()->GetXmin(), fake->GetXaxis()->GetXmax());
				TH1 *dfnormhist = new TH1F("dfnormhist","dfnormhist",difake->GetNbinsX(), difake->GetXaxis()->GetXmin(), difake->GetXaxis()->GetXmax());
				TH1 *tnormhist = new TH1F("tnormhist","tnormhist",top->GetNbinsX(), top->GetXaxis()->GetXmin(), top->GetXaxis()->GetXmax());
				TH1 *znormhist = new TH1F("znormhist","znormhist",zll->GetNbinsX(), zll->GetXaxis()->GetXmin(), zll->GetXaxis()->GetXmax());
				for(int i = 0; i <= fake->GetNbinsX()+1; i++)
				{
					dfnormhist->SetBinContent(i, dfnorm);
					dfnormhist->SetBinError(i, dfnormerr);
					fnormhist->SetBinContent(i, fnorm);
					fnormhist->SetBinError(i, fnormerr);
					tnormhist->SetBinContent(i, tnorm);
					tnormhist->SetBinError(i, tnormerr);
					znormhist->SetBinContent(i, znorm);
					znormhist->SetBinError(i, znormerr);
				}
				//******** Draw Upper Pad
				
				upper_pad->cd();
				upper_pad->SetLogx(false);
				upper_pad->SetLogy(true);
				
				data->Sumw2();
				data = overflow(data);
				data->SetMarkerStyle(20);
				data->SetMarkerColor(kBlack);
				data->SetMarkerSize(0.9);
				data->GetXaxis()->SetTitle(name);
				data->GetXaxis()->SetNoExponent(kTRUE);
				data->GetYaxis()->SetTitle("Events");
				data->GetYaxis()->SetTitle("Events");
				data->GetYaxis()->SetRangeUser(0.1, data->GetMaximum()*2);
				data->Draw("e");

				if(t < 2)
				{
					top_fake->Multiply(tnormhist);
					top_difake->Multiply(tnormhist);
				}
			
				mc->SetFillStyle(1001);
				mc->SetFillColor(kOrange);

				fake->Add(top_fake);
				fake->Add(zll_fake);
				fake->Add(mc_fake);
				fake->SetFillStyle(1001);
				fake->SetFillColor(kGreen);

				difake->Add(top_difake);
				difake->Add(zll_difake);
				difake->Add(mc_difake);
				difake->SetFillStyle(1001);
				difake->SetFillColor(kYellow);

				top->SetFillStyle(1001);
				top->SetFillColor(kBlue);
				zll->SetFillStyle(1001);
				zll->SetFillColor(kRed);

				if(t < 2)
				{
					difake->Multiply(dfnormhist);
					fake->Multiply(fnormhist);
					top->Multiply(tnormhist);
					zll->Multiply(znormhist);
				}
	
				delete dfnormhist;
				delete fnormhist;
				delete tnormhist;
				delete znormhist;
				
				THStack *background = new THStack();
				background->Add(overflow(top));
				background->Add(overflow(mc));
				background->Add(overflow(zll));
				background->Add(overflow(fake));
				background->Add(overflow(difake));
				
				for(int i = 0; i < background->GetHists()->GetEntries(); i++)
				{
					TH1 *h1 = (TH1 *)background->GetHists()->At(i);
					int min_index = i;
					double min = h1->Integral(1, h1->GetNbinsX());
					for(int i2 = i+1; i2 < background->GetHists()->GetEntries(); i2++)
					{
						TH1 *h2 = (TH1 *)background->GetHists()->At(i2);
						double n = h2->Integral(1, h2->GetNbinsX());
						if(n < min)
						{
							min_index = i2;
							min = n;
							h1 = h2;
						}
					}
					if(min_index > i)
					{
						background->GetHists()->Remove(h1);
						background->GetHists()->AddAt(h1,i);
					}
				}
	
				background->Draw("histsame");
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
				for(int k = 0; k < background->GetHists()->GetEntries(); k++)
				{
					TH1 *hist = (TH1 *)background->GetHists()->At(k);
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
				for(int k = 1; k < background->GetHists()->GetEntries(); k++)
					sumMC->Add((TH1 *)background->GetHists()->At(k));
				TH1 *ratio = (TH1 *)data->Clone("ratio");
				ratio->Divide(sumMC);
		
				ratio->SetMarkerStyle(20);
				ratio->SetMarkerColor(kBlack);
				ratio->SetMarkerSize(0.9);
				ratio->SetMaximum(1.5);
				ratio->SetMinimum(0.5);
		//		ratio->SetMaximum(10);
		//		ratio->SetMinimum(0);
				ratio->GetXaxis()->SetTitle(name);
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
				
				TH1 *errors = (TH1 *)sumMC->Clone("ratio");
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
	}
}
