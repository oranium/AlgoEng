//
// Created by Oran on 03.02.22.
//

#include "convolution.h"
#include <math.h>
#include <iostream>
#include "ppm.h"
#include "Matrix2D.h"

Matrix2D convolve(Matrix2D& filter, Matrix2D& img)
{
    // floor division
    // only square filters
    const int dimFilter = filter.shape()[0];
    const int sizePad = std::floor(filter.shape().at(0)/2);
    const int rowsPad = img.shape()[0] + 2*sizePad;
    const int colsPad = img.shape()[1] + 2*sizePad;
    Matrix2D paddedImg({rowsPad, colsPad});
    Matrix2D convolvedImg(img.shape());

    // create the padded image
    // we are zero padding
    // borders along the rows
    //std::fill(paddedImg.begin(), paddedImg.end(), 0);
    for (int i=0;i<sizePad;i++)
    {
        for (int j=0; j<img.shape()[1];j++) {
            paddedImg[{i, j}] = 0.0;
            paddedImg[{(img.shape()[0] - 1) - i, j}] = 0.0;
        }
    }

    // borders along the cols
    for(int i=0;i<img.shape()[0];i++)
    {
        for (int j=0; j<sizePad;j++)
        {
            paddedImg[{i, (img.shape()[1]-1)-j}] = 0.0;
            paddedImg[{i,j}] = 0.0;
        }
    }
    // the image
    for (int i=sizePad; i<img.shape()[0]; i++)
    {
        for (int j=sizePad; j<img.shape()[1];j++)
        {
            paddedImg[{i,j}] = img[{i,j}];
        }
    }
    // apply convolution
    for (int i=0; i<img.shape()[0]; ++i)
    {
        for (int j=0; j<img.shape()[1]; ++j)
        {
            Slice slice{i,i+dimFilter, j,j+dimFilter};
            std::vector<double> imageSlice = paddedImg[slice];
            double newVal = 0;
            for(int i=0;i<imageSlice.size();i++)
            {
                newVal += imageSlice.at(i) * filter[i];
            }
            convolvedImg[{i,j}] = newVal;
        }
    }
    return convolvedImg;
}
