#include <vector>
#include "Mesh.h"
#include "ShaderObject.h"

#ifndef HEXAGON_PLANE_H
#define HEXAGON_PLANE_H

class HexagonPlane : public Mesh
{
public:
	HexagonPlane(ShaderObject* shaderProgram);
	~HexagonPlane() = default;

private:
	void GenerateBuffers();
	void BindBufferData();
	void SetVertexAttributes();
private:
	unsigned int VAO; //vertex array object
	unsigned int VBO; //vertex buffer object
	unsigned int EBO; //element buffer object

	std::vector<MeshProperties::position> vertices;
	std::vector<MeshProperties::index> indices;

	ShaderObject* shader;

};

#endif // !HEXAGON_PLANE_H
