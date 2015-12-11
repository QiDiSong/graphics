#include "plane.h"

Plane::Plane(Point a, Point b) {
	//set first point as normal(a, b, c)
	this->a = a.x;
	this->b = a.y;
	this->c = a.z;

	//set second point as point(x, y, z)
	this->d = -(a.x*b.x + a.y*b.y + a.z + b.z);

}

Plane::~Plane()
{

}

bool Plane::intersects(Plane a)
{
	return false;
}