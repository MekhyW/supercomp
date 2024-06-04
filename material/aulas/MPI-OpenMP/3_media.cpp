#include <iostream>
#include <vector>
#include <mpi.h>
#include <omp.h>
#include <chrono>

int main(int argc, char* argv[]) {

    auto start = std::chrono::high_resolution_clock::now();

    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 1000000000; // Total de numeros
    const int local_N = N / size; // Elementos por processo (máquina)

    // Aloca memória para o vetor local 
    std::vector<double> local_data(local_N);

    // Inicializa o vetor local. Para simplificar, usaremos o índice.
    for (int i = 0; i < local_N; i++) {
        local_data[i] = i + rank * local_N;
    }

    double local_sum = 0.0;

    // Usa OpenMP para calcular a soma local 
    #pragma omp parallel for reduction(+:local_sum)
    for (int i = 0; i < local_N; i++) {
        local_sum += local_data[i];
    }

    // Reúne todas as somas locais para calcular a soma global
    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Calcula a média no processo principal 
    if (rank == 0) {
        double average = global_sum / N;
        std::cout << "The average is " << average << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
