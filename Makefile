export BIN_DIR = $(PWD)/bin
export OBJ_DIR = $(PWD)/obj

export ECHO = echo
export CC = g++
export C_FLAGS = -std=c++11 -g
export C_LIBS = `pkg-config --cflags --libs jack` -lncurses

default: beat_loop

beat_loop:
	cd src && make beat_loop

clean:
	rm $(OBJ_DIR)/* $(BIN_DIR)/*
