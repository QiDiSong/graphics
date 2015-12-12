#ifndef __BOUNDINGBOX_H__	//guard against cyclic dependancy
#define __BOUNDINGBOX_H__
#include "node.h"

#include <gl/glut.h>
#include "plane.h"

class BoundingBox {
public:
	//constructor
	BoundingBox(float objectSize);

	//destructor
	~BoundingBox();

	void translateBox(float x, float y, float z);
	void scaleBox(float x, float y, float z);
	double intersects(double* nearPoint, double* farPoint);
	
private:
	Plane * top;
	Plane * bottom;
	Plane * left;
	Plane * right;
	Plane * front;
	Plane * back;
	float size;
};

#endif