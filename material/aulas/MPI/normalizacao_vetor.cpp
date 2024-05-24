#include <iostream>
#include <mpi.h>
#include <vector>
#include <algorithm>
#include <climits>
#include <omp.h>

using namespace std; 

int main (int argc, char *argv[]) {
    MPI_Init (&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int array_size = 100;
    vector<float> number_list(array_size);
    // [é possível paralelizar ]
    // #pragma omp parallel for
    for (int i = 0; i < array_size; i++){
        number_list[i] = i+1;
    }
    int maximo = INT_MIN;
    if (rank == 0){
        // #pragma omp parallel for reduction(max:maximo)       
        for (int i = 0; i < array_size; i++){
            if (number_list[i] > maximo){
                maximo = number_list[i];
            }
        }
        cout << "Esse é o máximo da lista: " << maximo << endl;
    }

    MPI_Bcast(&maximo,1,MPI_INT,0,MPI_COMM_WORLD);
    int local_size = array_size / size;
    vector<float> local_vector(local_size);
    MPI_Scatter(number_list.data(), local_size, MPI_FLOAT,
            local_vector.data(), local_size, MPI_FLOAT,
            0, MPI_COMM_WORLD);

    for (int i = 0; i < local_size; i++) {
        local_vector[i] = local_vector[i] / maximo;
    }

    vector<float> parte_normalizada(array_size);
    MPI_Gather(local_vector.data(),local_size , MPI_FLOAT,
                parte_normalizada.data(), local_size, MPI_FLOAT,
                0, MPI_COMM_WORLD);

    if (rank == 0 ){
        cout << "Esse é o vetor final: ";
        for (int i = 0; i < array_size; i++) {
            cout << parte_normalizada[i] << " ";
        }
        cout << endl;
    }
    MPI_Finalize();
    return 0;
}