#ifndef __PLANE_H__	//guard against cyclic dependancy
#define __PLANE_H__
#include "point.h"

class Plane {
public:
	float a;
	float b;
	float c;
	float d;
	// bool result;
	// double topStuff;
	// double bottomStuff;
	double t;
	Point* intersectionPoint;
	float distance;
	float xDistance, yDistance, zDistance;

	//contructor
	Plane(Point a, Point e);

	//deconstructor
	~Plane();

	//takes point to check
	Point* intersects(double* nearPoint, double* farPoint, Point low, Point high);
};

#endif