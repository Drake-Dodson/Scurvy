/*********************************************************************************

	Drake Dodson
	CIS-153-FD01 Computer programing: Data Structures
	May 8th, 2019

	This is the BattleShip class that handles the last of the game functions. It
	is theoretically set up so that you can easily modify it and make it so that
	there are multiple game modes and multiple ways of playing the simple game of
	battleship. Most of the functions in this class just run the functions in the
	previous 2 classes. However, this is done to make it simpler and more 
	abstracted for the end user to use. So theoretically the user should only need
	this class and should never touch Ships and Board. Though some more 
	abstraction could be utilized.

	This class also contains some basic debugging options that can help to show
	the user what is going on with the program and make it easier to find the
	source of certain problems.

	Notes:
	-GameMode Class. Use Ships.cpp to change the ship game data
	-The termonology 'hit' is used to describe a location that has already been
		attacked regardless of if it is actually a ship or not.
	-Placement and Orientation mean the way that it goes along the axis
		Horizantal(Along the x axis) and Vertical(Along the y axis)

**********************************************************************************/

#include "BattleShip.h"
#include <iostream>

//! Basic GameMode constructor
//! Post: creates a ship class of size 10 , 10 and creates the ships
BattleShip::BattleShip() 
{
	// Initiaizes the ship class
	S1 = new Ships(10, 10);

	// Creates all the ships
	S1->NewShip(2, "Destroyer");
	S1->NewShip(3, "Cruiser");
	S1->NewShip(3, "Submarine");
	S1->NewShip(4, "BattleShip");
	S1->NewShip(5, "Carrier");
}

//! Post: Deletes the instance of the ships class
BattleShip::~BattleShip()
{
	delete S1;
}

//! Pre:  Takes in the location, placement, and name of the ship
//! Post: Returns true if the ship was set and places that ship
bool BattleShip::PlaceShip(unsigned int x, unsigned int y, HorVer placement, std::string ship)
{
	return S1->SetShipLocation(x, y, placement, ship) == true;
}

//! Post: Randomizes the ship placement
void BattleShip::RandomizeShipPlacements()
{
	S1->RandomizeShipPlacements();
}

//! Pre:  Takes in a location and a pointer
//! Post: Returns the values of the location, a pointer to the location and false if it's not hit, true if it is
bool BattleShip::GetNextHit(unsigned int& x, unsigned int& y, PointNode*& temp)
{
	return S1->B1->GetNextHit(x, y, temp);
}

//! Post: Returns the point number
unsigned int BattleShip::GetPointNum()
{
	return S1->B1->GetPointNum();
}

//! Pre:  Ships need to be intialized
//! Post: Returns false if they aren't all set
bool BattleShip::AllShipsSet()
{
	return S1->AllShipsSet();
}

//Pre: Takes in two points and tests them for validity.
//Post: Returns true for valid. False for invalid.
bool BattleShip::BoundTest(unsigned int x, unsigned int y)
{
	return S1->B1->BoundTest(x, y);
}

//! Pre:  Takes in two points
//! Post: Returns whether or not it was hit
bool BattleShip::IsHit(unsigned int x, unsigned int y)
{
	return S1->B1->IsHit(x, y);
}

//! Pre: Already NEEDS to be called first 
//! Post: Adds a new point and returns true if the point is not a ship or returns
bool BattleShip::AttackShip(unsigned int x, unsigned int y)
{
	PointNode* pLoc = nullptr;
	//! Creates a new point
	if (S1->B1->NewPoint(x, y, pLoc) == true)
	{
		S1->B1->SetHit(x, y);
		return false; // Miss
	}
	//! if it does not fail then that means it is a miss 
	else
	{
		S1->B1->SetHit(x, y);
		return true; // Hit
	}
}

//! Pre:  Needs points to check for
//! Post: Returns true if the point provided is a point of a ship false if it is not
bool BattleShip::ShipPointTest(unsigned int x, unsigned int y)
{
	return S1->ShipPointTest(x, y);
}

