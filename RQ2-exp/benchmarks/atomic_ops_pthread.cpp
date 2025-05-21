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

std::atomic<int> atomic_counter_p{0};

void *atomic_increment_p(void *arg)
{
    int ops = *(int *)arg;
    for (int i = 0; i < ops; ++i)
        ++atomic_counter_p;
    return nullptr;
}

void run_atomic_ops()
{
    int threads = 4;
    int ops = 100'000'000;
    pthread_t tid[threads];

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < threads; ++i){
        int* thread_ops = new int(ops / threads);
        pthread_create(&tid[i], nullptr, atomic_increment_p, thread_ops);
    }
    for (int i = 0; i < threads; ++i)
        pthread_join(tid[i], nullptr);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Final atomic counter (pthreads): " << atomic_counter_p.load() << "\n";
    std::cout << "Atomic increment duration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}

int main()
{
    run_atomic_ops();
}