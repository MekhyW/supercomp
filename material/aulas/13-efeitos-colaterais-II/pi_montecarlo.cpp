#include <iostream>
#include <omp.h>
#include <math.h>
using namespace std;

double pi_montecarlo(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        double x = (double) rand() / RAND_MAX;
        double y = (double) rand() / RAND_MAX;
        if (x * x + y * y <= 1) { sum++; }
    }
    return 4.0 * sum / n;
}

int main() {
    int n = 10000000;
    double start = omp_get_wtime();
    cout << "Pi = " << pi_montecarlo(n) << endl;
    double end = omp_get_wtime();
    cout << "Time: " << end - start << "s" << endl;
    return 0;
}