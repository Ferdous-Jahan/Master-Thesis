#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <random>

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

void parallel_merge_sort(std::vector<int>& data, int left, int right, int depth = 0) {
    const int threshold = 10000;
    if (right - left <= 1)
        return;
    if (right - left < threshold) {
        std::sort(data.begin() + left, data.begin() + right);
        return;
    }
    int mid = left + (right - left) / 2;
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

bool is_sorted(const std::vector<int>& data) {
    return std::is_sorted(data.begin(), data.end());
}

int main() {
    const size_t n = 1000000;
    std::vector<int> data(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (auto& x : data)
        x = dis(gen);

    auto start = std::chrono::high_resolution_clock::now();

    parallel_merge_sort(data, 0, data.size());

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_seconds = std::chrono::duration<double>(end - start).count();

    std::cout << "Manual thread sort completed in " << elapsed_seconds << " seconds.\n";
    std::cout << "Data sorted: " << (is_sorted(data) ? "Yes" : "No") << "\n";

    return 0;
}
