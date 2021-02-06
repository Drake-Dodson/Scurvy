/*
Creates the Vertex Array taking data from the Vertex Buffer Layout.

Code written by The ChernoProject
*/

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
public:

	//! Post: Generates the vertex array
	VertexArray();
	
	//! Post: Deletes the vertex array
	~VertexArray();

	//! Pre:  Takes in a VertexBuffer and a Vertex buffer layout
	//! Post: Creates a Vertex Array with the given layout and buffer
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	//! Pre: Vertex Array was constructed
	//! Post: Binds the VertexArray
	void Bind() const;

	//! Pre: Vertex Array was constructed
	//! Post: Unbinds the Vertex Array
	void Unbind() const;

private:

	unsigned int m_RendererID;	// Renderer ID

};



#endif //! VERTEXARRAY_H
