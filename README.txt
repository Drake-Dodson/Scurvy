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

	To view the code in action view this youtube video: https://www.youtube.com/watch?v=cuyT4iIPiks

	This software uses OpenGL to renderer and play a BattleShip like game. The program uses
	12 headerfiles and classes to make the code work. Contained in each class there is 
	documentation of what each does however, a brief outline of what each class does is 
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
	

	The main Application.cpp, runs the program. It contains multiple functions that handle 
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

	All textures in the game, except Sobble.png, were created by me using the program Aesprite. 


	**Documentation key**

		//    :	Usually means it was a piece of code used for debugging that was commented out 
		//!   :	A description of the code
		/***  :	A description of a block of code or multipe functions


\***********************************************************************************************/
