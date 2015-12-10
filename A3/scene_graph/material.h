#ifndef __MATERIAL_H__	//guard against cyclic dependancy
#define __MATERIAL_H__

#include <windows.h>
#include <stdio.h>

//material class, used for scene objects
class Material{
public:
	//constructors
	Material();
	Material(float amb[4], float dif[4], float spec[4], float sh);

	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shine;
};

void setMaterial(Material m);
#endif