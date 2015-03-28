**************************************************
FFTW基本介绍
**************************************************



FFTW 全称是“the Fastest Fourier Transform in the West”。FFTW是一堆高效的离散傅立叶变化的C子程序的集合。

- FFTW 可以计算复数据，实数据，偶对称或奇对称数据的DFT（其中对称变换也就是cos变化和sin变换），以及实数据的离散哈脱莱变换（DHT）。
- 输入数据可以是任意长度的。FFTW对任意长度的数据都是O(n log n)的复杂度，包括素数长度。
- FFTW 支持任意多维的数据。
- FFTW 支持 SSE, SSE2, AVX, Altivec, and MIPS PS 指令集。
- FFTW 3.3 包含了一个支持shared-memory系统的并行变换。不过还没有分布式内存系统的并行变换，计划实现MPI版本。暂时可以使用FFTW 2.1.3 的MPI版本

FFTW 文档中推荐了一本学习FFT相关知识的书：The Fast Fourier Transform and Its Applications by E. O. Brigham (Prentice-Hall, Englewood Cliffs, NJ, 1988). 

FFTW 根据不同的硬件架构使用不同的算法来最大化计算效率。变换过程被分为了两部分：一部分是FFTW的planner根据硬件架构来生成一个计划用一个名为plan的数据结构保存相关信息。然后执行计划来计算变换。对于大量的重复的相同数据规模的变换，值得花更多的时间预优算法。于是，FFTW提供了两种planner。深度预优的和普通的，对于重复次数非常大的情况下，就适合用深度预优的。

FFTW 支持任意的长度，等级？（rank），多样，以及常规的内存分布。对于简单情况，这个普遍性也许是不必要而且令人混乱。于是，他们实现三个层次的FFTW接口，逐步增加普遍性。

- 基本接口计算单纯的一个连续数据的变换
- 高级接口计算多个数组以及条形数组（strided arrays）
- 专家级接口支持几乎所有数据分布，复杂性，以及各种条形。

- The basic interface computes a single transform of contiguous data.
- The advanced interface computes transforms of multiple or strided arrays.
- The guru interface supports the most general data layouts, multiplicities, and strides.

基本接口基本上可以满足所有用户，而专家级接口需要非常小心的阅读文档才能避免出错。

另外，除了自动优化算法外，对于高级用户还可以自己优化算法。例如，FFTW只是对规模能分解为（2，3，5，7）的时候做了特殊处理，对于其他所有规模都用一个相对不那么高效的算法。如果你需要针对其他规模的高效算法，可以考虑利用能自动生成程序的FFTW代码生成器（code generator）。比如，例如需要计算513=19*33的时候，你就可以自定义自己的程序去支持因子为19的高效程序。

For more information regarding FFTW, see the paper, “The Design and Implementation of FFTW3,” by M. Frigo and S. G. Johnson, which was an invited paper in Proc. IEEE 93 (2), p. 216 (2005). The code generator is described in the paper “A fast Fourier transform compiler”, by M. Frigo, in the Proceedings of the 1999 ACM SIGPLAN Conference on Programming Language Design and Implementation (PLDI), Atlanta, Georgia, May 1999. These papers, along with the latest version of FFTW, the FAQ, benchmarks, and other links, are available at the FFTW home page.

The current version of FFTW incorporates many good ideas from the past thirty years of FFT literature. In one way or another, FFTW uses the `Cooley-Tukey algorithm <http://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm>`_ , the prime factor algorithm,  `Rader's algorithm <http://en.wikipedia.org/wiki/Rader's_FFT_algorithm>`_ for prime sizes, and a `split-radix algorithm <http://en.wikipedia.org/wiki/Split-radix_FFT_algorithm>`_ (with a “conjugate-pair” variation pointed out to us by `Dan Bernstein <http://en.wikipedia.org/wiki/Daniel_J._Bernstein>`_ ). FFTW's code generator also produces new algorithms that we do not completely understand. The reader is referred to the cited papers for the appropriate references.



