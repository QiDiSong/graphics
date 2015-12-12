
#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include "boundingBox.h"

BoundingBox::BoundingBox(float objectSize) {
	this->size = objectSize;
	this->top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, size/2.0, 0.0)); //y is positive
	this->bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(size/2.0), 0.0)); //y is negative
	this->left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(size/2.0), 0.0, 0.0)); //x is negative
	this->right = new Plane(Point(1.0, 0.0, 0.0), Point(size/2.0, 0.0, 0.0)); //x is positive
	this->front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(size/2.0))); //z is negative
	this->back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, size/2.0)); //z is positive
	printf("i am a box \n");
}

BoundingBox::~BoundingBox() {

}

void BoundingBox::translateBox(float x, float y, float z){
	this->top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, size/2.0+y, 0.0)); //y is positive
	this->bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(size/2.0)+y, 0.0)); //y is negative
	this->left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(size/2.0)+x, 0.0, 0.0)); //x is negative
	this->right = new Plane(Point(1.0, 0.0, 0.0), Point(size/2.0+x, 0.0, 0.0)); //x is positive
	this->front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(size/2.0)+z)); //z is negative
	this->back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, size/2.0+z)); //z is positive
}

void BoundingBox::scaleBox(float x, float y, float z){
	this->top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, size/2.0*y, 0.0)); //y is positive
	this->bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(size/2.0)*y, 0.0)); //y is negative
	this->left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(size/2.0)*x, 0.0, 0.0)); //x is negative
	this->right = new Plane(Point(1.0, 0.0, 0.0), Point(size/2.0*x, 0.0, 0.0)); //x is positive
	this->front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(size/2.0)*z)); //z is negative
	this->back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, size/2.0*z)); //z is positive
}

double BoundingBox::intersects(double* nearPoint, double* farPoint){
	Point** intersections;
	top->intersects(nearPoint, farPoint);
	bottom->intersects(nearPoint, farPoint);
	left->intersects(nearPoint, farPoint);
	right->intersects(nearPoint, farPoint);
	back->intersects(nearPoint, farPoint);
	front->intersects(nearPoint, farPoint);
	return 0;
}
