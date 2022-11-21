#include "GraphicsObject_Texture.h"

#include "MathEngine.h"
using namespace GD;

float delta = 1.0f;
float increment = 0.0125f;

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
	glBindTexture(GL_TEXTURE_2D, pTexture->getID());

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	this->pShaderObject->SetActive();
}

void GraphicsObject_Texture::SetDataGPU()
{
	glBindVertexArray(this->GetMesh().VAO);

	Matrix proj;
	proj[m0] = 1.60838020f;
	proj[m5] = 2.14450693f;
	proj[m10] = - 1.00019991f;
	proj[m11] = - 1.00000000f;
	proj[m12] = 0.00000000f;
	proj[m13] = 0.00000000f;
	proj[m14] = - 0.200020000f;

	if (delta > 6)
	{
		increment = -0.0125f;
	}
	else if (delta < 1)
	{
		increment = 0.0125f;
	}

	Matrix view(Matrix::Trans::XYZ, 0.0f, 0.0f, -delta);
	Matrix world(Matrix::Special::Identity);

	delta += increment;

	glUniformMatrix4fv(this->pShaderObject->GetUniformLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
	glUniformMatrix4fv(this->pShaderObject->GetUniformLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(this->pShaderObject->GetUniformLocation("world_matrix"), 1, GL_FALSE, (float*)&world);

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
