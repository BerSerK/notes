**************************************************
My Programming Notes
**************************************************

MPI
===========================

Rocommended Materials:

- Introduction to MPI(recommended toturial): http://www.citutor.org/index.php
- MPI tutorial: https://computing.llnl.gov/tutorials/mpi/ 
- High Performance Computing Training: https://computing.llnl.gov/?set=training&page=index
- MPI document: ftp://lab.yeshiwei.com/Ebooks/Prog/mpi/mpi21-report.pdf

Other Materrials:

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
----------------------------

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
 int MPI_Allgatherv(...);

数据散发::

 int MPI_Scatter(...);
 int MPI_Scatterv(...);

数据全收集散发::
 
 int MPI_Alltoall(...);
 int MPI_Alltoallv(...);

错误处理::

   MPI_Errhandler errhd1;
   

进程组和通信其
------------------------

进程组::

 一组进程，通过句柄进行操作，
 属于进程，不由进程组共享！

上下文::

 通信器的附属品，消息在一个给定的上下文上传递，以确保不同通信器之间的信息不要相互干扰

域内通信器::

 进程组和上下问组成
 可以在其中组成拓扑连接方式。

域间通信器::

 用于在分属于不同的进程组之间的进程进行通信。不能定义拓扑，也不能进行聚合通讯。

进程组操作::

 int MPI_Group_size(...);
 int MPI_Group_translate_ranks(...);
 int MPI_Group_compare(...);

域内通信的操作::

 int MPI_Comm_compare(...);
 int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *new_comm);//copy a Communicator
 int MPI_Comm_create(...);
 int MPI_Comm_split(...);
 int MPI_Comm_free(...);

域内通信器的附加属性（Caching）::

 int_MPI_Comm_create_keyval(...);
 int MPI_Comm_set_attr(...);
 ...

域间通信器::

 int MPI_Intercomm_create(...); 
 ...

进程的拓扑结构::

 这是域内通信的附加属性，描述了进程组中各个进程之间的逻辑连接方式。

笛卡尔拓扑结构::

 int MPI_Cart_create(...);// 创立笛卡尔拓扑结构
 int MPI_Dims_create(...);//维数划分
 int MPI_Cart_sub(...);//创建低维子笛卡尔结构
 int MPI_Cartdim_get(...);
 int MPI_Cart_get(...);
 int MPI_Cart_rank(...);
 ...
 int MPI_Cart_shift(...);

文件输入输出
-------------------------------

Fortran 需要包含头文件： mpiof.h

