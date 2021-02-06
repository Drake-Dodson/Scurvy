/*
This code uses vectors to determine what data type the user wants to use. The user can put in whatever data type they want and 
the count they want and this class will find those data types so the vertex array can use them properly.

code written by ChernoProject
*/

#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <vector>
#include "Renderer.h"


struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	//! Changes the size of the data type depending on what data type is entered
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	//! Pre: Takes in the count value 
	//! Post: Asserts if a value is pushed that doesn't exist
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}
	
	//! Pre: Takes in the count value 
	//! Post: Pushes the vector type to float and set's strid to count * the size of float
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	//! Pre: Takes in the count value 
	//! Post: Pushes the vector type to unsigned int and set's strid to count * the size of unsigned int
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	//! Pre: Takes in the count value 
	//! Post: Pushes the vector type to unsigned char and set's strid to count * the size of unsigned char
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	//! Post: Returns the value of elements
	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }

	//! Post: Returns the value of stride
	inline unsigned int GetStride() const { return m_Stride;  }

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
};

#endif //! VERTEXBUFFER_H
