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



/* DSPL VERSION */
#define DSPL_VERSION 0x00100105


/*
* Get DSPL version.
* This function return DSPL version
*/
DSPL_API int dspl_get_version(int printFlag)
{
	int ver = DSPL_VERSION;
	int yy;
	int mm;
	int dd;
	

	if(printFlag)
	{
		yy = (ver & 0x00FF0000) >> 16;
		mm = (ver & 0x0000FF00) >> 8;
		dd = (ver & 0x000000FF);
		printf("\n\n     D S P L\n");
		printf("     version %.2d.%.2d.%.2d\n\n", yy,mm,dd);
		printf("     Copyright (c) 2015, 2016  Sergey Bakhurin\n");
		printf("     home page: www.dsplib.org\n\n");		
	}
	return ver;
}







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
DSPL_API void dspl_print_err(int res, int printCR)
{
	switch(res)
	{
		case DSPL_OK:
			printf("OK");
			break;
		case DSPL_ERROR_PTR:
			printf("ERROR: pointer is wrong!");
			break;
		case DSPL_ERROR_SIZE:
			printf("ERROR: input arrray size is wrong!");
			break;
		case DSPL_ERROR_FILTER_A0:
			printf("ERROR: IIR filter coefficient a[0] cannot be zero!");
			break;
		default:
			printf("Unknown error");		
	}
	if(printCR)
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
	int k;
	FILE* pFile = NULL;
	
	if(!x)
		return DSPL_ERROR_PTR;
	if(n < 1)
		return DSPL_ERROR_SIZE;
	if(!fn)
		return DSPL_ERROR_FNAME;
	
	pFile = fopen(fn, "wb");
	if(pFile == NULL)
		return DSPL_ERROR_FOPEN;
	k = y ? DSPL_DAT_COMPLEX : DSPL_DAT_REAL;
	fwrite(&k, sizeof(int), 1, pFile);
	fwrite(&n, sizeof(int), 1, pFile);
	k = 1;
	fwrite(&k, sizeof(int), 1, pFile);
	fwrite(x, sizeof(double), n, pFile);
	if(y)
		fwrite(y, sizeof(double), n, pFile);
	fclose(pFile);
	return DSPL_OK;	
}

/*
 Save data to text file.
*/
DSPL_API int dspl_writetxt(double* x, double *y, int n, char* fn)
{
	int k;
	FILE* pFile = NULL;
	
	if(!x)
		return DSPL_ERROR_PTR;
	if(n < 1)
		return DSPL_ERROR_SIZE;
	if(!fn)
		return DSPL_ERROR_FNAME;
	
	pFile = fopen(fn, "w");
	if(pFile == NULL)
		return DSPL_ERROR_FOPEN;
	if(y)
		for(k = 0; k < n; k++)
			fprintf(pFile, "%+.12E\t%+.12E\n", x[k], y[k]);
	else
		for(k = 0; k < n; k++)
			fprintf(pFile, "%+.12E\n", x[k]);
	fclose(pFile);
	return DSPL_OK;	
}


