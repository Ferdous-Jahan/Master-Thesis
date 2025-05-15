#ifndef STD_THREAD_PARALLEL_FOR_API_HPP
#define STD_THREAD_PARALLEL_FOR_API_HPP

#include <opencv2/core/parallel/parallel_backend.hpp>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <string>
#include <map> // For thread ID mapping

// Forward declaration for a helper or assume cv::utils::getConfigurationParameterSizeT is available
// For simplicity, we'll define a local helper if needed or use std::thread::hardware_concurrency.
unsigned int get_default_std_threads();


class StdThreadParallelForAPI : public cv::parallel::ParallelForAPI {
public:
    StdThreadParallelForAPI(int nThreads = 0);
    ~StdThreadParallelForAPI() override;

    void parallel_for(int tasks, FN_parallel_for_body_cb_t body_callback, void* callback_data) override;
    int getThreadNum() const override;
    int getNumThreads() const override;
    int setNumThreads(int nThreads) override;
    const char* getName() const override;

private:
    void worker_loop(int worker_id);
    void start_threads(int n);
    void stop_all_threads();

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> task_queue_;

    std::mutex queue_mutex_;
    std::condition_variable worker_condition_; // For workers to wait on tasks
    std::condition_variable main_condition_;   // For main thread to wait on completion of all tasks in a parallel_for call

    std::atomic<bool> stop_threads_flag_{false};
    std::atomic<int> tasks_in_current_job_{0}; // Counts tasks for the current parallel_for call
    int configured_num_threads_ = 0;
    const std::string backend_name_ = "StdThread";

    // For getThreadNum()
    std::thread::id main_thread_id_;
    // To map std::thread::id to a simple int for getThreadNum()
    mutable std::mutex thread_id_map_mutex_;
    mutable std::map<std::thread::id, int> thread_id_to_int_map_;
    // 0 for main thread, worker_id + 1 for workers
};

#endif // STD_THREAD_PARALLEL_FOR_API_HPP