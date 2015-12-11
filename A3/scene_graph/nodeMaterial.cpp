#include "nodeMaterial.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>

NodeMaterial::NodeMaterial(Material m){	//constructor
	this->nodeType = material;
	this->mat = m;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeMaterial::nodeSpecificCodeDown(){
	setMaterial(this->mat);
	// glMaterialfv(GL_FRONT, GL_AMBIENT, mat.ambient);
	// glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.diffuse);
	// glMaterialfv(GL_FRONT, GL_SPECULAR, mat.specular);
	// glMaterialf(GL_FRONT, GL_SHININESS, mat.shine);
}

