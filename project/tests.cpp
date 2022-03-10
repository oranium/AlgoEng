//
// Created by oran on 2/24/22.
//
#define PAD_VAL 255

#include "aligned_allocator.h"
#include "filter.h"
#include "matrix_utils.h"
#include <cmath>
#include "convolution.h"
#include <catch2/catch_test_macros.hpp>
#include "ppm.h"

TEST_CASE( "Transpose is correct", "[transpose]" ) {
aligned_vector<double> in = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
aligned_vector<double> out(in.size());
aligned_vector<double> expected = {1,5,9,2,6,10,3,7,11,4,8,12};
int N = 3;
int M = 4;
transpose(in, out, N, M);

//Check element-wise equality
REQUIRE(out == expected );
}

TEST_CASE("Gaussian blur test"){

    aligned_vector<double> img = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    aligned_vector<double> blurred_img = {255, 255, 255, 255, 255, 0, 254, 33, 0, 10, 255, 255};
    aligned_vector<double> expected = {255, 255, 255, 255, 255, 6, 7, 8, 9, 10, 255, 255};

    aligned_vector<double> out(img.size());

    out = gaussFilter(img, blurred_img);
    REQUIRE(out == expected);
}

TEST_CASE("custom contrast filter test"){

    aligned_vector<double> img = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    aligned_vector<double> blurred_img = {255, 255, 255, 255, 255, 0, 254, 33, 0, 10, 255, 255};
    aligned_vector<double> expected = {255, 255, 255, 255, 255, 6, 7, 8, 9, 10, 255, 255};

    aligned_vector<double> out(img.size());

    out = sigmaFilter(img, blurred_img);
    REQUIRE(out == expected);
}

TEST_CASE("thresholding works correctly"){
    aligned_vector<double> in = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    aligned_vector<double> out(in.size());
    aligned_vector<double> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 255, 255};

    out = thresholding(in, 10);
    REQUIRE(out == expected);
}

TEST_CASE("removeBackground test "){

    aligned_vector<double> in = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    aligned_vector<double> mask = {255, 255, 255, 255, 255, 0, 254, 33, 0, 10, 255, 255};
    aligned_vector<double> expected = {255, 255, 255, 255, 255, 6, 7, 8, 9, 10, 255, 255};

    aligned_vector<double> out(in.size());

    out = removeBackground(in, mask);
    REQUIRE(out == expected);
}


TEST_CASE( "Correct Convolution Results", "[convolve]" ) {
aligned_vector<double> in = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
aligned_vector<double> filter = {1.0/3,1.0/3,1.0/3};
int N = 3;
int M = 4;

aligned_vector<double> out = convolve1D(filter, in, N, M);
// The next two instructions are what this particular convolution should achieve
aligned_vector<double> expected = {PAD_VAL+1+2, 1+2+3, 2+3+4, 3+4+PAD_VAL,
                                   PAD_VAL+5+6, 5+6+7, 6+7+8, 7+8+PAD_VAL,
                                    PAD_VAL+9+10, 9+10+11, 10+11+12, 11+12+PAD_VAL};
std::transform(expected.begin(), expected.end(), expected.begin(),
[&](double elem)->double
{return (elem/3.0);});

REQUIRE(out == expected );
}
