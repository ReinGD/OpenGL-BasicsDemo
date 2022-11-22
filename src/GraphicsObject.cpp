#include "GraphicsObject.h"
#include <cassert>

GraphicsObject::GraphicsObject(const Model* model, const ShaderObject* shader)
	:pShaderObject(shader)
{
	pMesh = model->AttachedMesh();
	assert(pMesh);
	assert(pShaderObject);


}

GraphicsObject::~GraphicsObject()
{
	//delete anything dynamic here
}

void GraphicsObject::Render()
{
	//Set the draw state for this particular object
	this->SetState();

	//Set the data needed for the shader (uniforms etc)
	this->SetDataGPU();

	//draw the object
	this->Draw();

	//Reset the state to the default state
	this->RestoreState();
}

void GraphicsObject::SetWorld()
{
	//this will set the world matrix, need to add math lib
}

const Mesh& GraphicsObject::GetMesh() const
{
	return *this->pMesh;
}
