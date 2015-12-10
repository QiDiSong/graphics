#include "plane.h"

Plane::Plane(Point a, Point b) {
	//set first point as normal(a, b, c)
	a = a.x;
	b = a.y;
	c = a.z;

	//set second point as point(x, y, z)
	d = -(a.x*b.x + a.y*b.y + a.z + b.z);

}

Plane::~Plane()
{

}

bool Plane::intersects(Plane a)
{
	return false;
}