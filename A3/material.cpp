#include <gl/glut.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "material.h"

/*Material*/
Material::Material(){
}

Material::Material(float* amb, float* dif, float* spec, float sh){
	this->ambient = amb;
	this->diffuse = dif;
	this->specular = spec;
	this->shine = sh;
}

//set current draw material to the given material
void setMaterial(Material m){
	glMaterialfv(GL_FRONT, GL_AMBIENT, m.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, m.shine);
}