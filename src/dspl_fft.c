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



void 	dspl_fft_krn (fft_t* pfft, int n, int p2);
int  	dspl_fft_p2 (int n);
void  	dspl_fft_reorder (fft_t* pfft, int n);


/* inverse FFT */
DSPL_API int dspl_ifft(double* xR, double* xI, int n, fft_t* pfft, 
											double* yR, double* yI)
{
	int p2;
	int k;
	double invn;
	size_t bufSize;
	if(!xR || !yR)
		return DSPL_ERROR_PTR;
	p2 = dspl_fft_p2(n);
	if(!p2)
		return DSPL_ERROR_FFT_SIZE;
	bufSize = n * sizeof(double);
	memcpy(pfft->t0R, xR, bufSize);
	if(xI)
		for (k = 0; k<n; k++)
			pfft->t0I[k] = -xI[k];
	else		
        memset(pfft->t0I, 0, bufSize);
	dspl_fft_reorder(pfft, n);
	dspl_fft_krn(pfft, n, p2);
	invn = 1.0 / (double) n;
	if(yI)
		for (k = 0; k<n; k++)
		{
			yR[k]=  invn * pfft->t0R[k];
			yI[k]= -invn * pfft->t0I[k];	
		}	
	else
		for (k = 0; k<n; k++)
			yR[k]=  invn * pfft->t0R[k];
	 
	return DSPL_OK;
}


/*
 Fast Fourier Transform.
*/
DSPL_API int dspl_fft(double* xR, double* xI, int n, fft_t* pfft, 
											double* yR, double* yI)
{
	int p2;
	size_t bufSize;
	if(!xR || !yR || !yI)
		return DSPL_ERROR_PTR;
	p2 = dspl_fft_p2(n);
	if(!p2)
		return DSPL_ERROR_FFT_SIZE;
	bufSize = n * sizeof(double);
	memcpy(pfft->t0R, xR, bufSize);
	if(xI)
		memcpy(pfft->t0I, xI, bufSize);
	else		
        memset(pfft->t0I, 0, bufSize);
	dspl_fft_reorder(pfft, n);
	dspl_fft_krn(pfft, n, p2);
	memcpy(yR, pfft->t0R, bufSize);
	memcpy(yI, pfft->t0I, bufSize);
	return DSPL_OK;
}








/*
* Fast Fourier Transform object create.
*/  
DSPL_API int dspl_fft_create(fft_t *pfft, int n)
{
	long double phi;
	long double dphi;
	int k;
	int n2;
	int ind; 
	size_t bufSize;
	if(pfft->n >= n)
		return DSPL_OK;
	if(!dspl_fft_p2(n))
		return DSPL_ERROR_FFT_SIZE;
	
	dphi = M_PI;
	bufSize = (size_t)(n*sizeof(double));
	pfft->wR = (double*)realloc( pfft->wR, bufSize);
	pfft->wI = (double*)realloc( pfft->wI, bufSize);
	pfft->t0R = (double*)realloc(pfft->t0R, bufSize);
	pfft->t0I = (double*)realloc(pfft->t0I, bufSize);
	pfft->t1R = (double*)realloc(pfft->t1R, bufSize);
	pfft->t1I = (double*)realloc(pfft->t1I, bufSize);
	
	pfft->n = n;
	n2 = 1;
	ind = 0;
	while(n2<n)
	{
		phi = 0;
		for(k = 0; k<n2; k++)
		{
			pfft->wR[ind+k] = (double)cos(phi);
			pfft->wI[ind+k] = (double)sin(phi);
			phi -= dphi;
		}
		ind+=n2;
		n2<<=1;
		dphi*=0.5;		
	}
	return DSPL_OK;
}




/*
	Clear Fast Fourier Transform object.
	This function clears memory for fft_t object
	------------------------------------------------------------------------------------------
	Parameters:                                                        
		[in, out]	fft_t* 	pfft	-	FFT object pointer. 
							Memory for twiddle factor will be free.
			
	Example: ex_dspl_fft.c
	
	Author:
	Sergey Bakhurin.                                                         www.dsplib.org    
	
*/  

