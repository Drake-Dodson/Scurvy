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

#include "Ships.h"
#include <iostream>

//! Post: Initalizes all of the game data and creates an instance of the board class that sets the size to 10 , 10
Ships::Ships()
{
	srand(time(NULL));
	B1 = new Board(10, 10);
	ship_front = nullptr;

	Ship_Num = 0;
}

//! Pre:  Takes in an x and a y for the board length
//! Post: Generates the size of the board to make it of the size that the user chooses. Initalizes everything
Ships::Ships(unsigned int x, unsigned int y)
{
	srand(time(NULL));		//! Seeds the randomizer
	B1 = new Board(x, y);	//! Creates a new board
	ship_front = nullptr;
	pLoc = nullptr;

	Ship_Num = 0;
}

//! Post: Deletes all the ship data and deletes the board
Ships::~Ships()
{
	ClearShips();
	delete B1;
}

//! Pre:  Takes in a length of a ship and a name for the ships
//! Post: Creates a new ship with the specifications
void Ships::NewShip(unsigned int slength, std::string sname)
{
	ShipNode* nShip;				//! Creates a new ship node
	nShip = new ShipNode;
	nShip->name = sname;			//! Sets all of the data to the specifications and the default
	nShip->destroyed = false;
	nShip->set = false;
	nShip->placement = HORZ;
	nShip->length = slength;
	nShip->next = ship_front;
	ship_front = nShip;				//! Iterates the ship number
	Ship_Num++;
}

//! Pre:  Ships need to be created
//! Post: Returns true if all the ships have been set and false if they have not
bool Ships::AllShipsSet()
{
	ShipNode* temp;
	temp = ship_front;
	int setcount = 0;
	
	for (int count = 0; count < GetShipNum(); count++)
	{
		if (temp->set == true)
			setcount++;
		temp = temp->next;
	}
	if (setcount == GetShipNum())
		return true;
	else
		return false;
}

//! Pre:  Ships need to be created
//! Post: Deletes all of the ships
void Ships::ClearShips()
{
	ShipNode* dShip;

	while (ship_front != nullptr)	//! Runs through all of the ships
	{
		dShip = ship_front;
		ship_front = ship_front->next;

		delete dShip;
	}
	Ship_Num = 0;					//! Sets ship num equal to 0
}

//! Pre:  Takes in a file stream
//! Post: Calls Output point in B1 and outputs the points to the file
void Ships::OutputPoints(std::ostream& outFile)
{
	B1->OutputPoints(outFile);
}

//! Pre:  Takes in a location a placement and the name of the ship to be placed
//! Post: Sets the location of that ship to the location that was choosen. Returns false if the placement is invalid
bool Ships::SetShipLocation(unsigned int nx, unsigned int ny, HorVer placement, std::string name)
{
	ShipNode *temp;
	temp = nullptr;
	
	if (ShipSearch(name, temp) == false)		//! Searches for the ship and changes the temp pointer
	{
		return false;
	}

	if (temp->set == true)						//! Returns false if the ship has already been set		
	{
		return false;
	}

	/*** Horizantal Placement ***/
	if (placement == HORZ)
	{
		if (BoundTest(nx + GetShipLength(name) - 1, ny) == false)				//! Tests to see if the ship can fit in the bounds
			return false;

		for (unsigned int check = 0; check < GetShipLength(name); check++)		//! Tests to see if a ship was already placed in that location
			if (B1->PointSearch(nx + check, ny, pLoc) == true)
				return false;

		for (unsigned int count = 0; count < GetShipLength(name); count++)		//! If the ship gets through all of that it finally creates new points and
		{
			if (B1->NewPoint(nx, ny, pLoc) == false)							//! Creates the new points
				return false;													//! This isn't necessary but is left here just incase something weird happens
			pLoc->entity = true;												//! Sets entity to true because there is a ship located their
			temp->point[count] = pLoc;											//! Returns the pointer for the point location and stores it to the ships points
			nx++;																//! increases the value of x
		}
		temp->set = true;
		temp->placement = HORZ;
	}
	/*** Vertical placement ***/
	else
	{	// Essentially the same as the Horizantal but manipulating y instead
		if (BoundTest(nx, ny + GetShipLength(name)-1) == false)
			return false;

		for (unsigned int check = 0; check < GetShipLength(name); check++)		//! Tests to see if the ship can fit in the bounds
			if (B1->PointSearch(nx, ny + check, pLoc) == true)
				return false;
																				//! Tests to see if a ship was already placed in that location
		for (unsigned int count = 0; count < GetShipLength(name); count++)
		{
			if (B1->NewPoint(nx, ny, pLoc) == false)
				return false;													//! If the ship gets through all of that it finally creates new points and
			pLoc->entity = true;
			temp->point[count] = pLoc;											//! Creates the new points
			ny++;																//! This isn't necessary but is left here just incase something weird happens
		}																		//! Sets entity to true because there is a ship located their
		temp->set = true;														//! Returns the pointer for the point location and stores it to the ships points
		temp->placement = VERT;													//! increases the value of y
	}
	return true;
}

