****************************************
SWIG wrap c++ into python
****************************************

`SWIG <http://www.swig.org/>`_ 是一个简单快捷地封装C/C++成更高级的语言的软件。它可以将
C/C++ 封装成包括Perl, PHP, Python, Tcl and Ruby在内的各种高级语言。

这里我整理一个linux下如何将C++封装成python的简单例子。

例子里有如下几个文件::

 example.i
 example.cxx
 example.h
 Makefile


example.i里面定义了封装后的python包里的函数和类。
example.h 和example.cxx是一个完整的C++程序包, 这里面的函数以及类不一定要在example.i里面出现。
也就是说example.i里面只要写上我们在python里面要用的函数和类就够了。

如果你想要封装的是一个复杂的C++ API，而使用的过程中又不需要整个API的所有功能，那么就可以自己写一个c++类调用你要用
的API，然后把自己的这个类封装成python包。这就体现了python的一个特性——“胶水语言”。

据说用SWIG封装可能会降低代码的执行效率，如果考虑效率的话那就只好用标准的更底层的封装方法了。那样的话需要大量的重写你的代码。


example.i

.. literalinclude:: src/example.i
		    :language: c++

example.cxx

.. literalinclude:: src/example.cxx
		    :language: c++


example.h

.. literalinclude:: src/example.h
		    :language: c++

Makefile

.. literalinclude:: src/Makefile

