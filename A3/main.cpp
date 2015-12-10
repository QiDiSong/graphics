/* CS 3GC3 - Texturing sample
 * by R. Teather
 */

 /*KEY-COMMANDS/*
 1 - insert cube at origin
 2 - insert sphere
 3 - insert teapot
 T - toggle transformation mode (mode is written at bottom left of screen)
 ASWD (and QE) - use transformations in +/- x, y, z directions
 tab - toggle between objects
 X - delete NOT PROPERLY IMPLEMENTED YET i don't think???
 arrow keys - lame camera control
 also if you try to use a transformation when nothing's there it'll crash

/*SCENE GRAPH:
implement next:
- deleting
- fix materials -> pick the 5 and make em changeable. also pick material for floor
- draw indication of selection
- dealing with ID's
- resetting scene
- scene rotation (copy from terrain)
- load/save
*/

#include <gl/glut.h>
#include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <vector>
#include <string>

#include "scene_graph/structs.h"
#include "scene_graph/sceneObj.cpp"

float pos[] = {0,1,0};
float camPos[] = {2.5, 2.5, 5};
float angle = 0.0f;

//lighting
float light_pos0[] = {10,10,10,1};
float amb0[4] = {0.5,0.5,0.5,1};
float diff0[4] = {0.5,0.5,0.5,1};
float em0[4] = {0.5,0.5,0.5,1};
float spec0[4] = {0.5,0.5,0.5,1};

//materials
float m_amb[] = {0.5,0.5,0.5, 1.0};
float m_dif[] = {0.5,0.5,0.5, 1.0};
float m_spec[] = {0.5,0.5,0.5, 1.0};
float shiny = 27.8;
Material m1 = Material(m_amb, m_dif, m_spec, shiny);

//emerald
float emAmb[] = {0.0215,	0.1745,	0.0215, 1.0};
float emDif[] = {0.07568,	0.61424,	0.07568,1};
float emSpec[] = {	0.633,	0.727811,	0.633,1};
float emShiny = 0.6*128;
Material m2 = Material (emAmb, emDif, emSpec, emShiny);

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

//sceneGraph
#include "scene_graph/sceneGraph.cpp"
#include "scene_graph/nodeGroup.cpp"

SceneGraph *SG;
int nextObjID = 0;
int currentObj = 0;
int numberOfObjs = 0;

string t = "translate";
string r = "rotate";
string s = "scale";
string transformMode = t;

int mode = 0;

vector<SceneObj*> *sceneObjs = new vector<SceneObj*>;

void insertObj(ModelType type){
	SG->goToRoot();

	//scale node
	Vector3D temp3;
	temp3.x = 1;
	temp3.y = 1;
	temp3.z = 1;

	//insert group node at root
	NodeGroup *objGroup = new NodeGroup();
	SG->insertChildNodeHere(objGroup);
	SG->goToChild(nextObjID);

	//insert remaining nodes, child after child
	//(rotate -> scale) -> translate -> (texture) -> model

	//scale
	NodeTransform *scNode = new NodeTransform(Scale, temp3);
	SG->insertChildNodeHere(scNode);
	SG->goToChild(0);

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

	//material
	NodeMaterial *matNode = new NodeMaterial(m1);
	//make material vector?
	SG->insertChildNodeHere(matNode);
	SG->goToChild(0);

	//model node
	NodeModel *modelNode = new NodeModel(type);
	SG->insertChildNodeHere(modelNode);

	//update globals
	SceneObj* newObj = new SceneObj(nextObjID++, trNode, scNode, rotNode, matNode, modelNode);
	sceneObjs->push_back(newObj);
	currentObj = newObj->ID;
	printf("%i \n",currentObj);
	numberOfObjs++;

}

//callbacks
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit (0);
			break;
		case '1': 
			insertObj(Cube);
			break;
		case '2':
			insertObj(Sphere);
			break;
		case '3':
			insertObj(Teapot);
			break;
		case 'a': //-x
			if (mode%3==0) sceneObjs->at(currentObj)->translate(-0.1, 0, 0);
			if (mode%3==1) sceneObjs->at(currentObj)->scale(-0.1, 0,0);
			if (mode%3==2) sceneObjs->at(currentObj)->rotate(-5,0,0);
			break;
		 case 'd': //+x
			if (mode%3==0) sceneObjs->at(currentObj)->translate(0.1, 0, 0);
			if (mode%3==1) sceneObjs->at(currentObj)->scale(0.1,0,0);
			if (mode%3==2) sceneObjs->at(currentObj)->rotate(5,0,0);
			break;
		case 'q': //-z
			if (mode%3==0) sceneObjs->at(currentObj)->translate(0, 0, -0.1);
			if (mode%3==1) sceneObjs->at(currentObj)->scale(0, 0,-0.1);
			if (mode%3==2) sceneObjs->at(currentObj)->rotate(0,0,-5);
			break;
		case 'e': //+z
			if (mode%3==0) sceneObjs->at(currentObj)->translate(0, 0, 0.1);
			if (mode%3==1) sceneObjs->at(currentObj)->scale(0, 0,0.1);
			if (mode%3==2) sceneObjs->at(currentObj)->rotate(0,0,5);
			break;
		case 's': //-y
			if (mode%3==0) sceneObjs->at(currentObj)->translate(0, -0.1, 0);
			if (mode%3==1) sceneObjs->at(currentObj)->scale(0, -0.1,0);
			if (mode%3==2) sceneObjs->at(currentObj)->rotate(0,-5,0);
			break;
		case 'w': //+y
			if (mode%3==0) sceneObjs->at(currentObj)->translate(0, 0.1, 0);
			if (mode%3==1) sceneObjs->at(currentObj)->scale(0, 0.1,0);
			if (mode%3==2) sceneObjs->at(currentObj)->rotate(0,5,0);
			break;
		case 't': //transform type toggle
			mode++;
			if (mode%3==0) transformMode = t;
			if (mode%3==1) transformMode = s;
			if (mode%3==2) transformMode = r;
			break;
		case 'x':
			sceneObjs->erase(sceneObjs->begin()+currentObj);
			// also remove from tree
			numberOfObjs--;
			currentObj -= 1;
		case 9: // toggle selected object (temporary fix before ray picking is implemented)
			currentObj = (currentObj+1)%numberOfObjs;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch(key)
	{

		case GLUT_KEY_LEFT:
			camPos[0]-=0.1;
			break;

		case GLUT_KEY_RIGHT:
			camPos[0]+=0.1;
			break;

		case GLUT_KEY_UP:
			camPos[2] -= 0.1;
			break;

		case GLUT_KEY_DOWN:
			camPos[2] += 0.1;
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


void init(void)
{	GLuint id = 1;

	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	//init our scenegraph
	SG = new SceneGraph();

}

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
	

}

void drawXZPlane(float y_intercept, float size){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
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


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	float origin[3] = {0,0,0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);

	glColor3f(1,1,1);

	
	glPushMatrix();
	glTranslatef(light_pos0[0],light_pos0[1],light_pos0[2]);
	glutSolidSphere(1,50,50);
	glPopMatrix();

	drawAxis(50);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0,GL_POSITION,light_pos0);
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb0);
	glLightfv(GL_LIGHT0,GL_EMISSION,em0);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diff0);
	glLightfv(GL_LIGHT0,GL_SPECULAR,spec0);

	//glutSolidSphere(1, 100, 100);
	//draw the sceneGraph
	drawXZPlane(0,50);
	
	SG->draw();
	drawText();

	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("SimpleSceneGraph");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}