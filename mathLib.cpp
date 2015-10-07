#include <stdio.h>
#include <math.h>
#include "mathLib.h"

/*Point2d class*/
Point2d::Point2d(){
	x = 0.0f;
	y = 0.0f; 
}

Point2d::Point2d(int x, int y){
	this->x = x;
	this->y = y;
}

//Point2d::~Point2d();

void Point2d::printVal(){

	printf("x = %f, y = %f \n", x,y); //printf is part of stdio

}

int Point2d::getX(){
	return this->x;
}

int Point2d::getY(){
	return this->y;
}

// /* Vec2d class */
Vec2d::Vec2d(){
	x = 0.0f;
	y = 0.0f;
	mag = 0.0f;
}

Vec2d::Vec2d(float x, float y){
	this->x = x;
	this->y = y;
	length(this);
}

void Vec2d::printVal(){
	printf("x= %f, y=%f, magnitude=%f \n", x, y, mag);
}

/*Colour class */
Colour::Colour(){
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
}

Colour::Colour(float r, float g, float b){
	this->r=r;
	this->g=g;
	this->b=b;
}

void Colour::randomize(){
	this->r=rand() / (RAND_MAX + 1.);
	this->g=rand() / (RAND_MAX + 1.);
	this->b=rand() / (RAND_MAX + 1.);
}

void Colour::printVal(){
	printf("r = %f, g = %f, b=%f \n", r,g,b);
}


/* Distance function */
// sqrt(dx^2 + dy^2)
float distance(Point2d *p1, Point2d *p2){
	return sqrt(pow((p2->x - p1->x),2) + pow((p2->y - p1->y),2));
}

// /* Fast distance function */
// // dx^2 + dy^2
float fastDistance(Point2d *p1, Point2d *p2){
	return pow((p2->x - p1->x),2) + pow((p2->y - p1->y),2);
}

// /* Length function*/
float length(Vec2d *vector){
	float mag = sqrt(pow(vector->x,2) + pow(vector->y, 2));
	vector->mag = mag;
	return mag;
}

// /* Normalize function */
Vec2d* normalize(Vec2d *vector){
	float xNorm = vector->x/vector->mag;
	float yNorm = vector->y/vector->mag;
	Vec2d *norm = new Vec2d(xNorm, yNorm);
	return norm;
}

// /* Vector multiply function */
Vec2d* multiplyVec2d(Vec2d *vector, float scalar){
	Vec2d *multiplied = new Vec2d(vector->x*scalar, vector->y*scalar);
	return multiplied;
}

Vec2d* createVec2d(Point2d *p1, Point2d *p2){
	Vec2d *between = new Vec2d(p2->x - p1->x, p2->y - p1->y);
	return between;
}

Point2d* movePoint2d(Point2d *point, Vec2d *vector){
	Point2d *moved = new Point2d(point->x + vector->x, point->y + vector->y);
	return moved;
}

//main, for testing
// int main(int argc, char** argv){
// 	Colour *c = new Colour (0.0f, 0.0f, 0.0f);
// 	float r = ((double) rand() / (RAND_MAX)) + 1;
// }