DSPL_API void dspl_fft_free(fft_t *pfft)
{
	if(pfft->wR)
		free(pfft->wR);
	if(pfft->wI)
		free(pfft->wI);
	if(pfft->t0R)
		free(pfft->t0R);
	if(pfft->t0I)
		free(pfft->t0I);
	if(pfft->t1R)
		free(pfft->t1R);
	if(pfft->t1I)
		free(pfft->t1I);
}





/* fft kernel */
void dspl_fft_krn(fft_t *pfft, int n, int p2)
{
	int k,p,q,q2,wi,ind0,i,ind0i, ind1, ind1i, iwi;
	double *ptr = NULL;
	double *ptr0R = NULL, *ptr0I = NULL; 
	double *ptr1R = NULL, *ptr1I = NULL;
	double zR, zI;
	
	p = n>>1;
	q = 1;
	q2 = 2;
	wi = 0;
	if(p2%2)
	{
		ptr0R = pfft->t1R;
		ptr1R = pfft->t0R;
		ptr0I = pfft->t1I;
		ptr1I = pfft->t0I;
	}
	else
	{
		ptr0R = pfft->t0R;
		ptr1R = pfft->t1R;
		ptr0I = pfft->t0I;
		ptr1I = pfft->t1I;
	}
	while(p)
	{
		ind0 = 0;
		for(k = 0; k<p; k++)
		{
			ind1 = ind0+q;
			for(i = 0; i<q; i++)
			{
				ind1i = ind1+i;
				iwi = wi+i;
				zR = ptr0R[ind1i] * pfft->wR[iwi] - ptr0I[ind1i] * pfft->wI[iwi];
				zI = ptr0R[ind1i] * pfft->wI[iwi] + ptr0I[ind1i] * pfft->wR[iwi];
				ind0i = ind0+i;
				ptr1R[ind0i] = ptr0R[ind0i] + zR;
				ptr1I[ind0i] = ptr0I[ind0i] + zI;
				ptr1R[ind1i] = ptr0R[ind0i] - zR;
				ptr1I[ind1i] = ptr0I[ind0i] - zI;
			}
			ind0+=q2;
		}
		p>>=1;
		wi+=q;
		q<<=1;
		q2 = q<<1;
		ptr = ptr0R;
		ptr0R = ptr1R;
		ptr1R = ptr;
		ptr = ptr0I;
		ptr0I = ptr1I;
		ptr1I = ptr;
	}
	
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




/* Bit inverse reordering for decimation in time */
void dspl_fft_reorder(fft_t* pfft, int n)
{
	int i;
	int i2;
	int n2;
	int n2jn22;
	int n22;
	int p;
	int j;
	int jn22;
	int jn221;
	double *ptr;
	
	n2 = n >> 1;
	p = 1;
	while(n2)
	{
		n22 = n2<<1;
		jn22 = 0;
		for(j = 0; j < p; j++)
		{
			n2jn22 = n2 + jn22;
			jn221 = jn22 + 1;
			for(i = 0; i < n2; i++)
			{
				i2 = i<<1;
				pfft->t1R[i + jn22]   = pfft->t0R[i2 + jn22];
				pfft->t1I[i + jn22]   = pfft->t0I[i2 + jn22];
				pfft->t1R[i + n2jn22] = pfft->t0R[i2 + jn221];
				pfft->t1I[i + n2jn22] = pfft->t0I[i2 + jn221];
			}
			jn22+=n22;
		}
		n2 >>= 1;
		p  <<= 1;
		ptr = pfft->t0R;
		pfft->t0R = pfft->t1R;
		pfft->t1R = ptr;
		ptr = pfft->t0I;
		pfft->t0I = pfft->t1I;
		pfft->t1I = ptr;
	}
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