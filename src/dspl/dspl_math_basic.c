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

/*
DSPL_API int dspl_acos_cmplx(double *xR, double *xI, int n, double *yR, double *yI)
{
	

}
*/

DSPL_API int dspl_asin_cmplx(double *xR, double *xI, int n, double *yR, double *yI)
{

	double wR, wI;
	int k, res;


	if(!xR || !yR ||  !yI)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;	
	}

	for(k =0; k < n; k++)
	{
		wR = xI ? 1.0 - xR[k]*xR[k] + xI[k]*xI[k] : 1.0 - xR[k]*xR[k];
		wI = xI ? 2.0 * xR[k] * xI[k] : 0.0;

		res = dspl_sqrt_cmplx(&wR, &wI, 1, &wR, &wI);
		if(res != DSPL_OK)
			goto exit_label;

		wI = wI + xR[k];
		wR = xI ? wR - xI[k] : wR;

		res = dspl_log_cmplx(&wR, &wI, 1, &wR, yR+k);
        if(res != DSPL_OK)
			goto exit_label;
		yI[k] = -wR;

	}

	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_cos_cmplx");
	return res;
	


}







DSPL_API int dspl_cos_cmplx(double *xR, double *xI, int n, double *yR, double *yI)
{
	double t, wn, wp;
	int k;
	int res;
	
	if(!xR || !yR || (xI && !yI))
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;	
	}
		
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
	
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_cos_cmplx");
	return res;
	
}



DSPL_API int dspl_log_cmplx(double *xR, double *xI, int n, double *yR, double *yI)
{
	double tI, tR;
	int k;
	int res;
	
	if(!xR || !yR || !yI)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;	
	}
	for(k = 0; k < n; k++)
	{
		tI = xI ? xI[k] : 0.0;
		tR = xR[k];
		yR[k] = 0.5 * log(tR * tR + tI * tI);
		yI[k] = atan2(tI, tR);		
	}
	
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_log_cmplx");
	return res;
	
}



DSPL_API int dspl_sin_cmplx(double *xR, double *xI, int n, double *yR, double *yI)
{
	double t, wn, wp;
	int k;
	int res;
	
	if(!xR || !yR || (xI && !yI))
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;	
	}
		
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
	
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_sin_cmplx");
	return res;
	
}







DSPL_API int dspl_sqrt_cmplx(double *xR, double *xI, int n, double * yR, double * yI)
{
	double t, tI, tR, a;
	int k;
	int res;
	
	if(!xR || !yR || !yI)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}

	if(n < 1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;	
	}
	
	
	for(k = 0; k < n; k++)
	{
		tI = xI ? xI[k] : 0.0;
		tR = xR[k];
		a = xI ? sqrt(tR*tR + tI*tI) : fabs(tR);
		yR[k] = sqrt(0.5 * (a+tR));
		t = sqrt(0.5*(a-tR));
		yI[k] = (tI > 0) ? t : -t;
		
	}
	
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_sqrt_cmplx");
	return res;
	
	
}










