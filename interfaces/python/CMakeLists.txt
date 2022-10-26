set(TARGET_NAME subsample_python_library)
set(PY_PACKAGE_NAME subsample)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

include(FetchContent)
FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG        v2.10.0
)

FetchContent_MakeAvailable(pybind11)

file(GLOB_RECURSE cpp_sources src/*.cpp src/*.h)
file(GLOB_RECURSE py_sources subsample/*.py)

add_library(${TARGET_NAME} MODULE ${cpp_sources})

target_link_libraries(${TARGET_NAME} PRIVATE
        pybind11::module
        subsample_library
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
        )

pybind11_extension(${TARGET_NAME})
pybind11_strip(${TARGET_NAME})

set_property(
        TARGET
        ${TARGET_NAME}
        PROPERTY POSITION_INDEPENDENT_CODE ON
)

set_target_properties(${TARGET_NAME}
        PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        C_VISIBILITY_PRESET hidden
        CUDA_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
        PREFIX "${PYTHON_MODULE_PREFIX}"
        SUFFIX "${PYTHON_MODULE_EXTENSION}"
        BUILD_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${PY_PACKAGE_NAME}/libs"
        BUILD_WITH_INSTALL_RPATH TRUE
        )

# Using the project version for the Python interface version
target_compile_definitions(${TARGET_NAME} PRIVATE VERSION_INFO=${CMAKE_PROJECT_VERSION})


# Build the name of the shared lib of pybind11
set(TARGET_PYMODULE_NAME "${PYTHON_MODULE_PREFIX}${TARGET_NAME}${PYTHON_MODULE_EXTENSION}")

# __init__.py, setup.py and getwheelname.py are templates that are filled with variables defined in CMake.
# With this, things like the library name, Python package name, etc. will be dynamic.
CONFIGURE_FILE(subsample/__init__.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PY_PACKAGE_NAME}/__init__.py @ONLY
        )
CONFIGURE_FILE(setup.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/setup.py @ONLY
        )
CONFIGURE_FILE(getwheelname.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/getwheelname.py @ONLY
        )

foreach (filename ${py_sources})
    get_filename_component(target "${filename}" NAME)
    message(STATUS "Copying ${filename} to ${PY_PACKAGE_NAME}/${target}")
    configure_file("${filename}" "${CMAKE_CURRENT_BINARY_DIR}/${PY_PACKAGE_NAME}/${target}" COPYONLY)
endforeach (filename)

execute_process(COMMAND "${Python3_EXECUTABLE}" getwheelname.py OUTPUT_VARIABLE PY_WHEELFILE
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Detected Python wheel filename ${PY_WHEELFILE}")

message(STATUS "Detected Python ${Python3_EXECUTABLE}")

# Build the Python wheel. Note that you need setuptools installed in the Python you're using!
add_custom_target(PyPackageBuild
        COMMAND "${Python3_EXECUTABLE}" -m pip wheel .
        DEPENDS ${TARGET_NAME}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Building Python wheel for SubSample"
        )

# Install the wheel. This will fail if you're using a global Python installation and don't have write access.
set_target_properties(PyPackageBuild PROPERTIES Package_Name ${PY_WHEELFILE})
add_custom_target(PyPackageInstall
        COMMAND "${Python3_EXECUTABLE}" -m pip install --upgrade --force-reinstall --no-deps "${PY_WHEELFILE}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Installing wheel file"
        )
add_dependencies(PyPackageInstall PyPackageBuild)