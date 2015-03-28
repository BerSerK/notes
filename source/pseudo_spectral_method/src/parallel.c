#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "mpi_util.h"
#define N (8)
#define dt (0.8/N)
#define T_max (3.16)

const double PI=acos(-1.0);
const double Runge_Kutta[4]={1, 0.5, 0.5, 1};

void init(fftw_complex * ,fftw_complex* , int, int);

void init_memory_and_plan(fftw_complex**, fftw_complex**, fftw_complex**,
						  fftw_complex**, fftw_complex**, int, int);

void free_memory_and_plan(fftw_complex**, fftw_complex**, fftw_complex**,
						  fftw_complex**, fftw_complex**）；
				

void evaluate_u_v(fftw_complex ** );

void normalize(fftw_complex *， int n_rank);

void de_alias(fftw_complex *);

void make_convalution( fftw_complex **, fftw_plan *, fftw_plan *);

void eval_right(fftw_complex **, fftw_complex **, fftw_complex **, int, fftw_complex*);

int shift(int);

void err_handler(MPI_Comm * comm, int * err_code, ...)
{
  int resultlen;
  char err_string[MPI_MAX_ERROR_STRING];
  MPI_Error_string(*err_code, err_string, &resultlen);
  printf("MPI exception caughted: error code %d\n", *err_code);
  printf("\terror: %s\n", err_string);
  MPI_Abort(*comm, *err_code);
}


int main(int argc, char * argv[])
{

  fftw_complex* temp;


  int i, j, rank, n_rank;
  MPI_File fh;
  MPI_Status status;
  MPI_Errhandler errhdl;
  int * send_buffer;
  int * recv_buffer;

  MPI_Init(&argc, &argv);
  MPI_Errhandler_create(&err_handler, &errhdl);
  MPI_Errhandler_set(MPI_COMM_WORLD, errhdl);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &n_rank);

  fftw_complex * working_pool[6];
  fftw_plan *forward, * backward;
  fftw_complex *rho, *w, *rhor[4], *wr[4];
  init_memory_and_plan( working_pool, rhor, wr, &rho, &w, forward, backward,rank, n_rank);
  init(rho, w, rank, n_rank);

  fftw_plan * p;
  p = (fftw_plan *) fftw_malloc(sizeof(fftw_plan) * N /n_rank);
  for(i = 0; i < N /n_rank; i ++){
	p[i] = fftw_plan_dft_1d( N,  rho + i * N, working_pool[0] + i * N, FFTW_BACKWARD, FFTW_MEASURE ); 
  }





  MPI_Finalize();
  return 0;
}

int shift(int a){
  if(2 * a > N) return a - N;
  if(2 * a == N) return 0;
  return a;
}
void init_memory_and_plan(fftw_complex** working_pool, 
						  fftw_complex** rhor,
						  fftw_complex** wr,
						  fftw_complex** rho,
						  fftw_complex** w,
						  fftw_plan* forward,
						  fftw_plan* backward,
						  int rank,
						  int n_rank){
  int i,j;
  *rho = ( fftw_complex* )fftw_malloc(sizeof(fftw_complex) * N * N/n_rank);
  *w = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N * N/n_rank );
  forward = (fftw_plan *) fftw_malloc(sizeof(fftw_plan) * N / n_rank * 6);
  backward = (fftw_plan *) fftw_malloc(sizeof(fftw_plan) * N / n_rank * 6);
  for( i = 0; i < 6; i++ )
	{
	  working_pool[i]=(fftw_complex * )fftw_malloc(sizeof(fftw_complex) * N * N/n_rank);
	  for( j = 0; j < N / n_rank; j ++){
		forward[i * N/n_rank +j] = fftw_plan_dft_1d( N, working_pool[i]+j*N, working_pool[i] + j * N, FFTW_FORWARD, FFTW_MEASURE);
		backward[i * N/n_rank +j] = fftw_plan_dft_1d( N, working_pool[i]+j*N, working_pool[i] + j * N, FFTW_BACKWARD, FFTW_MEASURE);
	  }
	}
  for( i = 0; i < 4; i++ )
	{
	  rhor[i] = (fftw_complex * )fftw_malloc(sizeof( fftw_complex ) * N * N /n_rank);
	  wr[i] = (fftw_complex * )fftw_malloc(sizeof( fftw_complex) * N * N/n_rank);
	}
}

void init(fftw_complex * rho,fftw_complex* w, int rank, int n_rank){
  int i,j;
  double x, y, c1, c2, rho1, rho2, PI2= PI * PI;

  fftw_plan *p;
  p = (fftw_plan *)fftw_malloc(sizeof(fftw_plan) * N / n_rank);
  for(i = 0; i < N/n_rank; i ++)
	{
	  p[i] = fftw_plan_dft_1d(N, rho + i * N, rho + i * N, FFTW_FORWARD, FFTW_MEASURE); 
	}
  int disp = rank * N/ n_rank;
  int index;
  for(i=0; i<N/n_rank;i++)
	{
	  x = 2 * PI * ( i + disp )/N;
	  for(j=0;j<N;j++)
		{
		  index = i * N + j;
		  w[ index ] = 0.0;
		  y = 2 * PI * ( j )/N;
		  c1 = PI2 - x * x  - (y - PI ) * ( y - PI);
		  c2 = 1.95 * 1.95 * PI2 - ( x - 2 * PI)*( x - 2 * PI);

		  if( c1 <= 0 || c2 <= 0){
			rho[ index ] = 0;
		  }else{
			rho1 = exp(1 - PI * PI / c1);
			rho2 = exp(1 - 1.95 * 1.95 * PI * PI / c2);
			rho[ index ] = 50 * rho1 * rho2 * ( 1 - rho1 );
		  }
		}
	}  
  for(i = 0; i < N / n_rank; i++)	{
	  fftw_execute(p[i]);
	  fftw_destroy_plan(p[i]);
	}
  normalize(rho, n_rank);
}

void normalize(fftw_complex * data, int n_rank){
  int i, j, index;
  double factor = N;

  for(i = 0 ; i < N /n_rank; i++)
	{
	  for(j = 0 ; j < N ; j++)
		{
		  index = i * N + j;
		  data[index]=data[index]/factor;
		}
	}
}

