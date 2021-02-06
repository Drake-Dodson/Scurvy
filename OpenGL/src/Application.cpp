/***********************************************************************************************\

		  _________
		 /   _____/ ____  __ ____________  _____.__.
		 \_____  \_/ ___\|  |  \_  __ \  \/ <   |  |
		 /        \  \___|  |  /|  | \/\   / \___  |
		/_______  /\___  >____/ |__|    \_/  / ____|
				\/     \/  Semester Project  \/ 

	Drake Dodson
	CIS-153-FD01 Computer programing: Data Structures
	May 8th, 2019



	This software uses OpenGL to renderer and play a BattleShip like game. The program uses
	12 headfiles and classes to make the code work. The contained in each class there is 
	documentation of what each does however, an brief outline of what each class does is 
	provided below:

	-src
		-game
			*BattleShip:		Runs the functions of the basic game
			*Board:				Framework for creatint bounded board and can generate points in 
								the board
			*Ships:				Framework for creating ships and binds them in a linked list
		
		*Create:				Draws the objects of the game to the screen
		*IndexBuffer:			Creates index buffers
		*Renderer:				Draws the objects
		*Shader:				Reads shader data
		*Texture:				Creates textures from pngs
		*VertexArray:			Binds buffer data and layout into a Vertex Array
		*VertexBuffer:			Generates buffer data
		*VertexBufferLayout:	Creates layout for vertex buffer.
	

	This fie, Application.cpp, runs the program. It contains multiple functions that handle 
	inputs from the users and updates the game data. Many of the functions have an iterator 
	that makes sure the input is not held in for too long and keeps the user from activating 
	something they may not have been ready to activate. 

	The program works by first having the user build their board by placing ships in which ever 
	location they would like to choose. Their are multiple checks within the game that prevent 
	the user from placing their ship in locations that are not valid. The user uses the WASD
	keys to move the ships, Enter to confirm it's location and Q to rotate the ship. After the
	build phase the user goes into the attack phase and has to find the location of the 
	opposing players ships. Again using WASD to control the inputs and Enter to confirm the 
	firing location. Once the player has destroyed all of the opponents ships they win. However,
	if the oppenent destroyes all of their ships they lose. 


	**Documentation key**

		//    :	Usually means it was a piece of code used for debugging that was commented out 
		//!   :	A description of the code
		/***  :	A description of a block of code or multipe functions


\***********************************************************************************************/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <string> 
#include <sstream>
#include <time.h>

#include "game/BattleShip.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Create.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//! All of ImGui's code is commented out because I only used it for debugging

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"

//! Lever Type was going to be used more to make better buttons but was ultimately only used once and not to its full potential
//!		May still use again in the future.
enum Lever{IDLE, ON, OFF};

//! Funcion prototypes. Most of the values are passed by reference so they can be updated multiple times within the
//!	render loop.
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void DecButton(unsigned int& count, unsigned int& iterate, bool& completed, int key, GLFWwindow* window);
void IncButton(unsigned int& count, unsigned int& iterate, bool& completed, int key, GLFWwindow* window);
void Switch(Lever& r, bool& completed, bool& output, unsigned int& iterator, GLFWwindow* window);
void Rotate(unsigned int x, unsigned int y, unsigned int& iterator, Lever& r, bool& completed, bool& Horizantal, HorVer& placement, std::string name, GLFWwindow* window, BattleShip& player);
void MoveX(unsigned int& x, unsigned int& iterator, bool& completed, HorVer placement, GLFWwindow* window, std::string name, BattleShip& player);
void MoveY(unsigned int& y, unsigned int& iterator, bool& completed, HorVer placement, GLFWwindow* window, std::string name, BattleShip& player);
void MoveSX(unsigned int& x, unsigned int& iterator, bool& completed, HorVer placement, GLFWwindow* window, std::string name, BattleShip& player);
void MoveSY(unsigned int& y, unsigned int& iterator, bool& completed, HorVer placement, GLFWwindow* window, std::string name, BattleShip& player);

//! Width of the window
const unsigned int WIN_WIDTH = 640;
const unsigned int WIN_HEIGHT = 640;


