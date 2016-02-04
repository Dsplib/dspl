#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include "dspl.h"

/* filter order */
#define ORD	3

/* frequency response vector size */
#define N	1000


int main()
{
	double b[ORD+1];	/* filter H(s) numerator coefficients */
	double a[ORD+1];	/* filter H(s) denominator coefficients */	
	double w[N];		/* Angular frequency [rad/s] */
	double hR[N];		/* Frequency response real part */
	double hI[N];		/* Frequency response image part */
	double h[N];		/* Filter Magnitude [dB] */
	HINSTANCE hDSPL;	/* DSPL.DLL handle */
	
	int n;
		
	/* load DSPL */
	hDSPL = dspl_load();

	/* print DSPL version */
	dspl_get_version(1);

	/* Butterworth filter analog prototype calculation */
	dspl_butter_ap(3.0, ORD, b, a);
	
	/* print filter transfer function coefficients */
	printf("Filter coefficients:\n");
	for (n = 0; n < ORD+1; n++)
		printf("\tb[%d] = %.5f\ta[%d] = %.5f\n", n, b[n], n, a[n]);

		
	/* fill angular freq. vector from 0.01 rad/s to 100 rad/s */
	dspl_logspace(-2.0, 2.0, N, DSPL_SYMMETRIC, w);		

	/* calculate filter frequency response */
	dspl_freqs(b, a, ORD, w, N, hR, hI);
	
	/* Calculate filter magnitude */	
	for (n = 0; n < N; n++)
		h[n] = 10.0*log10(hR[n] * hR[n] + hI[n] * hI[n]);
	
	/* save filter magnitude vector to "dat/ex_dspl_butter_ap.txt" */ 
	dspl_writetxt(w, h, N, "dat/ex_dspl_butter_ap.txt");
	
	/* clear DSPL handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
