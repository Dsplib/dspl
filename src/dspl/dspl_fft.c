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
#include "fftw3.h"
#include "dspl.h"
#include "dspl_main.h"



/* inverse FFT */
DSPL_API int dspl_ifft(double* xR, double* xI, int n, void* pdspl, double* yR, double* yI)
{
	int k, res;
	double *t;
	double ninv;
	
	fft_t *pfft = ((dspl_t*)pdspl)->pfft;
	
	if(!xR || !xI || !yR || !pdspl)
		return DSPL_ERROR_PTR;	
	if(n<1)
		return DSPL_ERROR_SIZE;
	
	
	res = dspl_fft_create(n, pfft, NULL);
	if(res!=DSPL_OK)
		return res;
	
	
	t = (double*)(pfft->in);

	for(k = 0; k < n; k++)
	{
		t[2*k]   = xR[k];
		t[2*k+1] = -xI[k];
	}

	
    fftw_execute(pfft->plan); /* repeat as needed */
  
	t = (double*)pfft->out;
	ninv = 1.0 / (double) n;
	if(yI)
	{	
		for(k = 0; k < n; k++)
		{
			yR[k] =  ninv * t[2*k];
			yI[k] = -ninv * t[2*k+1];
		}
	}
	else
		for(k = 0; k < n; k++)
			yR[k] = ninv * t[2*k];

	
	return DSPL_OK;
}


/*
 Fast Fourier Transform.
*/
DSPL_API int dspl_fft(double* xR, double* xI, int n, void* pdspl, double* yR, double* yI)
{
	int k, res;
	double *t;
	
	fft_t *pfft = ((dspl_t*)pdspl)->pfft;
	
	if(!xR || !yR || !yI || !pdspl)
		return DSPL_ERROR_PTR;	
	if(n<1)
		return DSPL_ERROR_SIZE;
	
	
	res = dspl_fft_create(n, pfft, NULL);
	if(res!=DSPL_OK)
		return res;
	
	
	t = (double*)(pfft->in);
	if(xI)
	{	
		for(k = 0; k < n; k++)
		{
			t[2*k] = xR[k];
			t[2*k+1] = xI[k];
		}
	}
	else
	{
		for(k = 0; k < n; k++)
		{
			t[2*k] = xR[k];
			t[2*k+1] = 0.0;
		}
	}
	
    fftw_execute(pfft->plan); /* repeat as needed */
  
	t = (double*)pfft->out;
	for(k = 0; k < n; k++)
	{
		yR[k] = t[2*k];
		yI[k] = t[2*k+1];
	}
	
	return DSPL_OK;
}








int dspl_fft_create(int n, fft_t *pfft, int *p2)
{
	if(!pfft)
		return DSPL_ERROR_PTR;
	if(n == pfft->n)
		return DSPL_OK;
	
	dspl_fft_free(pfft);
	pfft->in  = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    pfft->out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
	pfft->plan = fftw_plan_dft_1d(n, pfft->in, pfft->out, FFTW_FORWARD, FFTW_ESTIMATE);
	return DSPL_OK;
}




void dspl_fft_free(fft_t *pfft)
{
	fftw_destroy_plan(pfft->plan);
    fftw_free(pfft->in); 
	fftw_free(pfft->out);
	pfft->n = 0;
}



/* retrun power of 2 of FFT size. 
 Return zero if n is not power of 2 */
int dspl_fft_p2(int n)
{
	int n2;
	int p2;
	p2 = 0;;
	n2 = n;
	while(n2-1)
	{
		p2++;
		n2>>=1;
	}
	if(1<<p2 != n)
		return 0;
	return p2;	
}



DSPL_API int dspl_fft_shift(double* xR, double* xI, int n, double* yR, double* yI)
{
	int n2, r;
	int k;
	double tmp;
	double *buf;
	
	if(!xR || !yR || (!xI && yI) || (!yI && xI))
		return DSPL_ERROR_PTR;
	if(n<1)
		return DSPL_ERROR_SIZE;
	r = n%2;
	if(!r)
	{
		n2 = n>>1;
		if(xI)
		{
			for(k = 0; k < n2; k++)
			{
				tmp = xR[k];
				yR[k] = xR[k+n2];
				yR[k+n2] = tmp;
				
				tmp = xI[k];
				yI[k] = xI[k+n2];
				yI[k+n2] = tmp;
				
			}
		}
		else
		{
			for(k = 0; k < n2; k++)
			{
				tmp = xR[k];
				yR[k] = xR[k+n2];
				yR[k+n2] = tmp;
			}
			
		}
	}
	else
	{
		n2 = (n-1) >> 1;
		buf = (double*) malloc(n2*sizeof(double));
		memcpy(buf, xR, n2*sizeof(double));
		memcpy(yR, xR+n2, (n2+1)*sizeof(double));
		memcpy(yR+n2+1, buf, n2*sizeof(double));
		
		if(xI)
		{
			memcpy(buf, xI, n2*sizeof(double));
			memcpy(yI, xI+n2, (n2+1)*sizeof(double));
			memcpy(yI+n2+1, buf, n2*sizeof(double));			
		}
		free(buf);
	}
			
	return DSPL_OK;
}