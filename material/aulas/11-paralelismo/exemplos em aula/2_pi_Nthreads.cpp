#include <chrono>
#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std; 

int main() {
    
    int N = 1000000000;
    auto start = std::chrono::high_resolution_clock::now();
    float pi_sobre_4 = 0;

    #pragma omp parallel for reduction(+:pi_sobre_4)
    for (int i = 0; i < N; i++) {
        pi_sobre_4 += ((pow(-1, i)) / (2 * i + 1));
    }
    

    // Ajusta o resultado  
    float pi = 0; 
    pi = pi_sobre_4 * 4;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    cout << "pi ~= " << pi << endl;

    return 0; 
}