#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include <fftw3.h>

#define N 10
#define index (i * 2 * (N/2+1) + j)

int output(fftw_complex * data, char * filename){
  FILE *fp;
  int i,j;
  //sprintf(filename+7,"%d",x);
  fp = fopen(filename,"w");
  for( i = 0; i < N; i ++)
	{
	  for( j = 0; j < N; j ++){
		fprintf(fp, "%.8lf\t", creal(data[index]));
	  }
	  fprintf(fp, "\n");
	}  
}

void setmem(double**in, fftw_complex **out){
  *in = (double*) fftw_malloc(sizeof(double) * N * 2 * (N /2 + 1 ));
   *out = (fftw_complex *)(*in);
}

int main(){
  double *in;
  fftw_complex *out[2];
  fftw_plan f,b;
  setmem(&in,&out);
  f = fftw_plan_dft_r2c_2d( N, N, in, out,  FFTW_ESTIMATE);
  b = fftw_plan_dft_c2r_2d( N, N, out, in,  FFTW_ESTIMATE);
  int i,j;
  for(i =0; i < N; i++)
	{
	  for(j = 0; j< N; j++)
		{
		  in[index]=i*j;
		  printf("%lf\t", in[index]);
		}
	  printf("\n");
	}
	  printf("\n");
  
  fftw_execute(f); /* repeat as needed */
  fftw_execute(b); /* repeat as needed */

  for(i =0; i < N; i++)
	{
	  for(j = 0; j< N; j++)
		{
		  printf("%lf\t", in[index]);
		}
	  printf("\n");
	}


  fftw_destroy_plan(f);
  fftw_destroy_plan(b);
  fftw_free(in);
}
