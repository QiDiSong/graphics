#include "nodeLight.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>

NodeLight::NodeLight(float* pos, float* amb, float* dif,  float* spec, int n){	//constructor
	this->position = pos;
	this->ambient = amb;
	this->diffuse = dif;
	this->specular = spec;
	this->lightNum = n;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeLight::nodeSpecificCodeDown(){
	glEnable(GL_LIGHT0 + this->lightNum);
	glLightfv(GL_LIGHT0 + this->lightNum,GL_POSITION,this->position);
	glLightfv(GL_LIGHT0 + this->lightNum,GL_AMBIENT,this->ambient);
	glLightfv(GL_LIGHT0 + this->lightNum,GL_DIFFUSE,this->diffuse);
	glLightfv(GL_LIGHT0 + this->lightNum,GL_SPECULAR,this->specular);
}

