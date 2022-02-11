//
// Created by Bruno Reinhold on 09.02.22.
//
#include <math.h>
#include <algorithm>    // std::min

#include "filter.h"
#include "convolution.h"
#include "Matrix2D.h"
#include "ppm.h"


Matrix2D gaussFilter(Matrix2D& img, int size, double sig)
{

    // define Gauss filter
    std::vector<double> gauss_filter(size);

    int half_size = floor(size/2);
    int r, s = half_size * sig * sig;
    double sum = 0.0;

    //generate Gauss values
    for (int i = -half_size; i <= half_size; i++) {
            gauss_filter[i + half_size]  = 1/(sqrt(2 * M_PI) * sig) * (exp(-(i*i) / (2*s*s)));
            sum += gauss_filter[i + half_size];
    }
    //normalize
    std::transform(gauss_filter.begin(), gauss_filter.end(), gauss_filter.begin(),
                   [&](auto elem)->double {return elem/sum;});
    Matrix2D gaussianBlurredHorizontal = convolve1D(gauss_filter,  img);
    Matrix2D gaussianBlurredVertical({gaussianBlurredHorizontal.shape()[1], gaussianBlurredHorizontal.shape()[0]});
    // transpose the matrix to avoid cache misses for 'vertical' access
    transpose(gaussianBlurredHorizontal, gaussianBlurredVertical);
    // horizontal convolution on transposed matrix
    // equivalent to vertical convolution on original matrix
    gaussianBlurredVertical = convolve1D(gauss_filter, img);
    // transpose back to original shape
    transpose(gaussianBlurredVertical, gaussianBlurredHorizontal);

    return gaussianBlurredVertical;
}

Matrix2D sigmaFilter(Matrix2D& img, Matrix2D& blurred_image)
{
    double epsilon = 0.00000000001;
    double max_value = 255.0;
    int index = 0;

    Matrix2D filteres_image = img;

    for(auto ele: img){

        double divided = img[index]/blurred_image[index]+ epsilon;
        double min_val = std::min(max_value, divided * max_value + epsilon);
        double gamma = 0.5 +(min_val/ max_value) * min_val * min_val / 100000;//65025;
        double res = (pow((min_val / max_value), (1/ (gamma + epsilon)))) * max_value;
        filteres_image[index] = res;
        index++;
    }


    return filteres_image;
}

Matrix2D meanFilter(Matrix2D& img, int size)
{

    Matrix2D mean_filter({size, size});
    double filter_size;
    int i = 0 ;
    for(auto elem:mean_filter)
    {
        mean_filter[i] = 1.0/filter_size;
        i++;
    }

    return convolve(mean_filter,  img);
}


Matrix2D removeBackground(Matrix2D& img, Matrix2D& filtered_img)
{
    int index = 0;
    Matrix2D& clean_img = img;
    for(auto elem: filtered_img) {
        if (elem == 255.0) {
            clean_img[index] = filtered_img[index];
        }
        index++;
    }
    return clean_img;
}
