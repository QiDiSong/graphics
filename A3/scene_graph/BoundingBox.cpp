
#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include "boundingBox.h"

BoundingBox::BoundingBox(double size) {
	this->objectSize = 1.0;
	this->top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, objectSize/2.0, 0.0)); //y is positive
	this->bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(objectSize/2.0), 0.0)); //y is negative
	this->left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(objectSize/2.0), 0.0, 0.0)); //x is negative
	this->right = new Plane(Point(1.0, 0.0, 0.0), Point(objectSize/2.0, 0.0, 0.0)); //x is positive
	this->front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(objectSize/2.0))); //z is negative
	this->back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, objectSize/2.0)); //z is positive
}

BoundingBox::~BoundingBox() {

}