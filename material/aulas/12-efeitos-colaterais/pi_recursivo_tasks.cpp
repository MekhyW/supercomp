#include <omp.h>
#include <iostream>
#include <iomanip>

static long num_steps = 1024l*1024*102*2;
#define MIN_BLK  1024*1024*256

double sum = 0;
omp_lock_t sum_lock;

void pi_r(long Nstart, long Nfinish, double step) {
    long i, iblk;
    if (Nfinish - Nstart < MIN_BLK) {
        double local_sum = 0;
        for (i = Nstart; i < Nfinish; i++) {
            double x = (i + 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }
        omp_set_lock(&sum_lock);
        sum += local_sum;
        omp_unset_lock(&sum_lock);
    } else {
        iblk = (Nfinish - Nstart) / 2;
        #pragma omp task
        pi_r(Nstart, Nstart + iblk, step);
        #pragma omp task
        pi_r(Nstart + iblk, Nfinish, step);
    }
}

int main() {
    double step, pi;
    double init_time, final_time;

    step = 1.0 / (double) num_steps;
    init_time = omp_get_wtime();

    omp_init_lock(&sum_lock);
    #pragma omp parallel
    {
        #pragma omp single
        pi_r(0, num_steps, step);
    }
    omp_destroy_lock(&sum_lock);

    pi = step * sum;
    final_time = omp_get_wtime() - init_time;

    std::cout << "for " << num_steps << " steps pi = " << std::setprecision(15) << pi << " in " << final_time << " secs\n";
    return 0;
}
