option(PYTHON_INT "Enable the python interface" OFF)

if(PYTHON_INT)
    add_subdirectory(python)
endif(PYTHON_INT)
