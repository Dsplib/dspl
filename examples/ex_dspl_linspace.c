#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define N 5

int main()
{

	HINSTANCE hDSPL;
	double x[N];
	int k;
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	/* Periodic linspace example */
	printf("\nLinspace periodic filling\n");
	dspl_linspace(0.0, 5.0, N, DSPL_PERIODIC, x);
	for(k = 0; k < N; k++)
		printf("%10.3f", x[k]);
		
	
	/* Symmteric linspace example */
	printf("\n\nLinspace symmetric filling\n");
	dspl_linspace(0.0, 5.0, N, DSPL_SYMMETRIC, x);
	for(k = 0; k < N; k++)
		printf("%10.3f", x[k]);
	
	
	/* Periodic logspace example */
	printf("\n\nLogspace periodic filling\n");
	dspl_logspace(-2.0, 3.0, N, DSPL_PERIODIC, x);
	for(k = 0; k < N; k++)
		printf("%10.3f", x[k]);
		
	
	/* Symmteric logspace example */
	printf("\n\nLogspace symmetric filling\n");
	dspl_logspace(-2.0, 3.0, N, DSPL_SYMMETRIC, x);
	for(k = 0; k < N; k++)
		printf("%10.3f", x[k]);
	
	

	FreeLibrary(hDSPL);
	
	return 0;
}
