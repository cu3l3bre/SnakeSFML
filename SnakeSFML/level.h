//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "point.h"
#include <vector>
#include "time.h"
#include "snake.h"
#include <SFML/System/Clock.hpp>

/*
#define EMPTYFIELD char(0);
#define BOUNDARY '#';
#define SNAKEHEAD 'X';
#define SNAKEBODY '0';
#define FOOD char(148);
*/

using namespace std;

class Level
{
public:
	/*
	int rows = 20;
	int cols = 20;
	int points;
	char levelPoints[20][20];
	*/
	Snake snake;


	Point foodLocation;
	bool foodOnField;;
	int foodCount;
	double score;
	bool gameOver;
	bool gameRunning;

	sf::Time timeElapsed;
	sf::Clock clock;

	tm nowLocal;
	time_t timeNow;
	time_t gameStartTime;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int seconds;


	Level();
	~Level();

	// Methods

	//void drawBoundaries();
	//void updateLevel();

	//void drawLevel();
	void checkGameOver();

	void generateFood();
	void eatFood();

	void calculateStats();
	void showStats();
};