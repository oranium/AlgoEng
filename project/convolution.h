//
// Created by Oran on 03.02.22.
//
#pragma once
#include "Matrix2D.h"
#include "ppm.h"

std::vector<double> convolve(std::vector<double> filter, std::vector<double> img);
std::vector<double> convolve1D(std::vector<double>& filter, std::vector<double>& img, int N, int M);
