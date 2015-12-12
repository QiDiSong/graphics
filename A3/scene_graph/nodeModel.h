#ifndef __NODEMODEL_H__	//guard against cyclic dependancy
#define __NODEMODEL_H__

#include "node.h"
#include <gl/glut.h>
#include <iostream>
#include <fstream>
using namespace std;

enum ModelType{
	Sphere,
	Cube,
	Cone,
	Torus,
	Dodecahedron,
	Lighting,
};



class NodeModel:public Node{
public:
	NodeModel(ModelType whatType);	//constructor

	virtual void nodeSpecificCodeDown();
	virtual void saveNode(ofstream& file);

	ModelType modelType;
	//BoundingBox box;


};

#endif