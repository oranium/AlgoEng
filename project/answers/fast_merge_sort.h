//
// Created by oran on 2/24/22.
//
#pragma once

void merge(const int *__restrict__ a, const int *__restrict__ b,
           int *__restrict__ c, const int a_size, const int b_size,
           const int c_size);

void insertion_sort(int *arr, int n);

void merge_sort_naive(int *arr, int n);

void merge_sort_run(int *arr, int n);