**************************************************
用python做科学计算初步
**************************************************

.. currentmodule:: numpy


本章内容主要摘自 `用Python做科学计算 <http://hyry.dip.jp/pydoc/index.html>`_ , 并参照了：
`numpy reference <http://docs.scipy.org/doc/numpy-1.6.0/reference/>`_

程序安装或许可以参照： http://hyry.dip.jp/pydoc/install.html

不过个人不推荐，这个安装里面介绍的主要是windows环境下的使用，或许是挺轻松的。
不过，里面介绍的pythonxy在linux的安装似乎挺麻烦的，我甚至都没能找到下载的地方。网站上给的ubuntu的源也是根本连不上。
其实安装一个ipython，就够学习之用了。

IPython
==================================================
.. index::
   single: ipython

介绍一下 IPython 吧，来自 `wikipedia ipython <http://en.wikipedia.org/wiki/IPython>`_ and `ipython.org <http://ipython.org/>`_

IPython 是一个 python 的交互式 shell，比默认的 python shell 好用得多，支持变量tab补全，自动缩近，支持 bash shell 命令，内置了许多很有用的功能和函数，以及丰富的历史记录。

以下来自 `ipython.org`_ ：


 IPython provides a rich toolkit to help you make the most out of using Python interactively. Its main components are:

- Powerful interactive Python shells (terminal- and Qt-based).
- Support for interactive data visualization and use of GUI toolkits.
- Flexible, embeddable interpreters to load into your own projects.
- Tools for high level and interactive parallel computing.

最后一点很诱人阿。

我想在 `ipython.org`_ 首页中的Support 列表中有一条足以说服你使用ipython了：

- Microsoft’s team working on Python Tools for Visual Studio developed the integraton of IPython into the Python plugin for Visual Studio 2010.

最后请看 `ipython.org`_ 上的 `Introduction to ipython <http://ipython.org/ipython-doc/stable/interactive/tutorial.html>`_ . 他们也推荐直接从 `python官方文档 <http://docs.python.org/tutorial/>`_ 入手学python。

其中提到的magic functions 中的run是运行脚本的命令，如果重复运行一个脚本，用这个命令可以提高效率（估计是在import 软件包这个事儿上省了时间吧）。同时，他和import相比有个好处，import之后如果你修改了代码，得退出ipython（python）重新开始之后再import才会生效。
 
IPython的debug功能似乎也挺好用，以前我写python的时候总是靠print来debug。

这个页面也值得浏览一下： `ipython screenshots <http://ipython.scipy.org/screenshots/index.html>`_

下面回到numpy，scipy的使用介绍上来：

Numpy 基础
==================================================
NumPy弥补了python对数值计算中数组操作支持不够的不足，NumPy提供了两种基本的对象：ndarray（N-dimensional array object）和 ufunc（universal function object）。ndarray(下文统一称之为数组)是存储单一数据类型的多维数组，而ufunc则是能够对数组进行处理的函数。

下面例子中都用下面的方式加载numpy::

 import numpy as np

当然你也可以用别的方式加载，比如“from numpy import \*”的方式。

ndarray
----------------------
.. index::
   single: ndarray


可以用如下方式创建ndarray的各维数的数组，和matlab非常类似::

 In [1]: import numpy as np
 
 In [2]: a = np.array([1, 2, 3, 4])
 
 In [3]: b = np.array((5, 6, 7, 8))
 
 In [4]: c = np.array([[1, 2, 3, 4],[4, 5, 6, 7], [7, 8, 9, 10]])
 
 In [5]: b
 Out[5]: array([5, 6, 7, 8])
 
 In [6]: c
 Out[6]: 
 array([[ 1,  2,  3,  4],
        [ 4,  5,  6,  7],
        [ 7,  8,  9, 10]])
 
 In [7]: c.dtype
 Out[7]: dtype('int32')

数组的大小可以通过其shape属性获得::

 In [8]: c.shape
 Out[8]: (3, 4)
 
 In [9]: a.shape
 Out[9]: (4,)

