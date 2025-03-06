#include <algorithm>
#include <execution>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

// Utility function to check if the vector is sorted
bool is_sorted(const std::vector<int>& data) {
    return std::is_sorted(data.begin(), data.end());
}

int main() {
    const size_t n = 1000000; // Number of elements to sort
    std::vector<int> data(n);

    // Fill vector with random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (auto& x : data)
        x = dis(gen);

    auto start = std::chrono::high_resolution_clock::now();

    // Sorting using C++17 execution policy (parallel sort)
    std::sort(std::execution::par, data.begin(), data.end());

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_seconds = std::chrono::duration<double>(end - start).count();

    std::cout << "Parallel policy sort completed in " << elapsed_seconds << " seconds.\n";
    std::cout << "Data sorted: " << (is_sorted(data) ? "Yes" : "No") << "\n";

    return 0;
}
