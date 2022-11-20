#include "SimpleGame.h"
#include <windows.h>
#include <iostream>
#include <cassert>
#include "HexagonPlane.h"
#include "ShaderProgram.h"

#define UNUSED_VAR(x) (void(x))



const char* vertexShaderSource = "#version 450 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); \n"
"}\n"
";\n";

SimpleGame::SimpleGame()
	: _vsync(false), window(nullptr), windowWidth(800), windowHeight(800)
{
	
}

void SimpleGame::InitializeOpenGL()
{

	glfwInit(); //initialize glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //set the major version to 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); //set the minor version to 5
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


	//create window 800x800
	window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Demo", NULL, NULL);
	if (!window)
	{
		std::cout << "FAILED TO CREATE WINDOW\n";
		glfwTerminate();
		assert(false);

	}

	glfwMakeContextCurrent(window);//set this window to context

	//check for glad (this has to be executed after the window is set to context)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INITIALIZE GLAD\n";
		assert(false);
	}

	//set callback
	glfwSetFramebufferSizeCallback(window, glfw_onResize);
	glfwSetKeyCallback(window, glfw_onKey);
	glfwSetMouseButtonCallback(window, glfw_onMouseButton);
	glfwSetCursorPosCallback(window, glfw_onMouseMove);
	glfwSetScrollCallback(window, glfw_onMouseWheel);

	//set the debug callback if debug
#ifdef _DEBUG
	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback((GLDEBUGPROC) debug_callback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

#endif // _DEBUG

	setVSYNC(true);

	//setting the states for drawing (this is an initial set but each model should handle this)
	//winding and face culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	//depth test and operation
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
}

void SimpleGame::TerminateOpenGL()
{

	glfwTerminate();
}

void SimpleGame::run()
{

	//shader program
	ShaderProgram shaderProgram(vertexShaderSource, fragmentShaderSource);
	//this already sets the vbo 
	HexagonPlane model(shaderProgram);

	while (!glfwWindowShouldClose(window))
	{
		clearBuffer();
		model.draw();


		glfwSwapBuffers(window); //do context switching
		glfwPollEvents();

		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

	}

}

void SimpleGame::glfw_onResize(GLFWwindow* window, int width, int height)
{	
	//this handles resizing
	glViewport(0, 0, width, height);

}

void SimpleGame::glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	UNUSED_VAR(mods);
	UNUSED_VAR(scancode);
	UNUSED_VAR(action);
	UNUSED_VAR(key);
	UNUSED_VAR(action);
	UNUSED_VAR(window);

}

void SimpleGame::glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	UNUSED_VAR(mods);
	UNUSED_VAR(window);
	UNUSED_VAR(action);
	UNUSED_VAR(action);

}

void SimpleGame::glfw_onMouseMove(GLFWwindow* window, double x, double y)
{
	UNUSED_VAR(x);
	UNUSED_VAR(y);
	UNUSED_VAR(window);

}

void SimpleGame::glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{
	UNUSED_VAR(xoffset);
	UNUSED_VAR(yoffset);
	UNUSED_VAR(window);

}

void SimpleGame::setVSYNC(bool enable)
{
	_vsync = enable ? 1u : 0u;
	glfwSwapInterval((int)_vsync); //wait for vsync
}

void SimpleGame::clearBuffer()
{
	const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, windowWidth, windowHeight);
	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);

}

void APIENTRY SimpleGame::debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	GLvoid* userParam)
{
	reinterpret_cast<SimpleGame*>(userParam)->onDebugMessage(source, type, id, severity, length, message);
}

void SimpleGame::onDebugMessage(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
#ifdef _WIN32
	OutputDebugStringA(message);
	OutputDebugStringA("\n");

	DebugBreak();
#endif /* _WIN32 */
}

