# Author: Aidan Bush, David Dowie, Ben Ha
# Project: Konane
# Course: CMPT 355
# Date: Mar. 17, 19
# File: Makefile
# Description: It's a Makefile!
SHELL=/bin/bash
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -g # -O3

.PHONY: all clean

all: konane.exe

konane.exe: konane
	mv konane konane.exe

konane: konane.o state.o valid_moves.o input.o

konane.o: konane.c state.h valid_moves.h input.h

state.o: state.c state.h

minmax.o: minmax.c minmax.h state.h

valid_moves.o: valid_moves.c valid_moves.h state.h

heuristic.o: heuristic.c heuristic.h state.h

input.o: input.c input.h state.h

clean:
	$(RM) konane.exe *.o
