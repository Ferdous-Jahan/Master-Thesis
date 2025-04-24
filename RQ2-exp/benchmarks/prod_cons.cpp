#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> q;
bool done = false;

void producer(int items) {
    for (int i = 0; i < items; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        q.push(i);
        lock.unlock();
        cv.notify_one();
    }

    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    cv.notify_all();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !q.empty() || done; });

        if (q.empty() && done)
            break;

        int item = q.front();
        q.pop();
        lock.unlock();

        // Simulate processing
    }
}

int main() {
    std::thread prod(producer, 100000);
    std::thread cons(consumer);

    prod.join();
    cons.join();

    std::cout << "Producer-consumer scenario completed.\n";
}
