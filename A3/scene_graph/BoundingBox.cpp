
#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include "boundingBox.h"

BoundingBox::BoundingBox(double objectSize) {
	top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, objectSize/2.0, 0.0)); //y is positive
	bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(objectSize/2.0), 0.0)); //y is negative
	left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(objectSize/2.0), 0.0, 0.0)); //x is negative
	right = new Plane(Point(1.0, 0.0, 0.0), Point(objectSize/2.0, 0.0, 0.0)); //x is positive
	front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(objectSize/2.0))); //z is negative
	back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, objectSize/2.0)); //z is positive
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

void translate(float x, float y, float z){
	top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, objectSize/2.0+y, 0.0)); //y is positive
	bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(objectSize/2.0)+y, 0.0)); //y is negative
	left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(objectSize/2.0)+x, 0.0, 0.0)); //x is negative
	right = new Plane(Point(1.0, 0.0, 0.0), Point(objectSize/2.0+x, 0.0, 0.0)); //x is positive
	front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(objectSize/2.0)+z)); //z is negative
	back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, objectSize/2.0)+z); //z is positive
}

void scale (float x, float y, float z){
	top = new Plane(Point(0.0, 1.0, 0.0), Point(0.0, objectSize/2.0*y, 0.0)); //y is positive
	bottom = new Plane(Point(0.0, -1.0, 0.0), Point(0.0, -(objectSize/2.0)*y, 0.0)); //y is negative
	left = new Plane(Point(-1.0, 0.0, 0.0), Point(-(objectSize/2.0)*x, 0.0, 0.0)); //x is negative
	right = new Plane(Point(1.0, 0.0, 0.0), Point(objectSize/2.0*x, 0.0, 0.0)); //x is positive
	front = new Plane(Point(0.0, 0.0, -1.0), Point(0.0, 0.0, -(objectSize/2.0)*z)); //z is negative
	back = new Plane(Point(0.0, 0.0, 1.0), Point(0.0, 0.0, objectSize/2.0)*z); //z is positive
}