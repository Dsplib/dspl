
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define P 	1
#define Q	1
#define K	512
#define N	4 
#define FN_LEN	256

int main()
{

	HINSTANCE hDSPL;		/* dspl handle 						*/
	
	double s[N] = {0.0, 1.0, 0.0, 0.0};
		
	double *t=NULL;		/* time 								*/
	double *h=NULL;		/* Frac delay filter impulse response	*/
	double w[K];		/* Normalized Angular frequency			*/
	double H[K];		/* Frac delay filter magnitude			*/
	double GD[K];		/* Frac delay filter group delay		*/

	int  nh;	
	double frac_delay;	/* current fractional delay  			*/
	char fn[FN_LEN];	/* file name for result  				*/
	
    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	/* Allocation memory and fill vectors */
	dspl_resample_spline(s, N, P, Q, 0.0, &h, &nh);
	t = (double*) malloc(nh*sizeof(double));	
	dspl_linspace(0, nh, nh, DSPL_PERIODIC, t);	
	dspl_linspace(0, M_PI, K, DSPL_PERIODIC, w);
	
	/* cyycle for fraction delay from 0 to 1 */
	for(frac_delay = 0.0; frac_delay<1.0; frac_delay+=0.1)
	{
		/* current delay filter impulse response  */
		dspl_resample_spline(s, N, P, Q, frac_delay, &h, &nh);
		
		/* save to file */
		memset(fn, 0, FN_LEN);
		sprintf(fn, "dat/resample_spline_filter_fd_time_%.1f.txt", frac_delay);
		dspl_writetxt(t,h,nh,fn);
	
		/* current fractional delay filter magnitude (dB) and group delay  */
		dspl_freqz_resp(h, NULL, nh-1, w, K, H, NULL, GD);
		
		/*  save magnitude to file  */
		memset(fn, 0, FN_LEN);
		sprintf(fn, "dat/resample_spline_filter_fd_mag_%.1f.txt", frac_delay);
		dspl_writetxt(w,H,K,fn);
	
	
		/* dave group delay to file */
		memset(fn, 0, FN_LEN);
		sprintf(fn, "dat/resample_spline_filter_fd_gd_%.1f.txt", frac_delay);
		dspl_writetxt(w,GD,K,fn);
	}
		
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	free(h);
	free(t);
	return 0;
}
