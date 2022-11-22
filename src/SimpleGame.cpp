#include "SimpleGame.h"
#include <windows.h>
#include <cassert>
#include "HexagonPlane.h"
#include "ShaderObject.h"
#include "GraphicsObject_Simple.h"
#include "GraphicsObject_Texture.h"
#include "FileHelper.h"
#include "Cube.h"

#define UNUSED_VAR(x) (void(x))


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
		GDWriter::write("FAILED TO CREATE WINDOW\n");
		glfwTerminate();
		assert(false);

	}

	glfwMakeContextCurrent(window);//set this window to context

	//check for glad (this has to be executed after the window is set to context)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		GDWriter::write("FAILED TO INITIALIZE GLAD\n");
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
	//need to eliminate double output TODO
	GD::File::Error error;
	std::string vertexShader = FileHelper::FileOpenS("positioned_texture.vs.glsl", GD::File::Mode::READ, &error);
	assert(error == GD::File::Error::SUCCESS);
	std::string fragmentShader = FileHelper::FileOpenS("positioned_texture.fs.glsl", GD::File::Mode::READ, &error);
	assert(error == GD::File::Error::SUCCESS);

	//shader program
	ShaderObject* shaderProgram = new ShaderObject(vertexShader.c_str(), fragmentShader.c_str());

	//this already sets the vbo 
	Cube* model = new Cube();

	//set up the texture
	Texture* texture = new Texture("wall.dds", Texture::Mode::Mipmapped);

	//Set up the Graphics Object;
	GraphicsObject_Texture* gObject = new GraphicsObject_Texture(model, texture, shaderProgram);


	/*
		Graphics Object - > Contains the behaviour to render the object
		Game Object - > Contains the model data(VAO,VBOS,EBO)
		Texture -> Contains the Texture id to be passed to the Graphics Object
		Shader -> Contains the vertex and fragment shader to be used
		Graphics Object points to a Game Object to get this data
	*/
	
	//the only reason the object changes color is because the mipmaps are of different color
	//they are being interpolated as the object gets farther away

	while (!glfwWindowShouldClose(window))
	{
		clearBuffer();

		gObject->Render();

		glfwSwapBuffers(window); //do context switching
		glfwPollEvents();

		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

	}

	delete gObject;
	delete texture;
	delete model;
	delete shaderProgram;

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

	GDWriter::write("---------------\n");
	GDWriter::write("Debug message ({0})", id);
	GDWriter::write(message);
	GDWriter::write("\n");

	std::string sourceString; 
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             sourceString = "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceString = "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceString = "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceString = "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     sourceString = "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           sourceString = "Source: Other"; break;
	}

	GDWriter::write(sourceString.c_str());
	GDWriter::write("\n");

	std::string typeString;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               typeString = "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeString = "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeString = "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         typeString = "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         typeString = "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              typeString = "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          typeString = "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           typeString = "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               typeString = "Type: Other"; break;
	} 

	GDWriter::write(typeString.c_str());
	GDWriter::write("\n");

	std::string severityString;


	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         severityString = "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       severityString = "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          severityString = "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: severityString = "Severity: notification"; break;
	} 

	GDWriter::write(severityString.c_str());
	GDWriter::write("\n");

	GDWriter::write(message);
	GDWriter::write("\n");

	DebugBreak();
}

