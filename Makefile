export BIN_DIR = $(PWD)/bin
export OBJ_DIR = $(PWD)/obj

export ECHO = echo
export CC = g++
export C_FLAGS =
export C_LIBS = `pkg-config --cflags --libs jack`

default: beat_loop

beat_loop:
	cd src && make beat_loop
