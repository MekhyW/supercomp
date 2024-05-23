#include <iostream>
#include <unistd.h>
#include <chrono>
#include <omp.h>

double funcao1() {
    sleep(4);
    return 47;
}

double funcao2() {
    sleep(1);
    return -11.5;
}

int main() {
    double res_func1, res_func2;

    auto start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            res_func1 = funcao1();

            #pragma omp task
            res_func2 = funcao2();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << res_func1 << " " << res_func2 << "\n";
    std::cout << "Tempo total: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
}