int main(void)
{
	srand(time(NULL));
	//*** Version Stuff ***
	const char* glsl_version = "#version 330";

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Sets the Version to 3 */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Scurvy", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	/* Outputs current version */
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		//ImGui::CreateContext();
		//ImGui_ImplGlfw_InitForOpenGL(window, true);
		//ImGui::StyleColorsDark();
		//ImGui_ImplOpenGL3_Init(glsl_version);

		unsigned int x = 8;					//! X and Y location. Pre set to 4, 4 to account for boarder
		unsigned int y = 8;

		unsigned int bx = 0;				//! Board x and y. Changes based on the camera location
		unsigned int by = 0;

		unsigned int count = 0;				//! count variable. Used to make the user wait before inputting again

		BattleShip P1;						//! Creates an instance of battleship for player one and two
		BattleShip P2;	

		P2.RandomizeShipPlacements();		//! Randomizes A.I. Ship placement
		
		//P1.RandomizeShipPlacements();

		Create Draw;						//! Intializes the create class
		HorVer placement = HORZ;			//! Intializes the placement
		Lever rotate = ON;					//! Lever set to on
		
		bool moveboard = false;				//! Set to false to set the board at the left
		bool completed1 = true;				//! Completed is set to true because nothing is activated yet
		bool completed2 = true;
		bool Horizantal = true;				//! Horizantal bool value set to true
	
		bool build = true;					//! Starts with build phase so it is set to true				
		bool p1attack = false;				//! Set to false until after build phase
		bool p2attack = false;				//! Set to false until after player one attacks
		
		bool movey = true;					//! movex and movey bools are set to true. Controls whether or not an interator is ran
		bool movex = true;
		bool wait = false;					//! Wait set to false.

		std::string ShipName = "Carrier";	//! Sets the first ship to Carrier
		unsigned int iterator = 0;			//! General use iterator.
		unsigned int iteratorx = 0;			//! Iterator that slows the x and y movement down
		unsigned int iteratory = 0;
		/* Loop until the user closes the window */

		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			processInput(window);

			//ImGui_ImplOpenGL3_NewFrame();
			//ImGui_ImplGlfw_NewFrame();
			//ImGui::NewFrame();

			Draw.Initialize();
			Draw.Board(bx, by, P1, P2);

			/*** Moves board left if move baord is true and right if move board is false ***/
			
			if (completed1 == true)	//! Does not allow the user to press the button again until the action or cool down is done		
			{
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)			//! If the button is pressed it changes the bool moveboard to the opposite
				{															//!		of what it is and sets completed1 to false.
					if (moveboard == true)
					{
						moveboard = false;
						completed1 = false;
					}
					else
					{
						moveboard = true;
						completed1 = false;
					}
				}
			}

			if (moveboard == true)											//! If the board is set to true it moves the board up 16 spaces if it is false it moves it down 
			{
				if (bx < 16)
					bx++;
				else
					completed1 = true;
			}
			if (moveboard == false)
			{
				if (bx > 0)
					bx--;
				else
					completed1 = true;
			}


			/*** Build Phase ***/
			if (build == true)
			{
				Draw.Ship(ShipName, x, y, placement, bx, by);												//! Draws the Ship to be placed
				Rotate(x, y, iterator, rotate, completed2, Horizantal, placement, ShipName, window, P1);	//! Rotate function to allow the ship to rotate ships
				MoveSX(x, iteratorx, movex, placement, window, ShipName, P1);								//! Moves ship X location and moves ship Y location
				MoveSY(y, iteratory, movey, placement, window, ShipName, P1);
				
				if (wait == true)	//! Wait counter (Basically a cool down)
				{
					count++;
				}

				if (count > 20)		//! Resets cool down and set wait = false.
				{
					count = 0;
					wait = false;
				}

				if (wait == false)
				{
					if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)	//! After cool down the user can input
					{
						if (P1.PlaceShip(x - 3, y - 3, placement, ShipName) == true)	//! Places Ship and checks to see if the ship cna be placed
						{
							wait = true; //! Starts the cool down again and resets x and y to 4, 4 
							x = 4;		
							y = 4;
							ShipName = P1.GetNextShipName();				//! Goes to the next to the ShipName.
							if (P1.AllShipsSet() == false)					//! Checks to see if all the ships are set
							{
								ShipName = P1.GetNextShipName();			//! Runs through all ships that aren't set
								while (P1.IsSet(ShipName) == true)
								{
									ShipName = P1.GetNextShipName();
								}
							}
							else
							{
								build = false;								//! Sets equal to false and sets p1attack to true and resets x and y
								p1attack = true;
								p2attack = true;
								x = 8;
								y = 8;
							}
						}
					}
				}
			}


			//*** Win Lose check ***
			if (build == false)
			{
				if (P2.Lose() == true)
				{
					Draw.Win();
					p1attack = false;
					p1attack = false;
				}
				if (P1.Lose() == true)
				{
					Draw.Lose();
					p1attack = false;
					p1attack = false;
				}
			}


			/***** Player 1 Attack Phase ****/
			if (completed1 == true)
			{
				if (p1attack == true)
				{
					Draw.Target(x + 16, y, bx, by);		//! Draws Target. 
					
					//! X and Y movement functions.
					MoveX(x, iteratorx, movex, placement, window, ShipName, P1);
					MoveY(y, iteratory, movey, placement, window, ShipName, P1);

					if (wait == true)					//! Cooldown iterator
					{
						count++;
					}

					if (count > 20)						//! Moves board and allows user to input after cooldown
					{
						count = 0;
						wait = false;
						moveboard = true;
					}

					if (wait == false)
					{
						if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
						{
							if (P2.IsHit(x - 3, y - 3) != true)		//! Checks to make sure the location was not already hit
							{
								P2.AttackShip(x - 3, y - 3);		//! Attacks the ship and sets wait to true and flips p1 and p2 attacks
								p1attack = false;					
								p2attack = true;
								wait = true;
								x = 8;								//! Sets x and y to their default locations
								y = 8;
							}
						}
					}
				}
			}
			

			/***** Player 2 Attack Phase *****/
			//! -Add AI Maybe?
			if (p2attack == true)
			{
				Draw.Target(x + 3, y + 3, bx, by);	//! Draws the target		
				
				if (wait == true)					//! Cooldown
				{
					count++;
				}

				if (count > 20)						//! Same as before
				{
					count = 0;
					wait = false;
					moveboard = false;
				}

				if (wait == false)
				{
					//! Iterators 10 times for each new random location. This prevents the random numbers from generating too fast
					//!	and slows the "animation" down. 
					if (iterator < 10)
					{
						iterator++;
					}
					else
					{
						//! The random locations are meant to give the cpu a "Realistic" idea of the cpu "Choosing" a spot to hit
						iterator = 0;
						x = rand() % 10 + 1;
						y = rand() % 10 + 1;
					
						//! I feel like I use iterators too much...but here's another one that basically means only two randomized animation points
						count++; 
						if (count > 2)
						{
							while (P1.IsHit(x, y) == true)		//! Runs until a valid point is found (Maybe fix and make faster)
							{
								x = rand() % 10 + 1;
								y = rand() % 10 + 1;
							}

							//! If a valid point is found the cpu attacks the ship and everything flipped back to player1 
							P1.AttackShip(x, y);
							wait = true;
							p1attack = true;
							p2attack = false;
							x = 8;
							y = 8;
						}
					}
				}
			}

			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//ImGui::Render();
			//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	
	}
	// Cleanup
	
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

