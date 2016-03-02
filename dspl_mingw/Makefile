CC      = gcc
INC_DIR = src
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

CFLAGS = -c -Wall -I $(INC_DIR) -std=c89
	

OBJS=$(OBJ_DIR)/ex_dspl.o\
		
all:	ex_dspl\
				

ex_dspl:  $(OBJ_DIR)/ex_dspl.o $(OBJ_DIR)/dspl_load.o
	$(CC) $(OBJ_DIR)/ex_dspl.o $(OBJ_DIR)/dspl_load.o -o $(BIN_DIR)/ex_dspl


$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@



$(OBJS): $(INC_DIR)/dspl.h

clean: 
	rm $(OBJ_DIR)/*.o