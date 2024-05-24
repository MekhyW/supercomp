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

    const int ARRAY_SIZE = 100;
    vector<int> vetor_numeros(ARRAY_SIZE,10); // vetor com 100 elementos iguais a 10

    // fazer a distribuição 
    int local_size = ARRAY_SIZE / size;
    vector<int> local_vector(local_size);

    // Distrivuir partes do vetor para todos os processos
    MPI_Scatter(vetor_numeros.data(), local_size, MPI_INT,
                local_vector.data(), local_size, MPI_INT,
                0, MPI_COMM_WORLD);
    // após distribuir fazer a lógica

    int local_sum;
    for (int i = 0; i < local_size; i++){
        local_sum += local_vector[i];
    }

    int media_local = local_sum / local_size;

    // criar a lista para recolher tudo
    vector<int> medias_locais(size);
    MPI_Gather(&media_local,1,MPI_INT,
                medias_locais.data(),1,MPI_INT,
                0, MPI_COMM_WORLD);

    MPI_Finalize();
    if (rank == 0) {
        int total_soma_media_locais = 0;
        for (int i = 0; i<size; i++){
            total_soma_media_locais += medias_locais[i];
        }

        double media_global = total_soma_media_locais/size;
        cout << "Media global: " << media_global << endl;

    }


}