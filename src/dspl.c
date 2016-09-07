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



#include <stdio.h>
#include <windows.h>
#include "dspl.h"


#ifndef DLL_EXPORT

p_dspl_ap2bpass					dspl_ap2bpass			;
p_dspl_ap2bstop					dspl_ap2bstop			;
p_dspl_ap2high					dspl_ap2high			;
p_dspl_ap2low					dspl_ap2low				;
p_dspl_asin_cmplx				dspl_asin_cmplx			;
p_dspl_asinh					dspl_asinh				;
p_dspl_butter_ap				dspl_butter_ap			;
p_dspl_cheby1_ap				dspl_cheby1_ap			;
p_dspl_cheby2_ap				dspl_cheby2_ap			;
p_dspl_compos					dspl_compos				;
p_dspl_conv						dspl_conv				;
p_dspl_conv_cmplx   			dspl_conv_cmplx     	;
p_dspl_cos_cmplx				dspl_cos_cmplx			;
p_dspl_cosh 					dspl_cosh 				;
p_dspl_dft 						dspl_dft 				;
p_dspl_ellip_cd_cmplx			dspl_ellip_cd_cmplx		;
p_dspl_ellip_sn_cmplx 			dspl_ellip_sn_cmplx		;
p_dspl_ellipk					dspl_ellipk				;
p_dspl_fft						dspl_fft		    	;
p_dspl_fft_shift				dspl_fft_shift			;
p_dspl_filter_iir				dspl_filter_iir	    	;
p_dspl_freqs					dspl_freqs		    	;
p_dspl_freqz					dspl_freqz		    	;
p_dspl_freqz_resp				dspl_freqz_resp			;
p_dspl_get_version 				dspl_get_version 		;
p_dspl_goertzel					dspl_goertzel			;
p_dspl_hilbert					dspl_hilbert			;
p_dspl_histogram				dspl_histogram			;
p_dspl_histogram_norm			dspl_histogram_norm		;
p_dspl_ifft						dspl_ifft		    	;
p_dspl_linspace					dspl_linspace			;
p_dspl_log_cmplx				dspl_log_cmplx			;
p_dspl_logspace					dspl_logspace			;
p_dspl_minmax					dspl_minmax				;
p_dspl_obj_create				dspl_obj_create			; 
p_dspl_obj_free					dspl_obj_free			; 		
p_dspl_polyval					dspl_polyval	    	;
p_dspl_polyval_cmplx			dspl_polyval_cmplx  	;
p_dspl_print_err				dspl_print_err	    	;
p_dspl_print_msg 				dspl_print_msg 	    	;
p_dspl_pwelch					dspl_pwelch				;
p_dspl_rand						dspl_rand				;
p_dspl_randn					dspl_randn				;
p_dspl_resample_lagrange		dspl_resample_lagrange	;	
p_dspl_sin_cmplx				dspl_sin_cmplx			;
p_dspl_sinh						dspl_sinh				;
p_dspl_sqrt_cmplx				dspl_sqrt_cmplx			;
p_dspl_unwrap					dspl_unwrap				;
p_dspl_window					dspl_window         	;
p_dspl_writebin					dspl_writebin			;
p_dspl_writetxt					dspl_writetxt       	;

#endif

