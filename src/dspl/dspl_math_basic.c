/*
* Copyright (c) 2015, 2016 Sergey Bakhurin
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
#include <math.h>
#include <string.h>  
#include "dspl.h"


DSPL_API int dspl_cos_cmplx(double *xR, double *xI, int n, double *yR, double *yI)
{
	double t, wn, wp;
	int k;
	
	if(!xR || !yR || (xI && !yI))
		return DSPL_ERROR_PTR;
	if(n<1)
		return DSPL_ERROR_SIZE;
		
	if(!xI)
	{
		for(k = 0; k < n; k++)
			yR[k] = cos(xR[k]);
		if(yI)
			memset(yI, 0, n*sizeof(double));
		return DSPL_OK;
		
	}
	for(k =0; k < n; k++)
	{
		wn = exp(-xI[k]);
		wp = exp( xI[k]);
		
		t     = 0.5*cos(xR[k])*(wn+wp);
		yI[k] = 0.5*sin(xR[k])*(wn-wp);
		yR[k] = t;
	}
	return DSPL_OK;
	
}


DSPL_API int dspl_sin_cmplx(double *xR, double *xI, int n, double *yR, double *yI)
{
	double t, wn, wp;
	int k;
	
	if(!xR || !yR || (xI && !yI))
		return DSPL_ERROR_PTR;
	if(n<1)
		return DSPL_ERROR_SIZE;
		
	if(!xI)
	{
		for(k = 0; k < n; k++)
			yR[k] = sin(xR[k]);
		if(yI)
			memset(yI, 0, n*sizeof(double));
		return DSPL_OK;
		
	}
	
	for(k =0; k < n; k++)
	{
		wn = exp(-xI[k]);
		wp = exp( xI[k]);
	
		t     =  0.5*sin(xR[k])*(wn+wp);
		yI[k] = -0.5*cos(xR[k])*(wn-wp);
		yR[k] = t;
	}
	
	return DSPL_OK;
	
}