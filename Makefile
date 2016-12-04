OS_VER	= 64
CC      = gcc
INC_DIR = src
OBJ_DIR = obj

ifeq ($(OS_VER), 32)
	FFTW_DIR = lib/fftw32
	REL_DIR		 = bin/release/gcc/dspl32 
	VC_DIR		 = bin/release/vc/dspl32
endif

ifeq ($(OS_VER), 64)
	FFTW_DIR = lib/fftw64
	REL_DIR		 = bin/release/gcc/dspl64
	VC_DIR		 = bin/release/vc/dspl64

endif


DAT2CM_DIR = src/dat2cm

DLL_SRC_DIR  = src/dspl
DLL_OBJ_DIR  = obj/dspl
DLL_BIN_DIR  = bin/dspl
EXE_SRC_DIR  = src/examples
EXE_OBJ_DIR  = obj/examples
EXE_BIN_DIR  = bin/examples
VER_SRC_DIR  = src/verification
VER_OBJ_DIR  = obj/verification
VER_BIN_DIR  = bin/verification
PRF_SRC_DIR  = src/performance
PRF_OBJ_DIR  = obj/performance
PRF_BIN_DIR  = bin/performance




BIN_DIR = bin
OBJ_DIR = obj

DLL_CFLAGS  = -c -Wall -O3 -D DLL_EXPORT -I$(INC_DIR) -I$(FFTW_DIR) -fopenmp
EXE_CFLAGS  = -c -Wall -O3 -I$(INC_DIR)
VER_CFLAGS  = -c -Wall -O3 -I$(INC_DIR)


DLL_OBJS=	$(DLL_OBJ_DIR)/dspl_cconv.o\
			$(DLL_OBJ_DIR)/dspl_compos.o\
			$(DLL_OBJ_DIR)/dspl_conv.o\
			$(DLL_OBJ_DIR)/dspl_dft.o\
			$(DLL_OBJ_DIR)/dspl_fft.o\
			$(DLL_OBJ_DIR)/dspl_filter_ap.o\
			$(DLL_OBJ_DIR)/dspl_filter_iir.o\
			$(DLL_OBJ_DIR)/dspl_filter_fir.o\
			$(DLL_OBJ_DIR)/dspl_filter_transform.o\
			$(DLL_OBJ_DIR)/dspl_freqs.o\
			$(DLL_OBJ_DIR)/dspl_freqz.o\
			$(DLL_OBJ_DIR)/dspl_goertzel.o\
			$(DLL_OBJ_DIR)/dspl_hilbert.o\
			$(DLL_OBJ_DIR)/dspl_histogram.o\
			$(DLL_OBJ_DIR)/dspl_inout.o\
			$(DLL_OBJ_DIR)/dspl_linspace.o\
			$(DLL_OBJ_DIR)/dspl_logspace.o\
			$(DLL_OBJ_DIR)/dspl_main.o\
			$(DLL_OBJ_DIR)/dspl_math_basic.o\
			$(DLL_OBJ_DIR)/dspl_math_ellip.o\
			$(DLL_OBJ_DIR)/dspl_math_hyperbolic.o\
			$(DLL_OBJ_DIR)/dspl_math_stat.o\
			$(DLL_OBJ_DIR)/dspl_polyval.o\
			$(DLL_OBJ_DIR)/dspl_pwelch.o\
			$(DLL_OBJ_DIR)/dspl_rand_gen.o\
			$(DLL_OBJ_DIR)/dspl_resample.o\
			$(DLL_OBJ_DIR)/dspl_unwrap.o\
			$(DLL_OBJ_DIR)/dspl_win.o\

			
RES_OBJ = $(DLL_OBJ_DIR)/resource.o			

			
			



EXE_FILES =	$(EXE_BIN_DIR)/dft_freq_fig1.exe\
			$(EXE_BIN_DIR)/dft_freq_fig4.exe\
			$(EXE_BIN_DIR)/hilbert_fft.exe\
			$(EXE_BIN_DIR)/goertzel_dtmf.exe\
			$(EXE_BIN_DIR)/randn_histogram.exe\
			$(EXE_BIN_DIR)/resample_lagrange_ex_frac_delay.exe\
			$(EXE_BIN_DIR)/resample_lagrange_ex_fs.exe\
			$(EXE_BIN_DIR)/resample_lagrange_ex_interp.exe\
			$(EXE_BIN_DIR)/resample_lagrange_filter_interp.exe\
			$(EXE_BIN_DIR)/resample_lagrange_filter_frac_delay.exe\
			$(EXE_BIN_DIR)/resample_spline_filter_frac_delay.exe\
		
VER_FILES = $(VER_BIN_DIR)/ver_dspl_ellipj.exe\
			$(VER_BIN_DIR)/ver_dspl_ellipj_inv.exe\
			$(VER_BIN_DIR)/ver_dspl_ellipk.exe\
			$(VER_BIN_DIR)/ver_dspl_fft.exe\
			$(VER_BIN_DIR)/ver_dspl_fir_lpf.exe\
		    $(VER_BIN_DIR)/ver_dspl_hilbert.exe\
		    $(VER_BIN_DIR)/ver_dspl_histogram_norm.exe\
			$(VER_BIN_DIR)/ver_dspl_math_basic.exe\
		    $(VER_BIN_DIR)/ver_dspl_pwelch.exe\
			

PRF_FILES = $(PRF_BIN_DIR)/conv_performance.exe\
			$(PRF_BIN_DIR)/fft_performance.exe\
				 
 

COMMON_OBJS = $(OBJ_DIR)/dspl.o\


