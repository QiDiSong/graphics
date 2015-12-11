#ifndef __PLANE_H__	//guard against cyclic dependancy
#define __PLANE_H__
#include "point.h"

class Plane {
public:
	int a;
	int b;
	int c;
	int d;

	//contructor
	Plane(Point a, Point b);

	//deconstructor
	~Plane();

	//takes point to check
	bool intersects(Plane a);
};

#endif