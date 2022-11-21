#include <vector>
#include "Mesh.h"
#include "ShaderObject.h"

#ifndef HEXAGON_PLANE_H
#define HEXAGON_PLANE_H

class HexagonPlane : public Mesh
{
public:
	HexagonPlane();
	~HexagonPlane() = default;

protected:
	virtual void GenerateBuffers() override;
	virtual void BindBufferData() override;
	virtual void SetVertexAttributes() override;

private:
	//VBOS
	std::vector<MeshProperties::position> vertices;
	std::vector<MeshProperties::textureUV> textures;
	
	//EBO
	std::vector<MeshProperties::index> indices;

};

#endif // !HEXAGON_PLANE_H
