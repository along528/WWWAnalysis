#include "wwwAnalysis/Functions.h"
#include <iostream>
#include "TMath.h"
#include "TLorentzVector.h"

#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"

double wwwAnalysis::CosThetaStar(const TLorentzVector* mother,const TLorentzVector* daughter){
TLorentzVector TL1=*(mother);
TLorentzVector TL2=*(daughter);
TL2.Boost(-TL1.BoostVector());
return TMath::Cos(TL2.Angle(TL1.Vect()));
}


void wwwAnalysis::ExchangeResults(double &p1,double &p2){
double tmp=0;
if(TMath::Abs(p2)<TMath::Abs(p1)){
	tmp=p2;
	p2=p1;
	p1=tmp;
	}
	return;
}

double wwwAnalysis::AngleMin(const TLorentzVector* vect1,const TVector3* vect2){
TLorentzVector lep=*vect1;
return lep.Angle(*vect2);
}


double wwwAnalysis::TransMass(double Eet,double met,double phie,double phinu){
return TMath::Sqrt(2*Eet*met*(1-TMath::Cos(phie-phinu)));
}


double  wwwAnalysis::GetPt(double eta,double E,double phi){
float theta = 2*atan2((double)exp(-eta),1.);
float px=E*sin(theta)*cos(phi);
float py=E*sin(theta)*sin(phi);
return sqrt(pow(px,2)+pow(py,2));
}


void wwwAnalysis::GetPzNeutrino(TLorentzVector* e,TVector2* recomet,double& delta,double& sol1,double& sol2,double& en1,double&en2){
double mw=80403;
delta=0,en1=0,en2=0,sol1=0,sol2=0;

delta=16*pow(e->E(),2)*(4*(pow(recomet->Px(),2)+pow(recomet->Py(),2))*(pow(e->Pz(),2)-pow(e->E(),2))+pow((pow(mw,2)+2*(recomet->Px()*e->Px()+recomet->Py()*e->Py())),2));

double a=4*(pow(e->Pz(),2)-pow(e->E(),2));
double b=4*e->Pz()*(pow(mw,2)+2*(recomet->Px()*e->Px()+recomet->Py()*e->Py()));

if(delta<0){
//std::cout<<"imaginary solution"<<std::endl;
sol1=(-b)/(2*a);
sol2=(-b)/(2*a);
}

else
{
sol1=(-b+sqrt(delta))/(2*a);
sol2=(-b-sqrt(delta))/(2*a);
}

wwwAnalysis::ExchangeResults(sol1,sol2);
en1=sqrt(recomet->Px()*recomet->Px()+recomet->Py()*recomet->Py()+sol1*sol1);
en2=sqrt(recomet->Px()*recomet->Px()+recomet->Py()*recomet->Py()+sol2*sol2);
}


double wwwAnalysis::DeltaRPart(double eta_jet,double eta_part,double phi_jet,double phi_part){
 Double_t deta = eta_jet-eta_part;
 Double_t dphi = TVector2::Phi_mpi_pi(phi_jet-phi_part);
 return sqrt( deta*deta+dphi*dphi );
}

double wwwAnalysis::Get3MT(TLorentzVector* e,TLorentzVector* recomet,TLorentzVector* gamma){
TLorentzVector egamma=*e+*gamma;
return sqrt(pow((sqrt(pow(egamma.M(),2)+pow(egamma.Pt(),2)) + recomet->Pt()),2) - pow((egamma.Px()+recomet->Px()),2) - pow((egamma.Py()+recomet->Py()),2)); 
}


double wwwAnalysis::Get3MT(TLorentzVector* e,TVector2* recomet,TLorentzVector* gamma){
TLorentzVector egamma=*e+*gamma;
return sqrt(pow((sqrt(pow(egamma.M(),2)+pow(egamma.Pt(),2)) + recomet->Mod()),2) - pow((egamma.Px()+recomet->Px()),2) - pow((egamma.Py()+recomet->Py()),2)); 
}
double wwwAnalysis::GetMT(const TLorentzVector &p,const TVector2 &recomet) {
	return sqrt(pow((sqrt(pow(p.M(),2)+pow(p.Pt(),2)) + recomet.Mod()),2) - pow((p.Px()+recomet.Px()),2) - pow((p.Py()+recomet.Py()),2)); 
}

