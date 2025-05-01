#include <iostream>
#include <vector>
#include <pthread.h>
#include <random>
#include <chrono>

using Matrix = std::vector<std::vector<double>>;

struct ThreadData
{
    const Matrix *A;
    const Matrix *B;
    Matrix *C;
    size_t start_row;
    size_t end_row;
};

Matrix generate_matrix(size_t rows, size_t cols)
{
    Matrix mat(rows, std::vector<double>(cols));
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist(0.0, 10.0);
    for (auto &row : mat)
        for (auto &val : row)
            val = dist(gen);
    return mat;
}

void *multiply_worker(void *arg)
{
    ThreadData *data = static_cast<ThreadData *>(arg);
    size_t cols = data->B->at(0).size();
    size_t inner = data->B->size();
    for (size_t i = data->start_row; i < data->end_row; ++i)
        for (size_t j = 0; j < cols; ++j)
            for (size_t k = 0; k < inner; ++k)
                data->C->at(i)[j] += data->A->at(i)[k] * data->B->at(k)[j];
    return nullptr;
}

Matrix pthread_multiply(const Matrix &A, const Matrix &B, size_t num_threads)
{
    size_t rows = A.size();
    Matrix C(rows, std::vector<double>(B[0].size(), 0.0));
    std::vector<pthread_t> threads(num_threads);
    std::vector<ThreadData> thread_data(num_threads);
    size_t rows_per_thread = rows / num_threads;
    size_t extra = rows % num_threads;
    size_t start = 0;

    for (size_t t = 0; t < num_threads; ++t)
    {
        size_t end = start + rows_per_thread + (t < extra ? 1 : 0);
        thread_data[t] = {&A, &B, &C, start, end};
        pthread_create(&threads[t], nullptr, multiply_worker, &thread_data[t]);
        start = end;
    }

    for (auto &thread : threads)
        pthread_join(thread, nullptr);

    return C;
}

int main()
{
    const size_t size = 500;
    Matrix A = generate_matrix(size, size);
    Matrix B = generate_matrix(size, size);
    size_t num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0)
        num_threads = 4;

    auto start = std::chrono::high_resolution_clock::now();
    Matrix C = pthread_multiply(A, B, num_threads);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Matrix multiplication (pthreads) took "
              << std::chrono::duration<double>(end - start).count() << " seconds.\n";
    return 0;
}
