/*====================
	MADE BY REINGD
====================*/
#include "GraphicsObject_Simple.h"

GraphicsObject_Simple::GraphicsObject_Simple(const Model* model, const ShaderObject* shader)
	:GraphicsObject(model, shader)
{
	assert(model);
	assert(shader);
}

GraphicsObject_Simple::~GraphicsObject_Simple()
{
}

void GraphicsObject_Simple::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void GraphicsObject_Simple::SetDataGPU()
{
	glBindVertexArray(this->pMesh->VAO);
	this->pShaderObject->SetActive();
}

void GraphicsObject_Simple::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->pMesh->numTriangles, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Simple::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}
