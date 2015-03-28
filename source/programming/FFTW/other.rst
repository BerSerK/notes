**************************************************
Other Important Topics
**************************************************

.. index:: SIMD alignment
.. index:: fftw_malloc

SIMD alignment and fftw_malloc
==================================================

SIMD, which stands for “Single Instruction Multiple Data,” is a set of special operations supported by some processors to perform a single operation on several numbers (usually 2 or 4) simultaneously. SIMD floating-point instructions are available on several popular CPUs: SSE/SSE2/AVX on recent x86/x86-64 processors, AltiVec (single precision) on some PowerPCs (Apple G4 and higher), and MIPS Paired Single (currently only in FFTW 3.2.x). FFTW can be compiled to support the SIMD instructions on any of these systems.

comment：利用这个可以提高效率。所以用fftw_malloc 来分配内存，fftw_free 来释放。

A program linking to an FFTW library compiled with SIMD support can obtain a nonnegligible speedup for most complex and r2c/c2r transforms. In order to obtain this speedup, however, the arrays of complex (or real) data passed to FFTW must be specially aligned in memory (typically 16-byte aligned), and often this alignment is more stringent than that provided by the usual malloc (etc.) allocation routines.

In order to guarantee proper alignment for SIMD, therefore, in case your program is ever linked against a SIMD-using FFTW, we recommend allocating your transform data with fftw_malloc and de-allocating it with fftw_free. These have exactly the same interface and behavior as malloc/free, except that for a SIMD FFTW they ensure that the returned pointer has the necessary alignment (by calling memalign or its equivalent on your OS).

You are not required to use fftw_malloc. You can allocate your data in any way that you like, from malloc to new (in C++) to a fixed-size array declaration. If the array happens not to be properly aligned, FFTW will not use the SIMD extensions. Since fftw_malloc only ever needs to be used for real and complex arrays, we provide two convenient wrapper routines fftw_alloc_real(N) and fftw_alloc_complex(N) that are equivalent to (double*)fftw_malloc(sizeof(double) * N) and (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N), respectively (or their equivalents in other precisions).

comment： 使用fftw_alloc_real(N) fftw_alloc_complex(N) 更方便。

Multi-dimensional Array Format
======================================================================

This section describes the format in which multi-dimensional arrays are stored in FFTW. We felt that a detailed discussion of this topic was necessary. Since several different formats are common, this topic is often a source of confusion.


Row-major Format
------------------------------------------------------------

The multi-dimensional arrays passed to fftw_plan_dft etcetera are expected to be stored as a single contiguous block in row-major order (sometimes called “C order”). Basically, this means that as you step through adjacent memory locations, the first dimension's index varies most slowly and the last dimension's index varies most quickly.

To be more explicit, let us consider an array of rank d whose dimensions are :math:`n_0 * n_1 * n_2 * ... * n_{d-1}` . Now, we specify a location in the array by a sequence of d (zero-based) indices, one for each dimension: :math:`(i_0, i_1, i_2,..., i_{d-1})` . If the array is stored in row-major order, then this element is located at the position :math:`i_{d-1} + n_{d-1} * (i_{d-2} + n_{d-2} * (... + n_1 * i_0))` .

Note that, for the ordinary complex DFT, each element of the array must be of type fftw_complex; i.e. a (real, imaginary) pair of (double-precision) numbers.

In the advanced FFTW interface, the physical dimensions n from which the indices are computed can be different from (larger than) the logical dimensions of the transform to be computed, in order to transform a subset of a larger array. Note also that, in the advanced interface, the expression above is multiplied by a stride to get the actual array index—this is useful in situations where each element of the multi-dimensional array is actually a data structure (or another array), and you just want to transform a single field. In the basic interface, however, the stride is 1.

comment: 对于高级用户可以用高级接口只对数组的一部分做变换。

.. index:: Column-major Format

Column-major Format
------------------------------------------------------------

Readers from the Fortran world are used to arrays stored in column-major order (sometimes called “Fortran order”). This is essentially the exact opposite of row-major order in that, here, the first dimension's index varies most quickly.

If you have an array stored in column-major order and wish to transform it using FFTW, it is quite easy to do. When creating the plan, simply pass the dimensions of the array to the planner in reverse order. For example, if your array is a rank three N x M x L matrix in column-major order, you should pass the dimensions of the array as if it were an L x M x N matrix (which it is, from the perspective of FFTW). This is done for you automatically by the FFTW legacy-Fortran interface (see Calling FFTW from Legacy Fortran), but you must do it manually with the modern Fortran interface (see Reversing array dimensions).

comment： 只要在调用的时候将描述维度的数组倒序就行了。

