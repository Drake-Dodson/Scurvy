/*
This code generates the textures given the file path for the texture and binds them. The program is
set to nearest to give the textures a more blocky looking texture to give the game a pixelart asthetic

Code written by the ChernoProject
*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	
	//! Pre:  Needs the file path string 
	//! Post: Processes the information of the image
	Texture(const std::string& path);
	
	//! Post: Deletes the texture
	~Texture();

	//! Pre:  The function has been constructed
	//! Post: Binds the texture
	void Bind(unsigned int slot = 0) const;

	//! Pre:  The function has been constructed
	//! Post: Unbinds the texture
	void Unbind() const;

	//! Post: Returns the value of width
	inline int GetWidth() const { return m_Width; }

	//! Post: Returns the value of height
	inline int GetHeight() const { return m_Height; }

};

#endif //! TEXTURE_H