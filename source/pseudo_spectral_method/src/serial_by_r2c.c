/**
 * @file   serial.c
 * @author Alex <yeshiwei.math@gmail.com>
 * @date   Wed Dec 14 23:42:51 2011
 * 
 * @brief  用伪谱方法求解Boussinesq方程的串行实现。求解区域为：
 *         \f[
 *            [0,2\pi]\times [0,2\pi]
 *         \f]
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include <fftw3.h>
/// 网格数
#define N 512
/// 数组索引
#define index (i * 2 * (N/2+1)+j)
#define index_f (i * (N/2+1)+j)
/// 时间步长
#define dt (1.0/N)
/// 精度
#define eps 1e-8
/// 最大时间
#define T_max 3.16
/// \f$\pi\f$
const double PI=acos(-1.0);

void init(fftw_complex * ,fftw_complex* );
void init_memory_and_plan(fftw_complex**, double **, fftw_complex**, fftw_complex**,
						  fftw_complex**, fftw_complex**,
						  fftw_plan *, fftw_plan *);

void output(double *, char *);
void evaluate_u_v(fftw_complex ** );
void normalize(double *);
void de_alias(fftw_complex *);
void make_convalution( fftw_complex **, double **, fftw_plan *, fftw_plan *);
void eval_right(fftw_complex **, fftw_complex **, fftw_complex **, int, fftw_complex*);
int shift(int);


int main(){
  
  fftw_complex * working_pool[6];
  double * basic_space_pool[6];
  fftw_plan forward[6], backward[6];
  fftw_complex *rho, *w, *rhor[4], *wr[4];
  int i,j;

  init_memory_and_plan( working_pool, basic_space_pool, rhor, wr, &rho, &w, forward, backward);
  init(rho,w);

  //fftw_execute(p);
  //output_real(working_pool[0],"result/rho.txt");
  //output_real(rho,"result/rhot.txt");

  double T = 0.0 ;

  double x, y;
  char filename[50];
  int num = 0;

  sprintf(filename,"result/rho.txt");
  memcpy(working_pool[0], rho, 2 * ( N/2 + 1) * N * sizeof(double));
  fftw_execute(backward[0]);
  normalize(basic_space_pool[0]);
  //  output(basic_space_pool[0],filename);

  while(T < T_max){

	//if(num%10==0){
	sprintf(filename,"result/%06d.txt", num);
	memcpy(working_pool[0], rho, 2 * ( N/2 + 1) * N * sizeof(double));
	fftw_execute(backward[0]);
	normalize(basic_space_pool[0]);
	output(basic_space_pool[0],filename);
	//}

	num++;
	T = T + dt;

	///Now start to evaluate r1 for Runge-Kutta
	for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N/2+1; j ++)
		  {
			working_pool[0][index_f] = rho[index_f];
			working_pool[1][index_f] = w[index_f];
		  }
	  }

	evaluate_u_v(working_pool);	

	fftw_execute(backward[0]);
	normalize(basic_space_pool[0]);
	output(basic_space_pool[0],"result/rho.txt");
	fftw_execute(forward[0]);

	fftw_execute(backward[4]);
	normalize(basic_space_pool[4]);
	output(basic_space_pool[4],"result/u.txt");
	fftw_execute(forward[4]);

	
	make_convalution(working_pool, basic_space_pool, forward, backward);


	eval_right(working_pool, rhor, wr, 0, rho);
	
	/*	if(num%10==0){
	sprintf(filename,"result/rhor%06d.txt", num);
	fftw_execute(p1);
	normalize(working_pool[0]);
	output_real(working_pool[0],filename);
	}*/

	///Now start to evaluate r2 for Runge-Kutta
	for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N; j ++)
		  {
			working_pool[0][index_f] = rho[index_f]+rhor[0][index_f]/2;
			working_pool[1][index_f] = w[index_f]+wr[0][index_f]/2;
		  }
	  }	

	evaluate_u_v(working_pool);	
	make_convalution(working_pool, basic_space_pool, forward, backward);
	eval_right(working_pool, rhor, wr, 1, rho);

	///Now starts to evaluate r3 for Runge-Kutta
	for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N/2+1; j ++)
		  {
			working_pool[0][index_f] = rho[index_f]+rhor[1][index_f]/2;
			working_pool[1][index_f] = w[index_f]+wr[1][index_f]/2;
		  }
	  }	
	evaluate_u_v(working_pool);	
	make_convalution(working_pool, basic_space_pool, forward,backward);
	eval_right(working_pool, rhor, wr, 2, rho);

	///Now starts to evaluate r4 for Runge-Kutta
	for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N/2 + 1; j ++)
		  {
			working_pool[0][index_f] = rho[index_f]+rhor[2][index_f];
			working_pool[1][index_f] = w[index_f]+wr[2][index_f];
		  }
	  }	
	evaluate_u_v(working_pool);	
	make_convalution(working_pool, basic_space_pool, forward, backward);
	eval_right(working_pool, rhor, wr, 3, rho);
	
	///Now starts evaluate next step rho and w;
	  for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N; j ++)
		  {
			//rho[index_f] = rho[ index_f ] +  rhor[0][index_f];
			//w[index_f] = w[ index_f ] + wr[0][index_f];
			rho[index_f] = rho[ index_f ] + 
			  ( rhor[0][index_f] + 2 * rhor[1][index_f] + 2 * rhor[2][index_f] + rhor[3][index_f])/6;
			w[index_f] = w[ index_f ] + 
			  ( wr[0][index_f] + 2 * wr[1][index_f] + 2 * wr[2][index_f] + wr[3][index_f])/6;
		  }
	  }
  }
  
  return 0;
}


