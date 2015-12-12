#ifndef __NODETRANSFORM_H__	//guard against cyclic dependancy
#define __NODETRANSFORM_H__

#include "node.h"
#include "structs.h"
#include <iostream>
#include <fstream>
using namespace std;

enum transformType{
	Translate,
	Rotate,
	Scale
};

class NodeTransform:public Node{
public:
	NodeTransform(transformType whatType, Vector3D vec3);	//constructor
	NodeTransform(transformType whatType, Vector4D vec4);

	transformType transformationType;
	Vector3D amount3;
	Vector4D amount4;

	virtual void nodeSpecificCodeDown();
	virtual void saveNode(ofstream& file);
};

#endif