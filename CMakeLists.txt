cmake_minimum_required(VERSION 3.20)
project(repo)
project(project)
find_package(OpenMP REQUIRED)
#string(REPLACE "-Xclang" "" OpenMP_CXX_FLAGS_GPP "$OpenMP_CXX_FLAGS")

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS_GPP}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
#set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-11")
find_package(OpenMP REQUIRED)
add_executable(repo
        answers/warmup/1/hello.cpp answers/warmup/4/pi_singleline_parallel.cpp answers/warmup/4/pi_parallel_standard_cpp.cpp project/read_ppm.h project/read_ppm.cpp)
add_executable(project
        project/read_ppm.h project/read_ppm.cpp project/filter.cpp project/filter.h)

target_link_libraries(repo PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(project PUBLIC OpenMP::OpenMP_CXX)