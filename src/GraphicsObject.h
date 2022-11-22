#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "RenderMaterial.h"
#include "ShaderObject.h"
#include "Texture.h"
#include "Model.h"

class GraphicsObject : public RenderMaterial
{
public:
	GraphicsObject() = delete;
	GraphicsObject(const GraphicsObject&) = delete;
	GraphicsObject(GraphicsObject&&) = delete;
	GraphicsObject& operator= (const GraphicsObject) = delete;
	GraphicsObject& operator= (GraphicsObject&&) = delete;

	GraphicsObject(const Model* model, const ShaderObject* shader);
	virtual ~GraphicsObject();

	void Render();
	void SetWorld();

	const Mesh& GetMesh() const;


protected:
	const ShaderObject* pShaderObject;
	const Mesh* pMesh;
};

#endif // !GRAPHICS_OBJECT_H
