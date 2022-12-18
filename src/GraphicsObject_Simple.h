/*====================
	MADE BY REINGD
====================*/
#ifndef GRAPHICS_OBJECT_SIMPLE_H
#define GRAPHICS_OBJECT_SIMPLE_H

#include "GraphicsObject.h"

//TO BE USED WITH simple_texture SHADER

class GraphicsObject_Simple : public GraphicsObject
{
public:
	GraphicsObject_Simple(const Model* model, const ShaderObject* shader);
	~GraphicsObject_Simple();

	GraphicsObject_Simple() = delete;
	GraphicsObject_Simple(const GraphicsObject_Simple&) = delete;
	GraphicsObject_Simple(GraphicsObject_Simple&&) = delete;
	GraphicsObject_Simple& operator=(const GraphicsObject_Simple&) = delete;
	GraphicsObject_Simple& operator=(GraphicsObject_Simple&&) = delete;

protected:
	//RenderMaterial Contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;


};

#endif // !GRAPHICS_OBJECT_SIMPLE_H
