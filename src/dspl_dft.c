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
#include <math.h>
#include "dspl.h"



/*
* Discrete Fourier Transform.
* This function calculates n-point DFT of real or complex input signal. 
* ------------------------------------------------------------------------------------------
* Parameters:
*    [in]     double *xR   -  Input signal vector real  part pointer. Vector size is [n x 1]. 
*
*    [in]     double *xI   -  Input signal vector image part pointer. Vector size is [n x 1].
*                             This pointer can be NULL if DFT is calculated for a real signal
*
*    [in]     int n        -  DFT size (input and output vectors size).
*
*    [out]    double *yR   -  DFT vector real  part pointer. Vector size is [n x 1].
*                             Memory must be allocated.
*     
*    [out]    double *yI   -  DFT vector image part pointer. Vector size is [n x 1].
*                             Memory must be allocated.
*     
* ------------------------------------------------------------------------------------------
* Return:
*    DSPL_OK         if DFT is calculted successfuly
*
*    DSPL_ERROR_PTR  if xR == NULL or yR == NULL or yI == NULL
*
*    DSPL_ERROR_SIZE if n<1.
* ------------------------------------------------------------------------------------------
* Author:
*    Sergey Bakhurin.                                                         www.dsplib.org    
*
*/

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






