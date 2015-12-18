
#include <windows.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include "mazeGenerator.cpp"

#define SIZE 21

Cell maze[SIZE][SIZE];
float eye[3] = {SIZE,10,SIZE};

//lighting
float light_pos0[] = {SIZE/2,10,SIZE/2,1.0};
float amb0[4] = {0.5,0.5,0.5,1};
float diff0[4] = {1,1,1, 1};
float spec0[4] = {1, 1, 1, 1};

//animation
float pos[] = {5,1,5};
float rot[] = {0, 0, 0};
float headRot[] = {0, 0, 0};
int frame = 0;
int holdKey = 0;
bool animate = false;

//maze stuff
int mazeScale = 2;

void drawXZPlane(float y_intercept, float size){
	glColor3f(0.1,0.1,0.1);
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

void drawWalls(Cell path[][SIZE]){
	for (int x = 0; x < SIZE; x++){
		for (int z= 0; z < SIZE; z++){
			if (!path[x][z].vacant){
				glColor3f(1,0,0);
				glPushMatrix();
				glTranslatef(x, 0, z);
				glScalef(1,0.25,1);
				glutSolidCube(1);
				glPopMatrix();
			}
		}
	}
}

void kbd(unsigned char key, int x, int y)
{
	if (holdKey>1) animate = true;

	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;

		case 'a':
		case 'A':
			//if(pos[0] > -4.4)
				pos[0] -= 0.1;
			rot[1] = -90;
			holdKey++;
			if (animate) frame++;
			break;

		case 'w':
		case 'W':
			//if(pos[2] > -4.4)
				pos[2] -= 0.1;
			rot[1] = 180;
			holdKey++;
			if (animate) frame++;
			break;

		case 'd':
		case 'D':
			//if(pos[0] < 4.4)
				pos[0]+=0.1;
			rot[1] = 90;
			holdKey++;
			if (animate) frame++;
			break;

		case 's':
		case 'S':
			//if(pos[2] < 4.4)
				pos[2] += 0.1;
			rot[1] = 0;
			holdKey++;
			if (animate) frame++;
			break;

		case 'y':
		case 'Y':
			if(headRot[1] < 85)
				headRot[1] += 1;
			break;

		case 'u':
		case 'U':
			if(headRot[1] > -85)
				headRot[1] -= 1;
			break;
			
	}
	glutPostRedisplay();
}

//resets the vars used to check if a key is being held down (for walk-animation)
void keyUp(unsigned char key,int x, int y){
	switch(key)
	{
		case 'a':
		case 's':
		case 'd':
		case 'w':
			holdKey = 0;
			animate = false;
			break;
		default:
			break;

	}
	glutPostRedisplay();
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

void drawSnowman(float* pos, float* rot, int frame)
{
	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot[1], 0, 1, 0);

	//bouncing animation while the character is moving (movement key held down)
	if (animate)
	{	if ((frame)%8==7||(frame)%8==5){
			glTranslatef(0,0.025,0);
			glScalef(1,1.025,1);
		}
		if ((frame)%8==6){
			glTranslatef(0,0.025,0);
			glScalef(1,1.025,1);
		}
		if ((frame)%8==3||(frame)%8==1){
			glTranslatef(0,-0.025,0);
			glScalef(1,0.925,1);
		}
		if ((frame)%8==2){
			glTranslatef(0,-0.025,0);
			glScalef(1,0.925,1);
		}
	}

	//draw body
	glColor3f(1,1,1);
	glutSolidSphere(1, 16, 16);

	//draw buttons
	glPushMatrix();
	glTranslatef(0, 0.35, 0.9);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.15, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.05, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();


	glPushMatrix();
	//translate relative to body, and draw head
	glTranslatef(0, 1.25, 0);
	glRotatef(headRot[1], 0, 1, 0); //turn the head relative to the body
	glColor3f(1,1,1);
	glutSolidSphere(0.5, 16, 16);
	
	//translate and draw right eye
	glPushMatrix();
	glTranslatef(0.2, 0.15, 0.45);
	glColor3f(0,0,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw left eye
	glPushMatrix();
	glTranslatef(-0.2, 0.15, 0.45);
	glColor3f(0,0,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw nose
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1,0.4,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPopMatrix();//body
	glPopMatrix();//snowman
}

void display()
{
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0],eye[1],eye[2],SIZE/2,0,SIZE/2,0,1,0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0,GL_POSITION,light_pos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

	glPushMatrix();
	glScalef(mazeScale, 1, mazeScale);
	drawXZPlane(0, SIZE);
	drawWalls(maze);
	glPopMatrix();

	drawSnowman(pos, rot, frame);
	
	//swap buffers - rendering is done to the back buffer, bring it forward to display
	glutSwapBuffers();

	//force a redisplay, to keep the animation running
	glutPostRedisplay();
}

void init(){

}

int main(int argc, char** argv)
{
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Spinning Cube");

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

	Initialize(maze);
	DrawMaze(maze);
	int* startEnd = getStartAndGoalCoords(maze);
	pos[0] = startEnd[0]*mazeScale;
	pos[2] = startEnd[1]*mazeScale;
	drawSnowman(pos, rot, frame);


	//start the program!
	glutMainLoop();

	

	return 0;
}
