#ifndef MESH_H
#define MESH_H

#include "MeshProperties.h"
#include <cassert>

//this will be part of manager dlinks
class Mesh //: public DLink
{
public:
	Mesh();
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&&) = delete;
	Mesh& operator= (const Mesh&) = delete;
	Mesh& operator= (Mesh&&) = delete;

	virtual ~Mesh();

	void Wash();
	//Data
public:
	int numVerts;
	int numTriangles;

public:

	unsigned int VAO;
	unsigned int VBO_Verts; //position
	unsigned int VBO_Texts; //uv
	unsigned int VBO_Norms; //normals
	unsigned int VBO_Color; //color
	unsigned int EBO;		//indices (trilist)


};

#endif // !MESH_H
