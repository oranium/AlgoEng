//
// Created by oran on 2/24/22.
//
#include "aligned_allocator.h"
#include "Matrix2D.h"
#include "filter.h"
#include <catch2/catch_test_macros.hpp>

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

