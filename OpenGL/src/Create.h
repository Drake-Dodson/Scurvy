/********************************************************************************

	Drake Dodson
	CIS-153-FD01 Computer programing: Data Structures
	May 8th, 2019

	This class uses everything that was built in order to make OpenGL work and uses
	the BattleShip code. This class creates multiple VertexArrays and textures and 
	binds them together to generate the game objects. 

	The class has multiple functions that draw new game objects such as the ship 
	objects that draws a ship either Horizantally or vertically. The biggest part of
	the class would have to be the board function which almost draws everything
	that the user sees such as the ships, hits/misses, and the background board

********************************************************************************/

#ifndef CREATE_H
#define CREATE_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "game/BattleShip.h"
#include <memory>

class Create
{
public:

	//! Post: Generates all of the data for the textures/objects and model view projection matrix
	Create();
	
	//! Post: Does absolutely nothing right now 
	~Create();

	//! Post: Initializes the drawing of objects
	void Initialize();
	
	//! Pre: Takes in a placement, location, and board location
	//! Post: Draws the carrier
	void Carrier(unsigned int x, unsigned y, HorVer placement, unsigned int bx, unsigned int by);
	
	//! Pre: Takes in a placement, location, and board location
	//! Post: Draws the battleship
	void Battleship(unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by);
	
	//! Pre: Takes in a placement, location, and board location
	//! Post: Draws the cruiser
	void Cruiser(unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by);
	
	//! Pre: Takes in a placement, location, and board location
	//! Post: Draws the submarine
	void Submarine(unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by);
	
	//! Pre: Takes in a placement, location, and board location
	//! Post: Draws the destroyer
	void Destroyer(unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by);

	//! Pre: Takes in a ship name a placement, location, and board location
	//! Post: Draws the ship that was specified 
	void Ship(std::string name, unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by);

	//! Pre:  Needs the board x, y and the location x and y
	//! Post: Draws the target object
	void Target(unsigned int x, unsigned int y, unsigned int bx, unsigned int by);
	
	//! Pre:  Needs the board x, y and the location x and y
	//! Post: Draws the miss object
	void Miss(unsigned int x, unsigned int y, unsigned int bx, unsigned int by);
	
	//! Pre:  Needs the board x, y and the location x and y
	//! Post: Draws the hit object
	void Hit(unsigned int x, unsigned int y, unsigned int bx, unsigned int by);
	
	//! Pre:  Needs the board x, y and the location x and y
	//! Post: Draws the background
	void Background(int bx, int by);
	
	//! Post: Draws the win message
	void Win();
	
	//! Post: Draws the lose message
	void Lose();
	
	//! Pre:  
	//! Post:
	void Board(unsigned int bx, unsigned int by, BattleShip& player1, BattleShip& player2);

private:

	Renderer renderer;
	
	/***Creates all of the Buffers and Vertex arrays***/
	std::unique_ptr<VertexArray>  BoardVA;
	std::unique_ptr<VertexBuffer> BoardBuffer;

	std::unique_ptr<VertexArray>  TileVA;
	std::unique_ptr<VertexBuffer> TileBuffer;

	std::unique_ptr<VertexArray>  CarrierVVA;
	std::unique_ptr<VertexBuffer> CarrierVBuffer;

	std::unique_ptr<VertexArray>  CarrierHVA;
	std::unique_ptr<VertexBuffer> CarrierHBuffer;

	std::unique_ptr<VertexArray>  BattleshipVVA;
	std::unique_ptr<VertexBuffer> BattleshipVBuffer;
	std::unique_ptr<VertexArray>  BattleshipHVA;
	std::unique_ptr<VertexBuffer> BattleshipHBuffer;

	std::unique_ptr<VertexArray>  CruisSubVVA;
	std::unique_ptr<VertexBuffer> CruisSubVBuffer;
	std::unique_ptr<VertexArray>  CruisSubHVA;
	std::unique_ptr<VertexBuffer> CruisSubHBuffer;

	std::unique_ptr<VertexArray>  DestroyerVVA;
	std::unique_ptr<VertexBuffer> DestroyerVBuffer;
	std::unique_ptr<VertexArray>  DestroyerHVA;
	std::unique_ptr<VertexBuffer> DestroyerHBuffer;

	std::unique_ptr<VertexArray>  WinVA;
	std::unique_ptr<VertexBuffer> WinBuffer;

	std::unique_ptr<IndexBuffer> ib;
	std::unique_ptr<Shader> shader;

	/***Unique Pointers for all of the textures ***/
	std::unique_ptr<Texture> Target_Tex;
	std::unique_ptr<Texture> Miss_Tex;
	std::unique_ptr<Texture> Hit_Tex;
	std::unique_ptr<Texture> Board_Tex;
	std::unique_ptr<Texture> CarrierV_Tex;
	std::unique_ptr<Texture> CarrierH_Tex;
	std::unique_ptr<Texture> BattleshipV_Tex;
	std::unique_ptr<Texture> BattleshipH_Tex;
	std::unique_ptr<Texture> CruiserV_Tex;
	std::unique_ptr<Texture> CruiserH_Tex;
	std::unique_ptr<Texture> SubV_Tex;
	std::unique_ptr<Texture> SubH_Tex;
	std::unique_ptr<Texture> DestroyerV_Tex;
	std::unique_ptr<Texture> DestroyerH_Tex;
	std::unique_ptr<Texture> Win_Tex;
	std::unique_ptr<Texture> Lose_Tex;

	//Projection matrix and View matrix
	glm::mat4 proj;
	glm::mat4 view;
};
#endif