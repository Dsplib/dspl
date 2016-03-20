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



DSPL_API int dspl_unwrap(double* phi,  int n, double lev, double mar)
{
	double a[2] = {0.0, 0.0};
	double d;
	double th;
	int k;
	int flag = 1;
	if(!phi)
		return DSPL_ERROR_PTR;
	if(n<1)
		return DSPL_ERROR_SIZE;
	if(lev<=0 || mar <=0)
		return DSPL_ERROR_UNWRAP;
	th = mar*lev;
	while(flag)
	{
		flag = 0;
		a[0] = a[1] = 0.0;
		for(k = 0; k<n-1; k++)
		{
			d = phi[k+1] - phi[k];
			if( d > th)
			{
				a[0] -= lev;
				flag = 1;
			}
			if( d < -th)
			{
				a[0] += lev;	
				flag = 1;				
			}
			phi[k]+=a[1];
			a[1] = a[0];		
		}
		phi[n-1]+=a[1];
	}
	return DSPL_OK;
}



