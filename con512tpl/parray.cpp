//---------------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <iomanip>
#include "nr.h"
#include "nums.hh"
#include "main.hh"
#include "modlab.h"
//---------------------------------------------------------------------------
using namespace std;
using namespace Label;
//parameters:
const int qp_FS(0), rqp_FS(qp_FS+1), FS_c1(rqp_FS+1), rFS_c1(FS_c1+1), qp_bl(rFS_c1+1), rqp_bl(qp_bl+1), bl_bh(rqp_bl+1), rbl_bh(bl_bh+1), bh_qn1(rbl_bh+1), rbh_qn1(bh_qn1+1), bh_qn2(rbh_qn1+1), rbh_qn2(bh_qn2+1), qHbnd(rbh_qn2+1), rqHbnd(qHbnd+1), qnbnd(rqHbnd+1), rqnbnd(qnbnd+1), qpdis(rqnbnd+1), rqpdis(qpdis+1), qhnds(rqpdis+1),rqhnds(qhnds+1), vc1c(rqhnds+1), bypas(vc1c+1), vros(bypas+1), vfadf(vros+1), vfadr(vfadf+1), vbq1(vfadr+1), vrbq1(vbq1+1), vbq2(vrbq1+1), vrbq2(vbq2+1), vqdis(vrbq2+1), vrqdis(vqdis+1), vqbind(vrqdis+1), vrqbind(vqbind+1), vfred(vrqbind+1), vrfred(vfred+1), vn56(vrfred+1), vrn56(vn56+1), vn2qn1(vrn56+1), vrn2qn1(vn2qn1+1), vn2qn2(vrn2qn1+1), vrn2qn2(vn2qn2+1), vndis(vrn2qn2+1), vrndis(vndis+1), vpbind(vrndis+1), vrpbind(vpbind+1), ptp(vrpbind+1), vlk(ptp+1), vatsyn(vlk+1), vatpase(vatsyn+1), vGl(vatpase+1), vldh(vGl+1), vlacdif(vldh+1), vcs(vlacdif+1), vtca(vcs+1), akgsuc(vtca+1), vmdh(akgsuc+1), vmdhc(vmdh+1), vasp_atf(vmdhc+1), vasp_atr(vasp_atf+1), vmalakg(vasp_atr+1), vgluasp(vmalakg+1),vK(vgluasp+1), vglu_akg(vK+1), vglu_tr(vglu_akg+1), vgluout(vglu_tr+1),  vgluOH(vgluout+1), katase(vgluOH+1), vperos(katase+1), rct(vperos+1), ntmax(rct+1), glu_o(ntmax+1), laco(glu_o+1), k_o(laco+1), Na_o(k_o+1), nNV(Na_o+1);

//concentrations:
const int nqh(0), npsi(nqh+1), nnad(npsi+1), nnadc(nnad+1), npyr(nnadc+1), nsuc(npyr+1), nfum(nsuc+1), nfumc(nfum+1), noaa(nfumc+1), noaac(noaa+1), ncit(noaac+1), nakgm(ncit+1), nakgc(nakgm+1), nglum(nakgc+1), nglu(nglum+1), ngluo(nglu+1), naspm(ngluo+1), naspc(naspm+1), nca(naspc+1), nc1ros(nca+1), nc2ros(nc1ros+1), nc3ros(nc2ros+1), nk_i(nc3ros+1), npsio(nk_i+1), nNa_i(npsio+1), nAdp(nNa_i+1), nAtp(nAdp+1), neo(nAtp+1), nei(neo+1), nlac(nei+1), numx(nlac+1);
//fluxes:
const int fsdh(0), fsm(fsdh+1), fc1c(fsm+1), fme(fc1c+1), fpyrt(fme+1), fcs(fpyrt+1), ftca(fcs+1), fuoa(ftca+1), fatps(fuoa+1), flk(fatps+1), fbp(flk+1), fc1(fbp+1), fc2(fc1+1), flkc1(fc2+1), nflx(flkc1+1);

