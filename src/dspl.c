#include <stdio.h>
#include <windows.h>
#include "dspl.h"




p_dspl_ap2bpass			dspl_ap2bpass		;
p_dspl_ap2bstop			dspl_ap2bstop		;
p_dspl_ap2high			dspl_ap2high		;
p_dspl_ap2low			dspl_ap2low			;
p_dspl_asinh			dspl_asinh			;
p_dspl_butter_ap		dspl_butter_ap		;
p_dspl_cheby1_ap		dspl_cheby1_ap		;
p_dspl_cheby2_ap		dspl_cheby2_ap		;
p_dspl_compos			dspl_compos			;
p_dspl_conv				dspl_conv			;
p_dspl_conv_cmplx   	dspl_conv_cmplx     ;
p_dspl_cosh 			dspl_cosh 			;
p_dspl_dft 				dspl_dft 			;
p_dspl_goertzel			dspl_goertzel		;
p_dspl_ifft				dspl_ifft		    ;
p_dspl_fft				dspl_fft		    ;
p_dspl_fft_create		dspl_fft_create		;
p_dspl_fft_free			dspl_fft_free		;
p_dspl_fft_shift		dspl_fft_shift		;
p_dspl_filter_iir		dspl_filter_iir	    ;
p_dspl_freqs			dspl_freqs		    ;
p_dspl_freqz			dspl_freqz		    ;
p_dspl_get_version 		dspl_get_version 	;
p_dspl_linspace			dspl_linspace		;
p_dspl_logspace			dspl_logspace		;		
p_dspl_polyval			dspl_polyval	    ;
p_dspl_polyval_cmplx	dspl_polyval_cmplx  ;
p_dspl_print_err		dspl_print_err	    ;
p_dspl_print_msg 		dspl_print_msg 	    ;
p_dspl_sinh				dspl_sinh			;
p_dspl_unwrap			dspl_unwrap			;
p_dspl_window			dspl_window         ;
p_dspl_writebin			dspl_writebin		;
p_dspl_writetxt			dspl_writetxt        ;



HINSTANCE	dspl_load()
{
	HINSTANCE hInstDLL;
	hInstDLL = LoadLibrary("dspl.dll");
	
	printf("1\n");
	if(!hInstDLL)
	{
		return NULL;
	}
	printf("2\n");
	dspl_ap2bpass = (p_dspl_ap2bpass) GetProcAddress(hInstDLL, "dspl_ap2bpass");
	if(!dspl_ap2bpass)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	printf("3\n");
	dspl_ap2bstop = (p_dspl_ap2bstop) GetProcAddress(hInstDLL, "dspl_ap2bstop");
	if(!dspl_ap2bstop)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_ap2high = (p_dspl_ap2high) GetProcAddress(hInstDLL, "dspl_ap2high");
	if(!dspl_ap2high)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_ap2low = (p_dspl_ap2low) GetProcAddress(hInstDLL, "dspl_ap2low");
	if(!dspl_ap2low)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_asinh = (p_dspl_asinh) GetProcAddress(hInstDLL, "dspl_asinh");
	if(!dspl_asinh)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_butter_ap = (p_dspl_butter_ap) GetProcAddress(hInstDLL, "dspl_butter_ap");
	if(!dspl_butter_ap)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	

	dspl_cheby1_ap = (p_dspl_cheby1_ap) GetProcAddress(hInstDLL, "dspl_cheby1_ap");
	if(!dspl_cheby1_ap)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_cheby2_ap = (p_dspl_cheby2_ap) GetProcAddress(hInstDLL, "dspl_cheby2_ap");
	if(!dspl_cheby2_ap)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_compos = (p_dspl_compos) GetProcAddress(hInstDLL, "dspl_compos");
	if(!dspl_compos)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_conv = (p_dspl_conv) GetProcAddress(hInstDLL, "dspl_conv");
	if(!dspl_conv)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_conv_cmplx = (p_dspl_conv_cmplx) GetProcAddress(hInstDLL, "dspl_conv_cmplx");
	if(!dspl_conv_cmplx)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_cosh = (p_dspl_cosh) GetProcAddress(hInstDLL, "dspl_cosh");
	if(!dspl_cosh)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_dft = (p_dspl_dft) GetProcAddress(hInstDLL, "dspl_dft");
	if(!dspl_dft)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_goertzel = (p_dspl_goertzel) GetProcAddress(hInstDLL, "dspl_goertzel");
	if(!dspl_goertzel)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_ifft = (p_dspl_ifft) GetProcAddress(hInstDLL, "dspl_ifft");
	if(!dspl_ifft)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	
	dspl_fft = (p_dspl_fft) GetProcAddress(hInstDLL, "dspl_fft");
	if(!dspl_fft)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	

	dspl_fft_create = (p_dspl_fft_create) GetProcAddress(hInstDLL, "dspl_fft_create");
	if(!dspl_fft_create)
	{
		
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	dspl_fft_free = (p_dspl_fft_free) GetProcAddress(hInstDLL, "dspl_fft_free");
	if(!dspl_fft_free)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_fft_shift = (p_dspl_fft_shift) GetProcAddress(hInstDLL, "dspl_fft_shift");
	if(!dspl_fft_shift)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	

	dspl_filter_iir = (p_dspl_filter_iir) GetProcAddress(hInstDLL, "dspl_filter_iir");
	if(!dspl_filter_iir)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_freqs = (p_dspl_freqs) GetProcAddress(hInstDLL, "dspl_freqs");
	if(!dspl_freqs)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	

	dspl_freqz = (p_dspl_freqz) GetProcAddress(hInstDLL, "dspl_freqz");
	if(!dspl_freqz)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}

	

	dspl_get_version = (p_dspl_get_version) GetProcAddress(hInstDLL, "dspl_get_version");
	if(!dspl_get_version)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_linspace = (p_dspl_linspace) GetProcAddress(hInstDLL, "dspl_linspace");
	if(!dspl_linspace)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_logspace = (p_dspl_logspace) GetProcAddress(hInstDLL, "dspl_logspace");
	if(!dspl_logspace)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	
	dspl_polyval = (p_dspl_polyval) GetProcAddress(hInstDLL, "dspl_polyval");
	if(!dspl_polyval)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_polyval_cmplx = (p_dspl_polyval_cmplx) GetProcAddress(hInstDLL, "dspl_polyval_cmplx");
	if(!dspl_polyval_cmplx)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_print_err = (p_dspl_print_err) GetProcAddress(hInstDLL, "dspl_print_err");
	if(!dspl_print_err)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_print_msg = (p_dspl_print_msg) GetProcAddress(hInstDLL, "dspl_print_msg");
	if(!dspl_print_msg)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
		
	
	dspl_unwrap = (p_dspl_unwrap) GetProcAddress(hInstDLL, "dspl_unwrap");
	if(!dspl_unwrap)
	{
		printf("dspl_unwrap function loading error!\n");
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	dspl_window = (p_dspl_window) GetProcAddress(hInstDLL, "dspl_window");
	if(!dspl_window)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_writebin = (p_dspl_writebin) GetProcAddress(hInstDLL, "dspl_writebin");
	if(!dspl_writebin)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	dspl_writetxt = (p_dspl_writetxt) GetProcAddress(hInstDLL, "dspl_writetxt");
	if(!dspl_writetxt)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	
	
	dspl_sinh = (p_dspl_sinh) GetProcAddress(hInstDLL, "dspl_sinh");
	if(!dspl_sinh)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	
	return hInstDLL;
}