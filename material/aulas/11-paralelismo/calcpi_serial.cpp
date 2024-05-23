#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

double calcpi(int n) {
    double pi = 0;
    double delta = 1.0 / n;
    for (int i = 0; i < n; i++) {
        double x = (i + 0.5) * delta;
        pi += 4.0 / (1.0 + x * x);
    }
    return pi * delta;
}

int main() {
    int n = 1000000000;
    auto start = high_resolution_clock::now();
    double pi = calcpi(n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << pi << "\n";
    cout << "Time taken: " << duration.count() << "ms\n";
}