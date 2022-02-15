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


    ppm img(path);

    std::vector<double> r = gaussFilter(img.r, 5, 30, img.height, img.width);
    std::vector<double> g = gaussFilter(img.g,5,30, img.height, img.width);
    std::vector<double> b = gaussFilter(img.b, 5,30, img.height, img.width);

    r = sigmaFilter(img.r, r, 65000);
    g = sigmaFilter(img.g, g, 65000);
    b = sigmaFilter(img.b, b, 65000);
    ppm imgCvd(r, g, b, img.height, img.width);

    imgCvd.normalize();
    imgCvd.write(output);
    std::cout << "Time taken: " << (clock() - tStart)/CLOCKS_PER_SEC << std::endl;
    return 0;
}