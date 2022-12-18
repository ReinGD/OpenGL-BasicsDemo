/*====================
	MADE BY REINGD
====================*/
#include "Mesh.h"
#include "OpenGL_Helper.h"

Mesh::Mesh()
	:numVerts(0), numTriangles(0),
	VAO(0),
	VBO_Verts({}), VBO_Texts({}), VBO_Norms({}),
	VBO_Color({}), EBO({})
{
}

Mesh::~Mesh()
{
	//delete anything dynamic here
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);


	if (this->VBO_Verts.enabled)
	{
		glGenBuffers(1, &this->VBO_Verts.glIndex);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts.glIndex);
		glBufferData(GL_ARRAY_BUFFER, this->VBO_Verts.dataSize, (unsigned char*)this->VBO_Verts.pData, GL_STATIC_DRAW);
		glCheckError();

		glVertexAttribPointer(this->VBO_Verts.attributeIndex, 3, GL_FLOAT, GL_FALSE, this->VBO_Verts.dataWidth, 0);
		glEnableVertexAttribArray(this->VBO_Verts.attributeIndex);
		glCheckError();
	}
	if (this->VBO_Texts.enabled)
	{
		glGenBuffers(1, &this->VBO_Texts.glIndex);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texts.glIndex);
		glBufferData(GL_ARRAY_BUFFER, this->VBO_Texts.dataSize, (unsigned char*)this->VBO_Texts.pData, GL_STATIC_DRAW);
		glCheckError();

		glVertexAttribPointer(this->VBO_Texts.attributeIndex, 2, GL_FLOAT, GL_FALSE, VBO_Texts.dataWidth, 0);
		glEnableVertexAttribArray(this->VBO_Texts.attributeIndex);
		glCheckError();

	}

	if (this->EBO.enabled)
	{
		glGenBuffers(1, &this->EBO.glIndex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO.glIndex);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->EBO.dataSize, this->EBO.pData, GL_STATIC_DRAW);
		glCheckError();
	}
}

void Mesh::Wash()
{
	this->numVerts = 0;
	this->numTriangles = 0;
	VAO = 0;
	VBO_Verts.Clean();
	VBO_Norms.Clean();
	VBO_Texts.Clean();
	VBO_Color.Clean();
	EBO.Clean();

}
