#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <random>

// Merge function used in manual parallel merge sort
void merge(std::vector<int>& data, int left, int mid, int right) {
    std::vector<int> temp;
    int i = left, j = mid;
    while (i < mid && j < right) {
        if (data[i] <= data[j])
            temp.push_back(data[i++]);
        else
            temp.push_back(data[j++]);
    }
    while (i < mid)
        temp.push_back(data[i++]);
    while (j < right)
        temp.push_back(data[j++]);
    std::copy(temp.begin(), temp.end(), data.begin() + left);
}

// Recursive merge sort that spawns threads for parallelism up to a certain depth
void parallel_merge_sort(std::vector<int>& data, int left, int right, int depth = 0) {
    const int threshold = 10000; // below threshold, use std::sort directly
    if (right - left <= 1)
        return;
    if (right - left < threshold) {
        std::sort(data.begin() + left, data.begin() + right);
        return;
    }
    int mid = left + (right - left) / 2;
    // Spawn a new thread for the left half if the recursion depth is low
    if (depth < 2) {
        std::thread left_thread(parallel_merge_sort, std::ref(data), left, mid, depth + 1);
        parallel_merge_sort(data, mid, right, depth + 1);
        left_thread.join();
    } else {
        parallel_merge_sort(data, left, mid, depth + 1);
        parallel_merge_sort(data, mid, right, depth + 1);
    }
    merge(data, left, mid, right);
}

// Utility function to check if the vector is sorted
bool is_sorted(const std::vector<int>& data) {
    return std::is_sorted(data.begin(), data.end());
}

int main() {
    const size_t n = 1000000; // Number of elements to sort
    std::vector<int> data(n);

    // Fill vector with random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (auto& x : data)
        x = dis(gen);

    auto start = std::chrono::high_resolution_clock::now();

    // Sorting using manual parallel merge sort
    parallel_merge_sort(data, 0, data.size());

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_seconds = std::chrono::duration<double>(end - start).count();

    std::cout << "Manual thread sort completed in " << elapsed_seconds << " seconds.\n";
    std::cout << "Data sorted: " << (is_sorted(data) ? "Yes" : "No") << "\n";

    return 0;
}
