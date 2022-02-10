//
// Created by Oran on 01.02.22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "ppm.h"
#include "Matrix2D.h"

// based on https://github.com/sol-prog/Perlin_Noise/blob/master/ppm.h
// but we use an array for the values to make manipulation more efficient

void ppm::init(){
    width = 0;
    height = 0;
    // 1 Byte channel
    maxIntensity= 255;
}
/*
ppm::ppm(){
    this->r = Matrix2D({0, 0});
    this->g = Matrix2D({0, 0});
    this->b = Matrix2D({0, 0});

    init();

}
*/
ppm::ppm(const std::string &fname)
{
    init();
    read(fname);
}

ppm::ppm(Matrix2D &r, Matrix2D &g, Matrix2D &b)
{
    init();
    height = r.shape()[0];
    width = r.shape()[1];
    rows = height;
    cols = width;
    this->r = r;
    this->g = g;
    this->b = b;
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
        r = Matrix2D({rows, cols});
        g = Matrix2D({rows, cols});
        b = Matrix2D({rows, cols});
        // this char stores the read input byte
        char aux;
        // each r,g,b values come in that order
        for(int i=0; i<rows; i++) {
            for (int j = 0; j < cols; j++) {
                // read 1 bit
                in.read(&aux, 1);
                r[{i,j}] = (unsigned char) aux;
                // read 1 bit
                in.read(&aux, 1);
                g[{i,j}] = (unsigned char) aux;
                // read 1 bit
                in.read(&aux, 1);
                b[{i,j}] = (unsigned char) aux;
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
      out << "P6\n";
      out << width;
      out << " ";
      out << height << '\n';
      out << maxIntensity << '\n';

      // this char stores the output byte to be written
      char helper;
      for(int i=0; i<rows; i++)
      {
          for(int j=0; j<cols; j++){
              //TODO: why is this casted to char instead of staying unsigned? AKA why is helper char
              helper = static_cast<char>((int)std::round(r[{i,j}]));
              out.write(&helper, 1);
              helper = static_cast<char>((int)std::round(r[{i,j}]));
              out.write(&helper, 1);
              helper = static_cast<char>((int)std::round(r[{i,j}]));
              out.write(&helper, 1);
          }
      }
    }else
    {
        std::cout << "Error: Unable to open " << fname << std::endl;
    }
    out.close();
}

void ppm::normalize(double newMax)
{
    const std::array<double,2> minMaxR = r.minmax_element();
    const std::array<double,2> minMaxG = g.minmax_element();
    const std::array<double,2> minMaxB = b.minmax_element();

    std::cout << std::endl;
    std::transform(r.begin(), r.end(), r.begin(),
       [&](double elem)->double
        {
        auto min = minMaxR[0];
        auto max = minMaxR[1];
        return (newMax * (elem - min) / (max - min));
        });
    std::transform(g.begin(), g.end(), g.begin(),
                   [&](auto elem)->double
                   {
                       auto min = minMaxG[0];
                       auto max = minMaxG[1];
                       return (newMax * (elem - min) / (max - min));
                   });
    std::transform(b.begin(), b.end(), b.begin(),
                   [&](auto elem)->double
                   {
                       auto min = minMaxB[0];
                       auto max = minMaxB[1];
                       return (newMax * (elem - min) / (max - min));
                   });

}

