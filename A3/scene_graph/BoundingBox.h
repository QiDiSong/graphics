#include "node.h"
#include <gl/glut.h>
#include "plane.h"

class BoundingBox {
public:
	//constructor
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
	BoundingBox box;
};