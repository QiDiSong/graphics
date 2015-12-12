#include "plane.h"
#include <stdio.h>
#include <stdlib.h>

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

Point* Plane::intersects(double* nearPoint, double* farPoint) {
	float t;
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
			if (intersectionPoint->x > -0.5 && intersectionPoint->x < 0.5 && intersectionPoint->y > -0.5 && intersectionPoint->y < 0.5){
					printf("cube intersected front face!");
			}
			else printf("intersected plane \n");
			return intersectionPoint;
		}
	}
}