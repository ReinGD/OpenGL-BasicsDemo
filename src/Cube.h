#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "Model.h"

class Cube : public Model
{
public:
	Cube();
	~Cube() = default;

private:
	//VBOS
	std::vector<MeshProperties::position> vertices;
	std::vector<MeshProperties::textureUV> textures;

	//EBO
	std::vector<MeshProperties::index> indices;

};

#endif // !CUBE_H
