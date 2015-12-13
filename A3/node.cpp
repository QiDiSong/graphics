#include "node.h"
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;
Node::Node(){	//constructor
	ID = getID();
	nodeType = root; //base class will be only really our root node, so lets do that
	isDrawable = false;
	children = new vector<Node*>();
	parent = 0;
	currentChild = 0;
}

//==================================================================
//function which does all the heavy lifting
void Node::draw(){
	//we entered node, so execute the commands
	//ie. push matrix, apply material, draw geometry, etc.
	nodeSpecificCodeDown();

	//recursively call our children
	const int numberOfChildren = children->size();
	if (numberOfChildren > 0){
		for (int i = 0; i < numberOfChildren; i++){
			children->at(i)->draw();
		}
	}

	//we are exiting the node, so execute the commands
	//ie. pop matrix, etc.
	nodeSpecificCodeUp();
}

//====================================================================
//FUNCTION THAT DOES THE ACTUAL STUFF IN 
//DERIVED CLASSES

//TO BE OVERRIDDEN IN CHILD CLASSES AS NEEDED
//code where we add what the node will do when moving down the tree
void Node::nodeSpecificCodeDown(){}

//code where we add what the node will do when moving up the tree
void Node::nodeSpecificCodeUp(){}

void Node::saveNode(ofstream& file){};

string myConvert(float value)
{
  stringstream ss;
  //ss << setprecision(numeric_limits<float>::digits10+1);
  ss << value;
  return ss.str();
}

string Node::arrToString(float* arr){
	string val = "";
	for (int i = 0; i < 4; i++){
		val += " " + myConvert(arr[i]);
	}
	return val;
}