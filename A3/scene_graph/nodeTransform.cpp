#include "nodeTransform.h"
#include <stdio.h> //needed for printf command
#include <gl/glut.h>

//for gltranslate and gl scale
NodeTransform::NodeTransform(transformType whatType, Vector3D vec3){
	nodeType = transformation;
	transformationType = whatType;
	amount3 = vec3;
}

void NodeTransform::nodeSpecificCodeDown(){
	switch (transformationType){
	case Translate:
		glTranslatef(amount3.x, amount3.y, amount3.z);
		break;
	case Rotate:
		glRotatef(amount3.x,1, 0, 0);
		glRotatef(amount3.y,0,1,0);
		glRotatef(amount3.z,0,0,1);
		
		break;
	case Scale:
		glScalef(amount3.x, amount3.y, amount3.z);
		break;
	}
}
