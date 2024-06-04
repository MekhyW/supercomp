#include <iostream>
#include <chrono>
#include <math.h>
#include <omp.h>

using namespace std;

double calculate_pi(int num_terms) {
    double pi_over_4 = 0.0;

    #pragma omp parallel
    {
        // Tudo é disparado a partir de uma única thread
        #pragma omp single
        {
            // Para cada thread...
            int Nthrds = omp_get_num_threads();
            for (int id = 0; id < Nthrds; id++) {

                // Obtem o "bloco" a ser trabalhado
                int istart, iend;
                istart = (id) * (num_terms / Nthrds);     
                iend = (id + 1) * (num_terms / Nthrds);   
                if (id == Nthrds - 1)
                    iend = num_terms;

                // Dispara uma task para este bloco
                #pragma omp task 
                {

                    #pragma omp critical
                    cout << "[" << omp_get_thread_num() << "/" << omp_get_num_threads() << "]" << istart << "|" << iend << "|" << endl;

                    double term = 0;
                    for (int i=istart; i<iend; i++) { 
                        term += pow(-1, i) / (2 * i + 1);
                    }
                    
                    #pragma omp critical
                    pi_over_4 += term;
                }
            }
        }
    }

    return 4 * pi_over_4;
}




int main() {
    auto start = std::chrono::high_resolution_clock::now();

    int num_terms = 1000000000;  
    double pi = calculate_pi(num_terms);
    cout << "pi ~=" << pi << endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
