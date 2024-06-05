#include <cmath>
#include <iostream>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/host_vector.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/random.h>
#include <thrust/reduce.h>
#include <thrust/transform.h>

// Função para gerar números aleatórios
struct prg {
    float a, b;

    __host__ __device__
    prg(float _a = 0.f, float _b = 1.f) : a(_a), b(_b) {};

    __host__ __device__ float operator()(const unsigned int n) const {
        thrust::default_random_engine rng;
        thrust::uniform_real_distribution<float> dist(a, b);
        rng.discard(n);

        return dist(rng);
    }
};

int main() {
    const int N = 1000000; // Tamanho do vetor
    thrust::counting_iterator<unsigned int> index_sequence_begin(0);

    thrust::host_vector<float> h_vec(N);

    // Preencher o vetor com números aleatórios entre 1.0 e 2.0
    thrust::transform(index_sequence_begin,
                      index_sequence_begin + N,
                      h_vec.begin(),
                      prg(1.f, 2.f));

    // Imprime alguns valores do vetor criado para verificação
    for (int i = 0; i < 20; i++) {
        std::cout << "Elemento original " << i << ": " << h_vec[i] << std::endl;
    }

    // [COMPLETAR] Copia o vetor do host para o dispositivo
    thrust::device_vector<float> d_vec = h_vec;

    // [COMPLETAR] Calcule a norma L2 do vetor
    float norm = 0.0;
    // elevando ao quadrado
    thrust::transform(d_vec.begin(), d_vec.end(), d_vec.begin(), d_vec.begin(), thrust::multiplies<double>());
    for (int i = 0; i < 20; i++) {
        std::cout << "Elemento quadrado " << i << ": " << d_vec[i] << std::endl;
    }
    // reduz a soma
    norm = thrust::reduce(d_vec.begin(), d_vec.end(), 0, thrust::plus<int>());
    std::cout << "soma " << norm << std::endl;

    // tira a raiz
    norm = sqrt(norm);

    // Imprime a norma calculada
    std::cout << "Norma calculada : " << norm << std::endl;

    // [COMPLETAR] Normalize o vetor dividindo cada elemento pela norma L2

    // Imprime alguns valores do vetor normalizado para verificação
    // for (int i = 0; i < 20; i++) {
    //     std::cout << "Elemento normalizado " << i << ": " << d_vec[i] << std::endl;
    // }
    return 0;
}