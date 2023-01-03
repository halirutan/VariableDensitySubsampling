file(GLOB_RECURSE
        HEADER_LIST
        LIST_DIRECTORIES false
        CONFIGURE_DEPENDS
        "${Subsample_SOURCE_DIR}/include/*.h*")

add_library(subsample_library
        STATIC
        Approx.cpp
        LinkedList.cpp
        Point.cpp
        PoissonSubsampling.cpp
        SamplingMask.cpp
        SomeFunctions.cpp
        SubsampleMain.cpp
        VariableDensity.cpp
        VDSamplingUpper.cpp
        StdoutRedirector.cpp
        )

target_include_directories(subsample_library
        PUBLIC "${Subsample_SOURCE_DIR}/include"
        )
target_compile_features(subsample_library PUBLIC cxx_std_17)
target_compile_options(subsample_library PRIVATE -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable)
set_target_properties(subsample_library
        PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        INTERFACE_POSITION_INDEPENDENT_CODE ON
        CXX_VISIBILITY_PRESET hidden
        C_VISIBILITY_PRESET hidden
        CUDA_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
        )

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

install (TARGETS subsample_library
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT RuntimeLibraries
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT RuntimeLibraries
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/include" COMPONENT Development
        )