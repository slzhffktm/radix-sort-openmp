#include "omp.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

// declaration
void radix(int);
void print_vector(vector<int>);

// global variables
vector<int> input;

void rng(int* arr, int n) {
    int seed = 13516121; // Ganti dengan NIM anda sebagai seed.
    srand(seed);
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
    }
}

void radix(int thread_count) {
    int done = 0;
    int size = input.size();
 
    vector<vector<vector<int>>> buckets(thread_count, vector<vector<int>>(10));
    
    chrono::steady_clock sc;   // create an object of `steady_clock` class
    auto start = sc.now();
    
    int m = 10, n = 1;

    while(!done) {
        int i;
        int sum0 = 0;
        
            
        #pragma omp parallel for schedule(static) num_threads(thread_count) reduction(+:sum0)
        for (i = 0; i < size; i++) {
            int id = omp_get_thread_num();
            int idx = (input[i] % m)/(n);
            buckets[id][idx].push_back(input[i]);
            if (idx == 0) sum0++;
        }
        

        if (sum0 == size) break;
        
        input.clear();

        for (int i=0; i<10; i++) {
            for (int j=0; j<thread_count; j++) {
                for (auto it : buckets[j][i]) {
                    input.push_back(it);
                }
                buckets[j][i].clear();
            }
        }

        m *= 10;
        n *= 10;
    }

    auto end = sc.now();
    auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
    cout<<"Operation took: "<<time_span.count()<<" seconds";
}

void print_vector(vector<int> v) {
    cout << "[ ";
    for (auto i : v) {
        cout << i << " ";
    }
    cout << "]" << endl;
}

void print_output(vector<int> v) {
    ofstream fout;
    fout.open("output");
    for (auto i : v) {
        fout << i << "\n";
    }
    fout.close();
}

int main(int argc, char *argv[]) {
    int thread_count = strtol(argv[1], NULL, 10);

    int size = 400000;
    int arr[size];

    rng(arr, size);

    for (int i=0; i<size; i++) {
        input.push_back(arr[i]);
    }

    radix(thread_count);

    // print_vector(input);
    print_output(input);

    return 0;
}