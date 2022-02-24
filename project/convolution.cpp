//
// Created by Oran on 03.02.22.
//

#include "convolution.h"
#include <math.h>
#include <iostream>
#include "ppm.h"
#include "Matrix2D.h"
/*
std::vector<double> convolve(std::vector<double> filter, std::vector<double> img)
{
    // floor division
    // only square filters
    const int dimFilter = filter.size();
    const int sizePad = std::floor(filter.size()/2);
    const int rowsPad = img.size() + 2*sizePad;
    std::vector<double> paddedImg(rowsPad);
    std::vector<double> convolvedImg(img.size());

    // create the padded image
    // we are zero padding
    // borders along the rows
    //std::fill(paddedImg.begin(), paddedImg.end(), 0);
    // create the padded image
    // we are zero padding
    for (int i=0; i<sizePad;i++)
    {
        paddedImg[i] = 0;
    }
    int idx = sizePad;
    for (auto elem:img)
    {
        paddedImg[idx] = elem;
        ++idx;
    }
    for (int i=0; i<sizePad;i++)
    {
        paddedImg[paddedImg.size() - i] = 0;
    }
    // apply convolution
    for (int i=0; i<img.shape()[0]; ++i)
    {
        for (int j=0; j<img.shape()[1]; ++j)
        {
            Slice slice{i,i+dimFilter, j,j+dimFilter};
            std::vector<double> imageSlice = paddedImg[slice];
            double newVal = std::inner_product(imageSlice.begin(), imageSlice.end(), filter.begin(), 0);
            /*
            for(int i=0;i<imageSlice.size();i++)
            {
                newVal += imageSlice.at(i) * filter[i];
            }

            convolvedImg[{i,j}] = newVal;
        }
    }
    return convolvedImg;
}
*/
aligned_vector<double> convolve1D(aligned_vector<double> &filter, aligned_vector<double> &img, int N, int M)
{
    // floor division
    // only square filters
    const int sizePad = std::floor(filter.size()/2);
    // reserve space so no reallocation happens on filling
    aligned_vector<double>paddedImg;
    paddedImg.reserve(img.size() + sizePad + N * sizePad);
    aligned_vector<double> convolvedImg;
    convolvedImg.reserve(img.size());
    // create the padded image
    // we are zero padding
    for(int i=0; i<img.size()+1;i++)
    {
        if(i%M==0)
        {
            for(int j=0; j<sizePad; j++)
            {
                paddedImg.push_back(0);
            }
        }
        paddedImg.push_back(img[i]);
    }

    // apply convolution
    //#pragma omp parallel for default(none) shared(img, convolvedImg, sizePad, M, paddedImg, filter)
    for (int i=0; i<img.size(); ++i)
    {
            // avoid the padding
            int offset = (i/M) * sizePad;
            convolvedImg.push_back(std::inner_product((paddedImg.begin()+i+offset), (paddedImg.begin()+i+offset+filter.size())
                                                     , filter.begin(), 0.0));
    }
    return convolvedImg;
}