//! Pre:  Needs points to check for
//! Post: Returns true if the point provided is a point of a ship false if it is not
bool Ships::ShipPointTest(unsigned int x, unsigned int y)
{
	ShipNode* temp;
	temp = ship_front; 
	//! Runs through all the ships to see if any of their points match
	for (unsigned int count = 0; count < Ship_Num; count++)
	{
		for (unsigned int count2 = 0; count2 < GetShipLength(temp->name); count2++)
		{
			if (x == temp->point[count2]->x && y == temp->point[count2]->y)
				return true;
		}
		temp = temp->next;
	}
	return false; //! If their is no match then it returns false
}

//! Pre:  Needs a ship name
//! Post: Returns if it is destroyed or not and updates the status of the ship 
bool Ships::ShipDestroyed(std::string name)
{
	ShipNode* temp;
	int hitcount = 0;
	
	//! Searches for the ship
	if (ShipSearch(name, temp) == true);
	{
		if (temp->destroyed == true)												//! Prevents the program from running the loop if it is already found to be destroyed
			return true;
		else
		{
			for (unsigned int count = 0; count < GetShipLength(name); count++)
			{
				if (temp->point[count]->hit == true)								//! Adds to the hit count if the point is hit
					hitcount++;				
				else
					count = Max_Ship_Size;											//! If there is only one point that isn't hit the ship isn't destroyed so it breaks from the function
			}
			if (hitcount == GetShipLength(name))
			{
				temp->destroyed = true;												//! If the ship is destroyed then its bool is updated
			}
			return temp->destroyed;
		}
	}
}

//! Pre:  Needs a pointer and a name for the ship
//! Post: Finds the specified ship, returns true if it is found and changes the pointer to it's location
bool Ships::ShipSearch(std::string name, ShipNode*& spointer)
{
	spointer = ship_front;
	//! Iterates through all fo the ships 
	for (unsigned int count = 0; count < Ship_Num; count++)
	{
		if (spointer->name == name)
		{
			return true;
		}
		else
		{
			if (spointer->next == nullptr)	//! Checks to see if the process has reached the end of the line
				return false;
			spointer = spointer->next;		//! Goes to next ship
		}
	}
	return false;
}

//! Pre: Needs a test location
//! Post: Runs the bound test in the board and returns true if valid and false if invalid
bool Ships::BoundTest(unsigned int x, unsigned int y)
{
	return B1->BoundTest(x, y);
}

//! Pre:  Needs a ship to search for
//! Post: Returns true if it is set and false if it isn't
bool Ships::IsSet(std::string name)
{
	ShipNode* temp;
	ShipSearch(name, temp);
	return temp->set;
}

//! Pre:  There needs to be ships
//! Post: Ramdomizes the location of the ships that have not been set
void Ships::RandomizeShipPlacements()
{
	std::string name; 
	bool Invalid = true;
	//! Runs through all ships
	for (unsigned int count = 0; count < GetShipNum(); count++)
	{
		name = GetNextName();
		if (IsSet(name) == false)	//! Makes sure that ships isn't set and skips it if it is
		{
			Invalid = true;

			while (Invalid)			//! Continues to randomize until it gets a valid location for the ship
			{
				if (SetShipLocation(RNG(B1->GetBoardX(), 1), RNG(B1->GetBoardY(), 1), RNGHV(), name) == false) //! Gets a random number for x and y between 1 and the board length and a placement
					Invalid = true;
				else
					Invalid = false;
			} 
		}
	}
}

//! Pre:  The board needs to be intialized
//! Post: Resets all of the data within the board 
//!		Notes: Technically not used at all in the Application but may be used in the future
void Ships::ResetBoard()
{
	ShipNode* temp;
	temp = ship_front;
	//! Resets all of the points of the ship 
	for (int count = 0; count < Ship_Num; count++)
	{
		for (int count2 = 0; count2 < GetShipLength(temp->name); count2++)
		{
			temp->point[count2] = nullptr;
		}
		temp->set = false;
		temp->destroyed = false; 
		temp = temp->next;
	}
	B1->ClearPoints();
}

//! Pre:  Needs a ship name
//! Post: Returns its length
unsigned int Ships::GetShipLength(std::string name)
{
	ShipNode* temp;
	temp = ship_front;
	ShipSearch(name, temp);
	return temp->length;
}

//! Pre:  Ships need to be created
//! Post: Returns the name of the next ship
std::string Ships::GetNextName()
{
	//! Sets the position to front if it has not been intialized to anything else
	if (ship_pos == nullptr)
	{
		ship_pos = ship_front;
	}
	else
	{
		if (ship_pos->next == nullptr)	//! Makes sure the function can loop
		{
			ship_pos = ship_front;
		}
		else
		{
			ship_pos = ship_pos->next;	//! Gets the next ship
		}
	}
	return ship_pos->name;
}

//! Post: Randomizes the placement 
HorVer Ships::RNGHV()
{
	int input = rand() % 2 + 1;
	switch (input)
	{
	case 1: return HORZ;
		break;
	case 2: return VERT;
		break;
	default: return VERT;
	}
}

//! Pre:  Needs an upperbound and a lower bound
//! Post: Returns a random number in the limit
unsigned int Ships::RNG(unsigned int ub, unsigned int lb)
{
	return rand() % ub + lb;
}