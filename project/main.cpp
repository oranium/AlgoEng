//
// Created by Oran on 01.02.22.
//
#include<array>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string>
#include "ppm.h"
#include "convolution.h"

int main() {
    std::string path = "/Users/Oran/Documents/Master/WS21/algo_engineering/repo/test_p6.ppm";
    std::string output = "/Users/Oran/Documents/Master/WS21/algo_engineering/repo/output_p6.ppm";
    ppm img(path);
    Matrix2D filter({3,3});
    std::fill(filter.begin(), filter.end(), 1.0/filter.nelem());

    Matrix2D convImg = ppmConvolveBW(filter, img);
    ppm imgCvd(convImg, convImg, convImg);
    imgCvd.normalize();
    imgCvd.write(output);
    return 0;
}