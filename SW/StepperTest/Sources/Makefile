.PHONY: all syntax doxygen clean

all: syntax doxygen

syntax: 
	gcc -Wall -Wparentheses -c l6480.c -fsyntax-only

doxygen:
	doxygen l6480.doxyfile

clean:
	rm -rf html/
	rm -rf latex/
