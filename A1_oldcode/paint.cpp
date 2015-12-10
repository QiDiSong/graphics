#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <time.h>
#include "mathLib.cpp"

//VICKY BILBILY
//1317465

//Initalizing global variables

//Global accessible Point2d objects for mouse clicks.
Point2d *click1 = new Point2d(0, 0);
Point2d *click2= new Point2d(0, 0);

//Is it the first or second click? Relevant to different shape modes.
int whichClick = 1;

//Stored colours.
Colour *red = new Colour(1.0f, 0.0f, 0.0f);
Colour *green = new Colour(0.0f, 1.0f, 0.0f);
Colour *blue = new Colour(0.0f, 0.0f, 1.0f);
Colour *purple = new Colour(1.0f, 0.0f, 1.0f);
Colour *yellow = new Colour(1.0f, 1.0f, 0.0f);
Colour *drawColour = new Colour(1.0f, 1.0f, 1.0f); //default colour

//Point size (defaults to 2).
float pointSize = 2.0f;

//Shape modes, assigned values for menu callback.
int point = 0;
int line = 1;
int rectangle = 2;
int circle = 3;
int clear = 4;
int drawShape = point; //default shape is "point"

//Line drawing algorithm
void bresenham(Point2d *p1, Point2d *p2){
	bool steep=false;

	//Assigning pointers so that swapping does not mess up other calculations that require the 
	//given points (namely in drawRect)
	int* p1y = &(p1->y);
	int* p1x = &(p1->x);
	int* p2y = &(p2->y);
	int* p2x = &(p2->x);

	if (abs(*p2y - *p1y) > abs(*p2x - *p1x)){ //If the line is steep, swap Xs and Ys
		std::swap(p1y, p1x);
		std::swap(p2y, p2x);
		steep=true;
	}

	if (*p1x > *p2x){ //Make the left-most point p1.
		std::swap(p1x,p2x);
		std::swap(p1y,p2y);
	}

	//Bresenham's algorithm.
	int dx = *p2x - *p1x;
	int dy = abs(*p2y - *p1y);
	int d = 2*dy - dx;
	int incrX = dy*2;
	int incrXY = 2*dy - 2*dx;
	int x = *p1x;
	int y = *p1y;
	//Assign first point.
	if (steep) glVertex2i(y,x); //Switch Y and X coordinates, if they were swapped earlier
	else glVertex2i(x,y);
	//Assign the rest of the points...
	while (x < *p2x){
		if (d <= 0){
			d += incrX;
			x += 1;
		}
		else {
			d += incrXY;
			x += 1;
			y += (y < *p2y) ? 1 : -1;
		}
		if (steep) glVertex2i(y,x);
		else glVertex2i(x, y);
	}
}

//Draws point based on mouse-click.
void drawPoint() {
	glBegin(GL_POINTS);
			glVertex2i(click1->x, click1->y);
	glEnd();
	glFlush();
}

//Draws line based on two mouse-clicks and bresenham() function.
void drawLine() {
	glBegin(GL_POINTS);
		bresenham(click1, click2);
	glEnd();
	glFlush();
}

//Draws rectangle based on two mouse-clicks and bresenham() function.
void drawRectangle(){
	// Determine remaining corners based on the two clicks
	Point2d *otherCorner = new Point2d(click1->x, click2->y);
	Point2d *anotherCorner = new Point2d(click2->x, click1->y);
	//Draw!
	glBegin(GL_POINTS);
		bresenham(click1, otherCorner);
		bresenham(otherCorner, click2);
		bresenham(click2, anotherCorner);
		bresenham(anotherCorner,click1);
	glEnd();
	glFlush();
}

//Draws circle based on two mouse-clicks and bresenham() function.
//referenced https://banu.com/blog/7/drawing-circles/
void drawCircle(){
	int radius = distance(click1, click2);
	int x, y;
	glBegin(GL_POINTS);
	for (x = -radius; x<= radius; x++){
		y = (int)sqrt((double)(radius*radius)-(x*x));
		glVertex2i(click1->x+x,click1->y+y);
		glVertex2i(click1->x+x,click1->y-y);
		glVertex2i(click1->x+y,click1->y+x);
		glVertex2i(click1->x-y,click1->y-x);
	}
	glEnd();
	glFlush();
}

//Clears the screen by drawing every pixel black.
void drawClear(){
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
		for (int i = 0; i < 600; i++){
			for (int j = 0; j < 400; j++){
				glVertex2i(i,j);
			}
		}
	glEnd();
	glFlush();
}

