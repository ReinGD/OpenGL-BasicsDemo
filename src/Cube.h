#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "Mesh.h"

class Cube : public Mesh
{
public:
	Cube();
	~Cube() = default;

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

#endif // !CUBE_H
