#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm> 
#include "nr.h"
#include "StiffIntegratorT.h"
#include "NonStiffIntegratorT.h"
#include "nums.hh"
#include "modlab.h"
#include "main.hh"
//---------------------------------------------------------------------------
using namespace std;
using namespace Label;
  vector<double> vx;

void isores(const double& T, double y[],const double yprime[], double delta[], int& iRes, const double rPar[], const int iPar[]){
       double f[NN];
	horse.distr(y, f);
	for(unsigned i=0;i<NN;i++) delta[i]=f[i]-yprime[i];
}
void jac(const double& time,  double y[], const double yPrime[], double dfdy[][3], double& CJ, const double rPar[], const int iPar[]){}

int Ldistr::ddisolve(int istart,const double tfin, double *py,ostringstream& fkin) {
  int info[15],idid=0,lrw=200000,liw=500,iwork[500],ipar[2];
  double tinc=0.02*tfac,to,rtol=0.001,atol=1.0e-9,h0=1e-5, hmax=2.;
  double t=istart*tinc,term=tfin*tfac,rpar[2], yprime[NN], rwork[200000];
  rwork[1]=hmax; rwork[2]=h0;
  for(int i=0;i<15;i++) info[i]=0;   info[6]=1; info[10]=1;
  distr(py, yprime);
//   for(int i=0;i<NN;i++) cout<<i<<") "<<py[i]<<"  "<<yprime[i]<<'\n';
  istart++; to=t+tinc;
  while(to<term){
     ddassl_(isores,NN,t,py,yprime,to,info,rtol,atol,idid, rwork, lrw, iwork, liw, rpar, ipar, jac);
     if(idid==-1) { atol=1.0e-7; distr(py, yprime); info[0]=1; idid=0;
       ddassl_(isores,NN,t,py,yprime,to,info,rtol,atol,idid, rwork, lrw, iwork, liw, rpar, ipar, jac); }
     if(idid<-1) { throw("dassl problem");}
     sdev[istart] = nadh; fiout(to,fkin,istart-1); 
     t=to;
     istart++; to += tinc;
     }
  write("i0");
     return istart;}

void Ldistr::chast(double *py, double tint) {
  ostringstream fkin,fkont;  conc[nc2ros]=0.; conc[nc3ros]=0.; ifin1=0;
// py[nmet+nglu]=nv.nv[suc_o];
//  ifin1= ddisolve(0,tint,py,fkin);
//  setconc(nca,20.);
//  ifin1= ddisolve(ifin1,0.5,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,1.0,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,1.5,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,2.,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,2.5,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,3.0,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,3.5,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,4.,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,4.5,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,5.,py,fkin); setconc(nca,20.);
//  ifin1= ddisolve(ifin1,5.5,py,fkin); setconc(nca,20.);
//  double s=nv.setval(vlk,15.); // leak
//  ifin1= ddisolve(ifin1,2.0,py,fkin);
//  double a7=nv.setval(ptp, 0.1);	//PTP open 
//	ifin1= ddisolve(ifin1,3.0,py,fkin);
//  	nv.setval(ptp, a7);		//PTP close
//  double a6=nv.setval(qHbnd, 0.0000);//myxothiazol
//  ifin1= ddisolve(ifin1,3.0,py,fkin);
//  double a5=nv.setval(vgluout, 0.); // glutamate
//  ifin1= ddisolve(ifin1,3.0,py,fkin);
//  double a1=nv.setval(qnbnd, 0.0);//antimycine
//  ifin1=ddisolve(ifin1,4.0,py,fkin);
//  double a6=nv.setval(qHbnd, 0.0000);//myxothiazol
	ifin1= ddisolve(ifin1,tint,py,fkin);
//	fiout(tint,fkont,1); 
cout <<" qh= "<< conc[nqh]<<" psi= "<< conc[npsi]<<" nad= "<< conc[nnad]; 
	cout <<" nadc= "<< conc[nnadc]<<"\n";// 
	cout <<" pyr= "<< conc[npyr]<<"\tlac= "<< conc[nlac]<<"\n";// 
	cout <<" suc= "<< conc[nsuc]<<"\tfum= "<< conc[nfum]<<"\n";// 
	cout <<" AKGm= "<< conc[nakgm]<<"\tAKGc= "<< conc[nakgc]<<"\n"; 
	cout <<" OAm= "<< conc[noaa]<<"\tOAc= "<< conc[noaac]<<"\n";// 
	cout <<" cit= "<< conc[ncit]<<"\n";// 
	cout <<" glu= " << conc[nglu]<<"\tglum= " << conc[nglum]<<"\n"; 
	cout <<" Aspm= " << conc[naspm]<<"\tAspc= " << conc[naspc]<<"\n"; 
//  nv.setval(vlk,s); // leak
//  nv.setval(vgluout, a5); // glutamate
//  nv.setval(qnbnd, a1);//antimycine
//  nv.setval(qHbnd, a6);//myxothiazol
//	fkin.str(std::string());
//	fkont.str(std::string());
//	ifin1= ddisolve(0,tint,py,fkin);
	fiout(tint,fkont,1); 
	write("ii");
	kont = fkont.str();
  kkin=fkin.str();
  }

