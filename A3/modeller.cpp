/*SIMPLE 3D MODELLER
Assignment 3 for COMP SCI 3GC3
Vicky Bilbily bilbilv 1317465
Lucas Bongers bongerlj 1202472
*/

#include <gl/glut.h>
#include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "structs.h"
#include "sceneObj.cpp"

//camera
float pos[] = {0,1,0};
float camPos[] = {10, 5, 10};
float angleX = 0;
float angleY = 0;

//lighting
float light_pos0[] = {5,5,2,1.0};
float amb0[4] = {0.5,0.5,0.5,1};
float diff0[4] = {1,1,1, 1};
float spec0[4] = {1, 1, 1, 1};

float light_pos1[] = {2,5,5,1.0};
float amb1[4] = {0,0,0,1};
float diff1[4] = {0,1,1, 1};
float spec1[4] = {1, 1, 1, 1};

//materials
float m_amb[] = {0.5,0.5,0.5, 1.0};
float m_dif[] = {0.5,0.5,0.5, 1.0};
float m_spec[] = {0,0,0, 1.0};
float shiny = 27.8*128;
Material m1= Material (m_amb, m_dif, m_spec, shiny);

float emAmb[] = {0.0215,	0.1745,	0.0215, 1.0};
float emDif[] = {0.07568,	0.61424,	0.07568,1};
float emSpec[] = {	0.633,	0.727811,	0.633,1};
float emShiny = 0.6*128;
Material m2 = Material (emAmb, emDif, emSpec, emShiny);

float gAmb[] = {2150.24725, 	0.1995, 	0.0745, 1.0};
float gDif[] = {0.75164, 	0.60648, 	0.22648,1};
float gSpec[] = {0.628281, 	0.555802, 	0.366065,1};
float gShiny = 0.4*128;
Material m3 = Material(gAmb, gDif, gSpec, gShiny);

float pAmb[] =  {0.25, 	0.20725, 	0.20725, 1.0};
float pDif[] = {1, 	0.829, 	0.829,1};
float pSpec[] = {0.296648, 	0.296648, 	0.296648,1};
float pShiny =  0.088*128;
Material m4 = Material(pAmb, pDif, pSpec, pShiny);

float rAmb[] = {0.0, 	0.0, 	0.0, 1.0};
float rDif[] = {0.5, 	0.0, 	0.0,1};
float rSpec[] = { 0.7, 	0.6, 	0.6,1};
float rShiny = .25*128;
Material m5 = Material(rAmb, rDif, rSpec, rShiny);

Material curMat = m1;

//ray picking
double start[] ={0,0,0}, end[]={1,1,1};

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

//sceneGraph
#include "sceneGraph.cpp"
#include "nodeGroup.cpp"

SceneGraph *SG;
int nextChild = 0;
SceneObj * currentObj;
int currentObjIndex = 0;

//transform modes
string t = "translate";
string r = "rotate";
string s = "scale";
string transformMode = t;
int mode = 0;

//scene objects
vector<SceneObj*> *sceneObjs = new vector<SceneObj*>;


//print instructions to terminal
void instructions(){
	printf("\n\nHI NOEL OR THOMAS! Welcome to ~The Simple 3D Modeler~ \n"
		"(by Vicky Bilbily 1317465 and Lucas Bongers 1202472) \n\n"
		"How to use: \n"
		"The default scene starts with two lights represented by spheres \n"
		"Arrow keys - move camera location \n"
		"CTRL + arrow keys - rotate scene \n"
		"y - insert cube \n"
		"u - insert sphere \n"
		"i - insert cone \n"
		"o - insert torus \n"
		"p - insert teapot \n"
		"left-click - select object \n"
		"tab - toggle through objects \n"
		"right-click - delete object \n"
		"x - delete currently selected object \n"
		"r - clear all objects in scene \n"
		"1-5 - toggle current material \n"
		"m - set selected object to current material \n"
		"t - toggle transform mode (written in bottom-left corner of scene) \n"
		"aswd(qe) - transform selected object in all directions \n"
		"space - save scene to txt (give name in terminal) \n"
		"CTRL + space - load scene (give name in terminal) \n"
		"*WARNING* loading doesn't fully work yet, currently crashes the program... \n"
		"esc - exit \n"

		"\nExtra feature: you can ray-pick the lights \n"
		);
}

