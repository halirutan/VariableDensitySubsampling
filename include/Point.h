#pragma once

class Point
{
public:
	Point();
	Point(long gP[], float rP[], bool isP);
	~Point();

// =================================

	long *getGridPos();
	float *getRealPos();
	bool getIsPoint() const;

	void setGridPos(const long gridPosition[]);
	void setRealPos(const float realPosition[]);
	void setIsPoint(bool isPoint);

// =================================

	// "at = (0..1)" added to int-position; (at<0)? then random number (0..1) is added
	static float pointLongToFloat(long intPos, float at, long height, long width);
	void pointLongToFloat(float at, long height, long width);

	static long pointFloatToLong(float floatPos);
	void pointFloatToLong();

	void printPoint(); //prints to console

private:
	long gridPos[2];
	float realPos[2];
	bool isPoint;
};
