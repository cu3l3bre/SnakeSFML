//////////////////////////////////////////////////////////////////////////////////////////////
//																							//
//	Author:		DS																			//
//	Created:	2019.06.17																	//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "point.h"
#include <vector>
#include <fstream>
#include <string>
#include "time.h"
#include "snake.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>



class Level
{
public:


	Snake snake;

	Point foodLocation;
	bool foodOnField;;
	int foodCount;
	int score;
	bool gameOver;
	bool gameRunning;

	std::string pathToHighscoreFile;
	
	std::string oneLine;
	std::vector<std::string> fileContent;

	int currentHighscoreScore;
	std::string currentHighscoreDate;

	sf::Vector2f rectangleSize;
	sf::RectangleShape boundary;
	std::vector<sf::RectangleShape> boundaries;


	sf::CircleShape food;

	//sf::Font font;

	sf::FloatRect bounds;
	sf::Text txt_instrcution;
	sf::Text txt_instrcution2;
	sf::Text txt_instrcution3;
	sf::Text txt_gameOver;
	sf::Text txt_playtimeFood;
	sf::Text txt_totalScore;
	sf::Text txt_date;


	std::string scoreString;
	std::string foodString;
	std::string timeElapsedString;
	std::string yearString;
	std::string monthString;
	std::string dayString;
	std::string hourString;
	std::string minuteString;




	int circleRadius;
	int stepSize;
	int offsetOrigin;



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
	Level(sf::Font*);
	~Level();

	// Methods

	void createBoundaries();

	void checkGameOver();

	void generateFood();
	void eatFood();
	void checkSnakeAteFood();

	void calculateStats();
	void showStats();

	void prepareStats();
	void readHighScoresFromFile();
	void writeHighScoresToFile();
};