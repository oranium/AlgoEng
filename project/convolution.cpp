//
// Created by Oran on 03.02.22.
//

#include "convolution.h"
#include <math.h>
#include <iostream>
#include "ppm.h"
#include "Matrix2D.h"

Matrix2D ppmConvolveBW(Matrix2D& filter, ppm& img)
{
    // floor division
    // only square filters
    const int dimFilter = filter.shape()[0];
    const int sizePad = std::floor(filter.shape().at(0)/2);
    const int rowsPad = img.height + 2*sizePad;
    const int colsPad = img.width + 2*sizePad;
    Matrix2D paddedImg({rowsPad, colsPad});
    Matrix2D convolvedImg({img.height, img.width});

    // create the padded image
    // we are zero padding
    // borders along the rows
    //std::fill(paddedImg.begin(), paddedImg.end(), 0);
    for (int i=0;i<sizePad;i++)
    {
        for (int j=0; j<img.width;j++) {
            paddedImg[{i, j}] = 0.0;
            paddedImg[{(img.height - 1) - i, j}] = 0.0;
        }
    }

    // borders along the cols
    for(int i=0;i<img.height;i++)
    {
        for (int j=0; j<sizePad;j++)
        {
            paddedImg[{i, (img.width-1)-j}] = 0.0;
            paddedImg[{i,j}] = 0.0;
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
        for (int j=0; j<img.width; ++j)
        {
            Slice slice{i,i+dimFilter, j,j+dimFilter};
            std::vector<double> imageSlice = paddedImg[slice];
            double newVal = std::inner_product(imageSlice.begin(), imageSlice.end(), filter.begin(), 0);

            convolvedImg[{i,j}] = newVal;
        }
    }
    return convolvedImg;
}
