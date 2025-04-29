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

void *trivial_task_p(void *arg) { return nullptr; }

void run_thread_create()
{
    const int NUM_THREADS = 1000;
    pthread_t tid;

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_create(&tid, nullptr, trivial_task_p, nullptr);
        pthread_join(tid, nullptr);
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << "Average thread creation overhead (pthreads): "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / NUM_THREADS
              << " µs\n";
}

int main()
{
    run_thread_create();
}