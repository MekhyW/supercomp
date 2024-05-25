#include <iostream>
#include <mpi.h>
#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int ARRAY_SIZE = 100000;
    int array[ARRAY_SIZE];

    if (rank == 0) {
#pragma parallel for
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = i;
        }
    }

    int chunk_size = ARRAY_SIZE / size;
    int recv_array[chunk_size];

    MPI_Scatter(array, chunk_size, MPI_INT, recv_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    long soma_local = 0;
#pragma parallel for reduction(+ : soma_local)
    for (int i = 0; i < chunk_size; i++) {
        soma_local += recv_array[i] * recv_array[i];
    }

    long soma_global = 0;
    MPI_Reduce(&soma_local, &soma_global, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "soma global " << soma_global << endl;
    }

    MPI_Finalize();
    return 0;
}