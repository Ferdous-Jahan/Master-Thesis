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

std::vector<std::vector<int>> chunks;

void *sort_chunk(void *arg)
{
    int idx = *(int *)arg;
    std::sort(chunks[idx].begin(), chunks[idx].end());
    return nullptr;
}

void run_parallel_sort()
{
    const size_t SIZE = 10'000'000;
    std::vector<int> data(SIZE);
    std::mt19937 rng(42);
    std::generate(data.begin(), data.end(), rng);

    int threads = sysconf(_SC_NPROCESSORS_ONLN);
    size_t chunk_size = SIZE / threads;
    chunks.resize(threads);

    pthread_t tid[threads];
    std::vector<int> idx(threads);

    for (int i = 0; i < threads; ++i)
    {
        auto start_itr = data.begin() + i * chunk_size;
        auto end_itr = (i == threads - 1) ? data.end() : start_itr + chunk_size;
        chunks[i] = std::vector<int>(start_itr, end_itr);
    }

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < threads; ++i)
    {
        idx[i] = i;
        pthread_create(&tid[i], nullptr, sort_chunk, &idx[i]);
    }

    for (int i = 0; i < threads; ++i)
        pthread_join(tid[i], nullptr);

    // Merge sorted chunks
    auto sorted = chunks[0];
    for (int i = 1; i < threads; ++i)
    {
        std::vector<int> merged(sorted.size() + chunks[i].size());
        std::merge(sorted.begin(), sorted.end(), chunks[i].begin(), chunks[i].end(), merged.begin());
        sorted = std::move(merged);
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << "Parallel sort duration (pthreads): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}

int main()
{
    run_parallel_sort();
}