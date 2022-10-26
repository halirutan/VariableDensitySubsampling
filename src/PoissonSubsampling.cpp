#include "../include/PoissonSubsampling.h"

#include <string>
#include <stdexcept>

#include "../include/VariableDensity.h"
#include "../include/Approx.h"
#include "../include/VDSamplingUpper.h"
#include "../include/SamplingMask.h"

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
								float iso_fac)
{

	// seed timer for pseudo random number generation
	time_t seconds;
	time(&seconds);
	srand((unsigned) seconds);

	// flags
	bool flag_first = true;              // fix first point on/off
	bool flag_autoTest = true;          // automatic test if min_dist is too small or not on/off

	// important parameters
	//vd_options vd_op;
	long nX = lLines;                        // image height [px] y-direction
	long nY = lPartitions;                    // image width [px] z-direction
	float M = dAccel;                        // downsampling factor
	short int vd_type = v_type;              // type of variable density map
	short int smpl_type = s_type;          // type of sampling
	float pF_value = pF_val;              // applies partial fourier to the poisson disk sampling
	bool pF_x = pFx;                      // orientation of the partial fourier
	bool ellip_mask = ellipticalMask;
	short int body_region = body_part;
	SamplingMask
		samplingMask{static_cast<size_t>(lPartitions), static_cast<size_t>(lLines), static_cast<size_t>(lPhases)};

	int nPointsToTest = 20;  // determine how many points are generated/tested around one point
	float deviation = float(0.95);    // set maximal allowed deviation from undersampling factor

	float min_dist = M;                  // minimal distance around point in which no other point is allowed to be
	short int min_dist_status;    // 0 = undefined, 1 = too small, 2 = too large, 3 = best approx, 4 = done

	if ((vd_type == 3 || vd_type == 4) && fully_sampled > float(1 / M)) {
		throw std::domain_error("Number of fully_sampled-region-points is higher then the number of points to create.");
	}
	if (body_region != 0 && vd_type == 1) {
		throw std::invalid_argument("Variable Density Type can't be 1 in an a priori mask");
	}

	long nY_helper = nY;                  // is '1' if 2D-Sampling is activated
	if (nY_helper == 1) // force 2D-Sampling
	{
		smpl_type = 0;
	}

	// 2D-Sampling - options
	if (smpl_type == 0) {
		nY_helper = 1;
		ellip_mask = false;
		vd_type = 0;
	}
		// 3D-Sampling - options
	else {
		if (vd_type == 0) {
			throw std::invalid_argument("Variable Density Type can't be 0 in a 3D - Sampling Mask");
		}
	}

	VariableDensity *vd = new VariableDensity(nX, nY_helper, vd_type, fully_sampled, ellip_mask, p, n, iso_fac, M);

	if (vd_type < 6) {
		min_dist =
			Approx::findMinDistInLUT(nX, nY, M, fully_sampled, pF_value, vd_type, ellip_mask, p, iso_fac, smpl_type);
	}

	// necessary parameters for approximation of min_dist
	float step = 0;     // change of min_dist

	float *range;
	if (smpl_type != 0) {// 3D
		range = Approx::findRangeInLUT(nX, nY, M, fully_sampled, pF_value, vd_type, ellip_mask, p, iso_fac);
	}
	else {
		range = new float[2];
		range[0] = min_dist / 100;
		range[1] = min_dist * 6;
	}

	long nPointsMask = vd->genDensity();

	Approx *approx = new Approx(range, step);

	// generate Sampling object
	VDSamplingUpper *poiSamp = new VDSamplingUpper{flag_first,
												   vd_type,
												   smpl_type,
												   nX,
												   nY_helper,
												   M,
												   pF_value,
												   pF_x,
												   min_dist,
												   nPointsToTest,
												   deviation,
												   nPointsMask};

	for (size_t lPhase = 0; lPhase < lPhases; lPhase++) {
		int loopcounter = 0;
		bool failed = true;

		if (smpl_type == 1 && vd_type != 1)
			poiSamp->genMaskWithFullySampledRegion(vd);


		while (failed) {
			// generate the sampling mask
			min_dist_status = poiSamp->genSamplingMask(vd);

			// check the sampling mask and optimize min_dist if necessary
			// Note that flag_autoTest must be true so that it doesn't prompt the user.
			failed = approx->checkMask(flag_autoTest, poiSamp, min_dist_status, vd);

			// too many iterations? --> stop loop
			loopcounter++;
			if (loopcounter == 150) {
				failed = false;
			}
		}

		poiSamp->assignMaskSlice(samplingMask, lPhase);
	}

	delete poiSamp;
	delete approx;
	delete vd;

	return samplingMask;
}
