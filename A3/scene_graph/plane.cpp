#include "plane.h"
#include <stdio.h>
#include <stdlib.h>
#include "BoundingBox.h"
#include <math.h>

Plane::Plane(Point normal, Point origin) {
	//set first point as normal(a, b, c)
	this->a = normal.x;
	this->b = normal.y;
	this->c = normal.z;

	//set second point as point(x, y, z)
	this->d = -(normal.x*origin.x + normal.y*origin.y + normal.z*origin.z);

}

Plane::~Plane()
{

}

Point* Plane::intersects(double* nearPoint, double* farPoint, Point low, Point high) {
	float t;
	bool hit;
	float xDistance, yDistance, zDistance;
	Point * intersectionPoint;
	float topStuff = -(this->a*nearPoint[0] + this->b*nearPoint[1] + this->c*nearPoint[2] + d);
	float bottomStuff = (this->a*(float)farPoint[0] + this->b*(float)farPoint[1] + this->c*(float)farPoint[2]);
	if (bottomStuff==0){
		printf("zero denominator \n");
		return 0;
	}
	else{
		t = topStuff/bottomStuff;
		if(t <= 0){return 0; printf("no intersection");}
		else{
			intersectionPoint = new Point((float)nearPoint[0] + t*(float)farPoint[0], (float)nearPoint[1] + t*(float)farPoint[1], (float)nearPoint[2] + t*(float)farPoint[2]);
			//printf("x: %f \ny: %f \nz: %f \n \n", intersectionPoint->x, intersectionPoint->y, intersectionPoint->z);
			//return intersectionPoint;
		}
	}

	//calculate distance between ray origin and intersection point
	xDistance = intersectionPoint->x - nearPoint[0];
	yDistance = intersectionPoint->y - nearPoint[1];
	zDistance = intersectionPoint->z - nearPoint[2];
	distance = sqrt((xDistance * xDistance) + (yDistance * yDistance) + (zDistance * zDistance));


	//x side
	if((intersectionPoint->y >= low.y) && (intersectionPoint->y <= high.y) && (intersectionPoint->z >= low.z) && (intersectionPoint->z <= high.z)) {
		hit = true;
		printf("Hit X! \n");
		printf("Distance: %f \n", distance);
	}

	//y side
	if((intersectionPoint->x >= low.x) && (intersectionPoint->x <= high.x) && (intersectionPoint->z >= low.z) && (intersectionPoint->z <= high.z)) {
		hit = true;
		printf("Hit Y! \n");
	}
	//z side
	if((intersectionPoint->y >= low.y) && (intersectionPoint->y <= high.y) && (intersectionPoint->x >= low.x) && (intersectionPoint->x <= high.x)) {
		hit = true;
		printf("Hit Z! \n");
	}
	else {
		hit = false;
		printf("No Hit! \n");
	}

	return intersectionPoint;


}