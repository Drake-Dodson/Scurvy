/*
Creates a vertex buffer. The user creates an array with the vertices of the buffer and then passes them to the class when creating
the vertex buffer. The user also has to specify the size. Usually the dimensions times the size of the data type.

Code written by the ChernoProject
*/

#include "VertexBuffer.h"

#include "Renderer.h"

//Pre: Requires a data type and a size of the data
//Post: Generates the buffer given the data
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

//Pre: VertexBuffer was constructed
//Post: Deletes Vertexbuffer
VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID))
}

//Pre: VertexBuffer was constructed
//Post: Binds the buffer
void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

//Pre: VertexBuffer was constructed
//Post: Unbinds the buffer
void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}