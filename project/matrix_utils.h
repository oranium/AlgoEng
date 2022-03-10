//
// Created by Oran on 06.02.22.
//
#pragma once
#include "aligned_allocator.h"

void transpose(const aligned_vector<double>& src, aligned_vector<double>& dst, int N, int M);
void normalize(aligned_vector<double> &vec, double newMax=255);