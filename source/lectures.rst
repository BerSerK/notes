**************************************************
讲座笔记
**************************************************

应用部孟部长介绍：“天河一号”异构并行计算环境
==================================================

孟祥飞博士 mengxf{at}nscc.tj.gov.cn

国家超级计算天津中心情况介绍
--------------------------------------------------

国防科大+浪潮公司 

“天河一号”超级计算机系统
--------------------------------------------------

- 异构结构：CPU+GPU
- 峰值性能：4.7 PFlop/s
- 持续性能：2.566PFlop/s
- 功耗： 4.04MW

Processors 14336 intel cpus +7168 nvidia gpu memory: 2048 ?TB

- CPU 5%的ALU
- GPU 40%的ALU

国际上首台千万亿次CPU+GPU混合系统。

Compuate node = 4 CPU +2 GPU
CPU： x5670 GPU： M2050
rack = 16*cn
cabinet = 4*rack

FT-1000 cpu:

- 8 cores 64 threads


异构并行编程设计
----------------------------------------------------------------------------------------------------

- CPU+GPU 协同计算， 同时隐藏GPU编程。

GPU编程，需要对硬件充分了解，优化内存读写，尽量少的逻辑判断。

- 编程方法思路：
 
 1. 采用多极混合并行编程模型
 2. 节点间使用同构并行编程
 3. 节点内使用异构编程

多级混合并行编程模型

体系结构
 - 节点间，对称结构
 - 节点内，异构结构

编程模型：
 - 节点间，消息通信
 - 节点内，共享内存

  1.线程级并行，开发cpu的多核和GPU的纵核并行
  2.CPU与GPU协同计算,编译器自动优化，手工调优。
   

“天河一号”大规模应用成果
--------------------------------------------------

- 中石油，中石化，石油勘探
- 分子动力学模拟
- 药物公司
- 中科院力学所
- 华大，基因计算
- 全球气候
- 全球大气浅水波
- 磁约束巨变应用的研究：

 1. ITER-CN计划
 2. 与美国能源部“美洲豹”系统比较
 3. 北大，浙大聚变中心联合开发

- 最大规模的湍流的模拟
- 硅警惕院子模拟与尺度效应分析——分子动力学

大规模科学计算环境建设
----------------------------------------------------

- 大规模硬件设施
- 访问网络环境

技术与研发

- 应用程序转移
- 高性能应用开发
- 技术支持团队


系统部相关技术人员介绍：“天河系统架构及用户使用方法”
=====================================================

系统管理部 徐斌
xubin{at}nscc-ty.gov.cn

天河系统平台架构的介绍
-----------------------------------------------------

- 登录节点：麒麟操作系统，具备编译环境
- 数据拷贝节点：NAS存储服务器
- 计算节点：ramdisk精简内核，双路六核，GPU，具备运行环境
- 文件系统：集中式管理的分布式文件系统
- 互联网络：天河高速互联网络，高通信效率，低延迟。
- 作业管理系统： 基于 stread开发的。
- 共享目录： /vol-th
- 用户根目录 /vol-th/home/
- 常用软件: /vol-th/software/
- 常用的动态链接库： /vol-th/
- Intel 编译器
::

 C /opt/intel/cce/10.1.018/
 source /otp/intel/cce/10.1.018/bin/iccevars.sh
 Fortran

- GCC

::

  4.1.2
  4.6.1 /opt/gcc-4.6.1

- CUDA
  version 4.0 
- MPI 编译器
intel  版本::

  /usr/local/mpi/

gcc 版本::

  /usr/local/mpi-gcc/

系统登录条件：
- vpn帐号
- 拥有系统帐号和密码
- 系统登录终端工具::

 putty, secureCRT, Xmanage, SSHSecureShell等等

- vpn登录
 推荐使用ie浏览器
 1. 添加可信站点，工具-》Ineternet选项-》安全-》可信站点-》站点。
 2. 自定义可信站点 安全级别 确定开启ACtivex选项
 3. 访问Web地址 https://vpn.nscc-tj.cn 登录过程中允许插件运行

