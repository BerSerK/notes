**************************************************
My Programming Notes
**************************************************

MPI
===========================

`Example Codes <http://www.mcs.anl.gov/research/projects/mpi/usingmpi2/examples/main.htm>`_ from Book "Using MPI"

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
