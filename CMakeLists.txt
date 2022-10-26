cmake_minimum_required(VERSION 3.17)
project(Subsample
        VERSION 2022.0
        DESCRIPTION "Subsampling Algorithms for Kornelius"
        LANGUAGES CXX C
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED yes)


add_subdirectory(src)
add_subdirectory(interfaces)
add_subdirectory(tests)

