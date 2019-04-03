# Author: Aidan Bush, David Dowie, Ben Ha
# Project: Konane
# Course: CMPT 355
# Date: Mar. 17, 19
# File: Makefile
# Description: It's a Makefile!
SHELL=/bin/bash
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -g -D_POSIX_C_SOURCE=200809L -D_DEFAULT_SOURCE # -O3
LDFLAGS= -lpthread

.PHONY: all clean

all: konane.exe

konane.exe: konane
	mv konane konane.exe

konane: konane.o state.o valid_moves.o input.o heuristic.o manager.o alphabeta.o

konane.o: konane.c state.h valid_moves.h input.h heuristic.h manager.h alphabeta.h

state.o: state.c state.h heuristic.h manager.h

alphabeta.o: alphabeta.c alphabeta.h heuristic.h state.h valid_moves.h

valid_moves.o: valid_moves.c valid_moves.h state.h manager.h heuristic.h

heuristic.o: heuristic.c heuristic.h state.h

input.o: input.c input.h state.h

manager.o: manager.c manager.h heuristic.h state.h

hashtable.o: hashtable.c hashtable.h

valid_moves: valid_moves.o state.o manager.o heuristic.o

clean:
	$(RM) konane.exe *.o
