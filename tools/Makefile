CFLAGS=-I inculde -Wall 

all: headercompile  exr

headerCompile:
	gcc -o ./build/headercompile headercompile.c

ex:
	gcc -o ./build/exprmnt exprmnt.c

h:
	./build/headercompile

vh:
	valgrind ./build/headercompile | less

e: 
	./build/exprmnt
