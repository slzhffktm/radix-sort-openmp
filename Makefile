all: src/radix.omp.cxx
	g++ -g -Wall src/radix.omp.cxx -o radix_sort -fopenmp

without: src/radixsort.cxx
	g++ -o radix_sort src/radixsort.cxx

test: coba.cxx
	g++ -g -Wall coba.cxx -o main -fopenmp
