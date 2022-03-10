#pragma once

void merge(const int *__restrict__ a, const int *__restrict__ b,
           int *__restrict__ c, const int a_size, const int b_size,
           const int c_size);

void insertion_sort(int *array, int n);

void merge_sort_naive(int *array, int n);

void merge_sort(int *array, int *buffer, int n);

void merge_sort_run(int *array, int *buffer, int n);

void merge_sort_helper(int *array, int *buffer, int n);
