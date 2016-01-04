#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>
#include <time.h>

//VICKY BILBILY
//1317465

int T = 1200; //speed variable (milliseconds)
bool play = true; //player clicked play (spacebar)
bool timerCalled = false; //the timer was called to loop the animation
enum Pattern { CELL, BLOCK, BLINKER, GLIDER };
Pattern currentPat = CELL;

// The world is a 2d array, 52x52, of ints
//(only 50x50 will be displayed, the extra 2 is so that we don't
//have to worry about ArrayIndexOutOfBounds errors)
// 0 = dead, 1 = alive
int world[52][52]; 

//Sets all values in world[][] to 0.
void emptyWorld(){
	for (int i = 0; i < 52; i++){
		for (int j = 0; j < 52; j++){
			world[i][j]=0;
		}
	}
}

//Randomly selects 0 or 1 for every index in world[][] (except the edges).
void randomWorld(){
	for (int i = 1; i < 51; i++){
		for (int j = 1; j < 51; j++){
			world[i][j]= rand()%2;
		}
	}
}

//World copier so that we can store results without affecting the original array,
//while still using the original array for calculations.
void copyWorld(int original[][52], int copy[][52]){
	for (int i = 0; i < 52; i++){
		for (int j = 0; j < 52; j++){
			copy[i][j] = original[i][j];
		}
	}
}

//Checks whether a cell should live or die based on the rules of Conway's Game of Life.
void life(){
	int temp[52][52];
	copyWorld(world, temp);
	for (int i = 1; i < 51; i++){
		for (int j = 1; j < 51; j++){
			int n = 0; //neighbouring cell counter
			n = world[i+1][j] + world[i-1][j] + world[i][j+1] + world[i][j-1] + world[i+1][j+1] + world[i+1][j-1] + world[i-1][j-1] + world[i-1][j+1];
			if (n < 2 || n > 3){
				temp[i][j]=0; //cell dies due to under- or over-population
			}
			if(n == 2){ //with a balanced population, cell stays the same
				temp[i][j]=world[i][j];
			}
			if(n == 3){ //with enough live neighbours, new cells may be "born"
				temp[i][j]=1;
			}
		}
	}
	copyWorld(temp, world);
}

//Draws 50x50 grid.
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

//Draws living cells into their respective grid/world positions.
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

//Main display function to be passed into glutDisplayFunc.
//Clears buffers->draws the grid->draws the cells->swaps buffers.
void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT);
	grid();
	populate();
	glutSwapBuffers();
}

//Keyboard handler to be passed into glutKeyboardFunc
void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27: //esc key = exit window
		case 'q': //(or 'q')
			exit(0);
			break;
		case 32: //spacebar = pause/play toggle
			play = play==true ? false : true;
			timerCalled = false;
			break;
		case 'c': //clear world
			emptyWorld();
			break;
		case 'r': //randomize world
			randomWorld();
			break;
		default:
			break;
	}
}

//Special key handler, to be passed into glutSpecialFunc.
void special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP: //increase speed by a factor of 2 (max speed is 1 redisplay per 25ms)
			T = T > 25 ? T/2 : T;
			break;

		case GLUT_KEY_DOWN: //decrease speed speed by a factor of 2 (min speed is 1 redisplay per 2400ms)
			T = T < 2400 ? T*2 : T;
			break;

		default:
			break;
	}
}

void menu(int val){
	switch(val){
		case 0:
			currentPat = CELL;
			break;
		case 1:
			currentPat = BLOCK;
			break;
		case 2: 
			currentPat = BLINKER;
			break;
		case 3:
			currentPat = GLIDER;
			break;
		default:
			break;
	}
}

