#include "nodeMaterial.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include <iostream>
#include <fstream>

NodeMaterial::NodeMaterial(Material m){	//constructor
	this->nodeType = material;
	this->mat = m;
}

void NodeMaterial::nodeSpecificCodeDown(){
	setMaterial(this->mat);
}

//for saving SG to txt
void NodeMaterial::saveNode(ofstream& file){
	file << arrToString(this->mat.ambient);
	file << arrToString(this->mat.diffuse);
	file << arrToString(this->mat.specular);
	file << " " << this->mat.shine;
	file << " ";
	if (this->children->size()==0){
		file << endl;
		return;
	}
	for (int i=0; i<this->children->size();i++){
		this->children->at(i)->saveNode(file);
	}
}