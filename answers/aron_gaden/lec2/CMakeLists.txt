cmake_minimum_required(VERSION 3.21)
project(parallel_rc)
project(image_denoise)
project(min_solution_lock)

set(CMAKE_CXX_STANDARD 17)

add_executable(parallel_rc pi_parallel_rc.cpp)
add_executable(image_denoise image_denoise.cpp)
add_executable(min_solution_lock min_solution.cpp)
find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    target_link_libraries(parallel_rc PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(image_denoise PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(min_solution_lock PUBLIC OpenMP::OpenMP_CXX)
endif()