还可以改变一个数组的形状::

 In [10]: c.shape = 4,3
 
 In [11]: c
 Out[11]: 
 array([[ 1,  2,  3],
        [ 4,  4,  5],
        [ 6,  7,  7],
        [ 8,  9, 10]])

注意这并不是转置。

还可以这样::

 In [12]: c.shape = 2,-1
 
 In [13]: c
 Out[13]: 
 array([[ 1,  2,  3,  4,  4,  5],
        [ 6,  7,  7,  8,  9, 10]])

这里-1表示自动计算大小。

而reshape函数则是创建一个新数组，原来的数组不变::

 In [14]: d=a.reshape((2,2))
 
 In [15]: d
 Out[15]: 
 array([[1, 2],
        [3, 4]])
 
 In [16]: a
 Out[16]: array([1, 2, 3, 4])

注意！数组a和d其实共享数据存储内存区域，因此修改其中任意一个数组的元素都会同时修改另外一个数组的内容::

 In [17]: a[1]=123
 
 In [18]: d
 Out[18]: 
 array([[  1, 123],
        [  3,   4]])

数组的元素类型可以通过dtype属性获得。上面例子中的参数序列的元素都是整数，因此所创建的数组的元素类型也是整数，并且是32bit的长整型。可以通过dtype参数在创建时指定元素类型::

 In [19]: np.array([[1, 2, 3, 4],[4, 5, 6, 7], [7, 8, 9, 10]], dtype=np.float)
 Out[19]: 
 array([[  1.,   2.,   3.,   4.],
        [  4.,   5.,   6.,   7.],
        [  7.,   8.,   9.,  10.]])
 
 In [20]: np.array([[1, 2, 3, 4],[4, 5, 6, 7], [7, 8, 9, 10]], dtype=np.complex)
 Out[20]: 
 array([[  1.+0.j,   2.+0.j,   3.+0.j,   4.+0.j],
        [  4.+0.j,   5.+0.j,   6.+0.j,   7.+0.j],
        [  7.+0.j,   8.+0.j,   9.+0.j,  10.+0.j]])

还有下面的类似matlab中的方式办法生成一些矩阵::

 In [21]: np.arange(0,1,0.1)
 Out[21]: array([ 0. ,  0.1,  0.2,  0.3,  0.4,  0.5,  0.6,  0.7,  0.8,  0.9])
 
 In [22]: np.linspace(0, 1, 12)
 Out[22]: 
 array([ 0.        ,  0.09090909,  0.18181818,  0.27272727,  0.36363636,
         0.45454545,  0.54545455,  0.63636364,  0.72727273,  0.81818182,
         0.90909091,  1.        ])
 
 In [23]: np.logspace(0, 2, 20)
 Out[23]: 
 array([   1.        ,    1.27427499,    1.62377674,    2.06913808,
           2.6366509 ,    3.35981829,    4.2813324 ,    5.45559478,
           6.95192796,    8.8586679 ,   11.28837892,   14.38449888,
          18.32980711,   23.35721469,   29.76351442,   37.92690191,
          48.32930239,   61.58482111,   78.47599704,  100.        ])

- arange函数类似于python的range函数，通过指定开始值、终值和步长来创建一维数组，注意数组不包括终值.
- linspace函数通过指定开始值、终值和元素个数来创建一维数组，可以通过endpoint关键字指定是否包括终值，缺省设置是包括终值.
- logspace函数和linspace类似，不过它创建等比数列，下面的例子产生1(10^0)到100(10^2)、有20个元素的等比数列.

此外，使用frombuffer, fromstring, fromfile等函数可以从字节序列创建数组，下面以fromstring为例::

 In [24]: s = "abcdefgh"
 
 In [25]: np.fromstring(s, dtype=np.int8)
 Out[25]: array([ 97,  98,  99, 100, 101, 102, 103, 104], dtype=int8)
 
 In [26]: np.fromstring(s, dtype=np.int16)
 Out[26]: array([25185, 25699, 26213, 26727], dtype=int16)
 
 In [27]: np.fromstring(s, dtype=np.float)
 Out[27]: array([  8.54088322e+194])

