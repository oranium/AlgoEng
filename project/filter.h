//
// Created by Bruno Reinhold on 09.02.22.
//

#ifndef PROJECT_FILTER_H
#define PROJECT_FILTER_H

#endif //PROJECT_FILTER_H
#include "Matrix2D.h"

Matrix2D gaussFilter(Matrix2D& img, int size, double sig);
Matrix2D sigmaFilter(Matrix2D& img, Matrix2D& blurred_image);
Matrix2D meanFilter(Matrix2D& img, int size);
Matrix2D removeBackground(Matrix2D& img, Matrix2D& filtered_img);

