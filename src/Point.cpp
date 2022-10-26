#include "../include/SubsampleMain.h"

Point::Point()
	: gridPos{0, 0}, realPos{0, 0}, isPoint(true)
{}

Point::Point(long gP[], float rP[], bool isP)
	: Point()
{
	setGridPos(gP);
	setRealPos(rP);
	setIsPoint(isP);
}

Point::~Point() = default;

long *Point::getGridPos()
{
	return gridPos;
}

float *Point::getRealPos()
{
	return realPos;
}

bool Point::getIsPoint() const
{
	return isPoint;
}

void Point::setGridPos(const long gridPosition[])
{
	for (int i = 0; i <= 1; i++)
		this->gridPos[i] = gridPosition[i];
}

void Point::setRealPos(const float realPosition[])
{
	for (int i = 0; i <= 1; i++)
		this->realPos[i] = realPosition[i];
}

void Point::setIsPoint(bool isPoint)
{
	this->isPoint = isPoint;
}

// =================================

// "at = (0..1)" added to int-postion; (at<0)? then random number (0..1) is added
float Point::pointLongToFloat(long intPos, float at, long height, long width)
{
	float floatPos;

	// randomize the position of the point
	if (at < 0) {
		floatPos = (float(intPos) + SomeFunctions::randZeroOne());
	}
	else {
		floatPos = (intPos + at);
	}
	// avoid that the index exceeds the matrix dimensions
	if (floatPos > (height - 1) || floatPos > (width - 1))
		floatPos = float(intPos);

	return floatPos;
}

void Point::pointLongToFloat(float at, long height, long width)
{
	if (at < 0 || at >= 1) // randomize the position of the point
	{
		realPos[0] = (float(gridPos[0]) + SomeFunctions::randZeroOne());
		realPos[1] = (float(gridPos[1]) + SomeFunctions::randZeroOne());
	}
	else {
		realPos[0] = (gridPos[0] + at);
		realPos[1] = (gridPos[1] + at);
	}
	// avoid that the indices exceed the matrix dimensions
	if (realPos[0] > (height - 1))
		realPos[0] = float((height - 1));
	if (realPos[1] > (width - 1))
		realPos[1] = float((width - 1));
}

long Point::pointFloatToLong(float floatPos)
{
	long intPos = long(floatPos);
	return intPos;
}
void Point::pointFloatToLong()
{
	gridPos[0] = long(realPos[0]);
	gridPos[1] = long(realPos[1]);
}

void Point::printPoint()
{
	cout << "Point: grid position: ( " << gridPos[0] << " , " << gridPos[1] << " )"
		 << " and real position: ( " << realPos[0] << " , " << realPos[1] << " )\n\n";
}
