#include <stdio.h>
#include <complex.h>

#include <fftw3.h>
#include <mpi.h>

#define check printf("Here is FILE %s LINE %d\n",__FILE__,__LINE__);

int output(fftw_complex *buf, int size,char* filename,
		   int comm_rank);

int transpose(fftw_complex *buf, int N, int rank_size);


