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



/* Doxygen RU, EN*/
DSPL_API int dspl_dft(double *xR, double *xI, int n, double *yR, double *yI)
{
    int k;
    int m;
    double eR, eI;
    double divn;
    double dphi;
    double phi; 
	int res;

    if(!xR || !yR ||!yI)
	{
        res = DSPL_ERROR_PTR;
		goto exit_label;
	}
    if(n<1)
	{
        res = DSPL_ERROR_SIZE;
		goto exit_label;
	}

    divn = 1.0 / (double)n;
    if(xI)
    {
        for(k = 0; k < n; k++)
        {
            yR[k] = yI[k] = 0.0;
            dphi = -2.0 * M_PI * divn * (double)k;
            for(m = 0; m < n; m++)
            {
            	phi  = dphi*(double)m;
				eR = cos(phi);
				eI = sin(phi);
                yR[k] += xR[m] * eR - xI[m] * eI;
                yI[k] += xR[m] * eI + xI[m] * eR;
            }    
        }
    }
    else
    {
        for(k = 0; k < n; k++)
        {
            yR[k] = yI[k] = 0.0;
            dphi = -2.0 * M_PI * divn * (double)k;
            for(m = 0; m < n; m++)
            {
            	phi  = dphi*(double)m;
				eR = cos(phi);
				eI = sin(phi);
                yR[k] += xR[m] * eR;
                yI[k] += xR[m] * eI;
            }    
        }
    }
	
	res = DSPL_OK;
exit_label:
	dspl_print_err(res, "dspl_dft");
	return res;	
}