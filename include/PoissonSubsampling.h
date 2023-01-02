#pragma once
#include "SamplingMask.h"

/**
 * Samples an elliptical region according to a Poisson distribution
 * @param lLines
 * @param lPartitions
 * @param dAccel
 * @param fully_sampled
 * @param pF_val
 * @param pFx
 * @param lPhases
 * @param v_type
 * @param s_type
 * @param ellipticalMask
 * @param p
 * @param n
 * @param body_part
 * @param iso_fac
 * @param random_seed If greater than zero, then this value is used for initialization the random generator.
 * @return
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
								float p,
								float n,
								short int body_part,
								float iso_fac,
								unsigned int random_seed);