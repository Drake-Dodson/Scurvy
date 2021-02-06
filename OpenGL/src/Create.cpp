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

#include "Create.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


//! Post: Generates all of the data for the textures/objects and model view projection matrix
Create::Create()
{
	//! Vertex Buffer data
	float Tile[] = {
	 -8.0f,   -8.0f,	0.0f,   0.0f,  // 0
	  8.0f,   -8.0f,	1.0f,   0.0f,  // 1
	  8.0f,    8.0f,	1.0f,   1.0f,  // 2
	 -8.0f,    8.0f,    0.0f,   1.0f   // 3
	};

	float Board[] = {
		-256.0f,   -128.0f,	0.0f,   0.0f,  // 0
		 256.0f,   -128.0f,	1.0f,   0.0f,  // 1
		 256.0f,    128.0f,	1.0f,   1.0f,  // 2
		-256.0f,    128.0f,    0.0f,   1.0f   // 3
	};

	float CarrierV[] = {
		-8.0f,   -40.0f,	  0.0f,   0.0f,  // 0
		 8.0f,   -40.0f,	  1.0f,   0.0f,  // 1
		 8.0f,    40.0f,	  1.0f,   1.0f,  // 2
		-8.0f,    40.0f,      0.0f,   1.0f   // 3
	};

	float CarrierH[] = {
	 -40.0f,   -8.0f,	  0.0f,   0.0f, 
	  40.0f,   -8.0f,	  1.0f,   0.0f, 
	  40.0f,    8.0f,	  1.0f,   1.0f, 
	 -40.0f,    8.0f,    0.0f,   1.0f  
	};

	float BattleshipV[] = {
	  -8.0f,   -32.0f,	  0.0f,   0.0f, 
	   8.0f,   -32.0f,	  1.0f,   0.0f, 
	   8.0f,    32.0f,	  1.0f,   1.0f, 
	  -8.0f,    32.0f,      0.0f,   1.0f  
	};

	float BattleshipH[] = {
	  -32.0f,   -8.0f,	  0.0f,   0.0f, 
	   32.0f,   -8.0f,	  1.0f,   0.0f, 
	   32.0f,    8.0f,	  1.0f,   1.0f, 
	  -32.0f,    8.0f,    0.0f,   1.0f  
	};

	float CruisSubV[] = {
	  -8.0f,   -24.0f,	  0.0f,   0.0f, 
	   8.0f,   -24.0f,	  1.0f,   0.0f, 
	   8.0f,    24.0f,	  1.0f,   1.0f, 
	  -8.0f,    24.0f,    0.0f,   1.0f  
	};

	float CruisSubH[] = {
	  -24.0f,   -8.0f,	  0.0f,   0.0f, 
	   24.0f,   -8.0f,	  1.0f,   0.0f, 
	   24.0f,    8.0f,	  1.0f,   1.0f, 
	  -24.0f,    8.0f,    0.0f,   1.0f  
	};

	float DestroyerV[] = {
	   -8.0f,   -16.0f,	  0.0f,   0.0f, 
	    8.0f,   -16.0f,	  1.0f,   0.0f, 
	    8.0f,    16.0f,	  1.0f,   1.0f, 
	   -8.0f,    16.0f,   0.0f,   1.0f  
	};

	float DestroyerH[] = {
	  -16.0f,   -8.0f,	  0.0f,   0.0f, 
	   16.0f,   -8.0f,	  1.0f,   0.0f, 
	   16.0f,    8.0f,	  1.0f,   1.0f, 
	  -16.0f,    8.0f,    0.0f,   1.0f  
	};

	float Message[] = {
	-48.0f,   -16.0f,	  0.0f,   0.0f,
	 48.0f,   -16.0f,	  1.0f,   0.0f,
	 48.0f,    16.0f,	  1.0f,   1.0f,
	-48.0f,    16.0f,      0.0f,   1.0f
	};

	//! Index Buffer Vertices 
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	//! Blends the functions
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));

	shader = std::make_unique<Shader>("res/shaders/Basic.shader");
	
	//! Tile Vertex Array
	VertexArray va;
	TileVA = std::make_unique<VertexArray>();
	TileBuffer = std::make_unique<VertexBuffer>(Tile, 4 * 4 * sizeof(float)); // Four sets of four points of type float

	//! Board Vertex Array
	BoardVA = std::make_unique<VertexArray>();
	BoardBuffer = std::make_unique<VertexBuffer>(Board, 4 * 4 * sizeof(float)); // Four sets of four points of type float

	//! Carrier Vertex Array's
	CarrierVVA = std::make_unique<VertexArray>();
	CarrierVBuffer = std::make_unique<VertexBuffer>(CarrierV, 4 * 4 * sizeof(float));

	CarrierHVA = std::make_unique<VertexArray>();
	CarrierHBuffer = std::make_unique<VertexBuffer>(CarrierH, 4 * 4 * sizeof(float));

	//! BattleShip Vertex Array's
	BattleshipVVA = std::make_unique<VertexArray>();
	BattleshipVBuffer = std::make_unique<VertexBuffer>(BattleshipV, 4 * 4 * sizeof(float));

	BattleshipHVA = std::make_unique<VertexArray>();
	BattleshipHBuffer = std::make_unique<VertexBuffer>(BattleshipH, 4 * 4 * sizeof(float));

	//! Cruiser and Submarine Vertex Array
	CruisSubVVA = std::make_unique<VertexArray>();
	CruisSubVBuffer = std::make_unique<VertexBuffer>(CruisSubV, 4 * 4 * sizeof(float));
													 
	CruisSubHVA = std::make_unique<VertexArray>();	 
	CruisSubHBuffer = std::make_unique<VertexBuffer>(CruisSubH, 4 * 4 * sizeof(float));

	//! Destroyer Vertex Array
	DestroyerVVA = std::make_unique<VertexArray>();
	DestroyerVBuffer = std::make_unique<VertexBuffer>(DestroyerV, 4 * 4 * sizeof(float));
													  
	DestroyerHVA = std::make_unique<VertexArray>();	  
	DestroyerHBuffer = std::make_unique<VertexBuffer>(DestroyerH, 4 * 4 * sizeof(float));

	//! Message Vertex Array
	WinVA = std::make_unique<VertexArray>();
	WinBuffer = std::make_unique<VertexBuffer>(Message, 4 * 4 * sizeof(float));


	VertexBufferLayout layout;
	
	//! Sets the size of the layout to 2 layers of 2 points
	layout.Push<float>(2);
	layout.Push<float>(2);

	//! Adds all of the buffers and layouts to the vertex shader
	TileVA->AddBuffer(*TileBuffer, layout);
	BoardVA->AddBuffer(*BoardBuffer, layout);
	CarrierHVA->AddBuffer(*CarrierHBuffer, layout);
	CarrierVVA->AddBuffer(*CarrierVBuffer, layout);
	BattleshipHVA->AddBuffer(*BattleshipHBuffer, layout);
	BattleshipVVA->AddBuffer(*BattleshipVBuffer, layout);
	CruisSubHVA->AddBuffer(*CruisSubHBuffer, layout);
	CruisSubVVA->AddBuffer(*CruisSubVBuffer, layout);
	DestroyerHVA->AddBuffer(*DestroyerHBuffer, layout);
	DestroyerVVA->AddBuffer(*DestroyerVBuffer, layout);
	WinVA->AddBuffer(*WinBuffer, layout);

	//! Passes the indicies value and tells that there is 6 points
	ib = std::make_unique<IndexBuffer>(indices, 6);


	//! Creates Shader
	Shader s("res/shaders/Basic.shader");
	shader->Bind();
	shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

	//! Textures 
	Miss_Tex = std::make_unique<Texture>("res/textures/Miss.png");
	shader->SetUniform1i("u_Texture", 0);

	Target_Tex = std::make_unique<Texture>("res/textures/Target.png");
	
	Hit_Tex = std::make_unique<Texture>("res/textures/Hit.png");

	CarrierV_Tex = std::make_unique<Texture>("res/textures/CarrierV.png");

	CarrierH_Tex = std::make_unique<Texture>("res/textures/CarrierH.png");

	BattleshipV_Tex = std::make_unique<Texture>("res/textures/BattleshipV.png");

	BattleshipH_Tex = std::make_unique<Texture>("res/textures/BattleshipH.png");

	CruiserV_Tex = std::make_unique<Texture>("res/textures/CruiserV.png");			

	CruiserH_Tex = std::make_unique<Texture>("res/textures/CruiserH.png");

	SubV_Tex = std::make_unique<Texture>("res/textures/SubmarineV.png");	

	SubH_Tex = std::make_unique<Texture>("res/textures/SubmarineH.png");

	DestroyerV_Tex = std::make_unique<Texture>("res/textures/DestroyerV.png");
															
	DestroyerH_Tex = std::make_unique<Texture>("res/textures/DestroyerH.png");

	Board_Tex = std::make_unique<Texture>("res/textures/Board.png");

	Win_Tex = std::make_unique<Texture>("res/textures/Win.png");

	Lose_Tex = std::make_unique<Texture>("res/textures/Lose.png");

	// Projections
	proj = glm::ortho(0.0f, 256.0f, 0.0f, 256.0f, -1.0f, 1.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
}

