CFLAGS=-I inculde -Wall -Wextra

all: buildheaders

buildheaders:
	gcc -o ./build/headercompile headercompile.c

hb:
	./build/headercompile

vhb:
	valgrind ./build/headercompile
