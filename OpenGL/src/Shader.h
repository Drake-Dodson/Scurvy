/*
This class is used to create a shader from a given .shader file. The structure reads all of the data 
from this file and uses it to build a shader that the program can use.

Code written by the ChernoProject
*/


#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

//! A struct that stores the Vertex shader and Fragment shader
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:

	//! Pre:  Needs a filepath
	//! Post: Creates a shader from the code written in Basic.shader
	Shader(const std::string& filepath);

	//! Post: Deletes the shader
	~Shader();

	//! Pre:  Shader needs to be intialized 
	//! Post: Binds the shader
	void Bind() const;

	//! Pre:  Shader needs to be intialized 
	//! Post: Unbinds the shader
	void Unbind() const;
	
	//! Pre: Needs a name and values
	//! Post: Sets a uniform that is composed of 1 float
	void SetUniform1f(const std::string& name, float value);
	
	//! Pre: Needs a name and values
	//! Post: Sets a uniform that is composed of 1 int
	void SetUniform1i(const std::string& name, int value);

	//! Pre: Needs a name and values
	//! Post: Sets the uniform of the shader to 4 floats
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	//! Pre: Needs a name and values
	//! Post: Sets a uniform that is composed of Matrix of 4 floats
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;	 
	
	//! Pre:  Needs a filepath string
	//! Post: Returns a stream with the fragment shader data
	ShaderProgramSource ParseShader(const std::string& filepath);
	
	//! Pre:  Ran by CompileShader. Shaders need to be created
	//! Post: Compiles the shaders and returns their ids
	unsigned int CompileShader(unsigned int type, const std::string& source);
	
	//! Pre:  Needs data from the fragment and vertex shader
	//! Post: Creates the shader with the specifications
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	
	//! Pre: Needs a uniform name
	//! Post: Returns the uniforms location value
	int GetUniformLocation(const std::string& name);
};

#endif //! SHADER_H
