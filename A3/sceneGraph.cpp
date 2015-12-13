#include "sceneGraph.h"
#include "node.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "structs.h"
#include "material.h"
#include "sceneObj.h"
#include "nodeGroup.h"

SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;
}

//Scene Graph Navigation
//resets the current node to the root of the graph
void SceneGraph::goToRoot(){
	currentNode = rootNode;
}

//moves to a child node i
void SceneGraph::goToChild(int i){
	if (i < currentNode->children->size() && i >= 0)
		currentNode = currentNode->children->at(i);
	else
		printf("child out of range");
}

//moves to a child node with the ID "id"
void SceneGraph::goToChildID(int id){
	int correctIndex = -1;
	for (int i = 0; i < currentNode->children->size(); i++){
		if (currentNode->children->at(i)->ID==id){
			correctIndex = i;
			break;
		}
	}
	if (correctIndex = -1) printf("ID not found among children \n");
}

//get ID of the current node
int SceneGraph::getCurrentID(){
	return currentNode->ID;
}

void SceneGraph::goToParent(){
	if (currentNode->parent != 0)
		currentNode = currentNode->parent;
}

//inserts a child node into the current node
void SceneGraph::insertChildNodeHere(Node *node){
	currentNode->children->push_back(node);
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode(){
	vector<Node*> *tempVec = currentNode->children;
	goToParent();
	for (int i =0; i < tempVec->size(); i++){
		insertChildNodeHere(tempVec->at(i));
	}
}

//deletes the child with the given ID
void SceneGraph::deleteChildByID(int id){
	goToRoot();
	int index = -1;
	for (int i=0; i<currentNode->children->size(); i++){
		if (currentNode->children->at(i)->ID==id){
			index = i;
			currentNode->children->erase(currentNode->children->begin()+index);
			break;
		}
	}
	if (index==-1) printf("child not found \n");
}

//draw the scenegraph
void SceneGraph::draw(){
	rootNode->draw();
}

//save scenegraph to txt file
void SceneGraph::save(){
	char* name;
	std::cout << "Please select a filename (include extension): ";
	std::cin >> name;
	ofstream outfile(name);
	outfile << rootNode->children->size() << endl;
	for (int i = 0; i < rootNode->children->size(); i++){
		rootNode->children->at(i)->saveNode(outfile);
	}
	outfile.close();
}

//load scenegraph (and sceneobj list) from txt file
vector<SceneObj*>* SceneGraph::load(){
	rootNode = new Node();

	vector<SceneObj*> *sceneObjs = new vector<SceneObj*>;

	char* name;
	std::cout << "Please type the name of the file you would like to open: ";
	std::cin >> name;
	ifstream infile(name);
	
	char c;
	int lines;
	Vector4D temp4;
	Vector3D temp3;
	ModelType t;

	infile >> lines;
	for (int i = 0; i < lines-2; i++){//skipping the 2 lights for now because it's simpler
		this->goToRoot();
		//create group node
		NodeGroup *objGroup = new NodeGroup();
		this->insertChildNodeHere(objGroup);
		this->goToChild(i);
		int groupID = this->getCurrentID();
		//create translate node
		infile >> c;
		infile >> temp3.x;
		infile >> temp3.y;
		infile >> temp3.z;
		NodeTransform *trNode = new NodeTransform(Translate, temp3);
		this->insertChildNodeHere(trNode);
		this->goToChild(0);

		//create rotate node
		infile >> c;
		infile >> temp3.x;
		infile >> temp3.y;
		infile >> temp3.z;
		NodeTransform *rotNode = new NodeTransform(Rotate, temp3);
		this->insertChildNodeHere(rotNode);
		this->goToChild(0);

		//create scale node
		infile >> c;
		infile >> temp3.x;
		infile >> temp3.y;
		infile >> temp3.z;
		NodeTransform *scNode = new NodeTransform(Scale, temp3);
		this->insertChildNodeHere(rotNode);
		this->goToChild(0);

		//create material node
		infile >> temp4.x;
		infile >> temp4.y;
		infile >> temp4.z;
		infile >> temp4.w;
		float amb[4] = {temp4.x,temp4.y,temp4.z,temp4.w};
		infile >> temp4.x;
		infile >> temp4.y;
		infile >> temp4.z;
		infile >> temp4.w;
		float dif[4] = {temp4.x,temp4.y,temp4.z,temp4.w};
		infile >> temp4.x;
		infile >> temp4.y;
		infile >> temp4.z;
		infile >> temp4.w;
		float spec[4] = {temp4.x,temp4.y,temp4.z,temp4.w};
		infile >> temp3.x;

		Material m= Material (amb, dif, spec, temp3.x);
		NodeMaterial *matNode = new NodeMaterial(m);
		this->insertChildNodeHere(matNode);
		this->goToChild(0);

		infile >> c;
		switch (c){
			case 's':
			t = Sphere;
			break;
			case 'C':
			t = Cube;
			break;
			case 'c':
			t = Cone;
			break;
			case 't':
			t = Torus;
			break;
			case 'p':
			t = Teapot;
			break;
		}

		NodeModel *modelNode = new NodeModel(t);
		this->insertChildNodeHere(modelNode);

		SceneObj* newObj = new SceneObj(groupID, trNode, scNode, rotNode, matNode, modelNode);
		sceneObjs->push_back(newObj);
		
	}
	infile.close();
	return sceneObjs;
}