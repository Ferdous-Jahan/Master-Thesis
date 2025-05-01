#include <vector>
#include <random>
#include <execution>
#include <chrono>
#include <iostream>

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

Matrix parallel_multiply(const Matrix &A, const Matrix &B) {
    size_t rows = A.size(), cols = B[0].size(), inner = B.size();
    Matrix C(rows, std::vector<double>(cols, 0.0));
    std::for_each(std::execution::par_unseq, C.begin(), C.end(), [&](auto& row) {
        size_t i = &row - &C[0];
        for(size_t j = 0; j < cols; j++)
            for(size_t k = 0; k < inner; k++)
                row[j] += A[i][k] * B[k][j];
    });
    return C;
}

int main() {
    size_t N = 500;
    Matrix A = generate_matrix(N, N), B = generate_matrix(N, N);

    auto start = std::chrono::high_resolution_clock::now();
    Matrix C = parallel_multiply(A, B);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Matrix multiplication (par) took " 
              << std::chrono::duration<double>(end-start).count() << " seconds.\n";
}
