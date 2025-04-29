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

pthread_mutex_t mtx_p = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv_p = PTHREAD_COND_INITIALIZER;
std::queue<int> q_p;
bool done_p = false;

void *producer_p(void *arg)
{
    int items = *(int *)arg;
    for (int i = 0; i < items; ++i)
    {
        pthread_mutex_lock(&mtx_p);
        q_p.push(i);
        pthread_mutex_unlock(&mtx_p);
        pthread_cond_signal(&cv_p);
    }

    pthread_mutex_lock(&mtx_p);
    done_p = true;
    pthread_mutex_unlock(&mtx_p);
    pthread_cond_broadcast(&cv_p);
    return nullptr;
}

void *consumer_p(void *arg)
{
    while (true)
    {
        pthread_mutex_lock(&mtx_p);
        while (q_p.empty() && !done_p)
            pthread_cond_wait(&cv_p, &mtx_p);

        if (q_p.empty() && done_p)
        {
            pthread_mutex_unlock(&mtx_p);
            break;
        }

        int item = q_p.front();
        q_p.pop();
        pthread_mutex_unlock(&mtx_p);
        // Simulate processing
    }
    return nullptr;
}

void run_prod_cons()
{
    pthread_t prod, cons;
    int items = 100000;

    pthread_create(&prod, nullptr, producer_p, &items);
    pthread_create(&cons, nullptr, consumer_p, nullptr);

    pthread_join(prod, nullptr);
    pthread_join(cons, nullptr);

    std::cout << "Producer-consumer scenario completed (pthreads).\n";
}

int main()
{
    run_prod_cons();
}