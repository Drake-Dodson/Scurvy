/*
Renders all of the game files taking the IndexBuffer, Vertex Array and Shaders
binds them all and then draws them.

Code written by the ChernoProject
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

//! Used for debugging purposes. Breaks the program and outputs the line that there was an error
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

//! Post: Clears the errors
void GLClearError();

// Post: Returns an error message if there is an error
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	
	//! Pre: Takes in a vertexarray an indexbuffer and a shader
	//! Post: Binds all of them and then draws the element
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

	// Post: Clears the renderer
	void Clear();


};

#endif //! RENDERER_H