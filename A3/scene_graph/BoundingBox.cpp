
#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include "boundingBox.h"

BoundingBox::BoundingBox(double objectSize) {
	this->size = objectSize;
	this->top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, size/2.0, 0.0)); //y is positive
	this->bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(size/2.0), 0.0)); //y is negative
	this->left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(size/2.0), 0.0, 0.0)); //x is negative
	this->right = new Plane(Point(1.0, 0.0, 0.0), Point(size/2.0, 0.0, 0.0)); //x is positive
	this->front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(size/2.0))); //z is negative
	this->back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, size/2.0)); //z is positive
}

BoundingBox::~BoundingBox() {

}

bool BoundingBox::intersects(int x, int y) {

}

double BoundingBox::intersects(double* near, double* far){
	//check each plane
	//create a list of distances from each plane
	//pick closest distance
	//return this distance
	//(distance will be HUGE_VALF if no intersection)
}

void BoundingBox::translate(float x, float y, float z){
	this->top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, size/2.0+y, 0.0)); //y is positive
	this->bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(size/2.0)+y, 0.0)); //y is negative
	this->left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(size/2.0)+x, 0.0, 0.0)); //x is negative
	this->right = new Plane(Point(1.0, 0.0, 0.0), Point(size/2.0+x, 0.0, 0.0)); //x is positive
	this->front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(size/2.0)+z)); //z is negative
	this->back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, size/2.0+z)); //z is positive
}

void BoundingBox::scale (float x, float y, float z){
	this->top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, size/2.0*y, 0.0)); //y is positive
	this->bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(size/2.0)*y, 0.0)); //y is negative
	this->left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(size/2.0)*x, 0.0, 0.0)); //x is negative
	this->right = new Plane(Point(1.0, 0.0, 0.0), Point(size/2.0*x, 0.0, 0.0)); //x is positive
	this->front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(size/2.0)*z)); //z is negative
	this->back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, size/2.0*z)); //z is positive
}