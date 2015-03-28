#include <stdio.h>
#include <complex.h>

#include <fftw3.h>
#include <mpi.h>

#define check printf("Here is FILE %s LINE %d\n",__FILE__,__LINE__);

/** 
 * 输出buf到文件filename
 * 
 * @param buf 
 * @param size 
 * @param filename 
 * @param comm_rank 当前进程的rank
 * 
 * @return 
 */
int output(fftw_complex *buf, int size,char* filename,
		   int comm_rank){
  int size_double,amode,i;
  MPI_Datatype etype,filetype;
  MPI_Info info;
  MPI_Status status;
  MPI_File fh;
  MPI_Offset disp;
  amode=(MPI_MODE_CREATE|MPI_MODE_WRONLY);
  size_double=sizeof(double);
  info=MPI_INFO_NULL;
  MPI_File_open(MPI_COMM_WORLD, filename, amode,info,&fh);
  disp=2*comm_rank*size_double*size;
  etype=MPI_DOUBLE;
  filetype=MPI_DOUBLE;
  MPI_File_write_at(fh,disp,buf,2*size,MPI_DOUBLE,&status);
  return 0; 
}

int transpose(fftw_complex *buf, int N, int rank_size){
  fftw_complex * tmp;
  int chunk = 2 * N/rank_size;
  int width =  N/rank_size;
  double *sb, *rb;
  int i,j,k;
  int status;
  fftw_complex t;
  tmp = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)* N * width);
  sb =(double *) buf;
  rb =(double *) tmp;
  check
  for(i = 0; i < N/rank_size; i ++ )
	{
	  status = MPI_Alltoall(sb, chunk, MPI_DOUBLE, rb, chunk, MPI_DOUBLE, MPI_COMM_WORLD);
	  sb+=(N*2);
	  rb+=(N*2);
	}

  for(i = 0; i < rank_size; i ++ ){
	  for(j = 0; j < N/rank_size; j++ ){
		for( k = 0; k < N/rank_size; k++){
		  buf[k * N + i * width +j] = tmp[j * N + i * width +k];
		  buf[j * N + i * width +k] = tmp[k * N + i * width +j];
		}
	  }
	}
  fftw_free(tmp);
  return 0;
}
