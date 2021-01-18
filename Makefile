# -*- Makefile -*-
CC=gcc
AR=ar
FLAGS= -g -Wall

all: frequency

frequency: main.o 
	$(CC) $(FLAGS) -o frequency main.o 

main: main.c 
	$(CC) $(FLAGS) -c main.c

.PHONY: all clean

clean:
	rm -f *.o frequency
