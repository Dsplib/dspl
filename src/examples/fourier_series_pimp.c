#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


/* DFT size */
#define K 13
#define Q 120
#define P 1200

/* sample rate */
#define T	5.0



double trapz(double *x, double *y, int n)
{
	int k;
	double s = 0.0;
	for(k=1; k<n; k++)
	{
		s+=0.5*(y[k-1]+y[k])*(x[k]-x[k-1]);
	}
	return s;
}


int main()
{

	HINSTANCE hDSPL;		/* dspl handle 				*/
	
	/* DTMF frequency vector 	*/
	int N[K] = {2, 3, 4, 6, 9, 12, 16, 20, 25, 40, 60, 80, Q};
	int m, k, n;
	/* DTMF DFT indexes (N = 205)	*/
	double    t[P];
	double    s[P];
	double    sa[P], sb[P];
	double    tp[3*P], S[3*P];
	
	double a[Q+1], b[Q+1], w;
	char fn[500];


    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	
	memset(s, 0, P*sizeof(double));
	dspl_linspace(-T/2,   T/2,    P,  DSPL_PERIODIC,   t);
	dspl_linspace(-3*T/2, 3*T/2,  3*P, DSPL_PERIODIC,   tp);
	
	for(k = P/4; k < 3*P/4; k++)
		s[k] = 1.0;
	
	
	
	memcpy(S,        s, P*sizeof(double));
	memcpy(S+P,      s, P*sizeof(double));
	memcpy(S+2*P,    s, P*sizeof(double));
	dspl_writetxt(tp, S, 3*P, "dat/fourier_series_lim.csv");
	
	memset(S,    0, 3*P*sizeof(double));
	dspl_writetxt(tp, S, 3*P, "dat/fourier_series_lim_0.csv");
	
	a[0] = trapz(t,s,P)/T;
	b[0] = 0.0;
	
	for(m = 1; m<Q+1; m++)
	{
		memcpy(sa,s,P*sizeof(double));
		memcpy(sb,s,P*sizeof(double));
		w = M_2PI / T * (double)m;
		for(k = 0; k < P; k++)
		{
			sa[k]*=cos(w*t[k]);
			sb[k]*=sin(w*t[k]);
		}
		a[m] = trapz(t,sa,P)*2.0/T;
		b[m] = trapz(t,sb,P)*2.0/T;
	}
    
	for(m = 0; m < K; m++)
	{
		for(k = 0; k < P; k++)
			sa[k] = a[0];
		
		for(n = 1; n<N[m]; n++)
		{
			w = M_2PI / T * (double)n;
			for(k = 0; k < P; k++)
				sa[k] += a[n] * cos(w*t[k]) + b[n] * sin(w*t[k]);
		}
		
		memcpy(S,        sa, P*sizeof(double));
		memcpy(S+P,      sa, P*sizeof(double));
		memcpy(S+2*P,    sa, P*sizeof(double));
		memset(fn, 0, 500);
		sprintf(fn,"dat/fourier_series_lim_%d.csv", m+1);
		
		dspl_writetxt(tp, S, 3*P, fn);
	}
	
	
	
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	
	return 0;
}
