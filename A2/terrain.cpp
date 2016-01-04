
#include <windows.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "3Dlib.cpp"

/*TO-DO
- include for apple stuff
- material?
- print instructions
*/

//our two GLUT windows
int window1;
int window2;

//some global variables...
float** heightMap; 
Vector** normals; //array of normals that corresponds to heightmap
int mapSize = 0;
float angleX=5; //camera X-rotation
float angleY=5; //camera Y-rotation
float eye[] = {10,10,10}; //default camera location
float maxHeight = 0;
float editRadius = 10; //default hill radius when editing map

//booleans for different draw modes
int drawMode = 0;
bool smoothShade = true;
bool lightingOn = true;
bool materialOn = true;
bool moveLight0 = true;

//lighting
float light_pos0[] = {0,0,0,1.0};
float amb0[4] = {0.5,0.5,0.5,1};
float diff0[4] = {1,1,1, 1};
float spec0[4] = {1, 1, 1, 1};

float light_pos1[] = {0,0,0,1.0};
float amb1[4] = {0,0,0,1};
float diff1[4] = {0,1,1, 1};
float spec1[4] = {1, 1, 1, 1};

//print instructions to terminal
void instructions(){
	printf("\n\n~~~VICKY'S TERRAIN GENERATOR~~~\n"
		"This program renders random 3D terrains according to the circle algorithm. \n"
		"It also renders a 2D map of the terrain in a secondary window, which can be used to modify the terrain.\n\n"
		"Main Window Commands: \n"
		"\t r - randomize the terrain \n"
		"\t arrow keys - rotate camera around x and y axes \n"
		"\t v - toggle view between filled, wireframe, and filled + wireframe \n"
		"\t f - toggle between flat and smooth shading \n"
		"\t l - toggle lighting on or off \n"
		"\t w,a,s,d,(q,e) - move the light along x, y, and z axes   \n"
		"\t tab - toggle between moving light0 (white) and light1 (coloured) \n\n"
		"Secondary Window Commands: \n"
		"\t left click - add a hill at the click-location\n"
		"\t right click - add a dip at the click-location\n"
		"\t page up - increase the hill/dip radius\n"
		"\t page down - decrease the hill/dip radius\n"
		"\t repeated clicks will continue increasing/decreasing the height at a location\n\n"
		"NOTE: I put the 2D map in the middle of a 3x larger window because Windows enforces a minimum width on windows, which caused glitches for maps < 120x120.\n"
		"Also, Windows 10 specifically doesn't seem to support secondary GLUT windows very well. Works perfectly everywhere else. \n"
		"Enjoy :^)\n\n"
		);
}

//clamping function for the map
int inMap(int n){
	return n <= 0 ? 0 : n >= mapSize ? mapSize-1 : n;
}

//circle algorithm for creating a hill at a given point in a given heightmap
//the greater the value of disp, the steeper the hill
//modified algorithm from: 
void circleAlgo(float** heightMap, int x, int z, float radius, float disp){
	//looping through each X within the circle radius
	for (int i = inMap(x-radius); i <= inMap(x+radius); i++){
		//looping through each Z within the circle radius
		for (int j = inMap(z-radius); j <= inMap(z+radius); j++){
			float pb = sqrt(pow(z-j,2)+pow(x-i,2))*2/(radius*2);
			if (abs(pb) < 1.0) heightMap[i][j] += disp + cos(pb*3.14)*disp;
		}
	}
}

//finds max height in terrain (used in this program to generate greyscale coloring)
void findMaxHeight(){
	maxHeight = 0;
	for (int i = 0; i < mapSize; ++i) {
  		for (int j = 0; j < mapSize; j++){
  			if (heightMap[i][j] > maxHeight) maxHeight=heightMap[i][j];
  		}
	}
}

