CC=mpicc

CFLAGS=-g -O2

all : seq mpibasic

clean:
	rm -f *.o seq mpibasic
