#include "omp.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    int thread_count = strtol(argv[1], NULL, 10);

    int i;
    #pragma omp parallel num_threads(thread_count)
    {   
        #pragma omp for schedule(static)
        for (i=0; i<=100; i++) {
            int id = omp_get_thread_num();
            
            cout << "t" << id << " p" << i << endl;
        }
        
    }

    return 0;
}