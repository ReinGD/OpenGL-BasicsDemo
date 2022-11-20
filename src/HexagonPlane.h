#include <vector>
#include "ModelProperties.h"
#include "ShaderProgram.h"
#ifndef HEXAGON_PLANE_H
#define HEXAGON_PLANE_H

class HexagonPlane
{
public:
	HexagonPlane(ShaderProgram shaderProgram);
	~HexagonPlane() = default;

	void draw();

private:
	void GenerateBuffers();
	void BindBufferData();
	void SetVertexAttributes();
private:
	unsigned int VAO; //vertex array object
	unsigned int VBO; //vertex buffer object
	unsigned int EBO; //element buffer object

	std::vector<ModelProperties::vertex> vertices;
	std::vector<ModelProperties::index> indices;

	ShaderProgram shader;

};

#endif // !HEXAGON_PLANE_H
