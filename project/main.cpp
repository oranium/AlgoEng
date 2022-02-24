//
// Created by Oran on 01.02.22.
//
#include<iostream>
#include<string>
#include "ppm.h"
#include "filter.h"
#include <random>
#include <omp.h>

int main(int argc, char *argv[]) {
    clock_t tStart = omp_get_wtime();
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

    aligned_vector<double> r = gaussFilter(img.r, 5, 30, img.height, img.width);
    aligned_vector<double> g = gaussFilter(img.g,5,30, img.height, img.width);
    aligned_vector<double> b = gaussFilter(img.b, 5,30, img.height, img.width);

    r = sigmaFilter(img.r, r, 25000);
    g = sigmaFilter(img.g, g, 25000);
    b = sigmaFilter(img.b, b, 25000);
    ppm imgCvd(r, g, b, img.height, img.width);

    imgCvd.normalize();
    imgCvd.write(output);
    std::cout << "Time taken: " << (omp_get_wtime() - tStart) <<  std::endl;
    return 0;
}