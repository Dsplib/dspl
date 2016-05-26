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


DSPL_API int dspl_resample_lagrange(double *s, int n, int p, int q, double frd, double *z, int nz)
{
	double a[4];
	double t, x, dt;
	int ind, k;
	double g[4];
	double *y;
	
	if(!s || !z)
		return DSPL_ERROR_PTR;
	if(n<1)
		return DSPL_ERROR_SIZE;
	if(p <= 0 || q <= 0)
		return DSPL_ERROR_RESAMPLE_RATIO;
	if(frd <= -1.0 || frd >= 1.0)
		return DSPL_ERROR_RESAMPLE_FRAC_DELAY;	
	
	dt = (double)q/(double)p;
	
	if(nz < (int)((double)n*dt))
		return DSPL_ERROR_RESAMPLE_SIZE;	
	
	t = frd;
	k = 0;
	while(t < (double)n)
	{
		ind = floor(t);
		x = t - (double)ind;
		if(ind == 0)
		{
			memset(g, 0, 4*sizeof(double));
			memcpy(g+1, s, 3*sizeof(double));
			y = g;
		}
		else
		{
			if(ind > n-2)
			{
				memset(g, 0, 4*sizeof(double));
				memcpy(g, s+ind-1, (n-ind)*sizeof(double));
				y = g;
			}
			else
				y = s+ind-1;			
		}
		a[0] = y[1];
		a[3] = DSPL_RESAMPLE_LAGRANGE_COEFF*(y[3] - y[0]) + 0.5*(y[1] - y[2]);
		a[1] = 0.5*(y[2] - y[0])-a[3];
		a[2] = y[2] - y[1] -a[3]-a[1];
		
		dspl_polyval(a, 3, &x, 1, z+k);
		t+=dt;
		k++;		
	}
	
    return DSPL_OK;
}