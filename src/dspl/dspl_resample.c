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

#define DSPL_RESAMPLE_LAGRANGE_COEFF	0.16666666666666666666666666666667


DSPL_API int dspl_resample_lagrange(double *s, int n, int p, int q, double frd, double **y, int *ny)
{
	double a[4];
	double t, x, dt;
	int ind, k, res;
	double g[4];
	double *z;
	
	if(!s || !y)
	{
		res = DSPL_ERROR_PTR;
		goto  exit_label;
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto  exit_label;
	}
	if(p <= 0 || q <= 0)
	{
		res = DSPL_ERROR_RESAMPLE_RATIO;
		goto  exit_label;
	}
	if(frd <= -1.0 || frd >= 1.0)
	{
		res = DSPL_ERROR_RESAMPLE_FRAC_DELAY;
		goto  exit_label;		
	}
	dt = (double)q/(double)p;
	
	if((*ny) != (int)((double)(n-1)/dt)+1)
	{
		
		*ny = (int)((double)(n-1)/dt)+1;
		(*y) = (double*)realloc((*y), (*ny)*sizeof(double));
	}
				
	t = -frd;
	k = 0;
	while(k < (*ny))
	{
		ind = floor(t)+1;
		x = t - (double)ind;
		ind-=2;
		if(ind < 0)
		{
			memset(g, 0, 4*sizeof(double));
			if(ind > (-3))
				memcpy(g-ind, s, (4+ind)*sizeof(double));
			z = g;
		}
		else
		{
			if(ind < n-3)
				z = s+ind;
			else
			{
				memset(g, 0, 4*sizeof(double));
				if((n-ind)>0)
					memcpy(g, s+ind, (n-ind)*sizeof(double));
				z = g;
			}		
		}
		a[0] = z[2];
		a[3] = DSPL_RESAMPLE_LAGRANGE_COEFF*(z[3] -z[0]) + 0.5*(z[1] - z[2]);
		a[1] = 0.5*(z[3] - z[1])-a[3];
		a[2] = z[3] - z[2] -a[3]-a[1];
		
		
		
		
		
		res = dspl_polyval(a, 3, &x, 1, (*y)+k);
		
		if(res != DSPL_OK)
			goto exit_label;
		t+=dt;
		k++;		
	}
	
exit_label:
	dspl_print_err(res, "dspl_resample_lagrange");
    return res;
}