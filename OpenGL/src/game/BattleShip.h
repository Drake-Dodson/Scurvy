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


#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "Ships.h"
#include <iostream>
#include <time.h>

struct ShipNode;
struct PointNode;

class BattleShip
{
public:
	
	//! Basic GameMode constructor
	//! Post: creates a ship class of size 10 , 10 and creates the ships
	BattleShip();

	//! Post: Deletes the instance of the ships class
	~BattleShip();

	//! Post: Resets all of the data within the board such as the placement of the ships
	//!			and all of the points
	void ResetBoard();

	//! Pre:  Takes in the location, placement, and name of the ship
	//! Post: Returns true if the ship was set and places that ship
	bool PlaceShip(unsigned int x, unsigned int y, HorVer placement, std::string ship);

	//! Post: Randomizes the ship placement
	void RandomizeShipPlacements();

	//Pre: Takes in two points and tests them for validity.
	//Post: Returns true for valid. False for invalid.
	bool BoundTest(unsigned int x, unsigned int y);

	// Post: Returns the point number
	unsigned int GetPointNum();

	//! Pre:  Takes in a location and a pointer
	//! Post: Returns the values of the location, a pointer to the location and false if it's not hit, true if it is
	bool GetNextHit(unsigned int& x, unsigned int& y, PointNode*& temp);

	//! Pre:  Takes in two points
	//! Post: Returns if it is hit
	bool IsHit(unsigned int x, unsigned int y);
	
	//! Pre:  Needs a ship to search for
	//! Post: Returns true if it is set and false if it isn't
	bool IsSet(std::string name);

	//! Pre:  Needs a ship to search for
	//! Post: Returns true for destroyed and false for not destroyed 
	bool IsDestroyed(std::string name);

	//! Pre:  Ships need to be intialized
	//! Post: Returns false if they aren't all set
	bool AllShipsSet();

	//! Pre:  Takes in a ship to look for
	//! Post: Returns it's orientation
	HorVer GetShipOrientation(std::string name);

	//! Pre:  Needs points to check for
	//! Post: Returns true if the point provided is a point of a ship false if it is not
	bool ShipPointTest(unsigned int x, unsigned int y);

	//! Post: Returns the shipnumber 
	inline unsigned int GetShipNumber() { return S1->GetShipNum(); };

	//! Post: Returns the next ship name
	inline std::string GetNextShipName() { return S1->GetNextName(); };

	//! Pre:  Needs a string to search for
	//! Post: Returns the ships length
	unsigned int GetShipLength(std::string name);

	//! Pre: Already NEEDS to be called first 
	//! Post: Adds a new point and returns true if the point is not a ship or returns   
	bool AttackShip(unsigned int x, unsigned int y);
	
	//! Pre:  Takes in a ship name to search for
	//! Post: Outputs the first ship X value
	unsigned int OutputShipPointX(std::string name);
	
	//! Pre:  Takes in a ship name to search for
	//! Post: Outputs the first ship Y value
	unsigned int OutputShipPointY(std::string name);

	//! Pre:  Takes in an out file 
	//! Post: Output's all of the points 
	void OutputPoints(std::ostream& outFile);

	//! Pre:  Ships need to be set
	//! Post: Returns false if they player hasn't lost and true if they have
	bool Lose();
	
	//! Pre:  Needs ships to be created
	//! Post: Outputs the board layout to the file
	void PrintBoard(std::ostream& outFile);

private:
	
	Ships* S1;	//! Set to private so the user cannot manipulate the data with in the class
};


#endif //! PLAYER_H