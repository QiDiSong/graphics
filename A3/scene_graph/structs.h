#ifndef __STRUCTS_H__	//guard against cyclic dependancy
#define __STRUCTS_H__

typedef struct{
	float x, y, z;
}Vector3D;

typedef struct{
	float x, y, z, w;
}Vector4D;

// typedef struct{
// 	float ambient[4];
// 	float diffuse[4];
// 	float specular[4];
// 	float shine;
// }Material;

// typedef struct{
// 	float position[4];
// 	float ambient[4];
// 	float diffuse[4];
// 	float emission[4];
// 	float specular[4];
// }Lighting;

#endif