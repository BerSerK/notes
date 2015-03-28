CC=gcc
CFLAGS=-lfftw3 -lm -g
OBJS=complex_1d.o

all: $(OBJS)

%.o: %.c
	$(CC) $< -o $@ $(CFLAGS) 

clean:
	rm -rf *o 
