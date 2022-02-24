//
// Created by Bruno Reinhold on 09.02.22.
//

#pragma once
#include "Matrix2D.h"
#include "aligned_allocator.h"

aligned_vector<double> gaussFilter(aligned_vector<double>& img, int size, double sig, const int N, const int M);
aligned_vector<double> sigmaFilter(aligned_vector<double>& img, aligned_vector<double> &blurred_image, int contrast_constant);
aligned_vector<double> meanFilter(aligned_vector<double>& img, int size);
aligned_vector<double> thresholding(aligned_vector<double>& img, double threshold);
aligned_vector<double> removeBackground(aligned_vector<double>& img, aligned_vector<double>& filtered_img);

