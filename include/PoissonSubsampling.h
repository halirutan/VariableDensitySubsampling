#pragma once
#include "SamplingMask.h"

/**
 * Samples an elliptical region according to a Poisson distribution
 * Argument documentation can be found in the Python interface.
 */
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
                                float power,
                                float root,
								bool removeKSpaceCenter,
                                short int body_part,
                                float iso_fac,
                                unsigned int random_seed,
                                bool logging);