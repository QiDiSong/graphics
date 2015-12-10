#include "sceneGraph.h"
#include "node.h"
#include <stdio.h>

SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;
	printf("scene graph init done\n");
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

//draw the scenegraph
void SceneGraph::draw(){
	rootNode->draw();
}