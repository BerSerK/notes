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
#define N (512)
/// 数组索引
#define index (i * N + j)
/// 时间步长
#define dt (0.8/N)
/// 精度
#define eps (1.0e-10)
/// 最大时间
#define T_max (3.16)
/// \f$\pi\f$
const double PI=acos(-1.0);
const double Runge_Kutta[4]={1, 0.5, 0.5, 1};

void init(fftw_complex * ,fftw_complex* );

void init_memory_and_plan(fftw_complex**, fftw_complex**, fftw_complex**,
						  fftw_complex**, fftw_complex**,
						  fftw_plan *, fftw_plan *);

void free_memory_and_plan(fftw_complex**, fftw_complex**, fftw_complex**,
						  fftw_complex**, fftw_complex**,
						  fftw_plan *, fftw_plan *);

void output_real(fftw_complex *, char *);

void output_img(fftw_complex *, char *);

void output_norm(fftw_complex *, char *);

void evaluate_u_v(fftw_complex ** );

void normalize(fftw_complex *);

void de_alias(fftw_complex *);

void make_convalution( fftw_complex **, fftw_plan *, fftw_plan *);

void eval_right(fftw_complex **, fftw_complex **, fftw_complex **, int, fftw_complex*);

int shift(int);

int main( ){
  
  fftw_complex * working_pool[6];
  fftw_plan forward[6], backward[6];
  fftw_complex *rho, *w, *rhor[4], *wr[4];
  int i,j;

  init_memory_and_plan( working_pool, rhor, wr, &rho, &w, forward, backward);
  init(rho, w);

  fftw_plan p, p1, p2;//backward plan to show \f$\rho\f$ in base space
  p = fftw_plan_dft_2d( N, N,  rho, working_pool[0], FFTW_BACKWARD, FFTW_ESTIMATE); 
  p1 = fftw_plan_dft_2d( N, N,  wr[0], working_pool[0], FFTW_BACKWARD, FFTW_ESTIMATE); 
  p2 = fftw_plan_dft_2d( N, N,  rhor[0], working_pool[0], FFTW_BACKWARD, FFTW_ESTIMATE); 
  //fftw_execute(p);
  //output_real(working_pool[0],"result/rho.txt");
  //output_real(rho,"result/rhot.txt");

  double T = 0.0 ;

  double x, y;
  char filename[50];
  int num = 0;

  while(T < T_max){

	if(num%10==0){
	sprintf(filename,"result/%06d.txt", num);
	fftw_execute(p);
	normalize(working_pool[0]);
	output_real(working_pool[0],filename);
	}

	num++;
	T = T + dt;

	///Now start to evaluate r1 for Runge-Kutta
	///initial \f$ \rho \f$ adn \f$ \omega\f$

	memcpy(working_pool[0], rho, N * N * sizeof(fftw_complex));
	memcpy(working_pool[1], w, N * N * sizeof(fftw_complex));

	///evaluate \f$\hat{u}\hat{v}\f$ by \f$ \w \f$
	evaluate_u_v( working_pool );	
	
	make_convalution( working_pool, forward, backward);

	eval_right( working_pool, rhor, wr, 0, rho);
	

	/* for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N; j ++)
		  {
			rho[index] = rho[ index ] +  rhor[0][index];
			w[index] = w[ index ] + wr[0][index];
		  }
	  }
	  continue;
	/*if(num%10==0){
	sprintf(filename,"result/wr%06d.txt", num);
	fftw_execute(p1);
	normalize(working_pool[0]);
	output_real(working_pool[0],filename);

	sprintf(filename,"result/rhor%06d.txt", num);
	fftw_execute(p2);
	normalize(working_pool[0]);
	output_real(working_pool[0],filename);

	}*/

	///Now start to evaluate r2 for Runge-Kutta
	for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N; j ++)
		  {
			working_pool[ 0 ][ index ] = rho[ index ]+rhor[ 0 ][ index ]/2;
			working_pool[ 1 ][ index ] = w[ index ]+wr[ 0 ][ index ]/2;
		  }
	  }	

	evaluate_u_v(working_pool);	
	make_convalution(working_pool, forward, backward);
	eval_right(working_pool, rhor, wr, 1, rho);

	///Now starts to evaluate r3 for Runge-Kutta
	for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N; j ++)
		  {
			working_pool[ 0 ][ index ] = rho[ index ]+rhor[ 1 ][ index ]/2;
			working_pool[ 1 ][ index ] = w[ index ]+wr[ 1 ][ index ]/2;
		  }
	  }	
	evaluate_u_v(working_pool);	
	make_convalution(working_pool, forward, backward);
	eval_right(working_pool, rhor, wr, 2, rho);

	///Now starts to evaluate r4 for Runge-Kutta
	for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N; j ++)
		  {
			working_pool[0][index] = rho[index] + rhor[2][index];
			working_pool[1][index] = w[index] + wr[2][index];
		  }
	  }	
	evaluate_u_v(working_pool);	
	make_convalution(working_pool, forward, backward);
	eval_right(working_pool, rhor, wr, 3, rho);
	
	///Now starts evaluate next step rho and w;
	  for( i = 0; i < N; i ++)
	  {
		for( j = 0; j < N; j ++)
		  {
			rho[index] = rho[ index ] + 
			  ( rhor[0][index] + 2 * rhor[1][index] + 2 * rhor[2][index] + rhor[3][index])/6.0;
			w[index] = w[ index ] + 
			( wr[0][index] + 2 * wr[1][index] + 2 * wr[2][index] + wr[3][index])/6.0;
		  }
	  }
  }
  free_memory_and_plan( working_pool, rhor, wr, &rho, &w, forward, backward);
  return 0;
}


