.PHONY: all

all: test

test: test-dyn-array

test-dyn-array: test-dyn-array-c test-dyn-array-cpp

test-dyn-array-c: test-dyn-array.c dyn-array.h
	cc -std=c89 test-dyn-array.c -o test-dyn-array-c

test-dyn-array-cpp:test-dyn-array.cpp dyn-array.hpp dyn-array.h
	g++ -Wno-pointer-arith -std=c++17 test-dyn-array.cpp -o test-dyn-array-cpp

run-tests: test
	./test-dyn-array-c
	./test-dyn-array-cpp

clear:
	rm test-dyn-array-c test-dyn-array-cpp
clean: clear

.SUFFIXES:
