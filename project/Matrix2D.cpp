//
// Created by Oran on 11.02.22.
//

#include "Matrix2D.h"

std::array<double, 2> Matrix2D::minmax_element()
{
    std::array<double,2> minmax{MAXFLOAT,0};
    for(auto elem:m_data)
    {
        if(elem<minmax[0]){
            minmax[0]=elem;
        }
        if(elem>minmax[1]){
            minmax[1]=elem;
        }
    }
    return minmax;
}


/*
 * Store transpose of src in dst
 */
void transpose(Matrix2D &src, Matrix2D &dst)
{
    // transpose over
    int N = src.shape()[0];
    int M = src.shape()[1];
    for(int n=0; n<N*M; n++)
    {
        int i = n/N;
        int j = n%N;
        dst[n] = src[M*j + i];
    }
}