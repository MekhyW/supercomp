#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

bool isSubsetSum(const vector<int>& set, int n, int sum) {
    if (sum == 0) return true;
    if (n == 0) return false;
    if (set[n - 1] > sum) return isSubsetSum(set, n - 1, sum);
    return isSubsetSum(set, n - 1, sum) || isSubsetSum(set, n - 1, sum - set[n - 1]);
}

int main(int argc, char *argv[]) {
    vector<int> set;
    for (int i = 1; i < argc - 1; ++i) set.push_back(atoi(argv[i]));
    int targetSum = atoi(argv[argc - 1]);
    int setSize = set.size();
    auto start = high_resolution_clock::now();
    if (isSubsetSum(set, setSize, targetSum)) cout << "Encontrei um subset com soma " << targetSum << endl;
    else cout << "Nao encontrei um subset com soma " << targetSum << endl;
    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
    cout << "Tempo de execucao: " << duration.count() << " microsegundos" << endl;
    return 0;
}
