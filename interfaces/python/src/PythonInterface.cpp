#include "pybind11/pybind11.h"
#include "../../../include/SamplingMask.h"
#include "../../../include/PoissonSubsampling.h"

namespace py = pybind11;


PYBIND11_MODULE(subsample_lib, m)
{

	m.def("pd_sampling", [](
			  long lLines,
			  long lPartitions,
			  float dAccel,
			  float fully_sampled,
			  float pF_val,
			  bool pFx,
			  int lPhases,
			  short int v_type,
			  short int s_type,
			  bool ellipticalMask,
			  float p,
			  float n,
			  short int body_part,
			  float iso_fa
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
				body_part,
				iso_fa);
		  },
		  py::kw_only(),
		  py::arg("lines"),
		  py::arg("partitions"),
		  py::arg("dAccel"),
		  py::arg("fully_sampled"),
		  py::arg("pF_val"),
		  py::arg("pFx"),
		  py::arg("lPhases"),
		  py::arg("v_type"),
		  py::arg("s_type"),
		  py::arg("ellipticalMask"),
		  py::arg("p"),
		  py::arg("n"),
		  py::arg("body_part"),
		  py::arg("iso_fa")
	);

	py::class_<SamplingMask>(m, "SamplingMask", py::buffer_protocol())
		.def_buffer([](SamplingMask &m) -> py::buffer_info
					{
						return py::buffer_info(
							m.data(),                               /* Pointer to buffer */
							sizeof(int),                          /* Size of one scalar */
							py::format_descriptor<int>::format(), /* Python struct-style format descriptor */
							3,                                      /* Number of dimensions */
							{m.width(), m.height(), m.phases()},                 /* Buffer dimensions */
							{sizeof(int) * m.width() * m.height(),             /* Strides (in bytes) for each index */
							 sizeof(int) * m.width(),
							 sizeof(int)}
						);
					});
}

