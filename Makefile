CC      = gcc
INC_DIR = include
SRC_DIR = src
EX_DIR  = examples
BIN_DIR = bin
OBJ_DIR = obj

DLL_CFLAGS = -c -Wall -D DLL_EXPORT -I $(INC_DIR) -std=c89
EX_CFLAGS = -c -Wall -I $(INC_DIR) -std=c89



DLL_OBJS=$(OBJ_DIR)/dspl.o\
		$(OBJ_DIR)/dspl_compos.o \
		$(OBJ_DIR)/dspl_conv.o \
		$(OBJ_DIR)/dspl_dft.o \
		$(OBJ_DIR)/dspl_goertzel.o \
		$(OBJ_DIR)/dspl_fft.o \
		$(OBJ_DIR)/dspl_filter_ap.o \
		$(OBJ_DIR)/dspl_filter_iir.o \
		$(OBJ_DIR)/dspl_filter_transform.o \
		$(OBJ_DIR)/dspl_freqs.o \
		$(OBJ_DIR)/dspl_freqz.o \
		$(OBJ_DIR)/dspl_inout.o \
		$(OBJ_DIR)/dspl_linspace.o\
		$(OBJ_DIR)/dspl_logspace.o\
        $(OBJ_DIR)/dspl_math_basic.o \
        $(OBJ_DIR)/dspl_math_hyperbolic.o \
		$(OBJ_DIR)/dspl_polyval.o\
		$(OBJ_DIR)/dspl_unwrap.o\
		$(OBJ_DIR)/dspl_win.o\

		

EX_OBJS=$(OBJ_DIR)/ex_dspl.o\
		$(OBJ_DIR)/ex_dspl_butter_ap.o\
		$(OBJ_DIR)/ex_dspl_cheby1_ap.o\
		$(OBJ_DIR)/ex_dspl_cheby2_ap.o\
		$(OBJ_DIR)/ex_dspl_compos.o\
		$(OBJ_DIR)/ex_dspl_conv.o\
		$(OBJ_DIR)/ex_dspl_dft.o\
		$(OBJ_DIR)/ex_dspl_goertzel.o\
		$(OBJ_DIR)/ex_dspl_fft.o\
		$(OBJ_DIR)/ex_dspl_linspace.o\
		$(OBJ_DIR)/ex_dspl_polyval.o\
		$(OBJ_DIR)/ex_dspl_unwrap.o\
		
all:	dll\
		ex_dspl\
		ex_dspl_butter_ap\
		ex_dspl_cheby1_ap\
		ex_dspl_cheby2_ap\
		ex_dspl_compos\
		ex_dspl_conv\
		ex_dspl_dft\
		ex_dspl_goertzel\
		ex_dspl_fft\
		ex_dspl_linspace\
		ex_dspl_polyval\
		ex_dspl_unwrap\
		
		
		

dll: $(DLL_OBJS)
	$(CC) -o $(BIN_DIR)/dspl.dll -s -shared $(DLL_OBJS) -Wl,--subsystem,windows

ex_dspl:  $(OBJ_DIR)/ex_dspl.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl


ex_dspl_butter_ap: $(OBJ_DIR)/ex_dspl_butter_ap.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_butter_ap.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_butter_ap
	

ex_dspl_cheby1_ap: $(OBJ_DIR)/ex_dspl_cheby1_ap.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_cheby1_ap.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_cheby1_ap
	

ex_dspl_cheby2_ap: $(OBJ_DIR)/ex_dspl_cheby2_ap.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_cheby2_ap.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_cheby2_ap


ex_dspl_compos:  $(OBJ_DIR)/ex_dspl_compos.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_compos.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_compos
      	

ex_dspl_conv:  $(OBJ_DIR)/ex_dspl_conv.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_conv.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_conv

		
ex_dspl_dft: $(OBJ_DIR)/ex_dspl_dft.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_dft.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_dft


ex_dspl_goertzel: $(OBJ_DIR)/ex_dspl_goertzel.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_goertzel.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_goertzel


ex_dspl_fft: $(OBJ_DIR)/ex_dspl_fft.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_fft.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_fft


ex_dspl_linspace: $(OBJ_DIR)/ex_dspl_linspace.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_linspace.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_linspace

	

ex_dspl_polyval: $(OBJ_DIR)/ex_dspl_polyval.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_polyval.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_polyval

ex_dspl_unwrap: $(OBJ_DIR)/ex_dspl_unwrap.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_unwrap.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_unwrap

	
	

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(DLL_CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o:$(EX_DIR)/%.c
	$(CC) $(EX_CFLAGS) -c $< -o $@


$(DLL_OBJS): $(INC_DIR)/dspl.h

$(EX_OBJS): $(INC_DIR)/dspl.h