很容易理解上述代码：dtype为int16的时候正好是两个字符转化成一个int16。float是64位双精度浮点数正好8个字符。

我们可以写一个Python的函数，它将数组下标转换为数组中对应的值，然后使用此函数创建数组::

 In [32]: def func(i):
    ....:     return i*i+1
    ....: 
 
 In [33]: np.fromfunction(func, (10,))
 Out[33]: array([  1.,   2.,   5.,  10.,  17.,  26.,  37.,  50.,  65.,  82.])

fromfunction函数的第一个参数为计算每个数组元素的函数，第二个参数为数组的大小(shape)，因为它支持多维数组，所以第二个参数必须是一个序列，本例中用(10,)创建一个10元素的一维数组。

 
ndarray 一维数组的索引与普通python数组的索引类似::

 In [14]: a=np.arange(10)
 
 In [15]: a[:4]
 Out[15]: array([0, 1, 2, 3])
 
 In [16]: a[1:10:2]
 Out[16]: array([1, 3, 5, 7, 9])
 
高维数组相对复杂一点，也是和matlab非常相似，还可以动态增加维度，具体可以参照 `indexing <http://docs.scipy.org/doc/numpy/reference/arrays.indexing.html#arrays-indexing>`_ ::

 In [28]: b=np.array([[[1],[2],[3]], [[4],[5],[6]]])
 
 In [29]: b.shape
 Out[29]: (2, 3, 1)
 
 In [30]: b[1:2]
 Out[30]: 
 array([[[4],
         [5],
         [6]]])
 
 In [31]: b[0:1,2]
 Out[31]: array([[3]])
 
 In [32]: b[0:2,2]
 Out[32]: 
 array([[3],
        [6]])
 
 In [33]: b[1,2]
 Out[33]: array([6])
 
 In [34]: b[[0,1],2]
 Out[34]: 
 array([[3],
        [6]])

Data type objects (dtype) and 结构数组
--------------------------------------------------

数据类型（data type object, ie. numpy.dtype的实例）描述的是array对象怎样解析内存中的固定大小的内存段。它描素了数据的一下几个方面：

1. 数据的类型(integer, float, Python object, etc.)
2. 数据的大小(how many bytes is in e.g. the integer)
3. 二进制位的存储顺序(little-endian or big-endian)
4. 如果数据类型（data type）是一条记录，即其他数据类型的组合(e.g., describing an array item consisting of an integer and a float),这和C语言里面的struct类似。
 
 1. 记录的各个数据的名称是什么，怎么获取这个子数据。
 #. 每个子数据的的类型是什么。
 #. 每个子数据都使用哪一部分内存。

5. 如果数据是一个子数组，它的形状是什么。

Note that the scalar types are not dtype objects, even though they can be used in place of one whenever a data type specification is needed in Numpy.

如下例::
 
 In [19]: dt = np.dtype([('name', np.str_, 16), ('grades', np.float64, (2,))])
 
 In [20]: dt['name']
 Out[20]: dtype('|S16')
 
 In [21]: dt['grades']
 Out[21]: dtype(('float64',(2,)))
 
 In [22]: x = np.array([('Sarah', (8.0, 7.0)), ('John', (6.0, 7.0))], dtype=dt)
 
 In [23]: x[1]
 Out[23]: ('John', [6.0, 7.0])
 
 In [24]: type(x[1])
 Out[24]: <type 'numpy.void'>
 
 In [25]: type(x[1]['grades'])
 Out[25]: <type 'numpy.ndarray'>

如果要做C语言扩展, 或者输出文件用于C的读入文件需要注意下面这点:

.. note:: 内存对齐
 
 C语言的结构体为了内存寻址方便，会自动的添加一些填充用的字节，这叫做内存对齐。例如如果把下面的name[32]改为name[30]的话，由于内存对齐问题，在name和age中间会填补两个字节，最终的结构体大小不会改变。因此如果numpy中的所配置的内存大小不符合C语言的对齐规范的话，将会出现数据错位。为了解决这个问题，在创建dtype对象时，可以传递参数align=True，这样numpy的结构数组的内存对齐和C语言的结构体就一致了。