int Parray::par[nNV+1];
double Parray::nv[nNV];
string Parray::pname[nNV];
double Parray::frw[nNV];

void Parray::stflx(){for(int i=0;i<nflx;i++) fstore[i]=flx[i];}
void Parray::read(const char fn[],bool flg){
	int i; string sss;
	char com[30]; cout<<fn<<endl;
	ifstream fi(fn);
        for (i=0;i<nNV;i++) {fi>>com>>pname[i]>>nv[i]; getline(fi,sss);
                       comm.push_back(sss);}
	for(i=1;;i++) {fi>>par[i]; if(par[i]<0){i68= par[i]*(-1); break;}}
	par[0]=i;
	fi >> tf >> xi1 >> xi2;
	for(i=0;i<nflx;i++) fi>>com>>fln[i]>>flx[i]>>flx[i];
	for(i=0;i<rct;i++) frw[i] = nv[i] * nv[rct]; 
	if(flg){ ofstream fo("pars"); fo.precision(16);
	   fo<<"double nvv[]={"<<nv[0];
	   for (i=1;i<nNV;i++) fo<<", "<<nv[i]; fo<<"};\n";
	   fo<<"double ffrw[]={"<<frw[0];
	   for (i=1;i<rct;i++) fo<<", "<<frw[i]; fo<<"};\n";}
}

void Parray::write (int& fnum,double xi,bool flg) const {
         int i; char fn[15]; string aa="aaaaa";
         sprintf(fn,"%i",fnum);
   if(flg) for(int i=fnum+1;;i++) { sprintf(fn,"%i",i);
	   ifstream checkfi(fn);
	   if(!checkfi.good()) { checkfi.close(); fnum=i; break;}
	   checkfi.close();
   }
        ofstream fi(fn);
for (i=0;i<nNV;i++) fi<<i<<" "<<pname[i]<<" "<<nv[i]<<" "<<comm[i]<<'\n';
  for (i=1; i<par[0]; i++) fi << par[i]<<" "; fi<<(i68*(-1))<< endl;
	fi << tf <<" "<<xi<<" "<<xi<<endl;
       for (i=0;i<nflx;i++) fi<<i<<" "<<fln[i]<<" "<<flx[i]<<" "<<fstore[i]<<endl;
	fi.close();
cout <<"Saved File: " <<fnum << ": xi=" << xi  << "; time="<<tf<<endl;
}

void Parray::st2nv(double st[]){ int i;
        for(i=0;i<nNV;i++) nv[i] = st[i];
   for(i=0;i<rct;i++) frw[i] = nv[i] * nv[rct];
        }
        
void Parray::stat(const int NP ){
        Vec_DP a(NP), x1(NP), x2(NP); Vec_INT b(NP),t(NP);
        int i, *pb=&b[0];
        stringstream fn;
 for ( i=1;i<=NP;i++) {b[i-1]=i;
         fn.str(std::string());
	 fn<<i;
       read(fn.str().c_str()); t[i-1]=tf; x1[i-1]=xi1; x2[i-1]=xi2; a[i-1]=(0.*xi1+xi2);
 }
        NR::sort2a(a,b); cout<<"chi min="<<a[0]<<endl;
        cout << "After sorting, Parameter file (xi2) are:" << endl;
	cout.precision(4);
	for (i=0;i<NP;i++) {
		double df=(a[i]-a[0])/0.05;
		if (df<1.0) i68++;
		else if (df<2.71) i90++;
		else if (df<4.0)  i95++;
		else if (df<6.63)  i99++;
		else break;
	} 
	i90 += i68; i95 += i90; i99 += i95;
	cout<<" i95="<<i95<<endl;
	for(i=0;i<i95;i++){
cout<<setw(3)<<b[i]<<" ("<<a[i]<<"; "<<x1[pb[i]]<<"; "<<x2[pb[i]]<<"; "<<t[pb[i]]<<") "; 
if ((i%3)==0) cout<<endl;
	    }
	cout<<endl<<" i99="<<i99<<endl;
	for(i=i95;i<i99;i++){
cout<<setw(3)<<b[i]<<" ("<<a[i]<<"; "<<x1[pb[i]]<<"; "<<x2[pb[i]]<<"; "<<t[pb[i]]<<") "; 
if ((i%3)==0) cout<<endl;
	    }
int chr=NP;//i99;
 for (i=0;i<chr;i++) {
       fn.str(std::string());
       fn<<"mv "<<b[i]<<" "<<i+1<<"a";
		int is=system(fn.str().c_str());
	}
 for (i=chr;i<NP;i++) {
       fn.str(std::string());
       fn<<"rm "<<b[i];
		int is=system(fn.str().c_str());
	}
 for (i=0;i<chr;i++) {
       fn.str(std::string());
       fn<<"mv "<<i+1<<"a "<<i+1;
		int is=system(fn.str().c_str());
	}
readst();
	cout<<"selected " <<i99<<" from "<<NP<<endl;
}

