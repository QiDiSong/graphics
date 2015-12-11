#include "plane.h"

Plane::Plane(Point d, Point e) {
	//set first point as normal(a, b, c)
	a = d.x;
	b = d.y;
	c = d.z;

	//set second point as point(x, y, z)
	g = -(d.x*e.x + d.y*e.y + d.z + e.z);

}

Plane::~Plane()
{

}

bool Plane::intersects(Point p)
{
	return false;
}