inline void zerowsmal(Vec_DP& w, double cond, int n) {
	double wmax=0.0; int i;
	for (i=0;i<n;i++) if (w[i] > wmax) wmax=w[i];
//            cout<<"wmax=" << wmax<< endl;
	double wmin=wmax*cond;
// zero the "small" singular values
	for(i=0;i<n;i++) if(w[i] < wmin) w[i]=0.0;
}

void first(double *y,int ipar,double pint,double step){
	Vec_DP w(NN+1), c(NN+1), dx(NN+1);
	double x, sum(0), dp=pint*step, dy[NN+1], *rhs=&c[0], *df[NN+1];
	Mat_DP a(NN+1,NN+1), u(NN+1,NN+1),v(NN+1,NN+1);
	int i,j;
	init_ydot(y,ipar,dp,dy,rhs,NN);
	for(i=0;i<=NN;i++) {
	  df[i]=&u[i][0]; u[i][NN]=rhs[i]/dp; rhs[i] *= -1;}
	Jacobian(dp, y, df);
	for(i=0;i<=NN;i++)  u[NN][i]=dy[i]; rhs[NN]=0.000001;
// copy u
	for(i=0;i<=NN;i++)
	   for(j=0;j<=NN;j++) a[i][j]=u[i][j];
// SVD of u
	NR::svdcmp(u,w,v);
	zerowsmal(w, 1e-12, NN+1);
	  
// next vector y
	NR::svbksb(u,w,v,c,dx);
	double wmax=0.0;
	for ( i=0;i<NN;i++) {y[i]+=dx[i];
	  if(fabs(dx[i])>wmax) wmax=fabs(dx[i]);}
	cout << "--- dy max is: "<<wmax << endl;
	horse.nv.setval(ipar,y[NN]);
	
// next vector dy
	for(i=0;i<NN;i++) rhs[i] = 0;
	 rhs[NN]=1;
	NR::svbksb(u,w,v,c,dx);
	wmax=0.0;
	for ( i=0;i<NN;i++) if(fabs(dx[i])>wmax) wmax=fabs(dx[i]);
	cout << "---  max of dy: "<<wmax << endl;
	
//	  horse.distr(y, rhs);
	ydot(y,ipar,dp,dy,rhs,NN);
//	jsvd(y, w, u, v, a,1e-11,NN);
//	  horse.distr(y, rhs);
//	  double cmax=0;
//	  for (int i=0;i<NN;i++) {
//	    rhs[i] *= (-1.);
//	    if(fabs(c[i])>cmax) cmax=fabs(c[i]);
//	    if(cmax>1e4) {cout<<"max rhs** "<<cmax << endl; throw "error";}
//	  } cout<<cmax<<endl;
//	neuton(y,c, w, u, v, a,NN);
	
	sum=0;
	for(i=0;i<=NN;i++) {sum += dx[i]*dx[i];}
	sum=sqrt(sum);
	for(i=0;i<=NN;i++) a[NN][i] = dx[i]/sum;
	horse.distr(y, rhs); 
	Jacobian(dp,y,df);
	for (i=0;i<=NN;i++)
	   for (j=0;j<=NN;j++) a[i][j]= u[i][j];
	NR::svdcmp(u,w,v);
	zerowsmal(w, 1e-11, NN);
// a new vector a[NN][i]
	for(i=0;i<=NN;i++)
	   for(j=0;j<=NN;j++) u[i][j]=a[i][j];
}
void init_ydot(double *y,int ipar,double dp,double *ydot,double *c1,const int n){
	Vec_DP c(n), w(n);
	Mat_DP u(n,n),v(n,n);
	int i,j;
	double x, sum(0), y0[n];
	correct(y,c, w, u, v,n);
	for (i=0;i<n;i++) y0[i]= y[i]; //{c0[i]=(c1[i]-c0[i])/dp;}
	double p0=horse.nv.nv[ipar];
// last column c1/dp, rhs= -c1 :
	horse.nv.setval(ipar,p0+dp);
	horse.distr(y, c1); 
// last row ydot;
	correct(y,c, w, u, v,n);
	for(i=0;i<n;i++) {ydot[i]=(y[i]-y0[i])/dp; sum += ydot[i]*ydot[i];}
	sum +=1.; sum=sqrt(sum);
	for(i=0;i<n;i++) ydot[i] /= sum;
	ydot[n]= 1./sum; //-dp/sum-dp;
// back to initial point
//	horse.nv.setval(ipar,p0);
//	for (i=0;i<n;i++) y[i]= y0[i];
}
void ydot(double *y,int ipar,double dp,double *ydot,double *c1,const int n){
	Vec_DP c(n), w(n);
	Mat_DP u(n,n),v(n,n);
	int i,j;
	double x, sum(0), y0[n];
	correct(y,c, w, u, v,n);
}
void correct(double *y,Vec_DP& c,Vec_DP& w,Mat_DP& u,Mat_DP& v,const int n){
	double *rhs=&c[0],cmax; int i,k;
	Mat_DP a(n,n);
	jsvd(y, w, u, v, a,1e-11,n);
	for(k=0;k<5;k++){
	  horse.distr(y, rhs);
	  cmax=0;
//	  jsvd(y, w, u, v,n);
	  for (int i=0;i<n;i++) {
	    rhs[i] *= (-1.);
	    if(fabs(c[i])>cmax) cmax=fabs(c[i]);
	    if(cmax>1e4) {cout<<"max rhs** "<<cmax << endl; throw "error";}
	  }
	  cout << "*max rhs** "<<cmax << endl;
	  if(neuton(y,c, w, u, v, a,n)<1e-7) break;
	}
}
void jsvd(double *y,Vec_DP& w,Mat_DP& u,Mat_DP& v,Mat_DP& a, double cond,const int n){
	double x, *df[n];
	int i,j;
        for(i=0;i<n;i++) df[i]=&u[i][0];
	Jacobian(x,y,df);
	for (i=0;i<n;i++)
	   for (j=0;j<n;j++) a[i][j]= u[i][j];
	NR::svdcmp(u,w,v);
	zerowsmal(w, cond, n);
}
double neuton(double *y,Vec_DP& c,Vec_DP& w,Mat_DP& u,Mat_DP& v,Mat_DP& a,const int n){
//	cout << fixed << setprecision(6);
	Vec_DP dx(n),c1(n),dx1(n); int i,j;
	NR::svbksb(u,w,v,c,dx);
	double wmax=0.0; 
	for ( i=0;i<n;i++){ c1[i] = 0.;
	   for ( j=0;j<n;j++) c1[i] += a[i][j]*dx[j];
	   c1[i] -= c[i];
	   }
	jsvd(y, w, u, v, a,1e-12,n);
	NR::svbksb(u,w,v,c1,dx1);
	wmax=0.0;
	for ( i=0;i<n;i++) { dx[i] -= dx1[i]; y[i]+=dx[i];
	  if(fabs(dx[i])>wmax) wmax=fabs(dx[i]);}
	cout << " max of dx is: "<<wmax << endl;
return wmax; }

