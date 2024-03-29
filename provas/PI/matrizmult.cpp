#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

vector<vector<int>> multiplicarMatrizes(const vector<vector<int>>& a,
                                                 const vector<vector<int>>& b) {
    int n = a.size();
    int m = a[0].size();
    int p = b[0].size();
    
    vector<vector<int>> c(n, vector<int>(p, 0));

    for (int i = 0; i < n; ++i) {
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
    for (int tamanho = 10; tamanho <= 500; tamanho += 10) {
        vector<vector<int>> a(tamanho, vector<int>(tamanho, 1));
        vector<vector<int>> b(tamanho, vector<int>(tamanho, 2));
        auto start = high_resolution_clock::now();
        multiplicarMatrizes(a, b);
        auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
        cout << tamanho << " " << duration.count() << endl;
    }
    return 0;
}