Create::~Create()
{
}

//! Post: Initializes the drawing of objects
void Create::Initialize()
{
	// Sets background color
	GLCall(glClearColor(0.0f, 0.48f, 0.96f, 0.0f ));	//! Sets the background color to the same color as the water texture
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

//! Pre:  Needs the board x, y and the location x and y
//! Post: Draws the target object
void Create::Target(unsigned int x, unsigned int y, unsigned int bx, unsigned int by)
{
	glm::vec3 translation((x - bx) * 16 - 8, (y - by) * 16 -8, 0); // X, Y, Z

	Target_Tex->Bind();

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model;
		shader->SetUniformMat4f("u_MVP", mvp);
		shader->Bind();
		renderer.Draw(*TileVA, *ib, *shader);
	}
}

//! Pre:  Needs the board x, y and the location x and y
//! Post: Draws the miss object
void Create::Miss(unsigned int x, unsigned int y, unsigned int bx, unsigned int by)
{	
	glm::vec3 translation((x - bx) * 16 - 8, (y - by)*16 - 8, 0); // X, Y, Z

	Miss_Tex->Bind();

	{	
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model;
		shader->SetUniformMat4f("u_MVP", mvp);
		shader->Bind();
		renderer.Draw(*TileVA, *ib, *shader);
	}
}

