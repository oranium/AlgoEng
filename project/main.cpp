//
// Created by Oran on 01.02.22.
//
#include<array>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "ppm.h"
#include "filter.h"

int main() {
    std::string path = "/Users/brunoreinhold/FSU/AlgoEng/project/test_p6.ppm";
    std::string output = "/Users/brunoreinhold/FSU/AlgoEng/project/out_test_p6.ppm";
    ppm img(path);

    img.write(output);
    return 0;
}