//
// Created by Oran on 01.02.22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm> // std::minmax_element
#include <utility>
#include <valarray> //std::round ??
#include <array>
#include "ppm.h"
#include "matrix_utils.h"

// based on https://github.com/sol-prog/Perlin_Noise/blob/master/ppm.h
// working

void ppm::init(){
    width = 0;
    height = 0;
    // 1 Byte channel
    maxIntensity= 255;
}

ppm::ppm(const std::string &fname)
{
    init();
    read(fname);
}

ppm::ppm(aligned_vector<double>& r1, aligned_vector<double>& g1, aligned_vector<double>& b1, const int N, const int M)
{
    init();
    height = N;
    width = M;
    rows = height;
    cols = width;
    size = height * width;
    // clang-tidy told me std::move is cheaper than copying
    r  = r1;
    g = g1;
    b = b1;
    //already defined in init()
    //maxIntensity = 255;
}

void ppm::read(const std::string &fname)
{
    std::ifstream in(fname.c_str(), std::ios::in | std::ios::binary);
    if(in.is_open())
    {
        std::string line;
        std::getline(in, line);
        // TODO: P3 for ASCII (maybe)
        if (line != "P6")
        {
            std::cout << "Not a (binary) PPM." << std::endl;
            return;
        }
        // get width
        std::getline(in, line);
        // ignore comments
        while(line[0] == '#')
        {
            std::getline(in, line);
        }
        std::cout << "Image dimensions:" << std::endl;
        std::cout << line << std::endl;
        std::stringstream dimensions(line);
        try {
            dimensions >> width;
            dimensions >> height;
            rows = height;
            cols = width;
            size = height * width;
        }
        catch(std::exception &e)
        {
            std::cout << "Header format error: " << e.what() << std::endl;
            return;
        }
        std::getline(in, line);
        std::stringstream maxIntensityHeader;
        try
        {
            maxIntensityHeader >> maxIntensity;
        }
        catch(std::exception &e)
        {
            std::cout << "Header format error: " << e.what() << std::endl;
            return;
        }
        // dynamically create array based on header size
        // r/g/b are pointers to Arrays of pointers of unsigned char (1Byte) Arrays.
        r.reserve(size);
        g.reserve(size);
        b.reserve(size);
        // this char stores the read input byte
        char aux;
        // each r,g,b values come in that order
        for(int i=0; i<rows; i++) {
            for (int j = 0; j < cols; j++) {
                // read 1 bit
                in.read(&aux, 1);
                r.push_back(static_cast<unsigned char>(aux));
                // read 1 bit
                in.read(&aux, 1);
                g.push_back(static_cast<unsigned char>(aux));
                // read 1 bit
                in.read(&aux, 1);
                b.push_back(static_cast<unsigned char>(aux));
            }
        }

    }
    else
    {
        std::cout << "Error: Unable to open " << fname << std::endl;
    }
    in.close();
}
/*
 * Write values in RGB channels to valid PPM File
 * intensity values over 255 are UB (undefined behavior) -> call ppm::normalize first
 * TODO: be able to write values over 255 (up to 2 Byte=65535)
 */
void ppm::write(const std::string &fname)
{
    std::ofstream out(fname.c_str(), std::ios::out | std::ios::binary);
    if(out.is_open())
    {
        // string lookup table for 0-255
        std::array<char, 256> lookup{};
        for(int i=0;i<256;++i){ lookup[i]=static_cast<char>(i);}
        out << "P6\n" << width << " " << height << '\n' << maxIntensity << '\n';

      // this char stores the output byte to be written
      char helper;
#pragma omp parallel default(none) shared(helper, out, lookup, std::cout)
      {
            std::string valBuffer;
            valBuffer.reserve(cols * 12);
#pragma omp for schedule(dynamic) ordered
            for (int i = 0; i < height; i++) {
                valBuffer.clear();
                for (int j = 0; j < width; j++) {
                    valBuffer += (lookup[std::round(r[i * width + j])]);
                    valBuffer += (lookup[std::round(g[i * width + j])]);
                    valBuffer += (lookup[std::round(b[i * width + j])]);
                }
#pragma omp ordered
                out << valBuffer;
            }
      }
    }else
    {
        std::cout << "Error: Unable to open " << fname << std::endl;
    }
    out.close();
}

void ppm::normalize(int newMax)
{

    auto minmaxR = std::minmax_element (r.begin(),r.end());
    auto minmaxG = std::minmax_element (g.begin(),g.end());
    auto minmaxB = std::minmax_element (b.begin(),b.end());

    std::transform(r.begin(), r.end(), r.begin(),
       [& ](double elem)->double
        {return (newMax * (elem - *minmaxR.first) / (*minmaxR.second - *minmaxR.first));});

    std::transform(g.begin(), g.end(), g.begin(),
                   [& ](double elem)->double
                   {return (newMax * (elem - *minmaxG.first) / (*minmaxG.second - *minmaxG.first));});

    std::transform(b.begin(), b.end(), b.begin(),
                   [&](double elem)->double
                   {return (newMax * (elem - *minmaxB.first) / (*minmaxB.second - *minmaxB.first));});
}