/** 
 *  初始化 \f$\hat{\rho}\f$ 和 \f$\hat{\omega}\f$ 
 * 
 * @param rho 
 * @param w 
 */
void init(fftw_complex * rho,fftw_complex* w){
  int i,j;
  double x, y, c1, c2, rho1, rho2, PI2=PI*PI;
  double * basic_rho;
  basic_rho= (double *) rho;
  for(i=0;i<N;i++)
	{
	  for(j=0;j<N/2+1;j++)
		{
		  w[ index_f ] = 0;
		}
	}

  for(i=0;i<N;i++)
	{
	  x=2 * PI * i / N;
	  for(j=0;j<N;j++)
		{

		  y = 2 * PI * j / N;
		  
		  c1 = PI2 - x * x  - (y - PI ) * ( y - PI);
		  c2 = 1.95 * 1.95 * PI2 - ( x - 2 * PI)*( x - 2 * PI);

		  if( c1 <= 0 || c2 <= 0){
			basic_rho[ index ] = 0;
		  }else{
			rho1 = exp(1 - PI * PI / c1);
			rho2 = exp(1 - 1.95 * 1.95 * PI * PI / c2);
			basic_rho[ index ] = 50 * rho1 * rho2 * ( 1 - rho1 );
		  }
		}
	}  
  fftw_plan p;
  //output_real(rho,"result/rho1.txt");
  p = fftw_plan_dft_r2c_2d(N, N, basic_rho, rho, FFTW_MEASURE); 
  fftw_execute(p);
  fftw_destroy_plan(p);
  //output_real(rho,"result/rho2.txt");
}

/** 
 * 分配内存, 初始化working_pool 的fftw plan
 * 
 * @param working_pool 用于临时存储\f$\rho, \omega, u, v \f$
 * @param rhor Runge-Kutta 法中关于 \f$\rho\f$的 右端项
 * @param wr Runge-Kutta 法中关于 \f$\omega\f$的 右端项
 * @param rho \f$\rho\f$
 * @param w \f$\omega\f$
 * @param forward forword fftw plan for working_pool
 * @param backward backward fftw plan for working_pool
 */
