add_executable(maskImage maskImage.cpp)
target_compile_options(maskImage PRIVATE -Wall -Wextra)
target_include_directories(maskImage PRIVATE "${cxxopts_SOURCE_DIR}/include")
target_link_libraries(
        maskImage
        PRIVATE
        subsample_library
)
set_target_properties(maskImage
        PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        C_VISIBILITY_PRESET hidden
        CUDA_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
        )

install(TARGETS maskImage RUNTIME DESTINATION bin)