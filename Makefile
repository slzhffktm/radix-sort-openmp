all: radix.omp.cxx
	g++ -g -Wall radix.omp.cxx -o main -fopenmp

without: radixsort.cxx
	g++ -o main radixsort.cxx

test: coba.cxx
	g++ -g -Wall coba.cxx -o main -fopenmp
