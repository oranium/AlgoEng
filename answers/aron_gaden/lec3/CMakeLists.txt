cmake_minimum_required(VERSION 3.21)
project(mandelbrot)
project(parallel_pi_1_loc)
project(parallel_pi_cpp11)

# i set the cmake standard twice :^)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Ofast -std=c++11 -march=native -fopenmp")

add_executable(mandelbrot mandelbrot.cpp)
add_executable(parallel_pi_1_loc parallel_pi_1_loc.cpp)
add_executable(parallel_pi_cpp11 parallel_pi_cpp11.cpp)
