#include <iostream>
#include <omp.h>
#include <random>
#include <ctime>
using namespace std;

double pi_montecarlo(int n) {
    int sum = 0;
    #pragma omp parallel
    {
        default_random_engine generator(omp_get_thread_num() + time(nullptr));
        uniform_real_distribution<double> distribution(0.0, 1.0);
        int local_sum = 0;
        #pragma omp for
        for (int i = 0; i < n; i++) {
            double x = distribution(generator);
            double y = distribution(generator);
            if (x * x + y * y <= 1) { local_sum++; }
        }
        #pragma omp atomic
        sum += local_sum;
    }
    return 4.0 * sum / n;
}

int main() {
    int n = 10000000;
    double start = omp_get_wtime();
    double pi = pi_montecarlo(n);
    double end = omp_get_wtime();
    cout << "Pi = " << pi << endl;
    cout << "Time: " << end - start << "s" << endl;
    return 0;
}
