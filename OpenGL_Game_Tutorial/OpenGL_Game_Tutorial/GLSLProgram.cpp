#include "GLSLProgram.h"
#include "Errors.h"
#include <vector>
#include <iostream>
#include <fstream>



GLSLProgram::GLSLProgram() :_numAttribute(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) // Initialization list
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string & fragmentShaderFilepath)
{
	// create shader program
	//Get a program object.
	_programID = glCreateProgram();

	//create Vertex shader and get vertexShaderID
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
	{
		fatalProgramError("Vertex shader failed to be created!");
	}

	//create fragment shader and get fragmentID
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
	{
		fatalProgramError("Fragment shader failed to be created!");
	}


	//compile Shaders 
	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilepath, _fragmentShaderID);
}

void GLSLProgram::linkShaders()
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	
	

	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		std::printf("%s\n", &errorLog[0]);
		fatalProgramError("Shader failed to compile !");
	}

	//Always detach (ablösen) shaders after a successful link.

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);

}

// Add an attributo to our shader. Should be called between compiling and linking
void GLSLProgram::addAttribute(const std::string & attributeName)
{
	glBindAttribLocation(_programID, _numAttribute++, attributeName.c_str());
}

GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());

	if (location == GL_INVALID_INDEX)
	{
		fatalProgramError("Uniform " + uniformName + " not found in shader !");
	}
	return location;
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
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
	// crate an ifstream
	std::ifstream vertexFile(filePath, std::ifstream::in);;

	
	if (vertexFile.fail())
	{
		perror(filePath.c_str());
		fatalProgramError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line = "";

	//read every line of the textfile 
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
		fatalProgramError("Shader " + filePath + " failed to compile");

	}
}
