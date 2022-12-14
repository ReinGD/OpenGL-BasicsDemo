/*====================
	MADE BY REINGD
====================*/
#ifndef RENDER_MATERIAL_H
#define RENDER_MATERIAL_H
#include <glad/glad.h>

class RenderMaterial
{
protected:
	RenderMaterial() = default;
	virtual ~RenderMaterial() = default;

	RenderMaterial(const RenderMaterial&) = delete;
	RenderMaterial(RenderMaterial&&) = delete;
	RenderMaterial& operator= (const RenderMaterial&) = delete;
	RenderMaterial& operator= (RenderMaterial&&) = delete;

	virtual void SetState() = 0;
	virtual void SetDataGPU() = 0;
	virtual void Draw() = 0;
	virtual void RestoreState() = 0;
};
#endif // !RENDER_MATERIAL_H