关于C与numpy中array的交互请看 `array interface <http://docs.scipy.org/doc/numpy-1.6.0/reference/arrays.interface.html>`_

内存结构
-------------------------------------------------
元素在数据存储区中的排列格式有两种：C语言格式和Fortan语言格式。在C语言中，多维数组的第0轴是最上位的，即第0轴的下标增加1时，元素的地址增加的字节数最多；而Fortan语言的多维数组的第0轴是最下位的，即第0轴的下标增加1时，地址只增加一个元素的字节数。在NumPy中，元素在内存中的排列缺省是以C语言格式存储的，如果你希望改为Fortan格式的话，只需要给数组传递order="F"参数::
 
 In [27]: c = np.array([[0,1,2],[3,4,5],[6,7,8]], dtype=np.float32, order="F")
 
 In [28]: c.strides
 Out[28]: (4, 12)
 
strides中保存的是当每个轴的下标增加1时，数据存储区中的指针所增加的字节数。 

标准array子类
---------------------------

.. index::
   single: matrix

这里主要介绍一下matrix类，更多的时候直接用ndarray更好。

matrix类是ndarray的子类，所以有同样的变量和函数。主要有六点不同：

1. Matrix objects can be created using a string notation to allow
   Matlab-style syntax where spaces separate columns and semicolons
   (';') separate rows.

2. Matrix objects are always two-dimensional. This has far-reaching
   implications, in that m.ravel() is still two-dimensional (with a 1
   in the first dimension) and item selection returns two-dimensional
   objects so that sequence behavior is fundamentally different than
   arrays.

3. Matrix objects over-ride multiplication to be
   matrix-multiplication. **Make sure you understand this for
   functions that you may want to receive matrices. Especially in
   light of the fact that asanyarray(m) returns a matrix when m is
   a matrix.**

4. Matrix objects over-ride power to be matrix raised to a power. The
   same warning about using power inside a function that uses
   asanyarray(...) to get an array object holds for this fact.

5. The default __array_priority\__ of matrix objects is 10.0, and
   therefore mixed operations with ndarrays always produce matrices.

6. Matrices have special attributes which make calculations easier.
   These are：

   a.      matrix.T: transpose

   b.	  matrix.H: hermitian (conjugate) transpose

   c.	  matrix.I: inverse

   d. matrix.A: base array

作用在matrix上*和**是矩阵乘法，和矩阵指数。

:matrix:	
 Returns a matrix from an array-like object, or from a string of data.
:asmatrix(data[, dtype]):
 Interpret the input as a matrix.
:bmat(obj[, ldict, gdict]):
 Build a matrix object from a string, nested sequence, or array.

例子,用字符串生成::

 In [32]: a=np.mat('1 2 3; 4 5 3')
 
 In [33]: print (a*a.T).I
 [[ 0.29239766 -0.13450292]
  [-0.13450292  0.08187135]]

例子,用nested sequence::

 In [34]: np.mat([[1,5,10],[1.0,3,4j]])
 Out[34]: 
 matrix([[  1.+0.j,   5.+0.j,  10.+0.j],
         [  1.+0.j,   3.+0.j,   0.+4.j]])
 
例子，用ndarray生成::

 In [42]: np.mat(np.random.rand(3,3)).T
 Out[42]: 
 matrix([[ 0.52000784,  0.52112021,  0.86437867],
         [ 0.15670061,  0.42595431,  0.48985481],
         [ 0.30427789,  0.15568791,  0.43147207]])
 
更多细节请关注 `Standard array subclasses <http://docs.scipy.org/doc/numpy-1.6.0/reference/arrays.classes.html>`_

ufunc运算（universal function）
-----------------------------------------

.. index::
   single: universal function

universal function是一种能对数组的每个元素进行操作的函数。NumPy内置的许多ufunc函数都是在C语言级别实现的，因此它们的计算速度非常快。让我们来看一个例子::

 In [2]: x=np.linspace(0,2*np.pi,10)
 
 In [3]: y=np.sin(x)
 
 In [4]: y
 Out[4]: 
 array([  0.00000000e+00,   6.42787610e-01,   9.84807753e-01,
          8.66025404e-01,   3.42020143e-01,  -3.42020143e-01,
         -8.66025404e-01,  -9.84807753e-01,  -6.42787610e-01,
         -2.44921271e-16])
 
