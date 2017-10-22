#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>


class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);
	void linkShaders();
	void addAttribute(const std::string& attributeName);
	void use();
	void unuse();
private:
	void compileShader(const std::string& filePath, GLuint id);

	int _numAttribute;
	GLuint _programmID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;

};

