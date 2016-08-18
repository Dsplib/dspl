/*
*Copyright (c) 2015, 2016 Sergey Bakhurin
* Digital Signal Processing Library [http://dsplib.org]
*
* This file is part of DSPL.
* 
* DSPL is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dspl.h"




DSPL_API int dspl_polyval(double* a, int ord, double* x, int n, double* y)

{
	int k;
	int m;   
	int res;
	
	if(!a || !x || !y)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(ord<0)
	{
		res = DSPL_ERROR_POLY_ORD;
		goto exit_label;	
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;	
	}
	
	for(k = 0; k < n; k++)
	{
		y[k] = a[ord];
	 	for(m = ord-1; m>-1; m--)
			y[k] = y[k]*x[k] + a[m];			
	}  
	
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_polyval");
	return res;
}







DSPL_API int dspl_polyval_cmplx(	double* aR, double* aI, int ord, 
									double* xR, double* xI, int n,
									double* yR, double* yI)
{
	int k;
	int m;
	double tR;
	double tI;
	double *cI;
	double *zI; 
    int res;
	
	if(!aR || !xR || !yR)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(ord<0)
	{
		res = DSPL_ERROR_POLY_ORD;
		goto exit_label;	
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;	
	}
	if((aI || xI)&& !yI)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}

	if(!aI && !xI && !yI)
	{
		res = dspl_polyval(aR, ord, xR, n, yR);
		goto exit_label;
	}
	cI = aI;
	if(!cI)
	{
		cI = (double*)malloc((ord+1)*sizeof(double));
		memset(cI, 0, (ord+1)*sizeof(double));
	}

	zI = xI;
	if(!zI)
	{
		zI = (double*)malloc(n*sizeof(double));
		memset(zI, 0, n*sizeof(double));
	}

	for(k = 0; k < n; k++)
	{
		yR[k] = aR[ord];
		yI[k] = cI[ord];
	 	for(m = ord-1; m>-1; m--)
		{
			tR = yR[k]*xR[k] - yI[k]*zI[k] + aR[m];
			tI = yR[k]*zI[k] + yI[k]*xR[k] + cI[m];
			yR[k] = tR;
			yI[k] = tI;	 	
		}
	} 

	if(cI!=aI)
		free(cI);

	if(zI!=xI)
		free(zI);

	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_polyval_cmplx");
	return res;

}