//Mouse click handler.
void mouse(int button, int state, int x, int y){
	glColor3f(drawColour->r,drawColour->g,drawColour->b);

	if (state == GLUT_DOWN){
		if (drawShape == point){
			*click1 = Point2d(x, y);
			drawPoint();
		}
		else {
			if (whichClick == 1){
				*click1 = Point2d(x, y);
				whichClick = 2;
			}
			else {
				*click2 = Point2d(x, y);
				whichClick = 1;
				if (drawShape==line){
					drawLine();
				}
				else if (drawShape==rectangle){
					drawRectangle();
				}
				else {
					drawCircle();
				}
			}
		}
	}
}

//Motion-click handler.
void motion(int x, int y){
	if (drawShape == point){
		*click1 = Point2d(x, y);
		drawPoint();
	}
}

//Menu funcion for glutCreateMenu.
void menu(int val){
	switch (val){
		case 0:
			exit(0);
			break;
		case 1:
			*drawColour = *red;
			break;
		case 2:
			*drawColour = *blue;
			break;
		case 3:
			*drawColour = *green;
			break;
		case 4:
			*drawColour = *purple;
			break;
		case 5:
			*drawColour = *yellow;
			break;
		case 6:
			drawShape = point;
			break;
		case 7:
			whichClick = 1;
			drawShape = line;
			break;
		case 8:
			whichClick = 1;
			drawShape = rectangle;
			break;
		case 9:
			whichClick = 1;
			drawShape = circle;
			break;
		case 10:
			drawClear();
			break;
		case 100:
			drawColour->randomize();
			break;

		default:
			break;
	}
}

//Initialize menu values.
void initMenu(){
	int id = glutCreateMenu(menu);
	int colourMenu = glutCreateMenu(menu);
	int shapeMenu = glutCreateMenu(menu);

	glutSetMenu(id);
		glutAddSubMenu("Colours", colourMenu);
		glutAddSubMenu("Shapes", shapeMenu);
		glutAddMenuEntry("Clear", 10);
		glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutSetMenu(colourMenu);
		glutAddMenuEntry("Red", 1);
		glutAddMenuEntry("Blue", 2);
		glutAddMenuEntry("Green", 3);
		glutAddMenuEntry("Purple", 4);
		glutAddMenuEntry("Yellow", 5);
		glutAddMenuEntry("Random", 100);

	glutSetMenu(shapeMenu);
		glutAddMenuEntry("Point", 6);
		glutAddMenuEntry("Line", 7);
		glutAddMenuEntry("Rectangle", 8);
		glutAddMenuEntry("Circle", 9);
}

//Display function for glutDisplayFunc.
void display(void) {}

//Special key handler.
void special(int key, int x, int y){
	if (key == GLUT_KEY_UP && pointSize < 20.0){ //Up arrow increases point size.
		pointSize += 1.0;
		glPointSize(pointSize);
	}
	else if (key == GLUT_KEY_DOWN && pointSize > 1.0){ //Down arrow decreases point size.
		pointSize += -1.0;
		glPointSize(pointSize);
	}
}

//All callback functions in one place.
void glutCallbacks(){
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	
}

//Initialize.
void init() {
	glutInitWindowSize(600, 400);
	glutCreateWindow("paint");
	glPointSize(pointSize);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0f, 600.0f, 400.0f, 0.0f);
	initMenu();
	drawClear();
}

//Play instructions to be printed on startup.
void instructions(){
	printf("\n\n Welcome to Paint!");
	printf("\n by Vicky Bilbily :)");
	printf("\n\n Click anywhere to get started.");
	printf("\n\n INSTRUCTIONS:");
	printf("\n Left click: draw according to current shape-mode.");
	printf("\n Up arrow: increase draw size by 1 up to 20 pixels.");
	printf("\n Up arrow: decrease draw size by 1 up to 1 pixel.");
	printf("\n Right click: display the menu.");
	printf("\n * MENU OPTIONS:");
	printf("\n -> Shapes: select an item from this submenu to change the current shape-mode.");
	printf("\n -> Colours: select an item from this submenu to change the current draw-colour");
	printf("\n -> Clear: clears all previously drawn items from the canvas, leaving it black.");
	printf("\n -> Exit: close the program.");
	printf("\n * SHAPE OPTIONS");
	printf("\n -> Point: click or click-and-drag anywhere to draw a point at that coordinate.");
	printf("\n -> Line: two clicks- draws a line between the two coordinates");
	printf("\n -> Rectangle: two click- draws a rectangle with diagonally-opposite corners at the clicked coordinates.");
	printf("\n -> Circle: two clicks- draws a circle with a midpoint at the first click and a radius as large as the distance between the two coordinates.");
	printf("\n * COLOUR OPTIONS");
	printf("\n -> Red, Green, Blue, etc.: changes the draw colour to the selected colour.");
	printf("\n -> Random: changes the draw colour to a randomly generated colour.");
	printf("\n\n That's all! Enjoy.");
}
//Main function.
int main(int argc, char **argv) {
	instructions();
	srand(time(0));
	glutInit(&argc, argv);
	init();
	glutCallbacks();
	glutMainLoop();

	return 0;
}