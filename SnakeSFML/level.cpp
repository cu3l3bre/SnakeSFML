//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////


#include "level.h"
#include <iostream>

using namespace std;


// STD - Constructor
Level::Level()
{
	gameRunning = false;
	gameOver = false;
	foodOnField = false;
	foodCount = 0;
	score = 0.0;



	rectangleSize.x = 10;
	rectangleSize.y = 10;

	boundary.setSize(rectangleSize);
	boundary.setFillColor(sf::Color::Red);

	food.setRadius(5.f);
	food.setFillColor(sf::Color::Yellow);





	/*
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//levelPoints[i][j] = char(0);
		}
	}
	*/
}


// Destructor
Level::~Level(){}


// Methods
/*
void Level::drawBoundaries()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if ((i == 0) || (j == 0) || (i == (rows - 1)) || (j == (cols - 1)))
			{
				levelPoints[i][j] = BOUNDARY;
			}
			else
			{
				levelPoints[i][j] = EMPTYFIELD;
			}
		}
	}
}
*/


/************************************************************/
// Method for update all items in the game
// Boundieres, Snake, Food etc.
/*
void Level::updateLevel()
{
	int snakeIndex = 0;


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if ((i == 0) || (j == 0) || (i == (rows - 1)) || (j == (cols - 1)))
			{
				levelPoints[i][j] = BOUNDARY;
			}
			else if ((i == foodLocation.row) && (j == foodLocation.col))
			{
				levelPoints[i][j] = FOOD;
			}
			else {
				levelPoints[i][j] = EMPTYFIELD;
			}

			for (snakeIndex = 0; snakeIndex < snake.snakePoints.size(); snakeIndex++)
			{
				if ((i == snake.snakePoints[snakeIndex].row) && (j == snake.snakePoints[snakeIndex].col) &&
					(snakeIndex == 0))
				{
					levelPoints[i][j] = SNAKEHEAD;
				}

				else if ((i == snake.snakePoints[snakeIndex].row) && (j == snake.snakePoints[snakeIndex].col) &&
					(snakeIndex > 0))
				{
					levelPoints[i][j] = SNAKEBODY;
				}
			}
		}
	}
}
*/

/*
// Mehtod for drawing all items in the console
void Level::drawLevel()
{
	system("cls");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << levelPoints[i][j];
		}
		cout << endl;
	}
}
*/
/************************************************************/



// GameOver is When Head of Snake is in its body or boundaries
void Level::checkGameOver()
{
	//bool gameOver = false;
	// Starts at 1 because Head is 0
	for (int i = 1; i < snake.snakePoints.size(); i++)
	{
		// Check if snakes head is in its body
		if ((snake.snakePoints[0].row) == (snake.snakePoints[i].row) &&
			(snake.snakePoints[0].col) == (snake.snakePoints[i].col))
		{
			gameOver = true;
		}
		// Check if snakes head is in boundaries
		else if ((snake.snakePoints[0].row == 5) || (snake.snakePoints[0].row == 495) ||
			(snake.snakePoints[0].col == 5) || (snake.snakePoints[0].col == 495))
		{
			gameOver = true;
		}
	}
}


// Generate food at random location
void Level::generateFood()
{
	bool foodGeneratedOnSnake = true;

	while (foodGeneratedOnSnake)
	{
		bool foodOnSnake = false;

		// example
		// rows = 10;
		// boundaries are on 0 and 9
		// with %8 we would get numbers from 0 to 7
		// thats why we add +1 and we get numbers from 1 to 8 which are in the field


		foodLocation.row = ((rand() % 95)+ 3)*5;		// -2 because we dont want to spawn it on the boundaries
		if ((foodLocation.row % 10) == 0)
		{
			foodLocation.row += 5;
		}

		foodLocation.col = ((rand() % 95)+ 3)*5;
		if ((foodLocation.col % 10) == 0)
		{
			foodLocation.col += 5;
		}

		// check if food has been generated on snake
		for (int i = 0; i < snake.snakePoints.size(); i++)
		{
			if ((snake.snakePoints[i].row == foodLocation.row) && (snake.snakePoints[i].col == foodLocation.col))
			{
				foodOnSnake = true;
			}
		}

		if (foodOnSnake)
		{
			// excute while loop one more time
			foodGeneratedOnSnake = true;
		}
		else
		{
			// exit the while loop
			foodGeneratedOnSnake = false;
		}
	}

	// Set Drwaing Origin for shape
	food.setPosition(foodLocation.col - 5, foodLocation.row - 5);

}


//add new body part to snake if it has eaten some food
void Level::eatFood()
{
	foodOnField = false;
	Point newBodyPart;
	newBodyPart.row = 0;
	newBodyPart.col = 0;
	snake.snakePoints.push_back(newBodyPart);
	foodCount++;
}



void Level::calculateStats()
{
	timeElapsed = clock.getElapsedTime();

	score = round((((foodCount + 1) * 10) - (timeElapsed.asSeconds()*0.4)) * 100);

	timeNow = time(0);
	localtime_s(&nowLocal, &timeNow);

	year = nowLocal.tm_year + 1900;
	month = nowLocal.tm_mon + 1;
	day = nowLocal.tm_mday;
	hour = nowLocal.tm_hour;
	minute = nowLocal.tm_min;
	seconds = nowLocal.tm_sec;
}


void Level::showStats()
{
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! GAME OVER !!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "Your Run lastet " << timeElapsed.asSeconds() << " seconds! and ate " << foodCount << " Food! Good Job :)" << endl;
	cout << "Your total score is: " << score << " Keep up the good work!" << endl;
	cout << "Played on " << day << "." << month << "." << year << " at " << hour << ":" << minute << ":" << seconds << endl;
}


void Level::createBoundaries()
{
	for (int i = 5; i <= 495; i += 5)
	{
		for (int j = 5; j <= 495; j += 5)
		{
			if ((i == 5) || (j == 5) || (i == 495) || (j == 495))
			{

				boundary.setPosition(i - 5, j - 5);	// set the origin of each boundary
				boundaries.push_back(boundary);
			}
		}
	}


}