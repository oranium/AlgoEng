#include <iostream>
#include <omp.h>
#include "fast_merge_sort.h"
#include <vector>
#include <random>
#include <algorithm>

std::vector<int> get_random_int_vector(int n) {
    std::default_random_engine re{std::random_device{}()};
    std::uniform_int_distribution<int> next_rand{INT32_MIN, INT32_MAX};
    std::vector<int> v(n);
    for (auto &num : v) {
        num = next_rand(re);
    }
    return v;
}

int main(int argc, char *argv[]) {
    const int n = 100000000;
    std::vector<int> v = get_random_int_vector(n);
    std::vector<int> v_copy = v;
    std::vector<int> v_naive = v;
    std::vector<int> buffer(n);
    double start = omp_get_wtime();
    merge_sort_run(v.data(), buffer.data(), n);
    std::cout << "fast merge sort: " << omp_get_wtime() - start << " seconds" << std::endl;

    start = omp_get_wtime();
    std::sort(std::begin(v_copy), std::end(v_copy));
    std::cout << "std::sort: " << omp_get_wtime() - start << " seconds" << std::endl;
    if (v != v_copy) {
        std::cout << "sort implementation is buggy\n";
    }


    start = omp_get_wtime();
    merge_sort_naive(v_naive.data(), n);
    std::cout << "naive merge sort: " << omp_get_wtime() - start << " seconds" << std::endl;
    if (v != v_copy) {
        std::cout << "(naive) sort implementation is buggy\n";
    }
}

