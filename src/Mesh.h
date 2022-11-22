#ifndef MESH_H
#define MESH_H

#include "MeshProperties.h"
#include <cassert>

#include "VBOData.h"
typedef VBOData EBOData;

class Mesh 
{
public:
	Mesh();
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&&) = delete;
	Mesh& operator= (const Mesh&) = delete;
	Mesh& operator= (Mesh&&) = delete;
	virtual ~Mesh();
 
	void GenerateBuffers();

	void Wash();
	//Data
public:
	int numVerts;
	int numTriangles;

public:

	unsigned int VAO;
	VBOData VBO_Verts; //position
	VBOData VBO_Texts; //uv
	VBOData VBO_Norms; //normals
	VBOData VBO_Color; //color
	EBOData EBO;	   //indices (trilist)


};

#endif // !MESH_H
