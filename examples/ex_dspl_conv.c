#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


int main()
{
	double aR[2] = {1.0,  2.0};
	double bR[3] = {-1.0, 1.0, -2.0};
	double cR[4];
	int k;
	int res;

	HINSTANCE hInstDLL;

	hInstDLL = dspl_load();



	dspl_get_version(1);


	dspl_print_msg("Linear convolution", 1, 64);

	/* DFT calculation */
	res = dspl_conv(aR, 2, bR, 3, cR);

	dspl_print_err(res, 1);

 
	for(k = 0; k < 4; k++)
		printf("c[%d] = %.4f\n",k,cR[k]);

	FreeLibrary(hInstDLL);
	
    
	return 0;
}