- 终端登录：
 1. 通过vpn页面查看登陆权限
 2. 打开终端软件，输入可用的资源字符串用户名,密码
 3. 文件传输登录
  协议：ssh2


作业管理：

- 资源权限（GrpJobs,Grpodes,GrpCPUs,GrpSubmit,GrpCPUMins）
- 分区（alloc idle)::

 yhi

- 作业状态(PD R)::
 
 yhq

- 队列(AssociationResourceLimit Resources Priority)::

 yhq

- 作业提交：

 三种方式： yhrun, yhbatch yhalloc
1. yhrun 交互作业提交方式，关闭当前终端会导致程序退出::
 
 yhrun -n 240 -N 20 -p TH_NET ./a.out
 -n 进程数
 -N 节点数
 -p 指定使用的分区
 -w 请求指定列表中的节点 -w cn[32-]
 

 2. yhbatch 批处理作业提交方式::

 yhbatch -n 240 -N 20 -p TH_NET ./mpibatch.sh
 脚本第一行务必为“#!/bin/bash”
 yhbatch ./test.sh

 PBS script -> Slurm script

 3. yhalloc::
 
 yhalloc -N 10 -p TH_NET

 退出是需要在当前终端下输出exit。
 
- 取消已经提交的作业::

 yhq
 yhcancel [id]

联系方式： support@nscc-tj.gov.cn
电话：022-65375500


天河系统编译环境介绍
--------------------------------------------------


用户在使用过程中的系统登陆，任务提交，作业管理等方法介绍
----------------------------------------------------------------------------------------------------


应用部陈博文工程师介绍
==================================================

Fluent、CFX、Mechanical、LS-DYNA软件在天河超级计算机上的作业提交介绍

Fluent在TH-1上的作业提交、重启动、UDF使用方法
----------------------------------------------------------------------------------------------------

What is FLUENT
````````````````````````````````````````````````````````````````````````````````````````````````````

`FLUENT <https://confluence.cornell.edu/display/SIMULATION/FLUENT+Learning+Modules#FLUENTLearningModules-WhatisFLUENT>`_ is a computational fluid dynamics (CFD) software package to simulate fluid flow problems. It uses the finite-volume method to solve the governing equations for a fluid. It provides the capability to use different physical models such as incompressible or compressible, inviscid or viscous, laminar or turbulent, etc. Geometry and grid generation is done using GAMBIT which is the preprocessor bundled with FLUENT.


CFX在TH-1上的作业提交、重启动、以及CFX-Mechanical双向流固耦合方法
----------------------------------------------------------------------------------------------------

`CFX <http://en.wikipedia.org/wiki/CFX>`_ is a commercial Computational Fluid Dynamics (CFD) program, used to simulate fluid flow in a variety of applications. The ANSYS CFX product allows engineers to test systems in a virtual environment. The scalable program has been applied to the simulation of water flowing past ship hulls, gas turbine engines (including the compressors, combustion chamber, turbines and afterburners), aircraft aerodynamics, pumps, fans, HVAC systems, mixing vessels, hydrocyclones, vacuum cleaners, and more.


Mechanical在TH-1上的作业提交、重启动方法
----------------------------------------------------------------------------------------------------

LS-DYNA在TH-1上的作业提交、重启动方法
----------------------------------------------------------------------------------------------------
`LS-DYNA <http://en.wikipedia.org/wiki/LS-DYNA>`_ is an advanced general-purpose multiphysics simulation software package developed by the Livermore Software Technology Corporation (LSTC). While the package continues to contain more and more possibilities for the calculation of many complex, real world problems, its origins and core-competency lie in highly nonlinear transient dynamic finite element analysis (FEA) using explicit time integration. LS-DYNA is being used by the automobile, aerospace, construction, military, manufacturing, and bioengineering industries.
