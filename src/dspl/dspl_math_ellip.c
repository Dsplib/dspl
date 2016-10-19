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


#define DSPL_ELLIP_ITER	12





DSPL_API int dspl_ellip_acd_cmplx(double *wR, double *wI, int nw, double k, double *acdR, double *acdI)
{
	int n, m;
	double ktmp[DSPL_ELLIP_ITER];
	double uR, uI, tR, tI, tmp, mag;
	int res;
	
	if(!wR || !acdR || (wI && !acdI))
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(nw < 1)
	{
		res =DSPL_ERROR_SIZE;
		goto exit_label;	
	}
	if(k < 0.0 || k > 1.0)
	{
		res = DSPL_ERROR_ELLIP_K;
		goto exit_label;	
	}
	
	ktmp[0] = k;
	for(n = 1; n <  DSPL_ELLIP_ITER; n++)
	{
		ktmp[n]  = ktmp[n-1]/(1.0+sqrt(1.0-ktmp[n-1]*ktmp[n-1]));
		ktmp[n] *= ktmp[n];
	}
	
	
	for(m = 0; m < nw; m++)
	{
		uR = wR[m];
		uI = wI ? wI[m] : 0.0;
		
		for(n = 1; n < DSPL_ELLIP_ITER; n++)
		{
			mag = ktmp[n-1]*ktmp[n-1];
			tR = 1.0  -  mag * (uR * uR - uI * uI);
			tI = -2.0 *  mag * uR * uI;
			
			res = dspl_sqrt_cmplx(&tR, &tI, 1, &tR, &tI);
			if(res != DSPL_OK)
				goto exit_label;
			
			tR += 1.0;
			tR *= 1.0+ktmp[n];
			tI *= 1.0+ktmp[n];
			
			mag = tR * tR + tI * tI;			
			mag = 1.0/mag;
			
			uR*=2.0;
			uI*=2.0;
			
			tmp = mag * (uR * tR + uI * tI);
			uI  = mag * (uI * tR - uR * tI);
			uR = tmp;
		}
		
		res = dspl_acos_cmplx(&uR, &uI, 1, acdR+m, acdI+m);
		if(res != DSPL_OK)
			goto exit_label;
	}
	
	tmp = 2.0/M_PI;
	
	for(m = 0; m < nw; m++)
	{
		acdR[m] *= tmp;
		acdI[m] *= tmp;
	}

	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_ellip_asn_cmplx");
	return res;
}



DSPL_API int dspl_ellip_asn_cmplx(double *wR, double *wI, int nw, double k, double *asnR, double *asnI)
{
	int n, m;
	double ktmp[DSPL_ELLIP_ITER];
	double uR, uI, tR, tI, tmp, mag;
	int res;
	
	if(!wR || !asnR || (wI && !asnI))
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(nw < 1)
	{
		res =DSPL_ERROR_SIZE;
		goto exit_label;	
	}
	if(k < 0.0 || k > 1.0)
	{
		res = DSPL_ERROR_ELLIP_K;
		goto exit_label;	
	}
	
	ktmp[0] = k;
	for(n = 1; n <  DSPL_ELLIP_ITER; n++)
	{
		ktmp[n]  = ktmp[n-1]/(1.0+sqrt(1.0-ktmp[n-1]*ktmp[n-1]));
		ktmp[n] *= ktmp[n];
	}
	
	
	for(m = 0; m < nw; m++)
	{
		uR = wR[m];
		uI = wI ? wI[m] : 0.0;
		
		for(n = 1; n < DSPL_ELLIP_ITER; n++)
		{
			mag = ktmp[n-1]*ktmp[n-1];
			tR = 1.0  -  mag * (uR * uR - uI * uI);
			tI = -2.0 *  mag * uR * uI;
			
			res = dspl_sqrt_cmplx(&tR, &tI, 1, &tR, &tI);
			if(res != DSPL_OK)
				goto exit_label;
			
			tR += 1.0;
			tR *= 1.0+ktmp[n];
			tI *= 1.0+ktmp[n];
			
			mag = tR * tR + tI * tI;			
			mag = 1.0/mag;
			
			uR*=2.0;
			uI*=2.0;
			
			tmp = mag * (uR * tR + uI * tI);
			uI  = mag * (uI * tR - uR * tI);
			uR = tmp;
		}
		
		res = dspl_asin_cmplx(&uR, &uI, 1, asnR+m, asnI+m);
		if(res != DSPL_OK)
			goto exit_label;
	}
	
	tmp = 2.0/M_PI;
	for(m = 0; m < nw; m++)
	{
		asnR[m] *= tmp;
		asnI[m] *= tmp;
	}

	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_ellip_asn_cmplx");
	return res;
}