这里的np.sin是一个ufunc，上面的例子里面没有改变x的值。如果要求把结果保存在x中可以将x作为第二个参数::
 
 In [5]: t=np.sin(x,x)
 
 In [6]: t==x
 Out[6]: array([ True,  True,  True,  True,  True,  True,  True,  True,  True,  True], dtype=bool)
 
 In [7]: x
 Out[7]: 
 array([  0.00000000e+00,   6.42787610e-01,   9.84807753e-01,
          8.66025404e-01,   3.42020143e-01,  -3.42020143e-01,
         -8.66025404e-01,  -9.84807753e-01,  -6.42787610e-01,
         -2.44921271e-16])

 In [8]: id(t)==id(x)
 Out[8]: True

这时t和x指向同一块存储区。

值得注意的是，求数组的sin时，numpy.sin比python自带的math.sin要快很多，而单个sin的时候相反。也就是说下面三个代码的
速度依次递减::

 import numpy as np
 x = [i * 0.001 for i in xrange(1000000)]
 x = np.array(x)
 np.sin(x,x)
 
 import math
 x = [i * 0.001 for i in xrange(1000000)]
 for i, t in enumerate(x):
     x[i] = math.sin(t)
 
 x = [i * 0.001 for i in xrange(1000000)]
 x = np.array(x)
 for i, t in enumerate(x):
     x[i] = np.sin(t)


更多关于ufunc，请查阅 `ufunc <http://docs.scipy.org/doc/numpy-1.6.0/reference/ufuncs.html>`_
其他ufunc请查看： `Other ufuncs <http://docs.scipy.org/doc/numpy-1.6.0/reference/ufuncs.html#available-ufuncs>`_

另外还可以利用 `numpy.frompyfunc <http://docs.scipy.org/doc/numpy-1.6.0/reference/generated/numpy.frompyfunc.html#numpy.frompyfunc>`_ 自己构造.

Broadcasting (广播)
``````````````````````````````````````````

当我们使用ufunc函数对两个数组进行计算时，ufunc函数会对这两个数组的对应元素进行计算，因此它要求这两个数组有相同的大小(shape相同)。如果两个数组的shape不同的话，会进行如下的广播(broadcasting)处理：

1. 让所有输入数组都向其中shape最长的数组看齐，shape中不足的部分都通过在前面加1补齐
2. 输出数组的shape是输入数组shape的各个轴上的最大值
3. 如果输入数组的某个轴和输出数组的对应轴的长度相同或者其长度为1时，这个数组能够用来计算，否则出错
4. 当输入数组的某个轴的长度为1时，沿着此轴运算时都用此轴上的第一组值

请看例子::

 In [13]: a = np.arange(0, 60, 10).reshape(-1, 1)
 
 In [14]: b = np.arange(0, 5)
 
 In [15]: c = a + b
 
 In [16]: print a
 [[ 0]
  [10]
  [20]
  [30]
  [40]
  [50]]
 
 In [17]: print b
 [0 1 2 3 4]
 
 In [18]: print c
 [[ 0  1  2  3  4]
  [10 11 12 13 14]
  [20 21 22 23 24]
  [30 31 32 33 34]
  [40 41 42 43 44]
  [50 51 52 53 54]]

PS： `numpy.ogrid <http://docs.scipy.org/doc/numpy/reference/generated/numpy.ogrid.html>`_ 生成两个可以broadcasting成方形网格的一维数组.