//! Pre: Passes the window 
//! Post: Closes window if the Escape button is pressed
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//! Pre: Passes the window and the size of the window
//! Post: Changes the size of the window if the user resizes it
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, width);
}

//! Pre: Takes in an x and a y and a few bool values
//! Post: Changes the placement of the ship if the ship is able to be rotated
void Rotate(unsigned int x, unsigned int y, unsigned int& iterator, Lever& r, bool& completed, bool& Horizantal, HorVer& placement, std::string name, GLFWwindow* window, BattleShip& player)
{
	if (placement == HORZ)
	{
		if (y + player.GetShipLength(name) <= 14)					//! Checks to see if the value can fit in the bounds
		{
			Switch(r, completed, Horizantal, iterator, window);
			if (Horizantal == true)
				placement = HORZ;									//! Changes the value of placement 
			else
				placement = VERT;
		}

	}
	else
	{
		if (x + player.GetShipLength(name) <= 14)
		{
			Switch(r, completed, Horizantal, iterator, window);
			if (Horizantal == true)
				placement = HORZ;
			else
				placement = VERT;
		}

	}
}

//! Pre: Takes in a bool an iterator and a lever
//! Post: Runs after a cooldown then changes the output bool value to true or false
void Switch(Lever& r, bool& completed, bool& output, unsigned int& iterator, GLFWwindow* window)
{
	if (completed == true)
	{
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			if (r == ON)		//! Switches the input to on or off
			{
				r = OFF;
				completed = false;
			}
			else
			{
				r = ON;
				completed = false;
			}
		}
	}
	if (completed == false)			//! Runs this with a cooldown
	{
		if (r == ON)
		{
			if (iterator < 10)
				iterator = iterator + 1;
			else
			{
				output = true;		//! Changes the output 
				completed = true;	//! The wait time is over so the user can press Q again
				iterator = 0;		//! Resets the iterate
			}
		}
		else
		{
			if (iterator < 10)
				iterator = iterator + 1;
			else
			{
				output = false;
				completed = true;
				iterator = 0;
			}
		}
	}

}

