/*********************************************************************************

	Drake Dodson
	CIS-153-FD01 Computer programing: Data Structures
	May 8th, 2019

	This is the Ship class. It works with the board class to create entities with
	in the board. It does this by storing the locations of specific points within
	each ship. Each ship that is created is linked to the next ship via a unsorted
	linked list. I felt that because the ships have no need to be sorted in anyway
	that a sorted list would be a waste of resources and overhead.

	With this class you can create ships and manipulate their data. For instance 
	you can specify how many ships you want and at what lenght. So theoretically
	you could have 20 ships that are one point long or you could have one ship 
	that is 9 points long. 

	You can also see the status of the ships and randomize the ships location. 

**********************************************************************************/

#ifndef SHIPS_H
#define SHIPS_H

#include <iostream>
#include <time.h>
#include "Board.h"

//! Placement enum
enum HorVer { HORZ, VERT };

//! Maximum size of ship that is allowed
const unsigned int Max_Ship_Size = 9;

//! ShipNode structure. Contains all of the data for the ships
struct ShipNode
{
	unsigned int length;
	PointNode* point[Max_Ship_Size];
	bool destroyed;
	bool set;
	HorVer placement;
	std::string name;
	ShipNode* next;
};

class Ships
{

public:
	
	//! Board is public so BattleShip.h can manipulate it
	Board* B1;

	//! Post: Initalizes all of the game data and creates an instance of the board class that sets the size to 10 , 10
	Ships();

	//! Pre:  Takes in an x and a y for the board length
	//! Post: Generates the size of the board to make it of the size that the user chooses. Initalizes everything
	Ships(unsigned int x, unsigned int y);
	
	//! Post: Deletes all the ship data and deletes the board
	~Ships();

	//! Pre:  Takes in a length of a ship and a name for the ships
	//! Post: Creates a new ship with the specifications
	void NewShip(unsigned int slength, std::string sname);
	
	//! Pre:  Ships need to be created
	//! Post: Returns true if all the ships have been set and false if they have not
	bool AllShipsSet();

	//! Pre:  Ships need to be created
	//! Post: Deletes all of the ships
	void ClearShips();

	//! Pre:  Takes in a location a placement and the name of the ship to be placed
	//! Post: Sets the location of that ship to the location that was choosen. Returns false if the placement is invalid
	void OutputPoints(std::ostream& outFile);

	//! Pre:  Takes in a location a placement and the name of the ship to be placed
	//! Post: Sets the location of that ship to the location that was choosen. Returns false if the placement is invalid
	bool SetShipLocation(unsigned int nx, unsigned int ny, HorVer placement, std::string);
	
	//! Pre:  Needs points to check for
	//! Post: Returns true if the point provided is a point of a ship false if it is not
	bool ShipPointTest(unsigned int x, unsigned int y);

	//! Pre:  Needs points to check for
	//! Post: Returns true if the point provided is a point of a ship false if it is not 
	bool ShipDestroyed(std::string name);

	//! Pre:  Needs a pointer and a name for the ship
	//! Post: Finds the specified ship, returns true if it is found and changes the pointer to it's location
	bool ShipSearch(std::string name, ShipNode*& spointer);	

	//! Pre: Needs a test location
	//! Post: Runs the bound test in the board and returns true if valid and false if invalid
	bool BoundTest(unsigned int x, unsigned int y);

	//! Pre:  Needs a ship to search for
	//! Post: Returns true if it is set and false if it isn't
	bool IsSet(std::string name);

	//! Pre:  There needs to be ships
	//! Post: Ramdomizes the location of the ships that have not been set
	void RandomizeShipPlacements();
	
	//! Pre:  The board needs to be intialized
	//! Post: Resets all of the data within the board
	void ResetBoard();

	//! Pre:  Needs a ship name
	//! Post: Returns its length
	unsigned int GetShipLength(std::string name);

	//! Pre:  Ships need to be created
	//! Post: Returns the name of the next ship
	std::string GetNextName();

	//! Pre:  Needs an upperbound and a lower bound
	//! Post: Returns a random number in the limit
	unsigned int RNG(unsigned int ub, unsigned int lb);
	
	//! Post: Returns a random ship placement
	HorVer RNGHV();

	//! Post: Returns the ship number
	inline unsigned int GetShipNum() { return Ship_Num; }; 

private:

	unsigned int Ship_Num;

	ShipNode* ship_pos;
	ShipNode* ship_front;
	PointNode* pLoc;
};


#endif //! SHIPS_H
