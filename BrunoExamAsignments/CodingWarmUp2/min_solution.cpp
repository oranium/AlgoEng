#include <atomic>
#include <iostream>
#include <mutex>
#include <omp.h>

using namespace std;

bool is_solution(int number) { // test if number solves the problem
    for (volatile int i = 10000000; i--;) {} // mock computation
    return number > 133 && number < 140;
}

int main() {
    constexpr int biggest_possible_number = 10000;
    atomic<int> final_solution(INT32_MAX);
    const double start = omp_get_wtime();
    mutex mtx;

#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < biggest_possible_number; ++i) {
        if (final_solution < i)
            continue;
#pragma omp critical
{
        if (is_solution(i)) {
            final_solution = i;
        }
}
    }
    // end parallel region
    // check if we've found a solution at all is omitted, you can add the check
    cout << "The smallest solution is: " << final_solution << endl;
    cout << omp_get_wtime() - start << " seconds" << endl;
}

