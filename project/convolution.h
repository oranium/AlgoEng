//
// Created by Oran on 03.02.22.
//
#pragma once
#include "Matrix2D.h"
#include "ppm.h"

Matrix2D convolve(Matrix2D& filter, Matrix2D& img);
Matrix2D convolve1D(std::vector<double> filter, Matrix2D& img);
