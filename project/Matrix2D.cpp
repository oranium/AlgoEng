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
void transpose(const std::vector<double>& src, std::vector<double>& dst, int N, int M)
{
    // transpose over
    for(int n=0; n<N*M; n++)
    {
        int i = n / N;
        int j = n % N;
        dst[n] = src[M * j + i];

    }
}