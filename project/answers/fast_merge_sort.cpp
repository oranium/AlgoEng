#include <cstring>
#include <iostream>
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

void merge_sort_naive(int *arr, int n) { // slow merge sort

    if (n>32) {
        const int size_a = n / 2;
        const int size_b = n - size_a;
#pragma omp task if (size_a < 10000)
                merge_sort_naive(arr, size_a); // recursive call
                merge_sort_naive(arr + size_a, size_b); // recursive call
            // don't start merging before sublists have been sorted
#pragma omp taskwait
        int *c = new int[n]; // TODO: avoid using heap for small n
         merge(arr, arr + size_a, c, size_a, size_b, n);
         memcpy(arr, c, sizeof(int) * n);
         delete[](c);
         }
    else if(n>1)
    {
        insertion_sort(arr, n);
    }
}

