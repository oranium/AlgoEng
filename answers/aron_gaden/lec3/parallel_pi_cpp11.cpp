#include <iomanip>
#include <iostream>
#include <omp.h>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

mutex mtx;
void pi_step(int step, double width, int iterations, double &sum)
{
    double x=0.0;
    double local_sum = 0.0;
    for(int i=step*iterations; i<step*iterations+iterations; ++i)
    {
        x = (i + 0.5) * width; // midpoint
        local_sum += (1.0 / (1.0 + x * x));
    }
    // critical section
    mtx.lock();
    sum += local_sum ; // add new height of a rectangle
    mtx.unlock();
}

int main() {
    double start_time = omp_get_wtime();
    double sum = 0.0;
    int num_steps = 100000000; // amount of rectangles
    int num_threads = thread::hardware_concurrency();
    int iterations = num_steps / num_threads;
    double width = 1.0 / double(num_steps); // width of a rectangle
    vector<thread> ths;
    // create the desired number of threads
    for (int i = 0; i < num_threads; i++) {
        ths.push_back(thread(pi_step, i, width, iterations, ref(sum)));
    }
    // wait for threads to finish
    for (thread &t: ths) {
        t.join();
    }
    double pi = sum * 4 * width; // compute pi
    double run_time = omp_get_wtime() - start_time;

    cout << "pi with " << num_steps << " steps is " << setprecision(17)
         << pi << " in " << setprecision(6) << run_time << " seconds\n";
}
