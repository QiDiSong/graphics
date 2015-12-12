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
- disable transforms on lights...
- add 3 more materials!
- add textures
- draw indication of selection
- load/save
*/

#include <gl/glut.h>
#include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <vector>
#include <string>
#include <limits>

#include "scene_graph/structs.h"
#include "scene_graph/sceneObj.cpp"

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

// float pAmb[] = {2150.24725, 	0.1995, 	0.0745, 1.0};
// float pDif[] = {0.75164, 	0.60648, 	0.22648,1};
// float pSpec[] = {0.628281, 	0.555802, 	0.366065,1};
// float pShiny = 0.4*128;
// Material m4 = Material(pAmb, pDif, pSpec, pShiny);

// float gAmb[] = {2150.24725, 	0.1995, 	0.0745, 1.0};
// float gDif[] = {0.75164, 	0.60648, 	0.22648,1};
// float gSpec[] = {0.628281, 	0.555802, 	0.366065,1};
// float gShiny = 0.4*128;
// Material m5 = Material(gAmb, gDif, gSpec, gShiny);

Material curMat = m1;

//ray picking?
float nearPoint[] = {0,0,0};
float farPoint[] = {1,1,1};

double start[] ={0,0,0}, end[]={1,1,1};

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

//sceneGraph
#include "scene_graph/sceneGraph.cpp"
#include "scene_graph/nodeGroup.cpp"

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

void insertObj(ModelType type){
	SG->goToRoot();

	//scale node
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
	currentObj = newObj;
	currentObjIndex = sceneObjs->size()-1;
}

void insertLight(float pos[4], float amb[4], float dif[4], float spec[4], int n){
	SG->goToRoot();

	//scale node
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
	sceneObjs->push_back(newObj);
	currentObj = newObj;
}

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
			insertObj(Dodecahedron);
			break;
		case 'a': //-x
			if (sceneObjs->size()!=0){
				if (mode%3==0) currentObj->translate(-0.1, 0, 0);
				if (mode%3==1) currentObj->scale(-0.1, 0,0);
				if (mode%3==2) currentObj->rotate(-5,0,0);
			}
			break;
		 case 'd': //+x
		 if (sceneObjs->size()!=0){
				if (mode%3==0) currentObj->translate(0.1, 0, 0);
				if (mode%3==1) currentObj->scale(0.1,0,0);
				if (mode%3==2) currentObj->rotate(5,0,0);
			}
			break;
		case 'q': //-z
		if (sceneObjs->size()!=0){
			if (mode%3==0) currentObj->translate(0, 0, -0.1);
			if (mode%3==1) currentObj->scale(0, 0,-0.1);
			if (mode%3==2) currentObj->rotate(0,0,-5);}
			break;
		case 'e': //+z
		if (sceneObjs->size()!=0){
			if (mode%3==0) currentObj->translate(0, 0, 0.1);
			if (mode%3==1) currentObj->scale(0, 0,0.1);
			if (mode%3==2) currentObj->rotate(0,0,5);}
			break;
		case 's': //-y
		if (sceneObjs->size()!=0){
			if (mode%3==0) currentObj->translate(0, -0.1, 0);
			if (mode%3==1) currentObj->scale(0, -0.1,0);
			if (mode%3==2) currentObj->rotate(0,-5,0);}
			break;
		case 'w': //+y
		if (sceneObjs->size()!=0){
			if (mode%3==0) currentObj->translate(0, 0.1, 0);
			if (mode%3==1) currentObj->scale(0, 0.1,0);
			if (mode%3==2) currentObj->rotate(0,5,0);}
			break;
		case 't': //transform type toggle
			mode++;
			if (mode%3==0) transformMode = t;
			if (mode%3==1) transformMode = s;
			if (mode%3==2) transformMode = r;
			break;
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
			//curMat = m4;
			break;
		case '5':
			//curMat = m5;
			break;
		case 'm':
			currentObj->changeMaterial(curMat);
			break;
		case 'x':
			if (sceneObjs->size()!=0){
				deleteObj(currentObj->ID);
			}
			break;
		case 'r':
			SG = new SceneGraph();
			nextChild = 0;
			sceneObjs = new vector<SceneObj*>;
			insertLight(light_pos0, amb0, diff0, spec0, 0);
			insertLight(light_pos1, amb1, diff1, spec1, 1);
			break;
		case 9: // toggle selected object (temporary fix before ray picking is implemented)
			currentObj = sceneObjs->at(currentObjIndex++%sceneObjs->size());
			printf("ID= %i",currentObj->ID);
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

