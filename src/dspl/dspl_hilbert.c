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



/* hilbert transform*/
DSPL_API int dspl_hilbert(double* x, int n, void* pdspl, double* y)
{
	int k, res;
	double *in, *out;
	double ninv;
	
	fft_t *pfft = ((dspl_t*)pdspl)->pfft;
	
	if(!x|| !y || !pdspl)
		return DSPL_ERROR_PTR;	
	if(n<1)
		return DSPL_ERROR_SIZE;
	
	
	res = dspl_fft_create(n, pfft);
	if(res!=DSPL_OK)
		return res;
	
	
	in = (double*)(pfft->in);

	for(k = 0; k < n; k++)
	{
		in[2*k]   = x[k];
		in[2*k+1] = 0.0;
	}

    fftw_execute(pfft->plan);
	out = (double*)pfft->out;
	
	res = n%2;
	memset(in, 0, n*2*sizeof(double));
	
	for(k = 0; k<(n+res)/2; k++)
	{
		in[2*k]   =  out[2*k];
		in[2*k+1] = -out[2*k+1];
	}
	
	fftw_execute(pfft->plan);
	out = (double*)pfft->out;
	
	ninv = 2.0 / (double) n;
	
	for(k = 0; k < n; k++)
		y[k] = -ninv * out[2*k+1];
	
	return DSPL_OK;
}

