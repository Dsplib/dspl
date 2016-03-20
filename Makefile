CC      = gcc
INC_DIR = src
OBJ_DIR = obj


DLL_SRC_DIR  = src/dspl

DLL_OBJ_DIR  = obj/dspl

DLL_BIN_DIR  = bin/dspl


EXE_SRC_DIR  = src/examples
EXE_OBJ_DIR  = obj/examples
EXE_BIN_DIR  = bin/examples

VER_SRC_DIR  = src/verification
VER_OBJ_DIR  = obj/verification
VER_BIN_DIR  = bin/verification


BIN_DIR = bin
OBJ_DIR = obj

DLL_CFLAGS  = -c -Wall -O3 -D DLL_EXPORT -I$(INC_DIR)
EXE_CFLAGS  = -c -Wall -O3 -I$(INC_DIR)
VER_CFLAGS  = -c -Wall -O3 -I$(INC_DIR)


DLL_OBJS=	$(DLL_OBJ_DIR)/dspl.o\
			$(DLL_OBJ_DIR)/dspl_compos.o\
			$(DLL_OBJ_DIR)/dspl_conv.o\
			$(DLL_OBJ_DIR)/dspl_dft.o\
			$(DLL_OBJ_DIR)/dspl_goertzel.o\
			$(DLL_OBJ_DIR)/dspl_fft.o\
			$(DLL_OBJ_DIR)/dspl_filter_ap.o\
			$(DLL_OBJ_DIR)/dspl_filter_iir.o\
			$(DLL_OBJ_DIR)/dspl_filter_transform.o\
			$(DLL_OBJ_DIR)/dspl_freqs.o\
			$(DLL_OBJ_DIR)/dspl_freqz.o\
			$(DLL_OBJ_DIR)/dspl_inout.o\
			$(DLL_OBJ_DIR)/dspl_linspace.o\
			$(DLL_OBJ_DIR)/dspl_logspace.o\
			$(DLL_OBJ_DIR)/dspl_math_basic.o\
			$(DLL_OBJ_DIR)/dspl_math_hyperbolic.o\
			$(DLL_OBJ_DIR)/dspl_polyval.o\
			$(DLL_OBJ_DIR)/dspl_unwrap.o\
			$(DLL_OBJ_DIR)/dspl_win.o\

			




EXE_BINS=	$(EXE_BIN_DIR)/ex_dspl.exe\
			$(EXE_BIN_DIR)/ex_dspl_butter_ap.exe\
			$(EXE_BIN_DIR)/ex_dspl_cheby1_ap.exe\
			$(EXE_BIN_DIR)/ex_dspl_cheby2_ap.exe\
			$(EXE_BIN_DIR)/ex_dspl_compos.exe\
			$(EXE_BIN_DIR)/ex_dspl_conv.exe\
			$(EXE_BIN_DIR)/ex_dspl_dft.exe\
			$(EXE_BIN_DIR)/ex_dspl_goertzel.exe\
			$(EXE_BIN_DIR)/ex_dspl_fft.exe\
			$(EXE_BIN_DIR)/ex_dspl_linspace.exe\
			$(EXE_BIN_DIR)/ex_dspl_polyval.exe\
			$(EXE_BIN_DIR)/ex_dspl_unwrap.exe\
			
			
			
			
		
all:	dll\
		$(EXE_BINS)\




# DSPL.DLL compile	
dll:$(DLL_OBJS)
	$(CC) -o $(EXE_BIN_DIR)/dspl.dll -s -shared $(DLL_OBJS) -Wl,--subsystem,windows
	$(CC) -o $(VER_BIN_DIR)/dspl.dll -s -shared $(DLL_OBJS) -Wl,--subsystem,windows
	

	
$(DLL_OBJ_DIR)/%.o:$(DLL_SRC_DIR)/%.c
	$(CC) $(DLL_CFLAGS) -c $< -o $@

	
#$(DLL_OBJS) : $(INC_DIR)/dspl.h




	

$(EXE_BIN_DIR)/%.exe: $(EXE_OBJ_DIR)/%.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/dspl_load.o $< -o $@

$(EXE_OBJ_DIR)/%.o:$(EXE_SRC_DIR)/%.c
	$(CC) $(EXE_CFLAGS)  $< -o $@

$(OBJ_DIR)/dspl_load.o:$(INC_DIR)/dspl_load.c
	$(CC) $(EXE_CFLAGS)  $(INC_DIR)/dspl_load.c -o $(OBJ_DIR)/dspl_load.o



#$(EXE_BINS): $(INC_DIR)/dspl.h


clean:
	rm -f $(DLL_OBJ_DIR)/*.o
	rm -f $(EXE_OBJ_DIR)/*.o
	rm -f $(VER_OBJ_DIR)/*.o
	rm -f $(OBJ_DIR)/*.o