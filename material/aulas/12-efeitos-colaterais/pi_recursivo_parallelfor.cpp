#include <omp.h>
#include <iostream>
#include <iomanip>

static long num_steps = 1024l*1024*102*2;
#define MIN_BLK  1024*1024*256

double sum = 0;

int main() {
    long i;
    double step, pi;
    double init_time, final_time;

    step = 1.0 / (double) num_steps;
    init_time = omp_get_wtime();

    #pragma omp parallel
    {
        double thread_sum = 0;
        #pragma omp for schedule(static)
        for (i = 0; i < num_steps; i++) {
            double x = (i + 0.5) * step;
            thread_sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp atomic
        sum += thread_sum;
    }

    pi = step * sum;
    final_time = omp_get_wtime() - init_time;

    std::cout << "for " << num_steps << " steps pi = " << std::setprecision(15) << pi << " in " << final_time << " secs\n";
    return 0;
}
