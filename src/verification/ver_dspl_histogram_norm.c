
#ifdef DOXYGEN_EN

/*!

		
*/

#elseif DOXYGEN_RU

#endif




#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		1000000
#define NHIST	30

int main()
{
	double *y = NULL;
		
	double w[NHIST];
	double x[NHIST];
	
	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	
	y = (double*)malloc(N*sizeof(double));
	
	
	
	/* */
	dspl_rand(y, N);	
	dspl_histogram_norm(y, N, NHIST, x, w);	
	dspl_writebin(y, NULL, N,  "dat/histogram_rand_y.bin");
	dspl_writebin(x, w, NHIST, "dat/histogram_rand_h.bin");
	
	/* gaussian random numbers m = 0, std = 1.0 */
	dspl_randn(y, N, 0.0, 1.0);
	dspl_histogram_norm(y, N, NHIST, x, w);
	dspl_writebin(y, NULL, N,  "dat/histogram_randn_y.bin");
	dspl_writebin(x, w, NHIST, "dat/histogram_randn_h.bin");
	
	
	
	
	free(y);
	
	
	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