void isT::Function(double x, double *y, double *f){
	horse.distr(y, f);
}
void Function(double x, double *y, double *f){
	horse.distr(y, f);
}
//void Jacobian(double x, double *y, double **J){}
void Jacobian(double x, double *y, double **dfdy){
	int i,j;
//	int NN=y.size();
        double dydx0[NN];
        double dydx1[NN];
	double dy,aa;
		horse.distr(y, dydx0);
	for ( i=0;i<NN;i++) { aa=y[i];
	   dy=aa*0.001; if(dy>1.) dy=1.;
		y[i] += dy;
		horse.distr(y, dydx1);
		y[i] = aa;
		for ( j=0;j<NN;j++) 
		  if(dy>1e-12) dfdy[j][i] = (dydx1[j] - dydx0[j]) / dy;
		  else dfdy[j][i] = 0.0;
	}
}

void Mass(double **M){} // Mass
double tisolve(const double tmax,double *yy,int numint){
	// dimension of problem
	// initial value for x
	double xbeg(0.0), xend = tmax, dx(tmax/numint-1);
	// rtoler and atoler are scalars
	int itoler(0);
	// relative tolerance
	double *rtoler = new double(3.0e-2);
	// absolute tolerance
	double *atoler = new double(1.0e-5);
	const int iout(1);
	// initial step size
	double hinit(0.0005);
	// analytical Jacobian function provided
	 int ijac(0);
	// number of non-zero rows below main diagonal of Jacobian
	int mljac(NN);
	// number of non-zero rows above main diagonal of Jacobian
	int mujac(NN);
	// Mass matrix routine is identity
	const int imas(0);
	int mlmas(NN);
	int mumas(0);
	
	// Use default values (see header files) for these parameters:
	double hmax(0.0);
	int nmax(0);
	double uround(0.0), safe(0.), facl(0.0), facr(0.0);
	int nit(0);
	bool startn(false);
	int nind1(0), nind2(0), nind3(0), npred(0), m1(0), m2(0);
	bool hess(false);
	double fnewt(0.0), quot1(0.0), quot2(0.0), thet(0.1);
	
	double beta = 0.007;
	int nstiff = -1;
	int nrdens = NN;
	unsigned *icont = NULL;

	isT stiffT(NN, yy, xbeg, xend, dx, itoler, rtoler, atoler,
		iout, hinit, hmax, nmax, uround, safe, facl, facr, ijac, mljac,
		mujac, imas, mlmas, mumas, nit, startn, nind1, nind2, nind3, npred,
		m1, m2, hess, fnewt, quot1, quot2, thet);

		//	cout << "\n\n*******Problem integrated with RADAU5*******\n\n";
 horse.read();
	stiffT.Integrate();
//	ofstream fi("kinetics");
//     horse.fiout(xend,fi);
	
	delete rtoler;
	delete atoler;
}
void derivsl(const DP x, Vec_IO_DP &y, Vec_O_DP &dydx){
	DP *py=&y[0]; DP *pdydt=&dydx[0];
        nrhs++;
	horse.distr(py, pdydt);
}

