/*
Renders all of the game files taking the IndexBuffer, Vertex Array and Shaders
binds them all and then draws them.

Code written by the ChernoProject
*/

#include "Renderer.h"

#include <iostream>


//! Post: Clears the errors
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

// Post: Returns an error message if there is an error
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

// Post: Clears the renderer
void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

//! Pre: Takes in a vertexarray an indexbuffer and a shader
//! Post: Binds all of them and then draws the element
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();	// Binds the buffer to the VA 
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

