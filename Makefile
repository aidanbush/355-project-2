# Author: Aidan Bush, David Dowie, Ben Ha
# Project: Konane
# Course: CMPT 355
# Date: Mar. 17, 19
# File: Makefile
# Description: It's a Makefile!
SHELL=/bin/bash
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -g -D_TEST_INPUT # -O3

.PHONY: all clean

all: konane.exe

konane.exe: konane
	mv konane konane.exe

konane: konane.o model.o

konane.o: konane.c model.h

model.o: model.c model.h

clean:
	$(RM) konane.exe *.o
