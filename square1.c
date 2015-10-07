//opengl cross platform includes
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


void axis(int size){

	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex2f(-size,0);
		glVertex2f(size,0);

		for (int i=-size; i<=size; i++){
			glVertex2f(i, -0.5);
			glVertex2f(i, 0.5);
		}

		glColor3f(0,1,0);
		glVertex2f(0, -size);
		glVertex2f(0, size);

		for (int i=-size; i<=size; i++){
			glVertex2f(-0.5, i);
			glVertex2f(0.5, i);
		}

	glEnd();
}

/* display function - GLUT display callback function
 *		clears the screen, draws a square, and displays it
 */
void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT);
	axis(10);

	glPushMatrix();
	glTranslatef(2,3,0);
	glRotatef(30, 0, 0, 1);
	glScalef(2,2,1);
	glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);	
	glEnd();
	glPopMatrix();


	glFlush();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutCreateWindow("square");	//creates the window
	glutDisplayFunc(display);	//registers "display" as the display callback function
	
	gluOrtho2D(-10, 10, -10, 10);
	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}