/** 
 *  初始化 \f$\rho\f$ 和 \f$\omega\f$ 
 * 
 * @param rho 
 * @param w 
 */
void init(fftw_complex * rho,fftw_complex* w){
  int i,j;
  double x, y, c1, c2, rho1, rho2, PI2= PI * PI;

  fftw_plan p;
  p = fftw_plan_dft_2d(N, N, rho, rho, FFTW_FORWARD, FFTW_MEASURE); 

  for(i=0;i<N;i++)
	{
	  x = 2 * PI * ( i )/N;
	  for(j=0;j<N;j++)
		{
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
  fftw_execute(p);
  normalize(rho);
  fftw_destroy_plan(p);

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
						  fftw_complex** rhor,
						  fftw_complex** wr,
						  fftw_complex** rho,
						  fftw_complex** w,
						  fftw_plan *forward, 
						  fftw_plan *backward){
  int i;
  *rho = ( fftw_complex* )fftw_malloc(sizeof(fftw_complex) * N * N);
  *w = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N * N );
  for( i = 0; i < 6; i++ )
	{
	  working_pool[i]=(fftw_complex * )fftw_malloc(sizeof(fftw_complex) * N * N);

	  forward[i]=fftw_plan_dft_2d( N, N, working_pool[i], 
								   working_pool[i], FFTW_FORWARD, FFTW_MEASURE); 

	  backward[i]=fftw_plan_dft_2d( N, N,  working_pool[i], 
									working_pool[i], FFTW_BACKWARD, FFTW_MEASURE); 
	}
  for( i = 0; i < 4; i++ )
	{
	  rhor[i] = (fftw_complex * )fftw_malloc(sizeof( fftw_complex ) * N * N);
	  wr[i] = (fftw_complex * )fftw_malloc(sizeof( fftw_complex) * N * N);
	}
}

/** 
 * 输出一个complex数组的实部
 * 
 * @param data 数据指针
 * @param filename 文件名
 */
void output_real(fftw_complex *data, char*filename){
  printf("writing %s \n",filename);
  FILE *fp;
  fp=fopen(filename,"w");
  int i,j;
  for(i=0;i<N;i++)
	{
	  for(j=0;j<N;j++)
		{
		  fprintf(fp, "%le\t", creal(data[index]));
		}
	  fprintf(fp, "\n");
	}
  fclose(fp);
}

void output_img(fftw_complex *data, char*filename){
  printf("writing %s \n",filename);
  FILE *fp;
  fp=fopen(filename,"w");
  int i,j;
  for(i=0;i<N;i++)
	{
	  for(j=0;j<N;j++)
		{
		  fprintf(fp, "%le\t", cimag(data[index]));
		}
	  fprintf(fp, "\n");
	}
  fclose(fp);
}
void output_norm(fftw_complex *data, char*filename){
  printf("writing %s \n",filename);
  FILE *fp;
  fp=fopen(filename,"w");
  double c,r;
  int i,j;
  for(i=0;i<N;i++)
	{
	  for(j=0;j<N;j++)
		{
		  c=creal(data[ index ]);
		  r=cimag(data[ index ]);
		  fprintf(fp, "%le\t", sqrt( c*c + r*r));
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
void normalize(fftw_complex * data){
  int i, j;
  double factor = N;
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
		a = ((double) i)/N;
		for( j = 0; j < N; j ++)
		  {
			b = ((double) j)/N;
			if( (a >= 1./3 && a <= 2./ 3 )||(b >= 1./3 && b <= 2./ 3 ))
			  {
				data[index] = 0.0;
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
					   fftw_plan *forward,
					   fftw_plan *backward){
  fftw_complex RHO, W, U, V;
  int i,j;
  fftw_complex x,y;

  /// 乘上偏导项
  for( i = 0; i < N; i++)
	{
	  x= - I * shift( i ) ;
	  
	  for( j = 0; j < N; j++)
		{
		  y= -  I * shift( j );

		  RHO =  wp[0][index];
		  W   = wp[1][index];

		  wp[ 0 ][ index ] = RHO * x;
		  wp[ 1 ][ index ] = RHO * y;
		  wp[ 2 ][ index ] = x * W;
		  wp[ 3 ][ index ] = y * W;
		}
	}
  
  /// 将所有分量变换回原空间。
  for( i = 0 ; i < 6; i++)
	{
	  de_alias( wp[ i ] );
	  fftw_execute( backward[ i ] );
	  normalize( wp[ i ] );
	}

  /// 在原空间相乘。
  for( i = 0; i < N; i++)
	{
	  for( j = 0; j < N; j++)
		{
		  U = wp[4][index];
		  V = wp[5][index];
		  
		  wp[ 0 ][ index ] = wp[ 0 ][ index ] * U;
		  wp[ 1 ][ index ] = wp[ 1 ][ index ] * V;

		  wp[ 2 ][ index ] = wp[ 2 ][ index ] * U;
		  wp[ 3 ][ index ] = wp[ 3 ][ index ] * V;
		}
	}

  /// 将相乘所得乘积变换到Fourier空间。
  for(i = 0; i < 4; i ++ )
	{
	  fftw_execute(forward[i]);
	  normalize(wp[i]);
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
				fftw_complex **wr, int n, fftw_complex *rho){
  int i, j;
  fftw_complex rhou, rhov, wu, wv, RHO, x, y;
  for( i = 0; i < N; i ++ )
	  {
		x = - I * shift( i );
		
		//x = - 2 * PI * I * i /N;
		for( j = 0; j < N; j ++ )
		  {
			y = - I * shift( j );
			rhou = wp[0][index];
			rhov = wp[1][index];
			wu = wp[2][index];
			wv = wp[3][index];
			if(n == 0){
			  RHO = rho[ index ];
			}else{
			  RHO = rho[ index ] + rhor[n-1][ index ] * Runge_Kutta[n];
			}
			rhor[n][index] = dt * ( - rhou - rhov);
			wr[n][index] = dt * ( - wu - wv -  y * RHO);
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
  fftw_complex phi, RHO, W, U, V, x, y;
  int i, j, a, b;
	for( i = 0; i < N; i++)
	  {
		a = shift( i );
		x =  - I * a ;
		for( j = 0; j < N; j++)
		  {
			b = shift( j );
			y =  -  I * b;
			W = wp[1][ index ];
			if(a == 0 && b == 0){
			  wp[1][ index ] = 0;
			  wp[4][ index ] = 0;
			  wp[5][ index ] = 0;
			}else{
			  phi = - W / (x * x + y * y); 
			  wp[4][ index ] = - y * phi;/// wp[4] is now u
			  wp[5][ index ] = x * phi;/// wp[5] is now v
			}			  
		  }
	  }
}

int shift(int a){
  if(2 * a > N) return a - N;
  if(2 * a == N) return 0;
  return a;
}


/** 
 * 释放内存, destroy working_pool 的fftw plan
 * 
 * @param working_pool 用于临时存储\f$\rho, \omega, u, v \f$
 * @param rhor Runge-Kutta 法中关于 \f$\rho\f$的 右端项
 * @param wr Runge-Kutta 法中关于 \f$\omega\f$的 右端项
 * @param rho \f$\rho\f$
 * @param w \f$\omega\f$
 * @param forward forword fftw plan for working_pool
 * @param backward backward fftw plan for working_pool
 */
void free_memory_and_plan(fftw_complex** working_pool, 
						  fftw_complex** rhor,
						  fftw_complex** wr,
						  fftw_complex** rho,
						  fftw_complex** w,
						  fftw_plan *forward, 
						  fftw_plan *backward){
  int i;
  fftw_free(*rho );
  fftw_free(*w );

  for( i = 0; i < 6; i++ )
	{
	  fftw_free(working_pool[i]);
	  fftw_destroy_plan(forward[i]);
	  fftw_destroy_plan(backward[i]);
	}
  for( i = 0; i < 4; i++ )
	{
	  fftw_free( rhor[i] );
	  fftw_free( wr[i] );
	}
}

