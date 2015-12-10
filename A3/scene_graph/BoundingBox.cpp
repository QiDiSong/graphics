#include "NodeModel.h"
#include "Point.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>

BoundingBox::BoundingBox(double objectSize) {
	double objectSize = 1.0;
	top = BoundingBox(Point::Point(0.0, 1.0, 0.0), Point::Point(0.0, objectSize/2.0, 0.0)); //y is positive
	bottom = BoundingBox(Point::Point(0.0, -1.0, 0.0), Point::Point(0.0, -(objectSize/2.0), 0.0)); //y is negative
	left = BoundingBox(Point::Point(-1.0, 0.0, 0.0), Point::Point(-(objectSize/2.0), 0.0, 0.0)); //x is negative
	right = BoundingBox(Point::Point(1.0, 0.0, 0.0), Point::Point(objectSize/2.0, 0.0, 0.0)); //x is positive
	front = BoundingBox(Point::Point(0.0, 0.0, -1.0), Point::Point(0.0, 0.0, -(objectSize/2.0)); //z is negative
	back = BoundingBox(Point::Point(0.0, 0.0, 1.0), Point::Point(0.0, 0.0, objectSize/2.0)); //z is positive
}

BoundingBox::~BoundingBox() {

}