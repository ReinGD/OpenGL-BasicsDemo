#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

class ShaderObject
{
public:
	ShaderObject(const char* vertexShader, const char* fragmentShader);
	~ShaderObject();

	unsigned int getProgram();
private:
	unsigned int _vertexShader;
	unsigned int _fragmentShader;
	unsigned int shaderProgram;
};

#endif // !SHADER_OBJECT_H
