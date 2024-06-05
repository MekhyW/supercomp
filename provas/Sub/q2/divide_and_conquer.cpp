#define SEARCH_VALUE 12345
#define RANDOM_NUMBERS_SIZE 1000000

#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

using namespace std;

int main() {
    vector<int> randomNumbers;
    randomNumbers.reserve(RANDOM_NUMBERS_SIZE);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 99999);
    for (int i = 0; i < RANDOM_NUMBERS_SIZE; i++) {
        randomNumbers.push_back(distrib(gen));
    }
    omp_set_num_threads(omp_get_max_threads());
    int totalCount = 0;
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        int nThreads = omp_get_num_threads();
        int chunkSize = randomNumbers.size() / nThreads;
        int startIdx = threadID * chunkSize;
        int endIdx = (threadID == nThreads - 1) ? randomNumbers.size() : startIdx + chunkSize;
        int localCount = 0;
        for (int i = startIdx; i < endIdx; i++) {
            if (randomNumbers[i] == SEARCH_VALUE) { localCount++; }
        }
        #pragma omp critical
        {
            cout << "Thread " << threadID << " found " << SEARCH_VALUE << " " << localCount << " times." << endl;
        }
        #pragma omp critical
        {
            totalCount += localCount;
        }
    }
    cout << "Total count of " << SEARCH_VALUE << " in the vector is " << totalCount << "." << endl;
    return 0;
}
