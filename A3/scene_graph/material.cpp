#include <gl/glut.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "material.h"

/*Material*/
Material::Material(){
	//bloop
}

Material::Material(float amb[4], float dif[4], float spec[4], float sh){
	*this->ambient = *amb;
	*this->diffuse = *dif;
	*this->specular = *spec;
	this->shine = sh;
}

void setMaterial(Material m){
	glMaterialfv(GL_FRONT, GL_AMBIENT, m.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, m.shine);
}