//insert an object into the scene
void insertObj(ModelType type){
	SG->goToRoot();

	//temp for passing default values to nodes
	Vector3D temp3;

	//insert group node at root
	NodeGroup *objGroup = new NodeGroup();
	SG->insertChildNodeHere(objGroup);
	SG->goToChild(nextChild++);

	int groupID = SG->getCurrentID(); //identify this object by it's group-node ID
	//insert remaining nodes, child after child

	//reset temp vals to 0 to begin obj at origin, and rotations to be 0
	temp3.x = 0;
	temp3.y = 0;
	temp3.z = 0;

	//translate
	NodeTransform *trNode = new NodeTransform(Translate, temp3);
	SG->insertChildNodeHere(trNode);
	SG->goToChild(0);

	//rotate
	NodeTransform *rotNode = new NodeTransform(Rotate, temp3);
	SG->insertChildNodeHere(rotNode);
	SG->goToChild(0);

	//should be 1 for scale
	temp3.x = 1;
	temp3.y = 1;
	temp3.z = 1;

	//scale
	NodeTransform *scNode = new NodeTransform(Scale, temp3);
	SG->insertChildNodeHere(scNode);
	SG->goToChild(0);

	//material
	NodeMaterial *matNode = new NodeMaterial(curMat);
	SG->insertChildNodeHere(matNode);
	SG->goToChild(0);

	//model node
	NodeModel *modelNode = new NodeModel(type);
	SG->insertChildNodeHere(modelNode);

	//update globals
	SceneObj* newObj = new SceneObj(groupID, trNode, scNode, rotNode, matNode, modelNode);
	sceneObjs->push_back(newObj);
	if (nextChild>1) currentObj->unselect();
	newObj->select();
	currentObj = newObj;
	currentObjIndex = sceneObjs->size()-1;
}

//insert light into the scene
void insertLight(float pos[4], float amb[4], float dif[4], float spec[4], int n){
	SG->goToRoot();

	//temp for passing values to nodes
	Vector3D temp3;
	temp3.x = pos[0];
	temp3.y = pos[1];
	temp3.z = pos[2];

	//insert group node at root
	NodeGroup *objGroup = new NodeGroup();
	SG->insertChildNodeHere(objGroup);
	SG->goToChild(nextChild++);

	int groupID = SG->getCurrentID();

	//lighting
	NodeLight *lightNode = new NodeLight(pos, amb, dif, spec, n);
	SG->insertChildNodeHere(lightNode);
	SG->goToChild(0);

	//translate
	NodeTransform *trNode = new NodeTransform(Translate, temp3);
	SG->insertChildNodeHere(trNode);
	SG->goToChild(0);

	//model node
	NodeModel *modelNode = new NodeModel(Lighting);
	SG->insertChildNodeHere(modelNode);

	//update globals
	SceneObj* newObj = new SceneObj(groupID, trNode, lightNode, modelNode);
	if (nextChild>1) currentObj->unselect();
	newObj->select();
	sceneObjs->push_back(newObj);
	currentObj = newObj;
}

//delete object of given ID
void deleteObj(int ID){
	SG->deleteChildByID(ID);
	int index = -1;
	for (int i=0; i<sceneObjs->size(); i++){
		if (sceneObjs->at(i)->ID==ID){
			index = i;
			break;
		}
	}
	sceneObjs->erase(sceneObjs->begin()+index);
	currentObj = sceneObjs->at(sceneObjs->size()-1);
	nextChild--;
}

