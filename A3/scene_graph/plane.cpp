#include "plane.h"

Plane::Plane(Point normal, Point origin) {
	//set first point as normal(a, b, c)
	a = normal.x;
	b = normal.y;
	c = normal.z;

	//set second point as point(x, y, z)
	g = -(normal.x*origin.x + normal.y*origin.y + normal.z*origin.z);

}

Plane::~Plane()
{

}

bool Plane::intersects(Point p)
{
	return false;
}