all:	$(EXE_BIN_DIR)/dspl.dll\
		$(VER_BIN_DIR)/dspl.dll\
		$(PRF_BIN_DIR)/dspl.dll\
		$(EXE_FILES)\
		$(VER_FILES)\
		$(PRF_FILES)\
		dat2cm
		
# DSPL.DLL compile	
$(EXE_BIN_DIR)/dspl.dll:$(DLL_OBJS) $(RES_OBJ)
	$(CC) -o $(EXE_BIN_DIR)/dspl.dll -s -shared $(DLL_OBJS) $(RES_OBJ) -Wl,--subsystem,windows  -L$(FFTW_DIR) -llibfftw3-3 -lm -fopenmp
	echo "$(date) $(ls -1 | wc -l)"
	cp 	$(FFTW_DIR)/libfftw3-3.dll   	$(EXE_BIN_DIR)/libfftw3-3.dll
	cp 	$(EXE_BIN_DIR)/dspl.dll 		$(REL_DIR)/bin/dspl.dll 	
	cp	$(FFTW_DIR)/libfftw3-3.dll		$(REL_DIR)/bin/libfftw3-3.dll
	cp	$(INC_DIR)/dspl.h				$(REL_DIR)/src/dspl.h
	cp	$(INC_DIR)/dspl.c				$(REL_DIR)/src/dspl.c
	cp 	$(EXE_BIN_DIR)/dspl.dll 		$(VC_DIR)/bin/dspl.dll 	
	cp	$(FFTW_DIR)/libfftw3-3.dll		$(VC_DIR)/bin/libfftw3-3.dll
	cp	$(INC_DIR)/dspl.h				$(VC_DIR)/src/dspl.h
	cp	$(INC_DIR)/dspl.c				$(VC_DIR)/src/dspl.c
                  

$(VER_BIN_DIR)/dspl.dll:$(DLL_OBJS) $(RES_OBJ)
	$(CC) -o $(VER_BIN_DIR)/dspl.dll -s -shared $(DLL_OBJS) $(RES_OBJ) -Wl,--subsystem,windows  -L$(FFTW_DIR) -llibfftw3-3 -lm -fopenmp
	cp	$(FFTW_DIR)/libfftw3-3.dll   $(VER_BIN_DIR)/libfftw3-3.dll

$(PRF_BIN_DIR)/dspl.dll:$(DLL_OBJS) $(RES_OBJ)
	$(CC) -o $(PRF_BIN_DIR)/dspl.dll -s -shared $(DLL_OBJS) $(RES_OBJ) -Wl,--subsystem,windows  -L$(FFTW_DIR) -llibfftw3-3 -lm -fopenmp
	cp	$(FFTW_DIR)/libfftw3-3.dll   $(PRF_BIN_DIR)/libfftw3-3.dll



$(RES_OBJ):$(DLL_SRC_DIR)/resource.rc
	windres -i $(DLL_SRC_DIR)/resource.rc -o $(RES_OBJ)

	
$(DLL_OBJ_DIR)/%.o:$(DLL_SRC_DIR)/%.c                         
	$(CC) $(DLL_CFLAGS) -c $< -o $@   -L$(FFTW_DIR) -lfftw3_threads


	


$(EXE_BIN_DIR)/%.exe: $(EXE_OBJ_DIR)/%.o  $(COMMON_OBJS)
	$(CC) $(OBJ_DIR)/dspl.o $< -o $@

$(EXE_OBJ_DIR)/%.o:$(EXE_SRC_DIR)/%.c
	$(CC) $(EXE_CFLAGS)  $< -o $@



$(VER_BIN_DIR)/%.exe: $(VER_OBJ_DIR)/%.o  $(COMMON_OBJS)
	$(CC) $(OBJ_DIR)/dspl.o $< -o $@

$(VER_OBJ_DIR)/%.o:$(VER_SRC_DIR)/%.c
	$(CC) $(EXE_CFLAGS)  $< -o $@


$(PRF_BIN_DIR)/%.exe: $(PRF_OBJ_DIR)/%.o  $(COMMON_OBJS)
	$(CC) $(OBJ_DIR)/dspl.o $< -o $@

$(PRF_OBJ_DIR)/%.o:$(PRF_SRC_DIR)/%.c
	$(CC) $(EXE_CFLAGS)  $< -o $@




$(OBJ_DIR)/%.o:$(INC_DIR)/%.c
	$(CC) $(EXE_CFLAGS)  -c $< -o $@

	
dat2cm:$(DAT2CM_DIR)/dat2cm.c
	$(CC) $(DAT2CM_DIR)/dat2cm.c -o $(EXE_BIN_DIR)/tex/dat2cm.exe


$(DLL_OBJS):	 $(INC_DIR)/dspl.h 

$(EXE_FILES):	 $(INC_DIR)/dspl.h

$(VER_FILES):	 $(INC_DIR)/dspl.h 

$(PRF_FILES):	 $(INC_DIR)/dspl.h 

$(COMMON_OBJS):	 $(INC_DIR)/dspl.h


clean:
	rm -f   $(DLL_OBJ_DIR)/*.o
	rm -f   $(EXE_OBJ_DIR)/*.o
	rm -f   $(VER_OBJ_DIR)/*.o
	rm -f   $(PRF_OBJ_DIR)/*.o
	rm -f   $(OBJ_DIR)/*.o
	rm -f   $(EXE_BIN_DIR)/*.exe
	rm -f   $(EXE_BIN_DIR)/*.dll
	rm -f   $(VER_BIN_DIR)/*.exe
	rm -f   $(VER_BIN_DIR)/*.dll	
	rm -f   $(PRF_BIN_DIR)/*.exe
	rm -f   $(PRF_BIN_DIR)/*.dll
	                                                                      