#include "nodeGroup.h"
#include <stdio.h> //needed for printf command
#include <gl/glut.h>
#include <iostream>
#include <fstream>
using namespace std;

NodeGroup::NodeGroup(){
	nodeType = group;
}

void NodeGroup::nodeSpecificCodeDown(){
	glPushMatrix();
}

void NodeGroup::nodeSpecificCodeUp(){
	glPopMatrix();
}

void NodeGroup::saveNode(ofstream& file){
	file << "g,";
	if (this->children->size()==0){
		file << endl;
		return;
	}
	for (int i=0; i<this->children->size();i++){
		this->children->at(i)->saveNode(file);
	}
}