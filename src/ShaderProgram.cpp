#include "ShaderProgram.h"
#include <glad/glad.h>
#include <iostream>

ShaderProgram::ShaderProgram(const char* vertexShader, const char* fragmentShader)
	:_vertexShader(0), _fragmentShader(0), shaderProgram(0)
{
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(_vertexShader, 1, &vertexShader, NULL);
	glCompileShader(_vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(_vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(_fragmentShader, 1, &fragmentShader, NULL);
	glCompileShader(_fragmentShader);

	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(_fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, _vertexShader);
	glAttachShader(shaderProgram, _fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

}

ShaderProgram::~ShaderProgram()
{
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);

}

unsigned int ShaderProgram::getProgram()
{
	return shaderProgram;
}