void initMenu(){
	int id = glutCreateMenu(menu);
	glutSetMenu(id);
		glutAddMenuEntry("Toggle Cell", 0);
		glutAddMenuEntry("Block", 1);
		glutAddMenuEntry("Blinker", 2);
		glutAddMenuEntry("Glider", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//The weird math in the following function (world[(int)ceil(x/10)+1][(int)ceil(y/10)+1])) 
//converts inputs to their integers that correspond to the correct array indices.


//Mouse handler, to be passed into glutMousefunc.
void mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){ //toggle cells in grid to be alive or dead
		switch(currentPat){
			case CELL:
				world[(int)ceil(x/10)+1][(int)ceil(y/10)+1] = world[(int)ceil(x/10)+1][(int)ceil(y/10)+1] ? 0 : 1;
				break;
			case BLOCK:
				world[(int)ceil(x/10)+1][(int)ceil(y/10)+1] = 1;
				world[(int)ceil(x/10)+1][(int)ceil(y/10)+2] = 1;
				world[(int)ceil(x/10)+2][(int)ceil(y/10)+1] = 1;
				world[(int)ceil(x/10)+2][(int)ceil(y/10)+2] = 1;
				break;
			case BLINKER:
				world[(int)ceil(x/10)+1][(int)ceil(y/10)+1] = 1;
				world[(int)ceil(x/10)+2][(int)ceil(y/10)+1] = 1;
				world[(int)ceil(x/10)+3][(int)ceil(y/10)+1] = 1;
				break;
			case GLIDER:
				world[(int)ceil(x/10)+1][(int)ceil(y/10)+1] = 1;
				world[(int)ceil(x/10)+2][(int)ceil(y/10)+1] = 1;
				world[(int)ceil(x/10)+3][(int)ceil(y/10)+1] = 1;
				world[(int)ceil(x/10)+3][(int)ceil(y/10)+2] = 1;
				world[(int)ceil(x/10)+2][(int)ceil(y/10)+3] = 1;
				break;

			default:
				break;
		}
		
	}
}

//Timer to be passed into glutTimerfunc.
//Calls the world to update and then redisplays it.
void timer(int n)
{	if (play){
		life();
	    glutPostRedisplay();
	    glutTimerFunc(T, timer, T);
	}
}

//Idle function to be passed into glutIdleFunc.
//Idle determines whether to use the timer for 
//redisplay (when game is playing) or to idly redisplay (when game is paused)
void idle(){
	if (play && !timerCalled){
		timer(T);
		timerCalled=true;
	}
	else if (!play) glutPostRedisplay();
}

void instructions(){
	printf("\n\n Welcome to Conway\'s Game of Life!");
	printf("\n by Vicky Bilbily :)");
	printf("\n\n INSTRUCTIONS:");
	printf("\n Spacebar: toggles play/pause.");
	printf("\n Up key: increases speed by a factor of 2.");
	printf("\n Down key: decreases speed by a factor of 2.");
	printf("\n 'c' key: clears all cells from the grid.");
	printf("\n 'r' key: randomizes grid.");
	printf("\n Left click: edit the grid according to the current mode.");
	printf("\n Right click: display the menu to change the current mode.");
	printf("\n * MODES:");
	printf("\n -> Toggle cell: toggles clicked cell to be dead or alive.");
	printf("\n -> Block: draws block pattern-- click location determines the top-left cell of the pattern.");
	printf("\n -> Blinker: draws blinker pattern-- click location determines the top-left cell of the pattern.");
	printf("\n -> Glider: draws glider pattern-- click location determines the top-left cell of the pattern.");
	printf("\n -> (see http://www.conwaylife.com/wiki/Conway's_Game_of_Life for more info on patterns)");
	printf("\n Escape key (or 'q'): exit the window.");
	printf("\n\n That's all! Enjoy.");
}

//Main function.
int main(int argc, char **argv) {
	instructions();
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("conway's game of life");
	initMenu();
	glClearColor(0,0,0,1);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutSpecialFunc(special);
	gluOrtho2D(0, 50, 50, 0);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	emptyWorld();
	randomWorld();
	glutMainLoop();

	return 0;
}