double wwwAnalysis::GetLikelyMass(const TLorentzVector &lep1, const TLorentzVector &lep2, const TVector2 &recomet){
TLorentzVector tauNeutrinos,All;
double tauNeutrinoP = sqrt(pow(recomet.Px(),2)+pow(recomet.Py(),2)+pow(lep1.Pz() + lep2.Pz(),2));
double leptonsP = sqrt(pow(lep1.Px()+lep2.Px(),2)+pow(lep1.Py()+lep2.Py(),2)+pow(lep1.Pz()+lep2.Pz(),2));
double tauNeutrinosE = ((lep1.E()+lep2.E())/(leptonsP))*tauNeutrinoP;
tauNeutrinos.SetPxPyPzE(recomet.Px(),recomet.Py(),lep1.Pz() + lep2.Pz(),tauNeutrinosE);
All=lep1+lep2+tauNeutrinos;
return All.M();
}

double wwwAnalysis::x1(const TLorentzVector &lep1, const TLorentzVector &lep2, const TVector2 &met)
{
  return (lep1.Px()*lep2.Py() - lep1.Py()*lep2.Px()) /
          (lep2.Py()*(met.X()+lep1.Px()) - lep2.Px()*(met.Y()+lep1.Py())); 
//  return (lep1->Pt()+lep2->Pt())/(lep1->Pt()+lep2->Pt()+recomet->Mod());
}
double wwwAnalysis::x2(const TLorentzVector &lep1, const TLorentzVector &lep2, const TVector2 &met)
{
  return (lep1.Py()*lep2.Px() - lep1.Px()*lep2.Py()) /
          (lep1.Py()*(met.X()+lep2.Px()) - lep1.Px()*(met.Y()+lep2.Py())); 
//  return (lep1->Pt()+lep2->Pt())/(lep1->Pt()+lep2->Pt()+recomet->Mod());
}


int wwwAnalysis::GetNEventFromFile(SH::Sample *sh)
{
  int totalNum = 0;
  for(std::size_t j = 0; j < sh->numFiles(); j++){
				TFile *file = new TFile(sh->fileName(j).c_str());
				TH1 *h_sum = (TH1 *)file->Get("h_sumwt");
				if(!h_sum){
				TTree* tree=(TTree*)file->Get("physics");
				totalNum +=tree->GetEntries();
				}
				else{
				totalNum += h_sum->GetBinContent(1);
				}
				file->Close();
	}
  return totalNum;
}

int wwwAnalysis::GetNEventFromFilteredFile(SH::Sample *sh)
{
  int totalNum = 0;
  for(std::size_t j = 0; j < sh->numFiles(); j++){
				TFile *file = new TFile(sh->fileName(j).c_str());
				TH1 *h_sum = (TH1 *)file->Get("FilterEfficiencyUnweighted");
				if(!h_sum){
				TTree* tree=(TTree*)file->Get("physics");
				totalNum +=tree->GetEntries();
				}
				else{
				totalNum += h_sum->GetBinContent(1);
				}
				file->Close();
	}
  return totalNum;
}

TH1 *wwwAnalysis::scaleHist(TH1 *hist, double scale, double error)
{
	TH1 *shist = new TH1F("shist","shist",hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
	for(int i = 0; i <= hist->GetNbinsX()+1; i++)
	{
		shist->SetBinContent(i, scale);
		shist->SetBinError(i, error);
	}
	hist->Multiply(shist);
	delete shist;
	shist = 0;
	return hist;
}
TH1 *wwwAnalysis::scaleLumi(TH1 *hist, double scale)
{
	return scaleHist(hist, scale, scale*0.035);
}