HINSTANCE	dspl_load()
{
	HINSTANCE hDSPL;
	hDSPL = LoadLibrary("dspl.dll");
	LPCSTR	func_name;

	if(!hDSPL)
	{
		return NULL;
	}

	func_name = "dspl_ap2bpass";
	dspl_ap2bpass = (p_dspl_ap2bpass) GetProcAddress(hDSPL, func_name);
	if(!dspl_ap2bpass)
		goto error_proc;	

	
	func_name = "dspl_ap2bstop";
	dspl_ap2bstop = (p_dspl_ap2bstop) GetProcAddress(hDSPL, func_name);
	if(!dspl_ap2bstop)
		goto error_proc;
	

	func_name = "dspl_ap2high";	
	dspl_ap2high = (p_dspl_ap2high) GetProcAddress(hDSPL, func_name);
	if(!dspl_ap2high)
		goto error_proc;
	
	
	func_name = "dspl_ap2low";
	dspl_ap2low = (p_dspl_ap2low) GetProcAddress(hDSPL, func_name);
	if(!dspl_ap2low)
		goto error_proc;
	
	func_name = "dspl_asin_cmplx";
	dspl_asin_cmplx = (p_dspl_asin_cmplx) GetProcAddress(hDSPL, func_name);
	if(!dspl_asin_cmplx)
		goto error_proc;
	
	
	func_name = "dspl_asinh";
	dspl_asinh = (p_dspl_asinh) GetProcAddress(hDSPL, func_name);
	if(!dspl_asinh)
		goto error_proc;
	
	
	func_name = "dspl_butter_ap";
	dspl_butter_ap = (p_dspl_butter_ap) GetProcAddress(hDSPL, func_name);
	if(!dspl_butter_ap)
		goto error_proc;
	

	func_name = "dspl_cheby1_ap";
	dspl_cheby1_ap = (p_dspl_cheby1_ap) GetProcAddress(hDSPL, func_name);
	if(!dspl_cheby1_ap)
		goto error_proc;
	
		
	func_name = "dspl_cheby2_ap";
	dspl_cheby2_ap = (p_dspl_cheby2_ap) GetProcAddress(hDSPL, func_name);
	if(!dspl_cheby2_ap)
		goto error_proc;
	
	
	func_name = "dspl_compos";
	dspl_compos = (p_dspl_compos) GetProcAddress(hDSPL, func_name);
	if(!dspl_compos)
		goto error_proc;
	
	
	func_name = "dspl_conv";
	dspl_conv = (p_dspl_conv) GetProcAddress(hDSPL, func_name);
	if(!dspl_conv)
		goto error_proc;
	
	
	func_name = "dspl_conv_cmplx";
	dspl_conv_cmplx = (p_dspl_conv_cmplx) GetProcAddress(hDSPL, func_name);
	if(!dspl_conv_cmplx)
		goto error_proc;
	
	
	
	func_name = "dspl_cos_cmplx";
	dspl_cos_cmplx = (p_dspl_cos_cmplx) GetProcAddress(hDSPL, func_name);
	if(!dspl_cos_cmplx)
		goto error_proc;	
	
	
	
	func_name = "dspl_cosh";
	dspl_cosh = (p_dspl_cosh) GetProcAddress(hDSPL, func_name);
	if(!dspl_cosh)
		goto error_proc;
	
	
	func_name = "dspl_dft";
	dspl_dft = (p_dspl_dft) GetProcAddress(hDSPL, func_name);
	if(!dspl_dft)
		goto error_proc;
	
		
	func_name = "dspl_ellip_cd_cmplx";	
	dspl_ellip_cd_cmplx = (p_dspl_ellip_cd_cmplx) GetProcAddress(hDSPL, func_name);
	if(!dspl_ellip_cd_cmplx)
		goto error_proc;
	
	
	func_name = "dspl_ellip_sn_cmplx";
	dspl_ellip_sn_cmplx = (p_dspl_ellip_sn_cmplx) GetProcAddress(hDSPL, func_name);
	if(!dspl_ellip_sn_cmplx)
		goto error_proc;
	
		
	func_name = "dspl_ellipk";
	dspl_ellipk = (p_dspl_ellipk) GetProcAddress(hDSPL, func_name);
	if(!dspl_ellipk)
		goto error_proc;
	

	func_name = "dspl_fft";
	dspl_fft = (p_dspl_fft) GetProcAddress(hDSPL, func_name);
	if(!dspl_fft)
		goto error_proc;
	
	
	
	func_name = "dspl_fft_shift";
	dspl_fft_shift = (p_dspl_fft_shift) GetProcAddress(hDSPL, func_name);
	if(!dspl_fft_shift)
		goto error_proc;
	

	func_name = "dspl_filter_iir";
	dspl_filter_iir = (p_dspl_filter_iir) GetProcAddress(hDSPL, func_name);
	if(!dspl_filter_iir)
		goto error_proc;
	
	
	func_name = "dspl_freqs";
	dspl_freqs = (p_dspl_freqs) GetProcAddress(hDSPL, func_name);
	if(!dspl_freqs)
		goto error_proc;
	

	func_name = "dspl_freqz";
	dspl_freqz = (p_dspl_freqz) GetProcAddress(hDSPL, func_name);
	if(!dspl_freqz)
		goto error_proc;


	func_name = "dspl_freqz_resp";
	dspl_freqz_resp = (p_dspl_freqz_resp) GetProcAddress(hDSPL, func_name);
	if(!dspl_freqz_resp)
		goto error_proc;


	
	func_name = "dspl_get_version";
	dspl_get_version = (p_dspl_get_version) GetProcAddress(hDSPL, func_name);
	if(!dspl_get_version)
		goto error_proc;
		
	
	func_name = "dspl_goertzel";
	dspl_goertzel = (p_dspl_goertzel) GetProcAddress(hDSPL, func_name);
	if(!dspl_goertzel)
		goto error_proc;
	
	func_name = "dspl_hilbert";
	dspl_hilbert = (p_dspl_hilbert) GetProcAddress(hDSPL, func_name);
	if(!dspl_hilbert)
		goto error_proc;
	
	
	func_name = "dspl_histogram";
	dspl_histogram = (p_dspl_histogram) GetProcAddress(hDSPL, func_name);
	if(!dspl_histogram)
		goto error_proc;
	
	
	func_name = "dspl_histogram_norm";
	dspl_histogram_norm = (p_dspl_histogram_norm) GetProcAddress(hDSPL, func_name);
	if(!dspl_histogram_norm)
		goto error_proc;
		
	
	
	
	func_name = "dspl_ifft";
	dspl_ifft = (p_dspl_ifft) GetProcAddress(hDSPL, func_name);
	if(!dspl_ifft)
		goto error_proc;
	
	
	func_name = "dspl_linspace";
	dspl_linspace = (p_dspl_linspace) GetProcAddress(hDSPL, func_name);
	if(!dspl_linspace)
		goto error_proc;
	
	
	func_name = "dspl_logspace";
	dspl_logspace = (p_dspl_logspace) GetProcAddress(hDSPL, func_name);
	if(!dspl_logspace)
		goto error_proc;
	
		
	
	func_name = "dspl_log_cmplx";
	dspl_log_cmplx = (p_dspl_log_cmplx) GetProcAddress(hDSPL, func_name);
	if(!dspl_log_cmplx)
		goto error_proc;
	
	
	func_name = "dspl_minmax";
	dspl_minmax = (p_dspl_minmax) GetProcAddress(hDSPL, func_name);
	if(!dspl_minmax)
		goto error_proc;
	
	
	func_name = "dspl_obj_create";
	dspl_obj_create = (p_dspl_obj_create) GetProcAddress(hDSPL, func_name);
	if(!dspl_obj_create)
		goto error_proc;
	
	
	
	func_name = "dspl_obj_free";
	dspl_obj_free = (p_dspl_obj_free) GetProcAddress(hDSPL, func_name);
	if(!dspl_obj_free)
		goto error_proc;
	
	
	func_name = "dspl_polyval";
	dspl_polyval = (p_dspl_polyval) GetProcAddress(hDSPL, func_name);
	if(!dspl_polyval)
		goto error_proc;
	
	
	func_name = "dspl_polyval_cmplx";
	dspl_polyval_cmplx = (p_dspl_polyval_cmplx) GetProcAddress(hDSPL, func_name);
	if(!dspl_polyval_cmplx)
		goto error_proc;
	
	
	func_name = "dspl_print_err";
	dspl_print_err = (p_dspl_print_err) GetProcAddress(hDSPL, func_name);
	if(!dspl_print_err)
		goto error_proc;
	
	
	func_name = "dspl_print_msg";
	dspl_print_msg = (p_dspl_print_msg) GetProcAddress(hDSPL, func_name);
	if(!dspl_print_msg)
		goto error_proc;
	
	
	func_name = "dspl_pwelch";
	dspl_pwelch = (p_dspl_pwelch) GetProcAddress(hDSPL, func_name);
	if(!dspl_pwelch)
		goto error_proc;
	
	func_name = "dspl_rand";
	dspl_rand = (p_dspl_rand) GetProcAddress(hDSPL, func_name);
	if(!dspl_rand)
		goto error_proc;
	
	
	func_name = "dspl_randn";
	dspl_randn = (p_dspl_randn) GetProcAddress(hDSPL, func_name);
	if(!dspl_randn)
		goto error_proc;
	
	
	func_name = "dspl_resample_lagrange";
	dspl_resample_lagrange = (p_dspl_resample_lagrange) GetProcAddress(hDSPL, func_name);
	if(!dspl_resample_lagrange)
		goto error_proc;
	
	func_name = "dspl_sin_cmplx";
	dspl_sin_cmplx = (p_dspl_sin_cmplx) GetProcAddress(hDSPL, func_name);
	if(!dspl_sin_cmplx)
		goto error_proc;
	
	
	
	func_name = "dspl_sinh";
	dspl_sinh = (p_dspl_sinh) GetProcAddress(hDSPL, func_name);
	if(!dspl_sinh)
		goto error_proc;
	

	
	func_name = "dspl_sqrt_cmplx";
	dspl_sqrt_cmplx = (p_dspl_sqrt_cmplx) GetProcAddress(hDSPL, func_name);
	if(!dspl_sqrt_cmplx)
		goto error_proc;
	
	
	func_name = "dspl_unwrap";
	dspl_unwrap = (p_dspl_unwrap) GetProcAddress(hDSPL, func_name);
	if(!dspl_unwrap)
		goto error_proc;
		
	
	func_name = "dspl_window";
	dspl_window = (p_dspl_window) GetProcAddress(hDSPL, func_name);
	if(!dspl_window)
		goto error_proc;
	
	
	func_name = "dspl_writebin";	
	dspl_writebin = (p_dspl_writebin) GetProcAddress(hDSPL, func_name);
	if(!dspl_writebin)
		goto error_proc;
	
	
	func_name = "dspl_writetxt";	
	dspl_writetxt = (p_dspl_writetxt) GetProcAddress(hDSPL, func_name);
	if(!dspl_writetxt)
		goto error_proc;
	
	
	return hDSPL;
	
	
error_proc:	
	printf("Function %s loading ERROR!\n", func_name);
	FreeLibrary(hDSPL);
	return NULL;
}