//callbacks
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit (0);
			break;
		//draw objects
		case 'y': 
			insertObj(Cube);
			break;
		case 'u':
			insertObj(Sphere);
			break;
		case 'i':
			insertObj(Cone);
			break;
		case 'o':
			insertObj(Torus);
			break;
		case 'p':
			insertObj(Teapot);
			break;
		//transformations
		case 'a': //-x
			if (sceneObjs->size()!=0){
				if (mode%3==0) currentObj->translate(-0.1, 0, 0);
				if (mode%3==1&&!currentObj->isLight) currentObj->scale(-0.1, 0,0);
				if (mode%3==2&&!currentObj->isLight) currentObj->rotate(-5,0,0);
			}
			break;
		 case 'd': //+x
		 if (sceneObjs->size()!=0){
				if (mode%3==0) currentObj->translate(0.1, 0, 0);
				if (mode%3==1&&!currentObj->isLight) currentObj->scale(0.1,0,0);
				if (mode%3==2&&!currentObj->isLight) currentObj->rotate(5,0,0);
			}
			break;
		case 'q': //-z
		if (sceneObjs->size()!=0){
			if (mode%3==0) currentObj->translate(0, 0, -0.1);
			if (mode%3==1&&!currentObj->isLight) currentObj->scale(0, 0,-0.1);
			if (mode%3==2&&!currentObj->isLight) currentObj->rotate(0,0,-5);}
			break;
		case 'e': //+z
		if (sceneObjs->size()!=0){
			if (mode%3==0) currentObj->translate(0, 0, 0.1);
			if (mode%3==1&&!currentObj->isLight) currentObj->scale(0, 0,0.1);
			if (mode%3==2&&!currentObj->isLight) currentObj->rotate(0,0,5);}
			break;
		case 's': //-y
		if (sceneObjs->size()!=0){
			if (mode%3==0) currentObj->translate(0, -0.1, 0);
			if (mode%3==1&&!currentObj->isLight) currentObj->scale(0, -0.1,0);
			if (mode%3==2&&!currentObj->isLight) currentObj->rotate(0,-5,0);}
			break;
		case 'w': //+y
		if (sceneObjs->size()!=0){
			if (mode%3==0) currentObj->translate(0, 0.1, 0);
			if (mode%3==1&&!currentObj->isLight) currentObj->scale(0, 0.1,0);
			if (mode%3==2&&!currentObj->isLight) currentObj->rotate(0,5,0);}
			break;
		case 't': //transform type toggle
			mode++;
			if (mode%3==0) transformMode = t;
			if (mode%3==1) transformMode = s;
			if (mode%3==2) transformMode = r;
			break;
		case 32: //load/save
			if (glutGetModifiers()==GLUT_ACTIVE_CTRL){
				sceneObjs = SG->load();
				nextChild = sceneObjs->size();
				currentObj = sceneObjs->at(0);
				currentObj->select();
			}
			else SG->save();
			break;
		//toggle materials
		case '1':
			curMat = m1;
			break;
		case '2':
			curMat = m2;
			break;
		case '3':
			curMat = m3;
			break;
		case '4':
			curMat = m4;
			break;
		case '5':
			curMat = m5;
			break;
		//change selected object's material to current material
		case 'm':
			if (!currentObj->isLight) currentObj->changeMaterial(curMat);
			break;
		//delete selected object
		case 'x':
			if (sceneObjs->size()!=0){
				deleteObj(currentObj->ID);
			}
			break;
		//reset scene
		case 'r':
			SG = new SceneGraph();
			nextChild = 0;
			sceneObjs = new vector<SceneObj*>;
			insertLight(light_pos0, amb0, diff0, spec0, 0);
			insertLight(light_pos1, amb1, diff1, spec1, 1);
			break;
		case 9: // toggle selected object (was used before ray picking implemented, still useful anyway)
			currentObj->unselect();
			currentObj = sceneObjs->at(currentObjIndex++%sceneObjs->size());
			currentObj->select();
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	//use CTRL modifier to rotate scene
	switch(key)
	{

		case GLUT_KEY_LEFT:
			if (glutGetModifiers()==GLUT_ACTIVE_CTRL) angleX += 5;
			else camPos[0]-=0.1;
			
			break;

		case GLUT_KEY_RIGHT:
			if (glutGetModifiers()==GLUT_ACTIVE_CTRL) angleX += -5;
			else camPos[0]+=0.1;
			
			break;

		case GLUT_KEY_UP:
			if (glutGetModifiers()==GLUT_ACTIVE_CTRL) angleY += 5;
			else camPos[2] -= 0.1;
			
			break;

		case GLUT_KEY_DOWN:
			if (glutGetModifiers()==GLUT_ACTIVE_CTRL) angleY += -5;
			else camPos[2] += 0.1;
			break;
		
		case GLUT_KEY_HOME:
			camPos[1] += 0.1;
			break;

		case GLUT_KEY_END:
			camPos[1] -= 0.1;
			break;

	}
	glutPostRedisplay();
}

