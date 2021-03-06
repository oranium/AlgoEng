//
// Created by Oran on 03.02.22.
//

#include <cmath>
#include <iostream>
#include <numeric>
#include "convolution.h"
#include "ppm.h"
#include "matrix_utils.h"

template<class T>
void fill_pad(aligned_vector<T> &paddedImg, aligned_vector<T> &img, int sizePad, int N, int M)
{
    aligned_vector<double > pad(sizePad);
    std::fill(pad.begin(), pad.end(), 0);
    for(int i=0; i<(img.size())+1;i++)
    {
        if(i%M==0)
        {
            paddedImg.insert(std::end(paddedImg), std::begin(pad), std::end(pad));
        }
        paddedImg.push_back(img[i]);
    }
}

aligned_vector<double> convolve1D(aligned_vector<double> &filter, aligned_vector<double> &img, int N, int M)
{
    // floor division
    // only square filters
    const int sizePad = std::floor(filter.size()/2);
    // reserve space so no reallocation happens on filling
    aligned_vector<double>paddedImg;
    paddedImg.reserve(img.size() + sizePad + N * sizePad);
    aligned_vector<double> convolvedImg;
    convolvedImg.resize(img.size());
    // create the padded image
    // we are 255 padding because we assume white backgrounds/scanned paper
    fill_pad(paddedImg, img, sizePad, N, M);

    // apply convolution
#pragma omp parallel for default(none) shared(img, convolvedImg, sizePad, M, paddedImg, filter) if(img.size() > 100000)
    for (int i=0; i<img.size(); ++i)
    {
            // avoid the padding
            int offset = (i/M) * sizePad;
            double res = std::transform_reduce((paddedImg.begin()+i+offset), (paddedImg.begin()+i+offset+filter.size())
                    , filter.begin(), 0.0);
            convolvedImg[i] = res;
    }
    return convolvedImg;
}
