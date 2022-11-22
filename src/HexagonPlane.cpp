#include "HexagonPlane.h"
#include "OpenGL_Helper.h"
HexagonPlane::HexagonPlane()
{
	/*
		THIS WHOLE DATA SECTION WILL EVENTUALLY BE PART OF A SERIALIZATION/DESERIALIZATION PROCESS
		FOR NOW IT IS UPLOADED MANUALLY BUT THIS SHOULD COME FROM FILE
	*/

	this->meshData->numTriangles = 6;
	this->meshData->numVerts = 18;

	this->vertices.reserve(this->meshData->numVerts);
	this->textures.reserve(this->meshData->numVerts);
	this->indices.reserve(this->meshData->numTriangles);

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

	//this generates the vbos/ebo
	auto vertexSize = this->vertices.size() * sizeof(MeshProperties::position);
	this->meshData->VBO_Verts = VBOData(true, this->vertices.size(),0, vertexSize, sizeof(MeshProperties::position), this->vertices.data());

	auto textureSize = this->textures.size() * sizeof(MeshProperties::textureUV);
	this->meshData->VBO_Texts = VBOData(true, this->textures.size(),1, textureSize, sizeof(MeshProperties::textureUV), this->textures.data());

	auto indexSize = this->indices.size() * sizeof(MeshProperties::index);
	this->meshData->EBO = VBOData(true, this->indices.size(),0, indexSize, sizeof(MeshProperties::index), this->indices.data());

	GenerateVBOs();
}

