#ifndef __NODELIGHT_H__	//guard against cyclic dependancy
#define __NODELIGHT_H__

#include "node.h"
#include <gl/glut.h>

class NodeLight:public Node{
public:
	NodeLight(float* pos, float* amb, float* dif,  float* spec, int n);	//constructor
	float* position;
	float* ambient;
	float* diffuse;
	float* specular;
	int lightNum;

	virtual void nodeSpecificCodeDown();
};

#endif