.. index:: Fixed-size Arrays in C

Fixed-size Arrays in C
------------------------------------------------------------

A multi-dimensional array whose size is declared at compile time in C is already in row-major order. You don't have to do anything special to transform it. For example:

.. code-block:: c

     {
          fftw_complex data[N0][N1][N2];
          fftw_plan plan;
          ...
          plan = fftw_plan_dft_3d(N0, N1, N2, &data[0][0][0], &data[0][0][0],
                                  FFTW_FORWARD, FFTW_ESTIMATE);
          ...
     }

This will plan a 3d in-place transform of size N0 x N1 x N2. Notice how we took the address of the zero-th element to pass to the planner (we could also have used a typecast).

However, we tend to discourage users from declaring their arrays in this way, for two reasons. First, this allocates the array on the stack (“automatic” storage), which has a very limited size on most operating systems (declaring an array with more than a few thousand elements will often cause a crash). (You can get around this limitation on many systems by declaring the array as static and/or global, but that has its own drawbacks.) Second, it may not optimally align the array for use with a SIMD FFTW (see `SIMD alignment and fftw_malloc`_ ). Instead, we recommend using fftw_malloc, as described below.

comment: 尽量不要用这种方式声明数组。因为这样声明是在stack上的有大小限制。这样不能利用好fftw_malloc带来的效率优势。

.. index:: Dynamic Arrays in C

Dynamic Arrays in C
----------------------------------------------------------------------

comment:推荐使用fftw_malloc 方式来进行分配内存。

We recommend allocating most arrays dynamically, with fftw_malloc. This isn't too hard to do, although it is not as straightforward for multi-dimensional arrays as it is for one-dimensional arrays.

Creating the array is simple: using a dynamic-allocation routine like fftw_malloc, allocate an array big enough to store N fftw_complex values (for a complex DFT), where N is the product of the sizes of the array dimensions (i.e. the total number of complex values in the array). For example, here is code to allocate a 5 * 12 * 27 rank-3 array:

.. code-block:: c

     fftw_complex *an_array;
     an_array = (fftw_complex*) fftw_malloc(5*12*27 * sizeof(fftw_complex));

Accessing the array elements, however, is more tricky—you can't simply use multiple applications of the ‘[]’ operator like you could for fixed-size arrays. Instead, you have to explicitly compute the offset into the array using the formula given earlier for row-major arrays. For example, to reference the (i,j,k)-th element of the array allocated above, you would use the expression an_array[k + 27 * (j + 12 * i)].

comment: 只是索引元素的时候不那么方便了。不过定一个宏就解决了吧。C++的话就重定义一下()呗。

This pain can be alleviated somewhat by defining appropriate macros, or, in C++, creating a class and overloading the ‘()’ operator. The recent C99 standard provides a way to reinterpret the dynamic array as a “variable-length” multi-dimensional array amenable to ‘[]’, but this feature is not yet widely supported by compilers.

Dynamic Arrays in C—The Wrong Way
------------------------------------------------------------

A different method for allocating multi-dimensional arrays in C is often suggested that is incompatible with FFTW: using it will cause FFTW to die a painful death. We discuss the technique here, however, because it is so commonly known and used. This method is to create arrays of pointers of arrays of pointers of ...etcetera. For example, the analogue in this method to the example above is:

.. code-block:: c

     int i,j;
     fftw_complex ***a_bad_array;  /* another way to make a 5x12x27 array */
     
     a_bad_array = (fftw_complex ***) malloc(5 * sizeof(fftw_complex **));
     for (i = 0; i < 5; ++i) {
          a_bad_array[i] =
             (fftw_complex **) malloc(12 * sizeof(fftw_complex *));
          for (j = 0; j < 12; ++j)
               a_bad_array[i][j] =
                     (fftw_complex *) malloc(27 * sizeof(fftw_complex));
     }


comment: 严重注意这种方式不能用。

As you can see, this sort of array is inconvenient to allocate (and deallocate). On the other hand, it has the advantage that the (i,j,k)-th element can be referenced simply by a_bad_array[i][j][k].

If you like this technique and want to maximize convenience in accessing the array, but still want to pass the array to FFTW, you can use a hybrid method. Allocate the array as one contiguous block, but also declare an array of arrays of pointers that point to appropriate places in the block. That sort of trick is beyond the scope of this documentation; for more information on multi-dimensional arrays in C, see the comp.lang.c `FAQ <http://c-faq.com/aryptr/dynmuldimary.html>`_ .

comment: 实在是嫌索引不够方便，可以先分配内存再把指针指向所在位置。`FAQ <http://c-faq.com/aryptr/dynmuldimary.html>`_ .
