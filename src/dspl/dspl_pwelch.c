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


DSPL_API int dspl_pwelch(double *xR, double *xI, int n, 
						int win_type, double win_param, 
						int npsd, int noverlap, void *pdspl, 
						double fs, double *ppsd, double *pfrq)
{
	double *win = NULL, wg;
	double *tR = NULL, *tI = NULL, *sR = NULL, *sI = NULL;
	int res, k, pos, cnt;
	
	
	if(!xR || !pdspl || !ppsd)
		return DSPL_ERROR_PTR;
	if(n<1 || npsd < 1)
		return DSPL_ERROR_SIZE;
	if(noverlap < 1 || noverlap > npsd)
		return DSPL_ERROR_OVERLAP;
	if(fs < 0.0)
		return DSPL_ERROR_FS;
	
	win = (double*)malloc(npsd*sizeof(double));
	res = dspl_window(win, npsd, win_type, win_param);
	if(res != DSPL_OK)
		goto exit_label;
	
	wg = 0.0;
	for(k = 0; k < npsd; k++)
		wg += win[k] * win[k];
	
	wg = 1.0 / wg;
	
	tR = (double*)malloc(npsd*sizeof(double));
	tI = (double*)malloc(npsd*sizeof(double));
	sR = (double*)malloc(npsd*sizeof(double));
	sI = (double*)malloc(npsd*sizeof(double));
	
	pos = 0;
	cnt = 0;
	
	while(pos+npsd <= n)
	{
		if(xI)
		{
			for(k = 0; k < npsd; k++)
			{
				sR[k] = xR[k+pos]*win[k];
				sI[k] = xI[k+pos]*win[k];
			}
		}
		else
		{
			for(k = 0; k < npsd; k++)
			{
				sR[k] = xR[k+pos]*win[k];
				sI[k] = 0.0;
			}
		}
		res = dspl_fft(sR, sI, npsd, pdspl, tR, tI);
		
		if(res != DSPL_OK)
			goto exit_label;
	
		for(k = 0; k < npsd; k++)
			ppsd[k] += wg * (tR[k] * tR[k] + tI[k] * tI[k]);
		
		pos += noverlap;
		cnt++;
	}
	
	for(k = 0; k < npsd; k++)
		ppsd[k] /= (double)cnt * fs;
	
	if(pfrq)
		dspl_linspace(0, fs, npsd, DSPL_PERIODIC, pfrq);
	
	res = DSPL_OK;
	
exit_label:
	if(win)
		free(win);
	if(tR)
		free(tR);
	if(tR)
		free(tI);
	if(tR)
		free(sR);
	if(tR)
		free(sI);
	return DSPL_OK;
	
}