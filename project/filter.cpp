//
// Created by Bruno Reinhold on 09.02.22.
//
#include <math.h>
#include <algorithm>    // std::min

#include "filter.h"
#include "convolution.h"
#include "Matrix2D.h"
#include "ppm.h"


std::vector<double> gaussFilter(std::vector<double> &img, int size, double sig,const int N,const int M)
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
    std::vector<double> gaussianBlurredVertical;
    gaussianBlurredVertical.resize(img.size());
    std::vector<double> gaussianBlurredHorizontal;
    gaussianBlurredHorizontal.resize(img.size());
    // transpose the matrix to avoid cache misses for 'vertical' access
    // horizontal convolution on transposed matrix
    // equivalent to vertical convolution on original matrix

    transpose(img, gaussianBlurredVertical, N, M);

    gaussianBlurredVertical = convolve1D(gauss_filter, gaussianBlurredVertical, M, N);
    // transpose back to original shape
    transpose(gaussianBlurredVertical, gaussianBlurredHorizontal, M, N);

    gaussianBlurredHorizontal= convolve1D(gauss_filter, gaussianBlurredHorizontal, N, M);

    return gaussianBlurredHorizontal;
}



std::vector<double> sigmaFilter(std::vector<double> &img, std::vector<double> &blurred_image, int contrast_constant)
{
    double epsilon = 1e-5;
    auto max_val = std::max_element (blurred_image.begin(), blurred_image.end());


    std::vector<double> filteredImg;
    filteredImg.reserve(img.size());
    for(int i=0; i<img.size(); i++){
        
        double divided = abs(img[i]/blurred_image[i]+ epsilon);
        double min_val = std::min(*max_val, divided * *max_val + epsilon);
        double gamma = 0.5 +(min_val/ *max_val) * min_val * min_val / contrast_constant;//65025;
        double res = (pow((min_val / *max_val), (1/ (gamma + epsilon)))) * *max_val;
        filteredImg.push_back(res);
    }

    return filteredImg;
}
/*
std::vector<double> meanFilter(std::vector<double>& img, int size)
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
*/
std::vector<double> thresholding(std::vector<double>& img, double threshold)
{
    int index = 0;
    std::vector<double> threshold_img = img;
    for(auto elem: img) {
        if (elem > threshold) {
            threshold_img[index] = 255.0;
        }
        index++;
    }

    return threshold_img;
}

std::vector<double> removeBackground(std::vector<double>& img, std::vector<double> filtered_img)
{
    int index = 0;
    std::vector<double> clean_img = img;
    for(auto elem: filtered_img) {
        if (elem < 255.0) {
            clean_img[index] = filtered_img[index];
        }
        index++;
    }
    return clean_img;
}
