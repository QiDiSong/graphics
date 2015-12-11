#ifndef __PLANE_H__	//guard against cyclic dependancy
#define __PLANE_H__
#include "point.h"

class Plane {
public:
	int a;
	int b;
	int c;
	int g;

	//contructor
	Plane(Point a, Point e);

	//deconstructor
	~Plane();

	//takes point to check
	bool intersects(Point p);
};

#endif