//! Post: Draws the win message
void Create::Win()
{
	glm::vec3 translation(8 * 16, 8 * 16, 0); // X, Y, Z

	Win_Tex->Bind();

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model;
		shader->SetUniformMat4f("u_MVP", mvp);
		shader->Bind();
		renderer.Draw(*WinVA, *ib, *shader);
	}
}

//! Post: Draws the lose message
void Create::Lose()
{
	glm::vec3 translation(8 * 16, 8 * 16, 0); // X, Y, Z

	Lose_Tex->Bind();

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model;
		shader->SetUniformMat4f("u_MVP", mvp);
		shader->Bind();
		renderer.Draw(*WinVA, *ib, *shader);
	}
}

//! Pre:  Needs the board x, y and the location x and y
//! Post: Draws the hit object
void Create::Hit(unsigned int x, unsigned int y, unsigned int bx, unsigned int by)
{
	glm::vec3 translation((x-bx) * 16 - 8, (y-by) * 16 - 8, 0); // X, Y, Z

	Hit_Tex->Bind();
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model;
		shader->SetUniformMat4f("u_MVP", mvp);
		shader->Bind();
		renderer.Draw(*TileVA, *ib, *shader);
	}
}

//! Pre: Takes in a placement, location, and board location
//! Post: Draws the carrier
void Create::Carrier(unsigned int x, unsigned y, HorVer placement, unsigned int bx, unsigned int by)
{
	if (placement == HORZ)	//! Draws the ship in the Horizantal positon
	{
		CarrierH_Tex->Bind();

		{
			glm::vec3 translation((x - bx)* 16 + 24, y * 16 - 8, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*CarrierHVA, *ib, *shader);
		}
	}
	else
	{
		CarrierV_Tex->Bind();
		{
			glm::vec3 translation((x - bx) * 16 - 8, y * 16 + 24, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*CarrierVVA, *ib, *shader);
		}
	}
}

