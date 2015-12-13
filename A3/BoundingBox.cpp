//bounding box class for sceneObjs
#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include <limits>
#include "boundingBox.h"

BoundingBox::BoundingBox(float objectSize) {
	this->size = objectSize;
	this->low = Point(-size, -size, -size);
	this->high = Point(size, size, size);
}

BoundingBox::~BoundingBox() {

}

//translates box with sceneObj
void BoundingBox::translateBox(float x, float y, float z){
	this->low.add(Point(x, y, z));
	this->high.add(Point(x, y, z));
}

//scales box with sceneObj
void BoundingBox::scaleBox(float x, float y, float z){
	this->low.multiply(Point(x,y,z));
	this->high.multiply(Point(x, y, z));
}

//check for intersection based on limits and ray paramaters
//returns nearest point of intersection
//if no intersection, returns -1
double BoundingBox::slab(double* p0, double* pd){
		double Tnear = -10000;
		double Tfar = 10000;
		//x
		if (pd[0]==0){
			if (p0[0]<low.x||p0[0]>high.x) return -1;
		}
		
		double T1x = (low.x - p0[0])/pd[0];
		double T2x = (high.x - p0[0])/pd[0];

		if (T1x > T2x) std::swap(T1x, T2x);
		if (T1x > Tnear) Tnear = T1x;
		if (T2x < Tfar) Tfar = T2x;
		if (Tnear > Tfar) return -1;
		if (Tfar < 0) return -1;

		double T1y = (low.y - p0[1])/pd[1];
		double T2y = (high.y - p0[1])/pd[1];

		if (T1y > T2y) std::swap(T1y, T2y);
		if (T1y > Tnear) Tnear = T1y;
		if (T2y < Tfar) Tfar = T2y;
		if (Tnear > Tfar) return -1;
		if (Tfar < 0) return -1;

		double T1z = (low.z - p0[2])/pd[2];
		double T2z = (high.z - p0[2])/pd[2];

		if (T1z > T2z) std::swap(T1z, T2z);
		if (T1z > Tnear) Tnear = T1z;
		if (T2z < Tfar) Tfar = T2z;
		if (Tnear > Tfar) return -1;
		if (Tfar < 0) return -1;

		return Tnear;
}