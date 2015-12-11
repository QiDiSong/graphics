#ifndef __MATERIAL_H__	//guard against cyclic dependancy
#define __MATERIAL_H__

#include <windows.h>
#include <stdio.h>

//material class, used for scene objects
class Material{
public:
	//constructors
	Material();
	Material(float* amb, float* dif, float* spec, float sh);

	float* ambient;
	float* diffuse;
	float* specular;
	float shine;
};

void setMaterial(Material m);
#endif