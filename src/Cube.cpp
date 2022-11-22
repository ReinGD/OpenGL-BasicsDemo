#include "Cube.h"
#include "OpenGL_Helper.h"

Cube::Cube()
{
	this->numTriangles = 12;
	this->numVerts = 24;

	this->vertices.reserve(this->numVerts);
	this->textures.reserve(this->numVerts);
	this->indices.reserve(this->numTriangles);

	auto positionNearTopLeft  = MeshProperties::position(-1.0f, -1.0f,  1.0f);
	auto positionNearTopRight = MeshProperties::position( 1.0f, -1.0f,  1.0f);
	auto positionNearBotLeft  = MeshProperties::position(-1.0f,  1.0f,  1.0f);
	auto positionNearBotRight = MeshProperties::position( 1.0f,  1.0f,  1.0f);

	auto positionFarTopLeft  = MeshProperties::position(-1.0f, -1.0f, -1.0f);
	auto positionFarTopRight = MeshProperties::position( 1.0f, -1.0f, -1.0f);
	auto positionFarBotLeft  = MeshProperties::position(-1.0f,  1.0f, -1.0f);
	auto positionFarBotRight = MeshProperties::position( 1.0f,  1.0f, -1.0f);

	//front face
	this->vertices.emplace_back(positionNearTopRight);
	this->vertices.emplace_back(positionNearTopLeft);
	this->vertices.emplace_back(positionNearBotLeft);
	this->vertices.emplace_back(positionNearBotRight);

	this->textures.emplace_back(1.00f, 0.00f);
	this->textures.emplace_back(0.00f, 0.00f);
	this->textures.emplace_back(0.00f, 1.00f);
	this->textures.emplace_back(1.00f, 1.00f);

	this->indices.emplace_back(0, 1, 2);
	this->indices.emplace_back(2, 3, 0);

	//back face
	this->vertices.emplace_back(positionFarTopLeft);
	this->vertices.emplace_back(positionFarTopRight);
	this->vertices.emplace_back(positionFarBotRight);
	this->vertices.emplace_back(positionFarBotLeft);

	this->textures.emplace_back(1.00f, 0.00f);
	this->textures.emplace_back(0.00f, 0.00f);
	this->textures.emplace_back(0.00f, 1.00f);
	this->textures.emplace_back(1.00f, 1.00f);

	this->indices.emplace_back(4, 5, 6);
	this->indices.emplace_back(6, 7, 4);

	//left face
	this->vertices.emplace_back(positionNearTopLeft);
	this->vertices.emplace_back(positionFarTopLeft);
	this->vertices.emplace_back(positionFarBotLeft);
	this->vertices.emplace_back(positionNearBotLeft);

	this->textures.emplace_back(1.00f, 0.00f);
	this->textures.emplace_back(0.00f, 0.00f);
	this->textures.emplace_back(0.00f, 1.00f);
	this->textures.emplace_back(1.00f, 1.00f);

	this->indices.emplace_back(8, 9, 10);
	this->indices.emplace_back(10, 11, 8);

	//right face
	this->vertices.emplace_back(positionFarTopRight);
	this->vertices.emplace_back(positionNearTopRight);
	this->vertices.emplace_back(positionNearBotRight);
	this->vertices.emplace_back(positionFarBotRight);

	this->textures.emplace_back(1.00f, 0.00f);
	this->textures.emplace_back(0.00f, 0.00f);
	this->textures.emplace_back(0.00f, 1.00f);
	this->textures.emplace_back(1.00f, 1.00f);

	this->indices.emplace_back(12, 13, 14);
	this->indices.emplace_back(14, 15, 12);

	//top face
	this->vertices.emplace_back(positionFarTopRight);
	this->vertices.emplace_back(positionFarTopLeft);
	this->vertices.emplace_back(positionNearTopLeft);
	this->vertices.emplace_back(positionNearTopRight);

	this->textures.emplace_back(1.00f, 0.00f);
	this->textures.emplace_back(0.00f, 0.00f);
	this->textures.emplace_back(0.00f, 1.00f);
	this->textures.emplace_back(1.00f, 1.00f);

	this->indices.emplace_back(16, 17, 18);
	this->indices.emplace_back(18, 19, 16);

	//bot face
	this->vertices.emplace_back(positionNearBotRight);
	this->vertices.emplace_back(positionNearBotLeft);
	this->vertices.emplace_back(positionFarBotLeft);
	this->vertices.emplace_back(positionFarBotRight);

	this->textures.emplace_back(1.00f, 0.00f);
	this->textures.emplace_back(0.00f, 0.00f);
	this->textures.emplace_back(0.00f, 1.00f);
	this->textures.emplace_back(1.00f, 1.00f);

	this->indices.emplace_back(20, 21, 22);
	this->indices.emplace_back(22, 23, 20);

	GenerateBuffers();
	BindBufferData();
	SetVertexAttributes();
}

void Cube::GenerateBuffers()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO_Verts);
	glGenBuffers(1, &this->VBO_Texts);
	glGenBuffers(1, &this->EBO);
}

void Cube::BindBufferData()
{
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

	auto indexSize = indices.size() * sizeof(MeshProperties::index);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices.data(), GL_STATIC_DRAW);

	glCheckError();
}

void Cube::SetVertexAttributes()
{
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
