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
#include <random>

int main(int argc, char *argv[]) {
    clock_t tStart = clock();
    std::string path = argv[1];
    std::cout << "Removing background for image " << path << std::endl;
    std::string output;
    std::cout << argc << std::endl;
    if(argc>2)
    {
        output = argv[2];
    }
    else
    {
        output = "./output.ppm";
    }
    std::cout << "Writing to " << output << std::endl;

    std::vector<double> filter{1.0/3, 1.0/3, 1.0/3};

    ppm img(path);

    /*
    std::vector<double> convRT;
    convRT.resize(img.size);
    transpose(img.r, convRT, img.height, img.width);
    convRT = convolve1D(filter, convRT, img.width, img.height);
    std::vector<double> convR;
    convR.resize(img.size);
    transpose(convRT, convR, img.width, img.height);
    convR = convolve1D(filter, convR, img.height, img.width);

    std::vector<double> convGT;
    convGT.resize(img.size);
    transpose(img.g, convGT, img.height, img.width);
    convGT = convolve1D(filter, convGT, img.width, img.height);
    std::vector<double> convG;
    convG.resize(img.size);
    transpose(convGT, convG, img.width, img.height);
    convG = convolve1D(filter, convG, img.height, img.width);

    std::vector<double> convBT;
    convBT.resize(img.size);
    transpose(img.b, convBT, img.height, img.width);
    convBT = convolve1D(filter, convBT, img.width, img.height);
    std::vector<double> convB;
    convB.resize(img.size);
    transpose(convBT, convB, img.width, img.height);
    convB = convolve1D(filter, convB, img.height, img.width);
    */

    std::vector<double> r_blur = gaussFilter(img.r, 5, 30, img.height, img.width);
    std::vector<double> g_blur = gaussFilter(img.g,5,30, img.height, img.width);
    std::vector<double> b_blur = gaussFilter(img.b, 5,30, img.height, img.width);

    std::vector<double> r_sigma = sigmaFilter(img.r, r_blur, 100000);
    std::vector<double> g_sigma = sigmaFilter(img.g, g_blur, 100000);
    std::vector<double> b_sigma = sigmaFilter(img.b, b_blur, 100000);

    ppm imgCvd(r_sigma, g_sigma, b_sigma, img.height, img.width);

    imgCvd.normalize();
    imgCvd.write(output);
    std::cout << "Time taken: " << (clock() - tStart)/CLOCKS_PER_SEC << std::endl;
    return 0;
}