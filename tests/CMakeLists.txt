# Testing library
# We're fetching it directly from GitHub.
include(FetchContent)
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(catch2)

# Include their .cmake file so that all CTests inside a target are
# discovered automatically.
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

# Set up a target for our test-code
add_executable(test_subsample
        TestMain.cpp
        )

#target_link_libraries(test_nreco PRIVATE nreco_library Catch2::Catch2 Boost::log)

target_link_libraries(test_subsample PRIVATE subsample_library Catch2::Catch2)
set_target_properties(test_subsample
        PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        C_VISIBILITY_PRESET hidden
        CUDA_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
        )

target_compile_definitions(test_subsample PRIVATE -DSUBSAMPLE_TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")


catch_discover_tests(test_subsample)
