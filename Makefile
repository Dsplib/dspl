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


DLL_OBJS=	$(DLL_OBJ_DIR)/dspl_compos.o\
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
			$(DLL_OBJ_DIR)/dspl_main.o\
			$(DLL_OBJ_DIR)/dspl_math_basic.o\
			$(DLL_OBJ_DIR)/dspl_math_hyperbolic.o\
			$(DLL_OBJ_DIR)/dspl_polyval.o\
			$(DLL_OBJ_DIR)/dspl_unwrap.o\
			$(DLL_OBJ_DIR)/dspl_win.o\

			
RES_OBJ = $(DLL_OBJ_DIR)/resource.o			

			
			



EXE_FILES=	$(EXE_BIN_DIR)/ex_dspl.exe\
			$(EXE_BIN_DIR)/ex_dspl_butter_ap.exe\
			$(EXE_BIN_DIR)/ex_dspl_cheby1_ap.exe\
			$(EXE_BIN_DIR)/ex_dspl_cheby2_ap.exe\
			$(EXE_BIN_DIR)/ex_dspl_compos.exe\
			$(EXE_BIN_DIR)/ex_dspl_conv.exe\
			$(EXE_BIN_DIR)/ex_dspl_dft.exe\
			$(EXE_BIN_DIR)/ex_dspl_goertzel.exe\
			$(EXE_BIN_DIR)/ex_dspl_linspace.exe\
			$(EXE_BIN_DIR)/ex_dspl_polyval.exe\
			$(EXE_BIN_DIR)/ex_dspl_unwrap.exe\
			

			
VER_FILES = $(VER_BIN_DIR)/ver_dspl_fft.exe\
  

COMMON_OBJS = $(OBJ_DIR)/dspl.o\
			
			
		
all:	$(EXE_BIN_DIR)/dspl.dll\
		$(VER_BIN_DIR)/dspl.dll\
		$(EXE_FILES)\
		$(VER_FILES)\



# DSPL.DLL compile	
$(EXE_BIN_DIR)/dspl.dll:$(DLL_OBJS) $(RES_OBJ)
	$(CC) -o $(EXE_BIN_DIR)/dspl.dll -s -shared $(DLL_OBJS) $(RES_OBJ) -Wl,--subsystem,windows

$(VER_BIN_DIR)/dspl.dll:$(DLL_OBJS) $(RES_OBJ)
	$(CC) -o $(VER_BIN_DIR)/dspl.dll -s -shared $(DLL_OBJS) $(RES_OBJ) -Wl,--subsystem,windows



$(RES_OBJ):$(DLL_SRC_DIR)/resource.rc
	windres -i $(DLL_SRC_DIR)/resource.rc -o $(RES_OBJ)

	
$(DLL_OBJ_DIR)/%.o:$(DLL_SRC_DIR)/%.c
	$(CC) $(DLL_CFLAGS) -c $< -o $@

	


$(EXE_BIN_DIR)/%.exe: $(EXE_OBJ_DIR)/%.o  $(COMMON_OBJS)
	$(CC) $(OBJ_DIR)/dspl.o $< -o $@

$(EXE_OBJ_DIR)/%.o:$(EXE_SRC_DIR)/%.c
	$(CC) $(EXE_CFLAGS)  $< -o $@



$(VER_BIN_DIR)/%.exe: $(VER_OBJ_DIR)/%.o  $(COMMON_OBJS)
	$(CC) $(OBJ_DIR)/dspl.o $< -o $@

$(VER_OBJ_DIR)/%.o:$(VER_SRC_DIR)/%.c
	$(CC) $(EXE_CFLAGS)  $< -o $@





$(OBJ_DIR)/%.o:$(INC_DIR)/%.c
	$(CC) $(EXE_CFLAGS)  -c $< -o $@



$(DLL_OBJS):	 $(INC_DIR)/dspl.h  

$(EXE_OBJS):	 $(INC_DIR)/dspl.h

$(EXE_FILES):	 $(INC_DIR)/dspl.h

$(COMMON_OBJS):	 $(INC_DIR)/dspl.h


clean:
	rm -f $(DLL_OBJ_DIR)/*.o
	rm -f $(EXE_OBJ_DIR)/*.o
	rm -f $(VER_OBJ_DIR)/*.o
	rm -f $(OBJ_DIR)/*.o
	rm -f $(EXE_BIN_DIR)/*.exe
	rm -f $(EXE_BIN_DIR)/*.dll
	rm -f $(VER_BIN_DIR)/*.exe
	rm -f $(VER_BIN_DIR)/*.dll
