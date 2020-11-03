#include "nr.h"
extern Vec_INT *ija_p;
extern Vec_DP *sa_p;
        const int NMAX=61000;
        Vec_INT ija(NMAX);
        Vec_DP sa(NMAX);
	double sa_a[NMAX];
	int ija_a[NMAX];

void NR::simpr(Vec_I_DP &y, Vec_I_DP &dydx, Vec_I_DP &dfdx, Mat_I_DP &dfdy,
	const DP xs, const DP htot, const int nstep, Vec_O_DP &yout,
	void derivs(const DP, Vec_I_DP &, Vec_O_DP &))
{
	int i,j,nn,RAZMER;
	DP d,h,x;
        const int ITOL=2,ITMAX=75;
        const DP TOL=1.0e-9;
        int ii,iter;
        DP err;

	int n=y.size();
	Mat_DP a(n,n);
	Vec_INT indx(n);
	Vec_DP del(n),ytemp(n),xinit(n);
	h=htot/nstep;
	for (i=0;i<n;i++) {
		for (j=0;j<n;j++) a[i][j] = -h*dfdy[i][j];
		++a[i][i];
	}

        NR::sprsin(a,1.e-10,sa,ija);
//	ludcmp(a,indx,d);
		RAZMER = (ija[n]-1);
		for(i=0;i<RAZMER;i++) {ija_a[i]=ija[i]; sa_a[i] = sa[i];}
	for (i=0;i<n;i++){ xinit[i] = 0.;
		yout[i]=h*(dydx[i]+h*dfdx[i]);}
	ija_p=new Vec_INT(ija_a,NMAX);
        sa_p=new Vec_DP(sa_a,NMAX);
	NR::linbcg(yout,xinit,ITOL,TOL,ITMAX,iter,err);
//	lubksb(a,indx,yout);
	for (i=0;i<n;i++)
		ytemp[i]=y[i]+(del[i]=yout[i]=xinit[i]);
	x=xs+h;
	derivs(x,ytemp,yout);
	for (nn=2;nn<=nstep;nn++) {
		for (i=0;i<n;i++)
			yout[i]=h*yout[i]-del[i];
	NR::linbcg(yout,xinit,ITOL,TOL,ITMAX,iter,err);
//		lubksb(a,indx,yout);
		for (i=0;i<n;i++) ytemp[i] += (del[i] += 2.0*(yout[i]=xinit[i]));
		x += h;
		derivs(x,ytemp,yout);
	}
	for (i=0;i<n;i++)
		yout[i]=h*yout[i]-del[i];
	NR::linbcg(yout,xinit,ITOL,TOL,ITMAX,iter,err);
//	lubksb(a,indx,yout);
	for (i=0;i<n;i++)
		yout[i] = xinit[i] + ytemp[i];
        delete sa_p;
        delete ija_p;
}
