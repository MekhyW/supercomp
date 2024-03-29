#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;

vector<vector<int>> multiplicarMatrizes(const vector<vector<int>>& a, const vector<vector<int>>& b, int start_row, int end_row) {
    int n = a.size();
    int m = a[0].size();
    int p = b[0].size();
    vector<vector<int>> c(n, vector<int>(p, 0));
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < m; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

int main() {
    cout << "Entrada X Tempo" << endl;
    int n_threads = 10;
    for (int tamanho = 10; tamanho <= 500; tamanho += 10) {
        vector<vector<int>> a(tamanho, vector<int>(tamanho, 1));
        vector<vector<int>> b(tamanho, vector<int>(tamanho, 2));
        auto start = high_resolution_clock::now();
        vector<thread> threads(n_threads);
        vector<vector<int>> resultado(tamanho, vector<int>(tamanho, 0));
        int chunk_size = tamanho / n_threads;
        int start_row = 0;
        for (int i = 0; i < n_threads; ++i) {
            int end_row;
            if (i == n_threads - 1) end_row = tamanho;
            else end_row = start_row + chunk_size;
            threads[i] = thread(multiplicarMatrizes, cref(a), cref(b), start_row, end_row);
            start_row = end_row;
        }
        for (int i = 0; i < n_threads; ++i) threads[i].join();
        auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
        cout << tamanho << " " << duration.count() << endl;
    }
    return 0;
}
