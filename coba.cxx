#include "omp.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    int thread_count = strtol(argv[1], NULL, 10);

    // int i;
    #pragma omp parallel num_threads(thread_count)
    {
        for (int i=0; i<=10; i++) {
            int id = omp_get_thread_num();

            cout << "thread " << id << " prints " << i << endl;
        }
        
    }

    return 0;
}