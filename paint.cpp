#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <algorithm>

#include "mathLib.cpp"

/*
STILL NEED:
- line drawing function
- can i use gl_poly for clear?
*/

//global accessible variables for clicked points
Point2d *click1 = new Point2d(0, 0);
Point2d *click2= new Point2d(0, 0);

//is it the first or second click?
int whichClick = 1;

//stored colours
Colour *red = new Colour(1.0f, 0.0f, 0.0f);
Colour *green = new Colour(0.0f, 1.0f, 0.0f);
Colour *blue = new Colour(0.0f, 0.0f, 1.0f);
Colour *purple = new Colour(1.0f, 0.0f, 1.0f);
Colour *yellow = new Colour(1.0f, 1.0f, 0.0f);
Colour *drawColour = new Colour(1.0f, 1.0f, 1.0f); //default colour

//point size (defaults to 2)
float pointSize = 2.0f;

//shape modes
int point = 0;
int line = 1;
int rectangle = 2;
int circle = 3;
int clear = 4;
int drawShape = point; //default shape

void straightLine(Point2d *p1, Point2d *p2){
	if (p1->x == p2->x) {
		if (p2->x < p1->x){
			std::swap(p1,p2);
		}
		int x = p1->x;
		while (x <= p2->x){
			glVertex2i(x, p1->y);
			x += 1;
		}
	}
	else if (p1->y == p2->y){
		if (p2->y < p1->y){
		std::swap(p1,p2);
		}
		int y = p1->y;
		while (y <= p2->y){
			glVertex2i(p1->x, y);
			y += 1;
		}
	}
}

//line drawing algorithm
void bresenham(Point2d *p1, Point2d *p2){
	if (p1->x > p2->x){
		std::swap(p1,p2);
	}

	if (abs(p2->y - p1->y) > abs(p2->x - p1->x)){
		std::swap(p1->y, p1->x);
		std::swap(p2->y, p2->x);
	}

	int dx = p2->x - p1->x;
	int dy = abs(p2->y - p1->y);
	int d = 2*dy - dx;
	int incrX = dy*2;
	int incrXY = 2*dy - 2*dx;
	int x = p1->x;
	int y = p1->y;
	printf("from %i, %i to %i, %i \n", x, y, p2->x, p2->y);
	printf("dx: %i \n dy: %i \n d: %i \n", dx, dy, d);
	while (x <= p2->x){
		if (d <= 0){
			d += incrX;
			x += 1;
		}
		else {
			d += incrXY;
			x += 1;
			y += (y < p2->y) ? 1 : -1;
		}
		glVertex2i(x, y);
		printf("point: %i, %i \n", x, y);
	}
}

//used for point drawing mode
void drawPoint() {
	glBegin(GL_POINTS);
			glVertex2i(click1->x, click1->y);
	glEnd();
	glFlush();
}

//used for line drawing mode
void drawLine() {
	// glBegin(GL_LINES);
	// 		glVertex2i(click1->x, click1->y);
	// 		glVertex2i(click2->x, click2->y);
	glBegin(GL_POINTS);
		bresenham(click1, click2);
	glEnd();
	glFlush();
	printf("called drawline \n");
}

//used for rectangle drawing mode
void drawRectangle(){
	glBegin(GL_LINES);

		glVertex2i(click1->x, click1->y);
		glVertex2i(click1->x, click2->y);

		glVertex2i(click1->x, click2->y);
		glVertex2i(click2->x, click2->y);

		glVertex2i(click2->x, click2->y);
		glVertex2i(click2->x, click1->y);

		glVertex2i(click2->x, click1->y);
		glVertex2i(click1->x, click1->y);
	
	glEnd();
	glFlush();
	printf("called drawrect \n");
}

//used for circle drawing mode-
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

//clears the screen, pixel by pixel
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

//mouse click handler
void mouse(int button, int state, int x, int y){
	printf("mouse clicked at %i, %i \n", x, y);
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
				printf("assigned click 1 \n");
			}
			else {
				*click2 = Point2d(x, y);
				whichClick = 1;
				printf("assigned click 2 \n");
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

void motion(int x, int y){
	if (drawShape == point){
		*click1 = Point2d(x, y);
		drawPoint();
	}
}

void init() {
	glPointSize(pointSize);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0f, 600.0f, 400.0f, 0.0f);
	drawClear();
}

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

void display(void) {}

void special(int key, int x, int y){
	if (key == GLUT_KEY_UP && pointSize <= 20.0){
		pointSize += 1.0;
		glPointSize(pointSize);
		printf("increased point size to %f \n", pointSize);
	}
	else if (key == GLUT_KEY_DOWN && pointSize >= 1.0){
		pointSize += -1.0;
		glPointSize(pointSize);
		printf("decreased point size to %f \n", pointSize);
	}
}

void glutCallbacks(){
	glutDisplayFunc(display);
	// glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	// glutReshapeFunc(reshape);
	// glutPassiveMotionFunc(passive);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	//glutInitWindowPosition(200, 200);
	glutInitWindowSize(600, 400);
	glutCreateWindow("paint");
	glutCallbacks();
	initMenu();
	init();
	glutMainLoop();

	return 0;
}