void init_memory_and_plan(fftw_complex** working_pool, 
						  double** basic_space_pool,
						  fftw_complex** rhor,
						  fftw_complex** wr,
						  fftw_complex** rho,
						  fftw_complex** w,
						  fftw_plan *forward, 
						  fftw_plan *backward){
  int i;
  *rho = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (N / 2 + 1 ) * N);
  *w = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (N / 2 + 1 ) * N);
  for( i = 0; i < 6; i++ )
	{
	  working_pool[i]=(fftw_complex*)fftw_malloc(sizeof(double) * 2 * (N / 2+1 ) * N);
	  basic_space_pool[i]=(double *)working_pool[i];
	  forward[i]=fftw_plan_dft_r2c_2d( N, N, basic_space_pool[i], 
									   working_pool[i], FFTW_MEASURE); 

	  backward[i]=fftw_plan_dft_c2r_2d( N, N,  working_pool[i], 
									basic_space_pool[i], FFTW_MEASURE); 
	}
  for( i = 0; i < 4; i++ )
	{
	  rhor[i] = (fftw_complex*)fftw_malloc(sizeof(double) * 2 * (N / 2 + 1) * N);
	  wr[i] = (fftw_complex*)fftw_malloc(sizeof(double) * 2 * (N / 2 + 1) * N);
	}
}

/** 
 * 输出一个complex数组的实部
 * 
 * @param data 数据指针
 * @param filename 文件名
 */
void output(double *data, char*filename){
  printf("writing %s \n",filename);
  FILE *fp;
  fp=fopen(filename,"w");
  int i,j;
  for(i=0;i<N;i++)
	{
	  for(j=0;j<N;j++)
		{
		  fprintf(fp, "%le\t", data[index]);
		}
	  fprintf(fp, "\n");
	}
  fclose(fp);
}

/** 
 * 用fftw做完逆变换之后的归一化。
 * 
 * @param data 
 */
void normalize(double * data){
  int i, j;
  double factor = N*N;
  for(i = 0 ; i < N ; i++)
	{
	  for(j = 0 ; j < N ; j++)
		{
		  data[index]=data[index]/factor;
		}
	}
}

/** 
 * 去除折叠(alias)
 * 
 * @param data fourier 空间的的数组
 */
void de_alias( fftw_complex * data){
  int i,j;
  double a, b;
  for( i = 0; i < N; i ++)
	  {
		a = (double) i/N;
		for( j = 0; j < N/2+1; j ++)
		  {
			b = (double) j/N;
			if( (a >= 1./3 && a <= 2./ 3 )||(b >= 1./3 && b <= 2./ 3 ))
			  {
				data[index_f] = 0.0;
			  }
		  }
	  }
}

/** 
 * 计算右端函数的卷积部分。
 * \f$\hat{u}_{jk} \otimes 2 \pi i \frac{j}{N} \hat{\rho}_{jk}\f$
 * \f$\hat{v}_{jk} \otimes 2 \pi i \frac{k}{N} \hat{\rho}_{jk}\f$
 * \f$\hat{u}_{jk} \otimes 2 \pi i \frac{j}{N} \hat{w}_{jk} \f$
 * \f$\hat{v}_{jk} \otimes 2 \pi i \frac{k}{N} \hat{w}_{jk} \f$
 *
 * @param wp working_pool 存储 \f$\rho, \omega, u, v\f$
 * @param forward forward fftw plans for wp
 * @param backward backward fftw plans for wp
 */
void make_convalution( fftw_complex ** wp,
					   double **bp,
					   fftw_plan *forward,
					   fftw_plan *backward){
  fftw_complex RHO, W, U, V;
  int i,j;
  double x,y;
  for( i = 0; i < N; i++)
	{
	  x= - 2 * PI * I * shift( i )/N;
	  for( j = 0; j < N/2 +1; j++)
		{
		  y= - 2 * PI * I * shift( j )/N;
		  RHO =  wp[0][index];
		  W = wp[1][index];
		  wp[0][index]= x * RHO;
		  wp[1][index]= y * RHO;
		  wp[2][index]= x * W;
		  wp[3][index]= y * W;
		}
	}

  for( i = 0 ; i < 6; i++)
	{
	  // de_alias(wp[i]);
	  fftw_execute(backward[i]);
	  normalize(bp[i]);
	}

  for( i = 0; i < N; i++)
	{
	  for( j = 0; j < N; j++)
		{
		  U = bp[4][index];
		  V = bp[5][index];
		  
		  bp[0][index] = bp[0][ index ] * U;
		  bp[1][index] = bp[1][ index ] * V;
		  bp[2][index] = bp[2][ index ] * U;
		  bp[3][index] = bp[3][ index ] * V;
		}
	}
  for(i = 0; i < 4; i ++ )
	{
	  fftw_execute(forward[i]);
	}
}