ufunc的方法
```````````````````````````````````

ufunc函数本身还有些方法，这些方法只对两个输入一个输出的ufunc函数有效，其它的ufunc对象调用这些方法时会抛出ValueError异常。


ufunc.reduce(a[, axis, dtype, out]):

	Reduces a‘s dimension by one, by applying ufunc along one axis.

ufunc.accumulate(array[, axis, dtype, out]):

	Accumulate the result of applying the operator to all elements.

ufunc.reduceat(a, indices[, axis, dtype, out]):

	Performs a (local) reduce with specified slices over a single axis.

ufunc.outer(A, B):

	Apply the ufunc op to all pairs (a, b) with a in A and b in B.


详情请查看 `Methods <http://docs.scipy.org/doc/numpy-1.6.0/reference/ufuncs.html#methods>`_

矩阵运算补充
--------------------------------

矩阵的乘积可以使用dot函数进行计算。对于二维数组，它计算的是矩阵乘积，对于一维数组，它计算的是其点积。当需要将一维数组当作列矢量或者行矢量进行矩阵运算时，推荐先使用reshape函数将一维数组转换为二维数组。

除了dot计算乘积之外，NumPy还提供了inner和outer等多种计算乘积的函数。这些函数计算乘积的方式不同，尤其是当对于多维数组的时候，更容易搞混。

- dot : 对于两个一维的数组，计算的是这两个数组对应下标元素的乘积和(数学上称之为内积)；对于二维数组，计算的是两个数组的矩阵乘积；对于多维数组，它的通用计算公式如下，即结果数组中的每个元素都是：数组a的最后一维上的所有元素与数组b的倒数第二位上的所有元素的乘积和。

- inner : 和dot乘积一样，对于两个一维数组，计算的是这两个数组对应下标元素的乘积和；对于多维数组，它计算的结果数组中的每个元素都是：数组a和b的最后一维的内积，因此数组a和b的最后一维的长度必须相同。

- outer : 只按照一维数组进行计算，如果传入参数是多维数组，则先将此数组展平为一维数组之后再进行运算。outer乘积计算的列向量和行向量的矩阵乘积。

矩阵中更高级的一些运算可以在NumPy的线性代数子库linalg中找到。例如inv函数计算逆矩阵，solve函数可以求解多元一次方程组。

文件存取
--------------------------------

NumPy提供了多种文件操作函数方便我们存取数组内容。文件存取的格式分为两类：二进制和文本。而二进制格式的文件又分为NumPy专用的格式化二进制类型和无格式类型。

