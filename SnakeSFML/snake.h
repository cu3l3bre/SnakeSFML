//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "point.h"
#include "vector"


// Enum for Movement directions for the snake
enum SnakeDirection
{
	SnakeUp,
	SnakeRight,
	SnakeDown,
	SnakeLeft
};


class Snake
{
private:




public:
	Snake();
	~Snake();
	void updateSnake();


	int snakeLength;
	int direction; // 0 = up, 1 = right; 2 = down , 3 = left

	Point initLocation;
	Point location;
	std::vector<Point> snakePoints;

};