#include <iostream>
#include <mpi.h>
#include <vector>
#include <algorithm>

using namespace std;

int main (int argc, char *argv[]) {
    MPI_Init (&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int condicao_parada = 5;

    MPI_Bcast(condicao_parada,1,MPI_INT,0,MPI_COMM_WORLD);

    for(int i = 0; i < condicao_parada; i ++){
        cout << "contando o número " << i << " no rank " << rank << endl;
    }

    MPI_Finalize();
    if (rank == 0) {
        cout << "programa inicial, rank : " << rank << " terminando o programa" << endl;
    }
    return 0;
}