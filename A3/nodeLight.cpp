#include "nodeLight.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

NodeLight::NodeLight(float* pos, float* amb, float* dif,  float* spec, int n){	//constructor
	this->position = pos;
	this->ambient = amb;
	this->diffuse = dif;
	this->specular = spec;
	this->lightNum = n;
}

void NodeLight::nodeSpecificCodeDown(){
	glEnable(GL_LIGHT0 + this->lightNum);
	glLightfv(GL_LIGHT0 + this->lightNum,GL_POSITION,this->position);
	glLightfv(GL_LIGHT0 + this->lightNum,GL_AMBIENT,this->ambient);
	glLightfv(GL_LIGHT0 + this->lightNum,GL_DIFFUSE,this->diffuse);
	glLightfv(GL_LIGHT0 + this->lightNum,GL_SPECULAR,this->specular);
}

//for saving SG to txt
//commented out for now because loading is still buggy...
void NodeLight::saveNode(ofstream& file){
	// file << "l ";
	// file << arrToString(this->position);
	// file << arrToString(this->ambient);
	// file << arrToString(this->diffuse);
	// file << arrToString(this->specular);
	// file << " " << this->lightNum;
	// file << " ";
	// if (this->children->size()==0){
	// 	file << endl;
	// 	return;
	// }
	// for (int i=0; i<this->children->size();i++){
	// 	this->children->at(i)->saveNode(file);
	// }
}

