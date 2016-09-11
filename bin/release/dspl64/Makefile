CC      = gcc
INC_DIR = src
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

CFLAGS  = -c -Wall -O3 -I$(INC_DIR)


OBJS =  $(OBJ_DIR)/main.o\
		$(OBJ_DIR)/dspl.o\
		
all:	$(BIN_DIR)/main.exe

$(BIN_DIR)/main.exe: $(OBJS)
	$(CC) $(OBJS)  -o $(BIN_DIR)/main.exe

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS)  $< -o $@

                                  
$(OBJS):	 $(INC_DIR)/dspl.h


clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*.exe
	
