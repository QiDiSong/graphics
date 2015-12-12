#ifndef __PLANE_H__	//guard against cyclic dependancy
#define __PLANE_H__
#include "point.h"

class Plane {
public:
	int a;
	int b;
	int c;
	int g;
	bool result;
	double topStuff;
	double bottomStuff;
	Point normal;
	Point origin;
	double t;
	Point intersectionPoint;

	//contructor
	Plane(Point a, Point e);

	//deconstructor
	~Plane();

	//takes point to check
	Point intersects(double* nearPoint, double* farPoint);
};

#endif