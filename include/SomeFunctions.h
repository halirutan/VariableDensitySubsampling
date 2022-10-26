#pragma once

namespace SomeFunctions
{
// =================================

	// random number between 0 and 1
	 float randZeroOne();

	// decides if something happens with a given probability
	 bool isOccurred(float probability);

	 void insertParameters(long &nX,
								 long &nY,
								 double &M,
								 float &pF,
								 bool &pF_x,
								 short int &vd_type,
								 short int &smpl_type,
								 bool &ellip_mask,
								 float &fully_sampled,
								 bool flag_insertParam,
								 short int &subsampleType);
	 void showParams(long nX,
						   long nY,
						   double M,
						   float pF,
						   bool pF_x,
						   short int vd_type,
						   short int smpl_type,
						   bool ellip_mask,
						   float fully_sampled,
						   float deviation,
						   short int body_region,
						   short int subsampleType);

	 long getLineLong(long defaultVal);
	 double getLineDouble(double defaultVal);
	 float getLineFloat(float defaultVal);
	 bool getLineBool(bool defaultVal);
	 short int getLineShort(short int defaultVal);
};