//Pre:  X and Y need to start in the bounds. Needs an iterator placement ship name and x and y 
//Post: Determines whether or not the ship X can be incremented or not. 
void MoveSX(unsigned int& x, unsigned int& iterator, bool& completed, HorVer placement, GLFWwindow* window, std::string name, BattleShip& player)
{
	if (placement == HORZ)											//! If the placement is Horizantal it checks the extra bounds that the ship adds
	{
		if (x + player.GetShipLength(name) < 14)					//! Check to see if the ship can fit within the bounds
		{
			IncButton(x, iterator, completed, GLFW_KEY_D, window);	//! If it cannot fit in the bounds it will not increment further
		}
		DecButton(x, iterator, completed, GLFW_KEY_A, window);
	}
	else
	{
		IncButton(x, iterator, completed, GLFW_KEY_D, window);
		DecButton(x, iterator, completed, GLFW_KEY_A, window);
	}
}

//Pre:  X and Y need to start in the bounds. Needs an iterator placement ship name and x and y 
//Post: Determines whether or not the ship Y can be incremented or not. Changes Y value.
void MoveSY(unsigned int& y, unsigned int& iterator, bool& completed, HorVer placement, GLFWwindow* window, std::string name, BattleShip& player)
{
	if (placement == VERT)												//! If the placement is Vertical it checks the extra bounds that the ship adds
	{
		if (y + player.GetShipLength(name) < 14)						//! Check to see if the ship can fit within the bounds
		{
			IncButton(y, iterator, completed, GLFW_KEY_W, window);		//! If it cannot fit in the bounds it will not increment further
		}
		DecButton(y, iterator, completed, GLFW_KEY_S, window);
	}
	else
	{
		IncButton(y, iterator, completed, GLFW_KEY_W, window);
		DecButton(y, iterator, completed, GLFW_KEY_S, window);
	}
}

//! Pre:  Needs a y value, an iterator, a bool, ship placement, string name and a player.
//! Post: Increments x or Decrements it if it can within the bounds. 
void MoveX(unsigned int& x, unsigned int& iterator, bool& completed, HorVer placement, GLFWwindow* window, std::string name, BattleShip& player)
{
	if (placement == HORZ)											//! If the placement is Horizantal it checks the extra bounds that the ship adds
	{
		if (x < 14)													//! Check to see if the ship can fit within the bounds
		{
			IncButton(x, iterator, completed, GLFW_KEY_D, window);	//! If it cannot fit in the bounds it will not increment further
		}
		DecButton(x, iterator, completed, GLFW_KEY_A, window);
	}
	else
	{
		IncButton(x, iterator, completed, GLFW_KEY_D, window);
		DecButton(x, iterator, completed, GLFW_KEY_A, window);
	}
}

//! Pre:  Needs a y value, an iterator, a bool, ship placement, string name and a player.
//! Post: Increments y or Decrements it if it can within the bounds. 
void MoveY(unsigned int& y, unsigned int& iterator, bool& completed, HorVer placement, GLFWwindow* window, std::string name, BattleShip& player)
{
	if (placement == VERT)												//! If the placement is Horizantal it checks the extra bounds that the ship adds
	{
		if (y < 14)														//! Check to see if the ship can fit within the bounds
		{
			IncButton(y, iterator, completed, GLFW_KEY_W, window);		//! If it cannot fit in the bounds it will not increment further
		}
		DecButton(y, iterator, completed, GLFW_KEY_S, window);
	}
	else
	{
		IncButton(y, iterator, completed, GLFW_KEY_W, window);
		DecButton(y, iterator, completed, GLFW_KEY_S, window);
	}
}

//! Pre:  Needs a few values such as a count, iterator, bool, and a key to be pressed.
//! Post: Decrements count after a cool down. 
void DecButton(unsigned int& count, unsigned int& iterate, bool& completed, int key, GLFWwindow* window)
{
	if (completed == true)								//! The user cannot press the button again unti the iterator is done
	{
		if (glfwGetKey(window, key) == GLFW_PRESS)		//! Sees if the button was pressed. If it is and the x value is within bounds it decrements it
		{
			if(count > 4)
				count--;
			completed = false;							

		}
	}
	if (iterate < 30)									//! Runs the iterator 30 times 
	{
		iterate = iterate + 1;
	}
	else
	{
		completed = true;
		iterate = 0;
	}
}

//! Pre:  Needs a few values such as a count, iterator, bool, and a key to be pressed.
//! Post: Decrements count after a cool down. 
void IncButton(unsigned int& count, unsigned int& iterate, bool& completed, int key, GLFWwindow* window)
{
	if (completed == true)
	{
		if (glfwGetKey(window, key) == GLFW_PRESS)
		{
			if(count < 13)
				count++;
			completed = false;
		}
	}
	if (iterate < 30)
	{
		iterate = iterate + 1;
	}
	else
	{
		completed = true;
		iterate = 0;
	}
}

