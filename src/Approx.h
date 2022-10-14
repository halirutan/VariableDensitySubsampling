#pragma once

class Approx
{
public:
	Approx();
	Approx(const float range[], float step);
	~Approx();

// ==================================

	float* getRange();
	float getStep() const;

	void setStep(float stepSize);

// ==================================

    // find optimal starting point for minimal distance
	static float findMinDistInLUT(long nX, long nY, double M, float fs, float pF_value, short int vd_type, bool ellip_mask, float p, float iso_fac, short int smpl_type);

    // find starting range for bisection of minimal distance in iterations
    static float* findRangeInLUT(long nX, long nY, double M, float fs, float pF_value, short int vd_type, bool ellip_mask, float p, float iso_fac);

	// check the mask and optimize min_dist with bisection if necessary
	bool checkMask(bool flag_autoTest, VDSamplingUpper *poiSamp, short int min_dist_status, VariableDensity *vd);

	// looks for empty regions in the sampling mask
	bool autoTest(int **samplingMask, long height, long width, long *pF_border, float **fraction, float &min_dist);

private:
	float range[2];
	float step;
};

