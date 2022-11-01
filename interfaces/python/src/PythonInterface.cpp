#include "pybind11/pybind11.h"
#include "SamplingMask.h"
#include "PoissonSubsampling.h"

namespace py = pybind11;


PYBIND11_MODULE(subsample_python_library, m)
{
	m.doc() = "This is a Python binding of the C++ CS_MoCo_LAB Library";
	// Import detail: We switch lPartitions and lLines here because it seems "width" and "height" of the output
	// was confused inside the library. To give a predictable result that actually agrees with the passed width
	// and height arguments inside Python, we hack around this here.
	m.def("pd_sampling", [](
			  long lPartitions,
			  long lLines,
			  float dAccel,
			  float fully_sampled,
			  float pF_val,
			  bool pFx,
			  int lPhases,
			  short int v_type,
			  short int s_type,
			  bool ellipticalMask,
			  float p,
			  float n
		  )
		  {
			  return poissonSubsampling(
				  lLines,
				  lPartitions,
				  dAccel,
				  fully_sampled,
				  pF_val,
				  pFx,
				  lPhases,
				  v_type,
				  s_type,
				  ellipticalMask,
				  p,
				  n,
				  0,
				  1.0);
		  },
		  py::kw_only(),
		  py::arg("width"),
		  py::arg("height"),
		  py::arg("acceleration"),
		  py::arg("fully_sampled_fraction"),
		  py::arg("espresso_factor"),
		  py::arg("espresso_direction"),
		  py::arg("phases"),
		  py::arg("variable_density_type"),
		  py::arg("sample_type"),
		  py::arg("elliptical_mask"),
		  py::arg("power"),
		  py::arg("root")
	);

	py::class_<SamplingMask>(m, "SamplingMask", py::buffer_protocol())
		.def_buffer([](SamplingMask &m) -> py::buffer_info
					{
						return py::buffer_info(
							m.data().get(),                               /* Pointer to buffer */
							sizeof(int),                          /* Size of one scalar */
							py::format_descriptor<int>::format(), /* Python struct-style format descriptor */
							3,                                      /* Number of dimensions */
							{m.phases(), m.height(), m.width()},                 /* Buffer dimensions */
							{             /* Strides (in bytes) for each index */
								sizeof(int) * m.width() * m.height(),
								sizeof(int) * m.width(),
								sizeof(int)
							},
							true
						);
					});
}

