/*====================
	MADE BY REINGD
====================*/
#ifndef GRAPHICS_OBJECT_TEXTURE_H
#define GRAPHICS_OBJECT_TEXTURE_H

#include "GraphicsObject.h"

//TO BE USED WITH positioned_texture SHADER

class GraphicsObject_Texture : public GraphicsObject 
{
public:
	GraphicsObject_Texture(const Model* mesh, const Texture* texture, const ShaderObject* shader);
	~GraphicsObject_Texture();

	GraphicsObject_Texture() = delete;
	GraphicsObject_Texture(const GraphicsObject_Texture&) = delete;
	GraphicsObject_Texture(GraphicsObject_Texture&&) = delete;
	GraphicsObject_Texture& operator=(const GraphicsObject_Texture&) = delete;
	GraphicsObject_Texture& operator=(GraphicsObject_Texture&&) = delete;

	void SetTexture(const Texture* texture);

protected:
	//RenderMaterial Contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

private:
	const Texture* pTexture;
};

#endif // !GRAPHICS_OBJECT_TEXTURE_H
