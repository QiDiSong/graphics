#include "point.h"
#include <stdio.h> //needed for printf command

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

//print method
void Point::print(){
	printf("point= (%f, %f, %f) \n",this->x,this->y,this->z);
}