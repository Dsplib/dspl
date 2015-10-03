/*
* Copyright 2015 Sergey Bakhurin
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dspl.h"



void dspl_fft_krn (fft_t *fft; int n; int p2);
int  dspl_fft_p2 (int n);
int  dspl_fft_reordering (fft_t* fft, int n);



DSPL_API int dspl_fft(double* xR, double* xI, int n, fft_t *pfft, 
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





DSPL_API int dspl_fft_create(fft_t *fft, int n)
{
	double phi;
	double dphi;
	int k;
	int n2;
	int ind; 
	size_t bufSize;
	if(fft->n >= n)
		return DSPL_OK;
	if(!dspl_fft_p2(n))
		return DSPL_ERROR_FFT_SIZE;
	
	dphi = M_PI;
	bufSize = (size_t)(n*sizeof(double)));
	fft->wR = (double*)realloc(fft->wR, bufSize);
	fft->wI = (double*)realloc(fft->wI, bufSize);
	fft->t0R = (double*)realloc(fft->t0R, bufSize);
	fft->t0I = (double*)realloc(fft->t0I, bufSize);
	fft->t1R = (double*)realloc(fft->t1R, bufSize);
	fft->t1I = (double*)realloc(fft->t1I, bufSize);
	
	fft->n = n;
	n2 = 1;
	ind = 0;
	while(n2<n)
	{
		phi = 0;
		for(k = 0; k<n2; k++)
		{
			fft->wR[ind+k] = cos(phi);
			fft->wI[ind+k] = sin(phi);
			phi -= dphi;
		}
		ind+=n2;
		n2<<=1;
		dphi*=0.5;		
	}
	return DSPL_OK;
}





void dspl_fft_krn(fft_t *fft; int n; int p2)
{
	int k,p,q,q2,wi,ind0,i,ind0i, ind1i, iwi;
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
		ptr0R = fft->t1R;
		ptr1R = fft->t0R;
		ptr0I = fft->t1I;
		ptr1I = fft->t0I;
	}
	else
	{
		ptr0R = fft->t0R;
		ptr1R = fft->t1R;
		ptr0I = fft->t0I;
		ptr1I = fft->t1I;
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
				zR = ptr0R[ind1i] * fft->wR[iwi] - ptr0I[ind1i] * fft->wI[iwi];
				zI = ptr0R[ind1i] * fft->wI[iwi] - ptr0I[ind1i] * fft->wR[iwi];
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
		prt1R = ptr;
		ptr = ptr0I;
		ptr0I = ptr1I;
		prt1I = ptr;
	}
	
}





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





int dspl_fft_reordering(fft_t* fft, int n)
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
				fft->t1R[i + jn22]   = fft->t0R[i2 + jn22];
				fft->t1I[i + jn22]   = fft->t0I[i2 + jn22];
				fft->t1R[i + n2jn22] = fft->t0R[i2 + jn221];
				fft->t1I[i + n2jn22] = fft->t0I[i2 + jn221]
			}
			jn22+=n22;
		}
		n2 >>= 1;
		p  <<= 1;
		ptr = fft->t0R;
		fft->t0R = fft->t1R;
		fft->t1R = ptr;
		ptr = fft->t0I;
		fft->t0I = fft->t1I;
		fft->t1I = ptr;
	}
}



