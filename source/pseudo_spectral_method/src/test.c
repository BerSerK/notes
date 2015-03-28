#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>
#define N 512

const double PI=4*atan(1.0);
const double Pi=acos(-1.0);
struct variable{
  int u;
};

void print(struct variable *a){
  printf("%d\n",a->u);
  a->u=20;
}

int shift(int a){
  if(2 * a > N) return a - N;
  return a;
}


int main()
{
  struct variable a;
  fftw_complex y,z;
  int j=400;
  y=-1.1 - 2 * PI * I * shift( j )/ N;
  printf("%le+%le i\n",creal(y),cimag(y));
  z=1/y;
  
  for(j = 0; j < 100; j++){
	z=1/z;
  }

  printf("%le+%le i\n",creal(z),cimag(z));
  printf("%le+%le i\n",creal(z * y),cimag(z * y));
  printf("%d\n",abs(y));
  printf("%lf\n",fabs(y));
  a.u=10;
  print(&a);
  printf("%d\n",a.u);
  fftw_complex c1,c2,c3;
  c1=I;
  c2=1.0+2*I;
  c3=c1*c2;
  printf("%lf+%lf i\n",creal(c3),cimag(c3));
  printf("%1.50lf\n",PI);
  printf("%1.50lf\n",Pi*1/10);
  printf("%1.50lf\n",exp(1.0));
  int x=rand();
  char filename[50];
  sprintf(filename,"helloword%d",x);
  printf("%s\n",filename);
  return 0;
}
