/*
Creates an index buffer given the vertices and the data for the index buffer

Code written by the ChernoProject
*/

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	
	//! Pre: Needs the data and the amount of vertices in the data
	//! Post: Creates an index buffer
	IndexBuffer(const unsigned int* data, unsigned int count);	//Size means in byte, count means element count 
	
	//! Post: Deletes the buffer
	~IndexBuffer();

	//! Post: Binds the buffer
	void Bind() const;

	//! Post: Unbinds the buffer
	void Unbind() const;

	//! Pre: Returns the value of count
	inline unsigned int GetCount() const { return m_Count; };
};

#endif //! INDEXBUFFER_H