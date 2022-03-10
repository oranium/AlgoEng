//
// Created by Bruno Reinhold on 09.02.22.
//
#include <math.h>
#include <algorithm>    // std::min

#include "filter.h"
#include "convolution.h"
#include "matrix_utils.h"
#include "ppm.h"


aligned_vector<double> gaussFilter(aligned_vector<double> &img, int size, double sig,const int N,const int M)
{

    // define Gauss filter
    aligned_vector<double> gauss_filter(size);

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
    aligned_vector<double> gaussianBlurredVertical;
    gaussianBlurredVertical.resize(img.size());
    aligned_vector<double> gaussianBlurredHorizontal;
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



aligned_vector<double> sigmaFilter(aligned_vector<double> &img, aligned_vector<double> &blurred_image, int contrast_constant)
{
    double epsilon = 1e-5;
    auto max_val = std::max_element (blurred_image.begin(), blurred_image.end());


    aligned_vector<double> filteredImg;
    filteredImg.resize(img.size());
#pragma omp parallel for default(none) shared(img, blurred_image, filteredImg, max_val, epsilon, contrast_constant)
    for(int i=0; i<img.size(); i++){
        double divided = abs(img[i]/(blurred_image[i] + epsilon));
        double min_val = std::min(*max_val, divided * *max_val + epsilon);
        double gamma = 0.5 +(min_val/ *max_val) * min_val * min_val / contrast_constant;//65025;
        double res = (pow((min_val / *max_val), (1/ (gamma + epsilon)))) * *max_val;
        filteredImg[i] = res;
    }

    return filteredImg;
}


aligned_vector<double> thresholding(aligned_vector<double>& img, double threshold)
{
    aligned_vector<double> threshold_img;
    threshold_img.resize(img.size());
#pragma omp parallel for default(none) shared(img, threshold, threshold_img)
    for(int i=0; i<img.size(); i++) {
        bool above_th = img[i] > threshold;
        threshold_img[i] = above_th * 255.0 + (!above_th) * img[i];
    }
    return threshold_img;
}

aligned_vector<double> removeBackground(aligned_vector<double>& filtered_img, aligned_vector<double>& img_mask)
{
    aligned_vector<double> clean_img;
    clean_img.resize(img_mask.size());
#pragma omp parallel for default(none) shared(img_mask, clean_img, filtered_img)
    for(int i=0; i<img_mask.size(); i++) {
        bool above_threshold = img_mask[i] > 255.0;
        clean_img[i] = above_threshold * img_mask[i] + (!above_threshold) * filtered_img[i];
    }
    return clean_img;
}
