#include "GLSLProgram.h"
#include "Errors.h"
#include <vector>
#include <iostream>
#include <fstream>




GLSLProgram::GLSLProgram() :_numAttribute(0), _programmID(0), _vertexShaderID(0), _fragmentShaderID(0) // Initialization list
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string & fragmentShaderFilepath)
{
	_programmID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
	{
		fatalProgramError("Vertex shader failed to be created!");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
	{
		fatalProgramError("Fragment shader failed to be created!");
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilepath, _fragmentShaderID);
}

void GLSLProgram::linkShaders()
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	

	//Attach our shaders to our program
	glAttachShader(_programmID, _vertexShaderID);
	glAttachShader(_programmID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programmID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programmID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programmID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programmID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programmID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		std::printf("%s\n", &errorLog[0]);
		fatalProgramError("Shader failed to compile !");
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programmID, _vertexShaderID);
	glDetachShader(_programmID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);

}

void GLSLProgram::addAttribute(const std::string & attributeName)
{
	glBindAttribLocation(_programmID, _numAttribute++, attributeName.c_str());
}

void GLSLProgram::use()
{
	glUseProgram(_programmID);
	for (int i = 0; i < _numAttribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttribute; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint id)
{
	
	std::ifstream vertexFile(filePath, std::ifstream::in);;

	
	if (vertexFile.fail())
	{
		perror(filePath.c_str());
		fatalProgramError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line = "";

	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);
		std::printf("%s\n", &errorLog[0]);
		fatalProgramError("Shader" + filePath + "failed to compile");

	}
}
