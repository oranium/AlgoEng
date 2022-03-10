//
// Created by Oran on 27.01.22.
//
// based on https://github.com/sol-prog/Perlin_Noise/blob/master/ppm.h
// but we use an array for the values to make manipulation more efficient

#pragma once
#include <string>
#include "matrix_utils.h"
#include "aligned_allocator.h"
class ppm{
    void init();

    int rows;
    int cols;

public:
    // r,g,b arrays for each channel
    aligned_vector<double> r;
    aligned_vector<double> g;
    aligned_vector<double> b;


    //not the same as rows, cols?
    int height;
    int width;
    int maxIntensity;

    //number of pixels - necessary? - height*width
    unsigned int size;

    // fill
    explicit ppm(const std::string &fname);
    // construct ppm from r g b channels
    ppm(aligned_vector<double>& r, aligned_vector<double>& g, aligned_vector<double>& b, int N, int M);
    // write the ppm image
    void write(const std::string &fname);
    // read the ppm image
    void read(const std::string &fname);

    void normalize(int newMax=255);
};
