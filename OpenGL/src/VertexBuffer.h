/*
Creates a vertex buffer. The user creates an array with the vertices of the buffer and then passes them to the class when creating
the vertex buffer. The user also has to specify the size. Usually the dimensions times the size of the data type.

Code written by the ChernoProject
*/

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	
	//Pre: Requires a data type and a size of the data
	//Post: Generates the buffer given the data
	VertexBuffer(const void* data, unsigned int size);
	

	//Pre: VertexBuffer was constructed
	//Post: Deletes Vertexbuffer
	~VertexBuffer();

	//Pre: VertexBuffer was constructed
	//Post: Binds the buffer
	void Bind() const;
	
	//Pre: VertexBuffer was constructed
	//Post: Uninds the buffer
	void Unbind() const;

};

#endif //! VERTEXBUFFER_H