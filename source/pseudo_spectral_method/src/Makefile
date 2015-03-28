CC=gcc
MPICC=/usr/local/mpich2-1.4pl/bin/mpicc
CFLAGS=-lfftw3 -lm -g
MPICFLAGS=-lfftw3 -lm -g -c
OBJS=serial.o serial_by_r2c.o
MPIOBJS=mpi_util.mpi parallel.mpi mpifile.mpi 

all: $(OBJS) $(MPIOBJS) parallel.o

%.o: %.c
	$(CC) $< -o $@ $(CFLAGS) 

%.mpi: %.c
	$(MPICC) $< -o $@ $(MPICFLAGS) 

parallel.o: parallel.mpi mpi_util.mpi
	$(MPICC) parallel.mpi mpi_util.mpi -o $@ $(CFLAGS) 

clean:
	rm -rf *.o 
	rm -rf *.mpi 
