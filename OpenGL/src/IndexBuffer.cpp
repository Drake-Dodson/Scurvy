/*
Creates an index buffer given the vertices and the data for the index buffer

Code written by the ChernoProject
*/

#include "IndexBuffer.h"

#include "Renderer.h"

//! Pre: Needs the data and the amount of vertices in the data
//! Post: Creates an index buffer
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	//! Makes sure that the sizes of GLuint and unsigned int are the same
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	//! Creates a buffer of size count and passes the data into the buffer
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW)); // Unsigned int may not be four bytes
}

//! Post: Deletes the buffer
IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID))
}

//! Post: Binds the buffer
void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

//! Post: Unbinds the buffer
void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}