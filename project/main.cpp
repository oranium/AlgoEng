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



    aligned_vector<double> gray(img.size);
    for(int i=0; i<img.height;i++)
    {
        for(int j=0; j<img.width;j++)
        {
            gray[img.width * i + j] = img.r[img.width * i + j]*0.298
                                      + img.g[img.width * i + j]*0.587 + img.b[img.width * i + j]*0.114;
        }
    }


    // Gaussian blur
    aligned_vector<double> r = gaussFilter(img.r, 15, 30, img.height, img.width);
    aligned_vector<double> g = gaussFilter(img.g,15,30, img.height, img.width);
    aligned_vector<double> b = gaussFilter(img.b, 15,30, img.height, img.width);

    ppm imgCvd = ppm(r, g, b, img.height, img.width);

    //imgCvd.normalize();
    imgCvd.write("1blurout.ppm");
    // contrast filter
    r = sigmaFilter(img.r, r, 120000);
    g = sigmaFilter(img.g, g, 120000);
    b = sigmaFilter(img.b, b, 120000);
    normalize(r);
    normalize(g);
    normalize(b);
    ppm imgCvd_1 = ppm(r, g, b, img.height, img.width);
    imgCvd_1.write("sigma.ppm");

    // blurring contrast image
    aligned_vector<double> r_blur2 = gaussFilter(r, 15, 30, img.height, img.width);
    aligned_vector<double> g_blur2 = gaussFilter(g,15,30, img.height, img.width);
    aligned_vector<double> b_blur2 = gaussFilter(b, 15,30, img.height, img.width);

    imgCvd = ppm(r_blur2, g_blur2, b_blur2, img.height, img.width);
    //imgCvd.normalize();
    imgCvd.write("2blurrout.ppm");

    // threshold mask
    aligned_vector<double> r_mask = thresholding(r_blur2, 240);
    aligned_vector<double> g_mask = thresholding(g_blur2, 240);
    aligned_vector<double> b_mask = thresholding(b_blur2, 240);

    imgCvd = ppm(r_mask, g_mask, b_mask, img.height, img.width);
    //imgCvd.normalize();
    imgCvd.write("mask.ppm");

    // white background
    r = removeBackground(r, r_mask);
    g = removeBackground(g, g_mask);
    b = removeBackground(b, b_mask);

    imgCvd = ppm(r, g, b, img.height, img.width);

    imgCvd.normalize();
    imgCvd.write(output);
    std::cout << "Time taken: " << (omp_get_wtime() - tStart) <<  std::endl;
    return 0;
}