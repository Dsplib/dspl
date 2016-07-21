#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		32768
#define NPSD	512
#define FS		2


int main()
{
	/* input signal */
	double xR[N];
	double xI[N];
	
	double psd[NPSD];
	double frq[NPSD]; 
	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	int n;
	void *pdspl = NULL;
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	dspl_obj_create(&pdspl);
	
	dspl_randn(xR, N, 0.0, 1.0);
	dspl_randn(xI, N, 0.0, 1.0);


	dspl_pwelch(xR, xI, N, DSPL_WIN_HAMMING | DSPL_WIN_PERIODIC, 0, 
						NPSD, NPSD/2, pdspl, FS, psd, frq);
						
						
	dspl_writebin(xR,  xI, N, "dat/dspl_pwelch/pwelch_in_even.bin");
	dspl_writebin(frq, psd, NPSD, "dat/dspl_pwelch/pwelch_out_even.bin");
	
	
	dspl_pwelch(xR, xI, N-1, DSPL_WIN_BLACKMAN | DSPL_WIN_PERIODIC, 0, 
						NPSD, NPSD/2, pdspl, FS, psd, frq);
						
						
	dspl_writebin(xR,  xI, N-1, "dat/dspl_pwelch/pwelch_in_odd.bin");
	dspl_writebin(frq, psd, NPSD, "dat/dspl_pwelch/pwelch_out_odd.bin");
	
	
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
