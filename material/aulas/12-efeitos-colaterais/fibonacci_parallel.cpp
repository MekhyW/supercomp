#include <iostream>
#include <omp.h>
#include <math.h>
using namespace std;

int fibonacci(int n) {
    int x, y;
    if (n < 2) { return n; }
    if (n < 20) { return fibonacci(n - 1) + fibonacci(n - 2); } 
    else {
        #pragma omp task shared(x)
        x = fibonacci(n - 1);
        #pragma omp task shared(y)
        y = fibonacci(n - 2);
        #pragma omp taskwait
        return x + y;
    }
}

int main() {
    int n = 40;
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        cout << "Fibonacci(" << n << ") = " << fibonacci(n) << endl;
    }
    double end = omp_get_wtime();
    cout << "Time: " << end - start << "s" << endl;
    return 0;
}