//generate a random nxn heightmap
float** genHeights(){

	// creating a dynamic 2D array of floats
	// first level is Xs, second is Zs, with a Y value at each XY coordinate
	float** heightMap;
	heightMap = new float*[mapSize]; 

	// initializing all values in heightMap to 0
	for (int i = 0; i < mapSize; i++) {
  		heightMap[i] = new float[mapSize];
  		for (int j = 0; j < mapSize; j++){
  			heightMap[i][j] = 0;
  		}
	}
	//variables to be plugged into circle algorithm
	int x;
	int y;
	int r;
	int disp;

	// make a random number of hills at random points
	int numberOfHills= rand()%(int)round(mapSize); //number of hills relative to map size
	for (int hills=0; hills < numberOfHills; hills++){
		x = rand()%(mapSize-1);
		y = rand()%(mapSize-1);
		r = rand()%(int)round(mapSize/10)+10; //radius relative to map size
		disp = rand()%5; //displacement of height ranges from 0 to 10

		//perform the algorithm!
		circleAlgo(heightMap, x, y, r, disp);
	}
	return heightMap;
}

//computes normals of a given heights array that will be drawn with quads
Vector** computeNormals(float** heights){
		//instantiate first dimension of array
	Vector** normals = new Vector*[mapSize];
	for (int x = 0; x < mapSize; x++) {
		//instantiate second dimension of array
		normals[x] = new Vector[mapSize];
  		for (int z = 0; z < mapSize; z++){
  			
  			//create vector for the vertex normal at x,z
  			Vector* average = new Vector();

  			//1) FIND EDGES
  			//since this is a quad, there are four faces
  			//each face normal requires two edges to cross-product to find the normal
  			//however the edges are shared, so we only really need 4 edges:

  			//ALL THE CASE STATEMENTS are to avoid array-index out of bounds errors
  			//polygons on the edges don't necessarily have 4 neighbouring!!
  			Vector *e1;
  			if (x < (mapSize-1)) e1 = vBetween(new Point(x,heights[x][z],z),new Point(x+1,heights[x+1][z],z));
  			Vector *e2;
  			if (z < (mapSize-1)) e2 = vBetween(new Point(x,heights[x][z],z),new Point(x,heights[x][z+1],z+1));
  			Vector *e3;
  			if (x>0) e3 = vBetween(new Point(x,heights[x][z],z),new Point(x-1,heights[x-1][z],z));
  			Vector *e4;
  			if (z>0) e4 = vBetween(new Point(x,heights[x][z],z),new Point(x,heights[x][z-1],z-1));

  			//2) CROSS EDGES TO GET NORMAL
  			//and 3) ADD RESULT TO AVERAGE
  			if (x < (mapSize-1) && z < (mapSize-1)) average->add(e1->cross(e2));
  			if (x > 0 && z < (mapSize-1)) average->add(e2->cross(e3));
  			if (x > 0 && z > 0) average->add(e3->cross(e4));
  			if (x < (mapSize-1) && z > 0) average->add(e4->cross(e1));

  			//4) NORMALIZE TO GET VERTEX NORMAL!!!
  			average->normalize();
  			normals[x][z] = *average;
  		}
	}
	return normals;
}

//draws the terrain with greyscale coloring
void drawTerrain(float** heights){
	//enable filled polygon mode and lighting
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	if (lightingOn){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}
	else glDisable(GL_LIGHTING);

	glBegin(GL_QUADS);
    for (int x = 1; x < mapSize-1; x++) { 
      	for (int z = 1; z < mapSize-1; z++) {
        	
        	//find colours
	     	float c1 = heights[x][z]/maxHeight;
	        float c2 = heights[x+1][z]/maxHeight;
	        float c3 = heights[x+1][z+1]/maxHeight;
	        float c4 = heights[x][z+1]/maxHeight;
	    
	    	//draw quad vertices CCW
	    	//assigning colors and normals as well
	       	glColor3f(c1,c1,c1);
	       	glNormal3f(normals[x][z].x,normals[x][z].y,normals[x][z].z);
	        glVertex3f(x, heights[x][z], z);

	        glColor3f(c2,c2,c2);
	        glNormal3f(normals[x+1][z].x,normals[x+1][z].y,normals[x+1][z].z);
	        glVertex3f(x+1, heights[x+1][z], z);

	        glColor3f(c3,c3,c3);
	        glNormal3f(normals[x+1][z+1].x,normals[x+1][z+1].y,normals[x+1][z+1].z);
	        glVertex3f(x+1, heights[x+1][z+1], z+1);

	        glColor3f(c4,c4,c4);
	        glNormal3f(normals[x][z+1].x,normals[x][z+1].y,normals[x][z+1].z);
	        glVertex3f(x, heights[x][z+1], z+1);
      }
    }
    glEnd();
}

