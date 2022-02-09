//
// Created by Oran on 27.01.22.
//
// based on https://github.com/sol-prog/Perlin_Noise/blob/master/ppm.h
// but we use an array for the values to make manipulation more efficient

#pragma once
#include "Matrix2D.h"

class ppm{
    void init();

    int rows;
    int cols;

public:
    // r,g,b arrays for each channel
    Matrix2D r;
    Matrix2D g;
    Matrix2D b;


    //not the same as rows, cols?
    int height;
    int width;
    int maxIntensity;

    //number of pixels - necessary? - height*width
    unsigned int size;

    ppm();
    // fill
    ppm(const std::string &fname);
    // construct ppm from r g b channels
    ppm(Matrix2D &r, Matrix2D &g, Matrix2D &b);
    // write the ppm image
    void write(const std::string &fname);
    // read the ppm image
    void read(const std::string &fname);

    void normalize(double newMax=255.0);
};
