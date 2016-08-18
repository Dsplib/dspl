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
#include <string.h>
#include <math.h>
#include "dspl.h"


/* freqz function */

DSPL_API int dspl_freqz(double* b, double* a, int ord, 
						double* w, int n, 
						double *hR, double* hI)
{

	double jwR;
	double jwI;
	double tmp;
	double dR;
	double dI;
	double mag;
	int k;
	int res;

	if(!b || !w || !hR || !hI)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(ord<0)
	{
		res = DSPL_ERROR_FILTER_ORD;
		goto exit_label;	
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;	
	}


	for(k = 0; k < n; k++)
	{
		jwR =  cos(w[k]);
		jwI = -sin(w[k]);
		res = dspl_polyval_cmplx(b, NULL, ord, &jwR, &jwI, 1, hR+k, hI+k);	
		if(res != DSPL_OK)
			goto exit_label;
		if(a)
		{	
			res = dspl_polyval_cmplx(a, NULL, ord, &jwR, &jwI, 1, &dR, &dI);
			if(res != DSPL_OK)
				goto exit_label;
			mag = 1.0 / (dR * dR + dI * dI);
			tmp = (hR[k] * dR + hI[k] * dI) * mag;			
			hI[k] = (hI[k] * dR - hR[k] * dI) * mag;
			hR[k] = tmp;
		}
	}

	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_freqz");
	return res;
}  






DSPL_API int dspl_freqz_resp(double* b, double* a, int ord, 
							 double* w, int n, 
							 double *h, double* phi, double* gd)
{

	double *hR = NULL;
	double *hI = NULL;
	double *dw = NULL;
    double *phi1 = NULL;
    double *phi0 = NULL;

	int k;
	int res;

	if(!b || !w)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;
	}
	if(ord<0)
	{
		res = DSPL_ERROR_FILTER_ORD;
		goto exit_label;
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;
	}

	hR = (double*) malloc(n * sizeof(double));
	hI = (double*) malloc(n * sizeof(double));

	res = dspl_freqz(b, a, ord, w, n, hR, hI);
	if(res != DSPL_OK)
		goto exit_label;

	if(h)
	{
		for(k = 0; k < n; k++)
			h[k] = 10.0 * log10(hR[k]*hR[k] + hI[k]*hI[k]);
	}


	if(phi)
	{
		phi0 = phi;
		for(k = 0; k < n; k++)
			phi0[k] = atan2(hI[k], hR[k]);
		res = dspl_unwrap(phi0,  n, M_2PI, 0.7); 
		if(res!=DSPL_OK)
			goto  exit_label;
	}

	if(gd)
	{
		if(!phi0)
		{
			phi0 = (double*)malloc(n*sizeof(double));            
			for(k = 0; k < n; k++)
				phi0[k] = atan2(hI[k], hR[k]);
			res = dspl_unwrap(phi0,  n, M_2PI, 0.7); 
			if(res!=DSPL_OK)
				goto  exit_label;
		}

		dw = (double*)malloc(n*sizeof(double));
		phi1 = (double*)malloc(n*sizeof(double));

		dw[0] = w[0] + 0.01*(w[1] - w[0]);
		for(k = 1; k < n; k++)
			dw[k] = w[k] + 0.01*(w[k] - w[k-1]);
                       
        res = dspl_freqz(b, a, ord, dw, n, hR, hI);
		if(res != DSPL_OK)
			goto exit_label;
		for(k = 0; k < n; k++)
			phi1[k] = atan2(hI[k], hR[k]);
		res = dspl_unwrap(phi1,  n, M_2PI, 0.7); 
		if(res!=DSPL_OK)
			goto  exit_label;
		
		for(k = 0; k < n; k++)
			gd[k] = (phi0[k] - phi1[k])/(dw[k] - w[k]);			

	}   
	
    res = DSPL_OK;
exit_label:
	dspl_print_err(res, "dspl_freqz_resp");
	if(hR)
		free(hR);
	if(hI)
		free(hI);
	if(dw)
		free(dw);
	if(phi0!=phi)
		free(phi0);
	if(phi1)
		free(phi1);

	return res;
}  
