#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define P 	1
#define Q	1
#define N	8 
#define X0	0.25


int main()
{

	HINSTANCE hDSPL;		/* dspl handle 						*/
	
	double s[N] = {1.0, 1.0, 1.5, -0.5, -1.0, -1.5, -1.5, 1.0};
	double *y = NULL;	
	int ny;
		
    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	/* Allocation memory and fill vectors */
	dspl_resample_lagrange(s, N, P, Q, 0.25, &y, &ny);
			
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	return 0;
}
