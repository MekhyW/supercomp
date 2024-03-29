#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;

bool subsetSum(const vector<int>& set, int sum) {
    vector<int> sortedSet = set;
    sort(sortedSet.begin(), sortedSet.end(), greater<int>());
    int currentSum = 0;
    for (int i = 0; i < sortedSet.size(); ++i) {
        if (currentSum + sortedSet[i] <= sum) {
            currentSum += sortedSet[i];
            if (currentSum == sum) return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    vector<int> set;
    for (int i = 1; i < argc - 1; ++i) set.push_back(atoi(argv[i]));
    int targetSum = atoi(argv[argc - 1]);
    auto start = high_resolution_clock::now();
    if (subsetSum(set, targetSum)) cout << "Encontrei um subset com soma " << targetSum << endl;
    else cout << "Nao encontrei um subset com soma " << targetSum << endl;
    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
    cout << "Tempo de execucao: " << duration.count() << " microsegundos" << endl;
    return 0;
}
