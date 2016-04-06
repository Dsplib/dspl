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
#include "dspl.h"


#define DSPL_ELLIP_ITER	24


DSPL_API int dspl_ellipk(double *pk, int k, double *pK)
{
	
    int n, m;
    double ktmp;
   

    if(!pk || !pK)
        return DSPL_ERROR_PTR;
    if(k < 1)
        return DSPL_ERROR_SIZE;

	for(m = 0; m < k; m++)
	{
		ktmp = pk[m];
		if(ktmp >= 1.0 || ktmp<0.0)
			return DSPL_ERROR_ELLIP_K;
		pK[m] = M_PI_2;
		for(n = 1; n < DSPL_ELLIP_ITER; n++)
		{
			ktmp = ktmp / (1.0 + sqrt(1.0 - ktmp*ktmp));
			ktmp *= ktmp;
			pK[m] *= 1.0+ktmp;
		}
	}
	
    
    return DSPL_OK;
}