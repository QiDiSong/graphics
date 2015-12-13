#ifndef __POINT_H__	//guard against cyclic dependancy
#define __POINT_H__

//3D point class
class Point{
public:
	Point();
	Point(float x, float y, float z);
	float x;
	float y;
	float z;
	void print();
	void add(Point a);
};

#endif