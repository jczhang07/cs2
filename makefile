CC=mpicc

CFLAGS=-g -O2

all : seq mpibasic

seqtest : seq.o

mpibasic : mpibasic.o

clean:
	rm -f *.o seq mpibasic

