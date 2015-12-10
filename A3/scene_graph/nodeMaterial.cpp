#include "nodeMaterial.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>

NodeMaterial::NodeMaterial(Material m){	//constructor
	nodeType = material;
	mat = m;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeMaterial::nodeSpecificCodeDown(){
	setMaterial(mat);
}

