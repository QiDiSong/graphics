#include "NodeModel.h"
#include "Point.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include <iostream>
#include <fstream>

NodeModel::NodeModel(ModelType whatType){	//constructor
	nodeType = model;
	modelType = whatType;
	isDrawable = true;
	selected = false;
}

void NodeModel::nodeSpecificCodeDown(){
	switch (modelType){
	case Sphere:
		if(selected) glutWireCube(2);
		glutSolidSphere(1, 50, 50);
		break;
	case Cube:
		if(selected) glutWireCube(1.5);
		glutSolidCube(1);
		break;
	case Cone:
		if(selected){
			glTranslatef(0,0,0.5);
			glutWireCube(1);
			glTranslatef(0,0,-0.5);
		}
			glutSolidCone(0.5,1,50,50);
		break;
	case Torus:
		if(selected) glutWireCube(2);
		glutSolidTorus(0.5,0.5,50,50);
		break;
	case Teapot:
		if(selected) glutWireCube(2);
		glutSolidTeapot(1);
		break;
	case Lighting:
		if(selected) glutWireCube(1);
		glutSolidSphere(0.5,50,50);
		break;
	}
}

//for saving SG to txt
void NodeModel::saveNode(ofstream& file){
	switch (modelType){
	case Sphere:
		file << "s";
		break;
	case Cube:
		file << "C";
		break;
	case Cone:
		file << "c";
		break;
	case Torus:
		file << "t";
		break;
	case Teapot:
		file << "p";
		break;
	case Lighting:
		file << "l";
		break;
	}
	if (this->children->size()==0){
		file << endl;
		return;
	}
	for (int i=0; i<this->children->size();i++){
		this->children->at(i)->saveNode(file);
	}
}
