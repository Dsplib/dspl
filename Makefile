CC      = gcc
INC_DIR = include
SRC_DIR = src
EX_DIR  = examples
BIN_DIR = bin
OBJ_DIR = obj

DLL_CFLAGS = -c -Wall -D DLL_EXPORT -I $(INC_DIR) -std=c89
EX_CFLAGS = -c -Wall -I $(INC_DIR) -std=c89



DLL_OBJS=$(OBJ_DIR)/dspl_butter_norm.o \
		$(OBJ_DIR)/dspl_conv.o \
		$(OBJ_DIR)/dspl_dft.o \
		$(OBJ_DIR)/dspl_fft.o \
		$(OBJ_DIR)/dspl_filter_iir.o \
		$(OBJ_DIR)/dspl_freqs.o \
		$(OBJ_DIR)/dspl_freqz.o \
		$(OBJ_DIR)/dspl_inout.o \
        $(OBJ_DIR)/dspl_math_hyperbolic.o \
		$(OBJ_DIR)/dspl_polyval.o\
		$(OBJ_DIR)/dspl_win.o\

		

EX_OBJS=$(OBJ_DIR)/ex_dspl.o\
		$(OBJ_DIR)/ex_dspl_conv.o\
		$(OBJ_DIR)/ex_dspl_dft.o\
		$(OBJ_DIR)/ex_dspl_fft.o\
		$(OBJ_DIR)/ex_dspl_polyval.o\

all:	dll\
		ex_dspl\
		ex_dspl_conv\
		ex_dspl_dft\
		ex_dspl_fft\
		ex_dspl_polyval\

dll: $(DLL_OBJS)
	$(CC) -o $(BIN_DIR)/dspl.dll -s -shared $(DLL_OBJS) -Wl,--subsystem,windows

ex_dspl:  $(OBJ_DIR)/ex_dspl.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl

	
ex_dspl_conv:  $(OBJ_DIR)/ex_dspl_conv.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_conv.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_conv

		
ex_dspl_dft: $(OBJ_DIR)/ex_dspl_dft.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_dft.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_dft


ex_dspl_fft: $(OBJ_DIR)/ex_dspl_fft.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_fft.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_fft


ex_dspl_polyval: $(OBJ_DIR)/ex_dspl_polyval.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl_polyval.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl_polyval



$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(DLL_CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o:$(EX_DIR)/%.c
	$(CC) $(EX_CFLAGS) -c $< -o $@


$(DLL_OBJS): $(INC_DIR)/dspl.h

$(EX_OBJS): $(INC_DIR)/dspl.h

