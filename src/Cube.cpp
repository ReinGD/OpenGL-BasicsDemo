#include "Cube.h"
#include "OpenGL_Helper.h"

Cube::Cube()
{
	this->meshData->numTriangles = 12;
	this->meshData->numVerts = 24;

	this->vertices.reserve(this->meshData->numVerts);
	this->textures.reserve(this->meshData->numVerts);
	this->indices.reserve(this->meshData->numTriangles);

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


	//this generates the vbos/ebo
	auto vertexSize = this->vertices.size() * sizeof(MeshProperties::position);
	this->meshData->VBO_Verts = VBOData(true, this->vertices.size(),0, vertexSize, sizeof(MeshProperties::position), this->vertices.data());

	auto textureSize = this->textures.size() * sizeof(MeshProperties::textureUV);
	this->meshData->VBO_Texts = VBOData(true, this->textures.size(),1, textureSize, sizeof(MeshProperties::textureUV) ,this->textures.data());

	auto indexSize = this->indices.size() * sizeof(MeshProperties::index);
	this->meshData->EBO = VBOData(true, this->indices.size(),0, indexSize, sizeof(MeshProperties::index), this->indices.data());

	GenerateVBOs();
}

