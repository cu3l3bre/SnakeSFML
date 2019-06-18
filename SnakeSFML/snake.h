//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "point.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define SHAPESIZE 10

// Enum for Movement directions for the snake
enum SnakeDirection
{
	SnakeUp,
	SnakeRight,
	SnakeDown,
	SnakeLeft
};

// Note to SnakeDirection
// if we do +1 on each direction, we cycle through it clockwise
// if we do -1 on each direction, we cycle through it counterclockwise
// but need to pay attention if we are on 0 and do -1 , that would be -1 which would equal 3
// same is when direction is 3 and we do +1, that would be 4 , in that case it would be 0
// so we have to check for that "overflow"

//							SnakeUp = 0
//
//		SnakeLeft = 3							SnakeRight = 1
//
//							SnakeDown = 2



class Snake
{
public:

	int snakeLength;
	int direction;		// 0 = up, 1 = right; 2 = down , 3 = left

	Point location;
	std::vector<Point> snakePoints;

	int circleRadius;
	int stepSize;
	int offsetOrigin;

	sf::CircleShape head;
	sf::CircleShape body;
	std::vector<sf::CircleShape> snakebody;




	Snake();
	~Snake();
	void updateSnake();
	void setSnakeDirection();
	void checkDirectionOverflow();
};