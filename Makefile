all: src/radix.omp.cxx
	g++ -g -Wall src/radix.omp.cxx -o radix_sort -fopenmp
