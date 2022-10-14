#include <string>

#include "pybind11/pybind11.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

int shittyFunc() {
	return 1;
}

PYBIND11_MODULE(subsample_lib, m) {
	m.def("shitty_func", &shittyFunc);


#ifdef VERSION_INFO
	m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
	m.attr("__version__") = "dev";
#endif
}

