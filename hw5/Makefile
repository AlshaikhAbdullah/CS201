# Student's Makefile for the CS201 Asignment 5
CC = gcc
CFLAGS = -Wall -O2 -m32
LIBS = -lm

OBJS = driver.o kernels.o fcyc.o clock.o

all: driver

driver: $(OBJS) fcyc.h clock.h defs.h
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o driver

clean: 
	-rm -f driver core *~ kernels.o


