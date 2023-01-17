cmake_minimum_required(VERSION 3.17)
project(Subsample
        VERSION 2022.0
        DESCRIPTION "Subsampling Algorithms for Kornelius"
        LANGUAGES CXX C
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED yes)

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
        GIT_TAG        v3.0.0
)
FetchContent_MakeAvailable(cxxopts)

add_subdirectory(src)
add_subdirectory(interfaces)
add_subdirectory(tests)
add_subdirectory(apps)
