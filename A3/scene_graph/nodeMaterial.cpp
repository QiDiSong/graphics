#include "nodeMaterial.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>
#include <iostream>
#include <fstream>

NodeMaterial::NodeMaterial(Material m){	//constructor
	this->nodeType = material;
	this->mat = m;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeMaterial::nodeSpecificCodeDown(){
	setMaterial(this->mat);
}

void NodeMaterial::saveNode(ofstream& file){
	file << "M,";
	if (this->children->size()==0){
		file << endl;
		return;
	}
	for (int i=0; i<this->children->size();i++){
		this->children->at(i)->saveNode(file);
	}
}
