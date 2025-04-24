#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

void parallel_sort(std::vector<int>& data, int threads) {
    std::vector<std::thread> thread_pool;
    std::vector<std::vector<int>> chunks(threads);

    size_t chunk_size = data.size() / threads;

    for (int i = 0; i < threads; ++i) {
        auto start_itr = data.begin() + i * chunk_size;
        auto end_itr = (i == threads - 1) ? data.end() : start_itr + chunk_size;
        chunks[i] = std::vector<int>(start_itr, end_itr);

        thread_pool.emplace_back([&chunks, i]() {
            std::sort(chunks[i].begin(), chunks[i].end());
        });
    }

    for (auto& t : thread_pool)
        t.join();

    // Merge sorted chunks
    auto sorted = chunks[0];
    for (int i = 1; i < threads; ++i) {
        std::vector<int> merged(sorted.size() + chunks[i].size());
        std::merge(sorted.begin(), sorted.end(), chunks[i].begin(), chunks[i].end(), merged.begin());
        sorted = std::move(merged);
    }

    data = std::move(sorted);
}

int main() {
    const size_t SIZE = 10'000'000;
    std::vector<int> data(SIZE);

    std::mt19937 rng(42);
    std::generate(data.begin(), data.end(), rng);

    auto start = std::chrono::steady_clock::now();
    parallel_sort(data, std::thread::hardware_concurrency());
    auto end = std::chrono::steady_clock::now();

    std::cout << "Parallel sort duration: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}
