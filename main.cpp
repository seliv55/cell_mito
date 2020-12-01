//---------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "nr.h"
#include "StiffIntegratorT.h"
#include "NonStiffIntegratorT.h"
#include "nums.hh"
#include "modlab.h"
#include "analis.h"
#include "main.hh"
//---------------------------------------------------------------------------
//#pragma package(smart_init)


using namespace std;
using namespace Label;
extern vector<double> vx;
Ldistr horse;
//int  method=0;
const int NN=horse.setny()+numx, numex=horse.readexp(2,"a011110rbm.txt");
double ystart[500];
DP dxsav;   // defining declarations
DP *yy0, *yy1;
int kmax,kount;
Vec_DP *xp_p;
Mat_DP *yp_p;
Vec_INT *ija_p;
Vec_DP *sa_p;
int nrhs,ifn=0,istor=20001;   // counts function evaluations
Vec_DP *x_p;
Mat_DP *d_p;
    time_t ts,tf,tcal,tfirst;
double tfac, xi1(0), xi2(0);

 double solve(double *py,double tint){
    double xi, y[NN];
    for(int i=0;i<NN;i++) y[i]=py[i];
    ts=clock();
    try { // xi1=tisolve(horse.nv.nv[ntmax], y,99);
       horse.chast( py,tint);
// xi=d02nefsv(horse.nv.nv[ntmax], y,numex,crv,ros);
       tf=clock()-ts;
    }catch( char const* str ){cout <<"exception: "<<str<<endl;
            tf=1.e11; xi=1.e11;}
    return horse.getc3ros();}
    
 double cont(double *py,double tint,char c){
   double pmin, pint;
   int np, chpar; string aaa;
   ifstream fpar("cont");
   fpar>>aaa>>chpar>>aaa>>np>>aaa>>pmin>>aaa>>pint;
   const int nss(np);
   double a,dif,fact(1.0),f1(1.02),ss[2][nss];
   double dp=pint/(float)nss;
   stringstream fn; 
   ofstream fo;
   cout<<"par["<<chpar<<"]="<<horse.nv.nv[chpar]<<'\n'; 
   int j=0;
   double sum(0.),ss1(0.),ss2(0.);
   for(int k=0;k<2;k++){
      cout<<"nss="<<nss<<endl;
      for(int ii=0;ii<(nss+1);ii++){
        if(k) horse.nv.setval(chpar,(pmin+(pint-ii*dp)));
        else horse.nv.setval(chpar,(pmin+ii*dp));
        horse.setisot(py); 
//         horse.read("i1");// read init values
        if(c=='r') ss[k][ii]= horse.rotenone(py,tint);
        if(c=='c') ss[k][ii]= solve(py,tint);
        float ft = float(tf)/CLOCKS_PER_SEC;
     cout<<ii<<" "<<horse.nv.getval(chpar)<<" ψ="<<ss[k][ii]<<" t="<<ft<<'\n';
        fn<<horse.nv.getval(chpar)<<" "<<horse.kont;
        if(ii==nss) break;
        if(ft>3){
          fo.open("dynamics"); fo<<horse.kkin<<endl; fo.close(); 
          ostringstream pltt;
          pltt<< "gnuplot -e \"fn1='dynamics'; fn2='dynamics'; fno='kin/suc.png'; ax="<<tint<<"\" gplt.p";
          int sys=system(pltt.str().c_str());}
        }
   }
   aaa=fn.str(); cout<<aaa;
   ofstream ffo("00000"); ffo<<aaa;
   for(int i=0;i<nss;i++) { dif=abs(ss[0][i]-ss[1][nss-i]);
     if(dif>0.1) cout<<i<<" "<<dif<<"; ";
     sum += dif;
   } cout<< endl;
   cout<<" sum="<<sum<<endl;
return 1.;}


double Ldistr::rotenone(double *py,double tint){
 double a1=nv.setval(vn2qn1, 0.0), a2=nv.setval(vrn2qn1, 0.0), a3=nv.setval(vn2qn2, 0.0), a4=nv.setval(vrn2qn2, 0.0);
  double x=solve(py,tint);
  nv.setval(vn2qn1,a1); nv.setval(vrn2qn1,a2), nv.setval(vn2qn2, a3), nv.setval(vrn2qn2, a4); 
  return x;}

double Ldistr::antimycin(double *py){
  double a1=nv.setval(qnbnd, 0.0), a2=nv.setval(rqnbnd, 0.0),
     a3=nv.setval(qhnds, 0.0), a4=nv.setval(rqhnds, 0.0);
  double x=solve(py,5);
  nv.setval(qnbnd, a1); nv.setval(rqnbnd, a2);
     nv.setval(qhnds, a3); nv.setval(rqhnds, a4);
  return x;}
    
float Ldistr::efit(double *py){
  float xii(0);
  // solve(py); int tf1=tf;  xii=dev(0);
    rotenone(py,5.);  xii += dev(1); // tf += tf1;
     return xii;}

int main( int argc, char *argv[] ){
   cout<<"NN="<<NN<<'\n';
   cout<<"edata "<<argv[1]<<", init values "<<argv[2]<<", parameters " <<argv[3]<<", mode "<<argv[4]<<'\n';
   double x, tint(7.);
   char fn[22];
 //define last parameter-file:
   for(int i=ifn+1;;i++) { sprintf(fn,"%i",i);
	   ifstream checkfi(fn);
	   if(!checkfi.good()) { ifn=i; break;}
	   checkfi.close();
	   }
   horse.setarrays();
 //statistic: if((string)argv[4]=="stat")){horse.nv.stat(ifn); return 0;}
 //calculation: 
 //    deliv_();
   double *py = &ystart[0];  cout.precision(3);
   horse.setisot(&ystart[0]); 
   horse.readexp(2,(string)argv[1]);//read experiment
   horse.read((string)argv[2]);//"i0"); // read init values
   horse.nv.read(argv[3],1);//0-pyr+mal; 1-suc
  //   horse.glufl(); return 0;
   string s(argv[4]);
   tfac=horse.nv.nv[ntmax];
   if (s.size()==1){
     if(s=="0") x=solve(&ystart[0],tint);
     else horse.rotenone(py,tint);
     cout<<"time="<<tf/double(CLOCKS_PER_SEC)<<endl;
     ofstream fo("dynamics"); fo<<horse.kkin<<endl; fo.close(); 
  //   fo.open("rot"); fo<<horse.kkin<<endl; fo.close(); 
     int sys=system("gnuplot -e \"fn1='dynamics'; fn2='dynamics'; fno='kin/dynamics.png'; ax=6.99\" gplt.p");
     horse.nv.write(istor,xi1,0);
   }
   else {
     if(s=="cont")  x=cont(&ystart[0],tint,'c');
     if(s=="rc")  x=cont(&ystart[0],tint,'r');
     int sys=system("gnuplot gparplt.p");
   }
  //start fitting
  //   Analis analis; srand(time(NULL));
  //   if((argc==2)&&(argv[1][0]=='f')) analis.coord(ystart);
  //   if((argc==2)&&(argv[1][0]=='a')) analis.sensitivity(ystart);
}