/** 
 * 利用已经计算出来的卷积计算右端项。
 * \f[
 *   \frac{\partial \hat{\rho}_{jk}}{\partial t} = \hat{u}_{jk}
 *   \otimes 2 \pi i \frac{j}{N} \hat{\rho}_{jk} + \hat{v}_{jk}
 *   \otimes 2 \pi i \frac{k}{N} \hat{\rho}_{jk}
 * \f]
 * \f[
 *   \frac{\partial \hat{w}_{jk}}{\partial t} = \hat{u}_{jk}
 *   \otimes 2 \pi i \frac{j}{N} \hat{w}_{jk} + \hat{v}_{jk}
 *   \otimes 2 \pi i \frac{k}{N} \hat{w}_{jk} + 2 \pi i \frac{j}{N}
 *   \hat{\rho}_{jk}
 * \f]
 * 
 * @param wp 存储已经计算出来的卷积
 * @param rhor Runge-Kutta 方法中的相对于\f$\rho\f$的右端项
 * @param wr Runge-Kutta 方法中的相对于\f$\omega\f$的右端项
 * @param n 表示Runge-Kutta 方法中的第几个右端像。
 * @param rho 这一步的\f$\rho\f$
 */
void eval_right(fftw_complex **wp, fftw_complex **rhor, 
				fftw_complex **wr, int n, fftw_complex*rho){
  int i, j;
  fftw_complex rhou, rhov, wu, wv, RHO, x, y;
  for( i = 0; i < N; i ++)
	  {
		x = - 2 * PI * I *i/N;
		for( j = 0; j < N/2 +1; j ++)
		  {
			//y = j/N;
			rhou = wp[0][index_f];
			rhov = wp[1][index_f];
			wu = wp[2][index_f];
			wv = wp[3][index_f];
			switch(n){
			case 0: RHO = rho[index_f];break;
			case 1: RHO = rho[index_f] + rhor[0][index_f]/2;break;
			case 2: RHO = rho[index_f] + rhor[1][index_f]/2;break;
			case 3: RHO = rho[index_f] + rhor[2][index_f];break;
			}
			rhor[n][index_f] = dt *(- rhou - rhov);
			wr[n][index_f] = dt *(- wu - wv -  y * RHO);
		  }
	  }
  
}

/** 
 * 通过\f$\omega\f$计算 \f$u,v\f$
 * 
 * @param wp wp[1] 存储了\f$\omega\f$,且\f$u,v\f$ 将存储与wp[4], wp[5]
 */
void evaluate_u_v(fftw_complex ** wp)
{
  fftw_complex phi, RHO, W, U, V;
  double x, y;
  int i, j, a, b;
	for( i = 0; i < N; i++)
	  {
		a = shift( i );
		x =2 * PI * I * a / N;
		for( j = 0; j < N/2 + 1; j++)
		  {
			b = shift( j );
			y = 2 * PI * I * b / N;
			W = wp[1][ index_f ];
			if (a == 0 && b == 0){
			  wp[1][ index_f ] = 0;
			  wp[4][ index_f ] = 0;
			  wp[5][ index_f ] = 0;
			}else{
			  phi = - W / (x * x + y * y);
			  wp[4][ index_f ] = - y * phi;
			  wp[5][ index_f ] = x * phi;
			}
		  }
	  }
}


int shift(int i){
  if(2 * i > N) return i - N;
  else if ( 2 * i == N) return 0;
  return i;
}
