//Header file for class

#ifndef __MATHLIB_H__ //if not defined
#define __MATHLIB_H__ //define this term

class Point2d{

public:
	//constructors
	Point2d(); 
	Point2d(int x, int y);

	//deconstructor
	//~Point2d();
	
	//public vars
	int x,y;

	void printVal();
	int getX();
	int getY();
};

class Vec2d {

public:
	//constructors
	Vec2d();
	Vec2d(float x, float y);

	//deconstructor
	// ~Vec2d();

	//public vars
	float x, y, mag;

	void printVal();

};

class Colour {
public: 
	Colour();
	Colour(float r, float g, float b);

	~Colour();

	float r, g, b;

	void printVal();

	void randomize();
};

float distance(Point2d *p1, Point2d *p2);

float fastDistance(Point2d *p1, Point2d *p2);

float length(Vec2d *v); //also manipulates given vector

Vec2d* normalize(Vec2d *v);

Vec2d* multiplyVec2d(Vec2d *v, float s);

Vec2d* createVec2d(Point2d *p1, Point2d *p2);

Point2d* movePoint2d(Point2d *point, Vec2d *vector);

#endif