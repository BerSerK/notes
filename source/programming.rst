**************************************************
My Programming Notes
**************************************************

MPI
===========================

- `Example Codes <http://www.mcs.anl.gov/research/projects/mpi/usingmpi2/examples/main.htm>`_ from Book "Using MPI"

- Running MPICH: http://heather.cs.ucdavis.edu/~matloff/MPI/NotesMPICH.NM.html#run2

- Standford mpi toturial: http://www.slac.stanford.edu/comp/unix/farm/mpi.html
- UCLA MPI examples: http://www.ats.ucla.edu/clusters/common/computing/parallel/mpi.htm
- MPI exercise: http://www.mcs.anl.gov/research/projects/mpi/tutorial/mpiexmpl/contents.html

Lecture 1 Basic Functions
-------------------------------------
::
  
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&pro_num);
  MPI_Send(&mynumber,1,MPI_INT,(rank+1)%pro_num,99,MPI_COMM_WORLD);
  MPI_Recv(&get_number,1,MPI_INT,(rank-1+pro_num)%pro_num,99,MPI_COMM_WORLD,&status);
  MPI_Finalize();

Take attention about the message block.
::

  MPI_ISend(&mynumber,1,MPI_INT,(rank+1)%pro_num,99,MPI_COMM_WORLD);
  MPI_IRecv(&get_number,1,MPI_INT,(rank-1+pro_num)%pro_num,99,MPI_COMM_WORLD,&status);

Lecture 2 
--------------------------
  
Wait all message sent or received::

  MPI_Isend(buffer[i],buffer_size, MPI_INT,1,i+99, MPI_COMM_WORLD, &request[i]);
  MPI_Irecv(buffer[i],buffer_size, MPI_INT,0,i+99, MPI_COMM_WORLD, &request[i]);
  MPI_Waitall(n_buffer, request, status);

Probe, check without receive::

 int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status)
 int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status)

data_type::

 int MPI_Type_vector(int count, int blocklength, int stride,
 MPI_Datatype oldtype, MPI_Datatype *newtype)
 int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride,
 MPI_Datatype oldtype, MPI_Datatype *newtype)
 int MPI_Type_indexed(int count, int *array_of_blocklengths,
 int *array_of_displacements, MPI_Datatype oldtype,
 MPI_Datatype *newtype)
 int MPI_Type_create_hindexed(int count, int array_of_blocklengths[],
 MPI_Aint array_of_displacements[], MPI_Datatype oldtype,
 MPI_Datatype *newtype)


int MPI_Type_struct(...);

Lecture 3： 聚合通信
========================

聚合通信是所谓的非局部通信。聚合通信有两种方式：

1. 所有进程之间的关系对等。
2. 其中有一个特殊进程。

- 一对多
- 多对一
- 多对多

障碍同步::

 int MPI_Barreier(MPI_Comm comm);

广播::

 int MPI_Bcast(void * buffer, int count, MPI_Datatype data_type, int root, MPI_Comm comm);

 
数据收集::

 int MPI_Gather(void *send_buffer, int send_count, MPI_Datatype send_data_type,
 void * recv_buffer, int recv_count, MPI_Datatype recv_data_type,
 int root, MPI_Comm comm);

 int MPI_GAtherv(...);
 int MPI_Allgather(...);

数据散发::

 int MPI_Scatter(...);
 int MPI_Scatterv(...);

数据全收集散发::
 
 int MPI_Alltoall(...);
 int MPI_Alltoallv(...);

错误处理::

   MPI_Errhandler errhd1;
   


