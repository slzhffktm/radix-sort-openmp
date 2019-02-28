#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// declaration
void radix();
void print_vector(vector<int>);

// global variables
vector<vector<int>> bucket(10);
vector<int> input;
int m=10, n=1;

void rng(int* arr, int n) {
    int seed = 13516121; // Ganti dengan NIM anda sebagai seed.
    srand(seed);
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
    }
}

void radix() {
    int done = 0;
    int size = input.size();
    while(!done) {
        // print_vector(input);

        for (auto it : input) {
            int idx = (it % m)/n;
            bucket[idx].push_back(it);
        }
        
        if (bucket[0].size() == size) break;
        
        input.clear();

        for (int i=0; i<10; i++) {
            for (auto it : bucket[i]) {
                input.push_back(it);
            }
            bucket[i].clear();
        }

        m *= 10; n *= 10;
    }
}

void print_vector(vector<int> v) {
    cout << "[ ";
    for (auto i : v) {
        cout << i << " ";
    }
    cout << "]" << endl;
}

int main(void) {
    
    int n = 200000;
    int arr[n];

    rng(arr, n);

    for (int i=0; i<n; i++) {
        input.push_back(arr[i]);
    }

    chrono::steady_clock sc;   // create an object of `steady_clock` class
    auto start = sc.now();
    radix();
    auto end = sc.now();
    auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
    cout<<"Operation took: "<<time_span.count()<<" seconds";

    // print_vector(input);    

    return 0;
}