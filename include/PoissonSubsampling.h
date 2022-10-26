#pragma once
#include "SamplingMask.h"

SamplingMask poissonSubsampling(long lLines,
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
								float iso_fac);