double integrbs(const double tmax,Vec_DP &ystart,const int KMAX){
	int i,j; char fn[11]="init";
        DP eps=1.0e-6,h1=0.0001,hmin=1.0e-09,x1=0.0;
        nrhs=0;
        dxsav=tmax/(KMAX-1);
        kmax=KMAX;
        xp_p=new Vec_DP(KMAX);
        yp_p=new Mat_DP(NN,KMAX);
        Mat_DP &yp=*yp_p;
	Vec_DP &xp=*xp_p;
        int nbad,nok;
//	double *py = &ystart[0];
//	horse.setyinit(py);
     try {
        NR::odeint(ystart,x1,tmax,eps,h1,hmin,nok,nbad,derivsl,NR::rkqs);
    }catch( char const* str ){ cout << "exception: "<< str <<endl; 
//    			horse.kinet(xp,yp,kount);
                         throw str;
                         }
//    else if(method==1) NR::odeint(ystart,x1,tmax,eps,h1,hmin,nok,nbad,derivsl,NR::bsstep);if(method==0)
//    else if(method==2) NR::odeint(ystart,x1,tmax,eps,h1,hmin,nok,nbad,derivsl,NR::stifbs);
//    else NR::odeint(ystart,x1,tmax,eps,h1,hmin,nok,nbad,derivsl,NR::stiff);
//    horse.label(ystart,0.1);
//    horse.kinet(xp,yp,kount);
//    for (int i=0;i<NN;i++) yy[i]=yp[i][5];
//    DP *pyy = &yy[0];
//    horse.gety(pyy);
//    horse.label();
        delete yp_p;
        delete xp_p;
return tmax;}
/*
void sens(Vec_DP &ystart,float factor){
   double *py = &ystart[0];
      	horse.setisot(py); 
    ofstream fi("total"); int ii=0;
	horse.tout(0,ii,fi);
  for (int j=1;j<horse.nv.par[0];j++){
    cout<<"parameter "<<horse.nv.par[j]<<" "<<horse.nv.pname[horse.nv.par[j]]<<endl;
   for (int i=0;i<1;i++) {
   horse.nv.read();
    horse.nv.changeval(horse.nv.par[j],factor);
     try {
       solve(py);
    }catch( char const* str ){ cout << "exception: "<< str <<endl; 
                         break; }
	horse.tout(horse.nv.par[j],ii,fi);
	} }
}*/

