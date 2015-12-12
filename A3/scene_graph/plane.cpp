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

Point Plane::intersects(double* nearPoint, double* farPoint) {
	bool result;
	topStuff = -(normal.x*origin.x + normal.y*origin.y + normal.z*origin.z + g);
	bottomStuff = (origin.x*farPoint[0] + origin.y*farPoint[1] + origin.z*farPoint[2]);
	t = topStuff/bottomStuff;
	if(t <= 0 || bottomStuff == 0) {
		result = false;
	}
	else {
		result = true;
	}
	if(result) {
		intersectionPoint = Point(nearPoint[0] + t*farPoint[0], nearPoint[1] + t*farPoint[1], nearPoint[2] + t*farPoint[2]);
		return intersectionPoint;
	}
}