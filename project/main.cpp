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

int main() {
    std::string path = "/Users/brunoreinhold/FSU/AlgoEng/project/test_p6.ppm";
    std::string output = "/Users/brunoreinhold/FSU/AlgoEng/project/out_test_p6.ppm";
    ppm img(path);

    Matrix2D filter({3,3});
    short i = 0;
    for(auto elem:filter)
    {
        filter[i] = i;
        ++i;
    }
    std::array<int, 4> slice{0,1,1,2};
    const std::vector<double>& lol =  filter[slice];
    std::cout << lol.size() << std::endl;

    std::cout << "----SLICE ELEMENTS PART 2----" << std::endl;
    for(auto elem:lol)
    {
        std::cout << elem << std::endl;
    }

    img.write(output);
    return 0;
}