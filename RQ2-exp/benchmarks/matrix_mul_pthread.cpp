#include <pthread.h>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <vector>
#include <algorithm>
#include <unistd.h>

struct MatmulArgs
{
    const std::vector<std::vector<double>> *A;
    const std::vector<std::vector<double>> *B;
    std::vector<std::vector<double>> *C;
    size_t start_row;
    size_t end_row;
};

void *multiply_block_p(void *arg)
{
    MatmulArgs *args = (MatmulArgs *)arg;
    size_t N = args->A->size();
    for (size_t i = args->start_row; i < args->end_row; ++i)
        for (size_t j = 0; j < N; ++j)
        {
            double sum = 0.0;
            for (size_t k = 0; k < N; ++k)
                sum += (*(args->A))[i][k] * (*(args->B))[k][j];
            (*(args->C))[i][j] = sum;
        }
    return nullptr;
}

void run_matrix_mul()
{
    const size_t N = 1000;
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 1.0));
    std::vector<std::vector<double>> B(N, std::vector<double>(N, 2.0));
    std::vector<std::vector<double>> C(N, std::vector<double>(N, 0.0));

    int threads = sysconf(_SC_NPROCESSORS_ONLN);
    size_t block_size = N / threads;

    pthread_t tid[threads];
    std::vector<MatmulArgs> args(threads);

    auto start = std::chrono::steady_clock::now();

    for (int t = 0; t < threads; ++t)
    {
        args[t] = {&A, &B, &C, t * block_size, (t == threads - 1) ? N : (t + 1) * block_size};
        pthread_create(&tid[t], nullptr, multiply_block_p, &args[t]);
    }

    for (int t = 0; t < threads; ++t)
        pthread_join(tid[t], nullptr);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Matrix multiplication duration (pthreads): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}

int main()
{
    run_matrix_mul();
}