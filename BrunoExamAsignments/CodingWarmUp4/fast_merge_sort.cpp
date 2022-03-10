#include <cstring>
#include <iostream>
#include <omp.h>
#include "fast_merge_sort.h"


void merge(const int *__restrict__ a, const int *__restrict__ b,
                  int *__restrict__ c, const int a_size, const int b_size,
                  const int c_size) {
    int index_a = 0;
    int index_b = 0;
    for (int i = 0; i < c_size; ++i) {
        if (index_a == a_size) {
            c[i] = b[index_b++];
        } else if (index_b == b_size) {
            c[i] = a[index_a++];
        } else {
            c[i] = (a[index_a] < b[index_b]) ? a[index_a++] : b[index_b++];
        }
    }
}

void merge_sort_helper(int *array, int *buffer, int n)
{
    const int size_a = n / 2;
    const int size_b = n - size_a;
#pragma omp task if(size_a > 10000)
    merge_sort(array, buffer, size_a);
    merge_sort(array+size_a, buffer+size_a, size_b);
#pragma omp taskwait
    merge(array, array+size_a, buffer, size_a, size_b, n);
}

void insertion_sort(int *array, int n)
{
    for(int i=0; i<n-1; ++i)
    {
        int j = i+1;
        int current_value = array[j];
        while(j > 0 && current_value < array[j-1])
        {
            array[j] = array[j-1];
            j--;
        }
        array[j] = current_value;
    }
}

void merge_sort(int *array, int *buffer, int n) { 

    if (n>32) {
        const int size_a = n / 2;
        const int size_b = n - size_a;
        
#pragma omp task if (size_a > 10000)
        {
            merge_sort_helper(array, buffer, size_a);
        }
        merge_sort_helper(array + size_a, buffer + size_a, size_b);
#pragma omp taskwait
        merge(buffer, buffer + size_a, array, size_a, size_b, n);
    }
    else if(n>1)
    {
        insertion_sort(array, n);
    }
}

void merge_sort_run(int *array, int *buffer, int n)
{
#pragma omp parallel
    
#pragma omp single nowait
    merge_sort(array, buffer, n);
}

void merge_sort_naive(int *array, int n) { 
    if (n > 1) {
        const int size_a = n / 2;
        const int size_b = n - size_a;
        merge_sort_naive(array, size_a);
        
        merge_sort_naive(array + size_a, size_b); 
        int *c = new int[n];
        merge(array, array + size_a, c, size_a, size_b, n);
        memcpy(array, c, sizeof(int) * n);
        delete[](c);
        }
}