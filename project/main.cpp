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
#include "filter.h"
#include "convolution.h"


int main(int argc, char *argv[]) {
    std::string path = argv[1];
    std::string output;
    std::cout << argc << std::endl;
    if(argc>2)
    {
        output = argv[2];
        std::cout << "Output: " << argv[2] << std::endl;
    }
    else
    {
        output = "./output.ppm";
    }
    ppm img(path);

    Matrix2D filter({3,3});
    std::fill(filter.begin(), filter.end(), 1.0/filter.nelem());


    Matrix2D r_blurr = gaussFilter(img.r, 5,1);
    Matrix2D g_blurr = gaussFilter(img.g,5,1);
    Matrix2D b_blurr = gaussFilter(img.b, 5,1);

    Matrix2D r = sigmaFilter(img.r, r_blurr);
    Matrix2D g = sigmaFilter(img.g, g_blurr);
    Matrix2D b = sigmaFilter(img.b, b_blurr);


    ppm imgCvd(r, g, b);

    imgCvd.normalize();
    imgCvd.write(output);
    return 0;
}