#include "HexagonPlane.h"
#include "OpenGL_Helper.h"
HexagonPlane::HexagonPlane()
{


	this->numTriangles = 6;
	this->numVerts = 18;


	this->vertices.reserve(this->numVerts);
	this->textures.reserve(this->numVerts);
	this->indices.reserve(this->numTriangles);

	//each triangle will have a different texture coordinate
	//each triangle is separate on purpose to show texture 

	this->vertices.emplace_back(0.00f, 0.00f, 0.00f);
	this->vertices.emplace_back(0.25f, -0.50f, 0.00f);
	this->vertices.emplace_back(-0.25f, -0.50f, 0.00f);

	this->textures.emplace_back(0.50f, 0.50f);
	this->textures.emplace_back(1.00f, 1.00f);
	this->textures.emplace_back(0.00f, 1.00f);

	this->indices.emplace_back(0, 1, 2);

	this->vertices.emplace_back(0.00f, 0.00f, 0.00f);
	this->vertices.emplace_back(-0.25f, 0.50f, 0.00f);
	this->vertices.emplace_back(0.25f, 0.50f, 0.00f);

	this->textures.emplace_back(0.50f, 0.50f);
	this->textures.emplace_back(1.00f, 1.00f);
	this->textures.emplace_back(0.00f, 1.00f);

	this->indices.emplace_back(3, 4, 5);

	this->vertices.emplace_back(0.00f, 0.00f, 0.00f);
	this->vertices.emplace_back(-0.25f, -0.50f, 0.00f);
	this->vertices.emplace_back(-0.50f, 0.00f, 0.00f);

	this->textures.emplace_back(0.50f, 0.50f);
	this->textures.emplace_back(1.00f, 1.00f);
	this->textures.emplace_back(0.00f, 1.00f);

	this->indices.emplace_back(6, 7, 8);


	this->vertices.emplace_back(0.00f, 0.00f, 0.00f);
	this->vertices.emplace_back(0.50f, 0.00f, 0.00f);
	this->vertices.emplace_back(0.25f, -0.50f, 0.00f);

	this->textures.emplace_back(0.50f, 0.50f);
	this->textures.emplace_back(1.00f, 1.00f);
	this->textures.emplace_back(0.00f, 1.00f);

	this->indices.emplace_back(9, 10, 11);


	this->vertices.emplace_back(0.00f, 0.00f, 0.00f);
	this->vertices.emplace_back(-0.50f, 0.00f, 0.00f);
	this->vertices.emplace_back(-0.25f, 0.50f, 0.00f);

	this->textures.emplace_back(0.50f, 0.50f);
	this->textures.emplace_back(1.00f, 1.00f);
	this->textures.emplace_back(0.00f, 1.00f);

	this->indices.emplace_back(12, 13, 14);


	this->vertices.emplace_back(0.00f, 0.00f, 0.00f);
	this->vertices.emplace_back(0.25f, 0.50f, 0.00f);
	this->vertices.emplace_back(0.50f, 0.00f, 0.00f);

	this->textures.emplace_back(0.50f, 0.50f);
	this->textures.emplace_back(1.00f, 1.00f);
	this->textures.emplace_back(0.00f, 1.00f);

	this->indices.emplace_back(15, 16, 17);

	GenerateBuffers();
	BindBufferData();
	SetVertexAttributes();

}

void HexagonPlane::GenerateBuffers()
{
	//generate the vertex array object
	glGenVertexArrays(1, &this->VAO);
	//generate an open gl buffer to store vertex data
	glGenBuffers(1, &this->VBO_Verts);
	//generate an open gl buffer to store texture data
	glGenBuffers(1, &this->VBO_Texts);
	//generate an open gl buffer to store index data
	glGenBuffers(1, &this->EBO);
}

void HexagonPlane::BindBufferData()
{
	//bind it
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	auto indexSize = indices.size() * sizeof(MeshProperties::index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices.data(), GL_STATIC_DRAW);
	glCheckError();

}

void HexagonPlane::SetVertexAttributes()
{

	//with the buffer bound we set the attribute to describe how the vertex is layed out
	//this sets the data to the opengl buffers generated earlier
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts);
	auto vertexSize = vertices.size() * sizeof(MeshProperties::position);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices.data(), GL_STATIC_DRAW);
	glCheckError();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshProperties::position), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texts);
	auto textSize = textures.size() * sizeof(MeshProperties::textureUV);
	glBufferData(GL_ARRAY_BUFFER, textSize, textures.data(), GL_STATIC_DRAW);
	glCheckError();

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshProperties::textureUV), (void*)0);
	glEnableVertexAttribArray(1);

}
