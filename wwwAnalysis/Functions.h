#ifndef __Functions__
#define __Functions__


#include <vector>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TVector2.h>
#include <TH1.h>

#include "SampleHandler/Sample.h"
//class Sample;

using namespace std;
namespace wwwAnalysis {

double AngleMin(const TLorentzVector* vect1,const TVector3* vect2);
double CosThetaStar(const TLorentzVector* vect1,const TLorentzVector* vect2);
double TransMass(double Eet,double met,double phie,double phinu);
void ExchangeResults(double &p1,double &p2);
double GetPt(double eta,double E,double phi);
void GetPzNeutrino(TLorentzVector* El,TVector2* MEt,double& delta,double& sol1,double& sol2,double& en1,double&en2);
double DeltaRPart(double eta_jet,double eta_part,double phi_jet,double phi_part);
double Get3MT(TLorentzVector* e,TVector2* recomet,TLorentzVector* gamma);
double Get3MT(TLorentzVector* e,TLorentzVector* recomet,TLorentzVector* gamma);
double GetMT(const TLorentzVector &p,const TVector2 &recomet);
double GetLikelyMass(const TLorentzVector &, const TLorentzVector &, const TVector2 &);
double x1(const TLorentzVector &, const TLorentzVector &, const TVector2 &);
double x2(const TLorentzVector &, const TLorentzVector &, const TVector2 &);
int GetNEventFromFile(SH::Sample *sh);
int GetNEventFromFilteredFile(SH::Sample *sh);
TH1 *scaleHist(TH1 *, double, double);
TH1 *scaleLumi(TH1 *, double);

struct OutputInformations {
	int quad_lep1;
	int quad_lep2;
	int quad_lep3;
	int quad_lep4;
	bool dilep;
	bool quadlep;
	double dilep_mll;
	double dilep_mT1;
	double dilep_mT2;
	double dilep_SumHPTO;
	double dilep_SumCosDphi;
	double quadlep_m12;
	double quadlep_m34;
	};
};
#endif
