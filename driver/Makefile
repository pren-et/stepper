.PHONY: all syntax doxygen clean

all: build syntax doxygen

build:
	gcc -Wall -Wparentheses -D PL_PC -c main.c drv/l6480.c
	gcc main.o l6480.o -lm -o main.out

run:
	./main.out

syntax: 
	gcc -Wall -Wparentheses -c drv/l6480.c -fsyntax-only

doxygen:
	doxygen l6480.doxyfile

clean:
	rm -rf html/
	rm -rf latex/
	rm -rf *.o
	rm -rf *.out
