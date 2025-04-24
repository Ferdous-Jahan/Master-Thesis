#include <algorithm>
#include <execution>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

bool is_sorted(const std::vector<int>& data) {
    return std::is_sorted(data.begin(), data.end());
}

int main() {
    const size_t n = 1000000;
    std::vector<int> data(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (auto& x : data)
        x = dis(gen);

    auto start = std::chrono::high_resolution_clock::now();

    // Sorting using C++17 execution policy (parallel unsequenced)
    std::sort(std::execution::par_unseq, data.begin(), data.end());

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_seconds = std::chrono::duration<double>(end - start).count();

    std::cout << "Parallel unsequenced policy sort completed in " << elapsed_seconds << " seconds.\n";
    std::cout << "Data sorted: " << (std::is_sorted(data.begin(), data.end()) ? "Yes" : "No") << "\n";

    return 0;
}
