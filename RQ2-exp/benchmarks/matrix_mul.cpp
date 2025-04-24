#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void multiply_block(const std::vector<std::vector<double>>& A, 
                    const std::vector<std::vector<double>>& B, 
                    std::vector<std::vector<double>>& C,
                    size_t start_row, size_t end_row) {
    size_t N = A.size();
    for (size_t i = start_row; i < end_row; ++i)
        for (size_t j = 0; j < N; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < N; ++k)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
}

int main() {
    const size_t N = 1000;
    std::vector<std::vector<double>> A(N, std::vector<double>(N, 1.0));
    std::vector<std::vector<double>> B(N, std::vector<double>(N, 2.0));
    std::vector<std::vector<double>> C(N, std::vector<double>(N, 0.0));

    int threads = std::thread::hardware_concurrency();
    std::vector<std::thread> thread_pool;
    size_t block_size = N / threads;

    auto start = std::chrono::steady_clock::now();

    for (int t = 0; t < threads; ++t) {
        size_t start_row = t * block_size;
        size_t end_row = (t == threads - 1) ? N : start_row + block_size;
        thread_pool.emplace_back(multiply_block, std::cref(A), std::cref(B), std::ref(C), start_row, end_row);
    }

    for (auto& t : thread_pool)
        t.join();

    auto end = std::chrono::steady_clock::now();
    std::cout << "Matrix multiplication duration: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}
