#ifndef __SCENEOBJ_H__	//guard against cyclic dependancy
#define __SCENEOBJ_H__

#include <windows.h>
#include <stdio.h>
#include "structs.h"
#include "node.cpp"
#include "nodeTransform.cpp"
#include "nodeModel.cpp"
#include "nodeMaterial.cpp"

enum Shape{
	CUBE,
	SPHERE,
	CONE,
	CYLINDER,
	TORUS,
	TEAPOT,
	TETRAHEDRON,
	OCTAHEDRON,
	DODECAHEDRON,
	ICOSAHEDRON
};

//scene object class
class SceneObj{
public:
	//constructor
	SceneObj();
	SceneObj(int ID, NodeTransform *transNode, NodeTransform *scaleNode, NodeTransform *rotNode, NodeMaterial *matNode, NodeModel *modelNode);

	//instance variables (add bounding box!)
	int ID;
	NodeTransform *transNode;
	NodeTransform *scaleNode;
	NodeTransform *rotNode;
	NodeMaterial *matNode;
	NodeModel *modelNode;

	//bounding box???
	
	//public methods
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotate(float x, float y, float z);

	void changeMaterial(Material m);
};

#endif