#include "HexagonPlane.h"
#include "OpenGL_Helper.h"
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

HexagonPlane::HexagonPlane(ShaderObject shaderProgram)
	:shader(shaderProgram)
{
	this->vertices.reserve(18);
	this->indices.reserve(6);
	//each triangle will have a different z to show mipmaps
	//each triangle is separate on purpose to show mipmap representation with z depth


	this->vertices.emplace_back(0.00f, 0.00f, 0.00f);
	this->vertices.emplace_back(0.25f, -0.50f, 0.00f);
	this->vertices.emplace_back(-0.25f, -0.50f, 0.00f);

	this->indices.emplace_back(0, 1, 2);

	this->vertices.emplace_back(0.00f, 0.00f, 0.20f);
	this->vertices.emplace_back(-0.25f, 0.50f, 0.20f);
	this->vertices.emplace_back(0.25f, 0.50f, 0.20f);

	this->indices.emplace_back(3, 4, 5);

	this->vertices.emplace_back(0.00f, 0.00f, 0.40f);
	this->vertices.emplace_back(-0.25f, -0.50f, 0.40f);
	this->vertices.emplace_back(-0.50f, 0.00f, 0.40f);

	this->indices.emplace_back(6, 7, 8);


	this->vertices.emplace_back(0.00f, 0.00f, 0.60f);
	this->vertices.emplace_back(0.50f, 0.00f, 0.60f);
	this->vertices.emplace_back(0.25f, -0.50f, 0.60f);

	this->indices.emplace_back(9, 10, 11);


	this->vertices.emplace_back(0.00f, 0.00f, 0.80f);
	this->vertices.emplace_back(-0.50f, 0.00f, 0.80f);
	this->vertices.emplace_back(-0.25f, 0.50f, 0.80f);

	this->indices.emplace_back(12, 13, 14);


	this->vertices.emplace_back(0.00f, 0.00f, 1.00f);
	this->vertices.emplace_back(0.25f, 0.50f, 1.00f);
	this->vertices.emplace_back(0.50f, 0.00f, 1.00f);

	this->indices.emplace_back(15, 16, 17);

	GenerateBuffers();
	BindBufferData();
	SetVertexAttributes();

}

void HexagonPlane::draw()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glUseProgram(shader.getProgram());
	//glCheckError();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, 0);
	//glCheckError();

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

}

void HexagonPlane::GenerateBuffers()
{
	//generate the vertex array object
	glGenVertexArrays(1, &VAO);
	//generate an open gl buffer to store vertex data
	glGenBuffers(1, &VBO);
	//generate an open gl buffer to store index data
	glGenBuffers(1, &EBO);
}

void HexagonPlane::BindBufferData()
{
	//bind it
	glBindVertexArray(VAO);

	while (glGetError() != GL_NO_ERROR);

	//this sets the data to the opengl buffers generated earlier
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	auto vertexSize = vertices.size() * 3 * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices.data(), GL_STATIC_DRAW);
	//glCheckError();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	auto indexSize = indices.size() * 3 * sizeof(float);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices.data(), GL_STATIC_DRAW);
	//glCheckError();

}

void HexagonPlane::SetVertexAttributes()
{

	while (glGetError() != GL_NO_ERROR);

	//with the buffer bound we set the attribute to describe how the vertex is layed out
	//since i have only 1 element (position which is a 3 float element) this is the signature
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelProperties::vertex), (void*)0);
	//glCheckError();
	glEnableVertexAttribArray(0);

}
