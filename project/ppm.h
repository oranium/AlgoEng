//
// Created by Oran on 27.01.22.
//
// based on https://github.com/sol-prog/Perlin_Noise/blob/master/ppm.h
// but we use an array for the values to make manipulation more efficient


#ifndef PPM_H
#define PPM_H

class ppm{
    void init();

    unsigned int rows;
    unsigned int cols;

public:
    // r,g,b arrays for each channel
    // as we have two variable dimensions, we need to declare a pointer to a pointer of arrays
    unsigned char **r;
    unsigned char **g;
    unsigned char **b;


    //not the same as rows, cols?
    unsigned int height;
    unsigned int width;
    unsigned int maxIntensity;

    //number of pixels - necessary? - height*width
    unsigned int size;

    ppm();
    // fill
    ppm(const std::string &fname);
    // construct ppm from r g b channels
    ppm(const unsigned char &r, const unsigned char &g, const unsigned char &b);
    // write the ppm image
    void write(const std::string &fname);
    // read the ppm image
    void read(const std::string &fname);
};
#endif
