cmake_minimum_required(VERSION 3.14)
project(scanEnhancer LANGUAGES CXX)
project(test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# automatically build for release if no option given
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Built type" FORCE)
endif()

if(CMAKE_COMPILER_IS_GNUCXX MATCHES 1)
    set(CXX_COMPILER_IS_GNU 1)
else()
    set(CXX_COMPILER_IS_GNU 0)
endif()

if(CMAKE_CXX_COMPILER_LOADED)
    message(STATUS "Compiler path: ${CMAKE_CXX_COMPILER}")
    message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
    message(STATUS "Compiler is part of GCC: ${CMAKE_COMPILER_IS_GNUCXX}")
    message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
endif()

# possible compile options for GNU compiler
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native")

endif()

# possible compile options for (apple)clang
if(CMAKE_CXX_COMPILER_ID MATCHES "^(Apple)?Clang$")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

find_package(OpenMP REQUIRED)
# testing
Include(FetchContent)

# fetch catch2 from web for easy building
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview3
)

set(FETCHCONTENT_QUIET ON)
FetchContent_MakeAvailable(Catch2)
enable_testing()

add_executable(scanEnhancer main.cpp convolution.cpp convolution.h ppm.cpp ppm.h matrix_utils.cpp matrix_utils.h
                            filter.cpp filter.h aligned_allocator.h)

add_executable(testEnhancer tests.cpp aligned_allocator.h matrix_utils.h matrix_utils.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(scanEnhancer PUBLIC OpenMP::OpenMP_CXX)
endif()

target_link_libraries(testEnhancer PUBLIC Catch2::Catch2WithMain)

#include(CPack)
install(TARGETS scanEnhancer DESTINATION bin)
#list(APPEND CPACK_GENERATOR "DEB")
#set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Aron Gaden, Bruno Reinhold")
