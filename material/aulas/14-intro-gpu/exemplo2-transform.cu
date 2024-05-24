#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>

int main() {
    // Initialize V1 with a sequence [0, 1, 2, ..., 9]
    thrust::device_vector<double> V1(10, 0);
    thrust::sequence(V1.begin(), V1.end());

    // Initialize V2 with the first 5 elements as 5.5 and the next 5 elements as 10
    thrust::device_vector<double> V2(10, 0);
    thrust::fill(V2.begin(), V2.begin() + 5, 5.5);
    thrust::fill(V2.begin() + 5, V2.end(), 10);

    // Initialize V3 and V4 with 10 elements
    thrust::device_vector<double> V3(10);
    thrust::device_vector<double> V4(10);

    // V3 = V1 + V2
    thrust::transform(V1.begin(), V1.end(), V2.begin(), V3.begin(), thrust::plus<double>());
    // V4 = V1 * 0.5
    thrust::transform(V1.begin(), V1.end(), thrust::constant_iterator<double>(0.5), V4.begin(), thrust::multiplies<double>());

    // Print V1
    printf("V1: ");
    for (thrust::device_vector<double>::iterator i = V1.begin(); i != V1.end(); i++) {
        std::cout << *i << " ";
    }
    printf("\n");

    // Print V2
    printf("V2: ");
    for (thrust::device_vector<double>::iterator i = V2.begin(); i != V2.end(); i++) {
        std::cout << *i << " ";
    }
    printf("\n");

    // Print V3
    printf("V3: ");
    for (thrust::device_vector<double>::iterator i = V3.begin(); i != V3.end(); i++) {
        std::cout << *i << " ";
    }
    printf("\n");

    // Print V4
    printf("V4: ");
    for (thrust::device_vector<double>::iterator i = V4.begin(); i != V4.end(); i++) {
        std::cout << *i << " ";
    }
    printf("\n");
}

