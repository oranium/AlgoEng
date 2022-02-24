#include <cstring>
#include <iostream>
#include <omp.h>
#include "fast_merge_sort.h"
//
// Created by oran on 12/26/21.
//


void merge(const int *__restrict__ a, const int *__restrict__ b,
                  int *__restrict__ c, const int a_size, const int b_size,
                  const int c_size) {
    int idx_a = 0;
    int idx_b = 0;
    for (int i = 0; i < c_size; ++i) {
        if (idx_a == a_size) {
            c[i] = b[idx_b++];
        } else if (idx_b == b_size) {
            c[i] = a[idx_a++];
        } else {
            c[i] = (a[idx_a] < b[idx_b]) ? a[idx_a++] : b[idx_b++];
        }
    }
}

void insertion_sort(int *arr, int n)
{
    for(int i=0; i<n-1; ++i)
    {
        int j = i+1;
        int cur = arr[j];
        while(j > 0 && cur < arr[j-1])
        {
            arr[j] = arr[j-1];
            --j;
        }
        arr[j] = cur;
    }
}

void merge_sort(int *arr, int *buffer, int n) { // slow merge sort

    if (n>32) {
        const int size_a = n / 2;
        const int size_b = n - size_a;
#pragma omp task if (size_a > 10000)
        {
            merge_sort_helper(arr, buffer, size_a); // recursive call
        }
        // no task for the second call so the thread doesnt wait
        merge_sort_helper(arr + size_a, buffer + size_a, size_b);
// don't start merging before sublists have been sorted
#pragma omp taskwait
        merge(buffer, buffer + size_a, arr, size_a, size_b, n);
    }
    // avoid recursion overhead for small sublists
    else if(n>1)
    {
        insertion_sort(arr, n);
    }
}

void merge_sort_helper(int *arr, int *buffer, int n)
{
    const int size_a = n / 2;
    const int size_b = n - size_a;
// i am not using final because i find this to be more idiomatic
#pragma omp task if(size_a > 10000)
    merge_sort(arr, buffer, size_a);
    merge_sort(arr+size_a, buffer+size_a, size_b);
#pragma omp taskwait
    merge(arr, arr+size_a, buffer, size_a, size_b, n);
}


void merge_sort_run(int *arr, int *buffer, int n)
{
#pragma omp parallel
#pragma omp single nowait
    merge_sort(arr, buffer, n);
}

// original impl. for comparison
void merge_sort_naive(int *arr, int n) { // slow merge sort
    if (n > 1) { // TODO: use insertion sort for small n
        const int size_a = n / 2;
        const int size_b = n - size_a;
        // TODO: make next recursive call a task
        merge_sort_naive(arr, size_a); // recursive call
        merge_sort_naive(arr + size_a, size_b); // recursive call
        // TODO: here should be a taskwait
        int *c = new int[n]; // TODO: avoid using heap for small n
         merge(arr, arr + size_a, c, size_a, size_b, n);
         memcpy(arr, c, sizeof(int) * n);
         delete[](c);
         }
    }