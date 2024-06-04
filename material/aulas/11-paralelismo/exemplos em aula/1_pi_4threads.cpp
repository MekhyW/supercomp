#include <chrono>
#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std; 

float pi_sobre_4[] = {};

int main() {
    
    int N = 1000000000;
    auto start = std::chrono::high_resolution_clock::now();
    int nthreads;
    #pragma omp parallel
    {

        int id = omp_get_thread_num();  
        nthreads = omp_get_num_threads();  
        int chunk_size = N / nthreads;  
        int istart = id * chunk_size;  
        int iend = (id + 1) * chunk_size;  

        #pragma omp critical
        cout << "Estou na thread: " << id << endl;

        // Ajuste para a última thread
        if (id == nthreads - 1) {
            iend = N;
        }

        // Preenchimento do vetor
        for (int i = istart; i < iend; i++) {
            pi_sobre_4[id] += ((pow(-1, i)) / (2 * i + 1));
        }
    } 

    // Soma as partes   
    float pi = 0; 
    for (int k=0; k<nthreads; k++) {
        pi += pi_sobre_4[k];
    }
    pi = pi * 4;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    cout << "pi ~= " << pi << endl;

    return 0; 
}