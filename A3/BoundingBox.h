#ifndef __BOUNDINGBOX_H__	//guard against cyclic dependancy
#define __BOUNDINGBOX_H__
#include "node.h"

#include <gl/glut.h>
#include "point.h"

class BoundingBox {
public:
	//constructor
	BoundingBox(float objectSize);

	//destructor
	~BoundingBox();

	void translateBox(float x, float y, float z);
	void scaleBox(float x, float y, float z);
	double slab(double* p0, double* pd);
	
private:
	float size;
	Point low;
	Point high;
};

#endif