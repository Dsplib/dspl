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


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dspl.h"



/*
* Print DSPL error code 
* ------------------------------------------------------------------------------------------
* Parameters:
*	[in] 	int res		-	DSPL function returned value
*
*	[in]	int printCR	-	Print CR symbol	
*
* ------------------------------------------------------------------------------------------
* Author:
*	Sergey Bakhurin. 														www.dsplib.org	
*
*/
DSPL_API void dspl_print_err(int res, char* funcName)
{
	switch(res)
	{
		case DSPL_OK:
			return;			
		case DSPL_ERROR_ELLIP_K:
			printf("%s ERROR: Complete elliptic integral modulus can be from 0 to 1!", funcName);
			break;	
		case DSPL_ERROR_FFT_SIZE:
			printf("%s ERROR: FFT size must be power of two!", funcName);
			break;
		case DSPL_ERROR_FILTER_A0:	
			printf("%s ERROR: IIR filter coefficient a[0] cannot be zero!", funcName);
			break;
		case DSPL_ERROR_FILTER_ORD:	
			printf("%s ERROR: filter order must be more than zero!", funcName);
			break;
		case DSPL_ERROR_FILTER_RP:	
			printf("%s ERROR: filter Rp parameter must be more than zero!", funcName);
			break;
		case DSPL_ERROR_FILTER_RS:
			printf("%s ERROR: filter Rs parameter must be more than zero!", funcName);
			break;
		case DSPL_ERROR_FILTER_WP:
			printf("%s ERROR: filter passband parameter is wrong!", funcName);
			break;
		case DSPL_ERROR_FNAME:	
			printf("%s ERROR: file name is wrong!", funcName);
			break;
		case DSPL_ERROR_FOPEN:
			printf("%s ERROR: cannot to open file!", funcName);
			break;		
		case DSPL_ERROR_POLY_ORD:	
			printf("%s ERROR: polynomial order must be more than zero!", funcName);
			break;
		case DSPL_ERROR_PTR:
			printf("%s ERROR: pointer is wrong!", funcName);
			break;
		case DSPL_ERROR_SIZE:
			printf("%s ERROR: input array size is wrong!", funcName);
			break;
		case DSPL_ERROR_UNWRAP:
			printf("%s ERROR: unwrap level or margin is wrong!", funcName);
			break;
		//case DSPL_ERROR_WIN_TYPE:		
			
		default:
			printf("%s Unknown error code 0x%.8x", funcName, res);		
	}
	printf("\n");	
}






/*
* Print DSPL message to console.
* ------------------------------------------------------------------------------------------
* Parameters:
*	[in] 	char* msg 		-	Text message
*
*	[in]	int printTime	-	Print current time in format [yyyy-mm-dd hh:mm:ss]	
*
*	[in]	int msgLen		- 	Message length
* ------------------------------------------------------------------------------------------
* Author:
*	Sergey Bakhurin. 														www.dsplib.org	
*
*/
DSPL_API void dspl_print_msg(char* msg, int printTime, int msgLen)
{
	int len;
	time_t t;
	struct tm *ti;
	char msgout[DSPL_MSG_LENGTH];
	
	memset(msgout, 0, DSPL_MSG_LENGTH);
	if(printTime)
	{
		time(&t);
		ti = localtime(&t);
		sprintf(msgout, "[%.4d-%.2d-%.2d %.2d:%.2d:%.2d] > ", ti->tm_year+1900, 
				ti->tm_mon+1, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);

	}
	sprintf(msgout, "%s%s", msgout, msg);
	len = strlen(msgout);
	while(len<msgLen)
	{
		sprintf(msgout, "%s.", msgout);
		len++;	
	}
	printf("%s", msgout);
}








/*
 Save data to bin file.
*/
DSPL_API int dspl_writebin(double* x, double *y, int n, char* fn)
{
	int k, res;
	FILE* pFile = NULL;
	
	if(!x)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;
	}
	if(n < 1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;
	}
	if(!fn)
	{
		res =  DSPL_ERROR_FNAME;
		goto exit_label;
	}
	
	pFile = fopen(fn, "wb");
	if(pFile == NULL)
	{
		res = DSPL_ERROR_FOPEN;
		goto exit_label;
	}
	k = y ? DSPL_DAT_COMPLEX : DSPL_DAT_REAL;
	fwrite(&k, sizeof(int), 1, pFile);
	fwrite(&n, sizeof(int), 1, pFile);
	k = 1;
	fwrite(&k, sizeof(int), 1, pFile);
	fwrite(x, sizeof(double), n, pFile);
	if(y)
		fwrite(y, sizeof(double), n, pFile);

	res = DSPL_OK;
exit_label:
	dspl_print_err(res, "dspl_writebin");
	if(pFile)
		fclose(pFile);
	return res;	
}




/*
 Save data to text file.
*/
DSPL_API int dspl_writetxt(double* x, double *y, int n, char* fn)
{
	int k;
	int res;
	FILE* pFile = NULL;
	
	if(!x)
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;
	}
	if(n < 1)
	{
		res =DSPL_ERROR_SIZE;
		goto exit_label;
	}
	if(!fn)
	{
		res =DSPL_ERROR_FNAME;
		goto exit_label;
	}
	
	pFile = fopen(fn, "w+");
	if(pFile == NULL)
	{
		res =DSPL_ERROR_FOPEN;
		goto exit_label;
	}
	if(y)
		for(k = 0; k < n; k++)
			fprintf(pFile, "%+.12E\t%+.12E\n", x[k], y[k]);
	else
		for(k = 0; k < n; k++)
			fprintf(pFile, "%+.12E\n", x[k]);
	
	res = DSPL_OK;
exit_label:
	dspl_print_err(res, "dspl_writetxt");
	if(pFile)
		fclose(pFile);
	return res;	

}


