#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int fib(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

int main() {
    int N;
    cout << "Insira o valor de N: ";
    cin >> N;
    auto start = high_resolution_clock::now();
    int result = fib(N);
    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
    cout << "Fibonacci de " << N << " da " << result << endl;
    cout << "Tempo de execucao: " << duration.count() << " microsegundos" << endl;
    return 0;
}
