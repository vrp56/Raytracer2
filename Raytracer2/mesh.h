#pragma once
#ifndef MESH_H
#define MESH_H

#include "vec3.h"

class mesh {
public:
	mesh();
	void LoadObjModel(const char* filename); 
	
};
#endif // !MESH_H
