#include <chrono>
#include <iostream>
#include <thread>

void trivial_task() {}

int main() {
    const int NUM_THREADS = 1000;
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < NUM_THREADS; ++i) {
        std::thread t(trivial_task);
        t.join();
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << "Average thread creation overhead: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / NUM_THREADS
              << " µs\n";
}