DSPL_API int dspl_ellip_cd_cmplx(double *uR, double *uI, int nu, double k, double *cdR, double *cdI)
{
	int n, m;
	double ktmp[DSPL_ELLIP_ITER];
	double wR, wI, mag;
	int res;
	
	if(!uR || !cdR || (uI && !cdI))
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(nu < 1)
	{
		res =DSPL_ERROR_SIZE;
		goto exit_label;	
	}
	if(k < 0.0 || k > 1.0)
	{
		res = DSPL_ERROR_ELLIP_K;
		goto exit_label;	
	}
	
	ktmp[0] = k;
	for(n = 1; n <  DSPL_ELLIP_ITER; n++)
	{
		ktmp[n]  = ktmp[n-1]/(1.0+sqrt(1.0-ktmp[n-1]*ktmp[n-1]));
		ktmp[n] *= ktmp[n];
	}
	for(m = 0; m < nu; m++)
	{
		wR = uR[m] * M_PI_2;
		wI = uI ? uI[m] * M_PI_2 : 0.0;
		
		res = dspl_cos_cmplx(&wR, &wI, 1, &wR, &wI);
		if(res != DSPL_OK)
			goto exit_label;
		for(n = DSPL_ELLIP_ITER-1; n > 0; n--)
		{
			mag = wR * wR + wI * wI;
			if(mag == 0)
			{
				wR = wI = 0.0;
				goto exit;
			}
			wR = ktmp[n]*wR + wR / mag;
			wI = ktmp[n]*wI - wI / mag;
			
			mag = wR * wR + wI * wI;
			if(mag == 0)
			{
				wR = wI = 0.0;
				goto exit;
			}			
			
			wR =  (1.0 + ktmp[n]) * wR / mag;
			wI = -(1.0 + ktmp[n]) * wI / mag;
		}
	exit:
		cdR[m] = wR;
		if(cdI)
			cdI[m] = wI;
	}

	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_ellip_cd_cmplx");
	return res;
}






DSPL_API int dspl_ellip_sn_cmplx(double *uR, double *uI, int nu, double k, double *snR, double *snI)
{
	int n, m;
	double ktmp[DSPL_ELLIP_ITER];
	double wR, wI, mag;
	int res;
	
	
	if(!uR || !snR || (uI && !snI))
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(nu < 1)
	{
		res =DSPL_ERROR_SIZE;
		goto exit_label;	
	}
	if(k < 0.0 || k > 1.0)
	{
		res =DSPL_ERROR_ELLIP_K;
		goto exit_label;	
	}
	
	ktmp[0] = k;
	for(n = 1; n <  DSPL_ELLIP_ITER; n++)
	{
		ktmp[n]  = ktmp[n-1]/(1.0+sqrt(1.0-ktmp[n-1]*ktmp[n-1]));
		ktmp[n] *= ktmp[n];
	}
	for(m = 0; m < nu; m++)
	{
		wR = uR[m] * M_PI_2;
		wI = uI ? uI[m] * M_PI_2 : 0.0;
		
		res = dspl_sin_cmplx(&wR, &wI, 1, &wR, &wI);
		if(res != DSPL_OK)
			goto exit_label;
		for(n = DSPL_ELLIP_ITER-1; n > 0; n--)
		{
			mag = wR * wR + wI * wI;
			if(mag == 0)
			{
				wR = wI = 0.0;
				goto exit;
			}
			wR = ktmp[n]*wR + wR / mag;
			wI = ktmp[n]*wI - wI / mag;
			
			mag = wR * wR + wI * wI;
			if(mag == 0)
			{
				wR = wI = 0.0;
				goto exit;
			}			
			
			wR =  (1.0 + ktmp[n]) * wR / mag;
			wI = -(1.0 + ktmp[n]) * wI / mag;
		}
	exit:
		snR[m] = wR;
		if(snI)
			snI[m] = wI;
	}
	
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_ellip_sn_cmplx");
	return res;
}





DSPL_API int dspl_ellipk(double *pk, int k, double *pK)
{
	
    int n, m;
    double ktmp;
	int res;

    if(!pk || !pK)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
    if(k < 1)
	{
		res =DSPL_ERROR_SIZE;
		goto exit_label;	
	}

	for(m = 0; m < k; m++)
	{
		ktmp = pk[m];
		if(ktmp >= 1.0 || ktmp<0.0)
		{
			res = DSPL_ERROR_ELLIP_K;
			goto exit_label;
		}
		pK[m] = M_PI_2;
		for(n = 1; n < DSPL_ELLIP_ITER; n++)
		{
			ktmp = ktmp / (1.0 + sqrt(1.0 - ktmp*ktmp));
			ktmp *= ktmp;
			pK[m] *= 1.0+ktmp;
		}
	}
	
    
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_ellipk");
	return res;
}
 
