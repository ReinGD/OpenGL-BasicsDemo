#include "Model.h"

//Mesh* Model::AttachedMesh() const
//{
//	return this->meshData;
//}

Model::Model()
{
	this->meshData = new Mesh();
}

Model::~Model()
{
	delete this->meshData;
}

Mesh* Model::AttachedMesh() const
{
	return this->meshData;
}

void Model::GenerateVBOs() const
{
	this->meshData->GenerateBuffers();
}
