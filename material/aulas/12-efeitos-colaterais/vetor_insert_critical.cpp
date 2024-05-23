#include <vector>
#include <iostream>
#include <omp.h>

double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 10000; 
    std::vector<double> vec;

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double value = conta_complexa(i);
        #pragma omp critical
        {
            vec.push_back(value);
        }
    }

    for (int i = 0; i < N; i++) {
        std::cout << i << " ";
    }

    return 0;
}
