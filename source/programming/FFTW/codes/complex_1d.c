#include <complex.h>
#include <fftw3.h>
#define N 1000

int main()
{
  complex d;
  d.r=1.0;
  d.i=2.0;

  fftw_complex *in, *out;
  fftw_plan p;
  
  in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
  out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
  p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  int i;
  for(i = 0; i < N; i++)
	in[i]=d;

  fftw_execute(p); /* repeat as needed */
  
  fftw_destroy_plan(p);
  fftw_free(in); fftw_free(out);
  return 0;
}
