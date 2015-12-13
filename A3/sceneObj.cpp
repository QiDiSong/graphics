#include <gl/glut.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "sceneObj.h"


/*SceneObj*/
SceneObj::SceneObj(int ID, NodeTransform *transNode, NodeTransform *scaleNode, NodeTransform *rotNode, NodeMaterial *matNode, NodeModel *modelNode){ //modify this to include instantiation of material, later
	this->ID = ID;
	this->transNode = transNode;
	this->scaleNode = scaleNode;
	this->rotNode = rotNode;
	this->matNode = matNode;
	this->modelNode = modelNode;
	this->isLight = false;
	switch (modelNode->modelType){
	case Sphere:
		this->box = new BoundingBox(2);
		break;
	case Cube:
		this->box = new BoundingBox(0.5);
		break;
	case Cone:
		this->box = new BoundingBox(1);
		break;
	case Torus:
		this->box = new BoundingBox(1);
		break;
	case Teapot:
		this->box = new BoundingBox(2);
		break;
	}
}

//lighting obj
SceneObj::SceneObj(int ID, NodeTransform *transNode, NodeLight *lightNode, NodeModel *modelNode){
	this->ID = ID;
	this->transNode = transNode;
	this->modelNode = modelNode;
	this->lightNode = lightNode;
	this->box = new BoundingBox(0.5);
	this->box->translateBox(this->lightNode->position[0],this->lightNode->position[1],this->lightNode->position[2]);
	this->isLight=true;
}

void SceneObj::select(){
	this->modelNode->selected=true;
}

void SceneObj::unselect(){
	this->modelNode->selected=false;
}

void SceneObj::changeMaterial(Material m){
	this->matNode->mat = m;
}

void SceneObj::rotate(float angleX, float angleY, float angleZ){
	rotNode->amount3.x += angleX;
	rotNode->amount3.y += angleY;
	rotNode->amount3.z += angleZ;
}

void SceneObj::scale(float x, float y, float z){
	scaleNode->amount3.x += x;
	scaleNode->amount3.y += y;
	scaleNode->amount3.z += z;
	this->box->scaleBox(x, y, z);
}

void SceneObj::translate(float x, float y, float z){
	transNode->amount3.x += x;
	transNode->amount3.y += y;
	transNode->amount3.z += z;
	this->box->translateBox(x, y, z);
	if (modelNode->modelType==Lighting){
		lightNode->position[0]+=x;
		lightNode->position[1]+=y;
		lightNode->position[2]+=z;
	}
}

//print method
//makes use of Point print method as well
// void SceneObj::print(){
// 	printf("position: ");
// 	this->position.print();
// 	printf("scale: ");
// 	this->scaleFactor.print();
// 	printf("orientation: ");
// 	this->orientation.print();
// }

/*TESTING
int main(int argc, char** argv){
	float array[4] = {0.5,0.5,0.5,1};
	Material someMat = Material(array, array, array, array, 0.5);
	SceneObj* sphere1 = new SceneObj(SPHERE, someMat);
	sphere1->print();
	printf("\n");
	sphere1->scale(-2,4,6);
	sphere1->scale(0.5,0.5,0.5);
	sphere1->move(-1,-2,1);
	sphere1->move(1,2,0);
	sphere1->print();
	return 0;
}*/