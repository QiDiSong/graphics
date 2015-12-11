#ifndef __NODEMODEL_H__	//guard against cyclic dependancy
#define __NODEMODEL_H__

#include "node.h"
#include <gl/glut.h>

enum ModelType{
	Sphere,
	Cube,
	Teapot,
	Lighting,
};



class NodeModel:public Node{
public:
	NodeModel(ModelType whatType);	//constructor

	virtual void nodeSpecificCodeDown();

	ModelType modelType;
	//BoundingBox box;


};

#endif