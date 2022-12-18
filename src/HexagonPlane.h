/*====================
	MADE BY REINGD
====================*/
#ifndef HEXAGON_PLANE_H
#define HEXAGON_PLANE_H

#include <vector>
#include "Model.h"

class HexagonPlane : public Model
{
public:
	HexagonPlane();
	~HexagonPlane() = default;

private:
	//VBOS
	std::vector<MeshProperties::position> vertices;
	std::vector<MeshProperties::textureUV> textures;
	
	//EBO
	std::vector<MeshProperties::index> indices;

};

#endif // !HEXAGON_PLANE_H
