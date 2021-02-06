/*
Creates the Vertex Array taking data from the Vertex Buffer Layout.

Code written by the ChernoProject
*/

#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

//! Post: Generates the vertex array
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

//! Post: Deletes the vertex array
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));;
}

//! Pre:  Requires a VertexBuffer and a VertexBufferLayout
//! Post: Creates a buffer 
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();													// Binds the Array
	vb.Bind();												// Binds the vertex buffer
	const auto& elements = layout.GetElements();			// Gets the layout of the buffer
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)		// Runs through for the element size
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);		//! Creates the offset size for the amount of elements
	}
}

//! Pre:  Vertex Array was constructed
//! Post: Binds the VertexArray
void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

//! Pre:  Vertex Array was constructed
//! Post: Unbinds the Vertex Array
void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}