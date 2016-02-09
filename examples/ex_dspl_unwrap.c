#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include "dspl.h"

/* filter order */
#define ORD	6

/* frequency response vector size */
#define N	4000


int main()
{
	double b[ORD+1];	/* filter H(s) numerator coefficients */
	double a[ORD+1];	/* filter H(s) denominator coefficients */	
	double w[N];		/* Angular frequency [rad/s] */
	double hR[N];		/* Frequency response real part */
	double hI[N];		/* Frequency response image part */
	double phi[N];		/* Phase response [rad] */
	HINSTANCE hDSPL;	/* DSPL.DLL handle */
	
	int n, res;
	double tw;
		
	/* load DSPL */
	hDSPL = dspl_load();

	/* print DSPL version */
	dspl_get_version(1);

	/* Butterworth filter analog prototype calculation */
	printf("Butterworth analog LPF prototype..........");
	res = dspl_butter_ap(3.0, ORD, b, a);
	dspl_print_err(res, 1);
		
	/* fill angular freq. vector from 0.01 rad/s to 100 rad/s*/
	dspl_logspace(-2, 2, N, DSPL_SYMMETRIC,  w);	
	
	/* calculate filter frequency response */
	printf("Frequency response calculation............");
	res = dspl_freqs(b, a, ORD, w, N, hR, hI);
	dspl_print_err(res, 1);
	
	/* Calculate phase response */	
	for (n = 0; n < N; n++)
		phi[n] = atan2(hI[n], hR[n]);
	
	/* save initial phase response to "dat/ex_dspl_phase.txt" */ 
	dspl_writetxt(w, phi, N, "dat/ex_dspl_phase.txt");
	
	printf("Unwrap phase response.....................");
	res = dspl_unwrap(phi, N, M_PI, 0.8);
	dspl_print_err(res, 1);
	
	/* save unwrap phase response to "dat/ex_dspl_unwrap.txt" */ 
	dspl_writetxt(w, phi, N, "dat/ex_dspl_unwrap.txt");
	
	/* clear DSPL handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
