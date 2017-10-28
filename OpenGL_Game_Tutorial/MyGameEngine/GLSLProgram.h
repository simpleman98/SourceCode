#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>
namespace MyGameEngine
{

	// this class handles the compilation, linking and usage of a GLSL shader program.
	//Reference: http://www.opengl.org/wiki/ShaderCompilation

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);
		void linkShaders();
		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);
		void use();
		void unuse();
	private:
		void compileShader(const std::string& filePath, GLuint id);

		int _numAttribute;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

	};
}

