//
// Created by Oran on 01.02.22.
//
#include<array>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "ppm.h"

int main() {
    std::string path = "/Users/Oran/Documents/Master/WS21/algo_engineering/repo/test_p6.ppm";
    std::string output = "/Users/Oran/Documents/Master/WS21/algo_engineering/repo/output_p6.ppm";
    ppm img(path);
    img.write(output);
    return 0;
}