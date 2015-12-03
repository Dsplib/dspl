/*
*Copyright (c) 2015 Sergey Bakhurin
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




DSPL_API int dspl_dft(double *xR, double *xI, int n, double *yR, double *yI)
{
    int k;
    int m;
    double eR, eI;
    double dR, dI;
    double tR, tI;
    double divn;
    double dphi;         

    if(!xR || !yR ||!yI)
        return DSPL_ERROR_PTR;
    if(n<1)
        return DSPL_ERROR_SIZE;

    divn = 1.0 / (double)n;
    if(xI)
    {
        for(k = 0; k < n; k++)
        {
            yR[k] = yI[k] = 0.0;
            eR = 1.0;
            dphi = -2.0 * M_PI * divn * (double)k;
            dR = cos(dphi);
            dI = sin(dphi);
            for(m = 0; m < n; m++)
            {
				
                yR[k] += xR[m] * eR - xI[m] * eI;
                yI[k] += xR[m] * eI + xI[m] * eR;
                tR = eR * dR - eI * dI;
                tI = eR * dI + eI * dR;
                eR = tR;
                eI = tI;
            }    
        }
    }
    else
    {
        for(k = 0; k < n; k++)
        {
            yR[k] = yI[k] = 0.0;
            eR = 1.0;
            dphi = -2.0 * M_PI * divn * (double)k;
            dR = cos(dphi);
            dI = sin(dphi);
            for(m = 0; m < n; m++)
            {
                yR[k] += xR[m] * eR;
                yI[k] += xR[m] * eI;
                tR = eR * dR - eI * dI;
                tI = eR * dI + eI * dR;
                eR = tR;
                eI = tI;
            }    
        }
    }
    return DSPL_OK;
}

/*kuku*/