//draws terrain as green wireframe
void drawWireframe(float** heights){
	//enable lines mode, disables lighting
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	//drawing with quads
	glBegin(GL_QUADS);
	glColor3f(0,1,0); //green! ~the matrix~ effect :)
	for (int x = 1; x < mapSize-1; x++) { 
      	for (int z = 1; z < mapSize-1; z++) {

      		//draw quad vertices CCW
          	glVertex3f(x, heights[x][z], z);
         	glVertex3f(x+1, heights[x+1][z], z);
          	glVertex3f(x+1, heights[x+1][z+1], z+1);
          	glVertex3f(x, heights[x][z+1], z+1);
      	}
     }
      glEnd();
}

//display function for the second window (2d map window)
void display2(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set 2d co-ordinate space
	gluOrtho2D(0,mapSize*3,mapSize*3,0);
	glMatrixMode(GL_MODELVIEW);

	//translating the map to the middle of the window
	glTranslatef(mapSize,mapSize,0);

	//draw 2d map! 
	//the point at x,z will have its color determined by y
	glBegin(GL_POINTS);
	for (int x = 0; x<mapSize; x++){
		for (int z = 0; z<mapSize; z++){
			int y = heightMap[x][z];
			glColor3f(y/maxHeight,y/maxHeight,y/maxHeight);
			glVertex2i(x,z);
		}
	}
	glEnd();

	//translating back
	glTranslatef(-mapSize,-mapSize,0);

	glutSwapBuffers();
}


//display function for the main window (3d terrain!)
void display(){
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//CAMERA
	gluLookAt(eye[0], eye[1], eye[2], 0,0,0, 0, 1, 0);
	glRotatef(angleY,1,0,0);
	glRotatef(angleX,0,1,0);
	glTranslatef(-mapSize/2, 0, -mapSize/2);
    
    //LIGHTING
    if (lightingOn){
	    glPushMatrix();
	    glLightfv(GL_LIGHT0,GL_POSITION,light_pos0);
	    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

		glLightfv(GL_LIGHT1,GL_POSITION,light_pos1);
	    glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diff1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
		glPopMatrix();
	}

    //DRAWING
	glPushMatrix();
	//find max height for the sake of color computations
	findMaxHeight();
	//depending on drawMode, draw either the filled terrain, the wireframe, or both
   	if (drawMode%3==0 | drawMode%3==2) drawTerrain(heightMap);
    if (drawMode%3==1 | drawMode%3==2) drawWireframe(heightMap);
	glPopMatrix();

	glutSwapBuffers();
	
	//redisplay the secondary window as well
	glutSetWindow(window2);
	glutPostRedisplay();

	//set back to main window for next display
	glutSetWindow(window1);
}

//mouse func for window2
void mouse2(int button, int state, int x, int z){
	//(add mapSize/2 to account for the translation of the map within the window)
	x -= round(mapSize);
	z -= round(mapSize);

	//if the left button is clicked, add a hill in heightMap at x,z
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		circleAlgo(heightMap,x,z,editRadius,5);
		normals = computeNormals(heightMap); //recompute normals for new map
		glutSetWindow(window1);
		glutPostRedisplay();
	}
	//if the left button is clicked, add a valley in heightMap at x,z
	//(add mapSize/2 to account for the translation of the map within the window)
	if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON){
		circleAlgo(heightMap,x,z,editRadius,-5);
		normals = computeNormals(heightMap); //recompute normals for new map
		glutSetWindow(window1);
		glutPostRedisplay();
	}
}