//! Pre: Takes in a placement, location, and board location
//! Post: Draws the battleship
void Create::Battleship(unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by)
{
	if (placement == HORZ)
	{
		BattleshipH_Tex->Bind();
		{
			glm::vec3 translation((x -bx)* 16 + 16, y * 16 - 8, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*BattleshipHVA, *ib, *shader);
		}
	}
	else
	{
		BattleshipV_Tex->Bind();
		{
			glm::vec3 translation((x -bx)* 16 - 8, y * 16 + 16, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*BattleshipVVA, *ib, *shader);
		}
	}
}

//! Pre: Takes in a placement, location, and board location
//! Post: Draws the cruiser
void Create::Cruiser(unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by)
{
	if (placement == HORZ)
	{
		CruiserH_Tex->Bind();
		{
			glm::vec3 translation((x - bx) * 16 + 8, y * 16 - 8, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*CruisSubHVA, *ib, *shader);
		}

	}
	else
	{
		CruiserV_Tex->Bind();
		{
			glm::vec3 translation((x - bx) * 16 - 8, y * 16 + 8, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*CruisSubVVA, *ib, *shader);
		}
	}
}

//! Pre: Takes in a placement, location, and board location
//! Post: Draws the submarine
void Create::Submarine(unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by)
{

	if (placement == HORZ)
	{
		SubH_Tex->Bind();

		{
			glm::vec3 translation((x - bx) * 16 + 8, y * 16 - 8, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*CruisSubHVA, *ib, *shader);
		}
	}
	else
	{
		SubV_Tex->Bind();
		{
			glm::vec3 translation((x - bx) * 16 - 8, y * 16 + 8, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*CruisSubVVA, *ib, *shader);
		}
	}
}

//! Pre: Takes in a placement, location, and board location
//! Post: Draws the destroyer
void Create::Destroyer(unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by)
{

	if (placement == HORZ)
	{
		DestroyerH_Tex->Bind();

		{
			glm::vec3 translation((x - bx) * 16, y * 16-8, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*DestroyerHVA, *ib, *shader);
		}
	}
	else
	{
		DestroyerV_Tex->Bind();
		{
			glm::vec3 translation((x - bx) * 16 - 8, y * 16, 0); // X, Y, Z
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;
			shader->SetUniformMat4f("u_MVP", mvp);
			shader->Bind();
			renderer.Draw(*DestroyerVVA, *ib, *shader);
		}
	}
}

//! Pre: Takes in a ship name a placement, location, and board location
//! Post: Draws the ship that was specified 
void Create::Ship(std::string name, unsigned int x, unsigned int y, HorVer placement, unsigned int bx, unsigned int by)
{
	if (name == "Carrier")
		Carrier(x, y, placement, bx, by);
	else if (name == "BattleShip")
		Battleship(x, y, placement, bx, by);
	else if (name == "Cruiser")
		Cruiser(x, y, placement, bx, by);
	else if (name == "Submarine")
		Submarine(x, y, placement, bx, by);
	else if (name == "Destroyer")
		Destroyer(x, y, placement, bx, by);
}

//! Pre:  Needs the board x, y and the location x and y
//! Post: Draws the background
void Create::Background(int bx, int by)
{
	bool Player1 = false;
	glm::vec3 translation((-bx+16)*16, (-by+8)*16, 0);

	//glm::vec3 translation2((x)*8 + 256, y*16, 0);
	
	Renderer renderer;
	
	Board_Tex->Bind();
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model;
		shader->SetUniformMat4f("u_MVP", mvp);
		shader->Bind();
		renderer.Draw(*BoardVA, *ib, *shader);
	}
}