void Parray::readst(){
          int i,ii, tm; char aaa[30], fn[15];
          string com;
	ifstream fi;
        const double *pmp[i99]; cout<<endl;
        double mpar[i99][par[0]+30]; 
 for (int iset=0;iset<i99;iset++) {
	 sprintf(fn,"%i",(iset+1)); 
        read(fn);
	 
	pmp[iset]=&mpar[iset][0];
     for (i=1;i<(par[0]);i++) mpar[iset][i-1]=nv[par[i]];
	i=(par[0]-1); mpar[iset][i]=(double)tf;
	   mpar[iset][i+1]= xi1; 
	   ii=(i+3);
	   
 }
//    cout<<"Parameters:"<<setw(11)<<"mean"<<setw(11)<<"SD"<<setw(11)<<"SE"<<endl;
         wstorefl("statpar.csv", ii, pmp);
}
void Parray::wstorefl (const char fn1[],int numpar,const double** m) {
        ofstream fi(fn1);
   fi << " | %68 min | %90 min | %95 min | %99 min | bestfit" << endl;
//	        for (int j=0;j<parsets;j++) fi<<" "<<j; fi <<endl;
cout<<"numpar="<<numpar<<endl;
	        for (int i=0;i<(numpar);i++) {
		if(i<(par[0]-1)) fi<<pname[par[i+1]]<<" "; 
		 else if(i<(par[0]+2))fi<<"chi2 ";
		 else if(i<(par[0]+7))fi<<"c3sq ";
		 else if(i<(par[0]+12))fi<<"c1sq ";
		 else if(i<(par[0]+17))fi<<"fmnh ";
		 else if(i<(par[0]+22))fi<<"rn2 ";
	double mn=m[0][i], mx=m[0][i];
	        for (int j=0;j<i68;j++) {
			if(m[j][i]>mx) mx=m[j][i];
			else if(m[j][i]<mn) mn=m[j][i];
					        }
   fi << "| " << mx <<" "<< mn <<" ";
	        for (int j=i68;j<i90;j++) {
			if(m[j][i]>mx) mx=m[j][i];
			else if(m[j][i]<mn) mn=m[j][i];
					        }
   fi << "| " << mx <<" "<< mn <<" ";
	        for (int j=i90;j<i95;j++) {
			if(m[j][i]>mx) mx=m[j][i];
			else if(m[j][i]<mn) mn=m[j][i];
					        }
   fi << "| " << mx <<" "<< mn <<" ";
	        for (int j=i95;j<i99;j++) {
			if(m[j][i]>mx) mx=m[j][i];
			else if(m[j][i]<mn) mn=m[j][i];
					        }
   fi << "| " << mx <<" "<< mn <<" | "<< m[0][i] <<endl;
//   cout << (mx+mn)/2. <<" "<< (mx-mn)/2. <<" "<< m[0][i] <<endl;
                }
/* fi<<"tvme              "<<m[0][numpar]; fi <<endl;
 fi<<"chi1              "<<m[0][numpar+1]; fi <<endl;
 fi<<"chi2              "<<m[0][numpar+2]; fi <<endl;
*/
}

