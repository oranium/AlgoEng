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
void transpose(const aligned_vector<double>& src, aligned_vector<double>& dst, int N, int M)
{
    // transpose over
    #pragma omp parallel for default(none) shared(N, M, dst, src)
    for(int n=0; n<N*M; n++)
    {
        int i = n / N;
        int j = n % N;
        dst[n] = src[M * j + i];
    }
}