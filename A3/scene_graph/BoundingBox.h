#ifndef __BOUNDINGBOX_H__	//guard against cyclic dependancy
#define __BOUNDINGBOX_H__

#include <gl/glut.h>
#include "plane.h"

class BoundingBox {
public:
	//constructor
	//BoundingBox();
	BoundingBox(double);

	//destructor
	~BoundingBox();
private:
	Plane top;
	Plane bottom;
	Plane left;
	Plane right;
	Plane front;
	Plane back;
};