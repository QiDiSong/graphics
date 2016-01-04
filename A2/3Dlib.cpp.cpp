#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//library of 3d stuff???

typedef struct material {
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	float shine;
} material;

typedef struct lighting {
	float position[4];
	float ambient[4];
	float diffuse[4];
	float specular[4];
} lighting;

// void setMaterial(struct material m){
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
// 	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m->specular);
// 	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m->shine);
// }

// void setLighting(struct lighting l, int num){
// 	glLightfv(GL_LIGHT0 + num, GL_POSITION, l->position);
//     glLightfv(GL_LIGHT0 + num, GL_AMBIENT, l->ambient);
// 	glLightfv(GL_LIGHT0 + num, GL_DIFFUSE, l->diffuse);
// 	glLightfv(GL_LIGHT0 + num, GL_SPECULAR, l->specular);
// }

//3D point class
class Point{
public:
	Point();
	Point(float x, float y, float z);
	Point(int x, float y, int z);
	float x;
	float y;
	float z;
	void print();
};

//constructors
Point::Point(){
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

Point::Point(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

//constructor specialized for my heightmap
Point::Point(int x, float y, int z){
	this->x = (float)x;
	this->y = y;
	this->z = (float)z;
}

//print method
void Point::print(){
	printf("point= (%f, %f, %f) \n",this->x,this->y,this->z);
}

//3D vector class
class Vector{
public:
	Vector();
	Vector(float x, float y, float z);
	float x;
	float y;
	float z;
	float length;
	void print();
	void normalize();
	void add(Vector* v);
	float calcLength();
	Vector* cross(Vector* v);
};

//calculate the length of this vector and update its length variable
float Vector::calcLength(){
	this->length = sqrt(pow(this->x,2)+pow(this->y,2)+pow(this->z,2));
	return this->length;
}

//constructors
Vector::Vector(){
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->length = 0;
}

Vector::Vector(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
	this->calcLength();
}

//cross this vector with a given vector and return the resultant vector
Vector* Vector::cross(Vector* v){
	Vector* crossed = new Vector((this->y*v->z - this->z*v->y), (this->z*v->x - this->x*v->z), (this->x*v->y - this->y*v->x));
	return crossed;
}

//normalize this vector and update its length
void Vector::normalize(){
	this->x = this->x/this->length;
	this->y = this->y/this->length;
	this->z = this->z/this->length;
	this->calcLength();
}

//vector printing method
void Vector::print(){
	printf("vector= (%f, %f, %f) \n",this->x,this->y,this->z);
}

//calculate the vector between points a and b and return the corresponding vector object
Vector* vBetween(Point* a, Point* b){
	Vector* v = new Vector(b->x-a->x, b->y-a->y, b->z-a->z);
	return v;
}

//add vector v to this vector
void Vector::add(Vector* v){
	this->x += v->x;
	this->y += v->y;
	this->z += v->z;
	this->calcLength();
}