//! Pre:  Ships need to be set
//! Post: Returns false if they player hasn't lost and true if they have
bool BattleShip::Lose()
{
	//! Runs through all of the ships and checks to see if they are destroyed
	unsigned int destroyed = 0; 
	for (unsigned int count = 0; count < S1->GetShipNum(); count++)
	{
		if (S1->ShipDestroyed(S1->GetNextName()) == true)
		{
			destroyed++;		//! Talies up all of the destroyed ships
		}
	}

	//! Returns true if they are all destroyed. False if they aren't 
	if (destroyed == S1->GetShipNum())
	{
		return true;
	}
	else
		return false;
}

//! Pre:  Needs a string to search for
//! Post: Returns the ships length
unsigned int BattleShip::GetShipLength(std::string name)
{
	return S1->GetShipLength(name);
}

//! Post: Resets all of the data within the board such as the placement of the ships
//!			and all of the points
void BattleShip::ResetBoard()
{
	S1->ResetBoard();
}

//! Pre:  Takes in a ship to look for
//! Post: Returns it's orientation
HorVer BattleShip::GetShipOrientation(std::string name)
{
	ShipNode* temp;
	S1->ShipSearch(name, temp);
	return temp->placement;
}

//! Pre:  Needs a ship to search for
//! Post: Returns true if it is set and false if it isn't
bool BattleShip::IsSet(std::string name)
{
	return S1->IsSet(name);
}

//! Pre:  Needs a ship to search for
//! Post: Returns true for destroyed and false for not destroyed 
bool BattleShip::IsDestroyed(std::string name)
{
	return S1->ShipDestroyed(name);
}

//! Pre:  Takes in an out file 
//! Post: Output's all of the points 
void BattleShip::OutputPoints(std::ostream& outFile)
{
	S1->B1->OutputPoints(outFile);
}

//! Pre:  Needs ships to be created
//! Post: Outputs the board layout to the file
void BattleShip::PrintBoard(std::ostream& outFile)
{
	
	//! Top of the board
	outFile << "\n     _____________________________________________\n";
	outFile << "    |" << "Debug" << " board. \t\t\t\t  |\n";
	outFile << "    |_____________________________________________|\n";
	outFile << "    |+X|  1   2   3   4   5   6   7   8   9   10  |\n";
	outFile << "    |y_|__________________________________________|\n";
	outFile << "    |  |                                          |\n";

	for (unsigned int y = 1; y <= S1->B1->GetBoardY(); y++)			//! Runs for all of the y's 		
	{
		if (y != 10)
			outFile << "    |" << y << " |  ";																//Places a row based on the y cordinate
		else
			outFile << "    |" << y << "|  ";

		for (unsigned int x = 1; x <= S1->B1->GetBoardX(); x++)		//! Outputs for all the x's 
		{	
			if (S1->B1->IsHit(x, y))								//! Outputs x for a hit
			{
				outFile << "X";
			}
			else
			{
				if (S1->B1->IsEntity(x, y) == true)					//! # for a ship
					outFile << "#";
				else
					outFile << "~";									//! ~ for everything else
			}
			outFile << "   " ;														//Places a tile based on x and y cordinate of the loop. Eventually getting to all 100 tiles.
		}

		outFile << "|" << std::endl;
		if (y != S1->B1->GetBoardY())														//If it is not the end of the row this if statement is activated causeing the border to not be placed
			outFile << "    |  |                                          |" << std::endl;
		else
			outFile << "    |__|__________________________________________|\n";
	}
}

//! Pre:  Takes in a ship name to search for
//! Post: Outputs the first ship X value
unsigned int BattleShip::OutputShipPointX(std::string name)
{
	//! Searches for the ship and returns it's first point
	ShipNode* temp;
	S1->ShipSearch(name, temp);

	return temp->point[0]->x;
}

//! Pre:  Takes in a ship name to search 
//! Post: Outputs the first ship Y value
unsigned int BattleShip::OutputShipPointY(std::string name)
{
	//! Searches for the ship and returns it's first point
	ShipNode* temp;
	S1->ShipSearch(name, temp);

	return temp->point[0]->y;
}


