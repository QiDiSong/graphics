#include <stdlib.h>
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

/* TEXTURE */
GLubyte* image;
GLubyte* img_data;
int width, height, MAX;

GLubyte* LoadPPM(char* file, int* width, int* height, int* MAX)
{
	GLubyte* img;
	FILE *fd;
	int n, m;
	int  k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;
	
	/* first open file and check if it's an ASCII PPM (indicated by P3 at the start) */
	fd = fopen(file, "r");
	fscanf(fd,"%[^\n] ",b);
	if(b[0]!='P'|| b[1] != '3')
	{
		//printf("%s is not a PPM file!\n",file); 
		exit(0);
	}
	//printf("%s is a PPM file\n", file);
	fscanf(fd, "%c",&c);

	/* next, skip past the comments - any line starting with #*/
	while(c == '#') 
	{
		fscanf(fd, "%[^\n] ", b);
		//printf("%s\n",b);
		fscanf(fd, "%c",&c);
	}
	ungetc(c,fd); 

	/* now get the dimensions and MAX colour value from the image */
	fscanf(fd, "%d %d %d", &n, &m, &k);

	//printf("%d rows  %d columns  MAX value= %d\n",n,m,k);

	/* calculate number of pixels and allocate storage for this */
	nm = n*m;
	img = (GLubyte*)malloc(3*sizeof(GLuint)*nm);
	s=255.0/k;

	/* for every pixel, grab the read green and blue values, storing them in the image data array */
	for(i=0;i<nm;i++) 
	{
		fscanf(fd,"%d %d %d",&red, &green, &blue );
		img[3*nm-3*i-3]=red*s;
		img[3*nm-3*i-2]=green*s;
		img[3*nm-3*i-1]=blue*s;
	}

	/* finally, set the "return parameters" (width, height, MAX) and return the image array */
	*width = n;
	*height = m;
	*MAX = k;

	return img;
}

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
				//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
				//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //TEXTURE_MIN_FILTER
				glColor3f(1,0,0);
				glPushMatrix();
				glTranslatef(x, 0, z);
				glScalef(1,0.25,1);
				glutSolidCube(1);
				glPopMatrix();
			}
		}
	}
	/*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //TEXTURE_MIN_FILTER
	glutSolidTeapot(1);*/

}

void kbd(unsigned char key, int x, int y)
{
	//if the "q" key is pressed, quit the program
	if(key == 'q' || key == 'Q')
	{
		exit(0);
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

	drawXZPlane(0, SIZE);
	drawWalls(maze);
	
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
	glutCreateWindow("Maze Game");

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

	glEnable(GL_TEXTURE_2D);
	img_data = LoadPPM((char*)"marble.ppm", &width, &height, &MAX);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
	GL_UNSIGNED_BYTE, img_data); 

	//maze stuff
	int positionX = 0;
	int positionY = 0;
	int goalX = 0;
	int goalY = 0;

	Initialize(maze);
	DrawMaze(maze, positionX, positionY, goalX, goalY);

	//start the program!
	glutMainLoop();

	

	return 0;
}
