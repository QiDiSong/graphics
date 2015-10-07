#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

//TO-DO:
//- fix life function lols
//- step
//- play/pause
//- **insert certain "creatures"??

// grid is a 2d array, 102x102, of ints
//(only 100x100 will be displayed, the extra 2 is so that we don't
//have to worry about ArrayIndexOutOfBounds errors)
// 0 = dead, 1 = alive

int T = 1000;
bool play = true;

//randomizes grid
int world[52][52];

void randomWorld(){
	for (int i = 0; i < 52; i++){
		for (int j = 0; j < 52; j++){
			world[i][j]= rand()%2;
		}
	}
}
//empties grid
void emptyWorld(){
	for (int i = 0; i < 52; i++){
		for (int j = 0; j < 52; j++){
			world[i][j]=0;
		}
	}
}

//grid copier so that we can put results into the copied grid without affecting
//the calculations based off of the original grid
void copyWorld(int original[][52], int copy[][52]){
	for (int i = 0; i < 52; i++){
		for (int j = 0; j < 52; j++){
			copy[i][j] = original[i][j];
		}
	}
}

//checks whether a cell should live or die
void life(){
	int temp[52][52];
	copyWorld(world, temp);
	for (int i = 1; i < 52; i++){
		for (int j = 1; j < 52; j++){
			int n = 0; //neighbour counter
			n = world[i-1][j] + world[i+1][j] + world[i][j+1] + world[i][j-1] + world[i-1][j+1] + world[i+1][j+1] + world[i-1][j+1] + world[i+1][j-1];
			if (n==3 || (world[i][j]==1 && n==2)){
				temp[i][j]==1;
			}
			else{
				temp[i][j]==0;
			}
		}
	}
	copyWorld(temp, world);
}

void grid(){
	if (play){
	glColor3f(0,0.3,0);
	}
	else{
		glColor3f(0.3,0,0);
	}
	glPointSize(1);
	glBegin(GL_LINES);

	for (int i=0; i<=50; i++){
		glVertex2f(i, 0);
		glVertex2f(i, 50);
		glVertex2f(0, i);
		glVertex2f(50, i);
	}


	glEnd();
}

void populate(){
	glColor3f(1,1,1);
	glPointSize(8);
	glBegin(GL_POINTS);
		for (int i = 0; i < 52; i++){
			for (int j = 0; j < 52; j++){
				if (world[i][j]==1){
					glVertex2f(i-0.5,j-0.5);
				}
			}
		}
	glEnd();
}

void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT);
	grid();
	populate();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27: //esc
		case 'q':
			exit(0);
			break;
		case 32: //spacebar
			play = play==true ? false : true;
			break;
		case 'c':
			emptyWorld();
			break;
		case 'r':
			randomWorld();
			break;
		default:
			break;
	}
}

void special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			T -= T >=100 ? 100 : 0;
			printf("speed is now %i", T);
			break;

		case GLUT_KEY_DOWN:
			T += T <=2000 ? 100 : 0;
			printf("speed is now %i", T);
			break;

		case GLUT_KEY_RIGHT:	
			//step forward
			break;

		default:
			break;
	}
}

void mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN){
		printf("click at %i, %i",x,y);
		int clicked = world[(int)ceil(x/10)+1][(int)ceil(y/10)+1];
		world[(int)ceil(x/10)+1][(int)ceil(y/10)+1] = clicked ? 0 : 1;
	}
}

void timer(int n)
{
	world[25][25]= world[25][25]==1 ? 0 : 1;
    glutPostRedisplay();
    glutTimerFunc(T, timer, T);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("conway's game of life");
	//glutCallbacks();
	//initMenu();
	glClearColor(0,0,0,1);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutSpecialFunc(special);
	gluOrtho2D(0, 50, 50, 0);
	glutDisplayFunc(display);
	timer(T);
	emptyWorld();
	glutMainLoop();

	return 0;
}