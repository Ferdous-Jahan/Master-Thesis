#include "StdThreadParallelForAPI.hpp"
#include <iostream> // For debugging output
#include <algorithm> // For std::min/max

// Helper to get a default number of threads
unsigned int get_default_std_threads() {
    unsigned int n = std::thread::hardware_concurrency();
    return n == 0 ? 1 : n; // Return 1 if hardware_concurrency is not available or 0
}

StdThreadParallelForAPI::StdThreadParallelForAPI(int nThreads)
    : main_thread_id_(std::this_thread::get_id()) {
    thread_id_to_int_map_[main_thread_id_] = 0; // Main thread gets ID 0
    int num = (nThreads <= 0) ? get_default_std_threads() : nThreads;
    setNumThreads(num);
}

StdThreadParallelForAPI::~StdThreadParallelForAPI() {
    stop_all_threads();
}

void StdThreadParallelForAPI::stop_all_threads() {
    if (workers_.empty() && !stop_threads_flag_) return; // Already stopped or never started

    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_threads_flag_ = true;
        // Clear pending tasks if any, as threads are stopping
        std::queue<std::function<void()>> empty_queue;
        std::swap(task_queue_, empty_queue);
    }
    worker_condition_.notify_all(); // Wake up all workers to check stop_threads_flag_

    for (std::thread& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    workers_.clear();
    configured_num_threads_ = 0;
}

void StdThreadParallelForAPI::start_threads(int n) {
    if (n <= 0) return;
    stop_threads_flag_ = false; // Reset stop flag
    configured_num_threads_ = n;
    for (int i = 0; i < n; ++i) {
        // Worker ID for mapping is i + 1 (0 is main thread)
        workers_.emplace_back(&StdThreadParallelForAPI::worker_loop, this, i);
    }
}

void StdThreadParallelForAPI::worker_loop(int worker_id) {
    // Register this worker thread's ID
    {
        std::unique_lock<std::mutex> lock(thread_id_map_mutex_);
        thread_id_to_int_map_[std::this_thread::get_id()] = worker_id + 1;
    }

    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            worker_condition_.wait(lock, [this] {
                return stop_threads_flag_.load() || !task_queue_.empty();
            });

            if (stop_threads_flag_.load() && task_queue_.empty()) {
                return; // Exit worker loop
            }
            if (task_queue_.empty()) { // Spurious wakeup and not stopping
                continue;
            }

            task = std::move(task_queue_.front());
            task_queue_.pop();
        }
        task(); // Execute the captured lambda (which calls body_callback and decrements tasks_in_current_job_)
    }
}

void StdThreadParallelForAPI::parallel_for(int N, FN_parallel_for_body_cb_t body_callback, void* callback_data) {
    if (N <= 0) return;

    int num_threads = configured_num_threads_;
    if (num_threads <= 0 || workers_.empty() || N < num_threads) {
        // Fallback to sequential execution
        body_callback(0, N, callback_data);
        return;
    }

    // Stripe the work
    int stripe_size = (N + num_threads - 1) / num_threads;
    int num_stripes = (N + stripe_size - 1) / stripe_size;

    tasks_in_current_job_ = num_stripes;

    for (int t = 0; t < num_stripes; ++t) {
        int start = t * stripe_size;
        int end = std::min(N, start + stripe_size);
        if (start >= end) continue;
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            task_queue_.emplace([this, start, end, body_callback, callback_data]() {
                body_callback(start, end, callback_data);
                if (tasks_in_current_job_.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                    main_condition_.notify_one();
                }
            });
        }
        worker_condition_.notify_one();
    }

    // Wait for all tasks of the current job to complete
    std::mutex dummy_main_mutex_for_cv_wait;
    std::unique_lock<std::mutex> main_lock(dummy_main_mutex_for_cv_wait);
    main_condition_.wait(main_lock, [this] {
        return tasks_in_current_job_.load(std::memory_order_acquire) == 0;
    });
}

int StdThreadParallelForAPI::getNumThreads() const {
    return configured_num_threads_;
}

int StdThreadParallelForAPI::setNumThreads(int nThreads) {
    int num_to_set = (nThreads <= 0) ? get_default_std_threads() : nThreads;

    if (num_to_set == configured_num_threads_ && !workers_.empty()) { // No change and already initialized
        return configured_num_threads_;
    }

    stop_all_threads(); // Stop existing threads and clear queue
    start_threads(num_to_set); // Start new threads

    return configured_num_threads_;
}

const char* StdThreadParallelForAPI::getName() const {
    return backend_name_.c_str();
}

int StdThreadParallelForAPI::getThreadNum() const {
    std::thread::id current_id = std::this_thread::get_id();
    std::unique_lock<std::mutex> lock(thread_id_map_mutex_); // Protect map access
    auto it = thread_id_to_int_map_.find(current_id);
    if (it != thread_id_to_int_map_.end()) {
        return it->second;
    }
    // This should ideally not be reached if called from within a task
    // executed by a worker or from the main thread that set up the backend.
    // If an entirely different external thread calls this, it's "unknown".
    return -1; // Indicate unknown thread
}