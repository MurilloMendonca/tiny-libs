.PHONY: all

all: test

test: test-dyn-array test-sort-n-search test-logger

test-dyn-array: test-dyn-array-c test-dyn-array-cpp

test-dyn-array-c: test-dyn-array.c dyn-array.h
	cc -std=c89 test-dyn-array.c -o test-dyn-array-c

test-dyn-array-cpp:test-dyn-array.cpp dyn-array.hpp dyn-array.h
	g++ -Wno-pointer-arith -std=c++17 test-dyn-array.cpp -o test-dyn-array-cpp

test-sort-n-search: test-sort-n-search.c sort-n-search.h
	cc -std=c89 test-sort-n-search.c -o test-sort-n-search

test-logger: test-logger.c logger.h
	cc -std=c89 test-logger.c -o test-logger

run-tests: test
	./test-dyn-array-c
	./test-dyn-array-cpp
	./test-sort-n-search
	./test-logger

clear:
	rm test-dyn-array-c test-dyn-array-cpp test-sort-n-search test-logger
clean: clear

.SUFFIXES:
