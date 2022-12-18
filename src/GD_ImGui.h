/*====================
	MADE BY REINGD
====================*/
#ifndef GD_IM_GUI_H
#define GD_IM_GUI_H

CLEAN_NEW_BEGIN
#undef new
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

CLEAN_NEW_END

#include "GraphicsObject_Texture.h"

class GD_ImGui
{
public:

	static void Initialize(GLFWwindow* window, int windowWidth, int windowHeight);
	static void Terminate();
	static void SetObjectToModify(GraphicsObject_Texture* gObject);
	static void SetTextures(Texture* regular, Texture* custom);
	static void Update();
	static void Draw();

	void mainWindow();
private:
	static GD_ImGui& privGetInstance();

	GD_ImGui() = default;
	~GD_ImGui() = default;

	GD_ImGui(const GD_ImGui&) = delete;
	GD_ImGui(GD_ImGui&&) = delete;
	GD_ImGui& operator=(const GD_ImGui&) = delete;
	GD_ImGui& operator=(GD_ImGui&&) = delete;

private:
	GLFWwindow* window;
	GraphicsObject_Texture* gObject;
	Texture* singleTexture;
	Texture* mipmapTexture;
	int textureIndex;

};

#endif // !GD_IM_GUI_H
