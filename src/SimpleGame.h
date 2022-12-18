/*====================
	MADE BY REINGD
====================*/
#include <vector>
#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class SimpleGame
{
public:


public:
	//big 6
	SimpleGame();
	~SimpleGame() = default;
	SimpleGame(const SimpleGame&) = delete;
	SimpleGame(SimpleGame&&) = delete;
	SimpleGame& operator= (const SimpleGame&) = delete;
	SimpleGame& operator= (SimpleGame&&) = delete;


	void InitializeOpenGL();
	void TerminateOpenGL();
	void run();


	static void glfw_onResize(GLFWwindow* window, int width, int height);
	static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods);
	static void glfw_onMouseMove(GLFWwindow* window, double x, double y);
	static void glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset);

	void setVSYNC(bool enable);
	void clearBuffer();

	void onDebugMessage(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message);


private:
	GLFWwindow* window;
	unsigned int _vsync;
	int windowWidth;
	int windowHeight;

	static void APIENTRY debug_callback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		GLvoid* userParam);

};

#endif // !SIMPLE_GAME_H
