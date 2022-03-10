//
// Created by Oran on 01.02.22.
//
#include<iostream>
#include "ppm.h"
#include "filter.h"
#include <omp.h>
int main(int argc, char *argv[]) {
    clock_t tStart = omp_get_wtime();
    std::string path = argv[1];
    std::cout << "Removing background for image " << path << std::endl;
    std::string output;
    std::cout << argc << std::endl;
    if (argc > 2) {
        output = argv[2];
    } else {
        output = "./output.ppm";
    }
    std::cout << "Writing to " << output << std::endl;

    ppm img(path);

    aligned_vector<double> gray(img.size);
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            gray[img.width * i + j] = img.r[img.width * i + j] * 0.298
                                      + img.g[img.width * i + j] * 0.587 + img.b[img.width * i + j] * 0.114;
        }
    }

    aligned_vector<double> r, g, b;

    r = gaussFilter(img.r, 15, 30, img.height, img.width);

    g = gaussFilter(img.g, 15, 30, img.height, img.width);

    b = gaussFilter(img.b, 15, 30, img.height, img.width);
    // contrast filter
    r = sigmaFilter(img.r, r, 100000);

    g = sigmaFilter(img.g, g, 100000);

    b = sigmaFilter(img.b, b, 100000);
    normalize(r);
    normalize(g);
    normalize(b);

    // blurring contrast image
    aligned_vector<double> gray_blur, gray_mask;
    gray_blur = gaussFilter(gray, 15, 30, img.height, img.width);
    // threshold mask
    gray_mask = thresholding(gray_blur, 240);
    // white background
    r = removeBackground(r, gray_mask);
    g = removeBackground(g, gray_mask);
    b = removeBackground(b, gray_mask);
    ppm imgCvd(r, g, b, img.height, img.width);

    imgCvd.normalize();
    imgCvd.write(output);
    std::cout << "Removed background in  " << (omp_get_wtime() - tStart) <<  " seconds" << std::endl;
    return 0;
}