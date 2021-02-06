/*
This class is used to create a shader from a given .shader file. The structure reads all of the data
from this file and uses it to build a shader that the program can use.

Code written by the ChernoProject
*/

#include "Shader.h"

#include <fstream>
#include <iostream>
#include <string> 
#include <sstream>

#include "Renderer.h"

//! Pre:  Needs a filepath
//! Post: Creates a shader from the code in the shader 
Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);		//! Runs the program to get the string streams
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);	//! Sets the renderer ID
}

//! Post: Deletes the shader
Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}
//! Pre:  Needs a filepath string
//! Post: Returns a stream with the fragment shader data
ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	//! Reads from the given filepath
	std::ifstream stream(filepath);

	//! a class enum created to determine whether it is reading from the vertex shader, fragment shader or neither
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))						//! Runs until there is no more lines in the file
	{
		if (line.find("#shader") != std::string::npos)			//! Looks for the line that says shader
		{
			if (line.find("vertex") != std::string::npos)		//! Decides if the line is the vertex of fragment shader
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";						//! Returns the string stream 
		}
	}

	return { ss[0].str(), ss[1].str() };						//! Returns Fragment shader and vertex shader
}

//! Pre:  Needs data from the fragment and vertex shader
//! Post: Creates the shader with the specifications
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();						
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);		//! Compiles Vertex Shader
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);	//! Compiles Fragment Shader

	glAttachShader(program, vs);	//! Attackes the shaders
	glAttachShader(program, fs);
	glLinkProgram(program);			//! Links the shaders together
	glValidateProgram(program);

	glDeleteShader(vs);				//! Deletes the shaders
	glDeleteShader(fs);

	return program;		
}

//! Pre:  Ran by CompileShader. Shaders need to be created
//! Post: Compiles the shaders and returns their ids
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);	//! Creates the shader that was specified
	const char* src = source.c_str();		//! turns source into a c string
	glShaderSource(id, 1, &src, nullptr);	//! Compiles the shader
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)					//! Test to see if the shader will work
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? " vertex" : " fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;	

}

//! Pre:  Shader needs to be intialized 
//! Post: Binds the shader
void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

//! Pre:  Shader needs to be intialized 
//! Post: Unbinds the shader
void Shader::Unbind() const
{
	GLCall(glUseProgram(0))
}

//! Pre: Needs a name and value
//! Post: Sets a uniform that is composed of 1 int
void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

//! Pre: Needs a name and value
//! Post: Sets a uniform that is composed of 1 float
void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

//! Pre: Needs a name and values
//! Post: Sets a uniform that is composed of 4 floats
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

//! Pre: Needs a name and values
//! Post: Sets a uniform that is composed of Matrix of 4 floats
void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]))
}

//! Pre: Needs a uniform name
//! Post: Returns the uniforms location value
int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}