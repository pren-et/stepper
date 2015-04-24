.PHONY: all syntax doxygen clean

all: build syntax doxygen

build:
	gcc -Wall -Wparentheses -c main.c
	gcc -Wall -Wparentheses -c l6480.c
	gcc main.o l6480.o -lm -o main

run:
	./main

syntax: 
	gcc -Wall -Wparentheses -c l6480.c -fsyntax-only

doxygen:
	doxygen l6480.doxyfile

clean:
	rm -rf html/
	rm -rf latex/
	rm -rf *.o
