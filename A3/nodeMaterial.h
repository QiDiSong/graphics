#ifndef __NODEMATERIAL_H__	//guard against cyclic dependancy
#define __NODEMATERIAL_H__

#include "node.h"
#include "material.cpp"
#include <gl/glut.h>
#include <iostream>
#include <fstream>
using namespace std;

class NodeMaterial:public Node{
public:
	NodeMaterial(Material m);	//constructor
	Material mat;

	virtual void nodeSpecificCodeDown();
	virtual void saveNode(ofstream& file);
};

#endif