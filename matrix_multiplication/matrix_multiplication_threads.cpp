#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

using Matrix = std::vector<std::vector<double>>;

Matrix generate_matrix(size_t rows, size_t cols) {
    Matrix mat(rows, std::vector<double>(cols));
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist(0.0, 10.0);
    for(auto& row : mat)
        for(auto& val : row)
            val = dist(gen);
    return mat;
}

void multiply_worker(const Matrix& A, const Matrix& B, Matrix& C, size_t start, size_t end) {
    size_t cols = B[0].size(), inner = B.size();
    for (size_t i = start; i < end; ++i)
        for (size_t j = 0; j < cols; ++j)
            for (size_t k = 0; k < inner; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

Matrix thread_multiply(const Matrix &A, const Matrix &B, size_t num_threads) {
    size_t rows = A.size();
    Matrix C(rows, std::vector<double>(B[0].size(), 0.0));
    std::vector<std::thread> threads;
    size_t rows_per_thread = rows / num_threads;
    size_t extra = rows % num_threads;
    size_t start = 0;

    for(size_t t = 0; t < num_threads; ++t) {
        size_t end = start + rows_per_thread + (t < extra ? 1 : 0);
        threads.emplace_back(multiply_worker, std::cref(A), std::cref(B), std::ref(C), start, end);
        start = end;
    }
    for(auto& th : threads)
        th.join();

    return C;
}

int main() {
    const size_t size = 500;
    Matrix A = generate_matrix(size, size);
    Matrix B = generate_matrix(size, size);
    size_t num_threads = std::thread::hardware_concurrency();
    if(num_threads == 0) num_threads = 4;

    auto start = std::chrono::high_resolution_clock::now();
    Matrix C = thread_multiply(A, B, num_threads);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Matrix multiplication (manual threading) took " 
              << std::chrono::duration<double>(end-start).count() << " seconds.\n";
    return 0;
}


