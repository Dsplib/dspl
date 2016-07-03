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
#include <math.h>
#include <time.h>

#include "dspl.h"


#define DSPL_RAND_MOD_X1  2147483647 
#define DSPL_RAND_MOD_X2  2145483479

DSPL_API int dspl_rand(double* x, int n)
{
 	int k,m;
 	unsigned int x1[4], x2[4], y;

 	if(!x)
 		return DSPL_ERROR_PTR;
 	if(n<1)
 		return DSPL_ERROR_SIZE;

 	x1[1] = rand();
 	x2[1] = rand();
 	x1[2] = rand();
 	x2[2] = rand();
 	x1[3] = rand();
 	x2[3] = rand();
 	for(k = 0; k<n; k++)
 	{
 		x1[0] = (63308 * x1[2] - 183326*x1[3]) % DSPL_RAND_MOD_X1;
 		x2[0] = (86098 * x2[1] - 539608*x2[3]) % DSPL_RAND_MOD_X2;
 		y = (x1[0] - x2[0]) %  DSPL_RAND_MOD_X1;
 		for(m = 3; m > 0; m--)
 		{
 			x1[m] = x1[m-1];
 			x2[m] = x2[m-1];
 		}

 		x[k] = (double)y/DSPL_RAND_MOD_X1;
 	}
 	return DSPL_OK;
}





DSPL_API int dspl_randn(double* x, int n, double mu, double sigma)
{
	int k, m;
	double x1[128], x2[128];
	if(!x)
 		return DSPL_ERROR_PTR;
 	if(n<1)
 		return DSPL_ERROR_SIZE;
	if(sigma < 0.0)
		return DSPL_ERROR_RAND_SIGMA;
	k=0;
	while(k < n)
	{
		dspl_rand(x1, 128);
		dspl_rand(x2, 128);
		m = 0 ;
		while(k<n && m < 128)
		{
			x[k] = sqrt(-2.0*log(x1[m]))*cos(M_2PI*x2[m])*sigma + mu;
			k++;
			m++;
			if(k<n && m < 128)
			{
				x[k] = sqrt(-2.0*log(x1[m]))*sin(M_2PI*x2[m])*sigma + mu;
				k++;
				m++;			
			}			
		}		
	}
	return DSPL_OK;	
}