//ray picking via mouse function!
void mouse(int button, int state, int x, int y){
	
	//grab matrices
	double matModelView[16], matProjection[16]; 
	int viewport[4]; 

	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView); 
	glGetDoublev(GL_PROJECTION_MATRIX, matProjection); 
	glGetIntegerv(GL_VIEWPORT, viewport);

	//unproject values
	double winX = (double)x; 
	double winY = viewport[3] - (double)y; 

	// get point on the 'near' plane 
	gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
         viewport, &start[0], &start[1], &start[2]); 

	// get point on the 'far' plane
	gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
         viewport, &end[0], &end[1], &end[2]);

	//difference
	end[0] = end[0] - start[0];
	end[1] = end[1] - start[1];
	end[2] = end[2] - start[2];

	//magnitude
	double M = sqrt(end[0]*end[0] + end[1]*end[1] + end[2]*end[2]);

	//unit vector
	end[0] /= M;
	end[1] /= M;
	end[2] /= M;

	//list of intersection distances
	vector<double> *intersections = new vector<double>;
	//find the relative distance for each object in scene
	for (int i = 0; i < sceneObjs->size(); ++i)
	{	double intersection = sceneObjs->at(i)->box->slab(start,end);
		intersections->insert(intersections->begin()+i, intersection); 
	}

	//compare these distances
	double t;
	double closest = std::numeric_limits<double>::infinity();
	int closestIndex = -1;
	for (int i = 0; i < intersections->size(); ++i){
		t = intersections->at(i);
		if (t<closest && t>0){
			closest = t;
			closestIndex = i;
		}
	}
	//select closest intersected object, if any
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if (closestIndex > -1){
			currentObj->unselect();
			currentObj = sceneObjs->at(closestIndex);
			currentObj->select();
		}
	}
	//delete closest intersected object, if any
	if(button ==  GLUT_RIGHT_BUTTON && state == GLUT_DOWN && sceneObjs->size()!=0) deleteObj(currentObj->ID);
}


void init(void)
{	GLuint id = 1;

	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
	glEnable(GL_LIGHTING);
	//init our scenegraph
	SG = new SceneGraph();
	insertLight(light_pos1, amb1, diff1, spec1, 1);
	insertLight(light_pos0, amb0, diff0, spec0, 0);
	

}

//draw transformation mode in bottom left corner
void drawText(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);

	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2i(10, 10);
	for (int i = 0; i < transformMode.length(); i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,transformMode[i]);
	}
	glFlush();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
	
}

//draw base plane with normals
void drawXZPlane(float y_intercept, float size){
	glColor3f(0.2,0.2,0.2);
	glLineWidth(1);
	glBegin(GL_QUADS);
		for (int x = 0; x < size-1; x++) { 
      		for (int z = 0; z < size-1; z++) {
		    	//draw quad vertices CCW
		    	//assigning normals as well
		    	//it's a flat x-z plane so the normal is always 1 in the y direction
		       	glNormal3f(0,1,0);
		        glVertex3f(x, y_intercept, z);

		        glNormal3f(0,1,0);
		        glVertex3f(x+1, y_intercept, z);

		        glNormal3f(0,1,0);
		        glVertex3f(x+1, y_intercept, z+1);

		        glNormal3f(0,1,0);
		        glVertex3f(x, y_intercept, z+1);
      }
    }
    glEnd();

}

//draw x-y-z axis
void drawAxis(float size)
{	glLineWidth(10);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0,0,0);
		glVertex3f(size,0,0);

		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,size,0);
		
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,size);
	glEnd();
}


//display function
void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	glRotatef(angleY,1,0,0);
	glRotatef(angleX,0,1,0);

	drawAxis(50);
	//draw the sceneGraph
	glEnable(GL_LIGHTING);
	setMaterial(m1);
	drawXZPlane(0,50);

	glColor3f(0.5,0.5,0.5);
	SG->draw();
	drawText();

	glutSwapBuffers();
}

//main function
int main(int argc, char** argv)
{	instructions();
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("~Simple 3D Modeler~");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}