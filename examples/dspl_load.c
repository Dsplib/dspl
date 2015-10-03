#include <stdio.h>
#include <windows.h>
#include "dspl.h"
#include "dspl_load.h"



p_dspl_conv				dspl_conv			;
p_dspl_conv_cmplx   	dspl_conv_cmplx     ;
p_dspl_dft 				dspl_dft 			;
p_dspl_fft				dspl_fft		    ;
p_dspl_fft_create		dspl_fft_create		;
p_dspl_fft_free			dspl_fft_free		;
p_dspl_filter_iir		dspl_filter_iir	    ;
p_dspl_get_version 		dspl_get_version 	;
p_dspl_print_err		dspl_print_err	    ;
p_dspl_print_msg 		dspl_print_msg 	    ;
p_dspl_savetxt			dspl_savetxt        ;





HINSTANCE	dspl_load()
{
	HINSTANCE hInstDLL;
	hInstDLL = LoadLibrary("dspl.dll");
	
	if(!hInstDLL)
		return NULL;
	
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
	
	
	dspl_dft = (p_dspl_dft) GetProcAddress(hInstDLL, "dspl_dft");
	if(!dspl_dft)
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
	

	dspl_filter_iir = (p_dspl_filter_iir) GetProcAddress(hInstDLL, "dspl_filter_iir");
	if(!dspl_filter_iir)
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
	
	
	dspl_savetxt = (p_dspl_savetxt) GetProcAddress(hInstDLL, "dspl_savetxt");
	if(!dspl_savetxt)
	{
		FreeLibrary(hInstDLL);
		return NULL;		
	}
	
	return hInstDLL;
}