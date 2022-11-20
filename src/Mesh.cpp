#include "Mesh.h"

Mesh::Mesh()
	:numVerts(0), numTriangles(0),
	VAO(0),
	VBO_Verts(0), VBO_Texts(0), VBO_Norms(0),
	VBO_Color(0), EBO(0)
{
}

Mesh::~Mesh()
{
	//delete anything dynamic here
}

void Mesh::Wash()
{
	this->numVerts = 0;
	this->numTriangles = 0;
	VAO = 0;
	VBO_Verts = 0;
	VBO_Norms = 0;
	VBO_Texts = 0;
	VBO_Color = 0;
	EBO = 0;

}
