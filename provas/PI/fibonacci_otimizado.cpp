#include <iostream>
#include <unordered_map>
#include <chrono>
using namespace std;
using namespace std::chrono;
using MemoMap = unordered_map<int, int>;

int fib(int n, MemoMap& memo) {
    if (memo.find(n) != memo.end()) return memo[n];
    if (n <= 1) return n;
    else {
        memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
        return memo[n];
    }
}

int main() {
    int N;
    cout << "Insira o valor de N: ";
    cin >> N;
    MemoMap memo;
    auto start = high_resolution_clock::now();
    int result = fib(N, memo);
    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
    cout << "Fibonacci de " << N << " da " << result << endl;
    cout << "Tempo de execucao: " << duration.count() << " microsegundos" << endl;
    return 0;
}
