#pragma once
#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "hittable.h"
#include "vec3.h"

class TrianlgeMesh : public hittable {
public:
	TrianlgeMesh(
		const int nfaces,
		const std::unique_ptr<int[]>& faceIndex,
		const std::unique_ptr<int[]>& vertsIndex,
		const std::unique_ptr<vec3[]>& verts) :
		numTris(0)
	{
		int k = 0, maxVertIndex = 0;
		// find out how many triangles we need to create for this mesh
		for (int i = 0; i < nfaces; ++i)
		{
			numTris += faceIndex[i] - 2;
			for (int j = 0; j < faceIndex[i]; ++j)
			{
				if (vertsIndex[k + j] > maxVertIndex) maxVertIndex = vertsIndex[k + j];
			}
			k += faceIndex[i];
		}
		maxVertIndex += 1;

		// allocate memory to store the position of the mesh vertices
		P = std::unique_ptr<vec3[]>(new vec3[maxVertIndex]);
		for (int i = 0; i < maxVertIndex; ++i)
		{
			P[i] = verts[i];
		}


	}

public:
	int numTris;
	std::unique_ptr<vec3[]> P; // triangle vertex posistion
	std::unique_ptr<int[]> trisIndex; // vertex index array
	std::unique_ptr<vec3[]> N; // triangle vertex normals
	// Might need to add a vec2 class for texture coords
};
#endif // !TRIANGLEMESH_H