void mouse(int button, int state, int x, int y){
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){

	double matModelView[16], matProjection[16]; 
	int viewport[4]; 

	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView); 
	glGetDoublev(GL_PROJECTION_MATRIX, matProjection); 
	glGetIntegerv(GL_VIEWPORT, viewport);

	//unproject values
	double winX = (double)x; 
	double winY = viewport[3] - (double)y; 

	// get point on the 'near' plane (third param is set to 0.0)
	gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
         viewport, &start[0], &start[1], &start[2]); 

	// get point on the 'far' plane (third param is set to 1.0)
	gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
         viewport, &end[0], &end[1], &end[2]);

	printf("near point: %f,%f,%f\n", start[0], start[1], start[2]);
	printf("far point: %f,%f,%f\n", end[0], end[1], end[2]);

	//difference
	end[0] = end[0] - start[0];
	end[1] = end[1] - start[1];
	end[2] = end[2] - start[2];

	//magnitude!
	double M = sqrt(end[0]*end[0] + end[1]*end[1] + end[2]*end[2]);

	//unit vector!
	end[0] /= M;
	end[1] /= M;
	end[2] /= M;

	//vicky trying the slab method
		// for (int i = 0; i < sceneObjs->size(); ++i)
		// {	bool intersection = sceneObjs->at(i)->box->slab(start,end);
		// 	if(intersection) printf("object %i intersected! \n",i);
		// 	else printf("no intersection :( \n");
		// }

	//vicky trying stuff
		vector<float> *intersections = new vector<float>; //vector of intersection(distances)
		for (int i = 0; i < sceneObjs->size(); ++i)
		{	double intersection = sceneObjs->at(i)->box->intersects(start,end);
			intersections->push_back(intersection); 
		}

		// double closest = std::numeric_limits<double>::infinity();
		// int closestIndex = intersections->size();
		// for (int i = 0; i < intersections->size(); ++i){
		// 	if (intersections->at(i)<closest){
		// 		closest = intersections->at(i);
		// 		closestIndex = i;
		// 	}
		// }
		// if (closestIndex != intersections->size()){
		// 	currentObj = sceneObjs->at(closestIndex);
		// }
		//if closest != infinity set current obj to the closest intersect
		//else do nothing
		//endstuff

	// double R0x, R0y, R0z;
	// double end[0], end[1], end[2];

	// R0x = start[0];
	// R0y = start[1];
	// R0z = start[2];

	// end[0] = end[0] - start[0];
	// end[1] = end[1] - start[1];
	// end[2] = end[2] - start[2];

	// //magnitude
	// double M = sqrt(end[0]*end[0] + end[1]*end[1] + end[2]* end[2]);

	// //unit vector
	// end[0] /= M;
	// end[1] /= M;
	// end[2] /= M;
	// nearPoint[0] = camPos[0];
	// nearPoint[1] = camPos[1];
	// nearPoint[2] = camPos[2];

	// farPoint[0] = end[0];
	// farPoint[1] = end[1];
	// farPoint[2] = end[2];
	}

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

	glPushMatrix();
	glTranslatef(nearPoint[0], nearPoint[1], nearPoint[2]);
	//printf("%f, %f, %f\n", nearPoint[0], nearPoint[1], nearPoint[2]);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(farPoint[0], farPoint[1], farPoint[2]);
	printf("%f, %f, %f\n", farPoint[0], farPoint[1], farPoint[2]);
	glutSolidCube(1);
	glPopMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	glRotatef(angleY,1,0,0);
	glRotatef(angleX,0,1,0);
	//glTranslatef(50, 0, 50);

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
	glutMouseFunc(mouse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}