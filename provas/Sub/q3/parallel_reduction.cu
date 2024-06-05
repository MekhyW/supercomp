#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/reduce.h>

int main() {
    std::srand(std::time(nullptr));
    const size_t N = 200000;
    thrust::host_vector<int> h_vec(N);
    for (size_t i = 0; i < N; ++i) {
        h_vec[i] = std::rand() % 100;
    }
    thrust::device_vector<int> d_vec = h_vec;
    int sum = thrust::reduce(d_vec.begin(), d_vec.end(), 0, thrust::plus<int>());
    std::cout << "Sum of elements: " << sum << std::endl;
    return 0;
}
