/*====================
	MADE BY REINGD
====================*/
#include "GD_ImGui.h"
#include "GraphicsObject_Texture.h"


void GD_ImGui::Initialize(GLFWwindow* window, int windowWidth, int windowHeight)
{
	assert(window);
	const char* glsl_version = "#version 130";

	GD_ImGui& instance = GD_ImGui::privGetInstance();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.WantCaptureKeyboard = true;
	io.WantCaptureMouse = true;

	ImGui::StyleColorsDark();
	io.Fonts->AddFontFromFileTTF("extra_font/DroidSans.ttf", 24);
	io.FontGlobalScale = 1.0;

	instance.window = window;

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(instance.window, true); //callbacks are already implemented, installcallbacks would keep track of the originals
	ImGui_ImplOpenGL3_Init(glsl_version);


}

void GD_ImGui::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GD_ImGui::SetObjectToModify(GraphicsObject_Texture* gObject)
{
	GD_ImGui& instance = GD_ImGui::privGetInstance();
	instance.gObject = gObject;
}

void GD_ImGui::SetTextures(Texture* regular, Texture* custom)
{
	GD_ImGui& instance = GD_ImGui::privGetInstance();

	instance.singleTexture = regular;
	instance.mipmapTexture = custom;
}

void GD_ImGui::Update()
{
	GD_ImGui& instance = GD_ImGui::privGetInstance();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	instance.mainWindow();

	//send to buffer
	ImGui::Render();

}

void GD_ImGui::Draw()
{
	GD_ImGui& instance = GD_ImGui::privGetInstance();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void GD_ImGui::mainWindow()
{
	ImGuiWindowFlags 	windowFlags = ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoNavFocus;

	ImGui::Begin("Main Window", 0, windowFlags);
	{
		ImGui::Text("Select Texture:");
		const char* renderTextures[] = { "Regular Mipmap", "Custom Mipmap"};
		static int selectedTexture = 0;

		ImGui::SetNextItemWidth(250.0f);
		ImGui::ListBox("##list", &selectedTexture, renderTextures, IM_ARRAYSIZE(renderTextures));
		if (textureIndex != selectedTexture)
		{
			textureIndex = selectedTexture;

			auto texture = selectedTexture == 0 ? singleTexture : mipmapTexture;

			this->gObject->SetTexture(texture);
		}
	}
	ImGui::End();
}

GD_ImGui& GD_ImGui::privGetInstance()
{
	static GD_ImGui instance;
	return instance;
}
