
all: example

clean:
	rm -f example.py example.o  example_wrap.cxx example_wrap.o _example.so example.pyc\

example:example.cxx 
	swig -c++ -python example.i
	g++ -O2 -c -fPIC example.cxx -I../include
	g++ -O2 -c -fPIC  -I/usr/include/python2.7 example_wrap.cxx 
	g++ -shared example.o example_wrap.o -o _example.so 