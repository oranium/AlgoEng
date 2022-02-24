//
// Created by oran on 2/24/22.
//
#include "aligned_allocator.h"
#include "Matrix2D.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE( "Transpose is correct", "[transpose]" ) {
aligned_vector<double> in = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
aligned_vector<double> out(in.size());
aligned_vector<double> expected = {1,5,9,2,6,10,3,7,11,4,8,12};
int N = 3;
int M = 4;
transpose(in, out, N, M);
for(auto elem:out)
{
std::cout << elem << std::endl;
}
std::cout << std::endl;
for(auto elem:expected)
{
std::cout << elem << std::endl;
}

REQUIRE(out == expected );
}