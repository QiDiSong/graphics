#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include "BoundingBox.h"


BoundingBox::BoundingBox(double objectSize) {
	double objectSize = 1.0;
	top = Plane(Point(0.0, 1.0, 0.0), Point(0.0, objectSize/2.0, 0.0)); //y is positive
	bottom = Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(objectSize/2.0), 0.0)); //y is negative
	left = Plane(Point(-1.0, 0.0, 0.0), Point(-(objectSize/2.0), 0.0, 0.0)); //x is negative
	right = Plane(Point(1.0, 0.0, 0.0), Point(objectSize/2.0, 0.0, 0.0)); //x is positive
	front = Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(objectSize/2.0)); //z is negative
	back = Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, objectSize/2.0)); //z is positive
}

BoundingBox::~BoundingBox() {

}