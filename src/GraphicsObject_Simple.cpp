#include "GraphicsObject_Simple.h"

GraphicsObject_Simple::GraphicsObject_Simple(const Mesh* mesh, const ShaderObject* shader)
	:GraphicsObject(mesh, shader)
{
	assert(mesh);
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
	glBindVertexArray(this->GetMesh().VAO);
	this->pShaderObject->SetActive();


}

void GraphicsObject_Simple::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh().numTriangles, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Simple::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}
