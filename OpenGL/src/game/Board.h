/*********************************************************************************

	Drake Dodson
	CIS-153-FD01 Computer programing: Data Structures
	May 8th, 2019

	This is the board class that generates the code for the board and creates
	points within that board that can then be interacted with. The intention
	was to create it so that it is easily interchangable and can bend to the 
	users wishes. However, as I needed more specialized things it has sort of
	lost a little bit of that but is still about 99% constomizable.

	The class has the ability to create new points that are linked together going
	sorted going across the x axis left to right then down the y axis. The points
	are linked by a linked list. Also the class is set up so a point can never go
	outside the bounds of the board. 

**********************************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <time.h>

//! Compare type is used to see if something is greater than (GRT), less than (LST), or equal to (EQT) something 
enum CompareType { LST, EQT, GRT };

//! Structure that contains all of the information contained within each point
struct PointNode
{
	PointNode* next;
	bool hit;
	bool entity;
	unsigned int x;
	unsigned int y;
};

class Board
{
public:
	
	//! Post: Intializes everything and sets board length to 10 , 10
	Board();
	
	//! Pre:  Takes in an x and a y
	//! Post: Intializes everything and sets board length to x and y
	Board(unsigned int x, unsigned int y);
	
	//! Post: Deletes all of the points
	~Board();

	//inline void SetBoardX(int _x) { BoardX = _x; };
	//inline void SetBoardY(int _y) { BoardY = _y; };

	//! Pre: Takes in a location for a point and a pointer 
	//! Post: Creates a new point and returns true of it is unique. If it is not unique the point is not created
	//!			and false is returned. Also changes the value of the pointer to the location of the new point
	bool NewPoint(unsigned int nx, unsigned int ny, PointNode *& pLoc);
	
	//! Post: Clears all of the points 
	void ClearPoints();
	
	//! Pre:  Takes in an x and a y
	//! Post: Returns whether or not the point was hit
	bool IsHit(unsigned int nx, unsigned int ny);

	//! Pre:  Takes in an x and a y
	//! Post: Returns if it is an entity (ship) or not.
	bool IsEntity(unsigned int x, unsigned int y);
	
	//! Pre:  Takes in a x and a y
	//! Post: Sets the bool to hit for that point
	void SetHit(unsigned int nx, unsigned int ny);
	
	//! Pre:  Takes in x and y values to search for and a pointer
	//! Post: Returns whether or not it was found and returns the location of the pointer
	bool PointSearch(unsigned int nx, unsigned int ny, PointNode*& pointer);
	
	//! Pre:  Takes in a file
	//! Post: Outputs the poitns to the file.
	//!	-Used primarily for debugging
	void OutputPoints(std::ostream& outFile);
	
	//! Pre:  Takes in a x and y location
	//! Post: Returns true or false if it is within bounds
	bool BoundTest(unsigned int x, unsigned int y);
	
	//! Pre: Takes in an x and y and a pointer
	//! Post: Returns whether or not the point has been hit and changes the locaiton of the pointer to the next
	//!			location and sets the x and y to that pointers point location
	bool GetNextHit(unsigned int& x, unsigned int& y, PointNode*& temp);

	//! Pre: Takes in an unsigned int
	//! Post: Sets the board Y
	inline void SetBoardY(unsigned int _y) { BoardY = _y; };

	//! Pre: Takes in an unsigned int
	//! Post: Sets the board Y
	inline void SetBoardX(unsigned int _x) { BoardX = _x; };
	
	//! Post: returns the board x
	inline unsigned int GetBoardX() { return BoardX; };

	//! Post: Returns the board y
	inline unsigned int GetBoardY() { return BoardY; };
	
	//! Post: Returns the point number
	inline unsigned int GetPointNum() { return Point_Num; };
	


private:
	
	//! Pre:  Takes in a new point and a test point to be compared
	//! Post: Returns whether it was greater than equal to or less than the test point given
	CompareType ComparePoint(unsigned int nx, unsigned int ny, unsigned int x, unsigned int y);
	
	//! Board Height and Width
	unsigned int BoardX;
	unsigned int BoardY;
	unsigned int Point_Num;	//! The number of points 
	PointNode* pt_front;	//! The front of the linked list
};
#endif //! BOARD_H
