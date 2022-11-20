#include "SimpleGame.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

SimpleGame::SimpleGame()
{
	this->allVertex.reserve(18);

	//each triangle will have a different z to show mipmaps
	//each triangle is separate on purpose to show mipmap representation with z depth
	
	this->allVertex.emplace_back( 0.00f,  0.00f, 0.00f);
	this->allVertex.emplace_back(-0.25f, -0.50f, 0.00f);
	this->allVertex.emplace_back( 0.25f, -0.50f, 0.00f);

	this->allVertex.emplace_back( 0.00f,  0.00f, 0.25f);
	this->allVertex.emplace_back( 0.25f,  0.50f, 0.25f);
	this->allVertex.emplace_back(-0.25f,  0.50f, 0.25f);

	this->allVertex.emplace_back( 0.00f,  0.00f, 0.50f);
	this->allVertex.emplace_back(-0.50f,  0.00f, 0.50f);
	this->allVertex.emplace_back(-0.25f, -0.50f, 0.50f);
	
	this->allVertex.emplace_back( 0.00f,  0.00f, 0.75f);
	this->allVertex.emplace_back( 0.25f, -0.50f, 0.75f);
	this->allVertex.emplace_back( 0.50f,  0.00f, 0.75f);
	
	this->allVertex.emplace_back( 0.00f,  0.00f, 1.00f);
	this->allVertex.emplace_back(-0.25f,  0.50f, 1.00f);
	this->allVertex.emplace_back(-0.50f,  0.00f, 1.00f);

	this->allVertex.emplace_back( 0.00f,  0.00f, 0.00f);
	this->allVertex.emplace_back( 0.50f,  0.00f, 0.00f);
	this->allVertex.emplace_back( 0.25f,  0.50f, 0.00f);

}

void SimpleGame::InitializeOpenGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INITIALIZE GLAD\n";
		assert(false);
	}

	glfwInit(); //initialize glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //set the major version to 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //set the minor version to 5
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window 800x800
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Demo", NULL, NULL);
	if (!window)
	{
		std::cout << "FAILED TO CREATE WINDOW\n";
		glfwTerminate();
		assert(false);

	}

	glfwMakeContextCurrent(window); //set this window to context
	glViewport(0, 0, 800, 800);


	//set resize callback
	glfwSetFramebufferSizeCallback(window, resizeBufferCallback);
}

void SimpleGame::TerminateOpenGL()
{
}

void SimpleGame::run()
{
}

void resizeBufferCallback(GLFWwindow* window, int width, int height)
{
	//this handles resizing
	glViewport(0, 0, width, height);
}

