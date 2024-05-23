#include <vector>
#include <iostream>
#include <omp.h>

double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 10000; 
    std::vector<double> vec(N); // Pre-allocate the vector with size N
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        vec[i] = conta_complexa(i); // Directly assign to each element
    }
    
    for (int i = 0; i < N; i++) {
        std::cout << i << " ";
    }
    
    return 0;
}
