SRC = $(wildcard *.c*)
OBJ = $(SRC:.c*=.o)

SRC_C = $(wildcard *.c)
OBJ_C = $(SRC_C:.c=.o)

SRC_CPP = $(wildcard *.cpp)

CPP = g++
CC = gcc

OBJDIR = .obj/
INCLUDE = 
LIB_PATH = 

LDFLAGS =

CPPFLAGS = -Wall

CFLAGS = -c -o

SUFFIX = 

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CPPFLAGS+= -g
 	 SUFFIX = _g
endif


BIN_DIR = ../bin

$(BIN_DIR)/server$(SUFFIX): $(OBJ)
	@mkdir -p .obj
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_C) $(SRC_C)
	$(CPP) $(CPPFLAGS) -I$(INCLUDE) -L$(LIB_PATH) -o $@ $(SRC_CPP) $(OBJDIR)$(OBJ_C) $(LDFLAGS)

.PHONY: clean
clean:
	rm .obj/*.o
	rm $(BIN_DIR)/server*

