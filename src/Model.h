/*====================
	MADE BY REINGD
====================*/
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

//this will be part of manager dlinks
//this is the expandable object
//attach data as available
//animation, skelleton etc
class Model //: public DLink
{
public:
	Model();
	~Model();

	Mesh* AttachedMesh() const;
protected:
	void GenerateVBOs() const;

protected:
	Mesh* meshData;
};

#endif // !MODEL_H
