#include "GraphicsObject_Texture.h"

GraphicsObject_Texture::GraphicsObject_Texture(const Mesh* mesh, const Texture* texture, const ShaderObject* shader)
	:GraphicsObject(mesh, shader), pTexture(texture)
{
	assert(pTexture);
}

GraphicsObject_Texture::~GraphicsObject_Texture()
{
}

void GraphicsObject_Texture::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

}

void GraphicsObject_Texture::SetDataGPU()
{
	glBindTexture(GL_TEXTURE_2D, pTexture->getID());
	glBindVertexArray(this->GetMesh().VAO);
	this->pShaderObject->SetActive();

}

void GraphicsObject_Texture::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh().numTriangles, GL_UNSIGNED_INT, 0);
}

void GraphicsObject_Texture::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}
