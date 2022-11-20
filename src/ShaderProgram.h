#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexShader, const char* fragmentShader);
	~ShaderProgram();

	unsigned int getProgram();
private:
	unsigned int _vertexShader;
	unsigned int _fragmentShader;
	unsigned int shaderProgram;
};

#endif // !SHADER_PROGRAM_H
