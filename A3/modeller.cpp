
// basic 3D modeller
#include <windows.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "scene_graph/sceneObj.cpp"

float eye[3] = {5.0,5.0,5.0};
int shapeDrawn;
double start[] ={0,0,0}, end[]={1,1,1};

void drawAxis()
{
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0,0,0);
		glVertex3f(50,0,0);

		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,50,0);
		
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,50);
	glEnd();
}

//function which preforms intersection test
bool Intersect(int x, int y){
	printf("%i, %i\n", x, y);

	//allocate matricies memory
	double matModelView[16], matProjection[16]; 
	int viewport[4]; 

	//vectors


	//grab the matricies
	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView); 
	glGetDoublev(GL_PROJECTION_MATRIX, matProjection); 
	glGetIntegerv(GL_VIEWPORT, viewport); 

	//unproject the values
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

	//check for intersection against sphere!
	//hurray!

	double A, B, C;

	double R0x, R0y, R0z;
	double Rdx, Rdy, Rdz;

	R0x = start[0];
	R0y = start[1];
	R0z = start[2];

	Rdx = end[0] - start[0];
	Rdy = end[1] - start[1];
	Rdz = end[2] - start[2];

	//magnitude!
	double M = sqrt(Rdx*Rdx + Rdy*Rdy + Rdz* Rdz);

	//unit vector!
	Rdx /= M;
	Rdy /= M;
	Rdz /= M;

	//A = Rd dot Rd
	A = Rdx*Rdx + Rdy*Rdy + Rdz*Rdz;

	double Btempx, Btempy, Btempz;
	Btempx = R0x;
	Btempy =  R0y;
	Btempz =  R0z;

	B = Btempx * Rdx + Btempy * Rdy + Btempz *Rdz;
	B *= 2.0;

	C = R0x*R0x + R0y*R0y + R0z* R0z - 1;


	double sq = B*B  - 4*A*C;

	double t0 = 0, t1 = 0;

	if(sq < 0)
		printf("no Intersection!!!\n");
	else{
		t0 = ((-1) * B + sqrt(sq))/(2*A);
		t1 = ((-1) * B - sqrt(sq))/(2*A);

		printf("Intersection at: t = %f, and t = %f\n", t0, t1);
	}


	return false; //else returns false
}

void mouse(int button, int state, int x, int y){
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		Intersect(x,y);
	}

}

void display()
{
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0],eye[1],eye[2],0,0,0,0,1,0);

	drawAxis();

	//testing object drawing
	//glutSolidCube(1);

	//draw cube
	if(shapeDrawn == 1) {
		glColor3f(0,0.3,1);
    	glutSolidCube(1);
	}

	//draw sphere
	if(shapeDrawn == 2) {
		glColor3f(0,0.3,1);
    	glutSolidSphere(1, 50, 50);
	}

	//draw teapot
	if(shapeDrawn == 3) {
		glColor3f(0,0.3,1);
    	glutSolidTeapot(1);
	}

	//draw cone
	if(shapeDrawn == 4) {
		glColor3f(0,0.3,1);
    	glutSolidCone(1, 1, 50, 50);
	}

	//draw icosahedron
	if(shapeDrawn == 5) {
		glColor3f(0,0.3,1);
    	glutSolidIcosahedron();
	}

	if(shapeDrawn == 6) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eye[0],eye[1],eye[2],0,0,0,0,1,0);

		drawAxis();
	}

	//swap buffers - rendering is done to the back buffer, bring it forward to display
	glutSwapBuffers();

	//force a redisplay, to keep the animation running
	glutPostRedisplay();
}

void kbd(unsigned char key, int x, int y)
{
	//if the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q')
	{
		exit(0);
	}

	//draw cube
	if(key == 'c' || key == 'C') {
		shapeDrawn = 1;
	}

	//draw sphere
	if(key == 's' || key == 'S') {
		shapeDrawn = 2;
	}

	//draw teapot
	if(key == 't' || key == 'T') {
		shapeDrawn = 3;
	}

	//draw cone
	if(key == 'o' || key == 'O') {
		shapeDrawn = 4;
	}

	//draw icosahedron
	if(key == 'i' || key == 'I') {
		shapeDrawn = 5;
	}

	if(key == 'd' || key == 'D') {
		shapeDrawn = 6;
	}
}

void special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
		eye[0]-=0.2;
		break;

		case GLUT_KEY_RIGHT:
		eye[0]+=0.2;
		break;

		case GLUT_KEY_UP:
		eye[2]+=0.2;
		break;

		case GLUT_KEY_DOWN:
		eye[2]-=0.2;
		break;

		default:
		break;
	}
}

int main(int argc, char** argv)
{
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("basic 3D modeller");

	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);

	//setup the initial view
	// change to projection matrix mode, set the extents of our viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,1,100);

	//set clear colour to white
	glClearColor(1, 1, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	//look down from a 45 deg. angle
	glRotatef(45, 1, 0, 0);

	//register glut callbacks for keyboard and display function
	glutKeyboardFunc(kbd);
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	printf("C: Draw Cube");
	printf("\n");
	printf("S: Draw Sphere");
	printf("\n");
	printf("T: Draw Teapot");
	printf("\n");
	printf("O: Draw Cone");
	printf("\n");
	printf("I: Draw Icosahedron");
	printf("\n");
	printf("D: Delete");
	printf("\n");

	//start the program!
	glutMainLoop();

	return 0;
}