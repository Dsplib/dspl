#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		512
#define DMAX	8


int main()
{
	/* input signals */
	double b[DMAX],  a[DMAX];
	double hR[N],  hI[N];
	double H[N], PHI[N];
	double w[N];
	
	//int d = 1;
	int n;
	
	void *pdspl = NULL;
	
	/* dspl handle */
	HINSTANCE hDSPL;
		
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	/* create DSPL object for Hilbert transform */
	dspl_obj_create(&pdspl);
	
	
	dspl_linspace(0.001, M_PI, N, DSPL_PERIODIC, w);
	
	
	memset(b,0,DMAX*sizeof(double));
	memset(a,0,DMAX*sizeof(double));
	b[0] =  1.0;
	a[0] =  1.0;
	a[1] = -1.0;
	
	dspl_freqz(b, a, 1, w, N, hR, hI);
	for(n =0; n<N; n++)
	{
		H[n] = 10.0*log10(hR[n]*hR[n] + hI[n]*hI[n]);
		PHI[n] = atan2(hI[n], hR[n]);
	}

	   
	dspl_writetxt(w,  H,  N,	"dat/cic_integrator_h.txt");
	dspl_writetxt(w,  PHI,  N, 	"dat/cic_integrator_phi.txt");
	
	
	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}

