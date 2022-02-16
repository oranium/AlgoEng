//
// Created by Bruno Reinhold on 09.02.22.
//

#ifndef PROJECT_FILTER_H
#define PROJECT_FILTER_H

#endif //PROJECT_FILTER_H
#include "Matrix2D.h"

std::vector<double> gaussFilter(std::vector<double>& img, int size, double sig, const int N, const int M);
std::vector<double> sigmaFilter(std::vector<double>& img, std::vector<double> &blurred_image, int contrast_constant);
std::vector<double> meanFilter(std::vector<double>& img, int size);
std::vector<double> thresholding(std::vector<double>& img, double threshold);
std::vector<double> removeBackground(std::vector<double>& img, std::vector<double>& filtered_img);

