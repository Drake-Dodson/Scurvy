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

#include "Board.h"

//! Post: Intializes everything and sets board length to 10 , 10
Board::Board()
{
	BoardX = 10;
	BoardY = 10;
	pt_front = nullptr;
	Point_Num = 0;
}

//! Pre:  Takes in an x and a y
//! Post: Intializes everything and sets board length to x and y
Board::Board(unsigned int x, unsigned int y)
{	
	BoardX = x;
	BoardY = y;

	pt_front = nullptr;
	Point_Num = 0;
}

//! Post: Deletes all of the points
Board::~Board()
{
	ClearPoints();
}
//! Pre: Takes in a location for a point and a pointer 
//! Post: Creates a new point and returns true of it is unique. If it is not unique the point is not created
//!			and false is returned. Also changes the value of the pointer to the location of the new point
bool Board::NewPoint(unsigned int nx, unsigned int ny, PointNode *& pLoc)
{
	//! Checks to make sure the point given is within the bounds
	if (nx > BoardX)
		return false;
	if (ny > BoardY)
		return false;

	//! Creates 3 PointNode pointers
	PointNode* nPoint;
	PointNode* predLoc;
	PointNode* location;

	location = pt_front;
	predLoc = nullptr;
	int x;
	int y;

	bool search;

	search = (location != nullptr);	//! Makes sure the list is intialized 

	while (search)					//! Moves through all of the x values until 
	{
		x = location->x;
		y = location->y;
		switch (ComparePoint(nx, ny, x, y))
		{
		case GRT:
		{
			predLoc = location;				//! Sets predLoc to location and location to the next location
			location = location->next;
			search = (location != nullptr);	//! Tests to see if there is still more searching to be done or if the function has 
			break;							//!		reached the end of the list
		}
		case LST:
		{
			search = false;					//! If the value is less than then that means that it is the right location
			break;
		}
		case EQT:
		{
			return false;			//! Returns false to the function
			break;
		}
		}
	}
	
	//! Creates a new point
	nPoint = new PointNode;
	nPoint->x = nx;
	nPoint->y = ny;
	nPoint->hit = false;
	nPoint->entity = false;

	//! if the predLoc is nullptr or at the beginning of the list
	if (predLoc == nullptr)
	{
		nPoint->next = pt_front;	//! Sets the next pointer of new to the current front location
		pt_front = nPoint;			//! Moves nPoint to the new front location 
		pLoc = nPoint;				//! Sets the return pointer location to the new point location
	}
	else
	{
		nPoint->next = location;	//! Sets the next pointer to the number that is greater than the number
		predLoc->next = nPoint;		//! Sets the previous location to the new points location
		pLoc = nPoint;				//! Sets the return pointer location to the new point location
	}
	Point_Num++;	//! Iterates point number
	return true;
}

//! Post: Clears all of the points and sets Point num to zero
void Board::ClearPoints()
{
	PointNode* dPoint;

	while (pt_front != nullptr)
	{
		dPoint = pt_front;
		pt_front = pt_front->next;
		delete dPoint;
	}
	Point_Num = 0;
}

//! Pre:  Takes in a file
//! Post: Outputs the poitns to the file.
//!	-Used primarily for debugging
void Board::OutputPoints(std::ostream& outFile)
{
	PointNode* temp;	
	temp = pt_front;
	//! Outputs the number of points and all of the points in order in (X , Y) format
	outFile << GetPointNum() << " Points" << std::endl;
	for (unsigned int count = 0; count < GetPointNum(); count++)
	{
		outFile << temp->y << " , " << temp->x << "\n";
		temp = temp->next;
	}
}

//! Pre:  Takes in a x and a y
//! Post: Sets the bool to hit for that point. Also returns false if the point is not found
bool Board::IsHit(unsigned int nx, unsigned int ny)
{
	//! Searches for the point
	PointNode* temp;
	if (PointSearch(nx, ny, temp) == true)
	{
		if (temp->hit == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//! Pre:  Takes in an x and a y
//! Post: Returns if it is an entity (ship) or not. Also returns false if the point is not found
bool Board::IsEntity(unsigned int x, unsigned int y)
{
	//! Searches for the point's location
	PointNode* temp;
	if (PointSearch(x, y, temp) == true)
	{
		if (temp->entity == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

//! Pre:  Takes in a x and a y
//! Post: Sets the bool to hit for that point
void Board::SetHit(unsigned int nx, unsigned int ny)
{
	//! Searches for point
	PointNode* temp;
	temp = pt_front;
	//! if it is sets it's hit vaule to true
	if(PointSearch(nx, ny, temp) == true)
	{	
		temp->hit = true;
	}
	else
	{
		//! If it is not found it creates a new point and sets the new points value to true
		NewPoint(nx, ny, temp);
		temp->hit = true;
	}
}

//! Pre: Takes in an x and y and a pointer
//! Post: Returns whether or not the point has been hit and changes the locaiton of the pointer to the next
//!			location and sets the x and y to that pointers point location
bool Board::GetNextHit(unsigned int& x, unsigned int& y, PointNode*& temp)
{
	if (temp == nullptr)		//! If temp is set to nullptr it sets it to the front of the list
	{
		temp = pt_front;
		x = temp->x;			//! Sets x and y to the current x and y
		y = temp->y;
		return temp->hit;
	}
	if (temp->next == nullptr)	//! If the pointer reaches the end of the line it sets it to the front of the list
	{
		temp = pt_front;
	}
	else
	{
		temp = temp->next;
		x = temp->x;
		y = temp->y;
	}
	return temp->hit;			//! returns if the point is hit or not 
}

//! Pre:  Takes in x and y values to search for and a pointer and the list needs to be created
//! Post: Returns whether or not it was found and returns the location of the pointer
bool Board::PointSearch(unsigned int nx, unsigned int ny, PointNode*& pointer)	//! Returns a bool for if that item is already a point or not
{
	bool search = true;
	pointer = pt_front;
	for (unsigned int count = 0; count < Point_Num; count++)	//! Iterates through all of the pointes
	{
		if (pointer == nullptr)									//! Returns false if the list hasn't been created
			return false;
		else
		{
			if (nx == pointer->x && ny == pointer->y)			//! Returns true if nx and ny equal the pointers x and y
			{
				return true;
			}
			else
			{
				pointer = pointer->next;						//! Goes to next point
			}
		}
	}
	return false;												//! Returns false if the point is not found
}

//! Pre:  Takes in a x and y location
//! Post: Returns true or false if it is within bounds
bool Board::BoundTest(unsigned int x, unsigned int y)
{
	if (x > GetBoardX())						// Over bounds of x	
		return false;
	else if (y > GetBoardY())					// Over bounds of y
		return false;
	else
		return true;
}

//***Private Functions***

//! Pre:  Takes in a new point and a test point to be compared
//! Post: Returns whether it was greater than equal to or less than the test point given
CompareType Board::ComparePoint(unsigned int nx, unsigned int ny, unsigned int x, unsigned int y)
{
	if (ny > y) //! Checks to see if y is greater 
		return GRT;
	else
	{
		if (ny == y)			//! Checks to see if the y's are the same 
		{
			if (nx > x)			//! Sees if x is greater then returns greater
				return GRT;
			else if (nx == x)	//! Sees if x is the same then returns equal to if true and less than if false 
				return EQT;
			else
				return LST;
		}
		else
		{
			return LST;		
		}
	}
}