//glut keyboard function
void kbd(unsigned char key, int x, int y)
{
	switch(key){

		//quit program
		case 27:
			exit(0);
			break;

		//generate new random map, redisplay
		case 'r':
			heightMap = genHeights();
			normals = computeNormals(heightMap);
			glutPostRedisplay();
			break;

		//toggle between 3 draw-modes (solid, wireframe, wireframe+solid) and redisplay
		//drawMode var used in display func
		case 'v':
			drawMode++;
			glutPostRedisplay();
			break;

		//toggle shading mode between flat and smooth (gourad) and redisplay
		case 'f':
			if (smoothShade){
				glShadeModel(GL_FLAT);
				smoothShade = false;
			}
			else{
				glShadeModel(GL_SMOOTH);
				smoothShade = true;
			}
			glutPostRedisplay();
			break;

		//toggle lighting on or off, redisplay
		case 'l':
			if (lightingOn){
			 lightingOn = false; 
			 glutPostRedisplay();
			}
			else{
				lightingOn = true;
				glutPostRedisplay();
			}
			break;

		//MOVE LIGHTING! 
		//FIRST select which light you'd like to move

		case 9:
			if (moveLight0){
				moveLight0 = false;
			}
			else{
				moveLight0 = true;
			}
			break;

		//THEN
		//using WASD
		// d,a (+-x) w,s (+-y) e,q (z)
		//update light_pos#[]

		//left
		case 'a':
			if (lightingOn){
				if (moveLight0) light_pos0[0]-=5;
				else light_pos1[0]-=5;
				glutPostRedisplay();
			}
			break;

		//right
		case 'd':
			if (lightingOn){
				if (moveLight0) light_pos0[0]+=5;
				else light_pos1[0]+=5;
				glutPostRedisplay();
			}
			break;

		//down
		case 's':
			if (lightingOn){
				if (moveLight0) light_pos0[1]-=5;
				else light_pos1[1]-=5;
				glutPostRedisplay();
			}
			break;

		//up
		case 'w':
			if (lightingOn){
				if (moveLight0) light_pos0[1]+=5;
				else light_pos1[1]+=5;
				glutPostRedisplay();
			}
			break;

		//in
		case 'q':
			if (lightingOn){
				if (moveLight0)light_pos0[2]-=5;
				else light_pos1[2]-=5;
				glutPostRedisplay();
			}
			break;

		//out
		case 'e':
			if (lightingOn){
				if (moveLight0)light_pos0[2]+=5;
				else light_pos1[2]+=5;
				glutPostRedisplay();
			}
			break;

		default:
			break;
	}
}

//rotate camera by adjusting rotation angle
void special(int key, int x, int y){
  	switch(key){

    	 case GLUT_KEY_LEFT:
    	 	angleX -= 5;
        	glutPostRedisplay();
        	break;

     	 case GLUT_KEY_RIGHT:
     	 	angleX += 5;
       		glutPostRedisplay();
        	break;

      	case GLUT_KEY_UP:
      		angleY += 5;
       		glutPostRedisplay();
        	break;

      	case GLUT_KEY_DOWN:
      		angleY -= 5;
          	glutPostRedisplay();
          	break;

        case GLUT_KEY_PAGE_UP:
        	if (editRadius>=5){
        		editRadius += 5;
        	}
        	break;

        case GLUT_KEY_PAGE_DOWN:
        	if (editRadius <=mapSize){
        		editRadius -= 5;
        	}
        	break;

        default:
        	break;

  }
}

int main(int argc, char** argv){

	instructions();

	//to make random really random...
	srand(time(0));

	//ask user for terrain size
	std::cout << "Please pick a terrain size: ";
	std::cin >> mapSize;

	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	window1 = glutCreateWindow("terrain");
    
	//enable Z buffer test
	glEnable(GL_DEPTH_TEST);

	//initial setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set viewing volume
	gluPerspective(45,1,1,800);
	
	//set clear colour to black
	glClearColor(0, 0, 0, 0);

	//register glut callbacks for keyboard and display function
	glutKeyboardFunc(kbd);
	glutDisplayFunc(display);
	glutSpecialFunc(special);

	//generate terrain numbers
	heightMap = genHeights();
	normals = computeNormals(heightMap);

	//adjust camera location accordingly
	eye[0]=mapSize;
	eye[1]=mapSize;
	eye[2]=mapSize/2;

	//adjust light1 location to be at the corner of the map (using mapSize)
	light_pos1[0] = mapSize;
	light_pos1[2] = mapSize;

	//secondary window for 2D map display
	//size is mapSize*3 to avoid conflicting with Windows' minimum window width
	glutInitWindowSize(mapSize*3,mapSize*3);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	window2 = glutCreateWindow("map");
	glutSetWindow(window2);
	glutDisplayFunc(display2); //separate display func
	glutSpecialFunc(special); //uses the same special func
	glutMouseFunc(mouse2); //separate mouse func
	
	//start the rendering with the main window
	glutSetWindow(window1);
	//start the program!
	glutMainLoop();

	return 0;
}
