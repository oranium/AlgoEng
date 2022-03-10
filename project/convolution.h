//
// Created by Oran on 03.02.22.
//
#pragma once
#include "matrix_utils.h"
#include "ppm.h"

aligned_vector<double> convolve(aligned_vector<double> filter, aligned_vector<double> img);
aligned_vector<double> convolve1D(aligned_vector<double> &filter, aligned_vector<double> &img, int N, int M);
