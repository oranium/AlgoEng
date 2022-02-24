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
    mutex m; // mutual exclusion construct for updating final_solution

#pragma omp parallel for schedule(dynamic) // we could also use schedule(static, 1)
    for (int i = 0; i < biggest_possible_number; ++i) {
        if (final_solution < i) // we found a smaller solution, just continue iterating
            continue;
        // i tried this solution instead of the lock guard, but it is around 3 times slower
        // i also tried std::mutex.lock(), which is just as slow
        // because the lockguard only locks for the duration of the load?
#pragma omp critical
{
        if (is_solution(i)) {    // one solution found, update final_solution if it's smaller
            final_solution = i;
        }
}
    }
    // end parallel region
    // check if we've found a solution at all is omitted, you can add the check
    cout << "The smallest solution is: " << final_solution << endl;
    cout << omp_get_wtime() - start << " seconds" << endl;
}