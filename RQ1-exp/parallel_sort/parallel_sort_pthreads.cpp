#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <pthread.h>
#include <random>

struct SortData
{
    std::vector<int> *data;
    int left;
    int right;
    int depth;
};

void merge(std::vector<int> &data, int left, int mid, int right)
{
    std::vector<int> temp;
    int i = left, j = mid;
    while (i < mid && j < right)
        temp.push_back((data[i] <= data[j]) ? data[i++] : data[j++]);
    while (i < mid)
        temp.push_back(data[i++]);
    while (j < right)
        temp.push_back(data[j++]);
    std::copy(temp.begin(), temp.end(), data.begin() + left);
}

void *parallel_merge_sort(void *arg)
{
    SortData *params = static_cast<SortData *>(arg);
    int left = params->left;
    int right = params->right;
    int depth = params->depth;
    std::vector<int> &data = *(params->data);

    const int threshold = 10000;
    if (right - left <= 1)
        return nullptr;

    if (right - left < threshold)
    {
        std::sort(data.begin() + left, data.begin() + right);
        return nullptr;
    }

    int mid = left + (right - left) / 2;
    if (depth < 2)
    {
        pthread_t thread_left;
        SortData left_data{&data, left, mid, depth + 1};
        pthread_create(&thread_left, nullptr, parallel_merge_sort, &left_data);

        SortData right_data{&data, mid, right, depth + 1};
        parallel_merge_sort(&right_data);

        pthread_join(thread_left, nullptr);
    }
    else
    {
        SortData left_data{&data, left, mid, depth + 1};
        SortData right_data{&data, mid, right, depth + 1};
        parallel_merge_sort(&left_data);
        parallel_merge_sort(&right_data);
    }

    merge(data, left, mid, right);
    return nullptr;
}

bool is_sorted(const std::vector<int> &data)
{
    return std::is_sorted(data.begin(), data.end());
}

int main()
{
    const size_t n = 1000000;
    std::vector<int> data(n);
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (auto &x : data)
        x = dis(gen);

    SortData initial_data{&data, 0, static_cast<int>(data.size()), 0};

    auto start = std::chrono::high_resolution_clock::now();
    parallel_merge_sort(&initial_data);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Pthread parallel merge sort completed in "
              << std::chrono::duration<double>(end - start).count() << " seconds.\n";
    std::cout << "Data sorted: " << (is_sorted(data) ? "Yes" : "No") << "\n";

    return 0;
}
