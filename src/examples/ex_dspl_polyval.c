/*
*   dspl_fft function example.  
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


int main()
{
	double aR[4] = {1.0, 2.0, -1.0, 0.5};
	double aI[4] = {-1.0, 1.0, -2.0, -2.0};
	double xR = 4.0;
	double xI = -3.0;
	double yR;
	double yI;
	
	int res;
	
	HINSTANCE hDSPL;

	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	dspl_print_msg("Real polynom calculation", 1, 64);
	res = dspl_polyval(aR, 3, &xR, 1, &yR);
	if(res == DSPL_OK)
		printf("P(x) = %.4f\n", yR);
	else
		dspl_print_err(res, 1);
	
	
	dspl_print_msg("Complex polynom calculation", 1, 64);
	res = dspl_polyval_cmplx(aR,aI, 3, &xR,&xI, 1, &yR, &yI);
	if(res == DSPL_OK)
		printf("P(x) = %.4f%+.4fi\n", yR, yI);
	else
		dspl_print_err(res, 1);
	
	FreeLibrary(hDSPL);
	
	return 0;
}
