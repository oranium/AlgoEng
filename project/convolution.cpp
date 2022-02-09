//
// Created by Oran on 03.02.22.
//

#include "convolution.h"
#include <math.h>
#include <iostream>
#include "ppm.h"
#include "Matrix2D.h"
#include <valarray>

Matrix2D ppmConvolveBW(Matrix2D& filter, const ppm& img)
{
    const int size = filter.nelem();
    // floor division
    const int sizePad = std::floor(size/2);
    const int rowsPad = img.height + sizePad;
    const int colsPad = img.width + sizePad;
    Matrix2D paddedImg({rowsPad, colsPad});
    Matrix2D convolvedImg({img.height, img.width});
    std::vector<double> flat_filter;
    for (double elem: filter){
        flat_filter.push_back(elem);
    }
    // create the padded image
    // we are zero padding
    // borders along the rows
    for (int i=0;i<img.width;i++)
    {
        for (int j=0; j<sizePad;j++) {
            paddedImg[{0, j}] = 0;
            paddedImg[{(img.height - 1) - j, i}] = 0;
        }
    }
    // borders along the cols
    for(int i=0;i<img.height;i++)
    {
        for (int j=0; j<sizePad;j++)
        {
            paddedImg[{i,j}] = 0;
            paddedImg[{i,(img.width - 1) - j}] = 0;
        }
    }
    // the image
    for (int i=sizePad; i<img.height; i++)
    {
        for (int j=sizePad; j<img.width;j++)
        {
            paddedImg[{i,j}] = (0.2989 * img.r[{i,j}] + 0.5870*img.g[{i,j}] + 0.1140*img.b[{i,j}]);
        }
    }
    // apply convolution
    for (int i=0; i<img.height; ++i)
    {
        for (int j=0; i<img.width; ++j)
        {
            Slice slice{i,i+sizePad, j,j+sizePad};
            std::vector<double> imageSlice = paddedImg[slice];
            convolvedImg[{i,j}] = std::inner_product(imageSlice.begin(), imageSlice.end(), filter.begin(), 0);
        }
    }


    return convolvedImg;
}