使用数组的方法函数tofile可以方便地将数组中数据以二进制的格式写进文件。tofile输出的数据没有格式，因此用numpy.fromfile读回来的时候需要自己格式化数据::

 In [20]: a=np.arange(12)
 
 In [21]: a.shape = 3,4
 
 In [22]: a
 Out[22]: 
 array([[ 0,  1,  2,  3],
        [ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])
 
 In [23]: a.tofile('a.bin')
 
 In [24]: b = np.fromfile('a.bin', dtype=np.float)
 
 In [25]: b
 Out[25]: 
 array([  2.12199579e-314,   6.36598737e-314,   1.06099790e-313,
          1.48539705e-313,   1.90979621e-313,   2.33419537e-313])
 
 In [26]: a.dtype
 Out[26]: dtype('int32')
 
 In [27]: b = np.fromfile('a.bin', dtype=np.int32)
 
 In [28]: b
 Out[28]: array([ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11])
 
 In [29]: b.shape = 3,4
 
 In [30]: b
 Out[30]: 
 array([[ 0,  1,  2,  3],
        [ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])
 
从上面的例子可以看出，需要在读入的时候设置正确的dtype和shape才能保证数据一致。并且tofile函数不管数组的排列顺序是C语言格式的还是Fortran语言格式的，统一使用C语言格式输出。

此外如果fromfile和tofile函数调用时指定了sep关键字参数的话，数组将以文本格式输入输出。

numpy.load和numpy.save函数以NumPy专用的二进制类型保存数据，这两个函数会自动处理元素类型和shape等信息，使用它们读写数组就方便多了，但是numpy.save输出的文件很难和其它语言编写的程序读入::

 In [31]: np.save('a.npy',a)
 
 In [32]: c = np.load('a.npy')
 
 In [33]: c
 Out[33]: 
 array([[ 0,  1,  2,  3],
        [ 4,  5,  6,  7],
        [ 8,  9, 10, 11]])

如果你想将多个数组保存到一个文件中的话，可以使用numpy.savez函数。savez函数的第一个参数是文件名，其后的参数都是需要保存的数组，也可以使用关键字参数为数组起一个名字，非关键字参数传递的数组会自动起名为arr_0, arr_1, ...。savez函数输出的是一个压缩文件(扩展名为npz)，其中每个文件都是一个save函数保存的npy文件，文件名对应于数组名。load函数自动识别npz文件，并且返回一个类似于字典的对象，可以通过数组名作为关键字获取数组的内容::

 In [34]: a = np.array([[1,2,3],[4,5,6]])
 
 In [35]: b = np.arange(0, 1.0, 0.1)
 
 In [36]: c = np.sin(b)
 
 In [37]: np.savez("result.npz", a, b, sin_array = c)
 
 In [38]: r = np.load("result.npz")
 
 In [39]: r["arr_0"]
 Out[39]: 
 array([[1, 2, 3],
        [4, 5, 6]])
 
 In [40]: r["arr_1"]
 Out[40]: array([ 0. ,  0.1,  0.2,  0.3,  0.4,  0.5,  0.6,  0.7,  0.8,  0.9])
 
 In [41]: r["sin_array"]
 Out[41]: 
 array([ 0.        ,  0.09983342,  0.19866933,  0.29552021,  0.38941834,
         0.47942554,  0.56464247,  0.64421769,  0.71735609,  0.78332691])

如果你用解压软件打开result.npz文件的话，会发现其中有三个文件：arr_0.npy， arr_1.npy， sin_array.npy，其中分别保存着数组a, b, c的内容。

使用numpy.savetxt和numpy.loadtxt可以读写1维和2维的数组::

 In [2]: a = np.arange(0,12,0.5).reshape(4,-1)
 
 In [3]: np.savetxt("a.txt", a)  # 缺省按照'%.18e'格式保存数据，以空格分隔
 
 In [4]: np.loadtxt("a.txt")
 Out[4]: 
 array([[  0. ,   0.5,   1. ,   1.5,   2. ,   2.5],
        [  3. ,   3.5,   4. ,   4.5,   5. ,   5.5],
        [  6. ,   6.5,   7. ,   7.5,   8. ,   8.5],
        [  9. ,   9.5,  10. ,  10.5,  11. ,  11.5]])
 
 In [5]: np.savetxt("a.txt", a, fmt="%d", delimiter=",")#改为保存为整数，以逗号分隔
 
 In [6]: np.loadtxt("a.txt",delimiter=",") # 读入的时候也需要指定逗号分隔
 Out[6]: 
 array([[  0.,   0.,   1.,   1.,   2.,   2.],
        [  3.,   3.,   4.,   4.,   5.,   5.],
        [  6.,   6.,   7.,   7.,   8.,   8.],
        [  9.,   9.,  10.,  10.,  11.,  11.]])
 

以上介绍所举的例子都是传递的文件名，也可以传递已经打开的文件对象，例如对于load和save函数来说，如果使用文件对象的话，可以将多个数组储存到一个npy文件中：本节介绍所举的例子都是传递的文件名，也可以传递已经打开的文件对象，例如对于load和save函数来说，如果使用文件对象的话，可以将多个数组储存到一个npy文件中::

 In [7]: a = np.arange(8)
 
 In [8]: b = np.add.accumulate(a)
 
 In [9]: c = a + b
 
 In [10]: f = file("result.npy", "wb")
 
 In [11]: np.save(f, a)
 
 In [12]: np.save(f, b)
 
 In [13]: np.save(f, c)
 
 In [14]: f.close()
 
 In [15]: f = file("result.npy", "rb")
 
 In [16]: np.load(f)
 Out[16]: array([0, 1, 2, 3, 4, 5, 6, 7])
 
 In [17]: np.load(f)
 Out[17]: array([ 0,  1,  3,  6, 10, 15, 21, 28])
 
 In [18]: np.load(f)
 Out[18]: array([ 0,  2,  5,  9, 14, 20, 27, 35])
