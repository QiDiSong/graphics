#include "Point.h"

class Plane {
public:
	int a;
	int b;
	int c;
	int d;

	//contructor
	Plane(Point, Point);

	//deconstructor
	~Plane();

	//takes point to check
	bool intersects(Point);
};