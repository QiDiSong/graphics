#include "nodeTransform.h"
#include <stdio.h> //needed for printf command
#include <gl/glut.h>
#include <iostream>
#include <fstream>

//for gltranslate and gl scale
NodeTransform::NodeTransform(transformType whatType, Vector3D vec3){
	nodeType = transformation;
	transformationType = whatType;
	amount3 = vec3;
}

void NodeTransform::nodeSpecificCodeDown(){
	switch (transformationType){
	case Translate:
		glTranslatef(amount3.x, amount3.y, amount3.z);
		break;
	case Rotate:
		glRotatef(amount3.x,1, 0, 0);
		glRotatef(amount3.y,0,1,0);
		glRotatef(amount3.z,0,0,1);
		
		break;
	case Scale:
		glScalef(amount3.x, amount3.y, amount3.z);
		break;
	}
}

//for saving SG to txt
void NodeTransform::saveNode(ofstream& file){
	switch (transformationType){
	case Translate:
		file << "t";
		break;
	case Rotate:
		file << "r";
		break;
	case Scale:
		file << "s";
		break;
	}
	file << " "<< amount3.x;
	file << " "<< amount3.y;
	file << " "<< amount3.z;
	file << " ";
	if (this->children->size()==0){
		file << endl;
		return;
	}
	for (int i=0; i<this->children->size();i++){
		this->children->at(i)->saveNode(file);
	}
}
