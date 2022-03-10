//
// Created by Oran on 11.02.22.
//

#include "matrix_utils.h"
#include <algorithm>
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

void normalize(aligned_vector<double>& vec, double newMax)
{
    auto minmax = std::minmax_element (vec.begin(),vec.end());
        std::transform(vec.begin(), vec.end(), vec.begin(),
                       [& ](double elem)->double
                       {return (newMax * (elem - *minmax.first) / (*minmax.second - *minmax.first));});
}