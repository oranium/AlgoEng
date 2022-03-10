#include <vector>
#include <iostream>
#include <parallel/algorithm>
#include "merge_dac_parallel.cpp"

using namespace std;
int main(int argc, char *argv[]) {
    const int n = 50000000;
    vector<int> v1 = get_random_int_vector(n);
    vector<int> v2 = get_random_int_vector(n);

    // sort both vectors before merging
    __gnu_parallel::sort(begin(v1), end(v1));
    __gnu_parallel::sort(begin(v2), end(v2));

    // merge into these vectors
    vector<int> out1(2 * n);
    vector<int> out2(2 * n);
    vector<int> out3(2 * n);

    // test different merge implementations
    double start = omp_get_wtime();
    parallel_merge(v1.data(), v2.data(), out1.data(), n, n, omp_get_num_procs(), less<>());
    cout << "custom merge: " << omp_get_wtime() - start << " seconds" << endl;

    start = omp_get_wtime();
    __gnu_parallel::merge(begin(v1), end(v1), begin(v2), end(v2), begin(out2));
    cout << "__gnu_parallel::merge: " << omp_get_wtime() - start << " seconds" << endl;

    start = omp_get_wtime();
    std::merge(begin(v1), end(v1), begin(v2), end(v2), begin(out3));
    cout << "std::merge: " << omp_get_wtime() - start << " seconds" << endl;

    if (out1 != out2 || out3 != out2) {
        cout << "merge implementation is buggy\n";
    }
}