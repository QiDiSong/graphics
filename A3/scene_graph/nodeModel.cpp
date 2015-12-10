#include "NodeModel.h"
#include "Point.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>

NodeModel::NodeModel(ModelType whatType){	//constructor
	nodeType = model;
	modelType = whatType;
	isDrawable = true;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeModel::nodeSpecificCodeDown(){
	switch (modelType){
	case Sphere:
		glutSolidSphere(1, 100, 100);
		//box = BoundingBox(1);
		break;
	case Cube:
		glutSolidCube(1);
		//box = BoundingBox(1);
		break;
	case Teapot:
		glutSolidTeapot(1);
		break;
	case Custom:
		//own mesh thing
		break;
	}
}
