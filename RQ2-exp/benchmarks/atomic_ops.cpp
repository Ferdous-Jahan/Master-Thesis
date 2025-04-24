#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> atomic_counter{0};

void atomic_increment(int ops) {
    for (int i = 0; i < ops; ++i)
        ++atomic_counter;
}

int main() {
    int threads = 4;
    int ops = 100'000'000;
    std::vector<std::thread> thread_pool;

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < threads; ++i)
        thread_pool.emplace_back(atomic_increment, ops / threads);

    for (auto& t : thread_pool)
        t.join();

    auto end = std::chrono::steady_clock::now();
    std::cout << "Final atomic counter: " << atomic_counter.load() << "\n";
    std::cout << "Atomic increment duration: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}