- 文件： 和进程组想关联，所有进程必须同时对文件进行操作；
- 起始位置（dispalcement）：字节数
- 基本单元类型（etype）：位移非负且单调上升；
- 文件单元类型（filetype）：在基本单元类型上派生出来
- 文件视窗（view）：
- 位移(offset）：相对于起始位置
- 文件大小：
- 文件指针
- 文件句柄（file handle）：

打开MPI文件::

 int MPI_File_open(...);
 comm:
 filename:
 amode:
  MPI_MODE_RDONLY,...
 fh: 文件句柄

关闭MPI文件::

 int MPI_File_close(...);

设定文件长度::

 int MPI_File_set_size(...);

预分配空间::
 
 int MPI_File_preallocate(...);

设定文件视窗::

 int MPI_File_set_view();

聚合函数::

 datarep: native, internal, external32

定位::

 MPI_File_xxxx_at, MPI_File_xxxx_at_all,

MPI... sub array...

POSIX信号
-----------------------
 
kill: send a signal to a process::

 #include<signal.h>
 typedef void (*sighandler_t)(int);
 sighandler_t signal(int signum, sighandler_t handler);

POSIX线程
-----------------------
 
::

 #include <sys/types.h>
 #include <unistd.h>
 pid_t fork(void);
  
 #include <stded.h>
 int clone(int(*fn)(void*), void *child


External Data Representation(XDR)
------------------------------------

从文件指针创建::

 void xdrstdio_create(xdrs, file, op)
 XDR *xdrs;
 FILE *file;
 enum xdr_op op;

xdr_op: XDR_ENCODE(输出），XDR_DECODE（输入）

in bash::

 info xdr

销毁 XDR 对象::
 
 xdr_destroy

header file::

 #include<rpc/xdr.h>

单边通讯 One-Sided Communication
-------------------------------------

单边通信指的是通信通过一个进程直接读取或者写入另一个进程的内存区完成通信，
这个操作只和一个进程有关系，所以叫做单边通信。

单边通信的问题在于在多个进程同时操作同一块内存时需要考虑同步协作的问题。

MPI 的单边通信通过所谓窗口来完成。某个进程将自己的一块内存区设为窗口，然后其他进程直接来读写这个窗口的内容。

这种方式也叫做远程内存访问（Remote Memery Access）

创建窗口::

 int MPI_Win_Create(...)

释放窗口::

 int MPI_Win_Free(...)

三种操作:

 - 读 Get
 - 写 Put
 - 累加 （Accumulate）

三种同步方式：

 - Fence
 - 握手
 - Lock 

Get::

 int MPI_Get(...)

Put::

 int MPI_Put(...)

Accumulate::
 
 int MPI_Accumulate(...)

Fence::

 int MPI_Win_fence(int assert,...)

 assert: MPI_MODE_NOSTORE

聚合操作，松同步

MPI_Win_fence(0,win);
//读写窗口
MPI_Win_fence(0,win);

General Active Target Synchronization(握手)::

 int MPI_Win_start(...)
 int MPI_Win_complete(MPI_Win win);
 int MPI_Win_post(MPI_Group group, int assert, MPI_Win win);
 int MPI_Win_wait(MPI_Win win);

Lock::
 
 int MPI_Win_lock();
 int MPI_Win_unlock():
 state: MPI_LOCK_EXCLUSIVE or MPI_LOCK_SHARED
 MPI_Win_lock()
 //
 MPI_Win_unlock(rank, win);

MPI进程管理和域间通信
----------------------

 MPI_Comm_spawn

子进程获得域间通信器。

客户服务器模式（Client/Server）：
服务器端::
 int MPI_Open_port(...)
 int MPI_Close_port(...)
 int MPI_Comm_accept(...)
 int MPI_Publish_name(...)
 int MPI_Unpublish_name(...)

客户端::

 int MPI_Comm_connect(...)
 int MPI_Lookup_name(...)

Socket 模式::

 int MPI_Comm_join(...)

并行算法的评估
------------------------------------
串行算法：

 运行时间/问题规模

并行算法：
 
- 问题规模
- 进程个数
- 进程的相对速度
- 进程间通信速度

加速比：

 加速比=串行运行时间/运行时间*进程数

加速比作为进程个数的函数不是常数;
加速比也是依赖与机器硬件；
  加速比<=1；

造成加速比小于1的原因：

- 负载不平衡；
- 进程交互；
- 同步；
- 算法缺陷；

最好的的串行算法几乎总是不能被顺利的并行化，从而能够并行的总是一些效率不高的算法。

 加速比>1的情况会在一些特殊硬件架构下发生，或者在一些不确定性情况下发生。

加速比：
 
作为问题规模的函数，一般是增函数；
作为进程个数的函数，一般是减函数；

所以对于给定的问题规模而言，
 计算时间存在一个最小值。


- :math:`t_s` : 一个通信的启动时间
- :math:`t_w` : 单个通信时间
- p: 进程数
- m: 消息字数

超立方体拓扑结构

All-to-One 归约和One-to-All 广播时间花费：

.. math::

 T=(t_s+t_w m)log p

All-to-All 花费时间:

.. math::

 T=\sum_{i=1}^{\log p}(t_s+2^{i-1}t_w m)=t_s log p +t_w m(p-1);

稠密矩阵的相关算法

矩阵x向量
 矩阵按行分配给进程；
 n行n进程；
 少于n进程：每个进程n/p行；
 http://www.holoborodko.com/pavel/numerical-methods/numerical-derivative/central-differences/>`_

.. math::

 \frac{d^2u(x_i)}{dx^2}=\sum_{i=-3}^{i=3}\alpha^i u_i +o(\Delta x^6)

文档要求：

怎么得到方程，怎么分割，怎么交换数据。

Dead Line： 2011.11.20

学习其他计算软件：
`````````````````````````

- Trilinos
- PETsc
- fftw

学其中一个软件。Trilinos ,PETsc的开头，或者fftw的全部。

Dead Line： 考试当天晚上十二点之前。

最后一个作业
````````````````````

对于前面两个软件，需要写个代码求解一个稀疏矩阵。

对于fftw求解一个适合于使用谱方法的偏微分方程，要求使用串行接口。


Dead Line： 考试当天晚上十二点之前。


非重叠区域分解：

.. math::

 \frac{\partial}{\partial x^i}(a^{ij} \frac{\partial u}{\partial x^j}) =0 , in\, \Omega \\
 u|_{\partial\Omega}=u_b

在子区域的边界面上有：

.. math::

 (a_1 I \downtriangle u |^+_\Gamma_in-a_2I\downtriangle u|^-_\Gamma)\cdot \arrow{n}

求解方案：

1. 在 `:math: \Omega_1` 上求解Dirichlet边值问题

2. 在 `:math: \Omega_2` 上求解混合边值问题

3. 回到1

.. math::

 \Omega &= [0,1]\times [0,1]\\
 \Omega_1 = (0,1/2)\times(0,1), & \Omega_2(1/2,1)\times (0,1)\\
 a_1=1& a_2=10\\
 u_b=0,f=1


要求：
 
- 另个节点并行；
- 使用五点中心差分格式；
- 子区域内部矩阵求解方法自选；