//! Pre:  Needs two battleship classes for both players and the board locations
//! Post: Draws the Game board and all of the data within it from ships to the points
void Create::Board(unsigned int bx, unsigned int by, BattleShip& player1, BattleShip& player2)
{
	Background(bx, by);
	
	//! Displayes the location of the ships if they are set by the player
	if(player1.IsSet("Carrier") == true)
		Carrier(player1.OutputShipPointX("Carrier") + 3, player1.OutputShipPointY("Carrier") + 3, player1.GetShipOrientation("Carrier"), bx, by);
	if(player1.IsSet("BattleShip") == true)
		Battleship(player1.OutputShipPointX("BattleShip") + 3, player1.OutputShipPointY("BattleShip") + 3, player1.GetShipOrientation("BattleShip"), bx, by);
	if (player1.IsSet("Cruiser") == true)
		Cruiser(player1.OutputShipPointX("Cruiser") + 3, player1.OutputShipPointY("Cruiser") + 3, player1.GetShipOrientation("Cruiser"), bx, by);
	if (player1.IsSet("Submarine") == true)
		Submarine(player1.OutputShipPointX("Submarine") + 3, player1.OutputShipPointY("Submarine") + 3, player1.GetShipOrientation("Submarine"), bx, by);
	if (player1.IsSet("Destroyer") == true)
		Destroyer(player1.OutputShipPointX("Destroyer") + 3, player1.OutputShipPointY("Destroyer") + 3, player1.GetShipOrientation("Destroyer"), bx, by);

	//! Displays the opponents ships if they have been destroyed
	if (player2.IsDestroyed("Carrier") == true)
		Carrier(player2.OutputShipPointX("Carrier") + 3 + 16, player2.OutputShipPointY("Carrier") + 3, player2.GetShipOrientation("Carrier"), bx, by);
	if (player2.IsDestroyed("BattleShip") == true)
		Battleship(player2.OutputShipPointX("BattleShip") + 3 + 16, player2.OutputShipPointY("BattleShip") + 3, player2.GetShipOrientation("BattleShip"), bx, by);
	if (player2.IsDestroyed("Cruiser") == true)
		Cruiser(player2.OutputShipPointX("Cruiser") + 3 + 16, player2.OutputShipPointY("Cruiser") + 3, player2.GetShipOrientation("Cruiser"), bx, by);
	if (player2.IsDestroyed("Submarine") == true)
		Submarine(player2.OutputShipPointX("Submarine") + 3 + 16, player2.OutputShipPointY("Submarine") + 3, player2.GetShipOrientation("Submarine"), bx, by);
	if (player2.IsDestroyed("Destroyer") == true)
		Destroyer(player2.OutputShipPointX("Destroyer") + 3 + 16, player2.OutputShipPointY("Destroyer") + 3, player2.GetShipOrientation("Destroyer"), bx, by);

	PointNode* temp;
	temp = nullptr;
	unsigned int x;
	unsigned int y;

	//! Runs through all of player2's points and displays if they are hit or missed
	for (int count = 0; count < player2.GetPointNum(); count++)
	{
		if (player2.GetNextHit(x, y, temp) == true)
		{
			if (temp->entity == true)
				Hit(x + 16 + 3, y + 3, bx, by);
			else
				Miss(x + 16 + 3, y + 3, bx, by);
		}
	}
	
	//! Resets temp
	temp = nullptr;
	
	//! Runs through all of player1's points and displays if they are hit or missed
	for (int count = 0; count < player1.GetPointNum(); count++)
	{
		if (player1.GetNextHit(x, y, temp) == true)
		{
			if (temp->entity== true)
				Hit(x + 3, y + 3, bx, by);
			else
				Miss(x + 3, y + 3, bx, by);
		}
	}

	//! Old inefficent code
	/*for (unsigned int y = 1; y <= 10; y++)
	{
		for (unsigned int x = 1; x <= 10; x++)
		{
			if (player1.IsHit(x, y) == true)
			{
				if (player1.ShipPointTest(x, y) == true)
					Hit(x + 3, y + 3, bx, by);
				else
					Miss(x + 3, y + 3, bx, by);
			}
		}
	}*/
}

