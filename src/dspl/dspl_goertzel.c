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





DSPL_API int dspl_goertzel(double *xR, double *xI, int n, int *ind, int k, double *yR, double *yI)
{
	
    int m, p;
    double wR, wI;
    double alpha;
    double vR[3];
	double vI[3];

    if(!xR || !yR ||!yI || !ind)
        return DSPL_ERROR_PTR;
    if(n < 1 || k < 1)
        return DSPL_ERROR_SIZE;

	for(p = 0; p < k; p++)
	{
		wR = cos(M_2PI * (double)ind[p] / (double)n);
		wI = sin(M_2PI * (double)ind[p] / (double)n);
		
		alpha = 2.0 * wR;
		vR[0] = vR[1] = vR[2] = 0.0;
		vI[0] = vI[1] = vI[2] = 0.0;
		if(xI)
		{
			for(m = 0; m < n; m++)
			{
				vR[2] = vR[1];
				vR[1] = vR[0];
				vR[0] = xR[m]+alpha*vR[1] - vR[2];
				
				vI[2] = vI[1];
				vI[1] = vI[0];
				vI[0] = xI[m]+alpha*vI[1] - vI[2];
			}
		}
		else
		{
			for(m = 0; m < n; m++)
			{
				vR[2] = vR[1];
				vR[1] = vR[0];
				vR[0] = xR[m]+alpha*vR[1] - vR[2];
			}
		}
		yR[p] = wR * vR[0] - wI * vI[0] - vR[1];
		yI[p] = wR * vI[0] + wI * vR[0] - vI[1];
	}
	
    
    return DSPL_OK;
}