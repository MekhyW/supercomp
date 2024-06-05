#define BALL 1
#define TERMINATE 0
#define POSSESSION_LIMIT 1000000

#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 2 && rank == 0) {
        cerr << "Must be 2 processes" << endl;
        MPI_Finalize();
        return 1;
    }
    int possession_count = 0;
    int ball = BALL;
    MPI_Status status;
    srand(time(0) + rank);
    if (rank == 0) { MPI_Send(&ball, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); }
    while (1) {
        MPI_Recv(&ball, 1, MPI_INT, (rank + 1) % 2, 0, MPI_COMM_WORLD, &status);
        if (ball == TERMINATE) { break; }
        possession_count++;
        cout << "Rank " << rank << " received ball. Count: " << possession_count << endl;
        if (possession_count >= POSSESSION_LIMIT) {
            double random_value = static_cast<double>(rand()) / RAND_MAX;
            if (random_value <= 0.7) {
                ball = TERMINATE;
                MPI_Send(&ball, 1, MPI_INT, (rank + 1) % 2, 0, MPI_COMM_WORLD);
                break;
            }
        }
        MPI_Send(&ball, 1, MPI_INT, (rank + 1) % 2, 0, MPI_COMM_WORLD);
    }
    cout << "Rank " << rank << " terminating with count: " << possession_count << endl;
    MPI_Finalize();
    return 0;
}
